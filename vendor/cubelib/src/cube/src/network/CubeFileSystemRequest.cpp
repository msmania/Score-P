/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2018-2020                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014                                                     **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
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
 *  @brief   Declaration of the class cube::FileSystemRequest.
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
#include "CubeFileSystemRequest.h"
#include "CubeClientCallbackData.h"
#include "CubeClientConnection.h"
#include "CubeConnection.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "cube_network_types.h"

using namespace std;
using namespace cube;

static vector<FileInfo>
getDirectoryListing( const std::string& dirName )
{
    std::cmatch      sm;
    std::regex       cubex_reg( "(\\.cubex|\\.cube|\\.cube\\.gz)$" );
    vector<FileInfo> files;
    DIR*             dir;

    // convert dirName to absolute path realPath
    char* rp = realpath( dirName.c_str(), NULL );
    if ( !rp )
    {
        return files;
    }
    string realPath( rp );
    free( rp );

    if ( !realPath.empty() && ( dir = opendir( realPath.c_str() ) ) != NULL )
    {
        struct dirent* ent;
        FileInfo       cwd( string( realPath ), true, 0, 0 );
        files.push_back( cwd ); // put absolute directory path as 1st element into the result vector
        while ( ( ent = readdir( dir ) ) != NULL )
        {
            std::string fullName = realPath + "/" + ent->d_name;
            struct stat statbuf;
            bool        isDir = false;
            off_t       size  = 0;
            if ( stat( fullName.c_str(), &statbuf ) == 0 )
            {
                if ( statbuf.st_mode & S_IFDIR )
                {
                    isDir = true;
                }
                else
                {
                    if ( !std::regex_search( ent->d_name, sm, cubex_reg ) ) // didn't match .cubex, .cube.gz or .cube file
                    {
                        // skip entry
                        continue;
                    }
                    size = statbuf.st_size;
                }
            }

            FileInfo file( fullName, isDir, size, statbuf.st_mtime );
            files.push_back( file );
        }
        closedir( dir );
    }

    return files;
}

/// --- Request identification -------------------------------------------

string
FileSystemRequest::getName() const
{
    return "CubeFileSystemRequest";
}


NetworkRequest::id_t
FileSystemRequest::getId() const
{
    return FILESYSTEM_REQUEST;
}

/// --- Construction & destruction ---------------------------------------
///

NetworkRequestPtr
FileSystemRequest::create()
{
    return std::shared_ptr<FileSystemRequest>( new FileSystemRequest( "" ) );
}

NetworkRequestPtr
FileSystemRequest::create( const std::string& dirName )
{
    return std::shared_ptr<FileSystemRequest>( new FileSystemRequest( dirName ) );
}

FileSystemRequest::FileSystemRequest( const string& absolutePath )
    : mDirName( absolutePath )
{
}

FileSystemRequest::~FileSystemRequest()
{
}

void
FileSystemRequest::sendRequestPayload( ClientConnection& connection, ClientCallbackData* ) const
{
    // send directory name to server
    connection << this->mDirName;
}

void
FileSystemRequest::receiveRequestPayload( ServerConnection& connection, ServerCallbackData* )
{
    // read directory name from client
    connection >> this->mDirName;
}



void
FileSystemRequest::sendResponsePayload( ServerConnection& connection, ServerCallbackData* ) const
{
    // send directory contents to client
    try
    {
        vector<FileInfo> files = getDirectoryListing( mDirName );
        int              size  = files.size();
        connection << size;
        for ( vector<FileInfo>::iterator it = files.begin(); it != files.end(); ++it )
        {
            FileInfo    info = *it;
            std::string name = info.name();
            connection << name;
            connection << info.isDirectory();
            connection << info.size();
            connection << info.time();
        }
    }
    catch ( cube::Error& e )
    {
        connection << -1;
    }
}

void
FileSystemRequest::receiveResponsePayload( ClientConnection& connection, ClientCallbackData* )
{
    // receive directory contents from server
    int elements;
    connection >> elements;

    if ( elements < 0 )
    {
        isValid_ = false;
    }
    else
    {
        isValid_ = true;
        std::string name;
        for ( int i = 0; i < elements; i++ )
        {
            bool   isDirectory = false;
            off_t  size        = 0;
            time_t time;
            connection >> name;
            connection >> isDirectory;
            connection >> size;
            connection >> time;

            FileInfo info( name, isDirectory, size, time );
            mFiles.push_back( info );
        }
    }
}
