/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2020-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Definition of the class ServerConnection.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeServerConnection.h"

#include <iostream>

#include "CubeError.h"
#include "CubeNetworkRequest.h"
#include "CubeOperator.h"
#include "CubeSocket.h"
#include "CubeUrl.h"

using namespace std;

namespace cube
{
ServerConnection::Ptr
ServerConnection::create( SocketPtr socket,
                          size_t    port )
{
    return std::shared_ptr<ServerConnection>( new ServerConnection( socket, port ) );
}


void
ServerConnection::accept()
{
    if ( !mSocket.get() )
    {
        throw InvalidSocket( "Invalid Socket." );
    }

    mSocket->accept();
    uint64_t one;
    *this >> one;
    if ( one != 1 )
    {
        ByteSwapOperator< uint64_t >::apply( one );
        if ( one != 1 )
        {
            throw UnrecoverableNetworkError( "Unable to negotiate endianness" );
        }
        this->enableByteSwap( true );
    }
}


ServerConnection::ServerConnection( SocketPtr socket,
                                    size_t    port )
    : Connection( socket )
{
    if ( mSocket.get() )
    {
        mSocket->listen( port );
    }
}

ServerConnection::ServerConnection( const ServerConnectionPtr& ptr )
    : Connection( ptr.get()->mSocket, ptr.get()->mProtocol,
                  ptr.get()->mEnableByteSwap )
{
}


ServerConnection::~ServerConnection()
{
    if ( mSocket.get() )
    {
        mSocket->disconnect();
    }
}


bool
ServerConnection::isListening() const
{
    if ( mSocket.get() )
    {
        return mSocket->isListening();
    }

    return false;
}


NetworkRequestPtr
ServerConnection::createRequestFromStream( ServerCallbackData* data )
{
    NetworkRequestPtr request = NetworkRequest::createFromStream( *this, data );
    return request;
}


void
ServerConnection::stopListening()
{
    mSocket->shutdown();
}
}    /* namespace cube */
