/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2021                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#include <config.h>

/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Declaration of the class cube::CubeVersionRequest.
 **/
/*-------------------------------------------------------------------------*/

#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <regex>

#include "CubePlatformsCompat.h"
#include "CubeIoProxy.h"
#include "CubeVersionRequest.h"
#include "CubeClientCallbackData.h"
#include "CubeClientConnection.h"
#include "CubeConnection.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "cube_network_types.h"

using namespace std;
using namespace cube;


/// --- Request identification -------------------------------------------

string
CubeVersionRequest::getName() const
{
    return "CubeVersionRequest";
}


NetworkRequest::id_t
CubeVersionRequest::getId() const
{
    return VERSION_REQUEST;
}

/// --- Construction & destruction ---------------------------------------
///

NetworkRequestPtr
CubeVersionRequest::create()
{
    int versionNumber;
    return std::shared_ptr<CubeVersionRequest>( new CubeVersionRequest( versionNumber ) );
}

NetworkRequestPtr
CubeVersionRequest::create( int& versionNumber )
{
    return std::shared_ptr<CubeVersionRequest>( new CubeVersionRequest( versionNumber ) );
}

void
CubeVersionRequest::sendRequestPayload( ClientConnection& connection, ClientCallbackData* ) const
{
    connection << CUBELIB_VERSION_NUMBER;
}

void
CubeVersionRequest::receiveRequestPayload( ServerConnection& connection, ServerCallbackData* )
{
    connection >> versionNumber;
}

void
CubeVersionRequest::sendResponsePayload( ServerConnection& connection, ServerCallbackData* data ) const
{
    connection << CUBELIB_VERSION_NUMBER;
}

void
CubeVersionRequest::receiveResponsePayload( ClientConnection& connection, ClientCallbackData* )
{
    // receive version from server
    connection >> versionNumber;
}
