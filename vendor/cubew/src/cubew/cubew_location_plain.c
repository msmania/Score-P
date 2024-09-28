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
 * \file cubew_location_plain.c
   \brief Defines types and functions to deal with locations of running application.
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "cubew_location_plain.h"
#include "cubew_location_group_plain.h"
#include "cubew_meta_data_writer.h"
#include "cubew_vector.h"
#include "cubew_services.h"
#include "cubew_memory.h"

#define MEMORY_TRACING_PREFIX "[LOCATION PLAIN]"

/**
 * Allocates memory for the structure "location"
 */
cube_location_plain*
cube_location_plain_create( void )
{
    cube_location_plain* loc = NULL;
    ALLOC( loc, 1, cube_location_plain, MEMORY_TRACING_PREFIX "Allocate plain location" );
    XALLOC( loc->attr, 1, att_array, MEMORY_TRACING_PREFIX "Allocate plain location attribute" );
    loc->attr->size     = 0;
    loc->attr->capacity = 0;
    return loc;
}


/**
 * Fills the location with the information (rank, namem, id).
 *
 */
void
cube_location_plain_init( cube_location_plain* loc,
                          char*                name,
                          int                  rank,
                          cube_location_type   type )
{
    loc->name = name;
    loc->rank = rank;
    loc->type = type;
    cube_location_plain_clear( loc );
}

void
cube_location_plain_clear( cube_location_plain* loc )
{
    if ( loc->attr )
    {
        uint32_t i = 0;
        for ( i = 0; i < loc->attr->size; i++ )
        {
            CUBEW_FREE( ( loc->attr->data[ i ] )->key, MEMORY_TRACING_PREFIX "Release key of a plain location attribute" );
            CUBEW_FREE( ( loc->attr->data[ i ] )->value, MEMORY_TRACING_PREFIX "Release value of a plain location attribute" );
            CUBEW_FREE( loc->attr->data[ i ], MEMORY_TRACING_PREFIX "Release a plain location attribute" );
        }
        CUBEW_FREE( loc->attr->data, MEMORY_TRACING_PREFIX "Release vector of plain location attributes" );
        loc->attr->size     = 0;
        loc->attr->capacity = 0;
    }
}


/**
 * Releases memory of the structure "location"
 */
void
cube_location_plain_free( cube_location_plain* loc )
{
    if (  loc != NULL )
    {
        cube_location_plain_clear( loc );
        CUBEW_FREE( loc->attr, MEMORY_TRACING_PREFIX "Release plain location attributes" );
    }
    CUBEW_FREE( loc, MEMORY_TRACING_PREFIX "Release a plain location" );
}

void
cube_location_plain_add_attr( cube_location_plain* loc,
                              cmap*                m )
{
    ADD_NEXT( loc->attr, m, cmap*, MEMORY_TRACING_PREFIX "Add a plain location attrubute" );
}

void
cube_location_plain_def_attr( cube_location_plain* loc,
                              char*                key,
                              char*                value )
{
    cmap*
    XALLOC( m,
            1,
            cmap,
            MEMORY_TRACING_PREFIX "Allocate a plain location attribute" );

    m->key   = key;
    m->value = value;
    cube_location_plain_add_attr( loc, m );
}

void
cube_location_plain_write( cube_location_plain*   loc,
                           uint32_t               id,
                           cube_meta_data_writer* meta_data_writer )
{
    if (  loc != NULL )
    {
        char* _name = ( char* )cube_services_escape_to_xml__( loc->name );

        cube_location_type _type_ = loc->type;
        char*              _type  =  ( _type_ == CUBE_LOCATION_TYPE_CPU_THREAD ) ? "thread" :
                                    ( _type_ == CUBE_LOCATION_TYPE_METRIC ) ? "metric" :
                                    ( _type_ == CUBE_LOCATION_TYPE_ACCELERATOR_STREAM ) ? "accelerator stream" :
                                    "not supported";

        cube_write_meta_data__( meta_data_writer,  "<location Id=\"%d\">\n", id );
        cube_write_meta_data__( meta_data_writer,  "<name>%s</name>\n", _name  );
        cube_write_meta_data__( meta_data_writer,  "<rank>%d</rank>\n", loc->rank );
        cube_write_meta_data__( meta_data_writer,  "<type>%s</type>\n", _type );
        cube_services_write_attributes__( meta_data_writer,  loc->attr );
        CUBEW_FREE( _name, MEMORY_TRACING_PREFIX "Release _name" );
    }
    else
    {
        cube_write_meta_data__( meta_data_writer,  "</location>\n" );
    }
}
