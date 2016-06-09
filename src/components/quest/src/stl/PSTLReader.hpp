/*
 * $Id$
 */

/*!
 *******************************************************************************
 * \file PSTLReader.hpp
 *
 * \date Mar 10, 2016
 * \author George Zagaris (zagaris2@llnl.gov)
 *******************************************************************************
 */

#ifndef PSTLREADER_HPP_
#define PSTLREADER_HPP_

#include "common/ATKMacros.hpp"
#include "quest/STLReader.hpp" // base class

#include "mpi.h"

namespace quest
{

class PSTLReader : public STLReader
{
public:

  /*!
   *****************************************************************************
   * \brief Constructor.
   * \param [in] comm user-supplied MPI communicator.
   *****************************************************************************
   */
  PSTLReader( MPI_Comm comm );

  /*!
   *****************************************************************************
   * \brief Destructor.
   *****************************************************************************
   */
  virtual ~PSTLReader();

  /*!
   *****************************************************************************
   * \brief Reads in an STL file to all ranks in the associated communicator.
   * \note Rank 0 reads in the STL mesh file and broadcasts the data the rest
   *  of the ranks.
   *****************************************************************************
   */
  virtual void read();

private:

  /*!
   *****************************************************************************
   * \brief Default constructor. Does nothing.
   * \note Made private to prevent its use in application code.
   *****************************************************************************
   */
  PSTLReader(): m_comm(MPI_COMM_NULL), m_my_rank(0) { };

  MPI_Comm m_comm; /*!< MPI communicator */
  int m_my_rank;   /*!< MPI rank ID      */

  DISABLE_COPY_AND_ASSIGNMENT( PSTLReader );
};

} /* namespace quest */

#endif /* PSTLREADER_HPP_ */