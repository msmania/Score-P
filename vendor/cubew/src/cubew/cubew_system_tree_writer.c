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
 * \file cubew_system_tree_writer.c
   \brief Provides the data structure traverser and system tree writer
 */

#include <config.h>
#include "cubew_system_tree_writer.h"
#include "UTILS_Error.h"
#include "cubew_memory.h"

#define MEMORY_TRACING_PREFIX "[SYSTEM TREE WRITER]"

const uint32_t states_size_chunk = 128;


cube_system_tree_writer*
cube_system_tree_writer_create()
{
    cube_system_tree_writer* system_tree_writer__ = ( cube_system_tree_writer* )CUBEW_MALLOC( sizeof( cube_system_tree_writer ), MEMORY_TRACING_PREFIX "Allocate system tree writer"  );
    system_tree_writer__->init   = NULL;
    system_tree_writer__->step   = NULL;
    system_tree_writer__->finish = NULL;

    system_tree_writer__->user_ptr = NULL;

    system_tree_writer__->stn_id = 0;
    system_tree_writer__->lg_id  = 0;
    system_tree_writer__->loc_id = 0;

    system_tree_writer__->loc_id = 0;

    system_tree_writer__->stn_plain = cube_system_tree_node_plain_create();
    system_tree_writer__->lg_plain  = cube_location_group_plain_create();
    system_tree_writer__->loc_plain = cube_location_plain_create();



    /** basic state stack */
    system_tree_writer__->state_index                                  = 0;
    system_tree_writer__->states_size                                  = 1;
    system_tree_writer__->states                                       = CUBEW_MALLOC( states_size_chunk * sizeof( cube_system_tree_writer_state ), MEMORY_TRACING_PREFIX "Allocate vector of system tree writer states"  );
    system_tree_writer__->states[  system_tree_writer__->state_index ] = CUBE_SYSTEM_TREE_WRITER_INIT;

    system_tree_writer__->system_tree_information = ( cube_system_tree_information* )CUBEW_CALLOC( 1, sizeof( cube_system_tree_information ), MEMORY_TRACING_PREFIX "Allocate system tree information structure"  );

    return system_tree_writer__;
}


void
cube_system_tree_writer_free( cube_system_tree_writer* stwriter )
{
    if (  stwriter != NULL )
    {
        cube_system_tree_node_plain_free(  stwriter->stn_plain );
        cube_location_group_plain_free(  stwriter->lg_plain );
        cube_location_plain_free(  stwriter->loc_plain );
        CUBEW_FREE(  stwriter->states, MEMORY_TRACING_PREFIX "Release vector of system tree writer states" );
        CUBEW_FREE(  stwriter->system_tree_information, MEMORY_TRACING_PREFIX "Release system tree information structure"  );
    }
    CUBEW_FREE(  stwriter, MEMORY_TRACING_PREFIX "Release system tree writer" );
}


void
cube_system_tree_writer_setup( cube_system_tree_writer* stwriter, cube_system_tree_writer_init init, cube_system_tree_writer_step step, cube_system_tree_writer_driver driver, cube_system_tree_writer_finish finish, void* _user_ptr )
{
    stwriter->init     = init;
    stwriter->step     = step;
    stwriter->driver   = driver;
    stwriter->finish   = finish;
    stwriter->user_ptr = _user_ptr;
}


static
void
cube_system_tree_writer_state_pop__( cube_system_tree_writer* stwriter )
{
#if DEBUG
    if (  stwriter->state_index == 0 )
    {
        UTILS_FATAL( "Cannot reduce size of the states stack. Current size id 0\n" );
    }
#endif
    stwriter->state_index--;
}


static
void
cube_system_tree_writer_state_push__( cube_system_tree_writer*      stwriter,
                                      cube_system_tree_writer_state state )
{
    if (  stwriter->state_index == (  stwriter->states_size - 1 ) )
    {
        stwriter->states       = ( cube_system_tree_writer_state* )CUBEW_REALLOC(  stwriter->states,  stwriter->states_size * sizeof( cube_system_tree_writer_state ),  (  stwriter->states_size + states_size_chunk ) * sizeof( cube_system_tree_writer_state ), MEMORY_TRACING_PREFIX "Expand vector of states" );
        stwriter->states_size += states_size_chunk;
    }
    stwriter->state_index++;
    stwriter->states[   stwriter->state_index ] = state;
}

static
void
cube_system_tree_writer_process__( cube_system_tree_writer*      stwriter,
                                   cube_system_tree_writer_state next_state,
                                   cube_system_tree_node_plain*  _stn_plain,
                                   cube_location_group_plain*    _lg_plain,
                                   cube_location_plain*          _loc_plain )
{
    cube_system_tree_writer_state current_state =  stwriter->states[   stwriter->state_index ];
    switch ( current_state )
    {
        case CUBE_SYSTEM_TREE_WRITER_INIT:
            switch ( next_state )
            {
                case CUBE_SYSTEM_TREE_WRITER_STN:
                    cube_system_tree_writer_state_push__(  stwriter,  CUBE_SYSTEM_TREE_WRITER_STN );
                    cube_system_tree_node_plain_write( _stn_plain,  stwriter->stn_id,   stwriter->meta_data_writer );
                    stwriter->stn_id++;
                    break;
                case CUBE_SYSTEM_TREE_WRITER_INIT:
                case CUBE_SYSTEM_TREE_WRITER_LG:
                case CUBE_SYSTEM_TREE_WRITER_LOC:
                case CUBE_SYSTEM_TREE_WRITER_UP:
                    UTILS_WARNING( "Wrong system tree structure, One cannot start with location group, location or a 'step up'. System tree node is expected.\n" );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_END:
                default:
                    break;
            }
            ;
            break;
        case CUBE_SYSTEM_TREE_WRITER_STN:
            switch ( next_state )
            {
                case CUBE_SYSTEM_TREE_WRITER_STN:
                    cube_system_tree_writer_state_push__(  stwriter, CUBE_SYSTEM_TREE_WRITER_STN );
                    cube_system_tree_node_plain_write(  stwriter->stn_plain,  stwriter->stn_id,   stwriter->meta_data_writer );
                    stwriter->stn_id++;
                    break;
                case CUBE_SYSTEM_TREE_WRITER_LG:
                    cube_system_tree_writer_state_push__(  stwriter, CUBE_SYSTEM_TREE_WRITER_LG );
                    cube_location_group_plain_write( _lg_plain,  stwriter->lg_id,  stwriter->meta_data_writer );
                    stwriter->lg_id++;
                    break;
                case CUBE_SYSTEM_TREE_WRITER_LOC:
                    UTILS_FATAL( "Wrong system tree structure. System tree node cannot have location as a child. Location group or system tree node expected.\n" );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_INIT:
                    UTILS_FATAL( "Error in processing. Illegal 'INIT' state.\n" );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_UP:
                    cube_system_tree_node_plain_write( NULL, 0,  stwriter->meta_data_writer );
                    cube_system_tree_writer_state_pop__( stwriter );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_END:
                default:
                    break;
            }
            ;
            break;
        case CUBE_SYSTEM_TREE_WRITER_LG:
            switch ( next_state )
            {
                case CUBE_SYSTEM_TREE_WRITER_STN:
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_UP, _stn_plain, _lg_plain, _loc_plain );
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_STN, _stn_plain, _lg_plain, _loc_plain  );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_LG:
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_UP, _stn_plain, _lg_plain, _loc_plain  );
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_LG, _stn_plain, _lg_plain, _loc_plain  );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_LOC:
                    cube_location_plain_write( _loc_plain,  stwriter->loc_id,  stwriter->meta_data_writer );
                    cube_location_plain_write( NULL, 0,  stwriter->meta_data_writer );
                    stwriter->loc_id++;
                    break;
                case CUBE_SYSTEM_TREE_WRITER_INIT:
                    UTILS_FATAL( "Error in processing. Illegal 'INIT' state.\n" );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_UP:
                    cube_location_group_plain_write( NULL, 0,  stwriter->meta_data_writer );
                    cube_system_tree_writer_state_pop__( stwriter );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_END:
                default:
                    break;
            }
            ;
            break;
        case CUBE_SYSTEM_TREE_WRITER_LOC:
            switch ( next_state )
            {
                case CUBE_SYSTEM_TREE_WRITER_STN:
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_UP, _stn_plain, _lg_plain, _loc_plain  );
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_UP, _stn_plain, _lg_plain, _loc_plain  );
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_STN, _stn_plain, _lg_plain, _loc_plain  );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_LG:
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_UP, _stn_plain, _lg_plain, _loc_plain  );
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_UP, _stn_plain, _lg_plain, _loc_plain  );
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_LG, _stn_plain, _lg_plain, _loc_plain  );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_LOC:
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_UP, _stn_plain, _lg_plain, _loc_plain  );
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_LOC, _stn_plain, _lg_plain, _loc_plain  );
                    cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_UP, _stn_plain, _lg_plain, _loc_plain  );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_INIT:
                    UTILS_FATAL( "Error in processing. Illegal 'INIT' state.\n" );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_UP:
                    cube_location_plain_write( NULL, 0,  stwriter->meta_data_writer );
                    cube_system_tree_writer_state_pop__( stwriter );
                    break;
                case CUBE_SYSTEM_TREE_WRITER_END:
                default:
                    break;
            }
            ;
            break;
        case CUBE_SYSTEM_TREE_WRITER_UP:
        case CUBE_SYSTEM_TREE_WRITER_END:
        default:
            break;
    }
    ;
}



void
cube_system_tree_writer_driver_step( void*                         stwriter,
                                     cube_system_tree_writer_state next_state,
                                     cube_system_tree_node_plain*  _stn_plain,
                                     cube_location_group_plain*    _lg_plain,
                                     cube_location_plain*          _loc_plain )
{
    cube_system_tree_writer* writer = ( cube_system_tree_writer* )stwriter;
    cube_system_tree_writer_process__( writer, next_state, _stn_plain, _lg_plain, _loc_plain );


    /*
     * cleanup for next step
     */
    cube_system_tree_node_plain_clear( writer->stn_plain );
    cube_location_group_plain_clear( writer->lg_plain );
    cube_location_plain_clear( writer->loc_plain );
}



void
cube_system_tree_writer_start( cube_system_tree_writer* stwriter )
{
    if ( (  stwriter != NULL )
         && (  stwriter->init != NULL )
         )
    {
        stwriter->init(  stwriter->system_tree_information,  stwriter->user_ptr );
    }
}



void
cube_system_tree_writer_driver_write( cube_system_tree_writer* stwriter, cube_meta_data_writer* writer )
{
    if ( (  stwriter != NULL )
         && (  stwriter->driver != NULL )
         )
    {
        stwriter->driver(  stwriter,  stwriter->user_ptr );
    }
}






void
cube_system_tree_writer_write( cube_system_tree_writer* stwriter, cube_meta_data_writer* writer )
{
    stwriter->meta_data_writer = writer;
    cube_system_tree_node_plain_clear(  stwriter->stn_plain );
    cube_location_group_plain_clear(  stwriter->lg_plain );
    cube_location_plain_clear(  stwriter->loc_plain );

    if (  stwriter->step == NULL &&  stwriter->driver == NULL )
    {
        return;
    }
    if (  stwriter->step == NULL &&  stwriter->driver != NULL )
    {
        return cube_system_tree_writer_driver_write(  stwriter, writer );
    }
    if (  stwriter->step != NULL &&  stwriter->driver != NULL )
    {
        UTILS_FATAL( "'step' and 'driver' callbacks are not NULL. Only one at the time is allowed.\n" );
    }


    cube_system_tree_writer_state next_state =  stwriter->step(  stwriter->stn_plain,  stwriter->lg_plain,  stwriter->loc_plain,  stwriter->user_ptr );
    while (  next_state != CUBE_SYSTEM_TREE_WRITER_STOP )
    {
        cube_system_tree_writer_process__(  stwriter, next_state,  stwriter->stn_plain,  stwriter->lg_plain,  stwriter->loc_plain );

        cube_system_tree_node_plain_clear(  stwriter->stn_plain );
        cube_location_group_plain_clear(  stwriter->lg_plain );
        cube_location_plain_clear(  stwriter->loc_plain );

        next_state =  stwriter->step(  stwriter->stn_plain,  stwriter->lg_plain,  stwriter->loc_plain,  stwriter->user_ptr );
        if ( next_state == CUBE_SYSTEM_TREE_WRITER_END )
        {
            while (  stwriter->state_index != 0 )
            {
                cube_system_tree_writer_process__(  stwriter, CUBE_SYSTEM_TREE_WRITER_UP,  stwriter->stn_plain,  stwriter->lg_plain,  stwriter->loc_plain  );
            }
        }
    }

    cube_system_tree_node_plain_clear(  stwriter->stn_plain );
    cube_location_group_plain_clear(  stwriter->lg_plain );
    cube_location_plain_clear(  stwriter->loc_plain );
}

void
cube_system_tree_writer_end( cube_system_tree_writer* stwriter )
{
    if ( (  stwriter != NULL )
         &&
         (  stwriter->finish != NULL ) )
    {
        stwriter->finish(  stwriter->user_ptr );
    }
}
