/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2012,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2012,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2014, 2021,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2012,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2012,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2012,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2012,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */

/** @internal
 *
 *  @file
 *
 *  @brief      This tool generates a basic CUDA OTF2 trace.
 */

#include <config.h>

#include <otf2/otf2.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <inttypes.h>

#include <iostream>
#include <vector>
#include <map>


/* ___ Global variables. ____________________________________________________ */



/** @internal
 *  @brief Defines the number of system tree switches. */
static uint64_t otf2_NUM_SWITCHES = 1;

/** @internal
 *  @brief Defines the number of nodes per switches. */
static uint64_t otf2_NODES_PER_SWITCH = 1;

/** @internal
 *  @brief Defines the number of CUDA devices per node. */
static uint64_t otf2_DEVICES_PER_NODE = 1;

/** @internal
 *  @brief Defines the number of processes per node. */
static uint64_t otf2_PROCS_PER_NODE = 1;

/** @internal
 *  @brief Defines the number of CUDA streams per context. */
static uint64_t otf2_STREAMS_PER_CONTEXT = 1;


/* ___ Prototypes for static functions. _____________________________________ */



static void
otf2_get_parameters( int    argc,
                     char** argv );

static void
check_pointer( void*       pointer,
               const char* description );

static void
check_status( OTF2_ErrorCode status,
              const char*    description );

static OTF2_FlushType
pre_flush( void*         userData,
           OTF2_FileType fileType,
           uint64_t      locationId,
           void*         callerData,
           bool final );

static OTF2_TimeStamp
post_flush( void*         userData,
            OTF2_FileType fileType,
            uint64_t      locationId );

static OTF2_FlushCallbacks flush_callbacks =
{
    .otf2_pre_flush  = pre_flush,
    .otf2_post_flush = post_flush
};

/* empty string definition */
enum
{
    STRING_EMPTY
};

/* system tree root */
enum
{
    SYSTEM_TREE_ROOT
};

/* definition IDs for regions */
enum
{
    REGION_MAIN,
    REGION_CUDA_LAUNCH,
    REGION_CUDA_MEMCOPY,
    REGION_KERNEL
};


/* definition IDs for Groups */
enum
{
    GROUP_CUDA_LOCATIONS
};

/* definition IDs for comms */
enum
{
    COMM_CUDA_RMA
};

/* ___ main _________________________________________________________________ */



/** Main function
 *
 *  This tool generates a basic unified OTF2 archive to test the reader
 *  components and tools.
 *
 *  @return                 Returns EXIT_SUCCESS if successful, EXIT_FAILURE
 *                          if an error occures.
 */
int
main( int    argc,
      char** argv )
{
    otf2_get_parameters( argc, argv );

    char        archive_path[ 128 ];
    char const* archive_name = "TestTrace";

    snprintf( archive_path, sizeof( archive_path ),
              "otf2_trace_gen_cuda_%" PRIu64 "_%" PRIu64 "_%" PRIu64 "_%" PRIu64 "_%" PRIu64 "",
              otf2_NUM_SWITCHES, otf2_NODES_PER_SWITCH, otf2_DEVICES_PER_NODE,
              otf2_PROCS_PER_NODE, otf2_STREAMS_PER_CONTEXT );

    /* Print initial information. */
    printf( "\nGenerating an OTF2 test CUDA archive\n" );
    printf( "with %" PRIu64 " device(s)\n",
            ( otf2_NUM_SWITCHES * otf2_NODES_PER_SWITCH * otf2_DEVICES_PER_NODE ) );
    printf( "to %s/%s.otf2\n\n", archive_path, archive_name );


    /* Create new archive handle. */
    OTF2_Archive* archive = OTF2_Archive_Open( archive_path,
                                               archive_name,
                                               OTF2_FILEMODE_WRITE,
                                               1024 * 1024,
                                               4 * 1024 * 1024,
                                               OTF2_SUBSTRATE_POSIX,
                                               OTF2_COMPRESSION_NONE );
    check_pointer( archive, "Create archive" );

    OTF2_ErrorCode status;
    status = OTF2_Archive_SetFlushCallbacks( archive, &flush_callbacks, NULL );
    check_status( status, "Set flush callbacks." );

    /* Set description, and creator. */
    status = OTF2_Archive_SetSerialCollectiveCallbacks( archive );
    check_status( status, "Set serial mode." );
    status = OTF2_Archive_SetDescription( archive, "Simple OTF2 trace archive to valid reader components" );
    check_status( status, "Set description." );
    status = OTF2_Archive_SetCreator( archive, "otf2_trace_gen_cuda" );
    check_status( status, "Set creator." );

    std::vector<OTF2_LocationRef>                              threads;
    std::vector<OTF2_LocationRef>                              streams;
    std::vector<OTF2_LocationRef>                              all_comm_locations;
    std::map<OTF2_LocationRef, std::vector<OTF2_LocationRef> > thread_comm_locations;
    std::map<OTF2_LocationRef, OTF2_LocationRef>               thread_of_stream;
    OTF2_LocationRef                                           number_of_locations = 0;
    OTF2_LocationRef                                           number_of_threads   = 0;
    OTF2_LocationRef                                           number_of_streams   = 0;

    /* Switches */
    for ( uint64_t i_switch = 0; i_switch < otf2_NUM_SWITCHES; i_switch++ )
    {
        /* Nodes */
        for ( uint64_t i_node = 0; i_node < otf2_NODES_PER_SWITCH; i_node++ )
        {
            /* Processes */
            OTF2_LocationGroupRef initial_threads[ otf2_PROCS_PER_NODE ];
            for ( uint64_t i_proc = 0; i_proc < otf2_PROCS_PER_NODE; i_proc++ )
            {
                number_of_threads++;
                OTF2_LocationRef thread = number_of_locations++;
                all_comm_locations.push_back( thread );
                thread_comm_locations.emplace( std::make_pair( thread, std::vector<OTF2_LocationRef>() ) );
                thread_comm_locations[ thread ].push_back( thread ); // rank 0
                initial_threads[ i_proc ] = thread;
                threads.push_back( thread );
            }

            /* CUDA contexts, match up proc/devices by using bresenham */
            int dx = otf2_PROCS_PER_NODE - 1;
            int dy = otf2_DEVICES_PER_NODE - 1;

            int deltaslowdirection = ( dx >= dy ) ? dy : dx;
            int deltafastdirection = ( dx >= dy ) ? dx : dy;
            int pdx                = !!( dx >= dy );
            int pdy                = !pdx;

            int i_proc   = 0;
            int i_device = 0;
            int err      = deltafastdirection / 2;
            int i        = 0;

            do
            {
                /* Streams */
                for ( uint64_t i_stream = 0; i_stream < otf2_STREAMS_PER_CONTEXT; i_stream++ )
                {
                    number_of_streams++;
                    OTF2_LocationRef stream = number_of_locations++;

                    streams.push_back( stream );
                    thread_of_stream[ stream ] = initial_threads[ i_proc ];
                    all_comm_locations.push_back( stream );
                    thread_comm_locations[ initial_threads[ i_proc ] ].push_back( stream );
                }

                err -= deltaslowdirection;
                if ( err < 0 )
                {
                    err += deltafastdirection;
                    i_proc++;
                    i_device++;
                }
                else
                {
                    i_proc   += pdx;
                    i_device += pdy;
                }
            }
            while ( ++i <= deltafastdirection );
        }
    }

    status = OTF2_Archive_OpenEvtFiles( archive );
    check_status( status, "Open event files for writing." );

    /* Create local event writer. */
    OTF2_EvtWriter* evt_writer = NULL;

    uint64_t t = 0;

    /* Enter main. */
    for ( const auto thread : threads )
    {
        evt_writer = OTF2_Archive_GetEvtWriter( archive, thread );
        check_pointer( evt_writer, "Get event writer." );

        status = OTF2_EvtWriter_Enter( evt_writer, NULL, t, REGION_MAIN );
        check_status( status, "Write Enter." );
    }
    ++t;

    /* Call cudaMemcopy in thread for each stream */
    std::map<OTF2_LocationRef, int> streams_of_thread;
    int                             max_arity = 0;
    for ( const auto stream : streams )
    {
        const auto thread = thread_of_stream[ stream ];
        const auto arity  = streams_of_thread[ thread ]++;
        if ( arity >= max_arity )
        {
            max_arity = arity + 1;
        }

        auto* const thread_writer = OTF2_Archive_GetEvtWriter( archive, thread );
        check_pointer( evt_writer, "Get event writer." );

        auto* const stream_writer = OTF2_Archive_GetEvtWriter( archive, stream );
        check_pointer( evt_writer, "Get event writer." );

        status = OTF2_EvtWriter_Enter( thread_writer, NULL, t + 4 * arity, REGION_CUDA_MEMCOPY );
        check_status( status, "Write Enter." );

        status = OTF2_EvtWriter_RmaGet( stream_writer, NULL, t + 4 * arity + 1,
                                        thread /* RMA window */,
                                        0 /* rank => thread */,
                                        1024 * 1024 /* bytes */,
                                        42 /* matching */ );
        check_status( status, "Write RmaGet." );

        status = OTF2_EvtWriter_RmaOpCompleteBlocking( stream_writer, NULL, t + 4 * arity + 2, thread, 42 );
        check_status( status, "Write RmaOpCompleteBlocking." );

        status = OTF2_EvtWriter_Leave( thread_writer, NULL, t + 4 * arity + 3, REGION_CUDA_MEMCOPY );
        check_status( status, "Write Leave." );
    }
    t += 4 * max_arity;

    /* Call cudaLaunchKernel in thread for each stream */
    streams_of_thread.clear();
    for ( const auto stream : streams )
    {
        const auto thread = thread_of_stream[ stream ];
        const auto arity  = streams_of_thread[ thread ]++;

        auto* const thread_writer = OTF2_Archive_GetEvtWriter( archive, thread );
        check_pointer( evt_writer, "Get event writer." );

        auto* const stream_writer = OTF2_Archive_GetEvtWriter( archive, stream );
        check_pointer( evt_writer, "Get event writer." );

        status = OTF2_EvtWriter_Enter( thread_writer, NULL, t + 4 * arity, REGION_CUDA_LAUNCH );
        check_status( status, "Write Enter." );

        status = OTF2_EvtWriter_Enter( stream_writer, NULL, t + 4 * arity + 1, REGION_KERNEL );
        check_status( status, "Write Leave." );

        status = OTF2_EvtWriter_Leave( stream_writer, NULL, t + 4 * arity + 2, REGION_KERNEL );
        check_status( status, "Write Leave." );

        status = OTF2_EvtWriter_Leave( thread_writer, NULL, t + 4 * arity + 3, REGION_CUDA_LAUNCH );
        check_status( status, "Write Leave." );
    }
    t += 4 * max_arity;

    /* Call cudaMemcopy in thread for each stream */
    streams_of_thread.clear();
    for ( const auto stream : streams )
    {
        const auto thread = thread_of_stream[ stream ];
        const auto arity  = streams_of_thread[ thread ]++;
        if ( arity >= max_arity )
        {
            max_arity = arity + 1;
        }

        auto* const thread_writer = OTF2_Archive_GetEvtWriter( archive, thread );
        check_pointer( evt_writer, "Get event writer." );

        auto* const stream_writer = OTF2_Archive_GetEvtWriter( archive, stream );
        check_pointer( evt_writer, "Get event writer." );

        status = OTF2_EvtWriter_Enter( thread_writer, NULL, t + 4 * arity, REGION_CUDA_MEMCOPY );
        check_status( status, "Write Enter." );

        status = OTF2_EvtWriter_RmaPut( stream_writer, NULL, t + 4 * arity + 1,
                                        thread /* RMA window */,
                                        0 /* rank => thread */,
                                        1024 * 1024 /* bytes */,
                                        42 /* matching */ );
        check_status( status, "Write RmaPut." );

        status = OTF2_EvtWriter_RmaOpCompleteBlocking( stream_writer, NULL, t + 4 * arity + 2, thread, 42 );
        check_status( status, "Write RmaOpCompleteBlocking." );

        status = OTF2_EvtWriter_Leave( thread_writer, NULL, t + 4 * arity + 3, REGION_CUDA_MEMCOPY );
        check_status( status, "Write Leave." );
    }
    t += 4 * max_arity;

    /* Leave main on initial threads. */
    for ( const auto thread : threads )
    {
        evt_writer = OTF2_Archive_GetEvtWriter( archive, thread );
        check_pointer( evt_writer, "Get event writer." );

        status = OTF2_EvtWriter_Leave( evt_writer, NULL, t, REGION_MAIN );
        check_status( status, "Write Leave." );
    }
    ++t;

    std::map<OTF2_LocationRef, uint64_t> number_of_events_per_location;
    for ( OTF2_LocationRef location = 0; location < number_of_locations; location++ )
    {
        evt_writer = OTF2_Archive_GetEvtWriter( archive, location );
        check_pointer( evt_writer, "Get event writer." );

        uint64_t number_of_events;
        status = OTF2_EvtWriter_GetNumberOfEvents( evt_writer,
                                                   &number_of_events );
        check_status( status, "Get the numberof written events." );

        status = OTF2_Archive_CloseEvtWriter( archive, evt_writer );
        check_status( status, "Close event writer." );

        number_of_events_per_location[ location ] = number_of_events;
    }
    status = OTF2_Archive_CloseEvtFiles( archive );
    check_status( status, "Close event files for reading." );

    /* Write the global and local definitions. */
    OTF2_GlobalDefWriter* glob_def_writer = NULL;
    glob_def_writer = OTF2_Archive_GetGlobalDefWriter( archive );
    check_pointer( glob_def_writer, "Get global definition writer" );

    /* Write the timerange of the trace */
    status = OTF2_GlobalDefWriter_WriteClockProperties( glob_def_writer,
                                                        1, 0, t,
                                                        OTF2_UNDEFINED_TIMESTAMP );
    check_status( status, "Write ClockProperties definition." );

    status = OTF2_GlobalDefWriter_WriteString( glob_def_writer,
                                               STRING_EMPTY,
                                               "" );
    check_status( status, "Write String definition." );
    OTF2_StringRef number_of_strings = STRING_EMPTY + 1;

    /* Paradigm */
    {
        OTF2_StringRef cuda_name = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, cuda_name, "CUDA" );
        check_status( status, "Write String definition." );

        /* Write paradigm definitions */
        status = OTF2_GlobalDefWriter_WriteParadigm( glob_def_writer,
                                                     OTF2_PARADIGM_CUDA,
                                                     cuda_name,
                                                     OTF2_PARADIGM_CLASS_ACCELERATOR );
        check_status( status, "Write Paradigm definition." );

        OTF2_Type           type;
        OTF2_AttributeValue value;
        OTF2_AttributeValue_SetBoolean( OTF2_TRUE, &type, &value );

        status = OTF2_GlobalDefWriter_WriteParadigmProperty( glob_def_writer,
                                                             OTF2_PARADIGM_CUDA,
                                                             OTF2_PARADIGM_PROPERTY_RMA_ONLY,
                                                             type,
                                                             value );
        check_status( status, "Write ParadigmProperty definition." );
    }

    OTF2_LocationGroupRef                             number_of_location_groups = 0;
    std::map<OTF2_LocationRef, OTF2_LocationGroupRef> group_of_location;

    OTF2_StringRef initial_thread_name = number_of_strings++;
    status = OTF2_GlobalDefWriter_WriteString( glob_def_writer,
                                               initial_thread_name,
                                               "Initial thread" );
    check_status( status, "Write String definition." );

    std::size_t thread_it = 0;
    std::size_t stream_it = 0;
    /* Write system tree definitions. */
    {
        OTF2_StringRef machine_name  = number_of_strings++;
        OTF2_StringRef machine_class = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, machine_name, "fake" );
        check_status( status, "Write String definition." );
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, machine_class, "machine" );
        check_status( status, "Write String definition." );

        status = OTF2_GlobalDefWriter_WriteSystemTreeNode( glob_def_writer, SYSTEM_TREE_ROOT,
                                                           machine_name,
                                                           machine_class,
                                                           OTF2_UNDEFINED_SYSTEM_TREE_NODE );
        check_status( status, "Write SystemTreeNode definition." );
        OTF2_SystemTreeNodeRef number_of_system_tree_nodes = SYSTEM_TREE_ROOT + 1;

        status = OTF2_GlobalDefWriter_WriteSystemTreeNodeDomain( glob_def_writer,
                                                                 SYSTEM_TREE_ROOT,
                                                                 OTF2_SYSTEM_TREE_DOMAIN_MACHINE );
        check_status( status, "Write system tree node property." );

        OTF2_StringRef switch_class = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, switch_class, "switch" );
        check_status( status, "Write String definition." );

        OTF2_StringRef node_class = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, node_class, "node" );
        check_status( status, "Write String definition." );

        OTF2_StringRef device_class = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, device_class, "CUDA device" );
        check_status( status, "Write String definition." );

        /* Switches */
        for ( uint64_t i_switch = 0; i_switch < otf2_NUM_SWITCHES; i_switch++ )
        {
            char switch_name_buf[ 32 ];
            snprintf( switch_name_buf, sizeof( switch_name_buf ),
                      "#%" PRIu64, i_switch );

            OTF2_StringRef switch_name = number_of_strings++;
            status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, switch_name, switch_name_buf );
            check_status( status, "Write String definition." );

            OTF2_SystemTreeNodeRef switch_node = number_of_system_tree_nodes++;
            status = OTF2_GlobalDefWriter_WriteSystemTreeNode( glob_def_writer,
                                                               switch_node,
                                                               switch_name,
                                                               switch_class,
                                                               SYSTEM_TREE_ROOT );
            check_status( status, "Write SystemTreeNode definition." );

            /* Nodes */
            for ( uint64_t i_node = 0; i_node < otf2_NODES_PER_SWITCH; i_node++ )
            {
                uint64_t node_id = i_switch * otf2_NODES_PER_SWITCH + i_node;
                char     node_name_buf[ 32 ];
                snprintf( node_name_buf, sizeof( node_name_buf ),
                          "n%03" PRIu64 "", node_id );

                OTF2_StringRef node_name = number_of_strings++;
                status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, node_name, node_name_buf );
                check_status( status, "Write String definition." );

                OTF2_SystemTreeNodeRef node_node = number_of_system_tree_nodes++;
                status = OTF2_GlobalDefWriter_WriteSystemTreeNode( glob_def_writer,
                                                                   node_node,
                                                                   node_name,
                                                                   node_class,
                                                                   switch_node );
                check_status( status, "Write SystemTreeNode definition." );

                status = OTF2_GlobalDefWriter_WriteSystemTreeNodeDomain( glob_def_writer,
                                                                         node_node,
                                                                         OTF2_SYSTEM_TREE_DOMAIN_SHARED_MEMORY );
                check_status( status, "Write system tree node property." );

                /* Devices */
                OTF2_SystemTreeNodeRef devices[ otf2_DEVICES_PER_NODE ];
                for ( uint64_t i_device = 0; i_device < otf2_DEVICES_PER_NODE; i_device++ )
                {
                    char device_name_buf[ 32 ];
                    snprintf( device_name_buf, sizeof( device_name_buf ),
                              "%" PRIu64 "", i_device );

                    OTF2_StringRef device_name = number_of_strings++;
                    status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, device_name, device_name_buf );
                    check_status( status, "Write String definition." );

                    OTF2_SystemTreeNodeRef device_node = number_of_system_tree_nodes++;
                    status = OTF2_GlobalDefWriter_WriteSystemTreeNode( glob_def_writer,
                                                                       device_node,
                                                                       device_name,
                                                                       device_class,
                                                                       node_node );
                    check_status( status, "Write SystemTreeNode definition." );

                    devices[ i_device ] = device_node;

                    status = OTF2_GlobalDefWriter_WriteSystemTreeNodeDomain( glob_def_writer,
                                                                             device_node,
                                                                             OTF2_SYSTEM_TREE_DOMAIN_ACCELERATOR_DEVICE );
                    check_status( status, "Write SystemTreeNodeDomain definition." );
                }

                /* Processes */
                OTF2_LocationGroupRef procs[ otf2_PROCS_PER_NODE ];
                for ( uint64_t i_proc = 0; i_proc < otf2_PROCS_PER_NODE; i_proc++ )
                {
                    uint64_t proc_id = node_id * otf2_PROCS_PER_NODE + i_proc;
                    char     proc_name_buf[ 32 ];
                    snprintf( proc_name_buf, sizeof( proc_name_buf ),
                              "Process %" PRIu64 "", proc_id );

                    OTF2_StringRef proc_name = number_of_strings++;
                    status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, proc_name, proc_name_buf );
                    check_status( status, "Write String definition." );

                    OTF2_LocationGroupRef proc = number_of_location_groups++;
                    status = OTF2_GlobalDefWriter_WriteLocationGroup( glob_def_writer,
                                                                      proc,
                                                                      proc_name,
                                                                      OTF2_LOCATION_GROUP_TYPE_PROCESS,
                                                                      node_node,
                                                                      OTF2_UNDEFINED_LOCATION_GROUP );
                    check_status( status, "Write LocationGroup definition." );

                    procs[ i_proc ] = proc;

                    /* Initial thread */
                    OTF2_LocationRef thread = threads[ thread_it++ ];
                    group_of_location[ thread ] = proc;

                    status = OTF2_GlobalDefWriter_WriteLocation( glob_def_writer,
                                                                 thread,
                                                                 initial_thread_name,
                                                                 OTF2_LOCATION_TYPE_CPU_THREAD,
                                                                 number_of_events_per_location[ thread ],
                                                                 group_of_location[ thread ] );
                    check_status( status, "Write Location definition." );
                }

                /* CUDA contexts, match up proc/devices by using bresenham */
                int dx = otf2_PROCS_PER_NODE - 1;
                int dy = otf2_DEVICES_PER_NODE - 1;

                int deltaslowdirection = ( dx >= dy ) ? dy : dx;
                int deltafastdirection = ( dx >= dy ) ? dx : dy;
                int pdx                = !!( dx >= dy );
                int pdy                = !pdx;

                int i_proc   = 0;
                int i_device = 0;
                int err      = deltafastdirection / 2;
                int i        = 0;

                do
                {
                    char context_name_buf[ 32 ];
                    snprintf( context_name_buf, sizeof( context_name_buf ),
                              "CUDA context %d", i );

                    OTF2_StringRef context_name = number_of_strings++;
                    status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, context_name, context_name_buf );
                    check_status( status, "Write String definition." );

                    OTF2_LocationGroupRef context = number_of_location_groups++;
                    status = OTF2_GlobalDefWriter_WriteLocationGroup( glob_def_writer,
                                                                      context,
                                                                      context_name,
                                                                      OTF2_LOCATION_GROUP_TYPE_ACCELERATOR,
                                                                      devices[ i_device ],
                                                                      procs[ i_proc ] );
                    check_status( status, "Write LocationGroup definition." );

                    /* Streams */
                    for ( uint64_t i_stream = 0; i_stream < otf2_STREAMS_PER_CONTEXT; i_stream++ )
                    {
                        char stream_name_buf[ 64 ];
                        snprintf( stream_name_buf, sizeof( stream_name_buf ),
                                  "CUDA stream %" PRIu64 "", i_stream );

                        OTF2_StringRef stream_name = number_of_strings++;
                        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer, stream_name, stream_name_buf );
                        check_status( status, "Write String definition." );

                        OTF2_LocationRef stream = streams[ stream_it++ ];
                        group_of_location[ stream ] = context;

                        status = OTF2_GlobalDefWriter_WriteLocation( glob_def_writer,
                                                                     stream,
                                                                     stream_name,
                                                                     OTF2_LOCATION_TYPE_ACCELERATOR_STREAM,
                                                                     number_of_events_per_location[ stream ],
                                                                     group_of_location[ stream ] );
                        check_status( status, "Write Location definition." );
                    }

                    err -= deltaslowdirection;
                    if ( err < 0 )
                    {
                        err += deltafastdirection;
                        i_proc++;
                        i_device++;
                    }
                    else
                    {
                        i_proc   += pdx;
                        i_device += pdy;
                    }
                }
                while ( ++i <= deltafastdirection );
            }
        }
    }

    /* Write region definition for "main". */
    {
        OTF2_StringRef main_name = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer,
                                                   main_name,
                                                   "main(int, char**)" );
        check_status( status, "Write String definition" );

        OTF2_StringRef main_mangled_name = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer,
                                                   main_mangled_name,
                                                   "main" );
        check_status( status, "Write String definition" );

        status = OTF2_GlobalDefWriter_WriteRegion( glob_def_writer,
                                                   REGION_MAIN,
                                                   main_name,
                                                   main_mangled_name,
                                                   STRING_EMPTY,
                                                   OTF2_REGION_ROLE_FUNCTION,
                                                   OTF2_PARADIGM_COMPILER,
                                                   OTF2_REGION_FLAG_NONE,
                                                   STRING_EMPTY,
                                                   0,
                                                   0 );
        check_status( status, "Write Region definition" );
    }

    /* Write region definition for "cudaLaunchKernel". */
    {
        OTF2_StringRef launch_name = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer,
                                                   launch_name,
                                                   "cudaLaunchKernel" );
        check_status( status, "Write String definition" );

        status = OTF2_GlobalDefWriter_WriteRegion( glob_def_writer,
                                                   REGION_CUDA_LAUNCH,
                                                   launch_name,
                                                   launch_name,
                                                   STRING_EMPTY,
                                                   OTF2_REGION_ROLE_WRAPPER,
                                                   OTF2_PARADIGM_CUDA,
                                                   OTF2_REGION_FLAG_NONE,
                                                   STRING_EMPTY,
                                                   0,
                                                   0 );
        check_status( status, "Write Region definition" );
    }

    /* Write region definition for "cudaMemcopy". */
    {
        OTF2_StringRef memcpy_name = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer,
                                                   memcpy_name,
                                                   "cudaMemcopy" );
        check_status( status, "Write String definition" );

        status = OTF2_GlobalDefWriter_WriteRegion( glob_def_writer,
                                                   REGION_CUDA_MEMCOPY,
                                                   memcpy_name,
                                                   memcpy_name,
                                                   STRING_EMPTY,
                                                   OTF2_REGION_ROLE_WRAPPER,
                                                   OTF2_PARADIGM_CUDA,
                                                   OTF2_REGION_FLAG_NONE,
                                                   STRING_EMPTY,
                                                   0,
                                                   0 );
        check_status( status, "Write Region definition" );
    }

    /* Write region definition for "kernel". */
    {
        OTF2_StringRef kernel_name = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer,
                                                   kernel_name,
                                                   "kernel" );
        check_status( status, "Write String definition" );

        status = OTF2_GlobalDefWriter_WriteRegion( glob_def_writer,
                                                   REGION_KERNEL,
                                                   kernel_name,
                                                   kernel_name,
                                                   STRING_EMPTY,
                                                   OTF2_REGION_ROLE_FUNCTION,
                                                   OTF2_PARADIGM_CUDA,
                                                   OTF2_REGION_FLAG_NONE,
                                                   STRING_EMPTY,
                                                   0,
                                                   0 );
        check_status( status, "Write Region definition" );
    }

    status = OTF2_GlobalDefWriter_WriteGroup( glob_def_writer,
                                              GROUP_CUDA_LOCATIONS,
                                              STRING_EMPTY,
                                              OTF2_GROUP_TYPE_COMM_LOCATIONS,
                                              OTF2_PARADIGM_CUDA,
                                              OTF2_GROUP_FLAG_NONE,
                                              all_comm_locations.size(),
                                              all_comm_locations.data() );
    check_status( status, "Write Group definition." );
    OTF2_GroupRef number_of_groups = GROUP_CUDA_LOCATIONS + 1;

    for ( const auto& kv : thread_comm_locations )
    {
        const auto thread  = kv.first;
        const auto members = kv.second;
        status = OTF2_GlobalDefWriter_WriteGroup( glob_def_writer,
                                                  number_of_groups + thread,
                                                  STRING_EMPTY,
                                                  OTF2_GROUP_TYPE_COMM_GROUP,
                                                  OTF2_PARADIGM_CUDA,
                                                  OTF2_GROUP_FLAG_NONE,
                                                  members.size(),
                                                  members.data() );
        check_status( status, "Write Group definition." );

        status = OTF2_GlobalDefWriter_WriteComm( glob_def_writer,
                                                 thread,
                                                 STRING_EMPTY,
                                                 number_of_groups + thread,
                                                 OTF2_UNDEFINED_COMM,
                                                 OTF2_COMM_FLAG_NONE );
        check_status( status, "Write Comm definition." );

        char win_name_buf[ 64 ];
        snprintf( win_name_buf, sizeof( win_name_buf ),
                  "CUDA memory #%" PRIu64, thread );

        OTF2_StringRef win_name = number_of_strings++;
        status = OTF2_GlobalDefWriter_WriteString( glob_def_writer,
                                                   win_name,
                                                   win_name_buf );

        status = OTF2_GlobalDefWriter_WriteRmaWin( glob_def_writer,
                                                   thread,
                                                   win_name,
                                                   thread,
                                                   OTF2_RMA_WIN_FLAG_NONE );
        check_status( status, "Write RmaWin definition." );
    }

    status = OTF2_Archive_CloseGlobalDefWriter( archive, glob_def_writer );
    check_status( status, "Closing global definition writer." );

    status = OTF2_Archive_OpenDefFiles( archive );
    check_status( status, "Open local definition files for writing." );

    for ( OTF2_LocationRef location = 0; location < number_of_locations; location++ )
    {
        /* Open a definition writer, so the file is created. */
        OTF2_DefWriter* def_writer = OTF2_Archive_GetDefWriter( archive, location );
        check_pointer( def_writer, "Get definition writer." );

        status = OTF2_Archive_CloseDefWriter( archive, def_writer );
        check_status( status, "Close local definition writer." );
    }

    status = OTF2_Archive_CloseDefFiles( archive );
    check_status( status, "Close local definition files for writing." );

    /* Finalize. */
    status = OTF2_Archive_Close( archive );
    check_status( status, "Close archive." );


    printf( "Done\n\n" );


    return EXIT_SUCCESS;
}



/* ___ Implementation of static functions ___________________________________ */


/** @internal
 *  @brief Parse a number from the command line.
 */
uint64_t
otf2_parse_number_argument( const char* option,
                            const char* argument )
{
    uint64_t number = 0;
    for ( uint8_t j = 0; argument[ j ]; j++ )
    {
        if ( ( argument[ j ] < '0' ) || ( argument[ j ] > '9' ) )
        {
            printf( "ERROR: Invalid number argument for %s: %s\n", option, argument );
            printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
            exit( EXIT_FAILURE );
        }
        uint64_t new_number = number * 10 + argument[ j ] - '0';
        if ( new_number < number )
        {
            printf( "ERROR: Number argument to large for %s: %s\n", option, argument );
            printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
            exit( EXIT_FAILURE );
        }
        number = new_number;
    }

    return number;
}

/** @internal
 *  @brief Get command line parameters.
 *
 *  Parses command line parameters and checks for their existence.
 *  Prints help for parameters '-h' or '--help'.
 *
 *  @param argc             Programs argument counter.
 *  @param argv             Programs argument values.
 */
void
otf2_get_parameters( int    argc,
                     char** argv )
{
    /* Check if there is at least one command line parameter. */
    if ( argc < 2 )
    {
        return;
    }

    /* Check for passed '--help' or '-h' and print help. */
    if ( !strcmp( argv[ 1 ], "--help" ) || !strcmp( argv[ 1 ], "-h" ) )
    {
        printf( "Usage: otf2-trace-gen-cuda [OPTION]... \n" );
        printf( "Generate a basic unified OTF2 archive.\n" );
        printf( "\n" );
        printf( "  -spm, --switches-per-machine  Number of switches per machine (Should be small).\n" );
        printf( "  -nps, --nodes-per-switch      Number of nodes per switch (Should be small).\n" );
        printf( "  -dpn, --devices-per-node      Number of devices per node (Should be small).\n" );
        printf( "  -ppn, --procs-per-node        Number of processes per node (Should be small).\n" );
        printf( "  -spc, --streams-per-context   Number of streams per context (Should be small).\n" );
        printf( "  -V, --version                 Print version information.\n" );
        printf( "  -h, --help                    Print this help information.\n" );
        printf( "\n" );
        printf( "Report bugs to <%s>\n", PACKAGE_BUGREPORT );
        exit( EXIT_SUCCESS );
    }

    /* Check for passed '--version' or '-V' and print version information. */
    if ( !strcmp( argv[ 1 ], "--version" ) || !strcmp( argv[ 1 ], "-V" ) )
    {
        printf( "otf2-trace-gen-cuda: version %s\n", OTF2_VERSION );
        exit( EXIT_SUCCESS );
    }

    for ( uint8_t i = 1; i < argc; i++ )
    {
        if ( !strcmp( argv[ i ], "--switches-per-machine" ) || !strcmp( argv[ i ], "-spm" ) )
        {
            if ( i + 1 == argc )
            {
                printf( "ERROR: Missing argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }

            otf2_NUM_SWITCHES = otf2_parse_number_argument( argv[ i ], argv[ i + 1 ] );
            if ( otf2_NUM_SWITCHES == 0 )
            {
                printf( "ERROR: Invalid 0 argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }
            i++;
        }

        else if ( !strcmp( argv[ i ], "--nodes-per-witch" ) || !strcmp( argv[ i ], "-nps" ) )
        {
            if ( i + 1 == argc )
            {
                printf( "ERROR: Missing argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }

            otf2_NODES_PER_SWITCH = otf2_parse_number_argument( argv[ i ], argv[ i + 1 ] );
            if ( otf2_NODES_PER_SWITCH == 0 )
            {
                printf( "ERROR: Invalid 0 argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }
            i++;
        }

        else if ( !strcmp( argv[ i ], "--devices-per-node" ) || !strcmp( argv[ i ], "-dpn" ) )
        {
            if ( i + 1 == argc )
            {
                printf( "ERROR: Missing argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }

            otf2_DEVICES_PER_NODE = otf2_parse_number_argument( argv[ i ], argv[ i + 1 ] );
            if ( otf2_DEVICES_PER_NODE == 0 )
            {
                printf( "ERROR: Invalid 0 argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }
            i++;
        }

        else if ( !strcmp( argv[ i ], "--procs-per-node" ) || !strcmp( argv[ i ], "-ppn" ) )
        {
            if ( i + 1 == argc )
            {
                printf( "ERROR: Missing argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }

            otf2_PROCS_PER_NODE = otf2_parse_number_argument( argv[ i ], argv[ i + 1 ] );
            if ( otf2_PROCS_PER_NODE == 0 )
            {
                printf( "ERROR: Invalid 0 argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }
            i++;
        }

        else if ( !strcmp( argv[ i ], "--streams-per-context" ) || !strcmp( argv[ i ], "-spc" ) )
        {
            if ( i + 1 == argc )
            {
                printf( "ERROR: Missing argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }

            otf2_STREAMS_PER_CONTEXT = otf2_parse_number_argument( argv[ i ], argv[ i + 1 ] );
            if ( otf2_STREAMS_PER_CONTEXT == 0 )
            {
                printf( "ERROR: Invalid 0 argument for %s.\n", argv[ i ] );
                printf( "Try 'otf2-trace-gen-cuda --help' for information on usage.\n\n" );
                exit( EXIT_FAILURE );
            }
            i++;
        }

        else
        {
            printf( "WARNING: Skipped unknown control option %s.\n", argv[ i ] );
        }
    }

    return;
}


void
check_pointer( void*       pointer,
               char const* description )
{
    if ( pointer == NULL )
    {
        printf( "\nERROR: %s\n\n", description );
        exit( EXIT_FAILURE );
    }
}



void
check_status( OTF2_ErrorCode status,
              char const*    description )
{
    if ( status != OTF2_SUCCESS )
    {
        printf( "\nERROR: %s\n\n", description );
        exit( EXIT_FAILURE );
    }
}

static OTF2_FlushType
pre_flush( void*         userData,
           OTF2_FileType fileType,
           uint64_t      locationId,
           void*         callerData,
           bool final )
{
    return OTF2_FLUSH;
}

static OTF2_TimeStamp
post_flush( void*         userData,
            OTF2_FileType fileType,
            uint64_t      locationId )
{
    return 0; /* should never flush */
}
