/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2012,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2012,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2012, 2015,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2012,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2012, 2013, 2017-2018, 2020, 2023,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2012,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2012,
 * Technische Universitaet Muenchen, Germany
 *
 * Copyright (c) 2015,
 * Technische Universitaet Darmstadt, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */

/**
 * @file
 *
 *
 *
 * Contains implementation for post-processing operations for task structires and
 * task related metrics.
 * In particular, it moves the visits from the task pointer regions to a "no of switches"
 * metric
 *
 */

#include <config.h>

#include <SCOREP_Definitions.h>
#include <SCOREP_RuntimeManagement.h>

#include <scorep_profile_definition.h>
#include <scorep_profile_location.h>
#include <scorep_profile_event_base.h>
#include <scorep_profile_node.h>

#include <string.h>

static void
visit_to_switches( scorep_profile_node* node,
                   void*                param )
{
    if ( node->node_type != SCOREP_PROFILE_NODE_REGULAR_REGION )
    {
        return;
    }

    SCOREP_RegionHandle region = scorep_profile_type_get_region_handle( node->type_specific_data );
    if ( SCOREP_RegionHandle_GetType( region ) != SCOREP_REGION_TASK )
    {
        return;
    }

    static SCOREP_MetricHandle switches_metric = SCOREP_INVALID_METRIC;

    if ( switches_metric == SCOREP_INVALID_METRIC )
    {
        switches_metric = SCOREP_Definitions_NewMetric( "number of switches",
                                                        "Number of switches to this type of tasks. "
                                                        "This includes the number of task begins and "
                                                        "the number of task resumes",
                                                        SCOREP_METRIC_SOURCE_TYPE_TASK,
                                                        SCOREP_METRIC_MODE_ACCUMULATED_START,
                                                        SCOREP_METRIC_VALUE_UINT64,
                                                        SCOREP_METRIC_BASE_DECIMAL,
                                                        0,
                                                        "",
                                                        SCOREP_METRIC_PROFILING_TYPE_EXCLUSIVE,
                                                        SCOREP_INVALID_METRIC );
    }

    scorep_profile_trigger_int64( ( SCOREP_Profile_LocationData* )param,
                                  switches_metric,
                                  node->count,
                                  node,
                                  SCOREP_PROFILE_TRIGGER_UPDATE_VALUE_AS_IS );
    node->count = 0;
}

static scorep_profile_node*
change_root_node( SCOREP_Profile_LocationData* location,
                  scorep_profile_node*         localRootNode,
                  SCOREP_RegionHandle          rootRegion,
                  scorep_profile_node_type     rootType,
                  scorep_profile_node*         node,
                  bool                         addInclusiveTime )
{
    scorep_profile_node* program_root    = NULL;
    scorep_profile_node* artificial_root = NULL;
    if ( localRootNode == NULL )
    {
        /* Create root nodes for each new location. */
        scorep_profile_type_data_t program_region_data;
        memset( &program_region_data, 0, sizeof( program_region_data ) );
        scorep_profile_type_set_region_handle( &program_region_data, SCOREP_GetProgramRegion() );
        program_root = scorep_profile_create_node( location,
                                                   NULL,
                                                   rootType,
                                                   program_region_data,
                                                   SCOREP_GetBeginEpoch(),
                                                   false );

        scorep_profile_type_data_t root_region_data;
        memset( &root_region_data, 0, sizeof( root_region_data ) );
        scorep_profile_type_set_region_handle( &root_region_data, rootRegion );
        artificial_root = scorep_profile_create_node( location,
                                                      NULL,
                                                      rootType,
                                                      root_region_data,
                                                      UINT64_MAX, false );
        scorep_profile_add_child( program_root, artificial_root );
    }
    else
    {
        /* Reuse local program_root->artificial_node subtree. */
        program_root = localRootNode;
        UTILS_BUG_ON( program_root->first_child == NULL );
        artificial_root = program_root->first_child;
    }

    if ( addInclusiveTime )
    {
        /* If the program root requires the added inclusive time
         * depends if the specific case had already accounted for
         * this time or not.
         */
        scorep_profile_merge_node_inclusive( program_root, node );
    }

    /* Move the node instance to the local subtree node below the
     * artificial node and add the node's inclusive time to the
     * artificial node as time is stored inclusively and has to be
     * propagated down.
     */
    scorep_profile_remove_node( node );
    scorep_profile_add_child( artificial_root, node );
    scorep_profile_merge_node_inclusive( artificial_root, node );

    /* Give the artificial node the timestamp of the first node instance. */
    if ( node->first_enter_time < artificial_root->first_enter_time )
    {
        artificial_root->first_enter_time = node->first_enter_time;
    }
    return program_root;
}


void
scorep_profile_process_tasks( void )
{
    scorep_profile_node*         thread_root = scorep_profile.first_root_node;
    SCOREP_Profile_LocationData* location    = NULL;

    /* Loop over all threads on a process. */
    while ( thread_root != NULL )
    {
        scorep_profile_node* next                           = NULL;
        scorep_profile_node* node                           = thread_root->first_child;
        scorep_profile_node* program_root_with_tasks_node   = NULL;
        scorep_profile_node* program_root_with_threads_node = NULL;
        scorep_profile_node* program_root_with_kernels_node = NULL;
        location = scorep_profile_type_get_location_data( thread_root->type_specific_data );

        /* Loop over regions that would appear as roots in a calltree if no further processing is applied.
         * That covers the program root, pthread functions, tasks and GPU location activities.
         */
        while ( node != NULL )
        {
            next = node->next_sibling;
            if ( node->node_type == SCOREP_PROFILE_NODE_REGULAR_REGION )
            {
                SCOREP_RegionHandle region_handle = scorep_profile_type_get_region_handle( node->type_specific_data );
                /* The program root doesn't have to be touched as it is the intended primary root
                 * node of the profile calltree. The remaining instances create on their thread_root
                 * a local subtree of the form:
                 * program_root ->artifical node(THREADS,KERNELS or TASKS)->recorded instances of threads,kernels,tasks
                 */
                if ( region_handle != SCOREP_GetProgramRegion() )
                {
                    SCOREP_LocationType location_type = SCOREP_Location_GetType( location->location_data );

                    if ( location_type == SCOREP_LOCATION_TYPE_CPU_THREAD )
                    {
                        /* Register the region handle on first visit. */
                        static SCOREP_RegionHandle program_root_with_threads_node_region = SCOREP_INVALID_REGION;
                        if ( program_root_with_threads_node_region == SCOREP_INVALID_REGION )
                        {
                            program_root_with_threads_node_region = SCOREP_Definitions_NewRegion( "THREADS",
                                                                                                  NULL,
                                                                                                  SCOREP_INVALID_SOURCE_FILE,
                                                                                                  SCOREP_INVALID_LINE_NO,
                                                                                                  SCOREP_INVALID_LINE_NO,
                                                                                                  SCOREP_PARADIGM_PTHREAD,
                                                                                                  SCOREP_REGION_ARTIFICIAL );
                        }
                        program_root_with_threads_node = change_root_node( location,
                                                                           program_root_with_threads_node,
                                                                           program_root_with_threads_node_region,
                                                                           SCOREP_PROFILE_NODE_TASK_ROOT,
                                                                           node,
                                                                           true );
                    }
                    if ( location_type == SCOREP_LOCATION_TYPE_GPU )
                    {
                        /* Register the region handle on first visit. */
                        static SCOREP_RegionHandle program_root_with_kernels_node_region = SCOREP_INVALID_REGION;
                        if ( program_root_with_kernels_node_region == SCOREP_INVALID_REGION )
                        {
                            program_root_with_kernels_node_region = SCOREP_Definitions_NewRegion( "KERNELS",
                                                                                                  NULL,
                                                                                                  SCOREP_INVALID_SOURCE_FILE,
                                                                                                  SCOREP_INVALID_LINE_NO,
                                                                                                  SCOREP_INVALID_LINE_NO,
                                                                                                  SCOREP_RegionHandle_GetParadigmType( region_handle ),
                                                                                                  SCOREP_REGION_ARTIFICIAL );
                        }

                        program_root_with_kernels_node = change_root_node( location,
                                                                           program_root_with_kernels_node,
                                                                           program_root_with_kernels_node_region,
                                                                           SCOREP_PROFILE_NODE_TASK_ROOT,
                                                                           node,
                                                                           true );
                    }
                }
            }
            if ( node->node_type == SCOREP_PROFILE_NODE_TASK_ROOT )
            {
                SCOREP_RegionHandle region_handle = scorep_profile_type_get_region_handle( node->type_specific_data );
                /* Register the region handle on first visit. */
                static SCOREP_RegionHandle program_root_with_tasks_node_region = SCOREP_INVALID_REGION;
                if ( program_root_with_tasks_node_region == SCOREP_INVALID_REGION )
                {
                    program_root_with_tasks_node_region = SCOREP_Definitions_NewRegion( "TASKS",
                                                                                        NULL,
                                                                                        SCOREP_INVALID_SOURCE_FILE,
                                                                                        SCOREP_INVALID_LINE_NO,
                                                                                        SCOREP_INVALID_LINE_NO,
                                                                                        SCOREP_RegionHandle_GetParadigmType( region_handle ),
                                                                                        SCOREP_REGION_ARTIFICIAL );
                }

                program_root_with_tasks_node = change_root_node( location,
                                                                 program_root_with_tasks_node,
                                                                 program_root_with_tasks_node_region,
                                                                 SCOREP_PROFILE_NODE_TASK_ROOT,
                                                                 node,
                                                                 false );
            }

            node = next;
        }

        /* If tasks, threads or kernels local subtrees were created, add them to the thread_root. */
        if ( program_root_with_tasks_node != NULL )
        {
            scorep_profile_add_child( thread_root, program_root_with_tasks_node );
        }
        if ( program_root_with_threads_node != NULL )
        {
            scorep_profile_add_child( thread_root, program_root_with_threads_node );
        }
        if ( program_root_with_kernels_node != NULL )
        {
            scorep_profile_add_child( thread_root, program_root_with_kernels_node );
        }

        thread_root = thread_root->next_sibling;
    }
}
