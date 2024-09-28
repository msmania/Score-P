/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2013,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2013,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2014, 2023,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2013,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2014,
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

#include <otf2/otf2.h>

#include <otf2/OTF2_OpenMP_Locks.h>

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

static OTF2_CallbackCode
Enter_print( uint64_t            locationID,
             uint64_t            time,
             uint64_t            eventPosition,
             void*               userData,
             OTF2_AttributeList* attributeList,
             OTF2_RegionRef      region )
{
    printf( "Entering region %u at location %" PRIu64 " at time %" PRIu64 ".\n",
            region, location, time );

    return OTF2_CALLBACK_SUCCESS;
}

static OTF2_CallbackCode
Leave_print( uint64_t            locationID,
             uint64_t            time,
             uint64_t            eventPosition,
             void*               userData,
             OTF2_AttributeList* attributeList,
             OTF2_RegionRef      region )
{
    printf( "Leaving region %u at location %" PRIu64 " at time %" PRIu64 ".\n",
            region, location, time );

    return OTF2_CALLBACK_SUCCESS;
}

struct vector
{
    size_t   capacity;
    size_t   size;
    uint64_t members[];
};

static OTF2_CallbackCode
register_location( void*                 userData,
                   OTF2_LocationRef      location,
                   OTF2_StringRef        name,
                   OTF2_LocationType     locationType,
                   uint64_t              numberOfEvents,
                   OTF2_LocationGroupRef locationGroup )
{
    struct vector* locations = userData;

    if ( locations->size == locations->capacity )
    {
        return OTF2_CALLBACK_INTERRUPT;
    }

    locations->members[ locations->size++ ] = location;

    return OTF2_CALLBACK_SUCCESS;
}

int
main( int    argc,
      char** argv )
{
    OTF2_Reader* reader = OTF2_Reader_Open( argv[ 1 ] );

    OTF2_OpenMP_Reader_SetLockingCallbacks( reader );

    OTF2_Reader_SetSerialCollectiveCallbacks( reader );

    uint64_t number_of_locations;
    OTF2_Reader_GetNumberOfLocations( reader,
                                      &number_of_locations );
    struct vector* locations = malloc( sizeof( *locations )
                                       + number_of_locations
                                       * sizeof( *locations->members ) );
    locations->capacity = number_of_locations;
    locations->size     = 0;

    OTF2_GlobalDefReader* global_def_reader = OTF2_Reader_GetGlobalDefReader( reader );

    OTF2_GlobalDefReaderCallbacks* global_def_callbacks = OTF2_GlobalDefReaderCallbacks_New();
    OTF2_GlobalDefReaderCallbacks_SetLocationCallback( global_def_callbacks,
                                                       register_location );
    OTF2_Reader_RegisterGlobalDefCallbacks( reader,
                                            global_def_reader,
                                            global_def_callbacks,
                                            locations );
    OTF2_GlobalDefReaderCallbacks_Delete( global_def_callbacks );

    uint64_t definitions_read = 0;
    OTF2_Reader_ReadAllGlobalDefinitions( reader,
                                          global_def_reader,
                                          &definitions_read );

    for ( size_t i = 0; i < locations->size; i++ )
    {
        OTF2_Reader_SelectLocation( reader, locations->members[ i ] );
    }

    bool successful_open_def_files =
        OTF2_Reader_OpenDefFiles( reader ) == OTF2_SUCCESS;
    OTF2_Reader_OpenEvtFiles( reader );

    for ( size_t i = 0; i < locations->size; i++ )
    {
        if ( successful_open_def_files )
        {
            OTF2_DefReader* def_reader =
                OTF2_Reader_GetDefReader( reader, locations->members[ i ] );
            if ( def_reader )
            {
                uint64_t def_reads = 0;
                OTF2_Reader_ReadAllLocalDefinitions( reader,
                                                     def_reader,
                                                     &def_reads );
                OTF2_Reader_CloseDefReader( reader, def_reader );
            }
        }
    }

    if ( successful_open_def_files )
    {
        OTF2_Reader_CloseDefFiles( reader );
    }

    OTF2_EvtReaderCallbacks* event_callbacks = OTF2_EvtReaderCallbacks_New();
    OTF2_EvtReaderCallbacks_SetEnterCallback( event_callbacks,
                                              &Enter_print );
    OTF2_EvtReaderCallbacks_SetLeaveCallback( event_callbacks,
                                              &Leave_print );

    #pragma omp parallel shared(reader)
    {
        #pragma omp for
        for ( size_t i = 0; i < locations->size; i++ )
        {
            OTF2_EvtReader* evt_reader =
                OTF2_Reader_GetEvtReader( reader, locations->members[ i ] );

            OTF2_Reader_RegisterEvtCallbacks( reader,
                                              evt_reader,
                                              event_callbacks,
                                              NULL );

            uint64_t events_read = 0;
            OTF2_Reader_ReadAllLocalEvents( reader,
                                            evt_reader,
                                            &events_read );

            OTF2_Reader_CloseEvtReader( reader,
                                        evt_reader );
        }
    }

    OTF2_EvtReaderCallbacks_Delete( event_callbacks );

    OTF2_Reader_CloseEvtFiles( reader );

    OTF2_Reader_Close( reader );

    free( locations );

    return EXIT_SUCCESS;
}
