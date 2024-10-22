/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2023                                                **
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
 * \file Predicates.cpp
 * \brief Defines a set of functions-testers for different kind of regions.
 *
 */
#include "config.h"

#include <algorithm>
#include <cctype>
#include <functional>

#include "Predicates.h"
#include "CubeRegion.h"

using namespace std;


//--- Helper functions ------------------------------------------------------


/**
 * STL conform lowercase in cube:: namespace.
 */
string
cube::lowercase( const string& str )
{
    string result( str );

    transform( str.begin(), str.end(), result.begin(), [ ]( unsigned char c ){
        return std::tolower( c );
    } );

    return result;
}


//--- Predicates ------------------------------------------------------------
/**
 * Is a region related to EPIK measurement?
 */
bool
cube::is_epk( const Region* region )
{
    return region->get_name()  == "TRACING" &&
           region->get_mod()   == "EPIK"    &&
           region->get_descr() == "EPIK";
}

/**
 * Is a region a general  User code?
 */

bool
cube::is_usr( const Region* region )
{
    return ( region->get_descr() == "USR" ) || ( region->get_descr() == "compiler" );
}
/**
 * Is a region a general  OpenMP code?
 */
bool
cube::is_omp( const Region* region )
{
    const string omp_parallel_region = "!$omp parallel @";
    return ( region->get_descr() == "OMP" )
           ||
           ( region->get_descr() == "pomp" )
           ||
           ( region->get_mod() == "OMP" )
           ||
           (
        ( region->get_mod() != "OMP" )
        &&
        ( region->get_mod() != "pomp" )
        &&
        ( region->get_mod() != "MPI" )
        &&
        ( region->get_mod() != "mpi" )
        &&
        ( region->get_mod() != "EPIK" )
        &&
        ( region->get_name().compare( 0, omp_parallel_region.length(),  omp_parallel_region ) == 0 )
           );
    ;
}
/**
 * Is a region a general  MPI code?
 */
bool
cube::is_mpi( const Region* region )
{
    return ( region->get_descr() == "MPI" ) || ( region->get_descr() == "mpi" ) || ( region->get_mod() == "MPI" );
}

/**
 * Is a region a general  OpenMP-API code?
 */
bool
cube::is_omp_api( const string& region )
{
    const string omp_api1 = "omp_";
    const string omp_api2 = "!$omp ";
    return ( region.compare( 0, omp_api1.length(), omp_api1 ) == 0 ) || ( region.compare( 0, omp_api2.length(), omp_api2 ) == 0 );
}
/**
 * Is a region a flush in  OpenMP code?
 */
bool
cube::is_omp_flush( const string& region )
{
    const string omp_flush = "!$omp flush";
    return region.compare( 0, omp_flush.length(), omp_flush ) == 0;
}
/**
 * Is a region a atom of  OpenMP code?
 */
bool
cube::is_omp_atomic( const string& region )
{
    const string omp_atomic = "!$omp atomic";
    return region.compare( 0, omp_atomic.length(), omp_atomic ) == 0;
}
/**
 * Is a region a critical part of  OpenMP code?
 */
bool
cube::is_omp_critical( const string& region )
{
    const string omp_critical = "!$omp critical";
    const string omp_sblock   = " sblock";
    return is_omp_atomic( region ) ||
           ( ( region.compare( 0, omp_critical.length(), omp_critical ) == 0 ) &&
             ( region.compare( omp_critical.length(), omp_sblock.length(), omp_sblock ) != 0 ) );
}
/**
 * Is a region a asynchron barrier of  OpenMP code?
 */
bool
cube::is_omp_ebarrier( const string& region )
{
    const string omp_ebarrier = "!$omp barrier";
    return region.compare( 0, omp_ebarrier.length(), omp_ebarrier ) == 0;
}

/**
 * Is a region a asynchron barrier of  OpenMP code?
 */
bool
cube::is_omp_ibarrier( const string& region )
{
    const string omp_ibarrier1 = "!$omp ibarrier";
    const string omp_ibarrier2 = "!$omp implicit barrier";
    return ( region.compare( 0, omp_ibarrier1.length(), omp_ibarrier1 ) == 0 ) ||
           ( region.compare( 0, omp_ibarrier2.length(), omp_ibarrier2 ) == 0 );
}
/**
 * Is a region lock of  OpenMP code?
 */
bool
cube::is_omp_lock_api( const string& region )
{
    const string suffix = "_lock";
    return is_omp_api( region ) &&
           ( region.compare( region.length() - suffix.length(),
                             suffix.length(), suffix ) == 0 );
}
/**
 * Is a region PARALLEL OpenMP code?
 */
bool
cube::is_omp_parallel( const string& region )
{
    const string omp_parallel = "!$omp parallel @";
    return region.compare( 0, omp_parallel.length(), omp_parallel ) == 0;
}

/**
 * Is a region MPI-API?
 */
bool
cube::is_mpi_api( const string& region )
{
    return region.compare( 0, 4, "mpi_" ) == 0;
}

/**
 * Is a region COLLECTIVE MPI-communication?
 */
bool
cube::is_mpi_coll( const string& region )
{
    return region == "mpi_allgather"            ||
           region == "mpi_allgatherv"           ||
           region == "mpi_allreduce"            ||
           region == "mpi_alltoall"             ||
           region == "mpi_alltoallv"            ||
           region == "mpi_alltoallw"            ||
           region == "mpi_bcast"                ||
           region == "mpi_exscan"               ||
           region == "mpi_gather"               ||
           region == "mpi_gatherv"              ||
           region == "mpi_reduce"               ||
           region == "mpi_reduce_scatter"       ||
           region == "mpi_reduce_scatter_block" ||
           region == "mpi_scan"                 ||
           region == "mpi_scatter"              ||
           region == "mpi_scatterv";
}


bool
cube::is_mpi_p2p( const string& region )
{
    if ( !is_mpi_api( region ) )
    {
        return false;
    }

    string suffix = region.substr( 4 );
    return suffix.find( "buffer" )        != string::npos ||
           suffix.find( "cancel" )        != string::npos ||
           suffix.find( "get_count" )     != string::npos ||
           suffix.find( "probe" )         != string::npos ||
           suffix.find( "recv" )          != string::npos ||
           suffix.find( "request" )       != string::npos ||
           suffix.find( "send" )          != string::npos ||
           suffix.compare( 0, 4, "test" ) == 0 ||
           suffix.compare( 0, 4, "wait" ) == 0 ||
           ( suffix.substr( 0, 3 )          != "win" && (
                 suffix.find( "start" )        != string::npos ) );
}

/**
 * Is a region a "Point-to-Point MPI" communication?
 */
bool
cube::is_mpi_rma( const string& region )
{
    if ( !is_mpi_api( region ) )
    {
        return false;
    }

    string suffix = region.substr( 4 );
    return suffix == "get" ||
           suffix == "put" ||
           suffix == "accumulate";
}

/**
 * Is a region SYNCHRONISATIONS code?
 */
bool
cube::is_mpi_sync( const string& region )
{
    return is_mpi_sync_coll( region ) ||
           is_mpi_sync_rma( region );
}


bool
cube::is_mpi_sync_coll( const string& region )
{
    return region == "mpi_barrier";
}
/**
 * Is a region MPI_IO code?
 */

bool
cube::is_mpi_sync_rma( const string& region )
{
    return is_mpi_sync_rma_active( region ) ||
           is_mpi_sync_rma_passive( region );
}


bool
cube::is_mpi_sync_rma_active( const string& region )
{
    return ( region == "mpi_win_post" ) ||
           ( region == "mpi_win_wait" ) ||
           ( region == "mpi_win_start" ) ||
           ( region == "mpi_win_complete" ) ||
           ( region == "mpi_win_fence" );
}

bool
cube::is_mpi_sync_rma_fence( const std::string& region )
{
    return region == "mpi_win_fence";
}


bool
cube::is_mpi_sync_rma_gats_access( const std::string& region )
{
    return region == "mpi_win_start";
}


bool
cube::is_mpi_sync_rma_gats_exposure( const std::string& region )
{
    return region == "mpi_win_post";
}


bool
cube::is_mpi_sync_rma_passive( const string& region )
{
    return ( region == "mpi_win_lock" ) ||
           ( region == "mpi_win_unlock" );
}


bool
cube::is_mpi_comm_rma_put( const std::string& region )
{
    return ( region == "mpi_accumulate" ) ||
           ( region == "mpi_put" );
}


bool
cube::is_mpi_comm_rma_get( const std::string& region )
{
    return region ==  "mpi_get";
}


bool
cube::is_mpi_io( const string& region )
{
    return region.compare( 0, 8, "mpi_file" ) == 0;
}

/**
 * Is a region MPI_COLLECTIVE_IO code?
 */
bool
cube::is_mpi_coll_io( const string& region )
{
    if ( !is_mpi_io( region ) )
    {
        return false;
    }

    string suffix = region.substr( 8 );

    // MPI_File_set_errhandler is the only "_set" routine that is
    // non-collective, i.e., ignore it here.
    if ( suffix.compare( 0, 8, "_set_err" ) == 0 )
    {
        return false;
    }

    return suffix == "_open" ||
           suffix == "_close" ||
           suffix == "_preallocate" ||
           suffix == "_seek_shared" ||
           suffix == "_sync" ||
           suffix.find( "_all" ) != string::npos ||
           suffix.find( "_ordered" ) != string::npos ||
           suffix.find( "_set" ) != string::npos;
}

/**
 * Is a region an MPI File I/O read operation?
 */
bool
cube::is_mpi_io_read( const string& region )
{
    if ( !is_mpi_io( region ) )
    {
        return false;
    }

    return region.find( "read" ) != string::npos;
}

/**
 * Is a region an MPI File I/O write operation?
 */
bool
cube::is_mpi_io_write( const string& region )
{
    if ( !is_mpi_io( region ) )
    {
        return false;
    }

    return region.find( "write" ) != string::npos;
}


/**
 * Is a region MPI initialization or finalization code?
 */
bool
cube::is_mpi_init( const string& region )
{
    return region == "mpi_init" ||
           region == "mpi_init_thread" ||
           region == "mpi_finalize";
}
