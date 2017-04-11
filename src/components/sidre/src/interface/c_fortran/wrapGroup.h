// wrapGroup.h
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
/**
 * \file wrapGroup.h
 * \brief Shroud generated wrapper for Group class
 */
// For C users and C++ implementation

#ifndef WRAPGROUP_H
#define WRAPGROUP_H

#include "sidre/SidreTypes.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

// declaration of wrapped types
struct s_SIDRE_buffer;
typedef struct s_SIDRE_buffer SIDRE_buffer;
struct s_SIDRE_datastore;
typedef struct s_SIDRE_datastore SIDRE_datastore;
struct s_SIDRE_group;
typedef struct s_SIDRE_group SIDRE_group;
struct s_SIDRE_view;
typedef struct s_SIDRE_view SIDRE_view;

// splicer begin class.Group.C_definition
// splicer end class.Group.C_definition

const char * SIDRE_group_get_name(const SIDRE_group * self);

void SIDRE_group_get_name_bufferify(const SIDRE_group * self, char * SH_F_rv,
                                    int LSH_F_rv);

const SIDRE_group * SIDRE_group_get_parent(const SIDRE_group * self);

const SIDRE_datastore * SIDRE_group_get_data_store(const SIDRE_group * self);

size_t SIDRE_group_get_num_views(const SIDRE_group * self);

size_t SIDRE_group_get_num_groups(const SIDRE_group * self);

bool SIDRE_group_has_view(const SIDRE_group * self, const char * path);

bool SIDRE_group_has_view_bufferify(const SIDRE_group * self, const char * path,
                                    int Lpath);

bool SIDRE_group_has_child_view(const SIDRE_group * self, const char * name);

bool SIDRE_group_has_child_view_bufferify(const SIDRE_group * self,
                                          const char * name, int Lname);

bool SIDRE_group_rename(SIDRE_group * self, const char * new_name);

bool SIDRE_group_rename_bufferify(SIDRE_group * self, const char * new_name,
                                  int Lnew_name);

SIDRE_view * SIDRE_group_get_view_from_name(SIDRE_group * self,
                                            const char * path);

SIDRE_view * SIDRE_group_get_view_from_name_bufferify(SIDRE_group * self,
                                                      const char * path,
                                                      int Lpath);

SIDRE_view * SIDRE_group_get_view_from_index(SIDRE_group * self,
                                             const SIDRE_IndexType idx);

SIDRE_IndexType SIDRE_group_get_view_index(const SIDRE_group * self,
                                           const char * name);

SIDRE_IndexType SIDRE_group_get_view_index_bufferify(const SIDRE_group * self,
                                                     const char * name,
                                                     int Lname);

const char * SIDRE_group_get_view_name(const SIDRE_group * self,
                                       SIDRE_IndexType idx);

void SIDRE_group_get_view_name_bufferify(const SIDRE_group * self,
                                         SIDRE_IndexType idx, char * SH_F_rv,
                                         int LSH_F_rv);

SIDRE_IndexType SIDRE_group_get_first_valid_view_index(const SIDRE_group * self);

SIDRE_IndexType SIDRE_group_get_next_valid_view_index(const SIDRE_group * self,
                                                      SIDRE_IndexType idx);

SIDRE_view * SIDRE_group_create_view_and_allocate_nelems(SIDRE_group * self,
                                                         const char * path,
                                                         int type,
                                                         SIDRE_SidreLength num_elems);

SIDRE_view * SIDRE_group_create_view_and_allocate_nelems_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type,
  SIDRE_SidreLength num_elems);

SIDRE_view * SIDRE_group_create_view_and_allocate_shape(SIDRE_group * self,
                                                        const char * path,
                                                        int type, int ndims,
                                                        SIDRE_SidreLength * shape);

SIDRE_view * SIDRE_group_create_view_and_allocate_shape_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type, int ndims,
  SIDRE_SidreLength * shape);

SIDRE_view * SIDRE_group_create_view_scalar_int(SIDRE_group * self,
                                                const char * path, int value);

SIDRE_view * SIDRE_group_create_view_scalar_int_bufferify(SIDRE_group * self,
                                                          const char * path,
                                                          int Lpath, int value);

SIDRE_view * SIDRE_group_create_view_scalar_long(SIDRE_group * self,
                                                 const char * path, long value);

SIDRE_view * SIDRE_group_create_view_scalar_long_bufferify(SIDRE_group * self,
                                                           const char * path,
                                                           int Lpath,
                                                           long value);

SIDRE_view * SIDRE_group_create_view_scalar_float(SIDRE_group * self,
                                                  const char * path,
                                                  float value);

SIDRE_view * SIDRE_group_create_view_scalar_float_bufferify(SIDRE_group * self,
                                                            const char * path,
                                                            int Lpath,
                                                            float value);

SIDRE_view * SIDRE_group_create_view_scalar_double(SIDRE_group * self,
                                                   const char * path,
                                                   double value);

SIDRE_view * SIDRE_group_create_view_scalar_double_bufferify(SIDRE_group * self,
                                                             const char * path,
                                                             int Lpath,
                                                             double value);

SIDRE_view * SIDRE_group_create_view_string(SIDRE_group * self,
                                            const char * path,
                                            const char * value);

SIDRE_view * SIDRE_group_create_view_string_bufferify(SIDRE_group * self,
                                                      const char * path,
                                                      int Lpath,
                                                      const char * value,
                                                      int Lvalue);

SIDRE_view * SIDRE_group_create_view_empty(SIDRE_group * self,
                                           const char * path);

SIDRE_view * SIDRE_group_create_view_empty_bufferify(SIDRE_group * self,
                                                     const char * path,
                                                     int Lpath);

SIDRE_view * SIDRE_group_create_view_from_type(SIDRE_group * self,
                                               const char * path, int type,
                                               SIDRE_SidreLength num_elems);

SIDRE_view * SIDRE_group_create_view_from_type_bufferify(SIDRE_group * self,
                                                         const char * path,
                                                         int Lpath, int type,
                                                         SIDRE_SidreLength num_elems);

SIDRE_view * SIDRE_group_create_view_from_type_and_buffer(SIDRE_group * self,
                                                          const char * path,
                                                          int type,
                                                          SIDRE_SidreLength num_elems,
                                                          SIDRE_buffer * buff);

SIDRE_view * SIDRE_group_create_view_from_type_and_buffer_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type,
  SIDRE_SidreLength num_elems, SIDRE_buffer * buff);

SIDRE_view * SIDRE_group_create_view_from_type_external(SIDRE_group * self,
                                                        const char * path,
                                                        int type,
                                                        SIDRE_SidreLength num_elems,
                                                        void * external_ptr);

SIDRE_view * SIDRE_group_create_view_from_type_external_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type,
  SIDRE_SidreLength num_elems, void * external_ptr);

SIDRE_view * SIDRE_group_create_view_from_shape(SIDRE_group * self,
                                                const char * path, int type,
                                                int ndims,
                                                SIDRE_SidreLength * shape);

SIDRE_view * SIDRE_group_create_view_from_shape_bufferify(SIDRE_group * self,
                                                          const char * path,
                                                          int Lpath, int type,
                                                          int ndims,
                                                          SIDRE_SidreLength * shape);

SIDRE_view * SIDRE_group_create_view_from_shape_and_buffer(SIDRE_group * self,
                                                           const char * path,
                                                           int type, int ndims,
                                                           SIDRE_SidreLength * shape,
                                                           SIDRE_buffer * buff);

SIDRE_view * SIDRE_group_create_view_from_shape_and_buffer_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type, int ndims,
  SIDRE_SidreLength * shape, SIDRE_buffer * buff);

SIDRE_view * SIDRE_group_create_view_from_shape_external(SIDRE_group * self,
                                                         const char * path,
                                                         int type, int ndims,
                                                         SIDRE_SidreLength * shape,
                                                         void * external_ptr);

SIDRE_view * SIDRE_group_create_view_from_shape_external_bufferify(
  SIDRE_group * self, const char * path, int Lpath, int type, int ndims,
  SIDRE_SidreLength * shape, void * external_ptr);

SIDRE_view * SIDRE_group_create_view_into_buffer(SIDRE_group * self,
                                                 const char * path,
                                                 SIDRE_buffer * buff);

SIDRE_view * SIDRE_group_create_view_into_buffer_bufferify(SIDRE_group * self,
                                                           const char * path,
                                                           int Lpath,
                                                           SIDRE_buffer * buff);

SIDRE_view * SIDRE_group_create_view_external(SIDRE_group * self,
                                              const char * path,
                                              void * external_ptr);

SIDRE_view * SIDRE_group_create_view_external_bufferify(SIDRE_group * self,
                                                        const char * path,
                                                        int Lpath,
                                                        void * external_ptr);

void SIDRE_group_destroy_view(SIDRE_group * self, const char * path);

void SIDRE_group_destroy_view_bufferify(SIDRE_group * self, const char * path,
                                        int Lpath);

void SIDRE_group_destroy_view_and_data_name(SIDRE_group * self,
                                            const char * path);

void SIDRE_group_destroy_view_and_data_name_bufferify(SIDRE_group * self,
                                                      const char * path,
                                                      int Lpath);

void SIDRE_group_destroy_view_and_data_index(SIDRE_group * self,
                                             SIDRE_IndexType idx);

SIDRE_view * SIDRE_group_move_view(SIDRE_group * self, SIDRE_view * view);

SIDRE_view * SIDRE_group_copy_view(SIDRE_group * self, SIDRE_view * view);

bool SIDRE_group_has_group(SIDRE_group * self, const char * path);

bool SIDRE_group_has_group_bufferify(SIDRE_group * self, const char * path,
                                     int Lpath);

bool SIDRE_group_has_child_group(SIDRE_group * self, const char * name);

bool SIDRE_group_has_child_group_bufferify(SIDRE_group * self,
                                           const char * name, int Lname);

SIDRE_group * SIDRE_group_get_group(SIDRE_group * self, const char * path);

SIDRE_group * SIDRE_group_get_group_bufferify(SIDRE_group * self,
                                              const char * path, int Lpath);

SIDRE_IndexType SIDRE_group_get_group_index(const SIDRE_group * self,
                                            const char * name);

SIDRE_IndexType SIDRE_group_get_group_index_bufferify(const SIDRE_group * self,
                                                      const char * name,
                                                      int Lname);

const char * SIDRE_group_get_group_name(const SIDRE_group * self,
                                        SIDRE_IndexType idx);

void SIDRE_group_get_group_name_bufferify(const SIDRE_group * self,
                                          SIDRE_IndexType idx, char * SH_F_rv,
                                          int LSH_F_rv);

SIDRE_IndexType SIDRE_group_get_first_valid_group_index(const SIDRE_group * self);

SIDRE_IndexType SIDRE_group_get_next_valid_group_index(const SIDRE_group * self,
                                                       SIDRE_IndexType idx);

SIDRE_group * SIDRE_group_create_group(SIDRE_group * self, const char * path);

SIDRE_group * SIDRE_group_create_group_bufferify(SIDRE_group * self,
                                                 const char * path, int Lpath);

void SIDRE_group_destroy_group_name(SIDRE_group * self, const char * path);

void SIDRE_group_destroy_group_name_bufferify(SIDRE_group * self,
                                              const char * path, int Lpath);

void SIDRE_group_destroy_group_index(SIDRE_group * self, SIDRE_IndexType idx);

SIDRE_group * SIDRE_group_move_group(SIDRE_group * self, SIDRE_group * grp);

void SIDRE_group_print(const SIDRE_group * self);

bool SIDRE_group_is_equivalent_to(const SIDRE_group * self,
                                  const SIDRE_group * other);

void SIDRE_group_save(const SIDRE_group * self, const char * file_path,
                      const char * protocol);

void SIDRE_group_save_bufferify(const SIDRE_group * self,
                                const char * file_path, int Lfile_path,
                                const char * protocol, int Lprotocol);

void SIDRE_group_load(SIDRE_group * self, const char * file_path,
                      const char * protocol);

void SIDRE_group_load_bufferify(SIDRE_group * self, const char * file_path,
                                int Lfile_path, const char * protocol,
                                int Lprotocol);

void SIDRE_group_load_external_data(SIDRE_group * self, const char * file_path);

void SIDRE_group_load_external_data_bufferify(SIDRE_group * self,
                                              const char * file_path,
                                              int Lfile_path);

#ifdef __cplusplus
}
#endif

#endif  // WRAPGROUP_H