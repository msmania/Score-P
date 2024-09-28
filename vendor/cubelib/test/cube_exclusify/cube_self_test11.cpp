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
    cout << " Open cube example3_incl_excl.cubex...";
    cube.openCubeReport( "example3_incl_excl.cubex" );

    bool all_inclusive = true;
    metrics = cube.get_metv();
    for ( vector<Metric*>::iterator miter = metrics.begin(); miter != metrics.end(); miter++ )
    {
        all_inclusive &= ( ( *miter )->get_metric_kind() == "EXCLUSIVE" );
    }

    cout << std::fixed << std::setprecision( 0 );
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

    cout << std::fixed << std::setprecision( 1 );
    double v11 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << v11 << endl;
    double v22 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE, threads[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << v22 << endl;
    double v33 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << v33 << endl;
    double v44 = cube.get_sev( metrics[ 1 ], CUBE_CALCULATE_EXCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_EXCLUSIVE, threads[ 1 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << v44 << endl;

    cout << ( ( all_inclusive ) ? "all metrics exclusive" : "some metrics inclusive" ) << endl;
    return 0;
}
