/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2020                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#ifndef SERVER_WORKER_H
#define SERVER_WORKER_H

#include "CubeNetworkRequest.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
namespace cube
{
bool
serveClient( ServerConnection::Ptr connection );
}
#endif
