/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Copyright (c) 2017-2018, Lawrence Livermore National Security, LLC.
 *
 * Produced at the Lawrence Livermore National Laboratory
 *
 * LLNL-CODE-741217
 *
 * All rights reserved.
 *
 * This file is part of Axom.
 *
 * For details about use and distribution, please read axom/LICENSE.
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
// Axom includes
#include "axom/config.hpp"                   // for compile-time definitions

// Mint includes
#include "axom/mint/config.hpp"              // mint compile-time definitions
#include "axom/mint/execution/policy.hpp"    // mint execution policies/traits
#include "axom/mint/execution/interface.hpp" // for_all()

// Slic includes
#include "axom/slic.hpp" // for SLIC macros

#include "mint_test_utilities.hpp"

// gtest includes
#include "gtest/gtest.h" // for gtest

namespace axom
{
namespace mint
{

//------------------------------------------------------------------------------
// HELPER METHODS
//------------------------------------------------------------------------------
namespace
{

template < typename ExecPolicy, int MeshType, int Topology=SINGLE_SHAPE >
void check_for_all_faces( int dimension )
{
  constexpr char* mesh_name = internal::mesh_type< MeshType, Topology >::name(); 
  SLIC_INFO( "dimension=" << dimension << ", policy="
            << policy_traits< ExecPolicy >::name() << ", mesh_type="
            << mesh_name );

  const IndexType Ni = 20;
  const IndexType Nj = (dimension >= 2) ? Ni : -1;
  const IndexType Nk = (dimension == 3) ? Ni : -1;

  const double lo[] = { -10, -9, -8 };
  const double hi[] = {  10,  9,  8 };
  UniformMesh uniform_mesh( lo, hi, Ni, Nj, Nk );

  using MESH = typename internal::mesh_type< MeshType, Topology >::MeshType;
  MESH* test_mesh = dynamic_cast< MESH* >( internal::create_mesh< MeshType, Topology >( uniform_mesh ) );
  EXPECT_TRUE( test_mesh != nullptr );

  const IndexType numFaces = test_mesh->getNumberOfFaces();

  IndexType* field = test_mesh->template createField< IndexType >( "f1", FACE_CENTERED );

  for_all_faces< ExecPolicy >( test_mesh, 
    AXOM_LAMBDA( IndexType faceID )
    {
      field[ faceID ] = faceID;
    }
  );

  for ( IndexType faceID = 0 ; faceID < numFaces ; ++faceID )
  {
    EXPECT_EQ( field[ faceID ], faceID );
  }

  delete test_mesh;
  test_mesh = nullptr;
}

//------------------------------------------------------------------------------
template < typename ExecPolicy, int MeshType, int Topology=SINGLE_SHAPE >
void check_for_all_face_nodes( int dimension )
{
  constexpr char* mesh_name = internal::mesh_type< MeshType, Topology >::name(); 
  SLIC_INFO( "dimension=" << dimension << ", policy="
            << policy_traits< ExecPolicy >::name() << ", mesh_type="
            << mesh_name );

  const IndexType Ni = 20;
  const IndexType Nj = (dimension >= 2) ? Ni : -1;
  const IndexType Nk = (dimension == 3) ? Ni : -1;

  const double lo[] = { -10, -9, -8 };
  const double hi[] = {  10,  9,  8 };
  UniformMesh uniform_mesh( lo, hi, Ni, Nj, Nk );

  using MESH = typename internal::mesh_type< MeshType, Topology >::MeshType;
  MESH* test_mesh = dynamic_cast< MESH* >( internal::create_mesh< MeshType, Topology >( uniform_mesh ) );
  EXPECT_TRUE( test_mesh != nullptr );

  const IndexType numFaces = test_mesh->getNumberOfFaces();
  IndexType* conn = test_mesh->template createField< IndexType >( "f1", FACE_CENTERED, MAX_FACE_NODES );

  for_all_faces< ExecPolicy, xargs::nodeids >( test_mesh,
    AXOM_LAMBDA( IndexType faceID, const IndexType* nodes, IndexType N)
    {
      for ( int i = 0 ; i < N ; ++i )
      {
        conn[ faceID * MAX_FACE_NODES + i ] = nodes[ i ];
      } // END for all face nodes
    }
  );

  IndexType faceNodes[ MAX_FACE_NODES ];
  for ( IndexType faceID = 0 ; faceID < numFaces ; ++faceID )
  {
    const IndexType N = test_mesh->getFaceNodeIDs( faceID, faceNodes );
    for ( int i = 0 ; i < N ; ++i )
    {
      EXPECT_EQ( conn[ faceID * MAX_FACE_NODES + i ], faceNodes[ i ] );
    }
  }  // END for all cells

  /* clean up */
  delete test_mesh;
  test_mesh = nullptr;
}

//------------------------------------------------------------------------------
template < typename ExecPolicy, int MeshType, int Topology=SINGLE_SHAPE >
void check_for_all_face_coords( int dimension )
{
  constexpr char* mesh_name = internal::mesh_type< MeshType, Topology >::name(); 
  SLIC_INFO( "dimension=" << dimension << ", policy="
            << policy_traits< ExecPolicy >::name() << ", mesh_type="
            << mesh_name );

  const IndexType Ni = 20;
  const IndexType Nj = (dimension >= 2) ? Ni : -1;
  const IndexType Nk = (dimension == 3) ? Ni : -1;

  const double lo[] = { -10, -9, -8 };
  const double hi[] = {  10,  9,  8 };
  UniformMesh uniform_mesh( lo, hi, Ni, Nj, Nk );

  using MESH = typename internal::mesh_type< MeshType, Topology >::MeshType;
  MESH* test_mesh = dynamic_cast< MESH* >( internal::create_mesh< MeshType, Topology >( uniform_mesh ) );
  EXPECT_TRUE( test_mesh != nullptr );

  const IndexType numFaces = test_mesh->getNumberOfFaces();
  IndexType* conn = test_mesh->template createField< IndexType >( "conn", FACE_CENTERED, MAX_FACE_NODES );
  double* coords = test_mesh->template createField< double >( "coords", FACE_CENTERED, dimension * MAX_FACE_NODES );

  for_all_faces< ExecPolicy, xargs::coords >( test_mesh,
    AXOM_LAMBDA( IndexType faceID, const numerics::Matrix<double> & coordsMatrix,
                 const IndexType * nodes)
    {
      const IndexType numNodes = coordsMatrix.getNumColumns();
      for ( int i = 0 ; i < numNodes ; ++i )
      {
        conn[ faceID * MAX_FACE_NODES + i ] = nodes[ i ];

        for ( int dim = 0; dim < dimension; ++dim )
        {
          coords[ faceID * dimension * MAX_FACE_NODES + i * dimension + dim ] = coordsMatrix( dim, i );
        }
      } // END for all face nodes
    }
  );

  double nodeCoords[3];
  IndexType faceNodes[ MAX_FACE_NODES ];
  for ( IndexType faceID = 0 ; faceID < numFaces ; ++faceID )
  {
    const IndexType numNodes = test_mesh->getFaceNodeIDs( faceID, faceNodes );
    for ( int i = 0 ; i < numNodes ; ++i )
    {
      EXPECT_EQ( conn[ faceID * MAX_FACE_NODES + i ], faceNodes[ i ] );

      for ( int dim = 0; dim < dimension; ++dim )
      {
        test_mesh->getNode( faceNodes[ i ], nodeCoords );
        EXPECT_NEAR( coords[ faceID * dimension * MAX_FACE_NODES + i * dimension + dim ], 
                     nodeCoords[ dim ],
                     1e-8 );
      }
    }
  }  // END for all cells

  /* clean up */
  delete test_mesh;
  test_mesh = nullptr;
}

//------------------------------------------------------------------------------
template < typename ExecPolicy, int MeshType, int Topology=SINGLE_SHAPE >
void check_for_all_face_cells( int dimension )
{
  constexpr char* mesh_name = internal::mesh_type< MeshType, Topology >::name(); 
  SLIC_INFO( "dimension=" << dimension << ", policy="
            << policy_traits< ExecPolicy >::name() << ", mesh_type="
            << mesh_name );

  const IndexType Ni = 20;
  const IndexType Nj = (dimension >= 2) ? Ni : -1;
  const IndexType Nk = (dimension == 3) ? Ni : -1;

  const double lo[] = { -10, -9, -8 };
  const double hi[] = {  10,  9,  8 };
  UniformMesh uniform_mesh( lo, hi, Ni, Nj, Nk );

  using MESH = typename internal::mesh_type< MeshType, Topology >::MeshType;
  MESH* test_mesh = dynamic_cast< MESH* >( internal::create_mesh< MeshType, Topology >( uniform_mesh ) );
  EXPECT_TRUE( test_mesh != nullptr );

  const IndexType numFaces = test_mesh->getNumberOfFaces();
  IndexType* faceCells = test_mesh->template createField< IndexType >( "f1", FACE_CENTERED, 2 );

  for_all_faces< ExecPolicy, xargs::cellids >( test_mesh,
    AXOM_LAMBDA( IndexType faceID, IndexType cellIDOne, IndexType cellIDTwo )
    {
      faceCells[ 2 * faceID + 0 ] = cellIDOne;
      faceCells[ 2 * faceID + 1 ] = cellIDTwo;
    }
  );

  for ( IndexType faceID = 0 ; faceID < numFaces ; ++faceID )
  {
    IndexType cellIDOne, cellIDTwo;
    test_mesh->getFaceCellIDs( faceID, cellIDOne, cellIDTwo );

    EXPECT_EQ( faceCells[ 2 * faceID + 0 ], cellIDOne );
    EXPECT_EQ( faceCells[ 2 * faceID + 1 ], cellIDTwo );
  }

  /* clean up */
  delete test_mesh;
  test_mesh = nullptr;
}

} /* end anonymous namespace */

//------------------------------------------------------------------------------
// UNIT TESTS
//------------------------------------------------------------------------------

AXOM_CUDA_TEST( mint_execution_face_traversals, for_all_face_nodeids )
{
  for ( int dim = 2 ; dim <= 3 ; ++dim )
  {

    using seq_exec = policy::serial;
    check_for_all_face_nodes< seq_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_face_nodes< seq_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_face_nodes< seq_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_face_nodes< seq_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_face_nodes< seq_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#if defined(AXOM_USE_RAJA) && defined(AXOM_USE_OPENMP) && \
    defined(RAJA_ENABLE_OPENMP)

    using omp_exec = policy::parallel_cpu;
    check_for_all_face_nodes< omp_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_face_nodes< omp_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_face_nodes< omp_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_face_nodes< omp_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_face_nodes< omp_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#endif

#if defined(AXOM_USE_RAJA) && defined(AXOM_USE_CUDA) && \
    defined(RAJA_ENABLE_CUDA)

    using cuda_exec = policy::parallel_gpu< 512 >;
    check_for_all_face_nodes< cuda_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_face_nodes< cuda_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_face_nodes< cuda_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_face_nodes< cuda_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_face_nodes< cuda_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );
#endif

  } // END for all dimensions
}

AXOM_CUDA_TEST( mint_execution_face_traversals, for_all_face_coords )
{
  for ( int dim = 2 ; dim <= 3 ; ++dim )
  {

    using seq_exec = policy::serial;
    check_for_all_face_coords< seq_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_face_coords< seq_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_face_coords< seq_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_face_coords< seq_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_face_coords< seq_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#if defined(AXOM_USE_RAJA) && defined(AXOM_USE_OPENMP) && \
    defined(RAJA_ENABLE_OPENMP)

    using omp_exec = policy::parallel_cpu;
    check_for_all_face_coords< omp_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_face_coords< omp_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_face_coords< omp_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_face_coords< omp_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_face_coords< omp_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#endif

#if defined(AXOM_USE_RAJA) && defined(AXOM_USE_CUDA) && \
    defined(RAJA_ENABLE_CUDA)

    using cuda_exec = policy::parallel_gpu< 512 >;
    check_for_all_face_coords< cuda_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_face_coords< cuda_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_face_coords< cuda_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_face_coords< cuda_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_face_coords< cuda_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );
#endif

  } // END for all dimensions
}

AXOM_CUDA_TEST( mint_execution_face_traversals, for_all_face_cellids )
{
  for ( int dim = 2 ; dim <= 3 ; ++dim )
  {

    using seq_exec = policy::serial;
    check_for_all_face_cells< seq_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_face_cells< seq_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_face_cells< seq_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_face_nodes< seq_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_face_nodes< seq_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#if defined(AXOM_USE_RAJA) && defined(AXOM_USE_OPENMP) && \
    defined(RAJA_ENABLE_OPENMP)

    using omp_exec = policy::parallel_cpu;
    check_for_all_face_cells< omp_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_face_cells< omp_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_face_cells< omp_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_face_nodes< omp_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_face_nodes< omp_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#endif

#if defined(AXOM_USE_RAJA) && defined(AXOM_USE_CUDA) && \
    defined(RAJA_ENABLE_CUDA)

    using cuda_exec = policy::parallel_gpu< 512 >;
    check_for_all_face_cells< cuda_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_face_cells< cuda_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_face_cells< cuda_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_face_nodes< cuda_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_face_nodes< cuda_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#endif

  } // END for all dimensions
}


//------------------------------------------------------------------------------
AXOM_CUDA_TEST( mint_execution_face_traversals, for_all_faces_index )
{
  for ( int dim = 2 ; dim <= 3 ; ++dim )
  {

    using seq_exec = policy::serial;
    check_for_all_faces< seq_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_faces< seq_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_faces< seq_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_faces< seq_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_faces< seq_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#if defined(AXOM_USE_RAJA) && defined(AXOM_USE_OPENMP) && \
    defined(RAJA_ENABLE_OPENMP)

    using omp_exec = policy::parallel_cpu;
    check_for_all_faces< omp_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_faces< omp_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_faces< omp_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_faces< omp_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_faces< omp_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#endif

#if defined(AXOM_USE_RAJA) && defined(AXOM_USE_CUDA) && \
    defined(RAJA_ENABLE_CUDA)

    using cuda_exec = policy::parallel_gpu< 512 >;
    check_for_all_faces< cuda_exec, STRUCTURED_UNIFORM_MESH >( dim );
    check_for_all_faces< cuda_exec, STRUCTURED_CURVILINEAR_MESH >( dim );
    check_for_all_faces< cuda_exec, STRUCTURED_RECTILINEAR_MESH >( dim );
    check_for_all_faces< cuda_exec, UNSTRUCTURED_MESH, SINGLE_SHAPE >( dim );
    check_for_all_faces< cuda_exec, UNSTRUCTURED_MESH, MIXED_SHAPE >( dim );

#endif

  } // END for all dimensions
}

} /* namespace mint */
} /* namespace axom */

//------------------------------------------------------------------------------
#include "axom/slic/core/UnitTestLogger.hpp"
using axom::slic::UnitTestLogger;

int main(int argc, char* argv[])
{
  int result = 0;

  ::testing::InitGoogleTest(&argc, argv);

  UnitTestLogger logger;  // create & initialize test logger,

  // finalized when exiting main scope

  result = RUN_ALL_TESTS();

  return result;
}
