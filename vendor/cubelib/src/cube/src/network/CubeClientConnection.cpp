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
 *  @brief   Definition of the class ClientConnection.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeClientConnection.h"

#include <iostream>
#include <string.h>
#include <chrono>
#include <thread>

#include "CubeClientServerVersionRequest.h"
#include "CubeDisconnectRequest.h"
#include "CubeError.h"
#include "CubeNegotiateProtocolRequest.h"
#include "CubeNetworkRequest.h"
#include "CubeSocket.h"
#include "CubeUrl.h"

using namespace std;

namespace cube
{
ClientConnection::Ptr
ClientConnection::create( SocketPtr     socket,
                          const string& url_string )
{
    return std::shared_ptr<ClientConnection>( new ClientConnection( socket, url_string ) );
}


ClientConnection::ClientConnection( SocketPtr socket )
    : Connection( socket )
{
    if ( socket.get() )
    {
        receiveThread = new std::thread( &NetworkRequest::receiveResponseLoop, std::ref( *this ) );
    }
    else
    {
        receiveThread = nullptr;
    }
}


ClientConnection::ClientConnection( SocketPtr     socket,
                                    const string& url_string )
    : Connection( socket )
{
    // decode URL
    Url url( url_string );

    // connect socket
    mSocket->connect( url.getHost(), url.getPort() );

    // start thread which receives requests
    receiveThread = new std::thread( &NetworkRequest::receiveResponseLoop, std::ref( *this ) );

    // send 64-bit value of one, to check for endianness on server
    uint64_t one = 1;
    *this << one;

    // Negotiate Protocol with server
    NetworkRequestPtr request = createRequest( NEGOTIATE_PROTOCOL_REQUEST );
    request->sendRequest( *this, 0 );
    request->receiveResponse( *this, 0 );

    NetworkRequestPtr reqVersion = createRequest( GET_VERSION_STRING_REQUEST );
    reqVersion->sendRequest( *this, 0 );
    reqVersion->receiveResponse( *this, 0 );
}


ClientConnection::~ClientConnection()
{
    const std::chrono::milliseconds sleep_time( 250 );
    // send disconnect request
    if ( this->isEstablished() )
    {
        NetworkRequestPtr request = createRequest( DISCONNECT_REQUEST );
        try
        {
            request->sendRequest( *this, 0 );
            stop_reading_flag = true; // signaling reading thread to stop reading (QtServerStreanSocket)
            // one desnt wait for respond -> simply disconnect
            NetworkRequest::stopLoop();
            std::this_thread::sleep_for( sleep_time ); // artificial delay before disconnecting to give a chance to send request to server. we do not expect any answers.
        }
        catch ( NetworkError& theError )
        {
            cerr << theError << endl;
        }
        // disconnect socket at end of lifetime
        mSocket->disconnect();
    }
    NetworkRequest::stopLoop();
    if ( receiveThread != nullptr )
    {
        receiveThread->join();
        delete receiveThread;
    }
}
}    /* namespace cube */
