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



#ifndef CUBELIB_CUBE_INFO_CALLS_H
#define CUBELIB_CUBE_INFO_CALLS_H



AggrCube*
openCubeFile( const char* filename )
{
    AggrCube* input = new AggrCube();
    input->openCubeReport( filename );
    return input;
}


#endif
