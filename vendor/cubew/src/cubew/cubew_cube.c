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
 *
 * \file cubew_cube.c
 * \brief Contains a definition of functions and types related to "cube".
 *
 ************************************************/
#include "config.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "cubew_cube.h"
#include "cubew_vector.h"
#include "cubew_memory.h"
#include "cubew_report_layouts.h"
#include "cubew_services.h"
#include "cubew_types.h"
#include "cubew_region.h"
#include "cubew_cartesian.h"
#include "cubew_metric.h"
#include "cubew_cnode.h"
#include "cubew_system_tree_node.h"
#include "cubew_location_group.h"
#include "cubew_location.h"
#include "cubew_meta_data_writer.h"
#include "cubew_system_tree_writer.h"

#include <sys/stat.h>

#include "UTILS_Error.h"

#define MEMORY_TRACING_PREFIX "[CUBE]"

int         cubew_trace = 0;
enum bool_t cubew_compressed;
/**
 * Creates and returns a data strucure cube_t*;
 */

cube_t*
cube_create( char*               cube_name,
             enum CubeFlavours_t cv,
             enum bool_t         compressed )
{
    if ( cubew_initialized() == 0 )
    {
        cubew_init_allocs( NULL, NULL, NULL );
    }
    /* override any parameters given by user about compression: only configure --with-compression taken into account */
    cubew_compressed = CUBE_FALSE;
#if defined( BACKEND_CUBE_COMPRESSED ) || defined( FRONTEND_CUBE_COMPRESSED )
    char* env_compressed = getenv( "CUBEW_ZLIB_COMPRESSION" );
    if ( ( env_compressed != NULL ) && ( ( strcmp( env_compressed, "true" ) == 0 ) || ( strcmp( env_compressed, "yes" ) == 0 ) ) )
    {
        cubew_compressed = CUBE_TRUE;
    }
#endif
    compressed = cubew_compressed;

    cube_t* cube = NULL;
    cubew_trace = ( getenv( "CUBEW_TRACE" ) != NULL );
    if ( cubew_trace )
    {
        UTILS_WARNING( "CUBEW_TRACE=%d\n", cubew_trace );
    }
    /* allocate memory for cube */
    ALLOC(  cube, 1, cube_t, MEMORY_TRACING_PREFIX "Allocate cube_t" );
    if (  cube == NULL )
    {
        return NULL;
    }
    /* construct dynamic arrays */
    cube_construct_arrays( cube );
    cube->first_call         = CUBE_TRUE;
    cube->locked_for_writing = CUBE_FALSE;
    cube->cube_flavour       = cv;
    cube->metrics_title      = NULL;
    cube->calltree_title     = NULL;
    cube->systemtree_title   = NULL;
    cube->system_tree_writer = cube_system_tree_writer_create();

    cube->sev_flag            = 1;
    cube->compressed          = compressed;
    cube->cubename            = cubew_strdup( cube_name );
    cube->size_of_anchor_file = -1;

    cube->layout  = cube_writing_start(  cube->cubename,  cube->cube_flavour );
    cube->version = CUBE_ANCHOR_BASIC_VERSION;  /* set anchor version to basic syntax version*/
    return cube;
}

/**
 * Creates arrays for severities.
 */

void
cube_sev_init( cube_t* cube )
{
    cube->attr    = 0;
    cube->mirr_ar = 0;

    uint32_t i = 0;
    uint32_t j = 0;

    /* Only regions defined => flat profile => create top-lecel cnodes */
    if (  cube->cnd_ar->size == 0 &&  cube->reg_ar->size > 0 )
    {
        for ( i = 0; i <  cube->reg_ar->size; i++ )
        {
            cube_def_cnode(  cube, ( cube_region* )cube->reg_ar->data[ i ], NULL );
        }
    }

    XALLOC(  cube->sev,  cube->met_ar->size, double**, MEMORY_TRACING_PREFIX "Allocate vector of severities per metric" );
    for ( i = 0; i <  cube->met_ar->size; i++ )
    {
        XALLOC(  cube->sev[ i ],  cube->cnd_ar->size, double*, MEMORY_TRACING_PREFIX "Allocate vector of severities per metric per cnode" );
    }

    XALLOC(  cube->exist,  cube->met_ar->size, int*, MEMORY_TRACING_PREFIX "Allocate vector of metric existence flags"  );
    for ( i = 0; i <  cube->met_ar->size; i++ )
    {
        XALLOC(  cube->exist[ i ],  cube->cnd_ar->size, int, MEMORY_TRACING_PREFIX "Allocate vector of cnodes per metric"  );
    }
    XALLOC(  cube->cn_exist,  cube->met_ar->size, int**, MEMORY_TRACING_PREFIX "Allocate vector of cnode existence flags"  );

    for ( i = 0; i <  cube->met_ar->size; i++ )
    {
        XALLOC(  cube->cn_exist[ i ],  cube->cnd_ar->size, int*, MEMORY_TRACING_PREFIX "Allocate bitvector of existing severities"  );
        for ( j = 0; j <  cube->cnd_ar->size; j++ )
        {
            XALLOC(  cube->cn_exist[ i ][ j ],  cube->locs_ar->size, int, MEMORY_TRACING_PREFIX "Allocate bitvector of "  );
        }
    }
//   cube_assign_ids(this);
}


/**
 * Destroys all data in cube and removes it from memory.;
 */
void
cube_free( cube_t* cube )
{
    uint32_t i = 0;
    uint32_t j = 0;
    if ( !cube )
    {
        return;
    }
    cube_write_finish( cube );
    CUBEW_FREE(  cube->cubename, MEMORY_TRACING_PREFIX "Release name of cube file"  );

    /* CUBEW_FREE severities */
    if (  cube->sev )
    {
        for ( i = 0; i <  cube->met_ar->size; i++ )
        {
            for ( j = 0; j <  cube->cnd_ar->size; j++ )
            {
                CUBEW_FREE(  cube->sev[ i ][ j ], MEMORY_TRACING_PREFIX "Release vector of  severities"  );
            }
            CUBEW_FREE(  cube->sev[ i ], MEMORY_TRACING_PREFIX "Release vector of vector of severities"  );
        }
        CUBEW_FREE(  cube->sev, MEMORY_TRACING_PREFIX "Release all severities" );
    }

    if (  cube->exist )
    {
        for ( i = 0; i <  cube->met_ar->size; i++ )
        {
            CUBEW_FREE(  cube->exist[ i ], MEMORY_TRACING_PREFIX "Release vector of bitmasks"  );
        }
        CUBEW_FREE(  cube->exist, MEMORY_TRACING_PREFIX "Release bitmasks" );
    }

    if (  cube->cn_exist )
    {
        for ( i = 0; i <  cube->met_ar->size; i++ )
        {
            for ( j = 0; j <  cube->cnd_ar->size; j++ )
            {
                CUBEW_FREE(  cube->cn_exist[ i ][ j ], MEMORY_TRACING_PREFIX "Release cn_exist[i][j]" );
            }
            CUBEW_FREE(  cube->cn_exist[ i ], MEMORY_TRACING_PREFIX "Release cn_exist[i]"  );
        }
        CUBEW_FREE(  cube->cn_exist, MEMORY_TRACING_PREFIX "Release cn_exist"  );
    }
    /* CUBEW_FREE metrics */
    if (  cube->met_ar )
    {
        for ( i = 0; i <  cube->met_ar->size; i++ )
        {
            cube_metric_free(  cube->met_ar->data[ i ] );
        }
        CUBEW_FREE(  cube->met_ar->data, MEMORY_TRACING_PREFIX "Release vector of  metrics"  );
    }
    CUBEW_FREE(  cube->met_ar, MEMORY_TRACING_PREFIX "Release metrics"  );

    if (  cube->rmet_ar )
    {
        CUBEW_FREE(  cube->rmet_ar->data, MEMORY_TRACING_PREFIX "Release vector of  root metrics"  );
    }
    CUBEW_FREE(  cube->rmet_ar, MEMORY_TRACING_PREFIX "Release root metrics" );

    /* CUBEW_FREE regions */
    if (  cube->reg_ar )
    {
        for ( i = 0; i <  cube->reg_ar->size; i++ )
        {
            cube_region_free(  cube->reg_ar->data[ i ] );
        }
        CUBEW_FREE(  cube->reg_ar->data, MEMORY_TRACING_PREFIX "Release vector of regions"  );
    }
    CUBEW_FREE(  cube->reg_ar, MEMORY_TRACING_PREFIX "Release regions"  );

    /* CUBEW_FREE cnodes */
    if (  cube->cnd_ar )
    {
        for ( i = 0; i <  cube->cnd_ar->size; i++ )
        {
            cube_cnode_free(  cube->cnd_ar->data[ i ] );
        }
        CUBEW_FREE(  cube->cnd_ar->data, MEMORY_TRACING_PREFIX "Release vector of cnodes"  );
    }
    CUBEW_FREE(  cube->cnd_ar, MEMORY_TRACING_PREFIX "Release cnodes"  );
    if (  cube->rcnd_ar )
    {
        CUBEW_FREE(  cube->rcnd_ar->data, MEMORY_TRACING_PREFIX "Release vector of root cnodes"  );
    }
    CUBEW_FREE(  cube->rcnd_ar, MEMORY_TRACING_PREFIX "Release cnodes"  );


    /* CUBEW_FREE system tree nodes */
    if (  cube->stn_ar )
    {
        for ( i = 0; i <  cube->stn_ar->size; i++ )
        {
            cube_system_tree_node_free(  cube->stn_ar->data[ i ] );
        }
        CUBEW_FREE(  cube->stn_ar->data, MEMORY_TRACING_PREFIX "Release vector of system tree nodes"  );
    }
    CUBEW_FREE(  cube->stn_ar, MEMORY_TRACING_PREFIX "Release system tree nodes"  );

    if (  cube->root_stn_ar )
    {
        CUBEW_FREE(  cube->root_stn_ar->data, MEMORY_TRACING_PREFIX "Release vector of root system tree nodes"  );
    }
    CUBEW_FREE(  cube->root_stn_ar, MEMORY_TRACING_PREFIX "Release system tree nodes"  );

    /* CUBEW_FREE location group */
    if (  cube->lg_ar )
    {
        for ( i = 0; i <  cube->lg_ar->size; i++ )
        {
            cube_location_group_free(  cube->lg_ar->data[ i ] );
        }
        CUBEW_FREE(  cube->lg_ar->data, MEMORY_TRACING_PREFIX "Release vector of location groups"  );
    }
    CUBEW_FREE(  cube->lg_ar, MEMORY_TRACING_PREFIX "Release location groups"  );

    /* CUBEW_FREE location  */
    if (  cube->locs_ar )
    {
        for ( i = 0; i <  cube->locs_ar->size; i++ )
        {
            cube_location_free(  cube->locs_ar->data[ i ] );
        }
        CUBEW_FREE(  cube->locs_ar->data, MEMORY_TRACING_PREFIX "Release vector of locations"  );
    }
    CUBEW_FREE(  cube->locs_ar, MEMORY_TRACING_PREFIX "Release locations"  );
    /* CUBEW_FREE attrs */
    if (  cube->attr )
    {
        for ( i = 0; i <  cube->attr->size; i++ )
        {
            CUBEW_FREE( (  cube->attr->data[ i ] )->key, MEMORY_TRACING_PREFIX "Release key of cube attributes"  );
            CUBEW_FREE( (  cube->attr->data[ i ] )->value, MEMORY_TRACING_PREFIX "Release value of cube attributes"  );
            CUBEW_FREE(  cube->attr->data[ i ], MEMORY_TRACING_PREFIX "Release cube attribute"  );
        }
        CUBEW_FREE(  cube->attr->data, MEMORY_TRACING_PREFIX "Release vector of cube attributes"  );
    }
    CUBEW_FREE(  cube->attr, MEMORY_TRACING_PREFIX "Release cube attribures"  );
    /* CUBEW_FREE mirrors */
    if (  cube->mirr_ar )
    {
        for ( i = 0; i <  cube->mirr_ar->size; i++ )
        {
            if (  cube->mirr_ar->data[ i ] != 0 )
            {
                CUBEW_FREE(  cube->mirr_ar->data[ i ], MEMORY_TRACING_PREFIX "Release cube mirror"  );
            }
        }
        CUBEW_FREE(  cube->mirr_ar->data, MEMORY_TRACING_PREFIX "Release vector of cube mirrors"  );
    }
    CUBEW_FREE(  cube->mirr_ar, MEMORY_TRACING_PREFIX "Release cube mirrors"  );
    /* CUBEW_FREE cartesians */
    for ( i = 0; i <  cube->cart_ar->size; i++ )
    {
        cube_cart_free(  cube->cart_ar->data[ i ] );
    }
    if (  cube->cart_ar )
    {
        CUBEW_FREE(  cube->cart_ar->data, MEMORY_TRACING_PREFIX "Release vector of topologies"  );
    }
    CUBEW_FREE(  cube->cart_ar, MEMORY_TRACING_PREFIX "Release topologies"  );

    CUBEW_FREE(  cube->metrics_title, MEMORY_TRACING_PREFIX "Release metrics title"  );
    CUBEW_FREE(  cube->calltree_title, MEMORY_TRACING_PREFIX "Release calltree title"  );
    CUBEW_FREE(  cube->systemtree_title, MEMORY_TRACING_PREFIX "Release system tree title"  );

    cube_system_tree_writer_free(  cube->system_tree_writer );

    /* lastly, delete the cube object */

    cube->layout =  cube_writing_end(  cube->layout );
    CUBEW_FREE(  cube, MEMORY_TRACING_PREFIX "Release cube"  );
    cubew_report_allocs();
}


/**
 * Creates  empty dimensional arrays in the cube.
 */
void
cube_construct_arrays( cube_t* cube )
{
    /* construct metric array */
    XALLOC(  cube->met_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate  metrics"  );
    cube->met_ar->size     = 0;
    cube->met_ar->capacity = 0;

    /* construct root metric array */
    XALLOC(  cube->rmet_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate root metrics" );
    cube->rmet_ar->size     = 0;
    cube->rmet_ar->capacity = 0;

    /* construct region array */
    XALLOC(  cube->reg_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate regions" );
    cube->reg_ar->size     = 0;
    cube->reg_ar->capacity = 0;

    /* construct cnode array */
    XALLOC(  cube->cnd_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate  cnodes" );
    cube->cnd_ar->size     = 0;
    cube->cnd_ar->capacity = 0;

    /* construct root cnode array */
    XALLOC(  cube->rcnd_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate root cnodes" );
    cube->rcnd_ar->size     = 0;
    cube->rcnd_ar->capacity = 0;

    /* construct system tree node array */
    XALLOC(  cube->stn_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate  system tree nodes" );
    cube->stn_ar->size     = 0;
    cube->stn_ar->capacity = 0;
    /* construct root system tree node array */
    XALLOC(  cube->root_stn_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate root system tree nodes" );
    cube->root_stn_ar->size     = 0;
    cube->root_stn_ar->capacity = 0;

    /* construct location group array */
    XALLOC(  cube->lg_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate  location groups" );
    cube->lg_ar->size     = 0;
    cube->lg_ar->capacity = 0;

    /* construct location array */
    XALLOC(  cube->locs_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate  locations" );
    cube->locs_ar->size     = 0;
    cube->locs_ar->capacity = 0;

    /* construct cartesian array */
    XALLOC(  cube->cart_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate  topologies" );
    cube->cart_ar->size     = 0;
    cube->cart_ar->capacity = 0;

    /* construct mirror_url array */
    XALLOC(  cube->mirr_ar, 1, dyn_array, MEMORY_TRACING_PREFIX "Allocate  mirrors" );
    cube->mirr_ar->size     = 0;
    cube->mirr_ar->capacity = 0;

    /* construct attrs array */
    XALLOC(  cube->attr, 1, att_array, MEMORY_TRACING_PREFIX "Allocate attributes" );
    cube->attr->size     = 0;
    cube->attr->capacity = 0;
}

/**
 * Allocates memory for "num" metrics (and rmetrics) in the cube "this"
 * Returns 0 - succes, non 0 - failed (not enough memory or whatever)
 */
int
cube_reserve_metrics( cube_t*  cube,
                      unsigned num )
{
    cube->met_ar->capacity = num;
    ALLOC(  cube->met_ar->data,  cube->met_ar->capacity, void*, MEMORY_TRACING_PREFIX "Allocate vector of metrics" );
    cube->rmet_ar->capacity = num;
    ALLOC(  cube->rmet_ar->data,  cube->rmet_ar->capacity, void*, MEMORY_TRACING_PREFIX "Allocate vector of root metrics" );
    return cube->rmet_ar->data == NULL;
}

/**
 * Allocates memory for "num" regions in the cube "this"
 * Returns 0 - succes, non 0 - failed (not enough memory or whatever)
 */
int
cube_reserve_regions( cube_t*  cube,
                      unsigned num )
{
    cube->reg_ar->capacity = num;
    ALLOC(  cube->reg_ar->data,  cube->reg_ar->capacity, void*, MEMORY_TRACING_PREFIX "Allocate vector of regions" );
    return cube->reg_ar->data == NULL;
}

/**
 * Allocates memory for "num" calees in the cube "this"
 * Returns 0 - succes, non 0 - failed (not enough memory or whatever)
 */
int
cube_reserve_cnodes( cube_t*  cube,
                     unsigned num )
{
    cube->cnd_ar->capacity = num;
    ALLOC(  cube->cnd_ar->data,  cube->cnd_ar->capacity, void*, MEMORY_TRACING_PREFIX "Allocate vector of cnodes" );
    return cube->cnd_ar->data == NULL;
}



/**
 * Allocates memory for "num" elements of cartesian topology  in the cube "this"
 * Returns 0 - succes, non 0 - failed (not enough memory or whatever)
 */
int
cube_reserve_carts( cube_t*  cube,
                    unsigned num )
{
    cube->cart_ar->capacity = num;
    ALLOC(  cube->cart_ar->data,  cube->cart_ar->capacity, void*, MEMORY_TRACING_PREFIX "Allocate vector of topologies" );
    return cube->cart_ar->data == NULL;
}

/**
 * Adds a metric "met" into cube "this"
 */
void
cube_add_metric( cube_t*      cube,
                 cube_metric* met )
{
    cube_metric_set_id( met,  cube->met_ar->size );
    ADD_NEXT(  cube->met_ar, met, void*, MEMORY_TRACING_PREFIX "Add metric" );
}

/**
 * Adds a rmetric "met" into cube "this"
 */
void
cube_add_rmetric( cube_t*      cube,
                  cube_metric* met )
{
    ADD_NEXT(  cube->rmet_ar, met, void*, MEMORY_TRACING_PREFIX "Add root metric" );
}

/**
 * Adds a calee node "cnd" into cube "this"
 */
void
cube_add_cnode( cube_t*     cube,
                cube_cnode* cnd )
{
    cube_cnode_set_id( cnd,  cube->cnd_ar->size );
    ADD_NEXT(  cube->cnd_ar, cnd, void*, MEMORY_TRACING_PREFIX "Add cnode" );
}

/**
 * Adds a calee rnode "cnd" into cube "this"
 */
void
cube_add_rcnode( cube_t*     cube,
                 cube_cnode* cnd )
{
    ADD_NEXT(  cube->rcnd_ar, cnd, void*, MEMORY_TRACING_PREFIX "Add root cnode" );
}

/**
 * Adds a region of source code "reg" into cube "this"
 */
void
cube_add_region( cube_t*      cube,
                 cube_region* reg )
{
    cube_region_set_id( reg,  cube->reg_ar->size );
    ADD_NEXT(  cube->reg_ar, reg, void*, MEMORY_TRACING_PREFIX "Add region" );
}


/**
 * Adds a system tree node "stn" into cube "this"
 */
void
cube_add_system_tree_node( cube_t*                cube,
                           cube_system_tree_node* stn )
{
    cube_system_tree_node_set_id( stn,  cube->stn_ar->size );
    ADD_NEXT(  cube->stn_ar, stn, void*, MEMORY_TRACING_PREFIX "Add system tree node" );
    if ( stn->parent == NULL )
    {
        ADD_NEXT(  cube->root_stn_ar, stn, void*, MEMORY_TRACING_PREFIX "Add root system tree node" );
    }
}


/**
 * Adds a location group "group" into cube "this"
 */
void
cube_add_location_group( cube_t*              cube,
                         cube_location_group* group )
{
    cube_location_group_set_id( group,  cube->lg_ar->size );
    ADD_NEXT(  cube->lg_ar, group, void*, MEMORY_TRACING_PREFIX "Add location group" );
}


/**
 * Adds a location "loc" into cube "this"
 */
void
cube_add_location( cube_t*        cube,
                   cube_location* loc )
{
    cube_location_set_id( loc,  cube->locs_ar->size );
    ADD_NEXT(  cube->locs_ar, loc, void*, MEMORY_TRACING_PREFIX "Add location" );
}



/**
 * Adds a cartesian topology "cart" into cube "this"
 */
void
cube_add_cart( cube_t*         cube,
               cube_cartesian* cart )
{
    ADD_NEXT(  cube->cart_ar, cart, void*, MEMORY_TRACING_PREFIX "Add topology" );
}

/**
 * Adds a mirror  "mir" into cube "this"
 */
void
cube_add_mirror( cube_t*     cube,
                 const char* mir )
{
    char* nmir = cubew_strdup( mir );
    ADD_NEXT(  cube->mirr_ar, nmir, void*, MEMORY_TRACING_PREFIX "Add mirror" );
}

/**
 * Adds an attribute  "m" into cube "this"
 */
void
cube_add_attr( cube_t* cube,
               cmap*   m )
{
    ADD_NEXT(  cube->attr, m, cmap*, MEMORY_TRACING_PREFIX "Add attribute" );
}


/**
 * Creates and add in to cube "this" the attribute "key" with a vaue "value"
 */
void
cube_def_attr( cube_t*     cube,
               const char* key,
               const char* value )
{
    char* nkey   = cubew_strdup( key );
    char* nvalue = cubew_strdup( value );
    cmap*
    XALLOC( m,
            1,
            cmap,
            MEMORY_TRACING_PREFIX "Allocate cube attribute" );

    m->key   = nkey;
    m->value = nvalue;
    cube_add_attr(  cube, m );
}


/**
 * Creates and add in to cube "this" the mirror with an  url "url"
 */
void
cube_def_mirror( cube_t*     cube,
                 const char* url )
{
    cube_add_mirror(  cube, url );
}


/**
 * Creates and add in to cube "this" the metric.
 */
cube_metric*
cube_def_met( cube_t*             cube,
              const char*         disp_name,
              const char*         uniq_name,
              const char*         dtype,
              const char*         uom,
              const char*         val,
              const char*         url,
              const char*         descr,
              cube_metric*        parent,
              enum CubeMetricType metric_type )
{
    if ( parent != NULL )
    {
        if ( ( metric_type == CUBE_METRIC_POSTDERIVED  || metric_type == CUBE_METRIC_PREDERIVED_INCLUSIVE || metric_type == CUBE_METRIC_PREDERIVED_EXCLUSIVE )
             &&
             (
                 strcmp( cube_metric_get_dtype( parent ), "DOUBLE" ) != 0
                 &&
                 strcmp( cube_metric_get_dtype( parent ), "FLOAT" ) != 0
             )
             )
        {
            UTILS_WARNING( "Cannot create a derivated metric with parent metric having data type other than DOUBLE or FLOAT. Ignore call cube_def_met(...) and return NULL\n" );
            return NULL;
        }
    }
    cube_metric* met = cube_metric_create( NULL );
    cube_metric_init( met, disp_name, uniq_name, dtype, uom, val, url, descr, parent,  cube->layout, metric_type,  cube->compressed );
    if ( cube_metric_valid( met ) == CUBE_TRUE )
    {
        if ( parent == NULL )
        {
            cube_add_rmetric(  cube, met );
        }
        cube_add_metric(  cube, met );
    }
    else
    {
        UTILS_WARNING( " Metric type and data type are incompatible. Return NULL\n" );
        cube_metric_free( met );
        return NULL;
    }
    return met;
}

/*
 * Names used in CubePL processing must adhere to a naming convention. Names
 * following this convention are called 'unique' (for historical reasons).
 *
 * Use this function to create a CubePL conformant 'unique' name out of any
 * @a candidate string. The conformant string is copied to @a unique, which
 * must be char array of size >= strlen( candidate ). @a unique will get null
 * terminated. @a candidate and @a unique are of same length.
 *
 * @a candidate and @a unique must differ and not overlap. The former is
 * checked for.
 *
 * Returns true if @a candidate and @a unique differ.
 */
bool
cube_make_unique_name( const char* candidate, char* unique )
{
    UTILS_BUG_ON( unique == NULL,
                  "Argument must not be NULL but a char array of "
                  "size >= strlen(candidate)" );
    UTILS_BUG_ON( unique == candidate, "candidate and unique must differ." );

    bool   changed = CUBE_FALSE;
    size_t len     = strlen( candidate );
    for ( size_t i = 0; i < len; ++i )
    {
        /* most probable char processed first */
        if ( isalnum( candidate[ i ] ) )
        {
            unique[ i ] = candidate[ i ];
            continue;
        }
        /* least probable char processed */
        if ( ':' == candidate[ i ] || '_' == candidate[ i ] || '=' == candidate[ i ] )
        {
            unique[ i ] = candidate[ i ];
            continue;
        }
        /* char correction is least probable action */
        unique[ i ] = '_';
        changed     = CUBE_TRUE;
    }
    unique[ len ] = '\0';
    return changed;
}

/**
 * Creates and add in to cube "this" the region.
 */
cube_region*
cube_def_region( cube_t*     cube,
                 const char* name,
                 const char* mangled_name,
                 const char* paradigm,
                 const char* role,
                 long        begln,
                 long        endln,
                 const char* url,
                 const char* descr,
                 const char* mod )
{
    cube_region* reg = cube_region_create( NULL );
    cube_region_init( reg, name, mangled_name, paradigm, role, begln, endln, url, descr, mod );
    cube_add_region(  cube, reg );
    return reg;
}


/**
 * Creates and add in to cube "this" the calee cnode with available source code information.
 */
cube_cnode*
cube_def_cnode_cs( cube_t*      cube,
                   cube_region* callee,
                   const char*  mod,
                   int          line,
                   cube_cnode*  parent )
{
    if (  cube->locked_for_writing )
    {
        UTILS_WARNING( "Writing row call was already done  before. Cube is locked for writing. No changes in the dimensions are possible" );
        return NULL;
    }
    cube_cnode* cnode = cube_cnode_create( NULL );
    if ( !cnode )
    {
        return NULL;
    }
    cube_cnode_init( cnode, callee, mod, line, parent );
    if ( parent == NULL )
    {
        cube_add_rcnode(  cube, cnode );
    }
    else
    {
        cube_region* caller = cube_cnode_get_callee( parent );
        cube_region_add_cnode( caller, cnode );
    }
    cube_add_cnode(  cube, cnode );
    return cnode;
}


/**
 * Creates and add in to cube "this" the region without available source code information.
 */
cube_cnode*
cube_def_cnode( cube_t*      cube,
                cube_region* callee,
                cube_cnode*  parent )
{
    if (  cube->locked_for_writing )
    {
        UTILS_WARNING( "Writing row call was already done  before. Cube is locked for writing. No changes in the dimensions are possible" );
        return NULL;
    }
    /** if source code info not available, use empty string for mod */
    /** and -1 for line # */
    cube_cnode* cnode = cube_cnode_create( NULL );
    cube_cnode_init( cnode, callee, "", 0, parent );
    if ( parent == NULL )
    {
        cube_add_rcnode(  cube, cnode );
    }
    else
    {
        cube_region* caller = cube_cnode_get_callee( parent );
        cube_region_add_cnode( caller, cnode );
    }
    cube_add_cnode(  cube, cnode );
    return cnode;
}

/**
 * Creates and add in to cube "this" the system tree node.
 */
cube_system_tree_node*
cube_def_system_tree_node( cube_t*                cube,
                           const char*            name,
                           const char*            desc,
                           const char*            type,
                           cube_system_tree_node* parent
                           )
{
    cube_system_tree_node* stn = cube_system_tree_node_create( NULL );
    cube_system_tree_node_init( stn, name, desc, type,  parent );
    cube_add_system_tree_node(  cube, stn );
    return stn;
}


/**
 * Creates and add in to cube "this" the location group.
 */
cube_location_group*
cube_def_location_group( cube_t*                  cube,
                         const char*              name,
                         int                      rank,
                         cube_location_group_type type,
                         cube_system_tree_node*   parent
                         )
{
    cube_location_group* group = cube_location_group_create( NULL );
    cube_location_group_init( group, name, rank, type, parent );
    if ( type == CUBE_LOCATION_GROUP_TYPE_ACCELERATOR )
    {
        cube->version = CUBE_ANCHOR_GPU_VERSION;
    }
    cube_add_location_group(  cube, group );
    return group;
}


/**
 * Creates and add in to cube "this" the location group.
 */
cube_location*
cube_def_location( cube_t*              cube,
                   const char*          name,
                   int                  rank,
                   cube_location_type   type,
                   cube_location_group* parent
                   )
{
    cube_location* location = cube_location_create( NULL );
    cube_location_init( location, name, rank, type, parent );
    if ( type == CUBE_LOCATION_TYPE_ACCELERATOR_STREAM )
    {
        cube->version = CUBE_ANCHOR_GPU_VERSION;
    }
    cube_add_location(  cube, location );
    return location;
}


void
cube_system_tree_writer_initialize( cube_t*                        cb,
                                    cube_system_tree_writer_init   init,
                                    cube_system_tree_writer_step   step,
                                    cube_system_tree_writer_driver driver,
                                    cube_system_tree_writer_finish finish,
                                    void*                          user_ptr
                                    )
{
    cube_system_tree_writer_setup( cb->system_tree_writer, init, step, driver, finish, user_ptr );
}




void
cube_set_system_tree_size( cube_t*  cb,
                           uint32_t number_stn,
                           uint32_t number_location_groups,
                           uint32_t number_locations )
{
    cb->system_tree_writer->system_tree_information->number_stn             = number_stn;
    cb->system_tree_writer->system_tree_information->number_location_groups = number_location_groups;
    cb->system_tree_writer->system_tree_information->number_locations       = number_locations;
}


cube_system_tree_information*
cube_get_system_tree_information( cube_t* cb )
{
    return cb->system_tree_writer->system_tree_information;
}



/**
 * Creates and add in to cube "this" the machine.
 */
cube_machine*
cube_def_mach( cube_t*     cube,
               const char* name,
               const char* desc )
{
    return cube_def_system_tree_node(  cube, name, desc, "machine", NULL );
}


/**
 * Creates and add in to cube "this" the node of a machine.
 */
cube_node*
cube_def_node( cube_t*       cube,
               const char*   name,
               cube_machine* mach )
{
    return cube_def_system_tree_node(  cube, name, "", "node", mach );
}

/**
 * Creates and add in to cube "this" the process.
 */
cube_process*
cube_def_proc( cube_t*     cube,
               const char* name,
               int         rank,
               cube_node*  node )
{
    return cube_def_location_group(  cube, name, rank, CUBE_LOCATION_GROUP_TYPE_PROCESS, node );
}


/**
 * Creates and add in to cube "this" the thread.
 */
cube_thread*
cube_def_thrd( cube_t*       cube,
               const char*   name,
               int           rank,
               cube_process* proc )
{
    return cube_def_location(  cube, name, rank, CUBE_LOCATION_TYPE_CPU_THREAD, proc );
}

/**
 * Creates and add in to cube "this" the cartesian topology.
 * It does support only dim<=3 for cartesian topologies.
 */
cube_cartesian*
cube_def_cart( cube_t*   cube,
               long int  ndims,
               long int* dim,
               int*      period )
{
    cube_cartesian* newc;
    newc = cube_cart_create( NULL );
    if ( cube_cart_init( newc, ndims, dim, period ) != 0 )
    {
        UTILS_WARNING( "Failed to create definition for Cartesian topology\n" );
        cube_cart_free( newc );
        return NULL;
    }
    cube_add_cart(  cube, newc );
    return newc;
}



void
cube_def_coords( cube_t*         cube,
                 cube_cartesian* cart,
                 cube_thread*    thrd,
                 long int*       coord )
{
    if ( !cart )
    {
        return;
    }
    if (  cube == NULL )
    {
        UTILS_WARNING( "cube_t* reference in the call \"cube_def_coords\" is NULL.\n" );
    }
    cube_cart_def_coords( cart, thrd, coord );
}




dyn_array*
cube_get_rmet( cube_t* cube )
{
    return cube->rmet_ar;
}

dyn_array*
cube_get_met( cube_t* cube )
{
    return cube->met_ar;
}

dyn_array*
cube_get_rcnd( cube_t* cube )
{
    return cube->rcnd_ar;
}

dyn_array*
cube_get_cnd( cube_t* cube )
{
    return cube->cnd_ar;
}

dyn_array*
cube_get_mirr( cube_t* cube )
{
    return cube->mirr_ar;
}

dyn_array*
cube_get_reg( cube_t* cube )
{
    return cube->reg_ar;
}

dyn_array*
cube_get_root_stn( cube_t* cube )
{
    return cube->root_stn_ar;
}

dyn_array*
cube_get_cart( cube_t* cube )
{
    return cube->cart_ar;
}

att_array*
cube_get_attr( cube_t* cube )
{
    return cube->attr;
}



/* Set of methids for "out-of-proper-order-access*/
cube_metric*
cube_get_metric( cube_t*  cube,
                 uint32_t metricid )
{
    return ( metricid >=  cube->met_ar->size ) ? NULL :  cube->met_ar->data[ metricid ];
}
cube_cnode*
cube_get_cnode( cube_t*  cube,
                uint32_t cnodeid )
{
    return ( cnodeid >=  cube->cnd_ar->size ) ? NULL :  cube->cnd_ar->data[ cnodeid ];
}

cube_region*
cube_get_region( cube_t*  cube,
                 uint32_t regionid )
{
    return ( regionid >=  cube->reg_ar->size ) ? NULL :  cube->reg_ar->data[ regionid ];
}

/**
 * Writes a definitions-part of a .cube file.
 */
void
cube_write_def( cube_t* cube )
{
    if (  cube->cube_flavour != CUBE_MASTER )
    {
        return;
    }

    FILE* fp = cube_report_anchor_start(  cube->layout );
    if ( fp == NULL )
    {
        UTILS_FATAL( " Cannot create file for cube" );
    }
    cube_meta_data_writer* meta_data_writer = create_meta_data_writer( fp );

    dyn_array* rmet     = cube_get_rmet( cube );
    dyn_array* rcnd     = cube_get_rcnd( cube );
    dyn_array* reg      = cube_get_reg( cube );
    dyn_array* root_stn = cube_get_root_stn( cube );
    dyn_array* cart     = cube_get_cart( cube );
    dyn_array* mirr     = cube_get_mirr( cube );
    att_array* attr     = cube_get_attr( cube );

    uint32_t i = 0;
    /* xml header */

    cube_write_meta_data__( meta_data_writer, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n" );
    cube_write_meta_data__( meta_data_writer, "<cube version=\"%s\">\n",  cube->version );
    cube_write_meta_data__( meta_data_writer, "<attr key=\"" CUBEPL_VERSION_KEY "\" value=\"" CUBEPL_VERSION "\"/>\n" );
    cube_write_meta_data__( meta_data_writer, "<attr key=\"" CUBEW_VERSION_KEY "\" value=\"" CUBEW_VERSION "\"/>\n" );
    cube_write_meta_data__( meta_data_writer, "<attr key=\"" CUBE_ANCHOR_VERSION_KEY "\" value=\"%s\"/>\n",   cube->version );

    /* metadata info */
    for ( i = 0; i < attr->size; i++ )
    {
        char* key    = attr->data[ i ]->key;
        char* value  = attr->data[ i ]->value;
        char* _key   = ( char* )cube_services_escape_to_xml__( key );
        char* _value = ( char* )cube_services_escape_to_xml__( value );
        cube_write_meta_data__( meta_data_writer, "<attr key=\"%s\" value=\"%s\"/>\n",  _key ? _key : key,  _value ? _value : value );
        if ( _key )
        {
            CUBEW_FREE( _key, MEMORY_TRACING_PREFIX "Release _key of an attribure" );
        }
        if ( _value )
        {
            CUBEW_FREE( _value, MEMORY_TRACING_PREFIX "Release _value of an attribure" );
        }
    }


    /* mirrored URLs */
    cube_write_meta_data__( meta_data_writer, "<doc>\n" );
    cube_write_meta_data__( meta_data_writer, "<mirrors>\n" );
    for ( i = 0; i < mirr->size; i++ )
    {
        char* mirror  = ( char* )mirr->data[ i ];
        char* _mirror = ( char* )cube_services_escape_to_xml__( mirror );
        cube_write_meta_data__( meta_data_writer, "<murl>%s</murl>\n", _mirror ? _mirror : mirror );
        if ( _mirror )
        {
            CUBEW_FREE( _mirror, MEMORY_TRACING_PREFIX "Release _mirror" );
        }
    }
    cube_write_meta_data__( meta_data_writer, "</mirrors>\n" );
    cube_write_meta_data__( meta_data_writer, "</doc>\n" );


    /* metrics */
    cube_write_meta_data__( meta_data_writer, "<metrics" );
    char* metricstitle = ( char* )cube_services_escape_to_xml__( cube_get_metrics_title( cube ) );
    if ( metricstitle != NULL )
    {
        cube_write_meta_data__( meta_data_writer, " title=\"%s\"", metricstitle );
    }
    cube_write_meta_data__( meta_data_writer, ">\n" );
    CUBEW_FREE( metricstitle, MEMORY_TRACING_PREFIX "Release metricstitle" );
    for ( i = 0; i < rmet->size; i++ ) /* write metrics */
    {
        cube_metric* m = ( cube_metric* )rmet->data[ i ];
        cube_metric_writeXML( m, meta_data_writer );
    }
    cube_write_meta_data__( meta_data_writer, "</metrics>\n" );

    /* program */
    cube_write_meta_data__( meta_data_writer, "<program" );
    char* calltreetitle = ( char* )cube_services_escape_to_xml__( cube_get_calltree_title( cube ) );
    if ( calltreetitle != NULL )
    {
        cube_write_meta_data__( meta_data_writer, " title=\"%s\"", calltreetitle );
    }
    cube_write_meta_data__( meta_data_writer, ">\n" );
    CUBEW_FREE( calltreetitle, MEMORY_TRACING_PREFIX "Release calltreetitle"  );

    for ( i = 0; i < reg->size; i++ )
    {
        /* write regions */
        cube_region* r = ( cube_region* )reg->data[ i ];
        cube_region_writeXML( r, meta_data_writer );
    }

    for ( i = 0; i < rcnd->size; i++ )
    {
        /* write cnodes */
        cube_cnode* c = ( cube_cnode* )rcnd->data[ i ];
        cube_cnode_writeXML( c, meta_data_writer );
    }

    cube_write_meta_data__( meta_data_writer, "</program>\n" );

    /* system */
    cube_write_meta_data__( meta_data_writer, "<system" );
    char* systemtreetitle = ( char* )cube_services_escape_to_xml__( cube_get_systemtree_title( cube ) );
    if ( systemtreetitle != NULL )
    {
        cube_write_meta_data__( meta_data_writer, " title=\"%s\"", systemtreetitle );
    }
    cube_write_meta_data__( meta_data_writer, ">\n" );
    CUBEW_FREE( systemtreetitle, MEMORY_TRACING_PREFIX "Release systemtreetitle"  );


    if ( root_stn->size > 0 )
    {
        for ( i = 0; i < root_stn->size; i++ )  /* write system resources */
        {
            cube_system_tree_node* m = ( cube_system_tree_node* )root_stn->data[ i ];
            cube_system_tree_node_writeXML( m, meta_data_writer );
        }
    }
    else
    {
        cube_system_tree_writer_start(  cube->system_tree_writer );
        cube_system_tree_writer_write(  cube->system_tree_writer, meta_data_writer );
        cube_system_tree_writer_end(  cube->system_tree_writer );
    }

    /* topologies */
    cube_write_meta_data__( meta_data_writer, "<topologies>\n" );
    for ( i = 0; i < cart->size; i++ ) /* write topologies */
    {
        cube_cartesian* c = ( cube_cartesian* )cart->data[ i ];
        cube_cart_writeXML( c, meta_data_writer );
    }
    cube_write_meta_data__( meta_data_writer, "</topologies>\n" );
    cube_write_meta_data__( meta_data_writer, "</system>\n" );
    cube_write_meta_data__( meta_data_writer, "</cube>\n" );

    close_meta_data_writer( meta_data_writer );
    cube_report_anchor_finish(  cube->layout, fp );
}


/**
 * before any writing call cube has to prepare every metric for writing. It has to "inform" it
 * about number of threads and cnodes, so the corresponding metric allocated proper structureas in memory.
 */
static
void
cube_prepare_metrics_for_writing__( cube_t* cube )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    if (  cube->first_call == CUBE_TRUE )
    {
        uint64_t _n_flat_locations = cube_get_system_tree_information( cube )->number_locations;
        uint32_t i;
        for ( i = 0; i <  cube->met_ar->size; i++ )
        {
            cube_metric* metric =  cube->met_ar->data[ i ];
            cube_metric_setup_for_writing( metric,  cube->cnd_ar,  cube->rcnd_ar,  cube->locs_ar->size + _n_flat_locations );
        }
        cube->first_call = CUBE_FALSE;
    }
    cube->locked_for_writing = CUBE_TRUE;
}



/**
 *
 */
carray*
cube_get_cnodes_for_metric( cube_t*      cube,
                            cube_metric* metric )
{
    carray* enm =  cube_metric_return_enumeration( metric );
    if ( enm == NULL )
    {
        uint64_t _n_flat_locations = cube_get_system_tree_information( cube )->number_locations;
        cube_metric_setup_for_writing( metric,  cube->cnd_ar,  cube->rcnd_ar,  cube->locs_ar->size + _n_flat_locations );
    }
    enm = cube_metric_return_enumeration( metric );

    return enm;
}



/**
 * writes the "sevs" as a row  of chars (assumes, that it is a memory representation of correct values. For integer metric -> row of 64bit integers, for float metric -> row of doubles) over "threads" for given combination "metric, caleenode".
 */
void
cube_write_sev_row( cube_t*      cube,
                    cube_metric* met,
                    cube_cnode*  cnd,
                    void*        sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row( met, cnd, sevs );
}



/**
 * writes the "sevs" as a row of doubles over "threads" for given combination "metric, caleenode".
 * Metric performs internal transformation if needed into proper number type like double -> uint64_t
 */
void
cube_write_sev_row_of_doubles( cube_t*      cube,
                               cube_metric* met,
                               cube_cnode*  cnd,
                               double*      sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_doubles( met, cnd, sevs );
}




/**
 * writes the "sevs" as a row of 64 bits unsigned integers over "threads" for given combination "metric, caleenode".
 * Metric performs internal transformation if needed into proper number type like uint64_t -> double
 */
void
cube_write_sev_row_of_uint64( cube_t*      cube,
                              cube_metric* met,
                              cube_cnode*  cnd,
                              uint64_t*    sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }

    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_uint64( met, cnd, sevs );
}

/**
 * writes the "sevs" as a row of 64 bits unsigned integers over "threads" for given combination "metric, caleenode".
 * Metric performs internal transformation if needed into proper number type like uint64_t -> double
 */
void
cube_write_sev_row_of_int64( cube_t*      cube,
                             cube_metric* met,
                             cube_cnode*  cnd,
                             int64_t*     sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }

    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_int64( met, cnd, sevs );
}



/**
 * writes end of the .cube file. used in couple with "void cube_write_sev_row"
 */
void
cube_write_finish( cube_t* cube )
{
    uint32_t i;
    for ( i = 0; i <  cube->met_ar->size; i++ )
    {
        cube_metric* metric =  cube->met_ar->data[ i ];
        cube_metric_finish( metric,  cube->cube_flavour == CUBE_MASTER );
    }
    cube_write_def( cube );
}



/**
 * Inform a given metric about cnodes, which have nonzero data.
 * Metric transforms the bitstring according the its enumeration of cnodes.
 */
void
cube_set_known_cnodes_for_metric( cube_t*      cube,
                                  cube_metric* metric,
                                  char*        known_cnodes )
{
    if ( known_cnodes == 0 )
    {
        UTILS_FATAL(  "Failed to set a bit vector of known cnodes. Received pointer is zero.\n" );
    }
    uint64_t _n_flat_locations = cube_get_system_tree_information( cube )->number_locations;
    cube_metric_setup_for_writing( metric,  cube->cnd_ar,  cube->rcnd_ar,  cube->locs_ar->size + _n_flat_locations );
    cube_metric_set_known_cnodes( metric, known_cnodes );
}




/**
 *
 */
void
cube_set_statistic_name( cube_t*     cube,
                         const char* statfile )
{
    cube_def_attr( cube, "statisticfile", statfile );
}

/**
 *
 */
char*
cube_get_statistic_name( cube_t* cube )
{
    uint32_t i = 0;
    for ( i = 0; i < cube->attr->size; i++ )
    {
        if ( !strcmp( ( cube->attr->data[ i ] )->key, "statisticfile" ) )
        {
            return ( cube->attr->data[ i ] )->value;
        }
    }
    return "";
}




/**
 *
 */
void
cube_set_metrics_title( cube_t*     cube,
                        const char* metrics_title )
{
    if ( cube->metrics_title != NULL )
    {
        CUBEW_FREE( cube->metrics_title, MEMORY_TRACING_PREFIX "Release metrics title" );
    }
    cube->metrics_title = cubew_strdup( metrics_title );
}

/**
 *
 */
char*
cube_get_metrics_title( cube_t* cube )
{
    return cube->metrics_title;
}



/**
 *
 */
void
cube_set_calltree_title( cube_t*     cube,
                         const char* calltree_title )
{
    if ( cube->calltree_title != NULL )
    {
        CUBEW_FREE( cube->calltree_title, MEMORY_TRACING_PREFIX "Release call tree  title" );
    }
    cube->calltree_title = cubew_strdup( calltree_title );
}

/**
 *
 */
char*
cube_get_calltree_title( cube_t* cube )
{
    return cube->calltree_title;
}



/**
 *
 */
void
cube_set_systemtree_title( cube_t*     cube,
                           const char* systemtree_title )
{
    if ( cube->systemtree_title != NULL )
    {
        CUBEW_FREE( cube->systemtree_title, MEMORY_TRACING_PREFIX "Release system tree title" );
    }
    cube->systemtree_title = cubew_strdup( systemtree_title );
}

/**
 *
 */
char*
cube_get_systemtree_title( cube_t* cube )
{
    return cube->systemtree_title;
}




/**
 *
 */
void
cube_enable_flat_tree( cube_t*           cube,
                       const enum bool_t status )
{
    cube_def_attr( cube, "withflattree", ( status == CUBE_TRUE ) ? "yes" : "no" );
}

/**
 *
 */
enum bool_t
cube_is_flat_tree_enabled( cube_t* cube )
{
    uint32_t i = 0;
    for ( i = 0; i < cube->attr->size; i++ )
    {
        if ( !strcmp( ( cube->attr->data[ i ] )->key, "withflattree" )  )
        {
            if ( !strcmp( ( cube->attr->data[ i ] )->value, "no" )  )
            {
                return CUBE_FALSE;
            }
            if ( !strcmp( ( cube->attr->data[ i ] )->value, "yes" )  )
            {
                return CUBE_TRUE;
            }
        }
    }
    return CUBE_TRUE;
}


/* List of the canonical writing calls. They perform type casting if needed and check metric if it supports that kind of value. Internally they call cube_write_sev_row(...)*/


/* ----------------------- 8 bits -------------------- */
void
cube_write_sev_row_of_cube_type_uint8( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_uint8* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_uint8( met, cnd, sevs );
}

void
cube_write_sev_row_of_cube_type_int8( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_int8* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_int8( met, cnd, sevs );
}




/* ----------------------- 16 bits -------------------- */

void
cube_write_sev_row_of_cube_type_uint16( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_uint16* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_uint16( met, cnd, sevs );
}

void
cube_write_sev_row_of_cube_type_int16( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_int16* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_int16( met, cnd, sevs );
}



/* ----------------------- 32 bits -------------------- */


void
cube_write_sev_row_of_cube_type_uint32( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_uint32* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_uint32( met, cnd, sevs );
}

void
cube_write_sev_row_of_cube_type_int32( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_int32* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_int32( met, cnd, sevs );
}


/* ----------------------- 64 bits -------------------- */


void
cube_write_sev_row_of_cube_type_uint64( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_uint64* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_uint64( met, cnd, sevs );
}

void
cube_write_sev_row_of_cube_type_int64( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_int64* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_int64( met, cnd, sevs );
}

/* ----------------------- double -------------------- */

void
cube_write_sev_row_of_cube_type_double( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_double* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_double( met, cnd, sevs );
}

/* ----------------------- TAU atomic  -------------------- */


void
cube_write_sev_row_of_cube_type_tau_atomic( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_tau_atomic* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_tau_atomic( met, cnd, sevs );
}
/* ----------------------- Scale functions  -------------------- */


void
cube_write_sev_row_of_cube_type_scale_func( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_scale_func* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_scale_func( met, cnd, sevs );
}

/* ----------------------- Complex  -------------------- */
void
cube_write_sev_row_of_cube_type_complex( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_complex* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_complex( met, cnd, sevs );
}



/* ----------------------- Rate  -------------------- */
void
cube_write_sev_row_of_cube_type_rate( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_rate* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_rate( met, cnd, sevs );
}


/* ----------------------- Histogram  -------------------- */

void
cube_write_sev_row_of_cube_type_histogram( cube_t* cube, cube_metric* met,  cube_cnode* cnd, cube_type_double* sevs )
{
    if (  cube->cube_flavour == CUBE_SLAVE )
    {
        return;                                 /* CUBE_SLAVE doesn't write anything" */
    }
    cube_prepare_metrics_for_writing__( cube );
    cube_metric_write_row_of_cube_type_histogram( met, cnd, sevs );
}



/* ----------------------- Write miscelaneous data ---------*/
void
cube_write_misc_data( cube_t* cb, const char* dataname, char* data, uint64_t len )
{
    FILE* fp = cube_report_misc_data_start( cb->layout, dataname );
    fwrite( data, 1, len, fp );
    cube_report_anchor_finish( cb->layout, fp );
}
