/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2020                                                **
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
 *  @ingroup CUBE_tools
 *  @brief   Server application for the client-server network layer.
 *
 *  The cube server will listen on a given port for incoming client
 *  connections to serve information read and computed from a Cube file
 *  local to the server.
 **/
/*-------------------------------------------------------------------------*/
#include "config.h"

#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include <future>
#include <vector>

#include "CubeError.h"
#include "CubeNetworkRequest.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeSocket.h"
#include "CubeUrl.h"

#include "ServerWorker.h"

using namespace std;
using namespace cube;

/// @brief Print command-line options and usage info
///
const string&
getUsage()
{
    stringstream portNo;
    portNo << Url::getDefaultPort();
    static const string USAGE =
        "Usage: cube_server [options]\n"
        " -h, -?    Print this help message.\n"
        " -p N      Bind socket on port N (default port: " + portNo.str()
        + ")\n\n"
        "Report bugs to <" PACKAGE_BUGREPORT ">\n";

    return USAGE;
}


int
main( int   argc,
      char* argv[] )
{
    size_t       portNo = Url::getDefaultPort();
    stringstream message;

    int option_arg;

    // check for command line parameters
    while ( ( option_arg = getopt( argc, argv, "h?p:" ) ) != -1 )
    {
        switch ( option_arg )
        {
            case 'h':
            case '?':
                cerr << getUsage() << endl;
                exit( EXIT_SUCCESS );
                break;

            case 'p':
                portNo = atoi( optarg );
        }
    }

    SocketPtr                       socket     = Socket::create();
    ServerConnection::Ptr           connection = nullptr;
    std::vector<std::future<bool> > connections_futures;

    try
    {
        connection = ServerConnection::create(  socket,
                                                portNo );
    }
    catch ( NetworkError& theError )
    {
        cerr << "cube_server: " << theError.what() << endl;
        exit( EXIT_FAILURE );
    }
    message << "[" << getpid() << "] Cube Server: "
            << connection->getInfoString();
    cerr << message.str() << endl;
    message.str( "" );

    //     reset connection protocol
    connection->setProtocolVersion( 0 );


    while ( connection->isListening() )
    {
        // wait for incoming connection

#if defined( CUBE_NETWORK_DEBUG )
        message << "cube_server[" << getpid() << "] Waiting for connections on port " << portNo << ".";
        cerr << message.str() << endl;
        message.str( "" );
#endif

        try
        {
            connection->accept();
            ServerConnection::Ptr clientConnection = std::shared_ptr<ServerConnection> ( new ServerConnection( connection ) );
            // creating task and handing over connection
            connections_futures.emplace_back( std::async( std::launch::async,  serveClient, clientConnection ) );
        }
        catch ( const exception& err )
        {
            message << "cube_server[" << getpid() << "] " << err.what();
            cerr << message.str() << endl;
            message.str( "" );
            continue;
        }
    }
#if defined( CUBE_NETWORK_DEBUG )
    message << "cube_server[" << getpid() << "] Done.";
    cerr << message.str() << endl;
    message.str( "" );
#endif
}
