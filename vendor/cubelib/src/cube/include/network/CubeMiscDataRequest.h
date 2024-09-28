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


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Declaration of the class CubeMiscDataRequest
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_MISCDATAREQUEST_H
#define CUBE_MISCDATAREQUEST_H

#include <string>

#include "CubeNetworkRequest.h"

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   CubeMiscDataRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Simple class to get binary data from Cube.
 **/
/*-------------------------------------------------------------------------*/

class CubeMiscDataRequest
    : public NetworkRequest
{
public:
    /// @brief Virtual Desctructor.
    ///
    virtual
    ~CubeMiscDataRequest();

    /// @brief Server-side factory method.
    ///
    /// @return
    ///     Pointer to request.
    ///
    static NetworkRequestPtr
    create();

    /// Client-side factory method.
    ///
    /// @param name name to identify the misc data
    /// @param vec misc data
    /// @return
    ///     Pointer to created request
    ///
    static NetworkRequestPtr
    create( const std::string& name,
            std::vector<char>* vec );

    /// @brief Get the name of this request type.
    ///
    /// @return
    ///     String representation of request name.
    ///
    virtual std::string
    getName() const;

    /// @brief Get the unique network request ID.
    ///
    /// @return
    ///     Unique request Id defined in %cube::NetworkRequestId
    ///
    virtual NetworkRequest::id_t
    getId() const;

    /// @brief Server-side callback to execute after reception.
    ///
    /// @param data
    ///     Callback data structure.
    ///
    virtual void
    processRequest( ServerCallbackData* data );

protected:
    /// @brief Stream information from client to server.
    ///
    /// @param[in,out] connection
    ///     Reference to connection on client.
    /// @param[in,out] data
    ///     Pointer to callback data.
    ///
    virtual void
    sendRequestPayload( ClientConnection&   connection,
                        ClientCallbackData* data ) const;

    /// @brief Receive information from client on server.
    ///
    /// @param[inout] connection
    ///     Reference to connection on client.
    /// @param[inout] data
    ///     Pointer to callback data.
    ///
    virtual void
    receiveRequestPayload( ServerConnection&   connection,
                           ServerCallbackData* data );

    /// @brief Stream information from server to client.
    ///
    /// @param[in,out] connection
    ///     Reference to connection on client.
    /// @param[in,out] data
    ///     Pointer to callback data.
    ///
    virtual void
    sendResponsePayload( ServerConnection&   connection,
                         ServerCallbackData* data ) const;

    /// @brief Receive information from server on client.
    ///
    /// @param[in,out] connection
    ///     Reference to connection on client.
    /// @param[in,out] data Pointer to callback data.
    ///
    virtual void
    receiveResponsePayload( ClientConnection&   connection,
                            ClientCallbackData* data );


private:
    CubeMiscDataRequest( const std::string&,
                         std::vector<char>* data );
    std::string        name_;
    std::vector<char>* rawData;
};
}      /* namespace cube */

#endif /* !CUBE_MISCDATAREQUEST_H */
