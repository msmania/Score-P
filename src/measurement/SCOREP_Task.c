/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2014-2015,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2015, 2018, 2021-2022,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2015,
 * Technische Universitaet Muenchen, Germany
 *
 * Copyright (c) 2016, 2024,
 * Technische Universitaet Dresden, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */

/**
 * @file
 */

#include <config.h>
#include "scorep_task_internal.h"
#include <SCOREP_Memory.h>
#include <SCOREP_Subsystem.h>
#include <SCOREP_Events.h>
#include <SCOREP_Location.h>
#include <UTILS_Error.h>
#include <scorep_status.h>
#include <scorep_substrates_definition.h>
#include <SCOREP_Substrates_Management.h>
#include <SCOREP_InMeasurement.h>
#include <SCOREP_Definitions.h>

#include <jenkins_hash.h>

#include <string.h>

#define SCOREP_TASK_STACK_SIZE 30

/* ********************************************* types and variables */
typedef struct scorep_task_stack_frame
{
    SCOREP_RegionHandle             regions[ SCOREP_TASK_STACK_SIZE ];
    struct scorep_task_stack_frame* prev;
} scorep_task_stack_frame;

typedef struct SCOREP_Task
{
    scorep_task_stack_frame* current_frame;
    uint32_t                 current_index;
    uint32_t                 thread_id;
    uint32_t                 generation_number;
    uint32_t                 parent_hash_value;
    SCOREP_TaskHandle        next;
    void*                    substrate_data[];
} SCOREP_Task;

typedef struct scorep_location_task_data
{
    SCOREP_TaskHandle        current_task;
    SCOREP_TaskHandle        recycled_tasks;
    SCOREP_TaskHandle        implicit_task;
    scorep_task_stack_frame* recycled_frames;
} scorep_location_task_data;

static size_t task_subsystem_id;

/* ********************************************* static functions */
static inline void
recycle_stack_frame( SCOREP_Location*         location,
                     scorep_task_stack_frame* frame )
{
    scorep_location_task_data* subsystem_data
                                    = SCOREP_Location_GetSubsystemData( location, task_subsystem_id );
    frame->prev                     = subsystem_data->recycled_frames;
    subsystem_data->recycled_frames = frame;
}

static inline void
recycle_task( SCOREP_Location*  location,
              SCOREP_TaskHandle task )
{
    scorep_location_task_data* subsystem_data
                                   = SCOREP_Location_GetSubsystemData( location, task_subsystem_id );
    task->next                     = subsystem_data->recycled_tasks;
    subsystem_data->recycled_tasks = task;
}

static scorep_task_stack_frame*
alloc_new_stack_frame( SCOREP_Location* location )
{
    scorep_task_stack_frame*   new_frame;
    scorep_location_task_data* subsystem_data
        = SCOREP_Location_GetSubsystemData( location, task_subsystem_id );
    if ( subsystem_data->recycled_frames != NULL )
    {
        new_frame                       = subsystem_data->recycled_frames;
        subsystem_data->recycled_frames = subsystem_data->recycled_frames->prev;
    }
    else
    {
        new_frame = ( scorep_task_stack_frame* )
                    SCOREP_Location_AllocForMisc( location, sizeof( scorep_task_stack_frame ) );
    }

    return new_frame;
}

static SCOREP_ErrorCode
task_subsystem_register( size_t id )
{
    task_subsystem_id = id;
    return SCOREP_SUCCESS;
}

static SCOREP_ErrorCode
task_subsystem_init_location( SCOREP_Location* location, SCOREP_Location* parent )
{
    scorep_location_task_data* subsystem_data
        = SCOREP_Location_AllocForMisc( location,
                                        sizeof( *subsystem_data ) );

    memset( subsystem_data, 0, sizeof( *subsystem_data ) );

    SCOREP_Location_SetSubsystemData( location,
                                      task_subsystem_id,
                                      subsystem_data );

    subsystem_data->current_task = scorep_task_create( location,
                                                       SCOREP_Location_GetId( location ),
                                                       0 );
    subsystem_data->implicit_task                   = subsystem_data->current_task;
    subsystem_data->current_task->parent_hash_value =  SCOREP_Location_GetLastForkHash( parent );


    return SCOREP_SUCCESS;
}

static void
task_subsystem_finalize_location( SCOREP_Location* location )
{
    scorep_location_task_data* subsystem_data
        = SCOREP_Location_GetSubsystemData( location, task_subsystem_id );

    scorep_task_complete( location, subsystem_data->current_task );
}

static inline void
task_pop_stack( SCOREP_Location*  location,
                SCOREP_TaskHandle task )
{
    UTILS_BUG_ON( NULL == task->current_frame, "Task stack underflow." );
    if ( task->current_index == 0 )
    {
        scorep_task_stack_frame* old_frame = task->current_frame;
        task->current_frame = task->current_frame->prev;
        task->current_index = SCOREP_TASK_STACK_SIZE - 1;
        recycle_stack_frame( location, old_frame );
    }
    else
    {
        task->current_index--;
    }
}
/* ************************************** subsystem struct */

const SCOREP_Subsystem SCOREP_Subsystem_TaskStack =
{
    .subsystem_name              = "TASK",
    .subsystem_register          = &task_subsystem_register,
    .subsystem_init_location     = &task_subsystem_init_location,
    .subsystem_finalize_location = &task_subsystem_finalize_location
};

/* ************************************** internal interface functions */

SCOREP_TaskHandle
scorep_task_create( SCOREP_Location* location,
                    uint32_t         threadId,
                    uint32_t         generationNumber )
{
    SCOREP_TaskHandle          new_task;
    scorep_location_task_data* subsystem_data
        = SCOREP_Location_GetSubsystemData( location, task_subsystem_id );
    if ( subsystem_data->recycled_tasks != NULL )
    {
        new_task                       = subsystem_data->recycled_tasks;
        subsystem_data->recycled_tasks = subsystem_data->recycled_tasks->next;
    }
    else
    {
        new_task = ( SCOREP_TaskHandle )
                   SCOREP_Location_AllocForMisc( location, sizeof( SCOREP_Task ) +
                                                 SCOREP_Substrates_NumberOfRegisteredSubstrates() * sizeof( void* ) );
    }

    new_task->current_frame     = NULL;
    new_task->current_index     = SCOREP_TASK_STACK_SIZE - 1;
    new_task->thread_id         = threadId;
    new_task->generation_number = generationNumber;

    if ( subsystem_data->current_task != NULL )
    {
        /* Will only be used for explicit tasks, not implicit ones. */
        new_task->parent_hash_value = SCOREP_Task_GetRegionStackHash( subsystem_data->current_task );
    }


    memset( new_task->substrate_data, 0, SCOREP_Substrates_NumberOfRegisteredSubstrates() * sizeof( void* ) );

    /* Ignore return value 'substrate_id', only needed for re-initialization in OA. */
    SCOREP_CALL_SUBSTRATE_MGMT( CoreTaskCreate, CORE_TASK_CREATE,
                                ( location, new_task ) );

    return new_task;
}

void
scorep_task_complete( SCOREP_Location*  location,
                      SCOREP_TaskHandle task )
{
    SCOREP_CALL_SUBSTRATE_MGMT( CoreTaskComplete, CORE_TASK_COMPLETE,
                                ( location, task ) );
    recycle_task( location, task );
}

void
scorep_task_switch( SCOREP_Location*  location,
                    SCOREP_TaskHandle newTask )
{
    scorep_location_task_data* subsystem_data
                                 = SCOREP_Location_GetSubsystemData( location, task_subsystem_id );
    subsystem_data->current_task = newTask;
}

/* ************************************** external interface functions */

void
SCOREP_Task_ExitAllRegions( SCOREP_Location*  location,
                            SCOREP_TaskHandle task )
{
    UTILS_BUG_ON( location != SCOREP_Location_GetCurrentCPULocation(),
                  "You try to trigger exits on location A from location B." );
    while ( task->current_frame != NULL )
    {
        /* The exit removes the top region from the stack. */
        SCOREP_RegionHandle region = SCOREP_Task_GetTopRegion( task );
        if ( region != SCOREP_FILTERED_REGION )
        {
            SCOREP_ExitRegion( region );
        }
        else
        {
            task_pop_stack( location, task );
        }
    }
}

void
SCOREP_Location_Task_ExitAllRegions( SCOREP_Location*  location,
                                     SCOREP_TaskHandle task,
                                     uint64_t          timestamp )
{
    UTILS_BUG_ON( SCOREP_IS_MEASUREMENT_PHASE( WITHIN ) &&
                  location != SCOREP_Location_GetCurrentCPULocation(),
                  "It is not safe to trigger exits on location A from location B during measurement." );
    while ( task->current_frame != NULL )
    {
        /* The exit removes the top region from the stack. */
        SCOREP_RegionHandle region = SCOREP_Task_GetTopRegion( task );
        if ( region != SCOREP_FILTERED_REGION )
        {
            SCOREP_Location_ExitRegion( location, timestamp, region );
        }
        else
        {
            task_pop_stack( location, task );
        }
    }
}

SCOREP_RegionHandle
SCOREP_Task_GetTopRegion( SCOREP_TaskHandle task )
{
    return task->current_frame == NULL ? SCOREP_INVALID_REGION :
           task->current_frame->regions[ task->current_index ];
}

uint32_t
SCOREP_Task_GetThreadId( SCOREP_TaskHandle task )
{
    return task->thread_id;
}

uint32_t
SCOREP_Task_GetGenerationNumber( SCOREP_TaskHandle task )
{
    return task->generation_number;
}

SCOREP_TaskHandle
SCOREP_Task_GetCurrentTask( SCOREP_Location* location )
{
    scorep_location_task_data* subsystem_data
        = SCOREP_Location_GetSubsystemData( location, task_subsystem_id );
    return subsystem_data->current_task;
}

void
SCOREP_Task_ClearStack( SCOREP_Location*  location,
                        SCOREP_TaskHandle task )
{
    while ( task->current_frame != NULL )
    {
        scorep_task_stack_frame* old_frame = task->current_frame;
        task->current_frame = task->current_frame->prev;
        recycle_stack_frame( location, old_frame );
    }
    task->current_index = SCOREP_TASK_STACK_SIZE - 1;
}

void
SCOREP_Task_ClearCurrent( void )
{
    SCOREP_Location* location = SCOREP_Location_GetCurrentCPULocation();
    SCOREP_Task_ClearStack( location, SCOREP_Task_GetCurrentTask( location ) );
}

void
SCOREP_Task_Enter( SCOREP_Location*    location,
                   SCOREP_RegionHandle region )
{
    scorep_location_task_data* subsystem_data
        = SCOREP_Location_GetSubsystemData( location, task_subsystem_id );
    UTILS_ASSERT( subsystem_data != NULL );
    SCOREP_TaskHandle task = subsystem_data->current_task;

    if ( task->current_index < SCOREP_TASK_STACK_SIZE - 1 )
    {
        task->current_index++;
        task->current_frame->regions[ task->current_index ] = region;
    }
    else
    {
        scorep_task_stack_frame* new_frame = alloc_new_stack_frame( location );
        new_frame->prev                   = task->current_frame;
        task->current_frame               = new_frame;
        task->current_frame->regions[ 0 ] = region;
        task->current_index               = 0;
    }
}

void
SCOREP_Task_Exit( SCOREP_Location* location )
{
    scorep_location_task_data* subsystem_data
        = SCOREP_Location_GetSubsystemData( location, task_subsystem_id );
    SCOREP_TaskHandle task = subsystem_data->current_task;

    task_pop_stack( location, task );
}

void*
SCOREP_Task_GetSubstrateData( SCOREP_TaskHandle task,
                              size_t            substrateId )
{
    return task->substrate_data[ substrateId ];
}

void
SCOREP_Task_SetSubstrateData( SCOREP_TaskHandle task,
                              size_t            substrateId,
                              void*             data )
{
    task->substrate_data[ substrateId ] = data;
}

static uint32_t
stack_frame_aggregation( const scorep_task_stack_frame* frame,
                         uint32_t                       frameSize,
                         SCOREP_TaskHandle              task )
{
    if ( !frame )
    {
        return task->parent_hash_value;
    }
    /* All previous frames are full, thus always pass `( SCOREP_TASK_STACK_SIZE - 1 )` */
    uint32_t aggregated_jenkinshash_value = stack_frame_aggregation( frame->prev, ( SCOREP_TASK_STACK_SIZE - 1 ), task );

    for ( uint32_t i = 0; i <= frameSize; i++ )
    {
        uint32_t region_hash = SCOREP_LOCAL_HANDLE_DEREF( frame->regions[ i ], Region )->hash_value;
        aggregated_jenkinshash_value = jenkins_hash( &region_hash, sizeof( region_hash ), aggregated_jenkinshash_value );
    }

    return aggregated_jenkinshash_value;
}

uint32_t
SCOREP_Task_GetRegionStackHash( SCOREP_TaskHandle task )
{
    if ( task->current_frame == NULL )
    {
        return 0;
    }

    /* The aggregation of previous full frames has to happen from the bottom to
     * the top of the stack to allow the integration of the parent thread/task
     * hash values and to match the master thread callpaths.
     */
    return stack_frame_aggregation( task->current_frame, task->current_index, task );
}
