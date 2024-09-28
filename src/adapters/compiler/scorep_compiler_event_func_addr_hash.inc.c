/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2021-2023,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 */

#ifndef SCOREP_COMPILER_FUNC_ADDR_HASH_INC_C
#define SCOREP_COMPILER_FUNC_ADDR_HASH_INC_C

#include "scorep_compiler_func_addr_hash.h"
#include "scorep_compiler_demangle.h"

#include <SCOREP_FastHashtab.h>
#include <SCOREP_Addr2line.h>

#include <jenkins_hash.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <fnmatch.h>

/* Hash table for compiler instrumentation address lookup. The
   hashtable has 512 buckets, each chunk contains up to 3 key-value
   pairs. The hash table starts empty and gets filled at
   enter-function events. */

typedef uintptr_t           func_addr_hash_key_t;
typedef SCOREP_RegionHandle func_addr_hash_value_t;

#define FUNC_ADDR_HASH_EXPONENT 9

static inline bool
func_addr_hash_match_function_name( const char* functionName )
{
    return strncmp( functionName, "POMP", 4 ) == 0
           || ( strncmp( functionName, "Pomp", 4 ) == 0 )
           || ( strncmp( functionName, "pomp", 4 ) == 0 )
           || ( strncmp( functionName, "SCOREP_", 7 ) == 0 )
           || ( strncmp( functionName, "scorep_", 7 ) == 0 )
           || ( strncmp( functionName, "OTF2_", 5 ) == 0 )
           || ( strncmp( functionName, "otf2_", 5 ) == 0 )
           || ( strncmp( functionName, "cube_", 5 ) == 0 )
           || ( strncmp( functionName, "cubew_", 6 ) == 0 )
           || ( functionName[ 0 ] == '.' )
           || ( strstr( functionName, "DIR.OMP." ) )
           || ( strstr( functionName, ".extracted" ) )
           #if HAVE( SCOREP_COMPILER_CC_INTEL_ONEAPI ) || HAVE( SCOREP_COMPILER_CXX_INTEL_ONEAPI ) || HAVE( SCOREP_COMPILER_FC_INTEL_ONEAPI )
           || ( strstr( functionName, "_tree_reduce_" ) )
           #endif  /* Intel oneAPI compiler */
           || ( strncmp( functionName, "__omp", 5 ) == 0 )
           || ( strncmp( functionName, "virtual thunk", 13 ) == 0 )
           || ( strncmp( functionName, "non-virtual thunk", 17 ) == 0 )
           || ( strstr( functionName, "6Kokkos5Tools" ) )
           || ( strstr( functionName, "6Kokkos9Profiling" ) )
           || ( strstr( functionName, "Kokkos::Tools" ) )
           || ( strstr( functionName, "Kokkos::Profiling" ) )
           || ( strstr( functionName, ".omp_outlined" ) )
           || ( strstr( functionName, ".omp_outlined_debug__" ) )
           || ( fnmatch( "__nv_*_F[0-9]*L[0-9]*_[0-9]*", functionName, 0 ) == 0 )
           || ( fnmatch( "__sti___[0-9]*__*", functionName, 0 ) == 0 );
}

static inline bool
func_addr_hash_equals( func_addr_hash_key_t key1, func_addr_hash_key_t key2 )
{
    return key1 == key2;
}

static void*
func_addr_hash_allocate_chunk( size_t chunkSize )
{
    /* We might enter this function from an outlined OpenMP function
       in between fork and team-begin. Several threads compete to
       enter first. If a non-master thread is first, there is no valid
       location object. */
    void* chunk = SCOREP_Memory_AlignedMalloc( SCOREP_CACHELINESIZE, chunkSize );
    UTILS_BUG_ON( chunk == NULL );
    return chunk;
}

static void
func_addr_hash_free_chunk( void* chunk )
{
    SCOREP_Memory_AlignedFree( chunk );
}

static func_addr_hash_value_t
func_addr_hash_value_ctor( func_addr_hash_key_t* addr,
                           const void*           ctorDataUnused )
{
    void*       so_handle_unused;
    const char* so_file_name_unused;
    uintptr_t   so_base_addr_unused;
    uint16_t    so_token_unused;

    bool        scl_found;
    const char* file_name     = NULL;
    const char* function_name = NULL;
    unsigned    line_no       = SCOREP_INVALID_LINE_NO;

    SCOREP_Addr2line_LookupAddr( *addr,
                                 &so_handle_unused,
                                 &so_file_name_unused,
                                 &so_base_addr_unused,
                                 &so_token_unused,
                                 &scl_found,
                                 &file_name,
                                 &function_name,
                                 &line_no );

    func_addr_hash_value_t region = SCOREP_FILTERED_REGION;

    if ( scl_found && function_name != NULL )
    {
#if HAVE( PLATFORM_MAC )
        /* Skip these leading underscores on macOS */
        if ( '_' == function_name[ 0 ] )
        {
            function_name++;
        }
#endif  /*HAVE( PLATFORM_MAC )*/

        char* function_name_demangled;
        bool  use_address = ( *addr != 0 );
        /* Check mangled function names, since demangling them might
         * cause them to incorrectly pass the pattern checks */
        use_address &= !func_addr_hash_match_function_name( function_name );
        scorep_compiler_demangle( function_name, function_name_demangled );
        if ( function_name && use_address ) /* If demangling was successful */
        {
            use_address &= !func_addr_hash_match_function_name( function_name_demangled );
        }

        /* Usage of UTILS_IO_SimplifyPath on a copy of file_name not
         * needed as libbfd lookup provides absolute paths. */
        use_address &= ( !SCOREP_Filtering_Match( file_name, function_name_demangled, function_name ) );
        if ( use_address )
        {
            SCOREP_SourceFileHandle file_handle = SCOREP_Definitions_NewSourceFile( file_name );
            region = SCOREP_Definitions_NewRegion( function_name_demangled,
                                                   function_name,
                                                   file_handle,
                                                   line_no,
                                                   SCOREP_INVALID_LINE_NO,
                                                   SCOREP_PARADIGM_COMPILER,
                                                   SCOREP_REGION_FUNCTION );
#if HAVE( UTILS_DEBUG )
            UTILS_DEBUG( "[table-insert] %" PRIuPTR " used: %s(%s)@%s:%d",
                         *addr, function_name_demangled, function_name, file_name, line_no );
        }
        else
        {
            UTILS_DEBUG( "[table-insert] %" PRIuPTR " filtered: %s(%s)@%s:%d",
                         *addr, function_name_demangled, function_name, file_name, line_no );
#endif      /* HAVE( SCOREP_DEBUG ) */
        }
        scorep_compiler_demangle_free( function_name, function_name_demangled );
    }
    return region;
}


static inline uint32_t
func_addr_hash_bucket_idx( func_addr_hash_key_t key )
{
    uint32_t hash = jenkins_hash( &key, sizeof( key ), 0 ) & hashmask( FUNC_ADDR_HASH_EXPONENT );
    return hash;
}

static void
func_addr_hash_iterate_key_value_pair( func_addr_hash_key_t   key,
                                       func_addr_hash_value_t value )
{
}

SCOREP_HASH_TABLE_MONOTONIC( func_addr_hash, 10, hashsize( FUNC_ADDR_HASH_EXPONENT ) );

#undef FUNC_ADDR_HASH_EXPONENT


void
scorep_compiler_func_addr_hash_dlclose_cb( void*       soHandle,
                                           const char* soFileName,
                                           uintptr_t   soBaseAddr,
                                           uint16_t    soToken )
{
    UTILS_WARNING( "Shared object %s was dlclosed. It's addresses are not "
                   "removed from the compiler address hash table. If another "
                   "shared object is dlopened and addressees are reused, the "
                   "compiler adapter might enter/exit regions referring to "
                   "wrong source code locations", soFileName );
}


#endif /* SCOREP_COMPILER_FUNC_ADDR_HASH_INC_C */
