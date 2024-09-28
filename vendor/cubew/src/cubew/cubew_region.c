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
 * \file cubew_region.c
   \brief Defines types and functions to deal with regions in source code of running application.
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "cubew_region.h"
#include "cubew_memory.h"
#include "cubew_cnode.h"
#include "cubew_vector.h"
#include "cubew_services.h"
#include "cubew_meta_data_writer.h"
#include "cubew_types.h"

#define MEMORY_TRACING_PREFIX "[REGION]"


/**
 * Creating of callee node to( region )region.
 *
 */
static
void
cube_region_construct_cnode( cube_region* region )
{
    XALLOC( region->cnode, 1, cube_rarray, MEMORY_TRACING_PREFIX "Allocate vector of caller of a region"  );
    region->cnode->size     = 0;
    region->cnode->capacity = 0;
}


/**
 * Allocationg memory for a region.
 *
 */
cube_region*
cube_region_create( cube_region* region )
{
    if ( region == NULL )
    {
        ALLOC( region, 1, cube_region, MEMORY_TRACING_PREFIX "Allocate region"  );
    }
    if ( region != NULL )
    {
        cube_region_construct_cnode( region );
    }
    region->attr = NULL;
    /* construct attrs array */
    XALLOC( region->attr, 1, att_array, MEMORY_TRACING_PREFIX "Allocate region attributes"  );
    region->attr->size     = 0;
    region->attr->capacity = 0;

    return region;
}

/**
 * Filling a region with the information.
 *
 */
void
cube_region_init( cube_region* region,
                  const char*  name,
                  const char*  mangled_name,
                  const char*  paradigm,
                  const char*  role,
                  int          begln,
                  int          endln,
                  const char*  url,
                  const char*  descr,
                  const char*  mod )
{
    region->name         = cubew_strdup( name );
    region->mangled_name = cubew_strdup( mangled_name );
    region->paradigm     = cubew_strdup( paradigm );
    region->role         = cubew_strdup( role );
    region->begln        = begln;
    region->endln        = endln;
    region->url          = cubew_strdup( url );
    region->descr        = cubew_strdup( descr );
    region->mod          = cubew_strdup( mod );
}


/**
 * Addition of the callee node to( region )region.
 *
 */
void
cube_region_add_cnode( cube_region* region,
                       cube_cnode*  cnode )
{
    uint32_t i    = 0;
    uint32_t size = cube_region_num_children( region );
    for ( i = 0; i < size; i++ )
    {
        if ( cube_cnode_equal( cnode, region->cnode->data[ i ] ) == 1 )
        {
            return;
        }
    }
    ADD_NEXT( region->cnode, cnode, cube_cnode*, MEMORY_TRACING_PREFIX "Add caller of the region"  );
}

/**
 * Releases memory for a region.
 *
 */
void
cube_region_free( cube_region* region )
{
    if ( region != NULL )
    {
        CUBEW_FREE( region->name, MEMORY_TRACING_PREFIX "Release name of a region"  );
        CUBEW_FREE( region->mangled_name, MEMORY_TRACING_PREFIX "Release mangled name of a region" );
        CUBEW_FREE( region->paradigm, MEMORY_TRACING_PREFIX "Release paradigm of a region"  );
        CUBEW_FREE( region->role, MEMORY_TRACING_PREFIX "Release role of a region"  );
        CUBEW_FREE( region->url, MEMORY_TRACING_PREFIX "Release url of a region"  );
        CUBEW_FREE( region->descr, MEMORY_TRACING_PREFIX "Release description of a region"  );
        CUBEW_FREE( region->mod, MEMORY_TRACING_PREFIX "Release module of a region"  );

        CUBEW_FREE( region->cnode->data, MEMORY_TRACING_PREFIX "Release vector of caller of a region" );
        CUBEW_FREE( region->cnode, MEMORY_TRACING_PREFIX "Release callers of a region" );

        if ( region->attr )
        {
            uint32_t i = 0;
            for ( i = 0; i < region->attr->size; i++ )
            {
                CUBEW_FREE( ( region->attr->data[ i ] )->key, MEMORY_TRACING_PREFIX "Release key of a region attribute"  );
                CUBEW_FREE( ( region->attr->data[ i ] )->value, MEMORY_TRACING_PREFIX "Release value of a region attribute" );
                CUBEW_FREE( region->attr->data[ i ], MEMORY_TRACING_PREFIX "Release region attribute"  );
            }
            CUBEW_FREE( region->attr->data, MEMORY_TRACING_PREFIX "Release vector of region attributes" );
        }
        CUBEW_FREE( region->attr, MEMORY_TRACING_PREFIX "Release region attributes"  );
    }
    CUBEW_FREE( region, MEMORY_TRACING_PREFIX "Release region"  );
}



/**
 * Adds an attribute  "m" into cube "this"
 */
void
cube_region_add_attr( cube_region* region,
                      cmap*        m )
{
    ADD_NEXT( region->attr, m, cmap*, MEMORY_TRACING_PREFIX "Add a region attrubute" );
}

/**
 * Creates and add in to cube "region" the attribute "key" with a vaue "value"
 */
void
cube_region_def_attr( cube_region* region,
                      const char*  key,
                      const char*  value )
{
    char* nkey   = cubew_strdup( key );
    char* nvalue = cubew_strdup( value );
    cmap*
    XALLOC( m,
            1,
            cmap,
            MEMORY_TRACING_PREFIX "Allocate region attribute"   );

    m->key   = nkey;
    m->value = nvalue;
    cube_region_add_attr( region, m );
}


char*
cube_region_get_name( cube_region* region )
{
    return region->name;
}
char*
cube_region_get_mangled_name( cube_region* region )
{
    return region->mangled_name;
}

char*
cube_region_get_paradigm( cube_region* region )
{
    return region->paradigm;
}

char*
cube_region_get_role( cube_region* region )
{
    return region->role;
}

char*
cube_region_get_url( cube_region* region )
{
    return region->url;
}

char*
cube_region_get_descr( cube_region* region )
{
    return region->descr;
}

char*
cube_region_get_mod( cube_region* region )
{
    return region->mod;
}

int
cube_region_get_begn_ln( cube_region* region )
{
    return ( region->begln <= 0 ) ? -1 : region->begln;
}

int
cube_region_get_end_ln( cube_region* region )
{
    return ( region->endln <= 0 ) ? -1 : region->endln;
}

uint32_t
cube_region_num_children( cube_region* region )
{
    return region->cnode->size;
}

/**
 * Writes XML output for region in to .cube file.
 *
 * A special algorithm for saving a name of the region implemented.
 */
void
cube_region_writeXML( cube_region*           region,
                      cube_meta_data_writer* meta_data_writer )
{
    char* _mod      = cube_services_escape_to_xml__( cube_region_get_mod( ( region ) ) );
    char* _name     = cube_services_escape_to_xml__( cube_region_get_name( ( region ) ) );
    char* _m_name   = cube_services_escape_to_xml__( cube_region_get_mangled_name( ( region ) ) );
    char* _paradigm = cube_services_escape_to_xml__( cube_region_get_paradigm( ( region ) ) );
    char* _role     = cube_services_escape_to_xml__( cube_region_get_role( ( region ) ) );
    char* _url      = cube_services_escape_to_xml__( cube_region_get_url( ( region ) ) );
    char* _descr    = cube_services_escape_to_xml__( cube_region_get_descr( ( region ) ) );

    int _id       =  cube_region_get_id( ( region ) );
    int _begin_ln = cube_region_get_begn_ln( ( region ) );
    int _end_ln   = cube_region_get_end_ln( ( region ) );
    cube_write_meta_data__( meta_data_writer, "<region id=\"%d\" mod=\"%s\" begin=\"%d\" end=\"%d\">\n",
                            _id, _mod ? _mod : cube_region_get_mod( ( region ) ),
                            _begin_ln, _end_ln  );


    cube_write_meta_data__( meta_data_writer, "<name>%s</name>\n",  _name ? _name : cube_region_get_name( ( region ) ) );
    if ( _name ||  cube_region_get_mangled_name( ( region ) ) )
    {
        cube_write_meta_data__( meta_data_writer, "<mangled_name>%s</mangled_name>\n",  _m_name ? _m_name : cube_region_get_mangled_name( ( region ) ) );
    }
    cube_write_meta_data__( meta_data_writer, "<paradigm>%s</paradigm>\n",  _paradigm ? _paradigm : cube_region_get_paradigm( ( region ) ) );
    cube_write_meta_data__( meta_data_writer, "<role>%s</role>\n",  _role ? _role : cube_region_get_role( ( region ) ) );
    cube_write_meta_data__( meta_data_writer, "<url>%s</url>\n",  _url ? _url : cube_region_get_url( ( region ) ) );
    cube_write_meta_data__( meta_data_writer, "<descr>%s</descr>\n", _descr ? _descr : cube_region_get_descr( ( region ) ) );
    cube_services_write_attributes__( meta_data_writer,  region->attr );
    cube_write_meta_data__( meta_data_writer, "</region>\n" );


    CUBEW_FREE( _mod, MEMORY_TRACING_PREFIX "Release _mod" );
    CUBEW_FREE( _name, MEMORY_TRACING_PREFIX "Release _name" );
    CUBEW_FREE( _m_name, MEMORY_TRACING_PREFIX "Release _m_name" );
    CUBEW_FREE( _paradigm, MEMORY_TRACING_PREFIX "Release _paradigm" );
    CUBEW_FREE( _role, MEMORY_TRACING_PREFIX "Release _role" );
    CUBEW_FREE( _url, MEMORY_TRACING_PREFIX "Release _url" );
    CUBEW_FREE( _descr, MEMORY_TRACING_PREFIX "Release _descr" );
}

/**
 * Compares equaliy of two regions
 */

int
cube_region_equal( cube_region* a,
                   cube_region* b )
{
    const char* _a = cube_region_get_name( a );
    const char* _b = cube_region_get_name( b );
    if ( strcmp( _a, _b ) == 0 )
    {
        const char* _mod_a = cube_region_get_mod( a );
        const char* _mod_b = cube_region_get_mod( b );
        if ( strcmp( _mod_a, _mod_b ) == 0 )
        {
            return 1;
        }
    }
    return 0;
}

void
cube_region_set_id( cube_region* region,
                    int          new_id )
{
    region->id = new_id;
}

int
cube_region_get_id( cube_region* region )
{
    return region->id;
}
