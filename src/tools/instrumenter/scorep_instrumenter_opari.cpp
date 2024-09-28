/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2013,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2013,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2015, 2017, 2019,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2013,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2013, 2015, 2021-2022,
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

/**
 * @file
 */

#include <config.h>
#include <scorep_config_tool_backend.h>
#include <scorep_config_tool_mpi.h>
#include "scorep_instrumenter_opari.hpp"
#include "scorep_instrumenter_cmd_line.hpp"
#include "scorep_instrumenter_utils.hpp"
#include "scorep_instrumenter_install_data.hpp"
#include "scorep_instrumenter.hpp"

#include <scorep_tools_utils.hpp>

#include <algorithm>


/* **************************************************************************************
 * class SCOREP_Instrumenter_OpariAdapter
 * *************************************************************************************/
SCOREP_Instrumenter_OpariAdapter::SCOREP_Instrumenter_OpariAdapter( void )
    : SCOREP_Instrumenter_Adapter( SCOREP_INSTRUMENTER_ADAPTER_OPARI, "OPARI2" )
{
    m_default_on.push_back( SCOREP_INSTRUMENTER_ADAPTER_PREPROCESS );

    m_opari        = OPARI;
    m_opari_script = "`" OPARI_CONFIG " --region-initialization`";
    m_opari_config = OPARI_CONFIG;
    m_c_compiler   = SCOREP_CC;
    m_nm           = "`" OPARI_CONFIG " --nm`";
    m_openmp       = detect;
    m_parallel     = detect;
    m_pomp         = detect;
    m_use_tpd      = false;
#if SCOREP_BACKEND_COMPILER_MIC
    m_mmic_set = false;
#endif  /* SCOREP_BACKEND_COMPILER_MIC */
}

bool
SCOREP_Instrumenter_OpariAdapter::checkOption( const std::string& arg )
{
    if ( arg == "--openmp" )
    {
        m_openmp = enabled;
        return true;
    }
    if ( arg == "--noopenmp" )
    {
        m_openmp = disabled;
        return true;
    }
    if ( arg == "--pomp" )
    {
        m_pomp = enabled;
        return true;
    }
    if ( arg == "--nopomp" )
    {
        m_pomp = disabled;
        return true;
    }
    if ( arg.substr( 0, 8 ) == "--opari=" )
    {
        m_usage   = enabled;
        m_params += " " + arg.substr( 8, std::string::npos );
        return true;
    }
    /** Undocumented option */
    if ( arg == "--noopari" )
    {
        m_usage = disabled;
        return true;
    }
    return false;
}

bool
SCOREP_Instrumenter_OpariAdapter::isEnabled( void ) const
{
    return ( m_parallel == enabled ) ||
           ( m_openmp == enabled ) ||
           ( m_pomp == enabled ) ||
           ( m_usage == enabled );
}

std::string
SCOREP_Instrumenter_OpariAdapter::getConfigToolFlag( SCOREP_Instrumenter_CmdLine& /* cmdLine */,
                                                     const std::string& /* inputFile */ )
{
    if ( m_pomp == enabled )
    {
        return " --pomp";
    }
    return "";
}

void
SCOREP_Instrumenter_OpariAdapter::printHelp( void )
{
    std::cout << "  --pomp          Enables OPARI2 pomp user instrumentation. By default, it also\n";
    std::cout << "                  enables preprocessing.\n";
    std::cout << "  --nopomp        Disables OPARI2 pomp user instrumentation (Default).\n";
    std::cout << "  --openmp        Enables OPARI2 instrumentation of OpenMP directives. By default,\n";
    std::cout << "                  it also enables preprocessing (Default for compile units\n";
    std::cout << "                  with enabled OpenMP support during the compilation).\n";
#if HAVE( BACKEND_SCOREP_OMPT_SUPPORT )
    std::cout << "                  Conflicts with --thread=omp:ompt.\n";
#endif // BACKEND_SCOREP_OMPT_SUPPORT
    std::cout << "  --noopenmp      Disables OPARI2 instrumentation of OpenMP directives.\n";
    std::cout << "                  Note: To ensure thread-safe execution of the measurement,\n";
    std::cout << "                  parallel regions still need to be tracked and will appear\n";
    std::cout << "                  in the results (Default for compile units without OpenMP\n";
    std::cout << "                  enabled compilation).\n";
    std::cout << "  --opari=<parameter-list>\n";
    std::cout << "                  Pass options to the source-to-source instrumenter OPARI2\n";
    std::cout << "                  to have finer control over the instrumentation process.\n";
    std::cout << "                  Enables OPARI2 instrumentation.\n";
    std::cout << "                  Please refer to the OPARI2 user documentation for more\n";
    std::cout << "                  details.\n";
}


std::string
SCOREP_Instrumenter_OpariAdapter::precompile( SCOREP_Instrumenter&         instrumenter,
                                              SCOREP_Instrumenter_CmdLine& cmdLine,
                                              const std::string&           source_file )
{
    /* For Fortran source files, the extension must be in upper case to use the
       C-preprocessor */
    std::string extension = get_extension( source_file );
    if ( is_fortran_file( source_file ) )
    {
        std::transform( extension.begin(),
                        extension.end(),
                        extension.begin(),
                        ::toupper );
    }

    std::string modified_file = remove_path( remove_extension( source_file )
                                             + ".opari"
                                             + extension );

    invoke_opari( instrumenter, source_file, modified_file );
    instrumenter.addTempFile( modified_file );
    instrumenter.addTempFile( remove_path( source_file + ".opari.inc" ) );
    return modified_file;
}

void
SCOREP_Instrumenter_OpariAdapter::prelink( SCOREP_Instrumenter&         instrumenter,
                                           SCOREP_Instrumenter_CmdLine& cmdLine )
{
    // When linking a shared library, it must not contain a pomp init file
    if ( cmdLine.isTargetSharedLib() )
    {
        return;
    }

    std::vector<std::string>* input_files  = instrumenter.getInputFiles();
    std::string               output_name  = cmdLine.getOutputName();
    std::string               current_file = "";
    std::string               object_files = "";
    std::string               init_source  = output_name + ".opari2_init.c";
    std::string               init_object  = output_name + ".opari2_init.o";

    // Compile list of library and object files
    for ( std::vector<std::string>::iterator current_file = input_files->begin();
          current_file != input_files->end();
          current_file++ )
    {
        if ( is_object_file( *current_file ) || is_library( *current_file ) )
        {
            object_files += " " + *current_file;
        }
    }

    object_files += cmdLine.getLibraryFiles();

    // Create and compile the POMP2 init file.
    invoke_awk_script( instrumenter, object_files, init_source );
    compile_init_file( instrumenter, init_source, init_object );

    /* Add the object file for POMP2 initialization to the input files for linking.
       Prepend it to the front of input symbols, because some compilers do not
       find the POMP_Init_<ID> symbols (in libraries) if it is appended.
       See  ticket #627. */
    instrumenter.prependInputFile( init_object );
}

void
SCOREP_Instrumenter_OpariAdapter::setBuildCheck( SCOREP_Instrumenter_CmdLine& cmdLine )
{
    #if !HAVE( EXTERNAL_OPARI2 )
    m_opari_config = cmdLine.getPathToBinary() +
                     "../vendor/opari2/build-frontend/opari2-config --build-check";
    m_opari = cmdLine.getPathToBinary() +
              "../vendor/opari2/build-frontend/opari2";
    #endif
    m_nm           = "`" + m_opari_config +  " --nm`";
    m_opari_script = "`" + m_opari_config + " --region-initialization`";
}

bool
SCOREP_Instrumenter_OpariAdapter::checkCommand( const std::string& current,
                                                const std::string& next )
{
    std::string arg = ( current == "-f" ? current + next : current );

    if ( SCOREP_Instrumenter_InstallData::isArgForFreeform( arg ) )
    {
        set_fortran_form( true );
        return current == "-f";
    }
    if ( SCOREP_Instrumenter_InstallData::isArgForFixedform( arg ) )
    {
        set_fortran_form( false );
        return current == "-f";
    }

#if SCOREP_BACKEND_COMPILER_MIC
    if ( arg == "-mmic" )
    {
        m_mmic_set = true;
    }
#endif  /* SCOREP_BACKEND_COMPILER_MIC */

    return false;
}

void
SCOREP_Instrumenter_OpariAdapter::setTpdMode( const bool use_tpd )
{
    m_use_tpd = use_tpd;
}

void
SCOREP_Instrumenter_OpariAdapter::checkDefaults( void )
{
    if ( m_openmp == detect )
    {
        m_openmp = disabled;
    }
    if ( m_parallel == detect )
    {
        /* Usually parallel regions are instrumented whenever we have
           OpenMP construct instrumentation. However, if we have
           --thread=none && --nopenmp, only m_parallel should be enabled.
         */
        m_parallel = m_openmp;
    }
    if ( m_pomp == detect )
    {
        m_pomp = disabled;
    }
    if ( ( m_parallel == enabled ) || ( m_pomp == enabled ) )
    {
        m_usage = enabled;
        SCOREP_Instrumenter_Adapter::checkDefaults();
    }
}

void
SCOREP_Instrumenter_OpariAdapter::enableOpenmpDefault( void )
{
    m_parallel = enabled;
    if ( m_openmp != disabled )
    {
        m_openmp = enabled;
    }
}

/* ------------------------------------------------------------------- private methods */
static inline void
add_param( std::string&       command,
           const std::string& param,
           const std::string& prefix )
{
    if ( command.find( prefix ) == std::string::npos )
    {
        command += param + " ";
    }
}

void
SCOREP_Instrumenter_OpariAdapter::invoke_opari( SCOREP_Instrumenter& instrumenter,
                                                const std::string&   input_file,
                                                const std::string&   output_file )
{
    /*
     * tpd_mangling_scheme is used in opari2 option --omp-tpd-mangling.
     * This option is only used if the compiler doesn't support OpenMP ancestry
     * functions. These functions were introduced in OpenMP 3.0.
     * --omp-tpd-mangling=clang is not implemented in opari2. But as ancestry
     * is the default since scorep 4.0 and supported by clang, tpd options
     * wont get used.
     */
    std::string tpd_mangling_scheme;
    std::string language_flags;

    if ( is_c_file( input_file ) )
    {
#if SCOREP_BACKEND_COMPILER_CC_CRAY
        tpd_mangling_scheme = "cray";
#elif SCOREP_BACKEND_COMPILER_CC_GNU
        tpd_mangling_scheme = "gnu";
#elif SCOREP_BACKEND_COMPILER_CC_IBM
        tpd_mangling_scheme = "ibm";
#elif SCOREP_BACKEND_COMPILER_CC_INTEL
        tpd_mangling_scheme = "intel";
#elif SCOREP_BACKEND_COMPILER_CC_PGI
        tpd_mangling_scheme = "pgi";
#elif SCOREP_BACKEND_COMPILER_CC_FUJITSU
        tpd_mangling_scheme = "fujitsu";
#elif SCOREP_BACKEND_COMPILER_CC_CLANG || SCOREP_BACKEND_COMPILER_CC_INTEL_ONEAPI
        tpd_mangling_scheme = "clang";
#else
#error "Missing OPARI specific OpenMP compiler handling for your C compiler, extension required."
#endif
    }
    else if ( is_cpp_file( input_file ) )
    {
#if SCOREP_BACKEND_COMPILER_CXX_CRAY
        tpd_mangling_scheme = "cray";
#elif SCOREP_BACKEND_COMPILER_CXX_GNU
        tpd_mangling_scheme = "gnu";
#elif SCOREP_BACKEND_COMPILER_CXX_IBM
        tpd_mangling_scheme = "ibm";
#elif SCOREP_BACKEND_COMPILER_CXX_INTEL
        tpd_mangling_scheme = "intel";
#elif SCOREP_BACKEND_COMPILER_CXX_PGI
        tpd_mangling_scheme = "pgi";
#elif SCOREP_BACKEND_COMPILER_CXX_FUJITSU
        tpd_mangling_scheme = "fujitsu";
#elif SCOREP_BACKEND_COMPILER_CXX_CLANG || SCOREP_BACKEND_COMPILER_CXX_INTEL_ONEAPI
        tpd_mangling_scheme = "clang";
#else
#error "Missing OPARI specific OpenMP compiler handling for your C++ compiler, extension required."
#endif
    }
    else if ( is_fortran_file( input_file ) )
    {
#if SCOREP_BACKEND_HAVE_FC_COMPILER
#if SCOREP_BACKEND_COMPILER_FC_CRAY
        tpd_mangling_scheme = "cray";
        language_flags      = " --nosrc";
#elif SCOREP_BACKEND_COMPILER_FC_GNU
        tpd_mangling_scheme = "gnu";
#elif SCOREP_BACKEND_COMPILER_FC_IBM
        tpd_mangling_scheme = "ibm";
#elif SCOREP_BACKEND_COMPILER_FC_INTEL
        tpd_mangling_scheme = "intel";
#elif SCOREP_BACKEND_COMPILER_FC_PGI
        tpd_mangling_scheme = "pgi";
#elif SCOREP_BACKEND_COMPILER_FC_FUJITSU
        tpd_mangling_scheme = "fujitsu";
#elif SCOREP_BACKEND_COMPILER_FC_CLANG || SCOREP_BACKEND_COMPILER_FC_INTEL_ONEAPI
        tpd_mangling_scheme = "clang";
#else
#error "Missing OPARI specific OpenMP compiler handling for your Fortran compiler, extension required."
#endif
#endif  /* SCOREP_BACKEND_HAVE_FC_COMPILER */
    }

    std::string command = m_opari + m_params + language_flags + " ";

    add_param( command, "--omp-task-untied=keep", "--omp-task-untied=" );
    if ( m_use_tpd )
    {
        // Combination of cc/CC Clang and ftn Cray won't use tpd
        add_param( command, "--omp-tpd", "--omp-tpd" );
        add_param( command,
                   "--omp-tpd-mangling=" + tpd_mangling_scheme,
                   "--omp-tpd-mangling=" );
    }

    SCOREP_Instrumenter_Adapter* adapter = getAdapter( SCOREP_INSTRUMENTER_ADAPTER_PDT );
    if ( ( adapter != NULL ) && adapter->isEnabled() && is_fortran_file( input_file ) )
    {
        add_param( command, "--nosrc", "--nosrc" );
    }

    adapter = getAdapter( SCOREP_INSTRUMENTER_ADAPTER_PREPROCESS );
    if ( ( adapter != NULL ) && adapter->isEnabled() )
    {
        add_param( command, "--preprocessed", "--preprocessed" );
    }

    std::string disable = "";
    if ( m_pomp == disabled )
    {
        if ( disable != "" )
        {
            disable += "+";
        }
        disable += "pomp";
    }
    if ( m_openmp == disabled )
    {
        if ( disable != "" )
        {
            disable += "+";
        }
        disable += "omp";
        if ( m_parallel == disabled )
        {
            disable += ":all";
        }
    }
    if ( disable != "" )
    {
        command += "--disable=" + disable + " ";
    }

    command += input_file + " " + output_file;

    instrumenter.executeCommand( command );
}

void
SCOREP_Instrumenter_OpariAdapter::invoke_awk_script( SCOREP_Instrumenter& instrumenter,
                                                     const std::string&   object_files,
                                                     const std::string&   output_file )
{
    std::string command = m_nm + " " + object_files
#if HAVE( PLATFORM_MAC )
                          + " | sed -e 's/ _/ /'"
#endif
                          + " | " + m_opari_script
                          + " > " + output_file;
    instrumenter.executeCommand( command );

    instrumenter.addTempFile( output_file );
}

void
SCOREP_Instrumenter_OpariAdapter::compile_init_file( SCOREP_Instrumenter& instrumenter,
                                                     const std::string&   input_file,
                                                     const std::string&   output_file )
{
    std::string target_flags = "";

#if SCOREP_BACKEND_COMPILER_MIC && HAVE( MIC_SUPPORT )
    if ( m_mmic_set )
    {
        target_flags += " -mmic ";
    }
#endif  /* SCOREP_BACKEND_COMPILER_MIC && HAVE( MIC_SUPPORT ) */

    std::string command = m_c_compiler
                          + target_flags
                          + " -c " + input_file
                          + " `" + m_opari_config + " --cflags` "
                          + " -o " + output_file;

    instrumenter.executeCommand( command );

    instrumenter.addTempFile( output_file );
}

void
SCOREP_Instrumenter_OpariAdapter::set_fortran_form( bool is_free )
{
#if HAVE( OPARI2_FIX_AND_FREE_FORM_OPTIONS )
    if ( is_free )
    {
        m_params += " --free-form";
    }
    else
    {
        m_params += " --fix-form";
    }
#else
    if ( is_free )
    {
        m_params += " --f90";
    }
    else
    {
        m_params += " --f77";
    }
#endif
}
