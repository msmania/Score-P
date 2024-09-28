/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file cubew_location.c
   \brief Defines types and functions to deal with locations of running application.
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "cubew_location.h"
#include "cubew_location_group.h"
#include "cubew_meta_data_writer.h"
#include "cubew_vector.h"
#include "cubew_services.h"
#include "cubew_memory.h"

#define MEMORY_TRACING_PREFIX "[LOCATION]"
/**
 * Allocates memory for the structure "location"
 */
cube_location*
cube_location_create( cube_location* loc )
{
    if ( loc == NULL )
    {
        ALLOC( loc, 1, cube_location, MEMORY_TRACING_PREFIX "Allocate location"  );
    }
    loc->attr = NULL;
    /* construct attrs array */
    XALLOC( loc->attr, 1, att_array, MEMORY_TRACING_PREFIX "Allocate cnode attribute"  );
    loc->attr->size     = 0;
    loc->attr->capacity = 0;

    return loc;
}


/**
 * Fills the location with the information (rank, namem, id).
 *
 */
void
cube_location_init( cube_location*       loc,
                    const char*          name,
                    int                  rank,
                    cube_location_type   type,
                    cube_location_group* parent )
{
    loc->name   = cubew_strdup( name );
    loc->rank   = rank;
    loc->type   = type;
    loc->parent = parent;
    if ( parent != NULL )
    {
        cube_location_add_child( loc->parent, loc );
    }
}


/**
 * Adds a child of this location.
 *
 */
void
cube_location_add_child( cube_location_group* parent,
                         cube_location*       thrd )
{
    ADD_NEXT( parent->child, thrd, cube_location*, MEMORY_TRACING_PREFIX "Add next location to same parent"  );
}

/**
 * Releases memory of the structure "location"
 */
void
cube_location_free( cube_location* loc )
{
    if ( loc != NULL )
    {
        CUBEW_FREE( loc->name, MEMORY_TRACING_PREFIX "Release name of location"  );
        if ( loc->attr )
        {
            uint32_t i = 0;
            for ( i = 0; i < loc->attr->size; i++ )
            {
                CUBEW_FREE( ( loc->attr->data[ i ] )->key, MEMORY_TRACING_PREFIX "Release key of a location attribute"  );
                CUBEW_FREE( ( loc->attr->data[ i ] )->value, MEMORY_TRACING_PREFIX "Release value of a location attribute"  );
                CUBEW_FREE( loc->attr->data[ i ], MEMORY_TRACING_PREFIX "Release location attribute"  );
            }
            CUBEW_FREE( loc->attr->data, MEMORY_TRACING_PREFIX "Release vector of location attributes"  );
            CUBEW_FREE( loc->attr, MEMORY_TRACING_PREFIX "Release location attributes"  );
        }
    }
    CUBEW_FREE( loc, MEMORY_TRACING_PREFIX "Release location"  );
}


/**
 * Adds an attribute  "m" into location "loc"
 */
void
cube_location_add_attr( cube_location* loc,
                        cmap*          m )
{
    ADD_NEXT( loc->attr, m, cmap*, MEMORY_TRACING_PREFIX "Add a location attrubute"  );
}

/**
 * Creates and add in to location "loc" the attribute "key" with a vaue "value"
 */
void
cube_location_def_attr( cube_location* loc,
                        const char*    key,
                        const char*    value )
{
    char* nkey   = cubew_strdup( key );
    char* nvalue = cubew_strdup( value );
    cmap*
    XALLOC( m,
            1,
            cmap,
            MEMORY_TRACING_PREFIX "Allocate location attribute"  );

    m->key   = nkey;
    m->value = nvalue;
    cube_location_add_attr( loc, m );
}


cube_location_group*
cube_location_get_parent( cube_location* loc )
{
    return loc->parent;
}

char*
cube_location_get_name( cube_location* loc )
{
    return loc->name;
}

cube_location_type
cube_location_get_type( cube_location* loc )
{
    return loc->type;
}

int
cube_location_get_rank( cube_location* loc )
{
    return loc->rank;
}

int
cube_location_get_level( cube_location* loc )
{
    if ( cube_location_get_parent( loc ) == NULL )
    {
        return 0;
    }
    return cube_location_group_get_level( cube_location_get_parent( loc ) ) + 1;
}

/**
 * Writes XML output for location in to .cube file.
 * No recursiv. Plain one after another.
 *
 */
void
cube_location_writeXML( cube_location*         loc,
                        cube_meta_data_writer* meta_data_writer )
{
    char* _name = ( char* )cube_services_escape_to_xml__( cube_location_get_name( loc ) );

    cube_location_type _type_ = cube_location_get_type( loc );
    char*              _type  =  ( _type_ == CUBE_LOCATION_TYPE_CPU_THREAD ) ? "thread" :
                                ( _type_ == CUBE_LOCATION_TYPE_METRIC ) ? "metric" :
                                ( _type_ == CUBE_LOCATION_TYPE_ACCELERATOR_STREAM ) ? "accelerator stream" :
                                "not supported";

    cube_write_meta_data__( meta_data_writer,  "<location Id=\"%d\">\n", cube_location_get_id( loc ) );
    cube_write_meta_data__( meta_data_writer,  "<name>%s</name>\n", _name ? _name : cube_location_get_name( loc ) );
    cube_write_meta_data__( meta_data_writer,  "<rank>%d</rank>\n", cube_location_get_rank( loc ) );
    cube_write_meta_data__( meta_data_writer,  "<type>%s</type>\n", _type );
    cube_services_write_attributes__( meta_data_writer,  loc->attr );
    cube_write_meta_data__( meta_data_writer,  "</location>\n" );

    CUBEW_FREE( _name, MEMORY_TRACING_PREFIX "Release _name"  );
}

void
cube_location_set_id( cube_location* loc,
                      int            new_id )
{
    loc->id = new_id;
}

int
cube_location_get_id( cube_location* loc )
{
    return loc->id;
}

/**
 * Compares equality of two locations.
 */
int
cube_location_equal( cube_location* a,
                     cube_location* b )
{
    int _a = cube_location_get_rank( a );
    int _b = cube_location_get_rank( b );
    if ( _a == _b )
    {
        int _p_a = cube_location_group_get_rank( cube_location_get_parent( a ) );
        int _p_b = cube_location_group_get_rank( cube_location_get_parent( b ) );
        if (  _p_a == _p_b )
        {
            return 1;
        }
    }
    return 0;
}
