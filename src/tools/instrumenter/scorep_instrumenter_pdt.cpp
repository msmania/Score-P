/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2013, 2015, 2020, 2022,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2014, 2016-2017, 2021,
 * Technische Universitaet Dresden, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */

/**
 * @file
 *
 * Implements the class for PDT instrumentation.
 */

#include <config.h>
#include "scorep_instrumenter_pdt.hpp"
#include "scorep_instrumenter_cmd_line.hpp"
#include "scorep_instrumenter_install_data.hpp"
#include "scorep_instrumenter_selector.hpp"
#include "scorep_instrumenter_utils.hpp"
#include "scorep_instrumenter.hpp"
#include <scorep_config_tool_backend.h>
#include <scorep_config_tool_mpi.h>
#include <scorep_config_tool_shmem.h>

#include <scorep_tools_utils.hpp>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <sstream>

#include <UTILS_Error.h>
#include <UTILS_IO.h>

extern const int scorep_openmp_version;

/* **************************************************************************************
 * class SCOREP_Instrumenter_PdtAdapter
 * *************************************************************************************/
SCOREP_Instrumenter_PdtAdapter::SCOREP_Instrumenter_PdtAdapter( void )
    : SCOREP_Instrumenter_Adapter( SCOREP_INSTRUMENTER_ADAPTER_PDT, "pdt" )
{
    m_conflicts.push_back( SCOREP_INSTRUMENTER_ADAPTER_PREPROCESS );
    m_requires.push_back( SCOREP_INSTRUMENTER_ADAPTER_USER );
    m_default_off.push_back( SCOREP_INSTRUMENTER_ADAPTER_COMPILER );

    m_pdt_bin_path    = PDT;
    m_pdt_config_file = SCOREP_DATADIR "/SCOREP_Pdt_Instrumentation.conf";
    m_use_params      = true;

#if !HAVE( SCOREP_PDT )
    unsupported();
#endif
}

std::string
SCOREP_Instrumenter_PdtAdapter::getConfigToolFlag( SCOREP_Instrumenter_CmdLine& /* cmdLine */,
                                                   const std::string& /* inputFile */ )
{
    return "";
}

std::string
SCOREP_Instrumenter_PdtAdapter::precompile( SCOREP_Instrumenter&         instrumenter,
                                            SCOREP_Instrumenter_CmdLine& cmdLine,
                                            const std::string&           source_file )
{
    if ( is_cuda_file( source_file ) )
    {
        return source_file;
    }
    std::string extension = get_extension( source_file );
    if ( is_fortran_file( source_file ) )
    {
        std::transform( extension.begin(), extension.end(), extension.begin(), ::toupper );
    }
    std::string modified_file = remove_path( remove_extension( source_file ) +
                                             "_pdt" + extension );
    std::string       pdb_file = remove_path( remove_extension( source_file ) + ".pdb" );
    std::stringstream command;
    std::string       cflags = "`" + instrumenter.getConfigBaseCall() + " --inc` "
                               + instrumenter.getCompilerFlags();

    // Create database file
    if ( is_c_file( source_file ) )
    {
        command << m_pdt_bin_path << "/cparse " << source_file;
    }
    else if ( is_fortran_file( source_file ) )
    {
        command << m_pdt_bin_path << "/gfparse " << source_file;
    }
    else
    {
        command << m_pdt_bin_path << "/cxxparse " << source_file;
    }
    command << " " << cmdLine.getDefineFlags()
            << " " << cmdLine.getIncludeFlags()
            << " " << cflags;

    if ( SCOREP_Instrumenter_Selector::isParadigmSelected( "omp" ) )
    {
        command << " -D_OPENMP=" << scorep_openmp_version;
    }

    if ( SCOREP_Instrumenter_Selector::isParadigmSelected( "mpi" ) )
    {
        command << " -I" SCOREP_MPI_INCLUDE;
    }

    if ( SCOREP_Instrumenter_Selector::isParadigmSelected( "shmem" ) )
    {
        command << " -I" SCOREP_SHMEM_INCLUDE;
    }

    instrumenter.executeCommand( command.str() );

    // instrument source
    command.str( "" );
    command << m_pdt_bin_path << "/tau_instrumentor "
            << " " << pdb_file
            << " " << source_file
            << " -o " << modified_file
            << " -spec " << m_pdt_config_file
            << " " << m_params;

    if ( SCOREP_Instrumenter_Selector::isParadigmSelected( "mpi" ) )
    {
        command << " -I" SCOREP_MPI_INCLUDE;
    }

    if ( SCOREP_Instrumenter_Selector::isParadigmSelected( "shmem" ) )
    {
        command << " -I" SCOREP_SHMEM_INCLUDE;
    }

    instrumenter.executeCommand( command.str() );

    instrumenter.addTempFile( modified_file );
    instrumenter.addTempFile( pdb_file );

    return modified_file;
}

void
SCOREP_Instrumenter_PdtAdapter::setBuildCheck( SCOREP_Instrumenter_CmdLine& cmdLine )
{
    m_pdt_config_file = cmdLine.getPathToSrc() + "share/SCOREP_Pdt_Instrumentation.conf";
}

bool
SCOREP_Instrumenter_PdtAdapter::checkOption( const std::string& arg )
{
    const auto save_usage = m_usage;
    const auto ret        = SCOREP_Instrumenter_Adapter::checkOption( arg );
    if ( save_usage != m_usage && m_usage == enabled )
    {
        std::cerr << "[Score-P] WARNING: PDT instrumentation (--pdt) is deprecated. "
            "Consider using compiler or user instrumentation instead. ret =" << ret << " arg = " << arg << std::endl;
    }
    return ret;
}
