/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2013,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2017,
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
 * Implements the class for cuda instrumentation.
 */

#include <config.h>
#include "scorep_instrumenter_cuda.hpp"
#include "scorep_instrumenter_cmd_line.hpp"
#include "scorep_instrumenter_install_data.hpp"
#include "scorep_instrumenter_utils.hpp"
#include "scorep_instrumenter.hpp"
#include <scorep_config_tool_backend.h>
#include <scorep_config_tool_mpi.h>

#include <scorep_tools_utils.hpp>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <sstream>

#include <UTILS_Error.h>
#include <UTILS_IO.h>

/* **************************************************************************************
 * class SCOREP_Instrumenter_CudaAdapter
 * *************************************************************************************/
SCOREP_Instrumenter_CudaAdapter::SCOREP_Instrumenter_CudaAdapter( void )
    : SCOREP_Instrumenter_Adapter( SCOREP_INSTRUMENTER_ADAPTER_CUDA, "cuda" ),
    m_nvcc_compiler( false )
{
#if !HAVE_BACKEND( CUDA_SUPPORT )
    unsupported();
#endif
}

void
SCOREP_Instrumenter_CudaAdapter::printHelp( void )
{
    std::cout
        << "\
  --cuda          Enables CUDA instrumentation. Enabled by default, if the\n\
                  nvcc compiler is in use. In this case it also conflicts and\n\
                  thus automatically disables preprocessing.\n\
  --nocuda        Disables CUDA instrumentation."
        << std::endl;
}

void
SCOREP_Instrumenter_CudaAdapter::checkCompilerName( const std::string& compiler )
{
    if ( SCOREP_Instrumenter_CmdLine::isNvcc( compiler ) )
    {
        if ( m_usage == detect )
        {
            m_usage = enabled;
        }

        m_conflicts.push_back( SCOREP_INSTRUMENTER_ADAPTER_PREPROCESS );
        m_nvcc_compiler = true;
    }
}

bool
SCOREP_Instrumenter_CudaAdapter::checkCommand( const std::string& current,
                                               const std::string& next )
{
    bool skip_next = false;

    if ( current.substr( 0, 2 ) == "-l" )
    {
        std::string lib = current.substr( 2 );
        if ( lib.length() == 0 )
        {
            lib       = next;
            skip_next = true;
        }
        if ( ( m_usage == detect )
             && check_lib_name( lib, "cudart" ) )
        {
            m_usage = enabled;
        }
    }

    if ( ( current[ 0 ] != '-' ) &&
         is_cuda_file( current ) &&
         ( m_usage == detect ) )
    {
        m_usage = enabled;
    }

    return skip_next;
}

void
SCOREP_Instrumenter_CudaAdapter::checkObjects( SCOREP_Instrumenter& instrumenter )
{
    if ( m_usage != detect )
    {
        /* heuristic overwritten */
        return;
    }

    std::vector<std::string>* object_list = instrumenter.getInputFiles();
    std::stringstream         all_objects_stream;
    for ( std::vector<std::string>::iterator current_file = object_list->begin();
          current_file != object_list->end();
          current_file++ )
    {
        if ( is_object_file( *current_file ) || is_library( *current_file ) )
        {
            all_objects_stream << " " << *current_file;
        }
    }
    all_objects_stream << instrumenter.getCommandLine().getLibraryFiles();

    std::string command = SCOREP_NM " " + all_objects_stream.str() + " 2>/dev/null | "
                          SCOREP_EGREP " -l '(r fatbinData|U cuda|U __cuda)' >/dev/null 2>&1";
    if ( instrumenter.getCommandLine().getVerbosity() >= 1 )
    {
        std::cerr << command << std::endl;
    }
    int return_value = system( command.c_str() );
    if ( return_value == 0 )
    {
        m_usage = enabled;
    }
}

std::string
SCOREP_Instrumenter_CudaAdapter::getConfigToolFlag( SCOREP_Instrumenter_CmdLine& /* cmdLine */,
                                                    const std::string& /* inputFile */ )
{
    std::string flags;

    if ( isEnabled() )
    {
        flags += " --" + m_name;
    }
    else
    {
        flags += " --no" + m_name;
    }

    // if the nvcc compiler is used, we need to notify scorep-config about this
    if ( m_nvcc_compiler )
    {
        flags += " --nvcc";
    }

    return flags;
}

bool
SCOREP_Instrumenter_CudaAdapter::isNvcc( void )
{
    return m_nvcc_compiler;
}
