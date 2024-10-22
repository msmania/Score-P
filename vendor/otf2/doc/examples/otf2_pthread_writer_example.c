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

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include <otf2/otf2.h>

#include <otf2/OTF2_Pthread_Locks.h>

struct thread_data
{
    OTF2_Archive* archive;
    uint64_t      sequence;
    pthread_t     tid;
    uint64_t      lid;
};

static pthread_key_t tpd;

static OTF2_TimeStamp
get_time( void )
{
    struct thread_data* data = pthread_getspecific( tpd );
    return data->sequence++;
}

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

void*
event_writer( void* arg )
{
    struct thread_data* data = arg;
    pthread_setspecific( tpd, data );

    OTF2_EvtWriter* evt_writer = OTF2_Archive_GetEvtWriter( data->archive,
                                                            data->lid );

    OTF2_EvtWriter_Enter( evt_writer,
                          NULL,
                          get_time(),
                          0 /* region */ );
    OTF2_EvtWriter_Leave( evt_writer,
                          NULL,
                          get_time(),
                          0 /* region */ );

    OTF2_Archive_CloseEvtWriter( data->archive, evt_writer );

    return NULL;
}


int
main( int    argc,
      char** argv )
{
    int number_of_threads = 1;
    if ( argc > 1 )
    {
        number_of_threads = atoi( argv[ 1 ] );
    }
    pthread_key_create( &tpd, NULL );

    OTF2_Archive* archive = OTF2_Archive_Open( "ArchivePath",
                                               "ArchiveName",
                                               OTF2_FILEMODE_WRITE,
                                               1024 * 1024 /* event chunk size */,
                                               4 * 1024 * 1024 /* def chunk size */,
                                               OTF2_SUBSTRATE_POSIX,
                                               OTF2_COMPRESSION_NONE );

    OTF2_Archive_SetFlushCallbacks( archive, &flush_callbacks, NULL );

    OTF2_Archive_SetSerialCollectiveCallbacks( archive );

    OTF2_Pthread_Archive_SetLockingCallbacks( archive, NULL );

    OTF2_Archive_OpenEvtFiles( archive );

    struct thread_data* threads = calloc( number_of_threads, sizeof( *threads ) );
    for ( int i = 0; i < number_of_threads; i++ )
    {
        threads[ i ].archive = archive;
        threads[ i ].lid     = i;
        pthread_create( &threads[ i ].tid, NULL, event_writer, &threads[ i ] );
    }

    for ( int i = 0; i < number_of_threads; i++ )
    {
        pthread_join( threads[ i ].tid, NULL );
    }

    OTF2_Archive_CloseEvtFiles( archive );

    OTF2_Archive_OpenDefFiles( archive );
    for ( int thread = 0; thread < number_of_threads; thread++ )
    {
        OTF2_DefWriter* def_writer = OTF2_Archive_GetDefWriter( archive,
                                                                thread );
        OTF2_Archive_CloseDefWriter( archive, def_writer );
    }
    OTF2_Archive_CloseDefFiles( archive );

    OTF2_GlobalDefWriter* global_def_writer = OTF2_Archive_GetGlobalDefWriter( archive );

    OTF2_GlobalDefWriter_WriteClockProperties( global_def_writer,
                                               1 /* 1 tick per second */,
                                               0 /* epoch */,
                                               2 /* length */,
                                               OTF2_UNDEFINED_TIMESTAMP );

    OTF2_GlobalDefWriter_WriteString( global_def_writer, 0, "" );
    OTF2_GlobalDefWriter_WriteString( global_def_writer, 1, "Initial Process" );
    OTF2_GlobalDefWriter_WriteString( global_def_writer, 2, "Main Thread" );
    OTF2_GlobalDefWriter_WriteString( global_def_writer, 3, "MyFunction" );
    OTF2_GlobalDefWriter_WriteString( global_def_writer, 4, "Alternative function name (e.g. mangled one)" );
    OTF2_GlobalDefWriter_WriteString( global_def_writer, 5, "Computes something" );
    OTF2_GlobalDefWriter_WriteString( global_def_writer, 6, "MyHost" );
    OTF2_GlobalDefWriter_WriteString( global_def_writer, 7, "node" );

    OTF2_GlobalDefWriter_WriteRegion( global_def_writer,
                                      0 /* id */,
                                      3 /* region name  */,
                                      4 /* alternative name */,
                                      5 /* description */,
                                      OTF2_REGION_ROLE_FUNCTION,
                                      OTF2_PARADIGM_USER,
                                      OTF2_REGION_FLAG_NONE,
                                      0 /* source file */,
                                      0 /* begin lno */,
                                      0 /* end lno */ );

    OTF2_GlobalDefWriter_WriteSystemTreeNode( global_def_writer,
                                              0 /* id */,
                                              6 /* name */,
                                              7 /* class */,
                                              OTF2_UNDEFINED_SYSTEM_TREE_NODE /* parent */ );
    OTF2_GlobalDefWriter_WriteLocationGroup( global_def_writer,
                                             0 /* id */,
                                             1 /* name */,
                                             OTF2_LOCATION_GROUP_TYPE_PROCESS,
                                             0 /* system tree */,
                                             OTF2_UNDEFINED_LOCATION_GROUP /* creating process */ );

    for ( int i = 0; i < number_of_threads; i++ )
    {
        OTF2_StringRef name = 2;
        if ( i > 0 )
        {
            name = 7 + i;
            char name_buf[ 32 ];
            snprintf( name_buf, sizeof( name_buf ), "Pthread %d", i );
            OTF2_GlobalDefWriter_WriteString( global_def_writer, name, name_buf );
        }

        OTF2_GlobalDefWriter_WriteLocation( global_def_writer,
                                            i /* id */,
                                            name,
                                            OTF2_LOCATION_TYPE_CPU_THREAD,
                                            2 /* # events */,
                                            0 /* location group */ );
    }

    OTF2_Archive_Close( archive );

    pthread_key_delete( tpd );

    return EXIT_SUCCESS;
}
