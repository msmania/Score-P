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


#ifndef REQUEST_TASK_H
#define REQUEST_TASK_H

#include <iostream>
#include <sstream>
#include <string>

#include "CubeNetworkRequest.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeNetworkRequest.h"
namespace cube
{
/**
 * @brief The RequestTask class holds the data of a cube request and the method work() to execute it and to
 * send the result to the client.
 */
class RequestTask
{
public:
    RequestTask( ServerConnection::Ptr connection,
                 NetworkRequest::Ptr   request,
                 ServerCallbackData*   data
                 ) : connection_( connection ), request_( request ), data_( data )
    {
    }

    void
    work()
    {
        request_->processRequest( data_ ); // calculate result

        std::stringstream message;
        try
        {
            request_->sendResponse( *connection_, data_ ); // send result to client

#if defined( CUBE_NETWORK_DEBUG )
            message << "Sent response number #" << request_->getSequenceNumber();
            std::cerr << message.str() << std::endl;
            message.str( "" );
#endif
        }
        catch ( NetworkError& theError )
        {
            message << "cube_server[" << getpid() << "] ### Failed to send response.\n"
                    << "cube_server[" << getpid() << "] ### " << theError.what();
            std::cerr << message.str() << std::endl;
            message.str( "" );
            connection_->disconnect();
        }
        catch ( const std::exception& theError )
        {
            message << "cube_server[" << getpid() << "] ### Unexpected exception while handling request.\n"
                    << "cube_server[" << getpid() << "] ### " << theError.what();
            std::cerr << message.str() << std::endl;
            message.str( "" );
        }
    }
private:
    ServerConnection::Ptr connection_;
    NetworkRequest::Ptr   request_;
    ServerCallbackData*   data_;
};
}
#endif
