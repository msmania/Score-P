/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2015, 2017,
 * Technische Universitaet Dresden, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 */

#include <config.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <SCOREP_InMeasurement.h>
#include <SCOREP_RuntimeManagement.h>
#include <SCOREP_Definitions.h>
#include <SCOREP_Events.h>

#define rot( x, k ) ( ( ( x ) << ( k ) ) | ( ( x ) >> ( 32 - ( k ) ) ) )
#define mix( a, b, c ) \
    { \
        a -= c;  a ^= rot( c, 4 );  c += b; \
        b -= a;  b ^= rot( a, 6 );  a += c; \
        c -= b;  c ^= rot( b, 8 );  b += a; \
        a -= c;  a ^= rot( c, 16 );  c += b; \
        b -= a;  b ^= rot( a, 19 );  a += c; \
        c -= b;  c ^= rot( b, 4 );  b += a; \
    }

#if HAVE( SAMPLING_SUPPORT )

static SCOREP_InterruptGeneratorHandle raise_irq_handle;

static void
handler_SIGUSR1( int        signalNumber,
                 siginfo_t* signalInfo,
                 void*      contextPtr )
{
    ( void )signalNumber;
    ( void )signalInfo;
    bool outside = SCOREP_IN_MEASUREMENT_TEST_AND_INCREMENT();
    SCOREP_ENTER_SIGNAL_CONTEXT();

    if ( outside )
    {
        SCOREP_Sample( raise_irq_handle, contextPtr );
    }

    SCOREP_EXIT_SIGNAL_CONTEXT();
    SCOREP_IN_MEASUREMENT_DECREMENT();
}

#else

#define raise( signal ) do { } while ( 0 )

#endif

void
__attribute__( ( constructor ) )
test_constructor( void );

void
test_constructor( void )
{
    if ( SCOREP_IS_MEASUREMENT_PHASE( PRE ) )
    {
        SCOREP_InitMeasurement();
    }

#if HAVE( SAMPLING_SUPPORT )

    raise_irq_handle = SCOREP_Definitions_NewInterruptGenerator(
        "manually",
        SCOREP_INTERRUPT_GENERATOR_MODE_COUNT,
        SCOREP_METRIC_BASE_DECIMAL,
        0,
        1 );

    struct sigaction signal_action;
    memset( &signal_action, 0, sizeof( signal_action ) );
    signal_action.sa_sigaction = handler_SIGUSR1;
    signal_action.sa_flags     = SA_SIGINFO | SA_RESTART;
    sigfillset( &signal_action.sa_mask );
    if ( 0 != sigaction( SIGUSR1, &signal_action, NULL ) )
    {
        UTILS_WARNING( "Failed to install signal handler for sampling." );
    }

#endif

    raise( SIGUSR1 );
}

int
main( int ac, char* av[] )
{
    if ( SCOREP_IS_MEASUREMENT_PHASE( PRE ) )
    {
        SCOREP_InitMeasurement();
    }
    uint32_t a = 0, b = 0, c = 0;

    const char* arg = ac > 2 ? av[ 1 ] : "abc";
    size_t      len = strlen( arg );
    size_t      i   = 0;

    raise( SIGUSR1 );

    a += arg[ i++ % len ];
    b += arg[ i++ % len ];
    c += arg[ i++ % len ];
    mix( a, b, c );

    raise( SIGUSR1 );

    return 0;
}

/*
 * expected:
 */
