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
 * \file cubew_system_tree_node_plain.c
 * \brief Defines types and functions to deal with running system_tree_node as whole object.
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>

#include "cubew_system_tree_node_plain.h"
#include "cubew_location_group_plain.h"
#include "cubew_meta_data_writer.h"
#include "cubew_vector.h"
#include "cubew_services.h"
#include "cubew_memory.h"

#define MEMORY_TRACING_PREFIX "[SYSTEM TREE NODE PLAIN]"

/**
 * Allocates memory for system_tree_node.
 */
cube_system_tree_node_plain*
cube_system_tree_node_plain_create( void )
{
    cube_system_tree_node_plain* stn = NULL;
    ALLOC( stn, 1, cube_system_tree_node_plain, MEMORY_TRACING_PREFIX "Allocate plain system tree node"  );
    XALLOC( stn->attr, 1, att_array, MEMORY_TRACING_PREFIX "Allocate plain system tree node attribute" );
    stn->attr->size     = 0;
    stn->attr->capacity = 0;
    return stn;
}


/**
 * Sets a general desription of the system_tree_node and its name.
 */
void
cube_system_tree_node_plain_init( cube_system_tree_node_plain* stn,
                                  char*                        name,
                                  char*                        desc,
                                  char*                        stn_class
                                  )
{
    stn->name      = name;
    stn->desc      = desc;
    stn->stn_class = stn_class;
    cube_system_tree_node_plain_clear( stn );
}


/**
 * Releases memory  of the  system_tree_node.
 */
void
cube_system_tree_node_plain_clear( cube_system_tree_node_plain* stn )
{
    if ( stn->attr )
    {
        uint32_t i = 0;
        for ( i = 0; i < stn->attr->size; i++ )
        {
            CUBEW_FREE( ( stn->attr->data[ i ] )->key, MEMORY_TRACING_PREFIX "Release key of a plain system tree node attribute" );
            CUBEW_FREE( ( stn->attr->data[ i ] )->value, MEMORY_TRACING_PREFIX "Release value of a plain system tree node attribute" );
            CUBEW_FREE( stn->attr->data[ i ], MEMORY_TRACING_PREFIX "Release a plain system tree node attribute"  );
        }
        CUBEW_FREE( stn->attr->data, MEMORY_TRACING_PREFIX "Release vector of plain system tree node attributes"  );
        stn->attr->size     = 0;
        stn->attr->capacity = 0;
    }
}


/**
 * Releases memory  of the  system_tree_node.
 */
void
cube_system_tree_node_plain_free( cube_system_tree_node_plain* stn )
{
    if ( stn != NULL )
    {
        cube_system_tree_node_plain_clear( stn );
        CUBEW_FREE( stn->attr, MEMORY_TRACING_PREFIX "Release plain system tree node attributes" );
    }
    CUBEW_FREE( stn, MEMORY_TRACING_PREFIX "Release a plain system tree node"  );
}



/**
 * Adds an attribute  "m" into cube "stn"
 */
void
cube_system_tree_node_plain_add_attr( cube_system_tree_node_plain* stn,
                                      cmap*                        m )
{
    ADD_NEXT( stn->attr, m, cmap*, MEMORY_TRACING_PREFIX "Add a plain system tree node attrubute" );
}

/**
 * Creates and add in to cube "stn" the attribute "key" with a vaue "value"
 */
void
cube_system_tree_node_plain_def_attr( cube_system_tree_node_plain* stn,
                                      char*                        key,
                                      char*                        value )
{
    cmap*
    XALLOC( m,
            1,
            cmap,
            MEMORY_TRACING_PREFIX "Allocate a plain system tree node attribute" );

    m->key   = key;
    m->value = value;
    cube_system_tree_node_plain_add_attr( stn, m );
}


void
cube_system_tree_node_plain_write( cube_system_tree_node_plain* stn,
                                   uint32_t                     id,
                                   cube_meta_data_writer*       meta_data_writer )
{
    if ( stn != NULL )
    {
        char* _name  = ( char* )cube_services_escape_to_xml__( stn->name );
        char* _descr = ( char* )cube_services_escape_to_xml__( stn->desc );
        char* _class = ( char* )cube_services_escape_to_xml__( stn->stn_class );

        cube_write_meta_data__( meta_data_writer,  "<systemtreenode Id=\"%d\">\n", id );
        cube_write_meta_data__( meta_data_writer,  "<name>%s</name>\n", _name  );
        cube_write_meta_data__( meta_data_writer,  "<class>%s</class>\n", _class  );
        if ( strcmp( _descr, "" ) != 0 )
        {
            cube_write_meta_data__( meta_data_writer,  "<descr>%s</descr>\n",  _descr  );
        }

        cube_services_write_attributes__( meta_data_writer,  stn->attr );
        CUBEW_FREE( _name, MEMORY_TRACING_PREFIX "Release _name" );
        CUBEW_FREE( _descr, MEMORY_TRACING_PREFIX "Release _descr" );
        CUBEW_FREE( _class, MEMORY_TRACING_PREFIX "Release _class" );
    }
    else
    {
        cube_write_meta_data__( meta_data_writer,  "</systemtreenode>\n" );
    }
}
