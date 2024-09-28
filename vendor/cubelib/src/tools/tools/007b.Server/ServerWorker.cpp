/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#include "config.h"


#include <cerrno>
#include <iostream>
#include <sstream>
#include <string>
#include "ServerWorker.h"
#include "ThreadPool.h"
#include "RequestTask.h"

using namespace std;
using namespace cube;

bool
cube::serveClient( ServerConnection::Ptr connection )
{
    stringstream message;
/*     // child does not need to listen to the server socket
    try
    {
                cerr << "Client doenst listen anzmore " << endl;

        //connection->stopListening();
                cerr << "Client stoped listen anzmore " << endl;
    }
    catch ( const exception& err )
    {
        message << "cube_server[" << getpid() << "] " << err.what();
        cerr << message.str() << endl;
        message.str( "" );
        exit( EXIT_FAILURE );
    }
   #if defined( CUBE_NETWORK_DEBUG )
    message << "cube_server[" << getpid() << "] Child stopped listening.";
    cerr << message.str() << endl;
    message.str( "" );
 #endif */
    ThreadPool pool( std::thread::hardware_concurrency() );

    /* Allocated here and only one instance of ServerCallbackData, so that
     * server-side information is truly stored between distinct network
     * requests i.e. for the whole time of connection->isEstablished()
     */
    ServerCallbackData* data = new ServerCallbackData();
    while ( connection->isEstablished() )
    {
        // read request ID from stream
        NetworkRequest::Ptr request;
        try
        {
            // create request from input on connection stream
            request = connection->createRequestFromStream( data );

#if defined( CUBE_NETWORK_DEBUG )
            message << "cube_server[" << getpid() << "] -- Received request: "
                    << request->getName() << " --" << request.get()->getSequenceNumber();
            cerr << message.str() << endl;
            message.str( "" );
#endif

            if ( request->getName() == "OpenCube" )
            {
                // client waits for cube to be opened, so this check is not required, but it dosn't hurt
                // (and removes a lot of warning of helgrind)
                RequestTask( connection, request, data ).work();
            }
            else if ( request->getName() == "Disconnect" )
            {
                // just disconnect, no further communication to client
                connection->disconnect();
                break; // leave loop
            }
            else
            {
                pool.addTask( std::bind( &RequestTask::work, RequestTask( connection, request, data ) ) );
            }
        }
        catch ( const RecoverableNetworkError& theError )
        {
            message << "cube_server[" << getpid()
                    << "] ### Recoverable error while handling request.\n"
                    << "[" << getpid() << "] ### " << theError.what();
            cerr << message.str() << endl;
            message.str( "" );

            request->sendErrorResponse( *connection,
                                        REQUEST_ERROR_RECOVERABLE,
                                        theError.what() );
        }
        catch ( const UnrecoverableNetworkError& theError )
        {
            message << "cube_server[" << getpid()
                    << "] ### Unrecoverable error while handling request.\n"
                    << "[" << getpid() << "] ### " << theError.what();
            cerr << message.str() << ". Disconnect." << endl;
            message.str( "" );

            connection->disconnect();
            break;
        }
        catch ( const std::exception& theError )
        {
            message << "cube_server[" << getpid()
                    <<
                "] ### Unexpected exception while handling request.\n"
                    << "[" << getpid() << "] ### " << theError.what();
            cerr << message.str() << ". Disconnect." << endl;
            message.str( "" );
            connection->disconnect();
        }
    }      // connection->isEstablished()
    delete data;
    return true;
}
