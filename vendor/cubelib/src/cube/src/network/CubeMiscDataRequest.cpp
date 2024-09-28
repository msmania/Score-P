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
 *  @brief   Declaration of the class cube::CubeMiscDataRequest.
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
#include "CubeMiscDataRequest.h"
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
CubeMiscDataRequest::getName() const
{
    return "CubeMiscDataRequest";
}


NetworkRequest::id_t
CubeMiscDataRequest::getId() const
{
    return MISC_DATA_REQUEST;
}

/// --- Construction & destruction ---------------------------------------
///

NetworkRequestPtr
CubeMiscDataRequest::create()
{
    return std::shared_ptr<CubeMiscDataRequest>( new CubeMiscDataRequest( "", nullptr ) );
}

NetworkRequestPtr
CubeMiscDataRequest::create( const std::string& name, vector<char>* vec )
{
    return std::shared_ptr<CubeMiscDataRequest>( new CubeMiscDataRequest( name, vec ) );
}

CubeMiscDataRequest::CubeMiscDataRequest( const string& name, std::vector<char>* data )
    : name_( name ), rawData( data )
{
}

CubeMiscDataRequest::~CubeMiscDataRequest()
{
    rawData = nullptr;
}

void
CubeMiscDataRequest::sendRequestPayload( ClientConnection& connection, ClientCallbackData* ) const
{
    // send data identifier to server
    connection << this->name_;
}

void
CubeMiscDataRequest::receiveRequestPayload( ServerConnection& connection, ServerCallbackData* )
{
    // read data identifier from client
    connection >> this->name_;
}

void
CubeMiscDataRequest::processRequest( ServerCallbackData* data )
{
    /// @pre Valid CallbackData.
    assert( data );

    /// @pre Valid Cube object.
    assert( data->getCube() );

    try
    {
        rawData  = new std::vector<char>;
        *rawData = data->getCube()->getMiscData( name_ );
    }
    catch ( const std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
}

void
CubeMiscDataRequest::sendResponsePayload( ServerConnection& connection, ServerCallbackData* data ) const
{
    // send raw misc data to client
    try
    {
        connection << ( size_t )rawData->size();
        for ( char c : * rawData )
        {
            connection << c;
        }
    }
    catch ( cube::Error& e )
    {
        connection << -1;
    }
    delete rawData;
}

void
CubeMiscDataRequest::receiveResponsePayload( ClientConnection& connection, ClientCallbackData* )
{
    // receive raw misc data from server
    size_t size;
    connection >> size;

    char c;
    for ( size_t i = 0; i < size; i++ )
    {
        connection >> c;
        rawData->push_back( c );
    }
    //std::cerr << "=== receiveResponsePayload " << size << endl;
}
