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
 * \file cubew_system_tree_node.c
 * \brief Defines types and functions to deal with running system_tree_node as whole object.
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>

#include "cubew_system_tree_node.h"
#include "cubew_location_group.h"
#include "cubew_vector.h"
#include "cubew_services.h"
#include "cubew_meta_data_writer.h"
#include "cubew_memory.h"
#include "UTILS_Error.h"

#define MEMORY_TRACING_PREFIX "[SYSTEM TREE NODE]"


/**
 * Allocates memory for a child system_tree_node.
 */
static
void
cube_system_tree_node_construct_child( cube_system_tree_node* stn )
{
    XALLOC( stn->child, 1, cube_stnarray, MEMORY_TRACING_PREFIX "Allocate vector of children of a system tree" );
    stn->child->size     = 0;
    stn->child->capacity = 0;
    XALLOC( stn->group, 1, cube_lgarray, MEMORY_TRACING_PREFIX "Allocate vector of groups of a system tree" );
    stn->group->size     = 0;
    stn->group->capacity = 0;
}



/**
 * Allocates memory for system_tree_node.
 */
cube_system_tree_node*
cube_system_tree_node_create( cube_system_tree_node* stn )
{
    if ( stn == NULL )
    {
        ALLOC( stn, 1, cube_system_tree_node, MEMORY_TRACING_PREFIX "Allocate system tree node" );
    }
    if ( stn != NULL )
    {
        cube_system_tree_node_construct_child( stn );
    }
    stn->attr = NULL;
    /* construct attrs array */
    XALLOC( stn->attr, 1, att_array, MEMORY_TRACING_PREFIX "Allocate system tree node attribute"  );
    stn->attr->size     = 0;
    stn->attr->capacity = 0;

    return stn;
}

/**
 * Sets a general desription of the system_tree_node and its name.
 */
void
cube_system_tree_node_init( cube_system_tree_node* stn,
                            const char*            name,
                            const char*            desc,
                            const char*            stn_class,
                            cube_system_tree_node* parent
                            )
{
    stn->name      = cubew_strdup( name );
    stn->desc      = cubew_strdup( desc );
    stn->stn_class = cubew_strdup( stn_class );
    stn->parent    = parent;
    if ( parent != NULL )
    {
        cube_system_tree_node_add_child( stn->parent, stn );
    }
}

/**
 * Allocates memory for a nodes of the  system_tree_node.
 */
void
cube_system_tree_node_reserve_nodes( cube_system_tree_node* stn,
                                     unsigned               num )
{
    stn->child->capacity = num;
    ALLOC( stn->child->data, stn->child->capacity, cube_system_tree_node*, MEMORY_TRACING_PREFIX "Allocate vector for the children of a system tree node" );
}

/**
 * Releases memory  of the  system_tree_node.
 */
void
cube_system_tree_node_free( cube_system_tree_node* stn )
{
    if ( stn != NULL )
    {
        CUBEW_FREE( stn->name, MEMORY_TRACING_PREFIX "Release system tree node name " );
        CUBEW_FREE( stn->desc, MEMORY_TRACING_PREFIX "Release system tree node description " );
        CUBEW_FREE( stn->stn_class, MEMORY_TRACING_PREFIX "Release system tree node class " );
        if ( stn->child != NULL )
        {
            CUBEW_FREE( stn->child->data, MEMORY_TRACING_PREFIX "Release vector of children of a system tree node name " );
        }
        if ( stn->group != NULL )
        {
            CUBEW_FREE( stn->group->data, MEMORY_TRACING_PREFIX "Release vector of groups of a system tree node name " );
        }
        CUBEW_FREE( stn->group, MEMORY_TRACING_PREFIX "Release groups of a system tree node name " );
        CUBEW_FREE( stn->child, MEMORY_TRACING_PREFIX "Release children of a system tree node name " );
        if ( stn->attr )
        {
            uint32_t i = 0;
            for ( i = 0; i < stn->attr->size; i++ )
            {
                CUBEW_FREE( ( stn->attr->data[ i ] )->key, MEMORY_TRACING_PREFIX "Release key of a location group attribute" );
                CUBEW_FREE( ( stn->attr->data[ i ] )->value, MEMORY_TRACING_PREFIX "Release value of a location group attribute" );
                CUBEW_FREE( stn->attr->data[ i ], MEMORY_TRACING_PREFIX "Release location group attribute" );
            }
            CUBEW_FREE( stn->attr->data, MEMORY_TRACING_PREFIX "Release vector of location group attributes"  );
        }
        CUBEW_FREE( stn->attr, MEMORY_TRACING_PREFIX "Release location group attributes" );
    }
    CUBEW_FREE( stn, MEMORY_TRACING_PREFIX "Release system tree node"  );
}



/**
 * Adds an attribute  "m" into cube "this"
 */
void
cube_system_tree_node_add_attr( cube_system_tree_node* stn,
                                cmap*                  m )
{
    ADD_NEXT( stn->attr, m, cmap*, MEMORY_TRACING_PREFIX "Add a system tree node attrubute"   );
}

/**
 * Creates and add in to cube "this" the attribute "key" with a vaue "value"
 */
void
cube_system_tree_node_def_attr( cube_system_tree_node* stn,
                                const char*            key,
                                const char*            value )
{
    char* nkey   = cubew_strdup( key );
    char* nvalue = cubew_strdup( value );
    cmap*
    XALLOC( m,
            1,
            cmap,
            MEMORY_TRACING_PREFIX "Allocate system tree attribute" );

    m->key   = nkey;
    m->value = nvalue;
    cube_system_tree_node_add_attr( stn, m );
}


/**
 * Returns a i-th child on the system_tree_node.
 */
cube_system_tree_node*
cube_system_tree_node_get_child( cube_system_tree_node* stn,
                                 uint32_t               i )
{
    if ( i < 0 || i >= stn->child->size )
    {
        UTILS_WARNING( "cube_system_tree_node_get_child: out of range\n" );
    }
    return stn->child->data[ i ];
}

struct cube_location_group*
cube_system_tree_node_get_location_group( cube_system_tree_node* stn,
                                          uint32_t               i )
{
    if ( i < 0 || i >= stn->group->size )
    {
        UTILS_WARNING( "cube_system_tree_node_get_location_group: out of range\n" );
    }
    return stn->group->data[ i ];
}

char*
cube_system_tree_node_get_name( cube_system_tree_node* stn )
{
    return stn->name;
}

char*
cube_system_tree_node_get_desc( cube_system_tree_node* stn )
{
    return stn->desc;
}
char*
cube_system_tree_node_get_class( cube_system_tree_node* stn )
{
    return stn->stn_class;
}
uint32_t
cube_system_tree_node_num_children( cube_system_tree_node* stn )
{
    return stn->child->size;
}
uint32_t
cube_system_tree_node_num_location_group( cube_system_tree_node* stn )
{
    return stn->group->size;
}

int
cube_system_tree_node_get_level( cube_system_tree_node* stn )
{
    if ( stn == NULL )
    {
        UTILS_WARNING( "WARNING: argument in the call \"cube_system_tree_node_get_level\" is NULL" );
    }
    int                    level   = 0;
    cube_system_tree_node* _parent = stn->parent;
    while ( _parent != NULL )
    {
        level   = level + 1;
        _parent = _parent->parent;
    }
    return level;
}

/**
 * Writes a XML output of the system_tree_node in the .cube file.
 */
void
cube_system_tree_node_writeXML( cube_system_tree_node* stn,
                                cube_meta_data_writer* meta_data_writer )
{
    char* _name  = ( char* )cube_services_escape_to_xml__( cube_system_tree_node_get_name( stn ) );
    char* _descr = ( char* )cube_services_escape_to_xml__( cube_system_tree_node_get_desc( stn ) );
    char* _class = ( char* )cube_services_escape_to_xml__( cube_system_tree_node_get_class( stn ) );

    cube_write_meta_data__( meta_data_writer,  "<systemtreenode Id=\"%d\">\n", cube_system_tree_node_get_id( stn ) );
    cube_write_meta_data__( meta_data_writer,  "<name>%s</name>\n", _name ? _name :  cube_system_tree_node_get_name( stn ) );
    cube_write_meta_data__( meta_data_writer,  "<class>%s</class>\n", _class ? _class :  cube_system_tree_node_get_class( stn ) );
    if ( strcmp( cube_system_tree_node_get_desc( stn ), "" ) != 0 )
    {
        cube_write_meta_data__( meta_data_writer,  "<descr>%s</descr>\n",  _descr ? _descr : cube_system_tree_node_get_desc( stn ) );
    }

    cube_services_write_attributes__( meta_data_writer,  stn->attr );


    uint32_t i = 0;
    for ( i = 0; i < cube_system_tree_node_num_location_group( stn ); i++ )
    {
        cube_location_group* lg = cube_system_tree_node_get_location_group( stn, i );
        cube_location_group_writeXML( lg, meta_data_writer );
    }
    for ( i = 0; i < cube_system_tree_node_num_children( stn ); i++ )
    {
        cube_system_tree_node* node = cube_system_tree_node_get_child( stn, i );
        cube_system_tree_node_writeXML( node, meta_data_writer );
    }
    cube_write_meta_data__( meta_data_writer,  "</systemtreenode>\n" );

    CUBEW_FREE( _name, MEMORY_TRACING_PREFIX "Release _name" );
    CUBEW_FREE( _descr, MEMORY_TRACING_PREFIX "Release _descr" );
    CUBEW_FREE( _class, MEMORY_TRACING_PREFIX "Release _class" );
}

void
cube_system_tree_node_set_id( cube_system_tree_node* stn,
                              int                    new_id )
{
    stn->id = new_id;
}

int
cube_system_tree_node_get_id( cube_system_tree_node* stn )
{
    return stn->id;
}

/**
 * Compares eaquality of two system_tree_nodes
 */
int
cube_system_tree_node_equal( cube_system_tree_node* a,
                             cube_system_tree_node* b )
{
    const char* _a = cube_system_tree_node_get_name( a );
    const char* _b = cube_system_tree_node_get_name( b );
    if ( strcmp( _a, _b ) == 0 )
    {
        return 1;
    }
    return 0;
}

/**
 * Ads a location_group "proc" to the location_group "stn".
 *
 */
void
cube_system_tree_node_add_child( cube_system_tree_node* parent,
                                 cube_system_tree_node* child )
{
    ADD_NEXT( parent->child, child, cube_system_tree_node*, MEMORY_TRACING_PREFIX "Add system tree node to as a child to system tree node" );
}
/**
 * Ads a location_group "proc" to the location_group "stn".
 *
 */
void
cube_system_tree_node_add_group( cube_system_tree_node* parent,
                                 cube_location_group*   lg )
{
    ADD_NEXT( parent->group, lg, cube_location_group*, MEMORY_TRACING_PREFIX "Add location group to as a child to system tree node" );
}
