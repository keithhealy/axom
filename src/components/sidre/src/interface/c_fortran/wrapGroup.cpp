// wrapGroup.cpp
// This is generated code, do not edit
//
// Copyright (c) 2015, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory.
//
// All rights reserved.
//
// This source code cannot be distributed without permission and
// further review from Lawrence Livermore National Laboratory.
//
// wrapGroup.cpp
#include "wrapGroup.h"
#include <string>
#include "shroudrt.hpp"
#include "sidre/Group.hpp"
#include "sidre/SidreTypes.hpp"

extern "C" {
namespace axom
{
namespace sidre
{

const char * SIDRE_group_get_name(const SIDRE_group * self)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_name
  const std::string & SH_rv = SH_this->getName();
  return SH_rv.c_str();
// splicer end class.Group.method.get_name
}

void SIDRE_group_get_name_bufferify(const SIDRE_group * self, char * SH_F_rv,
                                    int LSH_F_rv)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_name_bufferify
  const std::string & SH_rv = SH_this->getName();
  shroud_FccCopy(SH_F_rv, LSH_F_rv, SH_rv.c_str());
  return;
// splicer end class.Group.method.get_name_bufferify
}

const SIDRE_group * SIDRE_group_get_parent(const SIDRE_group * self)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_parent
  const Group * SH_rv = SH_this->getParent();
  return static_cast<const SIDRE_group *>(static_cast<const void *>(SH_rv));
// splicer end class.Group.method.get_parent
}

const SIDRE_datastore * SIDRE_group_get_data_store(const SIDRE_group * self)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_data_store
  const DataStore * SH_rv = SH_this->getDataStore();
  return static_cast<const SIDRE_datastore *>(static_cast<const void *>(SH_rv));
// splicer end class.Group.method.get_data_store
}

size_t SIDRE_group_get_num_views(const SIDRE_group * self)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_num_views
  size_t SH_rv = SH_this->getNumViews();
  return SH_rv;
// splicer end class.Group.method.get_num_views
}

size_t SIDRE_group_get_num_groups(const SIDRE_group * self)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_num_groups
  size_t SH_rv = SH_this->getNumGroups();
  return SH_rv;
// splicer end class.Group.method.get_num_groups
}

bool SIDRE_group_has_view(const SIDRE_group * self, const char * path)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.has_view
  const std::string SH_path(path);
  bool SH_rv = SH_this->hasView(SH_path);
  return SH_rv;
// splicer end class.Group.method.has_view
}

bool SIDRE_group_has_view_bufferify(const SIDRE_group * self, const char * path,
                                    int Lpath)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.has_view_bufferify
  const std::string SH_path(path, Lpath);
  bool SH_rv = SH_this->hasView(SH_path);
  return SH_rv;
// splicer end class.Group.method.has_view_bufferify
}

bool SIDRE_group_has_child_view(const SIDRE_group * self, const char * name)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.has_child_view
  const std::string SH_name(name);
  bool SH_rv = SH_this->hasChildView(SH_name);
  return SH_rv;
// splicer end class.Group.method.has_child_view
}

bool SIDRE_group_has_child_view_bufferify(const SIDRE_group * self,
                                          const char * name, int Lname)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.has_child_view_bufferify
  const std::string SH_name(name, Lname);
  bool SH_rv = SH_this->hasChildView(SH_name);
  return SH_rv;
// splicer end class.Group.method.has_child_view_bufferify
}

bool SIDRE_group_rename(SIDRE_group * self, const char * new_name)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.rename
  const std::string SH_new_name(new_name);
  bool SH_rv = SH_this->rename(SH_new_name);
  return SH_rv;
// splicer end class.Group.method.rename
}

bool SIDRE_group_rename_bufferify(SIDRE_group * self, const char * new_name,
                                  int Lnew_name)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.rename_bufferify
  const std::string SH_new_name(new_name, Lnew_name);
  bool SH_rv = SH_this->rename(SH_new_name);
  return SH_rv;
// splicer end class.Group.method.rename_bufferify
}

SIDRE_view * SIDRE_group_get_view_from_name(SIDRE_group * self,
                                            const char * path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.get_view_from_name
  const std::string SH_path(path);
  View * SH_rv = SH_this->getView(SH_path);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.get_view_from_name
}

SIDRE_view * SIDRE_group_get_view_from_name_bufferify(SIDRE_group * self,
                                                      const char * path,
                                                      int Lpath)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.get_view_from_name_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->getView(SH_path);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.get_view_from_name_bufferify
}

SIDRE_view * SIDRE_group_get_view_from_index(SIDRE_group * self,
                                             const SIDRE_IndexType idx)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.get_view_from_index
  View * SH_rv = SH_this->getView(idx);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.get_view_from_index
}

SIDRE_IndexType SIDRE_group_get_view_index(const SIDRE_group * self,
                                           const char * name)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_view_index
  const std::string SH_name(name);
  IndexType SH_rv = SH_this->getViewIndex(SH_name);
  return SH_rv;
// splicer end class.Group.method.get_view_index
}

SIDRE_IndexType SIDRE_group_get_view_index_bufferify(const SIDRE_group * self,
                                                     const char * name,
                                                     int Lname)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_view_index_bufferify
  const std::string SH_name(name, Lname);
  IndexType SH_rv = SH_this->getViewIndex(SH_name);
  return SH_rv;
// splicer end class.Group.method.get_view_index_bufferify
}

const char * SIDRE_group_get_view_name(const SIDRE_group * self,
                                       SIDRE_IndexType idx)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_view_name
  const std::string & SH_rv = SH_this->getViewName(idx);
  // check for error
  if (!nameIsValid(SH_rv))
  {
    return SIDRE_InvalidName;
  }

  return SH_rv.c_str();
// splicer end class.Group.method.get_view_name
}

void SIDRE_group_get_view_name_bufferify(const SIDRE_group * self,
                                         SIDRE_IndexType idx, char * SH_F_rv,
                                         int LSH_F_rv)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_view_name_bufferify
  const std::string & SH_rv = SH_this->getViewName(idx);
  // check for error
  if (!nameIsValid(SH_rv))
  {
    std::memset(SH_F_rv, ' ', LSH_F_rv);
    return;
  }

  shroud_FccCopy(SH_F_rv, LSH_F_rv, SH_rv.c_str());
  return;
// splicer end class.Group.method.get_view_name_bufferify
}

SIDRE_IndexType SIDRE_group_get_first_valid_view_index(const SIDRE_group * self)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_first_valid_view_index
  IndexType SH_rv = SH_this->getFirstValidViewIndex();
  return SH_rv;
// splicer end class.Group.method.get_first_valid_view_index
}

SIDRE_IndexType SIDRE_group_get_next_valid_view_index(const SIDRE_group * self,
                                                      SIDRE_IndexType idx)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_next_valid_view_index
  IndexType SH_rv = SH_this->getNextValidViewIndex(idx);
  return SH_rv;
// splicer end class.Group.method.get_next_valid_view_index
}

SIDRE_view * SIDRE_group_create_view_and_allocate_nelems(SIDRE_group * self,
                                                         const char * path,
                                                         int type,
                                                         SIDRE_SidreLength num_elems)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_and_allocate_nelems
  const std::string SH_path(path);
  View * SH_rv = SH_this->createViewAndAllocate(SH_path, getTypeID(
                                                  type), num_elems);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_and_allocate_nelems
}

SIDRE_view * SIDRE_group_create_view_and_allocate_nelems_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type,
  SIDRE_SidreLength num_elems)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_and_allocate_nelems_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createViewAndAllocate(SH_path, getTypeID(
                                                  type), num_elems);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_and_allocate_nelems_bufferify
}

SIDRE_view * SIDRE_group_create_view_and_allocate_shape(SIDRE_group * self,
                                                        const char * path,
                                                        int type, int ndims,
                                                        SIDRE_SidreLength * shape)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_and_allocate_shape
  const std::string SH_path(path);
  View * SH_rv = SH_this->createViewAndAllocate(SH_path, getTypeID(
                                                  type), ndims, shape);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_and_allocate_shape
}

SIDRE_view * SIDRE_group_create_view_and_allocate_shape_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type, int ndims,
  SIDRE_SidreLength * shape)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_and_allocate_shape_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createViewAndAllocate(SH_path, getTypeID(
                                                  type), ndims, shape);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_and_allocate_shape_bufferify
}

SIDRE_view * SIDRE_group_create_view_scalar_int(SIDRE_group * self,
                                                const char * path, int value)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_scalar_int
  const std::string SH_path(path);
  View * SH_rv = SH_this->createViewScalar<int>(SH_path, value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_scalar_int
}

SIDRE_view * SIDRE_group_create_view_scalar_int_bufferify(SIDRE_group * self,
                                                          const char * path,
                                                          int Lpath, int value)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_scalar_int_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createViewScalar<int>(SH_path, value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_scalar_int_bufferify
}

SIDRE_view * SIDRE_group_create_view_scalar_long(SIDRE_group * self,
                                                 const char * path, long value)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_scalar_long
  const std::string SH_path(path);
  View * SH_rv = SH_this->createViewScalar<long>(SH_path, value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_scalar_long
}

SIDRE_view * SIDRE_group_create_view_scalar_long_bufferify(SIDRE_group * self,
                                                           const char * path,
                                                           int Lpath,
                                                           long value)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_scalar_long_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createViewScalar<long>(SH_path, value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_scalar_long_bufferify
}

SIDRE_view * SIDRE_group_create_view_scalar_float(SIDRE_group * self,
                                                  const char * path,
                                                  float value)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_scalar_float
  const std::string SH_path(path);
  View * SH_rv = SH_this->createViewScalar<float>(SH_path, value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_scalar_float
}

SIDRE_view * SIDRE_group_create_view_scalar_float_bufferify(SIDRE_group * self,
                                                            const char * path,
                                                            int Lpath,
                                                            float value)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_scalar_float_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createViewScalar<float>(SH_path, value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_scalar_float_bufferify
}

SIDRE_view * SIDRE_group_create_view_scalar_double(SIDRE_group * self,
                                                   const char * path,
                                                   double value)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_scalar_double
  const std::string SH_path(path);
  View * SH_rv = SH_this->createViewScalar<double>(SH_path, value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_scalar_double
}

SIDRE_view * SIDRE_group_create_view_scalar_double_bufferify(SIDRE_group * self,
                                                             const char * path,
                                                             int Lpath,
                                                             double value)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_scalar_double_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createViewScalar<double>(SH_path, value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_scalar_double_bufferify
}

SIDRE_view * SIDRE_group_create_view_string(SIDRE_group * self,
                                            const char * path,
                                            const char * value)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_string
  const std::string SH_path(path);
  const std::string SH_value(value);
  View * SH_rv = SH_this->createViewString(SH_path, SH_value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_string
}

SIDRE_view * SIDRE_group_create_view_string_bufferify(SIDRE_group * self,
                                                      const char * path,
                                                      int Lpath,
                                                      const char * value,
                                                      int Lvalue)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_string_bufferify
  const std::string SH_path(path, Lpath);
  const std::string SH_value(value, Lvalue);
  View * SH_rv = SH_this->createViewString(SH_path, SH_value);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_string_bufferify
}

SIDRE_view * SIDRE_group_create_view_empty(SIDRE_group * self,
                                           const char * path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_empty
  const std::string SH_path(path);
  View * SH_rv = SH_this->createView(SH_path);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_empty
}

SIDRE_view * SIDRE_group_create_view_empty_bufferify(SIDRE_group * self,
                                                     const char * path,
                                                     int Lpath)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_empty_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createView(SH_path);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_empty_bufferify
}

SIDRE_view * SIDRE_group_create_view_from_type(SIDRE_group * self,
                                               const char * path, int type,
                                               SIDRE_SidreLength num_elems)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_type
  const std::string SH_path(path);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(type), num_elems);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_type
}

SIDRE_view * SIDRE_group_create_view_from_type_bufferify(SIDRE_group * self,
                                                         const char * path,
                                                         int Lpath, int type,
                                                         SIDRE_SidreLength num_elems)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_type_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(type), num_elems);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_type_bufferify
}

SIDRE_view * SIDRE_group_create_view_from_type_and_buffer(SIDRE_group * self,
                                                          const char * path,
                                                          int type,
                                                          SIDRE_SidreLength num_elems,
                                                          SIDRE_buffer * buff)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_type_and_buffer
  const std::string SH_path(path);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(
                                       type), num_elems,
                                     static_cast<Buffer *>(static_cast<void *>(
                                                             buff)));
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_type_and_buffer
}

SIDRE_view * SIDRE_group_create_view_from_type_and_buffer_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type,
  SIDRE_SidreLength num_elems, SIDRE_buffer * buff)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_type_and_buffer_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(
                                       type), num_elems,
                                     static_cast<Buffer *>(static_cast<void *>(
                                                             buff)));
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_type_and_buffer_bufferify
}

SIDRE_view * SIDRE_group_create_view_from_type_external(SIDRE_group * self,
                                                        const char * path,
                                                        int type,
                                                        SIDRE_SidreLength num_elems,
                                                        void * external_ptr)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_type_external
  const std::string SH_path(path);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(
                                       type), num_elems, external_ptr);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_type_external
}

SIDRE_view * SIDRE_group_create_view_from_type_external_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type,
  SIDRE_SidreLength num_elems, void * external_ptr)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_type_external_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(
                                       type), num_elems, external_ptr);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_type_external_bufferify
}

SIDRE_view * SIDRE_group_create_view_from_shape(SIDRE_group * self,
                                                const char * path, int type,
                                                int ndims,
                                                SIDRE_SidreLength * shape)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_shape
  const std::string SH_path(path);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(type), ndims, shape);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_shape
}

SIDRE_view * SIDRE_group_create_view_from_shape_bufferify(SIDRE_group * self,
                                                          const char * path,
                                                          int Lpath, int type,
                                                          int ndims,
                                                          SIDRE_SidreLength * shape)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_shape_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(type), ndims, shape);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_shape_bufferify
}

SIDRE_view * SIDRE_group_create_view_from_shape_and_buffer(SIDRE_group * self,
                                                           const char * path,
                                                           int type, int ndims,
                                                           SIDRE_SidreLength * shape,
                                                           SIDRE_buffer * buff)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_shape_and_buffer
  const std::string SH_path(path);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(
                                       type), ndims, shape,
                                     static_cast<Buffer *>(static_cast<void *>(
                                                             buff)));
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_shape_and_buffer
}

SIDRE_view * SIDRE_group_create_view_from_shape_and_buffer_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type, int ndims,
  SIDRE_SidreLength * shape, SIDRE_buffer * buff)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_shape_and_buffer_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(
                                       type), ndims, shape,
                                     static_cast<Buffer *>(static_cast<void *>(
                                                             buff)));
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_shape_and_buffer_bufferify
}

SIDRE_view * SIDRE_group_create_view_from_shape_external(SIDRE_group * self,
                                                         const char * path,
                                                         int type, int ndims,
                                                         SIDRE_SidreLength * shape,
                                                         void * external_ptr)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_shape_external
  const std::string SH_path(path);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(
                                       type), ndims, shape, external_ptr);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_shape_external
}

SIDRE_view * SIDRE_group_create_view_from_shape_external_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type, int ndims,
  SIDRE_SidreLength * shape, void * external_ptr)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_from_shape_external_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createView(SH_path, getTypeID(
                                       type), ndims, shape, external_ptr);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_from_shape_external_bufferify
}

SIDRE_view * SIDRE_group_create_view_into_buffer(SIDRE_group * self,
                                                 const char * path,
                                                 SIDRE_buffer * buff)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_into_buffer
  const std::string SH_path(path);
  View * SH_rv =
    SH_this->createView(SH_path,
                        static_cast<Buffer *>(static_cast<void *>(buff)));
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_into_buffer
}

SIDRE_view * SIDRE_group_create_view_into_buffer_bufferify(SIDRE_group * self,
                                                           const char * path,
                                                           int Lpath,
                                                           SIDRE_buffer * buff)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_into_buffer_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv =
    SH_this->createView(SH_path,
                        static_cast<Buffer *>(static_cast<void *>(buff)));
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_into_buffer_bufferify
}

SIDRE_view * SIDRE_group_create_view_external(SIDRE_group * self,
                                              const char * path,
                                              void * external_ptr)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_external
  const std::string SH_path(path);
  View * SH_rv = SH_this->createView(SH_path, external_ptr);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_external
}

SIDRE_view * SIDRE_group_create_view_external_bufferify(SIDRE_group * self,
                                                        const char * path,
                                                        int Lpath,
                                                        void * external_ptr)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_view_external_bufferify
  const std::string SH_path(path, Lpath);
  View * SH_rv = SH_this->createView(SH_path, external_ptr);
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_view_external_bufferify
}

void SIDRE_group_destroy_view(SIDRE_group * self, const char * path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.destroy_view
  const std::string SH_path(path);
  SH_this->destroyView(SH_path);
  return;
// splicer end class.Group.method.destroy_view
}

void SIDRE_group_destroy_view_bufferify(SIDRE_group * self, const char * path,
                                        int Lpath)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.destroy_view_bufferify
  const std::string SH_path(path, Lpath);
  SH_this->destroyView(SH_path);
  return;
// splicer end class.Group.method.destroy_view_bufferify
}

void SIDRE_group_destroy_view_and_data_name(SIDRE_group * self,
                                            const char * path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.destroy_view_and_data_name
  const std::string SH_path(path);
  SH_this->destroyViewAndData(SH_path);
  return;
// splicer end class.Group.method.destroy_view_and_data_name
}

void SIDRE_group_destroy_view_and_data_name_bufferify(SIDRE_group * self,
                                                      const char * path,
                                                      int Lpath)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.destroy_view_and_data_name_bufferify
  const std::string SH_path(path, Lpath);
  SH_this->destroyViewAndData(SH_path);
  return;
// splicer end class.Group.method.destroy_view_and_data_name_bufferify
}

void SIDRE_group_destroy_view_and_data_index(SIDRE_group * self,
                                             SIDRE_IndexType idx)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.destroy_view_and_data_index
  SH_this->destroyViewAndData(idx);
  return;
// splicer end class.Group.method.destroy_view_and_data_index
}

SIDRE_view * SIDRE_group_move_view(SIDRE_group * self, SIDRE_view * view)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.move_view
  View * SH_rv = SH_this->moveView(
    static_cast<View *>(static_cast<void *>(view)));
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.move_view
}

SIDRE_view * SIDRE_group_copy_view(SIDRE_group * self, SIDRE_view * view)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.copy_view
  View * SH_rv = SH_this->copyView(
    static_cast<View *>(static_cast<void *>(view)));
  return static_cast<SIDRE_view *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.copy_view
}

bool SIDRE_group_has_group(SIDRE_group * self, const char * path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.has_group
  const std::string SH_path(path);
  bool SH_rv = SH_this->hasGroup(SH_path);
  return SH_rv;
// splicer end class.Group.method.has_group
}

bool SIDRE_group_has_group_bufferify(SIDRE_group * self, const char * path,
                                     int Lpath)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.has_group_bufferify
  const std::string SH_path(path, Lpath);
  bool SH_rv = SH_this->hasGroup(SH_path);
  return SH_rv;
// splicer end class.Group.method.has_group_bufferify
}

bool SIDRE_group_has_child_group(SIDRE_group * self, const char * name)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.has_child_group
  const std::string SH_name(name);
  bool SH_rv = SH_this->hasChildGroup(SH_name);
  return SH_rv;
// splicer end class.Group.method.has_child_group
}

bool SIDRE_group_has_child_group_bufferify(SIDRE_group * self,
                                           const char * name, int Lname)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.has_child_group_bufferify
  const std::string SH_name(name, Lname);
  bool SH_rv = SH_this->hasChildGroup(SH_name);
  return SH_rv;
// splicer end class.Group.method.has_child_group_bufferify
}

SIDRE_group * SIDRE_group_get_group(SIDRE_group * self, const char * path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.get_group
  const std::string SH_path(path);
  Group * SH_rv = SH_this->getGroup(SH_path);
  return static_cast<SIDRE_group *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.get_group
}

SIDRE_group * SIDRE_group_get_group_bufferify(SIDRE_group * self,
                                              const char * path, int Lpath)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.get_group_bufferify
  const std::string SH_path(path, Lpath);
  Group * SH_rv = SH_this->getGroup(SH_path);
  return static_cast<SIDRE_group *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.get_group_bufferify
}

SIDRE_IndexType SIDRE_group_get_group_index(const SIDRE_group * self,
                                            const char * name)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_group_index
  const std::string SH_name(name);
  IndexType SH_rv = SH_this->getGroupIndex(SH_name);
  return SH_rv;
// splicer end class.Group.method.get_group_index
}

SIDRE_IndexType SIDRE_group_get_group_index_bufferify(const SIDRE_group * self,
                                                      const char * name,
                                                      int Lname)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_group_index_bufferify
  const std::string SH_name(name, Lname);
  IndexType SH_rv = SH_this->getGroupIndex(SH_name);
  return SH_rv;
// splicer end class.Group.method.get_group_index_bufferify
}

const char * SIDRE_group_get_group_name(const SIDRE_group * self,
                                        SIDRE_IndexType idx)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_group_name
  const std::string & SH_rv = SH_this->getGroupName(idx);
  // check for error
  if (!nameIsValid(SH_rv))
  {
    return SIDRE_InvalidName;
  }

  return SH_rv.c_str();
// splicer end class.Group.method.get_group_name
}

void SIDRE_group_get_group_name_bufferify(const SIDRE_group * self,
                                          SIDRE_IndexType idx, char * SH_F_rv,
                                          int LSH_F_rv)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_group_name_bufferify
  const std::string & SH_rv = SH_this->getGroupName(idx);
  // check for error
  if (!nameIsValid(SH_rv))
  {
    std::memset(SH_F_rv, ' ', LSH_F_rv);
    return;
  }

  shroud_FccCopy(SH_F_rv, LSH_F_rv, SH_rv.c_str());
  return;
// splicer end class.Group.method.get_group_name_bufferify
}

SIDRE_IndexType SIDRE_group_get_first_valid_group_index(const SIDRE_group * self)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_first_valid_group_index
  IndexType SH_rv = SH_this->getFirstValidGroupIndex();
  return SH_rv;
// splicer end class.Group.method.get_first_valid_group_index
}

SIDRE_IndexType SIDRE_group_get_next_valid_group_index(const SIDRE_group * self,
                                                       SIDRE_IndexType idx)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.get_next_valid_group_index
  IndexType SH_rv = SH_this->getNextValidGroupIndex(idx);
  return SH_rv;
// splicer end class.Group.method.get_next_valid_group_index
}

SIDRE_group * SIDRE_group_create_group(SIDRE_group * self, const char * path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_group
  const std::string SH_path(path);
  Group * SH_rv = SH_this->createGroup(SH_path);
  return static_cast<SIDRE_group *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_group
}

SIDRE_group * SIDRE_group_create_group_bufferify(SIDRE_group * self,
                                                 const char * path, int Lpath)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.create_group_bufferify
  const std::string SH_path(path, Lpath);
  Group * SH_rv = SH_this->createGroup(SH_path);
  return static_cast<SIDRE_group *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.create_group_bufferify
}

void SIDRE_group_destroy_group_name(SIDRE_group * self, const char * path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.destroy_group_name
  const std::string SH_path(path);
  SH_this->destroyGroup(SH_path);
  return;
// splicer end class.Group.method.destroy_group_name
}

void SIDRE_group_destroy_group_name_bufferify(SIDRE_group * self,
                                              const char * path, int Lpath)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.destroy_group_name_bufferify
  const std::string SH_path(path, Lpath);
  SH_this->destroyGroup(SH_path);
  return;
// splicer end class.Group.method.destroy_group_name_bufferify
}

void SIDRE_group_destroy_group_index(SIDRE_group * self, SIDRE_IndexType idx)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.destroy_group_index
  SH_this->destroyGroup(idx);
  return;
// splicer end class.Group.method.destroy_group_index
}

SIDRE_group * SIDRE_group_move_group(SIDRE_group * self, SIDRE_group * grp)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.move_group
  Group * SH_rv =
    SH_this->moveGroup(static_cast<Group *>(static_cast<void *>(grp)));
  return static_cast<SIDRE_group *>(static_cast<void *>(SH_rv));
// splicer end class.Group.method.move_group
}

void SIDRE_group_print(const SIDRE_group * self)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.print
  SH_this->print();
  return;
// splicer end class.Group.method.print
}

bool SIDRE_group_is_equivalent_to(const SIDRE_group * self,
                                  const SIDRE_group * other)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.is_equivalent_to
  bool SH_rv =
    SH_this->isEquivalentTo(static_cast<const Group *>(static_cast<const
                                                                   void *>(other)));
  return SH_rv;
// splicer end class.Group.method.is_equivalent_to
}

void SIDRE_group_save(const SIDRE_group * self, const char * file_path,
                      const char * protocol)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.save
  const std::string SH_file_path(file_path);
  const std::string SH_protocol(protocol);
  SH_this->save(SH_file_path, SH_protocol);
  return;
// splicer end class.Group.method.save
}

void SIDRE_group_save_bufferify(const SIDRE_group * self,
                                const char * file_path, int Lfile_path,
                                const char * protocol, int Lprotocol)
{
  const Group * SH_this =
    static_cast<const Group *>(static_cast<const void *>(self));
// splicer begin class.Group.method.save_bufferify
  const std::string SH_file_path(file_path, Lfile_path);
  const std::string SH_protocol(protocol, Lprotocol);
  SH_this->save(SH_file_path, SH_protocol);
  return;
// splicer end class.Group.method.save_bufferify
}

void SIDRE_group_load(SIDRE_group * self, const char * file_path,
                      const char * protocol)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.load
  const std::string SH_file_path(file_path);
  const std::string SH_protocol(protocol);
  SH_this->load(SH_file_path, SH_protocol);
  return;
// splicer end class.Group.method.load
}

void SIDRE_group_load_bufferify(SIDRE_group * self, const char * file_path,
                                int Lfile_path, const char * protocol,
                                int Lprotocol)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.load_bufferify
  const std::string SH_file_path(file_path, Lfile_path);
  const std::string SH_protocol(protocol, Lprotocol);
  SH_this->load(SH_file_path, SH_protocol);
  return;
// splicer end class.Group.method.load_bufferify
}

void SIDRE_group_load_external_data(SIDRE_group * self, const char * file_path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.load_external_data
  const std::string SH_file_path(file_path);
  SH_this->loadExternalData(SH_file_path);
  return;
// splicer end class.Group.method.load_external_data
}

void SIDRE_group_load_external_data_bufferify(SIDRE_group * self,
                                              const char * file_path,
                                              int Lfile_path)
{
  Group * SH_this = static_cast<Group *>(static_cast<void *>(self));
// splicer begin class.Group.method.load_external_data_bufferify
  const std::string SH_file_path(file_path, Lfile_path);
  SH_this->loadExternalData(SH_file_path);
  return;
// splicer end class.Group.method.load_external_data_bufferify
}

// splicer begin class.Group.additional_functions
// splicer end class.Group.additional_functions

}  // namespace axom
}  // namespace sidre
}  // extern "C"