/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2021                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file cube_self_test2_gpu_metrics.cpp
 * \brief An example how to create and save a cube with GPU and METTRICS locations.
 */
#include "config.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Cube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeProcess.h"
#include "CubeNode.h"
#include "CubeThread.h"
#include "CubeCartesian.h"

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
    Metric*         met0, * met1, * met2;
    Region*         regn0, * regn1, * regn2;
    Cnode*          cnode0, * cnode1, * cnode2;
    SystemTreeNode* stn0;
    SystemTreeNode* stn1;
    LocationGroup*  lg_proc, * lg_gpu, * lg_metric;
    Location*       loc_thrd1, * loc_gpu1, * loc_metric1;
    Location*       loc_thrd2, * loc_gpu2, * loc_metric2;

    std::string cubename = "example_gpu_metrics";
    try
    {
        Cube cube;
//   Cube cube;

        // Specify mirrors (optional)
        cube.def_mirror( "http://icl.cs.utk.edu/software/scalasca/" );
        cube.def_mirror( "http://www.fz-juelich.de/jsc/scalasca/" );
        // Specify information related to the file (optional)
        cube.def_attr( "experiment time", "November 1st, 2014" );
        cube.def_attr( "description", "a simple example with GPU and metric locations " );

        // Build metric tree
        met0 = cube.def_met( "Time", "Uniq_name1", "INTEGER", "sec", "",
                             "@mirror@patterns-2.2.html#execution",
                             "root node", nullptr ); // using mirror
        met1 = cube.def_met( "User time", "Uniq_name2", "INTEGER", "sec", "",
                             "http://www.cs.utk.edu/usr.html",
                             "2nd level", met0 ); // without using mirror
        met2 = cube.def_met( "System time", "Uniq_name3", "INTEGER", "sec", "",
                             "http://www.cs.utk.edu/sys.html",
                             "2nd level", met0 ); // without using mirror

        // Build call tree
        string mod = "/ICL/CUBE/example.c";
        regn0 = cube.def_region( "main", "main", "mpi", "barrier", 21, 100, "", "1st level", mod );
        regn1 = cube.def_region( "foo", "foo", "mpi", "barrier", 1, 10, "", "2nd level", mod );
        regn2 = cube.def_region( "bar", "bar", "mpi", "barrier", 11, 20, "", "2nd level", mod );

        cnode0 = cube.def_cnode( regn0, mod, 21, nullptr );
        cnode1 = cube.def_cnode( regn1, mod, 60, cnode0 );
        cnode2 = cube.def_cnode( regn2, mod, 80, cnode0 );

        // Build location tree
        stn0      = cube.def_system_tree_node( "MSC", "", "", nullptr );
        stn1      = cube.def_system_tree_node( "Athena", "", "", stn0 );
        lg_proc   = cube.def_location_group( "Process 0", 0, CUBE_LOCATION_GROUP_TYPE_PROCESS, stn1 );
        lg_gpu    = cube.def_location_group( "Process 0 (GPU)", 0, CUBE_LOCATION_GROUP_TYPE_ACCELERATOR, stn1 );
        lg_metric = cube.def_location_group( "Process 0 (METRICS)", 0, CUBE_LOCATION_GROUP_TYPE_METRICS, stn1 );

        loc_thrd1 = cube.def_location( "Thread 1", 0, CUBE_LOCATION_TYPE_CPU_THREAD, lg_proc );
        loc_thrd2 = cube.def_location( "Thread 2", 1, CUBE_LOCATION_TYPE_CPU_THREAD, lg_proc );

        loc_gpu1 = cube.def_location( "Thread 1 (GPU)", 2, CUBE_LOCATION_TYPE_ACCELERATOR_STREAM, lg_gpu );
        loc_gpu2 = cube.def_location( "Thread 2 (GPU)", 3, CUBE_LOCATION_TYPE_ACCELERATOR_STREAM, lg_gpu );

        loc_metric1 = cube.def_location( "Thread 1 (METRICS)", 4, CUBE_LOCATION_TYPE_METRIC, lg_metric );
        loc_metric2 = cube.def_location( "Thread 2 (METRICS)", 5, CUBE_LOCATION_TYPE_METRIC, lg_metric );


        cube.initialize();


        // Severity mapping
        cube.set_sev( met0, cnode0, loc_thrd1, 1. );
        cube.set_sev( met0, cnode0, loc_thrd2, 2. );
        cube.set_sev( met0, cnode1, loc_thrd1, 3. );
        cube.set_sev( met0, cnode1, loc_thrd2, 4. );
        cube.set_sev( met0, cnode2, loc_thrd1, 5. );
        cube.set_sev( met0, cnode2, loc_thrd2, 6. );

        cube.set_sev( met0, cnode0, loc_gpu1, -1. );
        cube.set_sev( met0, cnode0, loc_gpu2, -2. );
        cube.set_sev( met0, cnode1, loc_gpu1, -3. );
        cube.set_sev( met0, cnode1, loc_gpu2, -4. );
        cube.set_sev( met0, cnode2, loc_gpu1, -5. );
        cube.set_sev( met0, cnode2, loc_gpu2, -6. );


        cube.set_sev( met0, cnode0, loc_metric1, 10. );
        cube.set_sev( met0, cnode0, loc_metric2, 20. );
        cube.set_sev( met0, cnode1, loc_metric1, 30. );
        cube.set_sev( met0, cnode1, loc_metric2, 40. );
        cube.set_sev( met0, cnode2, loc_metric1, 50. );
        cube.set_sev( met0, cnode2, loc_metric2, 60. );


        cube.set_sev( met1, cnode0, loc_thrd1, 11. );
        cube.set_sev( met1, cnode0, loc_thrd2, 22. );
        cube.set_sev( met1, cnode1, loc_thrd1, 33. );
        cube.set_sev( met1, cnode1, loc_thrd2, 44. );
        cube.set_sev( met1, cnode2, loc_thrd1, 55. );
        cube.set_sev( met1, cnode2, loc_thrd2, 66. );

        cube.set_sev( met1, cnode0, loc_gpu1, -11. );
        cube.set_sev( met1, cnode0, loc_gpu2, -22. );
        cube.set_sev( met1, cnode1, loc_gpu1, -33. );
        cube.set_sev( met1, cnode1, loc_gpu2, -44. );
        cube.set_sev( met1, cnode2, loc_gpu1, -55. );
        cube.set_sev( met1, cnode2, loc_gpu2, -66. );


        cube.set_sev( met1, cnode0, loc_metric1, 110. );
        cube.set_sev( met1, cnode0, loc_metric2, 220. );
        cube.set_sev( met1, cnode1, loc_metric1, 330. );
        cube.set_sev( met1, cnode1, loc_metric2, 440. );
        cube.set_sev( met1, cnode2, loc_metric1, 550. );
        cube.set_sev( met1, cnode2, loc_metric2, 660. );


        cube.set_sev( met2, cnode0, loc_thrd1, 111. );
        cube.set_sev( met2, cnode0, loc_thrd2, 222. );
        cube.set_sev( met2, cnode1, loc_thrd1, 333. );
        cube.set_sev( met2, cnode1, loc_thrd2, 444. );
        cube.set_sev( met2, cnode2, loc_thrd1, 555. );
        cube.set_sev( met2, cnode2, loc_thrd2, 666. );

        cube.set_sev( met2, cnode0, loc_gpu1, -111. );
        cube.set_sev( met2, cnode0, loc_gpu2, -222. );
        cube.set_sev( met2, cnode1, loc_gpu1, -333. );
        cube.set_sev( met2, cnode1, loc_gpu2, -444. );
        cube.set_sev( met2, cnode2, loc_gpu1, -555. );
        cube.set_sev( met2, cnode2, loc_gpu2, -666. );


        cube.set_sev( met2, cnode0, loc_metric1, 111. );
        cube.set_sev( met2, cnode0, loc_metric2, 222. );
        cube.set_sev( met2, cnode1, loc_metric1, 333. );
        cube.set_sev( met2, cnode1, loc_metric2, 444. );
        cube.set_sev( met2, cnode2, loc_metric1, 555. );
        cube.set_sev( met2, cnode2, loc_metric2, 666. );



        // building a topology
        // create 1st cartesian.
        int          ndims = 2;
        vector<long> dimv;
        vector<bool> periodv;
        for ( int i = 0; i < ndims; i++ )
        {
            dimv.push_back( 5 );
            if ( i % 2 == 0 )
            {
                periodv.push_back( true );
            }
            else
            {
                periodv.push_back( false );
            }
        }


        Cartesian* cart = cube.def_cart( ndims, dimv, periodv );

        if ( cart != nullptr )
        {
            vector<long> p[ 2 ];
            p[ 0 ].push_back( 0 );
            p[ 0 ].push_back( 0 );
            p[ 1 ].push_back( 2 );
            p[ 1 ].push_back( 2 );
            cube.def_coords( cart, loc_thrd1, p[ 0 ] );
        } // create 2nd cartesian
        ndims = 2;
        vector<long> dimv2;
        vector<bool> periodv2;
        for ( int i = 0; i < ndims; i++ )
        {
            dimv2.push_back( 3 );
            if ( i % 2 == 0 )
            {
                periodv2.push_back( true );
            }
            else
            {
                periodv2.push_back( false );
            }
        }


        Cartesian* cart2 = cube.def_cart( ndims, dimv2, periodv2 );
        cart2->set_name( "MY SUPER TOPOL<<d>&&$%&<y;\"\"OGYW 2" );
        if ( cart2 != nullptr )
        {
            vector<long> p2[ 2 ];
            p2[ 0 ].push_back( 0 );
            p2[ 0 ].push_back( 1 );
            p2[ 1 ].push_back( 1 );
            p2[ 1 ].push_back( 0 );
            cube.def_coords( cart2, loc_thrd1, p2[ 0 ] );
            cube.def_coords( cart2, loc_thrd2, p2[ 1 ] );
        }


        cube.set_statistic_name( "statisticstat" );
        cube.set_metrics_title( "sfdgsaf%$&WDFGYVART&" );
        cube.set_calltree_title( "calltreesfdgsaf%$&WDFGYVART&" );
        cube.set_systemtree_title( "systemsfdgsaf%$&WDFGYVART&" );

        cube.enable_flat_tree( false );



        const char* test2 = "In Hamburg lebten zwei Ameisen,"
                            "die wollten nach Australien reisen."
                            "Bei Altona, auf der Chaussee,"
                            "da taten ihnen die Beine weh,"
                            "und da verzichteten sie weise"
                            "dann auf den letzten Teil der Reise.";

        string dataname = "Die Ameisen";
        cube.write_misc_data( dataname, test2, strlen( test2 ) );


        cube.writeCubeReport( cubename );
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        return -1;
    }
    return 0;
}
