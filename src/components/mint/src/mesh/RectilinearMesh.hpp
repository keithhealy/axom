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

#ifndef MINT_RECTILINEARMESH_HPP_
#define MINT_RECTILINEARMESH_HPP_

#include "mint/StructuredMesh.hpp" // base class
#include "mint/config.hpp"         // for compile-time definitions

namespace axom
{
namespace mint
{

// Forward Declarations
template < typename T >
class Array;

/*!
 * \class RectilinearMesh
 *
 * \brief Provides the ability to represent and operate on a structured
 *  rectilinear mesh.
 *
 * The RectilinearMesh object extends the StructuredMesh base class and adds
 * the ability to represent and operate on structured, rectilinear meshes.
 *
 * A <em> RectilinearMesh </em> divides the solution domain in nodes and cells
 * that are arranged on a regular lattice that is axis-aligned with the
 * Cartesian coordinate axes. Consequently, the cells are always rectangular.
 * Due to the regular topology, each node/cell on the mesh can be uniquely
 * identified by a corresponding logical i-j-k index. However, the nodal
 * coordinates along each axis are explicitly defined and may have variable
 * spacing in between them. Given a logical i-j-k index of a node, the physical
 * coordinates of the corresponding node can be evaluated by taking the
 * Cartesian product of the corresponding coordinate along each direction. For
 * that reason, <em> rectilinear </em> meshes are also often called product
 * meshes.
 *
 * A <em> RectilinearMesh </em> object may be constructed using (a) a native
 * constructor, (b) an external constructor, or (c) Sidre, when Mint is
 * compiled with Sidre support.
 *
 * * <b> Native Constructor </b>
 *
 *   When using native storage, the RectilinearMesh object owns all associated
 *   memory. Once the object is deleted, all memory is returned to the system.
 *
 * * <b> External Constructor </b>
 *
 *   A RectilinearMesh may also be constructed from externally supplied
 *   coordinate buffers. In this case, the callind code owns the memory and is
 *   responsible for properly deallocating the supplied buffers.
 *
 * * <b> Sidre Constructor </b>
 *
 *   A RectilinearMesh may also be constructed and be associated with a
 *   sidre::Group. In this case, all memory is managed by Sidre. Once the
 *   object goes out-of-scope the data remains persistent in Sidre. Last,
 *   the data is stored in Sidre according to the conventions described in the
 *   <a href="http://llnl-conduit.readthedocs.io/en/latest/"> computational
 *   mesh blueprint </a>.
 *
 * \see StructuredMesh
 * \see Extent
 */
class RectilinearMesh : public StructuredMesh
{
public:

  /*!
   * \brief Default constructor. Disabled.
   */
  RectilinearMesh() = delete;

/// \name Native Constructors
/// @{

  /*!
   * \brief Constructs a rectilinear mesh of specified dimension and extent.
   *
   * \param [in] dimension the dimension of the mesh.
   * \param [in] ext the mesh extent
   *
   * \note The supplied `ext` pointer must point to a buffer that has at least
   * \f$ 2 \times N \f$ entries, where N is the dimension of the uniform mesh
   * given in the following order: [imin, imax, jmin, jmax, kmin, kmax]
   *
   * \pre 1 <= dimension <= 3
   * \pre ext != AXOM_NULLPTR
   *
   * \post getDimension() == dimension
   * \post getCoordinateArray( i ) != AXOM_NULLPTR \f$ \forall i \f$
   * \post hasSidreGroup() == false
   * \post isExternal() == false
   */
  RectilinearMesh( int dimension, const int64* ext );

  /*!
   * \brief Constructs a rectilinear mesh of specified dimensions.
   *
   * \param [in] Ni number of nodes in the i-direction
   * \param [in] Nj number of nodes in the j-direction (for dimension >= 2)
   * \param [in] Nk number of nodes in the k-direction (for dimension == 3)
   *
   * \pre Ni >= 1
   * \pre Nj >= 1 iff dimension >= 2
   * \pre Nk >= 1 iff dimension == 3
   *
   * \post 1 <= dimension <= 3
   * \post getCoordinateArray( i ) != AXOM_NULLPTR \f$ \forall i \f$
   * \post hasSidreGroup() == false
   * \post isExternal() == false
   */
  RectilinearMesh( IndexType Ni,
                   IndexType Nj=-1,
                   IndexType Nk=-1  );

/// @}

/// \name External Constructors
/// @{

  /*!
   * \brief Constructs a rectilinear mesh with the specified logical extent and
   *  external coordinate buffers.
   *
   * \param [in] ext the mesh logical extent.
   * \param [in] x coordinates along the i-direction
   * \param [in] y coordinates along the j-direction (required for 2D/3D)
   * \param [in] z coordinates along the k-direction (required for 3D only)
   *
   * \note The supplied `ext` pointer must point to a buffer that has at least
   * \f$ 2 \times N \f$ entries, where N is the dimension of the uniform mesh
   * given in the following order: [imin, imax, jmin, jmax, kmin, kmax]
   *
   * \note The calling code maintains ownership of the supplied coordinate
   *  buffers and the responsibility of properly deallocating them.
   *
   * \pre ext != AXOM_NULLPTR
   * \pre x != AXOM_NULLPTR
   * \pre y != AXOM_NULLPTR iff dimension >= 2
   * \pre z != AXOM_NULLPTR iff dimension == 3
   *
   * \post 1 <= getDimesion() <= 3
   * \post getCoordinateArray( i ) != AXOM_NULLPTR \f$ \forall i \f$
   * \post hasSidreGroup() == false.
   * \post isExternal() == true
   */
  RectilinearMesh( const int64* ext,
                   double* x,
                   double* y=AXOM_NULLPTR,
                   double* z=AXOM_NULLPTR );
/// @}

#ifdef MINT_USE_SIDRE

/// \name Sidre Constructors
/// @{

  /*!
   * \brief Creates a RectilinearMesh from the supplied Sidre group.
   *
   * \param [in] group pointer to the Sidre group associated with the mesh
   * \param [in] topo the name of the topology for this mesh (optional).
   *
   * \note The supplied group is expected to contain a valid curvilinear
   *  structured mesh instance that is conforming to the conventions described
   *  in the conduit <a href="http://llnl-conduit.readthedocs.io/en/latest/">
   *  computational mesh blueprint </a>.
   *
   * \note If a topology name is not provided, the implementation will use the
   *  1st topology group under the parent "topologies" group.
   *
   * \note When using this constructor, all data is owned by Sidre. Once the
   *  mesh object goes out-of-scope, the data will remain persistent in Sidre.
   *
   * \pre group != AXOM_NULLPTR
   * \pre blueprint::validRootGroup( group )
   *
   * \post hasSidreGroup() == true
   * \post isExternal() == false
   */
  explicit RectilinearMesh( sidre::Group* group,
                            const std::string& topo="" );

  /*!
   * \brief Creates a RectilinearMesh with the specified logical extent that is
   *  bound to the supplied Sidre group.
   *
   * \param [in] dimension the dimension of the mesh
   * \param [in] ext array that holds the logical extent of the mesh
   * \param [in] group pointer to the Sidre group where the to store the mesh.
   * \param [in] topo the name of the associated topology (optional)
   * \param [in] coordset the name of the associated coordset (optional)
   *
   * \note The supplied `ext` pointer must point to a buffer that has at least
   * \f$ 2 \times N \f$ entries, where N is the dimension of the uniform mesh
   * given in the following order: [imin, imax, jmin, jmax, kmin, kmax]
   *
   * \note If a topology and coordset name is not provided, internal defaults
   *  will be used by the implementation.
   *
   * \note When using this constructor, all data is owned by Sidre. Once the
   *  mesh object goes out-of-scope, the data will remain persistent in Sidre.
   *
   * \pre ext != AXOM_NULLPTR
   * \pre group != AXOM_NULLPTR
   * \pre group->getNumViews()==0
   * \pre group->getNumGroups()==0
   *
   * \post hasSidreGroup() == true
   * \post isExternal() == false
   */
  RectilinearMesh( int dimension,
                   const int64* ext,
                   sidre::Group* group,
                   const std::string& topo="",
                   const std::string& coordset="" );

  /*!
   * \brief Creates a RectilinearMesh instance of specified dimensions that is
   *  bound to the supplied Sidre group.
   *
   * \param [in] group pointer to the Sidre group where to store the mesh.
   * \param [in] topo the name of the associated topology (optional)
   * \param [in] coordset the name of the associated coordset (optional)
   * \param [in] Ni number of nodes in the i-direction
   * \param [in] Nj number of nodes in the j-direction (for 2D or 3D)
   * \param [in] Nk number of nodes in the k-direction (for 3D only)
   *
   * \note If a topology and coordset name is not provided, internal defaults
   *  will be used by the implementation.
   *
   * \note When using this constructor, all data is owned by Sidre. Once the
   *  mesh object goes out-of-scope, the data will remain persistent in Sidre.
   *
   * \pre Ni >= 1
   * \pre Nj >= 1 iff dimesion >=2
   * \pre Nk >= 1 iff dimesion == 3
   *
   * \pre group != AXOM_NULLPTR
   * \pre group->getNumViews()==0
   * \pre group->getNumGroups()==0
   *
   * \post hasSidreGroup() == true
   * \post isExternal() == false
   *
   */
  /// @{

  RectilinearMesh( sidre::Group* group,
                   const std::string& topo,
                   const std::string& coordset,
                   IndexType Ni,
                   IndexType Nj=-1,
                   IndexType Nk=-1  );

  RectilinearMesh( sidre::Group* group,
                   IndexType Ni,
                   IndexType Nj=-1,
                   IndexType Nk=-1  );

  /// @}

/// @}
#endif

/// \name Virtual methods
/// @{

  /*!
   * \brief Destructor.
   */
  virtual ~RectilinearMesh();

  /*!
   * \brief Returns true if coordinates of the mesh are externally supplied.
   * \return status true if the coordinates point to external buffers.
   */
  virtual bool isExternal() const final override
  { return m_coordinates[ 0 ]->isExternal(); }

  /*!
   * \brief Copy the coordinates of the given node into the provided buffer.
   *
   * \param [in] nodeID the ID of the node in question.
   * \param [in] coords the buffer to copy the coordinates into, of length at
   *  least getDimension().
   *
   * \note This method is provided primarily for convenience. It is a virtual
   *  method and should be used with caution. We advise to not call this method
   *  inside a tight loop to avoid the performance overhead of virtual calls.
   *  Instead, opt to use getCoordinateArray() method which can give direct
   *  memory access to the coordinates of a node.
   *
   * \pre 0 <= nodeID < getNumberOfNodes()
   * \pre coords != AXOM_NULLPTR
   */
  virtual void getNode( IndexType nodeID, double* node ) const final override;

  /*!
   * \brief Returns pointer to the nodal positions in the specified dimension.
   *
   * \param[in] dim the specified dimension
   *
   * \note the returned buffer is of length getNumberOfNodesAlongDim( dim ).
   *
   * \pre dim >= 0 && dim < dimension()
   * \pre dim == X_COORDINATE || dim == Y_COORDINATE || dim == Z_COORDINATE
   */
  /// @{

  virtual double* getCoordinateArray( int dim ) final override;
  virtual const double* getCoordinateArray( int dim ) const final override;

  /// @}

/// @}

private:

  /*!
   * \brief Initializes the RectilinearMesh
   * \note Helper method to be called from a constructor.
   */
  void initialize();

  /*!
   * \brief Allocates buffers for the coordinates along each coordinate axis.
   * \note Helper method to be called from constructors.
   */
  void allocateCoords();

#ifdef MINT_USE_SIDRE

  /*!
   * \brief Allocates buffers for the coorindates on Sidre.
   * \note Helper method to be called from Sidre constructors.
   */
  void allocateCoordsOnSidre();

#endif

  Array< double >* m_coordinates[3] = {AXOM_NULLPTR,AXOM_NULLPTR,AXOM_NULLPTR};

  DISABLE_COPY_AND_ASSIGNMENT( RectilinearMesh );
  DISABLE_MOVE_AND_ASSIGNMENT( RectilinearMesh );
};

} /* namespace mint */
} /* namespace axom */

#endif /* RECTILINEARMESH_HXX_ */
