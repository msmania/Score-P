/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2021                                                **
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



#ifndef CUBELIB_TOOLS_SCALING_CALLS_H
#define CUBELIB_TOOLS_SCALING_CALLS_H

#include <map>
#include "Cube.h"

using namespace std;
namespace cube
{
void
create_for_scaling_plugin(  cube::Cube*    outCube,
                            cube::Cube**   cubes,
                            bool           aggregation,
                            const unsigned num );
}

#endif
