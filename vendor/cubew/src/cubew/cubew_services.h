/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file cubew_services.h
   \brief Provides all kind of service functions. Cannot be linked from libcubew.a.
 */
#ifndef CUBEW_SERVICES_H
#define CUBEW_SERVICES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cubew_types.h"

/*          public part  */
char*
cube_services_escape_to_xml__( char* str );
void
cube_print_bit_string__( char*    bitstring,
                         unsigned size );
void
cube_print_row__( void*    row,
                  unsigned size );

/*     private part, should be not calles "standalone      */
enum DataType
cube_metric_dtype2data_type__( const char* dtype );
int
cube_metric_size_dtype__( cube_value_param_array* dtype );
char*
cube_metric_dtype2string__( cube_value_param_array* dtype );

cube_value_param_array*
cube_metric_dtype_param_split__( const char* dtype  );

void
cube_value_param_free__( cube_value_param_array* _array );

uint32_t
cube_metric_bit_position__( char*    bit_vector,
                            unsigned vlen,
                            unsigned cid );
uint32_t
cube_metric_size_of_index__( char*    bit_vector,
                             unsigned vlen );
uint32_t*
cube_metric_create_index__( char*    bit_vector,
                            unsigned vlen );
unsigned
cube_is_bit_set__( char* bit_vector,
                   int   bitposition );
void
cube_set_bit__( char* bit_vector,
                int   bitposition );

int
/* -1 shows empty bitstring */
cube_metric_last_bit_position__( char*    bit_vector,
                                 unsigned vlen
                                 );
size_t
cube_num_of_set_bits__( char*    bit_vector,
                        unsigned vlen
                        );


uint64_t*
cube_transform_doubles_into_uint64__( double*  data_row,
                                      uint32_t size );
int64_t*
cube_transform_doubles_into_int64__( double*  data_row,
                                     uint32_t size );

double*
cube_transform_uint64_into_doubles__( uint64_t* data_row,
                                      uint32_t  size );

double*
cube_transform_int64_into_doubles__( int64_t* data_row,
                                     uint32_t size );


enum value_compat_t
cube_type_compatibility_check__( cube_value_param_array* from,
                                 cube_value_param_array* to );

void*
cube_transform_row_of_values__( cube_value_param_array* from,
                                cube_value_param_array* to,
                                void*                   row,
                                uint32_t                size );


void
cube_value_transform__(  cube_value_param_array* from,
                         cube_value_param_array* to,
                         void*                   target_place_for_value,
                         void*                   source,
                         uint32_t                to_sizeof,
                         uint32_t                from_sizeof );

void*
cube_get_init_value__( cube_value_param_array* dtype_params,
                       enum value_init_t       sort_of_value,
                       void*                   value );


void
cube_initialize_row_of_memory__( cube_value_param_array* dtype_params,
                                 enum value_init_t       sort_of_value,
                                 void*                   row,
                                 uint64_t                size,
                                 void*                   value );                                                         /* size -> in bytes */


void*
cube_get_zero_row__( cube_value_param_array* dtype_params,
                     uint64_t                size );   /* size -> in bytes */


void*
cube_get_undefined_row__( cube_value_param_array* dtype_params,
                          uint64_t                size );   /* size -> in bytes */


void*
cube_get_valued_row__( cube_value_param_array* dtype_params,
                       uint64_t                size,
                       void*                   value );                /* size -> in bytes */



void
cube_services_write_attributes__( cube_meta_data_writer* writer,
                                  cube_att_array*        attr
                                  );


char*
cubew_strdup( const char* str );


void
cube_create_path_for_file__( char* path );


/* Our cube wrapper the POSIX fseeko implementation, because it is not available in
   C99 be default.  */
int
cubew_fseeko( FILE*    stream,
              uint64_t offset,
              int      whence );


#ifdef __cplusplus
}
#endif

#endif
