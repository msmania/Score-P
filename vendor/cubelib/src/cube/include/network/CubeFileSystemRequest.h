/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2020                                                     **
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


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Declaration of the class cube::FileSystemRequest.
 **/
/*-------------------------------------------------------------------------*/

#ifndef CUBEFILESYSTEMREQUEST_H
#define CUBEFILESYSTEMREQUEST_H

#include <string>
#include <vector>
#include <time.h>
#include "CubeNetworkRequest.h"

namespace cube
{
class FileInfo
{
public:
    FileInfo( const std::string& name, bool isDirectory, long bytes, time_t time ) :
        name_( name ), isDirectory_( isDirectory ), size_( bytes ), time_( time )
    {
    }
    std::string
    name() const
    {
        return name_;
    }

    bool
    isDirectory() const
    {
        return isDirectory_;
    }

    long
    size() const
    {
        return size_;
    }

    time_t
    time() const
    {
        return time_;
    }

private:
    std::string name_;
    bool        isDirectory_;
    long        size_;
    time_t      time_;
};

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::CubeFileSystemRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Network request to read the contents of a remote directory
 **/
/*-------------------------------------------------------------------------*/

class FileSystemRequest
    : public NetworkRequest
{
public:
    // --- NetworkRequest interface

    virtual NetworkRequest::id_t
    getId() const;
    virtual std::string
    getName() const;

    /// @brief Server-side factory method.
    /// @return
    ///     Pointer to request
    static NetworkRequestPtr
    create();

    /// @brief Client-side factory method.
    /// @param fileName
    ///     directory name
    /// @return
    ///     Pointer to request
    static NetworkRequestPtr
    create( const std::string& dirName );

    // --- getter

    /// @return contents of the given directory, first element is the directory itsself. If the directory isn't
    /// readable, an empty vector is returned
    ///
    std::vector<FileInfo>
    getFiles()
    {
        return mFiles;
    }
    ~FileSystemRequest();

protected:
    virtual void
    sendRequestPayload( ClientConnection& connection,
                        ClientCallbackData* ) const;
    virtual void
    receiveRequestPayload( ServerConnection& connection,
                           ServerCallbackData* );
    virtual void
    sendResponsePayload( ServerConnection& connection,
                         ServerCallbackData* ) const;
    virtual void
    receiveResponsePayload( ClientConnection& connection,
                            ClientCallbackData* );

private:
    std::string           mDirName;
    std::vector<FileInfo> mFiles;
    bool                  isValid_; // false, if the directory isn't readable

    FileSystemRequest( const std::string& absolutePath );
};
}

#endif // CUBEFILESYSTEMREQUEST_H
