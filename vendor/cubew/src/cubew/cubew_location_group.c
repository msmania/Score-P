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
 * \file cubew_location_group.c
   \brief Defines types and functions to deal with location group of running application.
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "cubew_location_group.h"
#include "cubew_system_tree_node.h"
#include "cubew_location.h"
#include "cubew_meta_data_writer.h"
#include "cubew_vector.h"
#include "cubew_memory.h"
#include "cubew_services.h"
#include "UTILS_Error.h"

#define MEMORY_TRACING_PREFIX "[LOCATION GROUP]"

/**
 * Creates a child of this location_group.
 *
 */
static
void
cube_location_group_construct_child( cube_location_group* lg )
{
    XALLOC( lg->child, 1, cube_larray, MEMORY_TRACING_PREFIX "Allocate vector of children of a location group"  );
    lg->child->size     = 0;
    lg->child->capacity = 0;
}



/**
 * Allocates memory for a location_group structure.
 *
 */
cube_location_group*
cube_location_group_create( cube_location_group* lg )
{
    if ( lg == NULL )
    {
        ALLOC( lg, 1, cube_location_group, MEMORY_TRACING_PREFIX "Allocate location group"  );
    }
    if ( lg != NULL )
    {
        cube_location_group_construct_child( lg );
    }
    lg->attr = NULL;
    /* construct attrs array */
    XALLOC( lg->attr, 1, att_array, MEMORY_TRACING_PREFIX "Allocate location group attribute"  );
    lg->attr->size     = 0;
    lg->attr->capacity = 0;

    return lg;
}

/**
 * Fills the structure with name and rank of location_group.
 *
 */
void
cube_location_group_init( cube_location_group*     lg,
                          const char*              name,
                          int                      rank,
                          cube_location_group_type type,
                          cube_system_tree_node*   parent )
{
    lg->name   = cubew_strdup( name );
    lg->rank   = rank;
    lg->parent = parent;
    lg->type   = type;
    if ( parent != NULL )
    {
        cube_location_group_add_child( lg->parent, lg );
    }
}


/**
 * Ads a location_group "proc" to the location_group "lg".
 *
 */
void
cube_location_group_add_child( cube_system_tree_node* parent,
                               cube_location_group*   lg )
{
    ADD_NEXT( parent->group, lg, cube_location_group*, MEMORY_TRACING_PREFIX "Add location group to same parent"  );
}

/**
 * Releases memory for a location_group structure.
 *
 */
void
cube_location_group_free( cube_location_group* lg )
{
    if ( lg != NULL )
    {
        CUBEW_FREE( lg->name, MEMORY_TRACING_PREFIX "Release name of location group"  );
        if ( lg->child != NULL )
        {
            CUBEW_FREE( lg->child->data, MEMORY_TRACING_PREFIX "Release vector of children of location group"  );
        }
        if ( lg->attr )
        {
            uint32_t i = 0;
            for ( i = 0; i < lg->attr->size; i++ )
            {
                CUBEW_FREE( ( lg->attr->data[ i ] )->key, MEMORY_TRACING_PREFIX "Release key of a location group attribute" );
                CUBEW_FREE( ( lg->attr->data[ i ] )->value, MEMORY_TRACING_PREFIX "Release value of a location group attribute" );
                CUBEW_FREE( lg->attr->data[ i ], MEMORY_TRACING_PREFIX "Release location group attribute" );
            }
            CUBEW_FREE( lg->attr->data, MEMORY_TRACING_PREFIX "Release vector of location group attributes"  );
        }
        CUBEW_FREE( lg->attr, MEMORY_TRACING_PREFIX "Release location group attributes" );
        CUBEW_FREE( lg->child, MEMORY_TRACING_PREFIX "Release location group children" );
    }
    CUBEW_FREE( lg, MEMORY_TRACING_PREFIX "Release location group" );
}



/**
 * Adds an attribute  "m" into cube "lg"
 */
void
cube_location_group_add_attr( cube_location_group* lg,
                              cmap*                m )
{
    ADD_NEXT( lg->attr, m, cmap*, MEMORY_TRACING_PREFIX "Add a location group attrubute"   );
}

/**
 * Creates and add in to cube "lg" the attribute "key" with a vaue "value"
 */
void
cube_location_group_def_attr( cube_location_group* lg,
                              const char*          key,
                              const char*          value )
{
    char* nkey   = cubew_strdup( key );
    char* nvalue = cubew_strdup( value );
    cmap*
    XALLOC( m,
            1,
            cmap,
            MEMORY_TRACING_PREFIX "Allocate location group attribute"   );

    m->key   = nkey;
    m->value = nvalue;
    cube_location_group_add_attr( lg, m );
}


cube_location*
cube_location_group_get_child( cube_location_group* lg,
                               uint32_t             i )
{
    if ( i < 0 || i >= lg->child->size )
    {
        UTILS_WARNING( "cube_location_group_get_child: out of range\n" );
    }
    return lg->child->data[ i ];
}

cube_system_tree_node*
cube_location_group_get_parent( cube_location_group* lg )
{
    return lg->parent;
}

int
cube_location_group_get_rank( cube_location_group* lg )
{
    return lg->rank;
}

char*
cube_location_group_get_name( cube_location_group* lg )
{
    return lg->name;
}

cube_location_group_type
cube_location_group_get_type( cube_location_group* lg )
{
    return lg->type;
}

uint32_t
cube_location_group_num_children( cube_location_group* lg )
{
    return lg->child->size;
}

/**
 * Gets a level of the location_group.
 * Does it recursiv with "deep search" algorithm
 */
int
cube_location_group_get_level( cube_location_group* lg )
{
    if ( cube_location_group_get_parent( lg ) == NULL )
    {
        return 0;
    }
    return cube_system_tree_node_get_level( cube_location_group_get_parent( lg ) ) + 1;
}

/**
 * Writes XML output for location_group in to .cube file.
 * Does it recursiv with "deep search" algorithm
 */
void
cube_location_group_writeXML( cube_location_group*   lg,
                              cube_meta_data_writer* meta_data_writer )
{
    char* _name = ( char* )cube_services_escape_to_xml__( cube_location_group_get_name( lg ) );

    cube_location_group_type _type_ = cube_location_group_get_type( lg );
    char*                    _type  = ( _type_ == CUBE_LOCATION_GROUP_TYPE_PROCESS ) ? "process" :
                                      ( _type_ == CUBE_LOCATION_GROUP_TYPE_METRICS ) ? "metrics" :
                                      ( _type_ == CUBE_LOCATION_GROUP_TYPE_ACCELERATOR ) ? "accelerator" :
                                      "not supported";
    cube_write_meta_data__( meta_data_writer,  "<locationgroup Id=\"%d\">\n", cube_location_group_get_id( lg ) );
    cube_write_meta_data__( meta_data_writer,  "<name>%s</name>\n", _name ? _name : cube_location_group_get_name( lg ) );
    cube_write_meta_data__( meta_data_writer,  "<rank>%d</rank>\n", cube_location_group_get_rank( lg ) );
    cube_write_meta_data__( meta_data_writer,  "<type>%s</type>\n", _type );
    cube_services_write_attributes__( meta_data_writer,  lg->attr );
    uint32_t i = 0;
    for ( i = 0; i < cube_location_group_num_children( lg ); i++ )
    {
        cube_location* thrd = cube_location_group_get_child( lg, i );
        cube_location_writeXML( thrd, meta_data_writer );
    }
    cube_write_meta_data__( meta_data_writer,  "</locationgroup>\n" );

    if ( _name )
    {
        CUBEW_FREE( _name, MEMORY_TRACING_PREFIX "Release _name" );
    }
}

void
cube_location_group_set_id( cube_location_group* lg,
                            int                  new_id )
{
    lg->id = new_id;
}

int
cube_location_group_get_id( cube_location_group* lg )
{
    return lg->id;
}

/**
 * Compares equality of two location_groupes.
 */
int
cube_location_group_equal( cube_location_group* a,
                           cube_location_group* b )
{
    unsigned _a = cube_location_group_get_rank( a );
    unsigned _b = cube_location_group_get_rank( b );
    if ( _a == _b  )
    {
        return 1;
    }
    return 0;
}
