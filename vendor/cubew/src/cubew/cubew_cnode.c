/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2023                                                **
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
 * \file cubew_cnode.c
   \brief Defines types and functions to deal with calee nodes.
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>

#include "cubew_cnode.h"
#include "cubew_memory.h"
#include "cubew_region.h"
#include "cubew_vector.h"
#include "cubew_meta_data_writer.h"
#include "cubew_services.h"
#include "cubew_types.h"
#include "UTILS_Error.h"


#define MEMORY_TRACING_PREFIX "[CNODE]"


/**
 * Allocate memory for a child of some cnoed "this"
 */
static
void
cube_cnode_construct_child( cube_cnode* cnode )
{
    XALLOC( cnode->child, 1, carray, MEMORY_TRACING_PREFIX "Allocate cnode children" );
    cnode->child->size     = 0;
    cnode->child->capacity = 0;
}



/**
 * Allocates memory for cnodes in the cube.
 */
cube_cnode*
cube_cnode_create( cube_cnode* cnode )
{
    if ( ( cnode ) == NULL )
    {
        ALLOC( cnode, 1, cube_cnode, MEMORY_TRACING_PREFIX "Allocate cnode" );
    }
    if ( ( cnode ) != NULL )
    {
        cube_cnode_construct_child( ( cnode ) );
    }
    cnode->num_parameters    = NULL;
    cnode->string_parameters = NULL;
    cnode->attr              = NULL;
    /* construct attrs array */
    XALLOC( cnode->attr, 1, att_array, MEMORY_TRACING_PREFIX "Allocate cnode attributes" );
    cnode->attr->size     = 0;
    cnode->attr->capacity = 0;
    return cnode;
}

/**
 * Initialize the cnode structure with data and connect parents and children.
 */
void
cube_cnode_init( cube_cnode*         cnode,
                 struct cube_region* callee,
                 const char*         mod,
                 int                 line,
                 cube_cnode*         parent )
{
    cnode->parent = parent;
    cnode->callee = callee;
    cnode->mod    = cubew_strdup( mod );
    cnode->line   = line;

//   cnode->id = id;
    if ( parent != NULL )
    {
        cube_cnode_add_child( cnode->parent, ( cnode ) );
    }
}


/**
 * Add a new parameter in the parameter list. If there is no parameter yet, memory should be allocated.
 */
void
cube_cnode_add_numeric_parameter( cube_cnode* cnode,
                                  const char* param_name,
                                  double      value )
{
    if ( cnode->num_parameters == NULL )
    {
        XALLOC( cnode->num_parameters, 1, nparam_parray, MEMORY_TRACING_PREFIX "Allocate cnode numeric parameters" );
        cnode->num_parameters->size     = 0;
        cnode->num_parameters->capacity = 0;
    }
    nmap* parameter_pair = ( nmap* )CUBEW_MALLOC( sizeof( nmap ), MEMORY_TRACING_PREFIX "Allocate numeric parameter pair"  );
    parameter_pair->key   = cubew_strdup( param_name );
    parameter_pair->value = value;
    ADD_NEXT( cnode->num_parameters, parameter_pair, nmap*, MEMORY_TRACING_PREFIX "Add numeric parameter" );
}


/**
 * Add a new parameter in the parameter list. If there is no parameter yet, memory should be allocated.
 */
void
cube_cnode_add_string_parameter( cube_cnode* cnode,
                                 const char* param_name,
                                 const char* value )
{
    if ( cnode->string_parameters == NULL )
    {
        XALLOC( cnode->string_parameters, 1, cparam_parray, MEMORY_TRACING_PREFIX "Allocate cnode symbolic parameters" );
        cnode->string_parameters->size     = 0;
        cnode->string_parameters->capacity = 0;
    }

    cmap* parameter_pair = ( cmap* )CUBEW_MALLOC( sizeof( cmap ), MEMORY_TRACING_PREFIX "Allocate symbolic parameter pair"   );
    parameter_pair->key   = cubew_strdup( param_name );
    parameter_pair->value = cubew_strdup( value );
    ADD_NEXT( cnode->string_parameters, parameter_pair, cmap*, MEMORY_TRACING_PREFIX "Add symbolic parameter"  );
}





/**
 * Adds a child cnode "cnode" to the parent "parent"
 */
void
cube_cnode_add_child( cube_cnode* parent,
                      cube_cnode* cnode )
{
    ADD_NEXT( parent->child, cnode, cube_cnode*, MEMORY_TRACING_PREFIX "Add next child" );
}

/**
 * Releases a memory of cnode "this"
 */
void
cube_cnode_free( cube_cnode* cnode )
{
    if ( ( cnode ) != NULL )
    {
        if ( cnode->mod != 0 )
        {
            CUBEW_FREE( cnode->mod, MEMORY_TRACING_PREFIX "Release mod" );
        }
        CUBEW_FREE( cnode->child->data, MEMORY_TRACING_PREFIX "Release vector of children" );
        CUBEW_FREE( cnode->child, MEMORY_TRACING_PREFIX "Release child" );
        uint32_t i = 0;
        if ( cnode->num_parameters != NULL )
        {
            for ( i = 0; i < cnode->num_parameters->size; i++ )
            {
                CUBEW_FREE( cnode->num_parameters->data[ i ]->key, MEMORY_TRACING_PREFIX "Release key of numeric parameter" );
                CUBEW_FREE( cnode->num_parameters->data[ i ], MEMORY_TRACING_PREFIX "Release pair of numeric parameters" );
            }
            CUBEW_FREE( cnode->num_parameters->data, MEMORY_TRACING_PREFIX "Release content of numeric parameters" );
            CUBEW_FREE( cnode->num_parameters, MEMORY_TRACING_PREFIX "Release numeric parameters"  );
        }
        if ( cnode->string_parameters != NULL )
        {
            for ( i = 0; i < cnode->string_parameters->size; i++ )
            {
                CUBEW_FREE( cnode->string_parameters->data[ i ]->key, MEMORY_TRACING_PREFIX "Release key of symbolic parameter"  );
                CUBEW_FREE( cnode->string_parameters->data[ i ]->value, MEMORY_TRACING_PREFIX "Release value of symbolic parameter"  );
                CUBEW_FREE( cnode->string_parameters->data[ i ], MEMORY_TRACING_PREFIX "Release pair of symbolic parameters"  );
            }
            CUBEW_FREE( cnode->string_parameters->data, MEMORY_TRACING_PREFIX "Release content of symbolic parameters"  );
            CUBEW_FREE( cnode->string_parameters, MEMORY_TRACING_PREFIX "Release symbolic parameters"  );
        }
        if ( cnode->attr )
        {
            for ( i = 0; i < cnode->attr->size; i++ )
            {
                CUBEW_FREE( ( cnode->attr->data[ i ] )->key, MEMORY_TRACING_PREFIX "Release key of attributes"   );
                CUBEW_FREE( ( cnode->attr->data[ i ] )->value, MEMORY_TRACING_PREFIX "Release value of attributes"  );
                CUBEW_FREE( cnode->attr->data[ i ], MEMORY_TRACING_PREFIX "Release pair of attributes" );
            }
            CUBEW_FREE( cnode->attr->data, MEMORY_TRACING_PREFIX "Release content of attributes"  );
            CUBEW_FREE( cnode->attr, MEMORY_TRACING_PREFIX "Release attributes" );
        }
        CUBEW_FREE( cnode, MEMORY_TRACING_PREFIX "Release cnode" );
    }
}



/**
 * Returns a i-th child of the given cnode.
 */
cube_cnode*
cube_cnode_get_child( cube_cnode* cnode,
                      uint32_t    i )
{
    if ( i < 0 || i >= cnode->child->size )
    {
        UTILS_WARNING( "cube_cnode_get_child: out of range\n" );
    }
    return cnode->child->data[ i ];
}


/**
 *  Returns a parent of the cnode.
 */
cube_cnode*
cube_cnode_get_parent( cube_cnode* cnode )
{
    return cnode->parent;
}


/**
 *  Returns a line of the source code for current cnode
 */
int
cube_cnode_get_line( cube_cnode* cnode )
{
    return ( cnode->line <= 0 ) ? -1 : cnode->line;
}

/**
 *  Returns a modus of the current cnode.
 */
char*
cube_cnode_get_mod( cube_cnode* cnode )
{
    return cnode->mod;
}

/**
 *  Returns a calee ot the current cnode.
 */
cube_region*
cube_cnode_get_callee( cube_cnode* cnode )
{
    return cnode->callee;
}

/**
 *  Returns a caller of the current cnode.
 */
cube_region*
cube_cnode_get_caller( cube_cnode* cnode )
{
    if ( cube_cnode_get_parent( ( cnode ) ) == NULL )
    {
        return NULL;
    }
    return cube_cnode_get_callee( cube_cnode_get_parent( ( cnode ) ) );
}

/**
 *  Returns a number of the children of the current cnode.
 */
uint32_t
cube_cnode_num_children( cube_cnode* cnode )
{
    return cnode->child->size;
}


/**
 *  Sets an id to the cnode.
 */
void
cube_cnode_set_id( cube_cnode* cnode,
                   int         new_id )
{
    cnode->id = new_id;
}


/**
 * Returns an id of the cnode.
 */
int
cube_cnode_get_id( cube_cnode* cnode )
{
    return cnode->id;
}

/**
 * Returns the level
 */
int
cube_cnode_get_level( cube_cnode* cnode )
{
    if ( cube_cnode_get_parent( ( cnode ) ) == NULL )
    {
        return 0;
    }
    return cube_cnode_get_level( cube_cnode_get_parent( ( cnode ) ) ) + 1;
}


/**
 * Adds an attribute  "m" into cube "this"
 */
void
cube_cnode_add_attr( cube_cnode* cnode,
                     cmap*       m )
{
    ADD_NEXT( cnode->attr, m, cmap*, MEMORY_TRACING_PREFIX "Add attribute" );
}

/**
 * Creates and add in to cube "this" the attribute "key" with a vaue "value"
 */
void
cube_cnode_def_attr( cube_cnode* cnode,
                     const char* key,
                     const char* value )
{
    char* nkey   = cubew_strdup( key );
    char* nvalue = cubew_strdup( value );
    cmap*
    XALLOC( m,
            1,
            cmap,
            MEMORY_TRACING_PREFIX "Allocate attribure"
            );

    m->key   = nkey;
    m->value = nvalue;
    cube_cnode_add_attr( cnode, m );
}



/**
 * Writes XML output for cnode in "<program>" part of the .cube file.

 */
void
cube_cnode_writeXML( cube_cnode*            cnode,
                     cube_meta_data_writer* meta_data_writer )
{
    char* _mod = ( char* )cube_services_escape_to_xml__( cube_cnode_get_mod( ( cnode ) ) );



    uint32_t i = 0;
    cube_write_meta_data__( meta_data_writer, "<cnode id=\"%d\" ", cube_cnode_get_id( ( cnode ) ) );
    if ( cube_cnode_get_line( ( cnode ) ) != -1 )
    {
        cube_write_meta_data__( meta_data_writer, "line=\"%d\" ", cube_cnode_get_line( ( cnode ) ) );
    }
    if ( strcmp( cube_cnode_get_mod( ( cnode ) ), "" ) != 0 )
    {
        cube_write_meta_data__( meta_data_writer, "mod=\"%s\" ", _mod ? _mod : cube_cnode_get_mod( ( cnode ) ) );
    }
    cube_write_meta_data__( meta_data_writer, "calleeId=\"%d\">\n", cube_region_get_id( cube_cnode_get_callee( ( cnode ) ) ) );
    /*  write parameters */
    if ( cnode->num_parameters != NULL )
    {
        for ( i = 0; i < cnode->num_parameters->size; i++ )
        {
            char* _key = ( char* )cube_services_escape_to_xml__( cnode->num_parameters->data[ i ]->key );
            cube_write_meta_data__( meta_data_writer, "<parameter partype=\"numeric\" parkey=\"%s\" parvalue=\"%g\" />\n", _key, cnode->num_parameters->data[ i ]->value );
            CUBEW_FREE( _key, MEMORY_TRACING_PREFIX "Release numeric _key" );
        }
    }
    if ( cnode->string_parameters != NULL )
    {
        for ( i = 0; i < cnode->string_parameters->size; i++ )
        {
            char* _key   = ( char* )cube_services_escape_to_xml__( cnode->string_parameters->data[ i ]->key );
            char* _value = ( char* )cube_services_escape_to_xml__( cnode->string_parameters->data[ i ]->value );

            cube_write_meta_data__( meta_data_writer, "<parameter partype=\"string\" parkey=\"%s\" parvalue=\"%s\" />\n", _key, _value );
            CUBEW_FREE( _key, MEMORY_TRACING_PREFIX "Release symbolic _key" );
            CUBEW_FREE( _value, MEMORY_TRACING_PREFIX "Release symbolic _value" );
        }
    }

    cube_services_write_attributes__( meta_data_writer,  cnode->attr );

    for ( i = 0; i < cube_cnode_num_children( ( cnode ) ); i++ )
    {
        cube_cnode* child = cube_cnode_get_child( cnode, i );
        cube_cnode_writeXML( child, meta_data_writer );
    }
    cube_write_meta_data__( meta_data_writer, "</cnode>\n" );

    CUBEW_FREE( _mod, MEMORY_TRACING_PREFIX "Release mod" );
}

/**
 * Compares on equality two cnodes.
 */
int
cube_cnode_equal( cube_cnode* a,
                  cube_cnode* b )
{
    const char* _a = cube_cnode_get_mod( a );
    const char* _b = cube_cnode_get_mod( b );

    if ( strcmp( _a, _b  ) == 0 )
    {
        cube_region* _reg_a = cube_cnode_get_callee( a );
        cube_region* _reg_b = cube_cnode_get_callee( b );


        if ( cube_region_equal( _reg_a, _reg_b ) == 1 )
        {
            int _line_a = cube_cnode_get_line( a );
            int _line_b = cube_cnode_get_line( b );
            if ( _line_a  == _line_b )
            {
                return 1;
            }
        }
    }
    return 0;
}
