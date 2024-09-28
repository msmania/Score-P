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
 * Opens a big created cube report and reqds some values.
 */
#include "config.h"

#include <iostream>
#include <cmath>
#include <iomanip>

#include "Cube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeThread.h"

using namespace std;
using namespace cube;



int
main( int argc, char** argv )
{
    Cube cube;

    vector<Metric*> metrics;
    vector<Cnode*>  cnodes;
    vector<Thread*> threads;
    cout << " Open cube example2.cubex...";
    cube.openCubeReport( "example2.cubex" );

    metrics = cube.get_metv();
    cnodes  = cube.get_cnodev();
    threads = cube.get_thrdv();
    cout << "done" << endl;
    double v1 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << v1 << endl;
    double v2 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE, threads[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << v2 << endl;
    double v3 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << v3 << endl;
    double v4 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_EXCLUSIVE, threads[ 1 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << v4 << endl;


    metrics.clear();
    cnodes.clear();
    threads.clear();


    cout << " Open cube example3.cubex...";
    cube.openCubeReport( "example3.cubex" );

    metrics = cube.get_metv();
    cnodes  = cube.get_cnodev();
    threads = cube.get_thrdv();
    cout << "done" << endl;

    cout << std::fixed << std::setprecision( 0 );
    double vv1 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv1 << endl;
    double vv2 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE, threads[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv2 << endl;
    double vv11 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << vv11 << endl;
    double vv22 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_EXCLUSIVE, threads[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv22 << endl;

    double vv12 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv12 << endl;
    double vv23 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_INCLUSIVE, threads[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv23 << endl;
    double vv114 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << vv114 << endl;
    double vv225 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_EXCLUSIVE, threads[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv225 << endl;

    double vv33 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << vv33 << endl;

    cout <<  std::fixed << std::setprecision( 1 );

    double vv34 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << vv34 << endl;


    double vv4 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE, threads[ 1 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv4 << endl;
    double vv5 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv5 << endl;
    double vv44 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_EXCLUSIVE, threads[ 1 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv44 << endl;
    double vv55 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << vv55 << endl;

    double vv441 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_INCLUSIVE, threads[ 1 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv441 << endl;
    double vv551 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv551 << endl;
    double vv4461 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_EXCLUSIVE, threads[ 1 ], CUBE_CALCULATE_INCLUSIVE );
    cout << vv4461 << endl;
    double vv5571 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << vv5571 << endl;



    metrics.clear();
    cnodes.clear();
    threads.clear();

    return 0;
}
