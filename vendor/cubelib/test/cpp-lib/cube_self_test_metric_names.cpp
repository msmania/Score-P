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
 * \file cube_test.cpp
 * \brief An example how to create and save a cube with attributes
 */
#include "config.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Cube.h"

using namespace std;
using namespace cube;

/** Debug: only used for Metric, Cnode */
template <class T>
void
traverse_print( T root )
{
    cout << root->get_id() << endl;
    for ( int i = 0; i < root->num_children(); i++ )
    {
        traverse_print<T>( ( T )root->get_child( i ) );
    }
}

// example code.
/**
 * Main program.
 * - Create an object "cube"
 * - Specify mirrors for onilne help.
 * - Specify information related to the file (optional)
 * - Build metric tree
 * - Build call tree
 * - Build location tree
 * - Severity mapping
 * - Building a topology
 *    - create 1st cartesian.
 *    - create 2nd cartesian
 * - Output to a cube file
 *
 * - For a test read the cube again and save it in another file.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    Metric*  met0, * met1, * met2;
    Region*  regn0, * regn1, * regn2;
    Cnode*   cnode0, * cnode1, * cnode2;
    Machine* mach;
    Node*    node;
    Process* proc0, * proc1;
    Thread*  thrd0, * thrd1;

    std::string cubename = "example_uniq_name_correction";
    try
    {
        Cube cube;
//   Cube cube;

        // Specify mirrors (optional)
        cube.def_mirror( "http://icl.cs.utk.edu/software/kojak/" );
        cube.def_mirror( "http://www.fz-juelich.de/jsc/kojak/" );
        cube.def_mirror( "file:///home/psaviank/Soft/Installed/scalasca-trunk/doc/html/" );
        // Specify information related to the file (optional)
        cube.def_attr( "experiment time", "November 1st, 2004" );
        cube.def_attr( "description", "a simple example" );

        string unique_corrected;
        if ( cube.make_unique_name( "time", unique_corrected ) )
        {
            std::cout << "Uniq name " << "time  has been altered to  \"" << unique_corrected  << "\"" << std::endl;
        }
        met0 = cube.def_met( "Time1", unique_corrected, "INTEGER", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "Total CPU allocation time", NULL, CUBE_METRIC_EXCLUSIVE );

        if ( cube.make_unique_name( "time::time time=0", unique_corrected ) )
        {
            std::cout << "Uniq name " << "\"time::time time=0\" has been altered to  \"" << unique_corrected  << "\"" << std::endl;
        }

        met1 = cube.def_met( "Time3", unique_corrected, "INTEGER", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "Total CPU allocation time", met0, CUBE_METRIC_EXCLUSIVE );


        if ( cube.make_unique_name( "time_?%&!* +~time", unique_corrected )  )
        {
            std::cout << "Uniq name " << "time_?%&!* +~time\" has been altered to \"" << unique_corrected  << "\"" << std::endl;
        }

        met2 = cube.def_met( "Time5", unique_corrected, "INTEGER", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "Total CPU allocation time", met0, CUBE_METRIC_EXCLUSIVE );

        met1->def_attr( "attribute1", "Super attribute1" );
        met1->def_attr( "attribute2", "Super attribute2" );


        // Build call tree
        string mod = "/ICL/CUBE/example.c";
        regn0 = cube.def_region( "main", "main", "mpi", "barrier", 21, 100, "", "1st level", mod );
        regn1 = cube.def_region( "foo", "foo", "mpi", "barrier", 1, 10, "", "2nd level", mod );
        regn2 = cube.def_region( "bar", "bar", "mpi", "barrier", 11, 20, "", "2nd level", mod );

        regn0->def_attr( "attribute1", "Super attribute1" );
        regn2->def_attr( "attribute2", "Super attribute2" );


        cnode0 = cube.def_cnode( regn0, mod, 21, NULL );
        cnode1 = cube.def_cnode( regn1, mod, 60, cnode0 );
        cnode2 = cube.def_cnode( regn2, mod, 80, cnode0 );

        cnode1->def_attr( "attribute1", "Super attribute1" );
        cnode1->def_attr( "attribute2", "Super attribute2" );


        // Build location tree
        mach  = cube.def_mach( "MSC", "" );
        node  = cube.def_node( "Athena", mach );
        proc0 = cube.def_proc( "Process 0", 0, node );
        proc1 = cube.def_proc( "Process 1", 1, node );
        thrd0 = cube.def_thrd( "Thread 0", 0, proc0 );
        thrd1 = cube.def_thrd( "Thread 1", 1, proc1 );

        mach->def_attr( "attribute1", "Super attribute1" );
        node->def_attr( "attribute2", "Super attribute2" );
        proc1->def_attr( "attribute1", "Super attribute1" );
        thrd0->def_attr( "attribute2", "Super attribute2" );
        thrd0->def_attr( "attribute2", "Super attribute2" );
        thrd0->def_attr( "attribute2", "Super attribute2" );

        cube.initialize();


        // Severity mapping

        cube.set_sev( met0, cnode0, thrd0, 4. );
        cube.set_sev( met0, cnode0, thrd1, 0. );
        cube.set_sev( met0, cnode1, thrd0, 5. );
        cube.set_sev( met0, cnode1, thrd1, 9. );
        cube.set_sev( met1, cnode0, thrd0, 2. );
        cube.set_sev( met1, cnode0, thrd1, 1. );
        // unset severities default to zero
        cube.set_sev( met1, cnode1, thrd1, 3. );
        cube.set_sev( met2, cnode1, thrd1, 323. );
        cube.writeCubeReport( cubename );
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        return -1;
    }
    return 0;
}
