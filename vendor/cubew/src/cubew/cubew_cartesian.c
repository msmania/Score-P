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
 * \file cubew_cartesian.c
   \brief Defines a types and functions to deal with cartesian topology.
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "cubew_cartesian.h"
#include "cubew_system_tree_node.h"
#include "cubew_location_group.h"
#include "cubew_location.h"
#include "cubew_vector.h"
#include "cubew_services.h"
#include "cubew_meta_data_writer.h"
#include "cubew_memory.h"
#include "UTILS_Error.h"

#define MEMORY_TRACING_PREFIX "[CART]"

/* CARTESIAN TYPES*/
/**
 * Maps a thread and its three-dimenasional coordinates.
 */
typedef struct map_thrd
{
    cube_thread* key;
    long int*    value;   /* currently any number of dimensions! */
} map_thrd;



/**
 * Allocates memory for the array with definition of coordnates for every thread.
 */
cube_cartesian*
cube_cart_create( cube_cartesian* cart )
{
    if ( cart == NULL )
    {
        ALLOC( cart, 1, cube_cartesian, MEMORY_TRACING_PREFIX "Allocate topology" );
    }
    cart->name = NULL;
    return cart;
}

/**
 * Allocates memory for the arrays for dimensions and set the values for them.
 */
int
cube_cart_init( cube_cartesian* cart,
                long int        ndims,
                long int*       dim,
                int*            period )
{
    int i    = 0;
    int locs = 1;
    cart->ndims = ndims;
    ALLOC( cart->dim, ndims, long int, MEMORY_TRACING_PREFIX "Allocate dimensions" );
    ALLOC( cart->period, ndims, int, MEMORY_TRACING_PREFIX "Allocate period" );
    ALLOC( cart->namedims, ndims, char*, MEMORY_TRACING_PREFIX "Allocate dimension names"  );
    if ( ( cart->dim == NULL ) || ( cart->period == NULL ) )
    {
        return 1;
    }
    for ( i = 0; i < ndims; i++ )
    {
        locs             *= dim[ i ];
        cart->dim[ i ]    = dim[ i ];
        cart->period[ i ] = period[ i ];
    }
    ALLOC( cart->thrd2coord, locs, map_thrd, MEMORY_TRACING_PREFIX "Allocate location->coordinate mapping" );
    for ( i = 0; i < locs; i++ )
    {
        ALLOC( cart->thrd2coord[ i ].value, ndims, long int, MEMORY_TRACING_PREFIX "Add coordinate" );
    }
    return cart->thrd2coord == NULL;
}

/**
 * Releases allocated memory
 */
void
cube_cart_free( cube_cartesian* cart )
{
    if ( cart != NULL )
    {
        unsigned int i    = 0;
        unsigned int locs = 1;
        for ( i = 0; i < cart->ndims; i++ )
        {
            locs *= cart->dim[ i ];
            CUBEW_FREE( cart->namedims[ i ], MEMORY_TRACING_PREFIX "Release dimension names" );
        }
        CUBEW_FREE( cart->dim, MEMORY_TRACING_PREFIX "Release dimensions" );
        CUBEW_FREE( cart->period, MEMORY_TRACING_PREFIX "Release period" );
        for ( i = 0; i < locs; i++ )
        {
            CUBEW_FREE( cart->thrd2coord[ i ].value, MEMORY_TRACING_PREFIX "Release coordinate" );
        }
        CUBEW_FREE( cart->thrd2coord, MEMORY_TRACING_PREFIX "Release location->coorinate mapping" );
        CUBEW_FREE( cart->name, MEMORY_TRACING_PREFIX "Release topology name" );
        CUBEW_FREE( cart->namedims, MEMORY_TRACING_PREFIX "Release names of dimensions" );
        CUBEW_FREE( cart, MEMORY_TRACING_PREFIX "Release topology" );
    }
}

/**
 * Set for given thread "thrd" in the cartesian topology "cart" coordinates "coord"
 */

void
cube_cart_def_coords( cube_cartesian* cart,
                      cube_thread*    thrd,
                      long int*       coord )
{
    unsigned int i      = 0;
    int          pos    = coord[ 0 ];
    int          factor = cart->dim[ 0 ];
    for ( i = 1; i < cart->ndims; i++ )
    {
        pos    += coord[ i ] * factor;
        factor *= cart->dim[ i ];
    }
    map_thrd* m = &cart->thrd2coord[ pos ];

    m->key = thrd;
    for ( i = 0; i < cart->ndims; i++ )
    {
        m->value[ i ] = coord[ i ];
    }
}


/**
   Sets the name of cartesian topology.
 */
void
cube_cart_set_name( cube_cartesian* cart,
                    const char*     name )
{
    CUBEW_FREE( cart->name, MEMORY_TRACING_PREFIX "Release topology name" );
    cart->name = cubew_strdup( name );
}



/**
   Sets the name of the dimensions
 */
void
cube_cart_set_namedims( cube_cartesian* cart,
                        char**          _namedims )
{
    unsigned int i = 0;
    for ( i = 0; i < cart->ndims; i++ )
    {
        CUBEW_FREE( cart->namedims[ i ], MEMORY_TRACING_PREFIX "Release name of the dimension" ); /* remove previosli set name, if was done. Prevent possible memory leaks.*/
        cart->namedims[ i ] = cubew_strdup( _namedims[ i ] );
    }
}
/**
   Sets the name of the dimension "dim"
 */
void
cube_cart_set_dim_name( cube_cartesian* cart,
                        const char*     _name,
                        unsigned        dim )
{
    if ( dim < 0 && dim >= cart->ndims )
    {
        UTILS_WARNING( "Index for dimensions %d is out of range [0: %d]. Ignore setting name in topology %s. \n", dim, cart->ndims, cart->name );
        return;                                                                                 /* do not set name if index is out of range*/
    }
    CUBEW_FREE( cart->namedims[ dim ], MEMORY_TRACING_PREFIX "Release name of the dimension" ); /* remove previosli set name, if was done. Prevent possible memory leaks.*/
    cart->namedims[ dim ] = cubew_strdup( _name );
}

/**
 * Writes topology in XML format.
 */
void
cube_cart_writeXML( cube_cartesian*        cart,
                    cube_meta_data_writer* meta_data_writer )
{
    unsigned int i    = 0;
    unsigned int j    = 0;
    unsigned int k    = 0;
    unsigned int locs = 1;
    char*        per;

    char* _name =   ( char* )cube_services_escape_to_xml__( cart->name );
    cube_write_meta_data__( meta_data_writer, "<cart " );
    if ( cart->name != NULL )
    {
        cube_write_meta_data__( meta_data_writer, "name=\"%s\" ", _name );
    }
    cube_write_meta_data__( meta_data_writer, "ndims=\"%u\">\n", cart->ndims );
    CUBEW_FREE( _name, MEMORY_TRACING_PREFIX "Release _name" );
    for ( i = 0; i < cart->ndims; i++ )
    {
        locs *= cart->dim[ i ];
        if ( cart->period[ i ] == 0 )
        {
            per = "false";
        }
        else
        {
            per = "true";
        }
        cube_write_meta_data__( meta_data_writer, "<dim " );
        if ( cart->namedims[ i ] != NULL )
        {
            char* dimName = ( char* )cube_services_escape_to_xml__( cart->namedims[ i ] );
            cube_write_meta_data__( meta_data_writer, "name=\"%s\" ", dimName );
            CUBEW_FREE( dimName, MEMORY_TRACING_PREFIX "Release dimName" );
        }
        cube_write_meta_data__( meta_data_writer, "size=\"%ld\" periodic=\"%s\"/>\n", cart->dim[ i ], per );
    }

    for ( j = 0; j < locs; j++ )
    {
        map_thrd*      m = &cart->thrd2coord[ j ];
        cube_location* t = m->key;
        if ( t )
        {
            cube_write_meta_data__( meta_data_writer, "<coord locId=\"%d\">", cube_thread_get_id( t ) );
            for ( k = 0; k < cart->ndims; k++ )
            {
                if ( k != 0 )
                {
                    cube_write_meta_data__( meta_data_writer, " " );
                }
                cube_write_meta_data__( meta_data_writer, "%ld", m->value[ k ] );
            }
            cube_write_meta_data__( meta_data_writer, "</coord>\n" );
        }
    }
    cube_write_meta_data__( meta_data_writer, "</cart>\n" );
}
