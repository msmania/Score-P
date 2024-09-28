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
 * \file cubew_location_group_plain.c
   \brief Defines types and functions to deal with plain location group of running application.
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "cubew_location_group_plain.h"
#include "cubew_system_tree_node_plain.h"
#include "cubew_location_plain.h"
#include "cubew_meta_data_writer.h"
#include "cubew_vector.h"
#include "cubew_services.h"
#include "cubew_memory.h"

#define MEMORY_TRACING_PREFIX "[LOCATION GROUP PLAIN]"
/**
 * Allocates memory for a location_group structure.
 *
 */
cube_location_group_plain*
cube_location_group_plain_create( void )
{
    cube_location_group_plain* lg = NULL;
    ALLOC( lg, 1, cube_location_group_plain, MEMORY_TRACING_PREFIX "Allocate plain location group"  );
    XALLOC( lg->attr, 1, att_array, MEMORY_TRACING_PREFIX "Allocate plain location group attribute"  );
    lg->attr->size     = 0;
    lg->attr->capacity = 0;
    return lg;
}

/**
 * Fills the structure with name and rank of location_group.
 *
 */
void
cube_location_group_plain_init(  cube_location_group_plain* lg,
                                 char*                      name,
                                 int                        rank,
                                 cube_location_group_type   type )
{
    lg->name = name;
    lg->rank = rank;
    lg->type = type;
    cube_location_group_plain_clear( lg );
}

/**
 * Fills the structure with name and rank of location_group.
 *
 */
void
cube_location_group_plain_clear(  cube_location_group_plain* lg )
{
    if ( lg->attr )
    {
        uint32_t i = 0;
        for ( i = 0; i < lg->attr->size; i++ )
        {
            CUBEW_FREE( ( lg->attr->data[ i ] )->key, MEMORY_TRACING_PREFIX "Release key of a plain location group attribute" );
            CUBEW_FREE( ( lg->attr->data[ i ] )->value, MEMORY_TRACING_PREFIX "Release value of a plain location group attribute" );
            CUBEW_FREE( lg->attr->data[ i ], MEMORY_TRACING_PREFIX "Release a plain location group attribute"  );
        }
        CUBEW_FREE( lg->attr->data, MEMORY_TRACING_PREFIX "Release vector of plain location group attributes" );
        lg->attr->size     = 0;
        lg->attr->capacity = 0;
    }
}


/**
 * Releases memory for a location_group structure.
 *
 */
void
cube_location_group_plain_free( cube_location_group_plain* lg )
{
    if (  lg != NULL )
    {
        cube_location_group_plain_clear( lg );
        CUBEW_FREE( lg->attr, MEMORY_TRACING_PREFIX "Release plain location group attributes" );
    }
    CUBEW_FREE( lg, MEMORY_TRACING_PREFIX "Release a plain location group" );
}


void
cube_location_group_plain_add_attr( cube_location_group_plain* lg,
                                    cmap*                      m )
{
    ADD_NEXT( lg->attr, m, cmap*, MEMORY_TRACING_PREFIX "Add a plain location group attrubute" );
}
void
cube_location_group_plain_def_attr( cube_location_group_plain* lg,
                                    char*                      key,
                                    char*                      value )
{
    cmap*
    XALLOC( m,
            1,
            cmap,
            MEMORY_TRACING_PREFIX "Allocate a plain location group attribute"  );

    m->key   = key;
    m->value = value;
    cube_location_group_plain_add_attr( lg, m );
}


void
cube_location_group_plain_write( cube_location_group_plain* lg,
                                 uint32_t                   id,
                                 cube_meta_data_writer*     meta_data_writer )
{
    if (  lg != NULL )
    {
        char* _name = ( char* )cube_services_escape_to_xml__( lg->name );

        cube_location_group_type _type_ = lg->type;
        char*                    _type  = ( _type_ == CUBE_LOCATION_GROUP_TYPE_PROCESS ) ? "process" :
                                          ( _type_ == CUBE_LOCATION_GROUP_TYPE_METRICS ) ? "metrics" :
                                          ( _type_ == CUBE_LOCATION_GROUP_TYPE_ACCELERATOR ) ? "accelerator" :
                                          "not supported";
        cube_write_meta_data__( meta_data_writer,  "<locationgroup Id=\"%d\">\n", id );
        cube_write_meta_data__( meta_data_writer,  "<name>%s</name>\n", _name  );
        cube_write_meta_data__( meta_data_writer,  "<rank>%d</rank>\n", lg->rank );
        cube_write_meta_data__( meta_data_writer,  "<type>%s</type>\n", _type );
        cube_services_write_attributes__( meta_data_writer,  lg->attr );
        CUBEW_FREE( _name, MEMORY_TRACING_PREFIX "Release _name" );
    }
    else
    {
        cube_write_meta_data__( meta_data_writer,  "</locationgroup>\n" );
    }
}
