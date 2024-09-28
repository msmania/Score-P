/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2009-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2009-2011                                                **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  Copyright (c) 2009-2016                                                **
**  TU Dresden, Zentrum fuer Informationsdienste und Hochleistungsrechnen  **
**                                                                         **
**  Copyright (c) 2009-2013                                                **
**  Technische Universitaet Muenchen, Germany                              **
**                                                                         **
**  Copyright (c) 2009-2013                                                **
**  University of Oregon, Eugene, USA                                      **
**                                                                         **
**  Copyright (c) 2009-2013                                                **
**  Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany      **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * @file
 *
 * Declares classes for the representation and analysis of library dependencies
 */

#ifndef CUBEW_CONFIG_DATA_HPP
#define CUBEW_CONFIG_DATA_HPP

#include <map>
#include <deque>
#include <string>
#include <generate-library-dependencies-la-object.hpp>


/**
 * A class to store and analyze the dependencies from libraries. To generate
 * the dependecies, the .la files are parsed and initialization code is
 * generated by build-config/common/generate-library-dependecies.sh
 */
class cubew_config_data
{
    // ------------------------------------- Public types
public:

    /**
     * Constructs the library dependecies
     */
    cubew_config_data();

    /**
     * Destructor
     */
    virtual
    ~cubew_config_data();

    /**
     * Returns the string containing the @a input_libs and its dependencies.
     * @param input_libs  A list of libraries, that should be linked.
     */
    std::string
    GetLibraries( const std::deque<std::string>& inputLibs );

    /**
     * Returns the string containing the library path flags for the @a input_libs and
     * its dependencies.
     * @param libs     A list of library names.
     */
    std::string
    GetLDFlags( const std::deque<std::string>& libs );

    /**
     * Returns the string containing the rpath flags for the @a libs and
     * its dependencies.
     * @param libs      A list of library names.
     */
    std::string
    GetRpathFlags( const std::deque<std::string>& libs );

    /**
     * Construct rpath construction flags
     */
    void
    prepare_rpath_flags();

    /*
     * Returns @a pathList without system path entries.
     */
    std::deque<std::string>
    remove_system_path( const std::deque<std::string>& pathList ) const;

    /**
     * Add content of the environment variable LD_RUN_PATH as -rpath argument
     */
    std::string
    append_ld_run_path_to_rpath( const std::string& rpath ) const;

    /** Make string with compiler or linker flags compatible to CUDA
     *  compiler requirements.
     *
     *  @param str              String to be processed.
     *
     *  @return Returns string with compiler or linker flags that can be
     *          passes to CUDA compiler.
     */
    std::string
    prepare_string( const std::string& str ) const;

    /**
     * Calculates the dependencies for a given set of libraries.
     * @param libs      A list of library names.
     * @param frontend  Specifies whether the data for the frontend or
     *                  for the backend is requested. Pass true, if you
     *                  need frontend data. Pass false is you want
     *                  backend data.
     */
    std::deque<std::string>
    get_dependencies( const std::deque<std::string>& libs );

    // ------------------------------------- Public members
    std::string m_rpath_head;
    std::string m_rpath_delimiter;
    std::string m_rpath_tail;

    std::string m_cc;
    std::string m_cppflags;
    std::string m_incldir;
    bool        m_use_rpath_flag;
    std::string m_rpath_flag_cc;
    std::string m_wl_flag;
    std::string m_aix_libpath;
    std::string m_sys_lib_dlsearch_path;

    std::map< std::string, la_object> m_la_objects;
};

cubew_config_data*
cubew_config_get_backend_data();

#ifdef CROSS_BUILD

cubew_config_data*
cubew_config_get_frontend_data();

#else

#define cubew_config_get_frontend_data() \
    cubew_config_get_backend_data()

#endif

#endif /* CUBEW_CONFIG_DATA_HPP */
