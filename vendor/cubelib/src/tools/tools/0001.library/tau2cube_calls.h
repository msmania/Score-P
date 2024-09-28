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



#ifndef CUBELIB_TOOLS_CUBE_TAU2CUBE_CALLS_H
#define CUBELIB_TOOLS_CUBE_TAU2CUBE_CALLS_H

#include <map>
#include "Cube.h"
#include "TauProfile.h"

using namespace std;
namespace cube
{
/**
 * @brief create_from_tau reads a tau profile and creates a cube with it's data
 * @param cube cube object with tau data
 * @param path path of the tau measurements
 */
void
create_from_tau( cube::Cube* cube,
                 const char* path );
}

#endif
