/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2013,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2013,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2014, 2021,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2013,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2013,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2013,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2013,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */

//! [stdheaders]
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
//! [stdheaders]

//! [mpiotf2headers]
#include <mpi.h>

#include <otf2/otf2.h>
//! [mpiotf2headers]

//! [mpitypemacros]
#if MPI_VERSION < 3
#define OTF2_MPI_UINT64_T MPI_UNSIGNED_LONG
#define OTF2_MPI_INT64_T  MPI_LONG
#endif
//! [mpitypemacros]

#include <otf2/OTF2_MPI_Collectives.h>

//! [timestamps]
static OTF2_TimeStamp
get_time( void )
{
    double t = MPI_Wtime() * 1e9;
    return ( uint64_t )t;
}
//! [timestamps]

//! [flush]
static OTF2_FlushType
pre_flush( void*            userData,
           OTF2_FileType    fileType,
           OTF2_LocationRef location,
           void*            callerData,
           bool             final )
{
    return OTF2_FLUSH;
}

static OTF2_TimeStamp
post_flush( void*            userData,
            OTF2_FileType    fileType,
            OTF2_LocationRef location )
{
    return get_time();
}

static OTF2_FlushCallbacks flush_callbacks =
{
    .otf2_pre_flush  = pre_flush,
    .otf2_post_flush = post_flush
};
//! [flush]

enum
{
    REGION_MPI_INIT,
    REGION_MPI_FINALIZE,
    REGION_MPI_COMM_SPLIT,
    REGION_MPI_INTERCOMM_CREATE,
    REGION_MPI_COMM_FREE,
    REGION_MPI_BCAST,
    REGION_MPI_IBARRIER,
    REGION_MPI_TEST,
    REGION_MPI_WAIT
};

enum
{
    COMM_WORLD,
    COMM_SPLIT_0,
    COMM_SPLIT_1,
    COMM_INTERCOMM
};

//! [startmain]
int
main( int    argc,
      char** argv )
{
//! [startmain]
//! [mpiinit]
    MPI_Init( &argc, &argv );
    int size;
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    int rank;
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
//! [mpiinit]

//! [archiveopen]
    OTF2_Archive* archive = OTF2_Archive_Open( "ArchivePath",
                                               "ArchiveName",
                                               OTF2_FILEMODE_WRITE,
                                               1024 * 1024 /* event chunk size */,
                                               4 * 1024 * 1024 /* def chunk size */,
                                               OTF2_SUBSTRATE_POSIX,
                                               OTF2_COMPRESSION_NONE );
//! [archiveopen]

    OTF2_Archive_SetFlushCallbacks( archive, &flush_callbacks, NULL );

//! [collectivecbs]
    OTF2_MPI_Archive_SetCollectiveCallbacks( archive,
                                             MPI_COMM_WORLD,
                                             MPI_COMM_NULL );
//! [collectivecbs]

    OTF2_Archive_OpenEvtFiles( archive );

//! [getevtwriter]
    OTF2_EvtWriter* evt_writer = OTF2_Archive_GetEvtWriter( archive,
                                                            rank );
//! [getevtwriter]

    struct timespec epoch_timestamp_spec;
    clock_gettime( CLOCK_REALTIME, &epoch_timestamp_spec );
    uint64_t epoch_start = get_time();

//! [enter]
    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_INIT );
//! [enter]

//! [collbegin]
    OTF2_EvtWriter_MpiCollectiveBegin( evt_writer,
                                       NULL,
                                       get_time() );
//! [collbegin]

    // fake MPI_Init
    MPI_Barrier( MPI_COMM_WORLD );

    OTF2_EvtWriter_CommCreate( evt_writer,
                               NULL,
                               get_time(),
                               COMM_WORLD );

//! [collend]
    OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                     NULL,
                                     get_time(),
                                     OTF2_COLLECTIVE_OP_CREATE_HANDLE,
                                     COMM_WORLD,
                                     OTF2_COLLECTIVE_ROOT_NONE,
                                     0 /* bytes provided */,
                                     0 /* bytes obtained */ );
//! [collend]

//! [leave]
    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_INIT );
//! [leave]

    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_IBARRIER );

    uint64_t barrier_request_id = 1; /* freely chosen request ID */
    OTF2_EvtWriter_NonBlockingCollectiveRequest( evt_writer,
                                                 NULL,
                                                 get_time(),
                                                 barrier_request_id );

    MPI_Request barrier_request;
    MPI_Ibarrier( MPI_COMM_WORLD, &barrier_request );

    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_IBARRIER );

    MPI_Comm split_comm;
    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_COMM_SPLIT );

    OTF2_EvtWriter_MpiCollectiveBegin( evt_writer,
                                       NULL,
                                       get_time() );

    MPI_Comm_split( MPI_COMM_WORLD, rank % 2, rank, &split_comm );

    if ( 0 == rank % 2 )
    {
        OTF2_EvtWriter_CommCreate( evt_writer,
                                   NULL,
                                   get_time(),
                                   COMM_SPLIT_0 );
    }
    else
    {
        OTF2_EvtWriter_CommCreate( evt_writer,
                                   NULL,
                                   get_time(),
                                   COMM_SPLIT_1 );
    }

    OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                     NULL,
                                     get_time(),
                                     OTF2_COLLECTIVE_OP_CREATE_HANDLE,
                                     COMM_WORLD,
                                     OTF2_COLLECTIVE_ROOT_NONE,
                                     0 /* bytes provided */,
                                     0 /* bytes obtained */ );

    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_COMM_SPLIT );

    MPI_Comm inter_comm;
    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_INTERCOMM_CREATE );

    OTF2_EvtWriter_MpiCollectiveBegin( evt_writer,
                                       NULL,
                                       get_time() );

    if ( 0 == rank % 2 )
    {
        MPI_Intercomm_create( split_comm, 0, MPI_COMM_WORLD, 1, 1, &inter_comm );
    }
    else
    {
        MPI_Intercomm_create( split_comm, 0, MPI_COMM_WORLD, 0, 1, &inter_comm );
    }

    OTF2_EvtWriter_CommCreate( evt_writer,
                               NULL,
                               get_time(),
                               COMM_INTERCOMM );

    OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                     NULL,
                                     get_time(),
                                     OTF2_COLLECTIVE_OP_CREATE_HANDLE,
                                     COMM_WORLD,
                                     OTF2_COLLECTIVE_ROOT_NONE,
                                     0 /* bytes provided */,
                                     0 /* bytes obtained */ );

    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_INTERCOMM_CREATE );

    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_COMM_FREE );

    OTF2_EvtWriter_MpiCollectiveBegin( evt_writer,
                                       NULL,
                                       get_time() );

    MPI_Comm_free( &split_comm );

    if ( 0 == rank % 2 )
    {
        OTF2_EvtWriter_CommDestroy( evt_writer,
                                    NULL,
                                    get_time(),
                                    COMM_SPLIT_0 );

        OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                         NULL,
                                         get_time(),
                                         OTF2_COLLECTIVE_OP_DESTROY_HANDLE,
                                         COMM_SPLIT_0,
                                         OTF2_COLLECTIVE_ROOT_NONE,
                                         0 /* bytes provided */,
                                         0 /* bytes obtained */ );
    }
    else
    {
        OTF2_EvtWriter_CommDestroy( evt_writer,
                                    NULL,
                                    get_time(),
                                    COMM_SPLIT_1 );

        OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                         NULL,
                                         get_time(),
                                         OTF2_COLLECTIVE_OP_DESTROY_HANDLE,
                                         COMM_SPLIT_1,
                                         OTF2_COLLECTIVE_ROOT_NONE,
                                         0 /* bytes provided */,
                                         0 /* bytes obtained */ );
    }

    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_COMM_FREE );

    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_TEST );

    /* fake failing MPI_Test( &barrier_request, &flag, &status ); */
    OTF2_EvtWriter_MpiRequestTest( evt_writer,
                                   NULL,
                                   get_time(),
                                   barrier_request_id );

    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_TEST );

    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_BCAST );

    OTF2_EvtWriter_MpiCollectiveBegin( evt_writer,
                                       NULL,
                                       get_time() );

    int res = -1;
    if ( rank % 2 == 0 )
    {
        if ( rank == 0 )
        {
            res = 1;
            MPI_Bcast( &res, 1, MPI_INT, MPI_ROOT, inter_comm );

            OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                             NULL,
                                             get_time(),
                                             OTF2_COLLECTIVE_OP_BCAST,
                                             COMM_INTERCOMM,
                                             OTF2_COLLECTIVE_ROOT_SELF,
                                             0 /* bytes provided */,
                                             0 /* bytes obtained */ );
        }
        else
        {
            MPI_Bcast( &res, 1, MPI_INT, MPI_PROC_NULL, inter_comm );

            OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                             NULL,
                                             get_time(),
                                             OTF2_COLLECTIVE_OP_BCAST,
                                             COMM_INTERCOMM,
                                             OTF2_COLLECTIVE_ROOT_THIS_GROUP,
                                             0 /* bytes provided */,
                                             0 /* bytes obtained */ );
        }
    }
    else if ( rank % 2 == 1 )
    {
        MPI_Bcast( &res, 1, MPI_INT, 0, inter_comm );

        OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                         NULL,
                                         get_time(),
                                         OTF2_COLLECTIVE_OP_BCAST,
                                         COMM_INTERCOMM,
                                         0 /* root */,
                                         0 /* bytes provided */,
                                         0 /* bytes obtained */ );
    }

    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_BCAST );

    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_COMM_FREE );

    OTF2_EvtWriter_MpiCollectiveBegin( evt_writer,
                                       NULL,
                                       get_time() );

    MPI_Comm_free( &inter_comm );

    OTF2_EvtWriter_CommDestroy( evt_writer,
                                NULL,
                                get_time(),
                                COMM_INTERCOMM );

    OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                     NULL,
                                     get_time(),
                                     OTF2_COLLECTIVE_OP_DESTROY_HANDLE,
                                     COMM_INTERCOMM,
                                     OTF2_COLLECTIVE_ROOT_NONE,
                                     0 /* bytes provided */,
                                     0 /* bytes obtained */ );

    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_COMM_FREE );

    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_WAIT );

    MPI_Status barrier_status;
    MPI_Wait( &barrier_request, &barrier_status );

    OTF2_EvtWriter_NonBlockingCollectiveComplete( evt_writer,
                                                  NULL,
                                                  get_time(),
                                                  OTF2_COLLECTIVE_OP_BARRIER,
                                                  COMM_WORLD,
                                                  OTF2_COLLECTIVE_ROOT_NONE,
                                                  0 /* bytes provided */,
                                                  0 /* bytes obtained */,
                                                  barrier_request_id );

    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_WAIT );

    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_FINALIZE );

    OTF2_EvtWriter_MpiCollectiveBegin( evt_writer,
                                       NULL,
                                       get_time() );

    // fake MPI_Finalize
    MPI_Barrier( MPI_COMM_WORLD );

    OTF2_EvtWriter_CommDestroy( evt_writer,
                                NULL,
                                get_time(),
                                COMM_WORLD );

    OTF2_EvtWriter_MpiCollectiveEnd( evt_writer,
                                     NULL,
                                     get_time(),
                                     OTF2_COLLECTIVE_OP_DESTROY_HANDLE,
                                     COMM_WORLD,
                                     OTF2_COLLECTIVE_ROOT_NONE,
                                     0 /* bytes provided */,
                                     0 /* bytes obtained */ );

    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          REGION_MPI_FINALIZE );

    uint64_t epoch_end = get_time();

    OTF2_Archive_CloseEvtWriter( archive, evt_writer );

    OTF2_Archive_CloseEvtFiles( archive );

//! [deffiles]
    OTF2_Archive_OpenDefFiles( archive );
    OTF2_DefWriter* def_writer = OTF2_Archive_GetDefWriter( archive,
                                                            rank );
    OTF2_Archive_CloseDefWriter( archive, def_writer );
    OTF2_Archive_CloseDefFiles( archive );
//! [deffiles]

//! [epoch_reduce]
    uint64_t epoch_timestamp = epoch_timestamp_spec.tv_sec * 1000000000 + epoch_timestamp_spec.tv_nsec;
    struct
    {
        uint64_t timestamp;
        int      index;
    } epoch_start_pair, global_epoch_start_pair;
    epoch_start_pair.timestamp = epoch_start;
    epoch_start_pair.index     = rank;
    MPI_Allreduce( &epoch_start_pair,
                   &global_epoch_start_pair,
                   1, MPI_LONG_INT, MPI_MINLOC,
                   MPI_COMM_WORLD );
    if ( epoch_start_pair.index != 0 )
    {
        if ( rank == 0 )
        {
            MPI_Recv( &epoch_timestamp, 1, OTF2_MPI_UINT64_T,
                      epoch_start_pair.index, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
        }
        else
        {
            MPI_Send( &epoch_timestamp, 1, OTF2_MPI_UINT64_T,
                      0, 0, MPI_COMM_WORLD );
        }
    }

    uint64_t global_epoch_end;
    MPI_Reduce( &epoch_end,
                &global_epoch_end,
                1, OTF2_MPI_UINT64_T, MPI_MAX,
                0, MPI_COMM_WORLD );
//! [epoch_reduce]

//! [global_def_writer]
    if ( 0 == rank )
    {
        OTF2_GlobalDefWriter* global_def_writer = OTF2_Archive_GetGlobalDefWriter( archive );
//! [global_def_writer]

//! [clock_properties]
        OTF2_GlobalDefWriter_WriteClockProperties( global_def_writer,
                                                   1000000000,
                                                   global_epoch_start_pair.timestamp,
                                                   global_epoch_end - global_epoch_start_pair.timestamp + 1,
                                                   epoch_timestamp );
//! [clock_properties]

//! [strings]
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  0, "" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  1, "Initial Thread" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  2, "MPI_Init" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  3, "PMPI_Init" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  4, "MPI_Finalize" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  5, "PMPI_Finalize" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  6, "MPI_Comm_split" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  7, "PMPI_Comm_split" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  8, "MPI_Intercomm_create" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer,  9, "PMPI_Intercomm_create" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 10, "MPI_Comm_free" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 11, "PMPI_Comm_free" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 12, "MPI_Bcast" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 13, "PMPI_Bcast" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 14, "MPI_Ibarrier" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 15, "PMPI_Ibarrier" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 16, "MPI_Test" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 17, "PMPI_Test" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 18, "MPI_Wait" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 19, "PMPI_Wait" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 20, "MyHost" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 21, "node" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 22, "MPI" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 23, "MPI_COMM_WORLD" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 24, "SPLIT 0" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 25, "SPLIT 1" );
        OTF2_GlobalDefWriter_WriteString( global_def_writer, 26, "INTERCOMM" );
//! [strings]

//! [regions]
        OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                          REGION_MPI_INIT,
                                          2 /* region name  */,
                                          3 /* alternative name */,
                                          0 /* description */,
                                          OTF2_REGION_ROLE_FUNCTION,
                                          OTF2_PARADIGM_MPI,
                                          OTF2_REGION_FLAG_NONE,
                                          22 /* source file */,
                                          0 /* begin lno */,
                                          0 /* end lno */ );

        OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                          REGION_MPI_FINALIZE,
                                          4 /* region name  */,
                                          5 /* alternative name */,
                                          0 /* description */,
                                          OTF2_REGION_ROLE_FUNCTION,
                                          OTF2_PARADIGM_MPI,
                                          OTF2_REGION_FLAG_NONE,
                                          22 /* source file */,
                                          0 /* begin lno */,
                                          0 /* end lno */ );

        OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                          REGION_MPI_COMM_SPLIT,
                                          6 /* region name  */,
                                          7 /* alternative name */,
                                          0 /* description */,
                                          OTF2_REGION_ROLE_FUNCTION,
                                          OTF2_PARADIGM_MPI,
                                          OTF2_REGION_FLAG_NONE,
                                          22 /* source file */,
                                          0 /* begin lno */,
                                          0 /* end lno */ );

        OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                          REGION_MPI_INTERCOMM_CREATE,
                                          8 /* region name  */,
                                          9 /* alternative name */,
                                          0 /* description */,
                                          OTF2_REGION_ROLE_FUNCTION,
                                          OTF2_PARADIGM_MPI,
                                          OTF2_REGION_FLAG_NONE,
                                          22 /* source file */,
                                          0 /* begin lno */,
                                          0 /* end lno */ );

        OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                          REGION_MPI_COMM_FREE,
                                          10 /* region name  */,
                                          11 /* alternative name */,
                                          0 /* description */,
                                          OTF2_REGION_ROLE_FUNCTION,
                                          OTF2_PARADIGM_MPI,
                                          OTF2_REGION_FLAG_NONE,
                                          22 /* source file */,
                                          0 /* begin lno */,
                                          0 /* end lno */ );

        OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                          REGION_MPI_BCAST,
                                          12 /* region name  */,
                                          13 /* alternative name */,
                                          0 /* description */,
                                          OTF2_REGION_ROLE_COLL_ONE2ALL,
                                          OTF2_PARADIGM_MPI,
                                          OTF2_REGION_FLAG_NONE,
                                          22 /* source file */,
                                          0 /* begin lno */,
                                          0 /* end lno */ );

        OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                          REGION_MPI_IBARRIER,
                                          14 /* region name  */,
                                          15 /* alternative name */,
                                          0 /* description */,
                                          OTF2_REGION_ROLE_BARRIER,
                                          OTF2_PARADIGM_MPI,
                                          OTF2_REGION_FLAG_NONE,
                                          22 /* source file */,
                                          0 /* begin lno */,
                                          0 /* end lno */ );

        OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                          REGION_MPI_TEST,
                                          16 /* region name  */,
                                          17 /* alternative name */,
                                          0 /* description */,
                                          OTF2_REGION_ROLE_BARRIER,
                                          OTF2_PARADIGM_MPI,
                                          OTF2_REGION_FLAG_NONE,
                                          22 /* source file */,
                                          0 /* begin lno */,
                                          0 /* end lno */ );

        OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                          REGION_MPI_WAIT,
                                          18 /* region name  */,
                                          19 /* alternative name */,
                                          0 /* description */,
                                          OTF2_REGION_ROLE_FUNCTION,
                                          OTF2_PARADIGM_MPI,
                                          OTF2_REGION_FLAG_NONE,
                                          22 /* source file */,
                                          0 /* begin lno */,
                                          0 /* end lno */ );
//! [regions]

//! [systree]
        OTF2_GlobalDefWriter_WriteSystemTreeNode( global_def_writer,
                                                  0 /* id */,
                                                  20 /* name */,
                                                  21 /* class */,
                                                  OTF2_UNDEFINED_SYSTEM_TREE_NODE /* parent */ );
//! [systree]

//! [locations_and_groups]
        for ( int r = 0; r < size; r++ )
        {
            char process_name[ 32 ];
            snprintf( process_name, sizeof( process_name ), "MPI Rank %d", r );
            OTF2_GlobalDefWriter_WriteString( global_def_writer,
                                              27 + r,
                                              process_name );

            OTF2_GlobalDefWriter_WriteLocationGroup( global_def_writer,
                                                     r /* id */,
                                                     27 + r /* name */,
                                                     OTF2_LOCATION_GROUP_TYPE_PROCESS,
                                                     0 /* system tree */,
                                                     OTF2_UNDEFINED_LOCATION_GROUP /* creating process */ );

            OTF2_GlobalDefWriter_WriteLocation( global_def_writer,
                                                r /* id */,
                                                1 /* name */,
                                                OTF2_LOCATION_TYPE_CPU_THREAD,
                                                43 /* # events */,
                                                r /* location group */ );
        }
//! [locations_and_groups]

//! [comm_step_1]
        uint64_t comm_locations[ size ];
        for ( int r = 0; r < size; r++ )
        {
            comm_locations[ r ] = r;
        }
//! [comm_step_1]
//! [comm_step_2]
        OTF2_GlobalDefWriter_WriteGroup( global_def_writer,
                                         0 /* id */,
                                         24 /* name */,
                                         OTF2_GROUP_TYPE_COMM_LOCATIONS,
                                         OTF2_PARADIGM_MPI,
                                         OTF2_GROUP_FLAG_NONE,
                                         size,
                                         comm_locations );

        OTF2_GlobalDefWriter_WriteGroup( global_def_writer,
                                         1 /* id */,
                                         0 /* name */,
                                         OTF2_GROUP_TYPE_COMM_GROUP,
                                         OTF2_PARADIGM_MPI,
                                         OTF2_GROUP_FLAG_NONE,
                                         size,
                                         comm_locations );
//! [comm_step_2]

//! [comm_step_3]
        OTF2_GlobalDefWriter_WriteComm( global_def_writer,
                                        COMM_WORLD,
                                        23 /* name */,
                                        1 /* group */,
                                        OTF2_UNDEFINED_COMM /* parent */,
                                        OTF2_COMM_FLAG_CREATE_DESTROY_EVENTS /* flags */ );

        for ( int r = 0; r < size; r += 2 )
        {
            comm_locations[ r / 2 ] = r;
        }
        OTF2_GlobalDefWriter_WriteGroup( global_def_writer,
                                         2 /* id */,
                                         0 /* name */,
                                         OTF2_GROUP_TYPE_COMM_GROUP,
                                         OTF2_PARADIGM_MPI,
                                         OTF2_GROUP_FLAG_NONE,
                                         ( size + 1 ) / 2,
                                         comm_locations );

        OTF2_GlobalDefWriter_WriteComm( global_def_writer,
                                        COMM_SPLIT_0,
                                        24 /* name */,
                                        2 /* group */,
                                        COMM_WORLD,
                                        OTF2_COMM_FLAG_CREATE_DESTROY_EVENTS /* flags */ );

        for ( int r = 1; r < size; r += 2 )
        {
            comm_locations[ r / 2 ] = r;
        }
        OTF2_GlobalDefWriter_WriteGroup( global_def_writer,
                                         3 /* id */,
                                         0 /* name */,
                                         OTF2_GROUP_TYPE_COMM_GROUP,
                                         OTF2_PARADIGM_MPI,
                                         OTF2_GROUP_FLAG_NONE,
                                         size / 2,
                                         comm_locations );

        OTF2_GlobalDefWriter_WriteComm( global_def_writer,
                                        COMM_SPLIT_1,
                                        25 /* name */,
                                        3 /* group */,
                                        COMM_WORLD,
                                        OTF2_COMM_FLAG_CREATE_DESTROY_EVENTS /* flags */ );

        OTF2_GlobalDefWriter_WriteInterComm( global_def_writer,
                                             COMM_INTERCOMM,
                                             26 /* name */,
                                             2 /* groupA */,
                                             3 /* groupB */,
                                             COMM_WORLD,
                                             OTF2_COMM_FLAG_CREATE_DESTROY_EVENTS /* flags */ );
        OTF2_Archive_CloseGlobalDefWriter( archive,
                                           global_def_writer );
    }
//! [comm_step_3]
    MPI_Barrier( MPI_COMM_WORLD );

    OTF2_Archive_Close( archive );

    MPI_Finalize();

    return EXIT_SUCCESS;
}
//! [close]
