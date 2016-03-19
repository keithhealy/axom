/*
 * Copyright (c) 2015, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * This source code cannot be distributed without permission and
 * further review from Lawrence Livermore National Laboratory.
 */

/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   Implementation file for DataView class.
 *
 ******************************************************************************
 */

// Associated header file
#include "DataView.hpp"

// Other toolkit project headers
#include "common/CommonTypes.hpp"
#include "slic/slic.hpp"

// SiDRe project headers
#include "DataBuffer.hpp"
#include "DataGroup.hpp"
#include "DataStore.hpp"

namespace asctoolkit
{
namespace sidre
{

/*
 *************************************************************************
 *
 * Allocate data for view, previously described.
 * The state may transition from EMPTY to BUFFER;
 * otherwise, the state must already be BUFFER.
 *
 *************************************************************************
 */
DataView * DataView::allocate()
{
  if ( isAllocateValid() )
  {
    if (m_state == EMPTY)
    {
      m_data_buffer = m_owning_group->getDataStore()->createBuffer();
      m_data_buffer->attachView(this);
      m_state = BUFFER;
    }

    TypeID type = static_cast<TypeID>(m_schema.dtype().id());
    SidreLength num_elems = m_schema.dtype().number_of_elements();
    m_data_buffer->allocate(type, num_elems);
    apply();
  }

  return this;
}

/*
 *************************************************************************
 *
 * Allocate data for view with type and number of elements.
 *
 *************************************************************************
 */
DataView * DataView::allocate( TypeID type, SidreLength num_elems)
{
  if ( num_elems < 0 )
  {
    SLIC_CHECK(num_elems >= 0);
    return this;
  }

  describe(type, num_elems);
  allocate();

  return this;
}

/*
 *************************************************************************
 *
 * Allocate data for view described by a Conduit data type object.
 *
 *************************************************************************
 */
DataView * DataView::allocate(const DataType& dtype)
{
  if ( dtype.is_empty() )
  {
    SLIC_CHECK_MSG( !dtype.is_empty(),
                    "Unable to allocate with empty data type.");
    return this;
  }

  describe(dtype);
  allocate();

  return this;
}

/*
 *************************************************************************
 *
 * Reallocate data for view to given number of elements.
 * This function requires that the view is already described.
 * The state may transition from EMPTY to BUFFER;
 * otherwise, the state must already be BUFFER.
 *
 *************************************************************************
 */
DataView * DataView::reallocate(SidreLength num_elems)
{
  TypeID vtype = static_cast<TypeID>(m_schema.dtype().id());

  if ( num_elems < 0 )
  {
    SLIC_CHECK_MSG(false, "num_elems must be >= 0");
  }
  else if ( isAllocateValid() )
  {
    if ( m_state == EMPTY )
    {
      allocate( vtype, num_elems);
    }
    else if ( m_data_buffer->isAllocated() )    //  XXX if ( isAllocated() )
    {
      describe(vtype, num_elems);
      m_data_buffer->reallocate(num_elems);
      apply();
    }
    else
    {
      allocate( vtype, num_elems );
    }
  }

  return this;
}

/*
 *************************************************************************
 *
 * Deallocate data for view.
 *
 *************************************************************************
 */
DataView * DataView::deallocate()
{
  if ( !isAllocateValid() )
  {
    SLIC_CHECK_MSG( isAllocateValid(),
                    "View " << this->getName() << "'s state " <<
                    getStateStringName(m_state) <<
                    " does not allow data deallocation");
    return this;
  }

  if ( hasBuffer() )
  {
    m_data_buffer->deallocate();
  }

  return this;
}

/*
 *************************************************************************
 *
 * Reallocate data for view using a Conduit data type object.
 *
 *************************************************************************
 */
DataView * DataView::reallocate(const DataType& dtype)
{
  // If we don't have an allocated buffer, we can just call allocate.
  if ( !isAllocated() )
  {
    return allocate(dtype);
  }

  TypeID type = static_cast<TypeID>(dtype.id());
  TypeID view_type = static_cast<TypeID>(m_schema.dtype().id());

  if (dtype.is_empty() || !isAllocateValid() || type != view_type)
  {
    SLIC_CHECK_MSG( !dtype.is_empty(),
                    "Unable to re-allocate with empty data type.");
    SLIC_CHECK_MSG( isAllocateValid(),
                    "View " << this->getName() << "'s state " <<
                    getStateStringName(m_state) <<
                    " does not allow data re-allocation");
    SLIC_CHECK_MSG( type == view_type,
                    "View " << this->getName() <<
                    " attempting to re-allocate with different type.");
    return this;
  }

  describe(dtype);
  SidreLength num_elems = dtype.number_of_elements();
  m_data_buffer->reallocate(num_elems);
  apply();

  return this;
}

/*
 *************************************************************************
 *
 * Attach buffer to view.
 *
 *************************************************************************
 */
DataView * DataView::attachBuffer(DataBuffer * buff)
{
  if ( !isAttachBufferValid() || buff == ATK_NULLPTR)
  {
    SLIC_CHECK_MSG( isAttachBufferValid(),
                    "View state " << getStateStringName(m_state) <<
                    " does not allow attaching buffer");
    SLIC_CHECK( buff != ATK_NULLPTR );
    return this;
  }

  buff->attachView(this);
  m_data_buffer = buff;
  m_state = BUFFER;
  m_is_applied = false;

  // If view is described and the buffer is allocated, then call apply.
  if ( isDescribed() && m_data_buffer->isAllocated() )
  {
    apply();
  }

  return this;
}

/*
 *************************************************************************
 *
 * Apply data description to data.
 *
 *************************************************************************
 */
DataView * DataView::apply()
{
  if ( !isApplyValid() )
  {
    SLIC_CHECK_MSG( isApplyValid(),
                    "View state, '" << getStateStringName(m_state) <<
                    "', does not allow apply operation");
    return this;
  }

  void * data_pointer = ATK_NULLPTR;

  if ( hasBuffer() )
  {
    data_pointer = m_data_buffer->getVoidPtr();
  }
  else
  {
    SLIC_ASSERT( m_state == EXTERNAL );
    data_pointer = m_external_ptr;
  }

  m_node.set_external(m_schema, data_pointer);
  m_is_applied = true;

  return this;
}

/*
 *************************************************************************
 *
 * Apply given # elems, offset, stride description to data view.
 *
 *************************************************************************
 */
DataView * DataView::apply(SidreLength num_elems,
                           SidreLength offset,
                           SidreLength stride)
{
  if ( num_elems < 0 || offset < 0 )
  {
    SLIC_CHECK(num_elems >= 0);
    SLIC_CHECK(offset >= 0);

    return this;
  }

  DataType dtype(m_schema.dtype());
  if ( dtype.is_empty() )
  {
    dtype = conduit::DataType::default_dtype(m_data_buffer->getTypeID());
  }

  dtype.set_number_of_elements(num_elems);
  dtype.set_offset(offset * dtype.element_bytes() );
  dtype.set_stride(stride * dtype.element_bytes() );

  describe(dtype);

  apply();

  return this;
}

/*
 *************************************************************************
 *
 * Apply given type, # elems, offset, stride desscription to data view.
 *
 *************************************************************************
 */
DataView * DataView::apply(TypeID type, SidreLength num_elems,
                           SidreLength offset,
                           SidreLength stride)
{
  if ( num_elems < 0 || offset < 0)
  {
    SLIC_CHECK(num_elems >= 0);
    SLIC_CHECK(offset >= 0);

    return this;
  }

  DataType dtype = conduit::DataType::default_dtype(type);

  size_t bytes_per_elem = dtype.element_bytes();

  dtype.set_number_of_elements(num_elems);
  dtype.set_offset(offset * bytes_per_elem);
  dtype.set_stride(stride * bytes_per_elem);

  describe(dtype);
  apply();

  return this;
}

/*
 *************************************************************************
 *
 * Apply given type, number of dimensions and shape to data view.
 * If ndims is 1 then do not save in m_shape.
 *
 *************************************************************************
 */
DataView * DataView::apply(TypeID type, int ndims, SidreLength * shape)
{
  if ( ndims < 1 || shape == ATK_NULLPTR )
  {
    SLIC_CHECK(ndims >= 1);
    SLIC_CHECK(shape != ATK_NULLPTR);

    return this;
  }

  describe(type, ndims, shape);
  apply();

  return this;
}

/*
 *************************************************************************
 *
 * Apply a data type description to data view.
 *
 *************************************************************************
 */
DataView * DataView::apply(const DataType &dtype)
{
  if ( dtype.is_empty() )
  {
    SLIC_CHECK_MSG( !dtype.is_empty(),
                    "Unable to apply description, data type is empty.");
    return this;
  }

  describe(dtype);
  apply();

  return this;
}

/*
 *************************************************************************
 *
 * Get void pointer to any data held by the view.
 *
 *************************************************************************
 */
void * DataView::getVoidPtr() const
{
  void * rv = ATK_NULLPTR;

  switch (m_state)
  {
  case EMPTY:
    SLIC_CHECK_MSG( m_state != EMPTY,
                    "Unable to retrieve raw pointer to data, view has no data.");
    break;
  case EXTERNAL:
    if (isApplied())
    {
      rv = const_cast<void *>(m_node.element_ptr(0));
    }
    else
    {
      rv = m_external_ptr;  // Opaque
    }
    break;
  case BUFFER:
    if (isApplied())
    {
      rv = const_cast<void *>(m_node.element_ptr(0));
    }
    else
    {
      SLIC_CHECK_MSG(false, "View has no applied data.");
    }
    break;
  case STRING:
  case SCALAR:
    rv = const_cast<void *>(m_node.element_ptr(0));
    break;
  default:
    SLIC_ASSERT_MSG(false, "Unexpected value for m_state");
  }

  return rv;
}

/*
 *************************************************************************
 *
 * Set data view to hold external data.
 *
 *************************************************************************
 */
DataView * DataView::setExternalDataPtr(void * external_ptr)
{
  if ( !isSetExternalDataPtrValid() )
  {
    SLIC_CHECK_MSG( isSetExternalDataPtrValid(),
                    "View state " << getStateStringName(m_state) <<
                    " does not allow setting external data pointer");
    return this;
  }

  m_external_ptr = external_ptr;
  m_state = EXTERNAL;

  if ( isDescribed() )
  {
    apply();
  }

  return this;
}

/*
 *************************************************************************
 *
 * Return true if view contains allocated data.  This could mean a buffer
 * with allocated data, or a scalar value, or a string.
 *
 * Note: Most of our isXXX functions are implemented in the header.
 * This one is in not, because we are only forward declaring the buffer
 * class in the view header.
 *************************************************************************
 */
bool DataView::isAllocated()
{
  bool rv = false;

  switch (m_state)
  {
  case EMPTY:
    SLIC_CHECK_MSG( m_state == EMPTY,
                    "isAllocated was called with an empty view, was this intentional?");
    break;
  case EXTERNAL:
    rv = m_external_ptr != ATK_NULLPTR;
    break;
  case BUFFER:
    // XXX what if buffer allocated but description is not applied. Look in Node?  isApplied?
    rv = m_data_buffer->isAllocated();
    break;
  case STRING:
  case SCALAR:
    rv = true;
    break;
  default:
    SLIC_ASSERT_MSG(false, "Unexpected value for m_state");
  }

  return rv;
}

/*
 *************************************************************************
 *
 * Return number of dimensions and fill in shape information.
 *
 *************************************************************************
 */
int DataView::getShape(int ndims, SidreLength * shape) const
{
  if (static_cast<unsigned>(ndims) < m_shape.size())
  {
    return -1;
  }

#if 0
  for(std::vector<SidreLength>::iterator it = v.begin() ;
      it != v.end() ;
      ++it)
  {
    *shape++ = it.
  }
#else
  for(std::vector<SidreLength>::size_type i = 0 ;
      i != m_shape.size() ;
      ++i)
  {
    shape[i] = m_shape[i];
  }
#endif
  return m_shape.size();
}

/*
 *************************************************************************
 *
 * Print JSON description of data view to stdout.
 *
 *************************************************************************
 */
void DataView::print() const
{
  print(std::cout);
}

/*
 *************************************************************************
 *
 * Print JSON description of data view to an  ostream.
 *
 *************************************************************************
 */
void DataView::print(std::ostream& os) const
{
  Node n;
  info(n);
  n.to_json_stream(os);
}

/*
 *************************************************************************
 *
 * Copy data view description to given Conduit node.
 *
 *************************************************************************
 */
void DataView::info(Node &n) const
{
  n["name"] = m_name;
  n["schema"] = m_schema.to_json();
  n["node"] = m_node.to_json();
  n["state"] = getStateStringName(m_state);
  n["is_applied"] = m_is_applied;
}

/*
 *************************************************************************
 *
 * PRIVATE ctor for DataView not associated with any data.
 *
 *************************************************************************
 */
DataView::DataView( const std::string& name,
                    DataGroup * const owning_group)
  :   m_name(name),
  m_owning_group(owning_group),
  m_data_buffer(ATK_NULLPTR),
  m_schema(),
  m_node(),
  m_shape(),
  m_external_ptr(ATK_NULLPTR),
  m_state(EMPTY),
  m_is_applied(false)
{}

/*
 *************************************************************************
 *
 * PRIVATE dtor.
 *
 *************************************************************************
 */
DataView::~DataView()
{
  if (m_data_buffer != ATK_NULLPTR)
  {
    m_data_buffer->detachView(this);
  }
}

/*
 *************************************************************************
 *
 * PRIVATE method to describe data view with type and number of elements.
 *
 *************************************************************************
 */
void DataView::describe(TypeID type, SidreLength num_elems)
{
  if ( num_elems < 0 )
  {
    SLIC_CHECK_MSG(num_elems >= 0,
                   "Describe: must give number of elements >= 0");
    return;
  }

  DataType dtype = conduit::DataType::default_dtype(type);
  dtype.set_number_of_elements(num_elems);
  m_schema.set(dtype);
  describeShape();
  m_is_applied = false;
}

/*
 *************************************************************************
 *
 * PRIVATE method to describe data view with type, number of dimensions,
 *         and number of elements per dimension.
 *
 *************************************************************************
 */
void DataView::describe(TypeID type, int ndims, SidreLength * shape)
{
  if ( ndims < 0 || shape == ATK_NULLPTR)
  {
    SLIC_CHECK(ndims >= 0);
    SLIC_CHECK(shape != ATK_NULLPTR);
    return;
  }

  SidreLength num_elems = 0;
  if (ndims > 0)
  {
    num_elems = shape[0];
    for (int i=1 ; i < ndims ; i++)
    {
      num_elems *= shape[i];
    }
  }

  describe(type, num_elems);
  describeShape(ndims, shape);
}

/*
 *************************************************************************
 *
 * PRIVATE method to describe data view with a Conduit data type object.
 *
 *************************************************************************
 */
void DataView::describe(const DataType& dtype)
{
  if ( dtype.is_empty() )
  {
    SLIC_CHECK_MSG(
      !dtype.is_empty(),
      "Unable to set description in View, datatype parameter is empty.");
    return;
  }

  m_schema.set(dtype);
  describeShape();
  m_is_applied = false;
}

/*
 *************************************************************************
 *
 * PRIVATE method set shape to described length.
 * This is called after describe to set the shape.
 *
 *************************************************************************
 */
void DataView::describeShape()
{
  m_shape.clear();
  m_shape.push_back(m_schema.dtype().number_of_elements());
}

/*
 *************************************************************************
 *
 * PRIVATE method set shape from user input.
 *
 *************************************************************************
 */
void DataView::describeShape(int ndims, SidreLength * shape)
{
  m_shape.clear();
  for (int i=0 ; i < ndims ; i++)
  {
    m_shape.push_back(shape[i]);
  }
}

/*
 *************************************************************************
 *
 * PRIVATE method returns true if view can allocate data; else false.
 *
 * This method does not need to emit the view state as part of it's
 * checking.  The caller functions are already printing out the view
 * state if this function returns false.
 *************************************************************************
 */
bool DataView::isAllocateValid() const
{
  bool rv = false;

  switch (m_state)
  {
  case EMPTY:
      // allocate is valid assuming the caller attaches a buffer.
      rv = true;
      break;
  case STRING:
  case SCALAR:
  case EXTERNAL:
    SLIC_CHECK_MSG( false,
                    "Allocate is not valid for " <<
                    getStateStringName(m_state) << "view");
    break;
  case BUFFER:
    // Check that buffer is only referenced by this view.
    if (m_data_buffer->getNumViews() != 1 )
    {
      SLIC_CHECK_MSG(
        m_data_buffer->getNumViews() != 1,
        "Allocate is not valid, buffer does not contain exactly one view.");
    }
    else
    {
      rv = true;
    }
    break;
  default:
    SLIC_ASSERT_MSG(false, "Unexpected value for m_state");
  }

  return rv;
}

/*
 *************************************************************************
 *
 * PRIVATE method returns true if attaching buffer to view is valid;
 * else false.
 *
 * This method does not need to emit the view state as part of it's
 * checking.  The caller functions are already printing out the view
 * state if this function returns false.
 *
 *************************************************************************
 */
bool DataView::isAttachBufferValid() const
{
  return ( m_state == EMPTY || m_state == BUFFER );
}

/*
 *************************************************************************
 *
 * PRIVATE method returns true if setting external data pointer on view
 * is valid; else false.
 *
 * This method does not need to emit the view state as part of it's
 * checking.  The caller functions are already printing out the view
 * state if this function returns false.
 *
 *************************************************************************
 */
bool DataView::isSetExternalDataPtrValid() const
{
  return ( m_state == EMPTY || m_state == EXTERNAL );
}

/*
 *************************************************************************
 *
 * PRIVATE method returns true if apply is a valid operation on view;
 * else false.
 *
 * For an EXTERNAL view, assume user provided m_external_ptr and
 * description are consistent. This includes m_external_ptr == NULL.
 *
 *************************************************************************
 */
bool DataView::isApplyValid() const
{
  bool rv = false;

  if ( !isDescribed() )
  {
    SLIC_CHECK_MSG(false,
                   "Apply is not valid, no description in view to apply");
  }

  switch (m_state)
  {
  case EMPTY:
  case STRING:
  case SCALAR:
    SLIC_CHECK_MSG( false,
                    "Apply is not valid for " <<
                    getStateStringName(m_state) << "view");
    break;
  case EXTERNAL:
    if (m_external_ptr == ATK_NULLPTR && getNumElements() > 0)
    {
      SLIC_CHECK_MSG(false, "Should not apply a non-zero length to a NULL address");
    }
    else
    {
      rv = true;
    }
    break;
  case BUFFER:
    if ( !m_data_buffer->isAllocated() )
    {
      SLIC_CHECK_MSG(false, "Apply is not valid, buffer is not allocated");
    }
    else if ( getTotalBytes() > m_data_buffer->getTotalBytes() )
    {
      SLIC_CHECK_MSG(false,
                     "Apply is not valid, buffer description is smaller than view description");
    }
    else
    {
      rv = true;
    }
    break;
  default:
    SLIC_ASSERT_MSG(false, "Unexpected value for m_state");
  }

  return rv;
}

/*
 *************************************************************************
 *
 * PRIVATE method returns string name of given view state enum value.
 *
 *************************************************************************
 */
char const * DataView::getStateStringName(State state) const
{
  char const * ret_string = NULL;

  switch ( state )
  {
  case EMPTY:
    ret_string = "EMPTY";
    break;
  case BUFFER:
    ret_string = "BUFFER";
    break;
  case EXTERNAL:
    ret_string = "EXTERNAL";
    break;
  case SCALAR:
    ret_string = "SCALAR";
    break;
  case STRING:
    ret_string = "STRING";
    break;
  default:
    ret_string = "UNKNOWN";
  }

  return ret_string;
}


} /* end namespace sidre */
} /* end namespace asctoolkit */
