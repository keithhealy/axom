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

#include "axom/quest/stl/STLReader.hpp"

#include "axom/core/utilities/Utilities.hpp"  // isLittleEndian()/swapEndian()

// Mint includes
#include "axom/mint/config.hpp"          // for mint::IndexType
#include "axom/mint/mesh/CellTypes.hpp"       // for mint::Triangle

// Slic includes
#include "axom/slic/interface/slic.hpp"            // for SLIC macros

// C/C++ includes
#include <fstream>   // for ifstream


namespace
{
const std::size_t BINARY_HEADER_SIZE = 80;      // bytes
const std::size_t BINARY_TRI_SIZE = 50;         // bytes
}


//------------------------------------------------------------------------------
//      STLReader Implementation
//------------------------------------------------------------------------------
namespace axom
{
namespace quest
{

STLReader::STLReader() :
  m_fileName(""),
  m_num_nodes(0),
  m_num_faces(0)
{}

//------------------------------------------------------------------------------
STLReader::~STLReader()
{
  this->clear();
}

//------------------------------------------------------------------------------
void STLReader::clear()
{
  m_num_nodes = 0;
  m_num_faces = 0;
  m_nodes.clear();
}

//------------------------------------------------------------------------------
bool STLReader::isAsciiFormat() const
{
  // The binary format consists of
  //    a header of size BINARY_HEADER_SIZE==80 bytes
  //    followed by a four byte int encoding the number of triangles
  //    followed by the triangle data (BINARY_TRI_SIZE == 50 bytes per triangle)

  // Open the file
  std::ifstream ifs( m_fileName.c_str(), std::ios::in| std::ios::binary);

  if ( !ifs.is_open() )
  {
    /* short-circuit */
    SLIC_WARNING( "Cannot open the provided STL file [" << m_fileName << "]" );
    return false;
  }

  // Find out the file size
  ifs.seekg(0, ifs.end);
  common::int32 fileSize = static_cast< common::int32>(ifs.tellg());

  const int totalHeaderSize =
    (BINARY_HEADER_SIZE + sizeof( common::int32 ) );
  if(fileSize < totalHeaderSize)
    return true;

  // Find the number of triangles (if the file were binary)
  int numTris = 0;
  ifs.seekg(BINARY_HEADER_SIZE, ifs.beg);
  ifs.read( (char*)&numTris, sizeof( common::int32));

  if ( !utilities::isLittleEndian() )
  {
    numTris = utilities::swapEndian(numTris);
  }

  // Check if the size matches our expectation
  int expectedBinarySize = totalHeaderSize + (numTris * BINARY_TRI_SIZE);

  ifs.close();

  return (fileSize != expectedBinarySize);
}

//------------------------------------------------------------------------------
int STLReader::readAsciiSTL()
{
  std::ifstream ifs( m_fileName.c_str());

  if ( !ifs.is_open() )
  {
    SLIC_WARNING( "Cannot open the provided STL file [" << m_fileName << "]" );
    return ( -1 );
  }

  std::string junk;
  double x,y,z;

  // In an STL  file, we only care about the vertex positions
  // Vertices are strings of the form: "vertex v_x v_y v_z"
  while(true)
  {
    do
    {
      ifs >> junk;
    }
    while( ifs.good() && junk != "vertex");

    if(ifs.fail())
      break;

    ifs >> x >> y >> z;
    m_nodes.push_back(x);
    m_nodes.push_back(y);
    m_nodes.push_back(z);
  }

  // Set the number of nodes and faces
  m_num_nodes = m_nodes.size() / 3;
  m_num_faces = m_num_nodes / 3;

  ifs.close();
  return ( 0 );
}

//------------------------------------------------------------------------------
int STLReader::readBinarySTL()
{
  // Binary STL format consists of
  //    an 80 byte header (BINARY_HEADER_SIZE)
  //    followed by a 32 bit int encoding the number of faces
  //    followed by the triangles, each of which is 50 bytes (BINARY_TRI_SIZE)

  // A local union data structure for triangles in a binary STL
  union BinarySTLTri
  {
    common::int8 raw[BINARY_TRI_SIZE];
    struct
    {
      float normal[3];
      float vert[9];
      common::uint16 attr;
    };
  } tri;

  bool const isLittleEndian = axom::utilities::isLittleEndian();

  // Open binary file, skip the header
  std::ifstream ifs( m_fileName.c_str(), std::ios::in| std::ios::binary);
  if ( !ifs.is_open() )
  {
    SLIC_WARNING( "Cannot open the provided STL file [" << m_fileName << "]" );
    return ( -1 );
  }

  ifs.seekg(BINARY_HEADER_SIZE);

  // read the num faces and reserve room for the vertex positions
  ifs.read( (char*)&m_num_faces, sizeof( common::int32 ) );

  if ( !isLittleEndian )
  {
    m_num_faces = utilities::swapEndian(m_num_faces);
  }

  m_num_nodes = m_num_faces * 3;
  m_nodes.reserve( m_num_nodes * 3);

  // Read the triangles. Cast to doubles and ignore normals and attributes
  for( mint::IndexType i=0 ; i < m_num_faces ; ++i)
  {
    ifs.read( (char*)tri.raw, BINARY_TRI_SIZE);

    for(int j=0 ; j<9 ; ++j)
    {
      float coord = isLittleEndian ?
                    tri.vert[j] : utilities::swapEndian(tri.vert[j]);

      m_nodes.push_back( static_cast<double>( coord) );
    }
  }

  ifs.close( );

  return ( 0 );

}


//------------------------------------------------------------------------------
int STLReader::read()
{
  if ( m_fileName.empty() )
  {
    return ( -1 );
  }

  // Clear internal data, check the format and load the data
  this->clear();

  int rc = ( isAsciiFormat() ) ? readAsciiSTL() : readBinarySTL();
  return ( rc );
}

//------------------------------------------------------------------------------
void STLReader::getMesh(
  axom::mint::UnstructuredMesh< mint::SINGLE_SHAPE >* mesh )
{
  /* Sanity checks */
  SLIC_ERROR_IF( mesh == nullptr,
                 "supplied mesh is null!" );
  SLIC_ERROR_IF(
    static_cast< mint::IndexType >(m_nodes.size()) != 3*m_num_nodes,
    "nodes vector size doesn't match expected size!" );
  SLIC_ERROR_IF( mesh->getDimension() != 3,
                 "STL reader expects a 3D mesh!" );
  SLIC_ERROR_IF( mesh->getCellType() != mint::TRIANGLE,
                 "STL reader expects a triangle mesh!" );

  // pre-allocate space to store the mesh
  mesh->reserve( m_num_nodes, m_num_faces );

  // Load the vertices into the mesh
  for ( mint::IndexType i=0 ; i < m_num_nodes ; ++i )
  {
    const mint::IndexType offset = i*3;
    mesh->appendNode( m_nodes[ offset   ],
                      m_nodes[ offset+1 ],
                      m_nodes[ offset+2 ]   );
  }

  // Load the triangles.  Note that the indices are implicitly defined.
  for ( mint::IndexType i=0 ; i < m_num_faces ; ++i )
  {
    mint::IndexType tv[3] = {3*i, 3*i+1, 3*i+2};
    mesh->appendCell( tv );
  }

}

} // end namespace quest
} // end namespace axom