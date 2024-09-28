/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2022                                                **
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
 * \file tau2cube4.cpp
 * \brief Tool to transform TAU data file in to .cube file.
 */
#include "config.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "CubeServices.h"

using namespace std;
using namespace cube;
using namespace services;

#include "tau2cube_calls.h"



/**
 * Main program.
 * - Check the calling parameters.
 * - Read the  profile. TAU file. and saves it in TAUprofile object.
 * - Create CUBE
 * - Create in CUBE corresponding demensions.
 * - Fill the CUBE.
 * - Saves a created cube in either "-o output" or "a.cube" file.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    string tau_profile_dir;
    string cube_file;

    if ( argc > 4 )
    {
        cerr << "Usage: tau2cube4 [<tau-profile-dir>] [-o <cube-file>]" << endl << std::endl;
        std::cerr << "Report bugs to <" PACKAGE_BUGREPORT ">\n";
        ;
        exit( EXIT_FAILURE );
    }
    vector<string> inputs;
    string         output;
    string         cur;
    bool           out_flag = false;
    // analyze the input command
    for ( int i = 1; i < argc; i++ )
    {
        cur = argv[ i ];
        if ( out_flag )
        {
            output   = cur;
            out_flag = false;
            continue;
        }
        if ( cur != "-o" )
        {
            inputs.push_back( cur );
        }
        else
        {
            out_flag = true;
        }
    }

    if ( inputs.empty() )
    {
        tau_profile_dir = ".";
    }
    else
    {
        tau_profile_dir = inputs[ 0 ];
    }
    if ( !output.empty() )
    {
        cube_file = output;
    }
    else
    {
        cube_file = "tau_profile";
    }
    // create CUBE profile
    cerr << "Creating CUBE profile...        ";
    Cube* cube = new Cube();
    // set aggregation mode
    cube->def_attr( "CUBE_CT_AGGR", "MAX" );

    create_from_tau( cube, tau_profile_dir.c_str() );

    cerr << " Write cube " << cube_file << flush;
    cube->writeCubeReport( get_cube4_name( cube_file ) );

    delete cube;
    cerr << " done." << endl;
}
