/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2022                                                     **
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
 *  @brief   Declaration of the class CubeNetworkRequest
 *
 *  Declaration of the class CubeNetworkRequest.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_NETWORKREQUEST_H
#define CUBE_NETWORKREQUEST_H

#include <string>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <condition_variable>
#include <tuple>


#include "cube_network_types.h"

namespace cube
{
// Forward declarations
class Protocol;
class ServerCallbackData;
class ClientCallbackData;

/*-------------------------------------------------------------------------*/
/**
 *  @class   NetworkRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Abstract base class for Cube client-server network requests.
 *
 *  Abstract base class for Cube client-server network requests, providing
 *  the common interface for all requests. It enables a generic handling of
 *  such requests.
 *
 *  To derive a concrete network request implement the following virtual
 *  functions:
 *
 *  - @a getId
 *  - @a getName
 *  - @a sendRequestPayload
 *  - @a receiveRequestPayload
 *  - @a sendResponsePayload
 *  - @a receiveResponsePayload
 *
 *  Furthermore, static factory methods need to be implemented that
 *  - create a request object without input parameters (server side)
 *  - create a request with client-specific input parameters (client side)
 *
 **/
/*-------------------------------------------------------------------------*/

class NetworkRequest
{
public:
    /// Type name for the connection pointer
    typedef NetworkRequestPtr Ptr;

    /// Callback function to create a request object
    typedef NetworkRequestPtr (* factory_method_t)();

    /// Datatype used for request IDs
    typedef request_id_t id_t;

    /// Datatype used for unique request instance id
    typedef request_seq_t sequence_t;

    /// Datatype for markers in the request buffer
    typedef uint32_t marker_t;


    /// Identifiers for unregistered network requests
    static const id_t UNREGISTERED;

    /// @name Construction & destruction
    /// @{

    /// @brief Factory-method for creating network request objects on the
    ///     server side and receiving the request from client.
    ///
    static NetworkRequestPtr
    createFromStream( ServerConnection&   connection,
                      ServerCallbackData* data );

    /// Virtual base-class destructor
    virtual
    ~NetworkRequest();

    /// @}
    /// @name Request identification
    /// @{

    /// @brief Get a sequence number unique to all requests in the system.
    ///
    /// @return
    ///     Sequence number
    ///
    sequence_t
    getSequenceNumber() const;

    /// @brief Set sequence number of request object;
    ///
    void
    setSequenceNumber( sequence_t seqNo );

    /// @brief Get the unique network request ID.
    ///
    /// @return
    ///     Unique request Id
    ///
    virtual NetworkRequest::id_t
    getId() const = 0;

    /// @brief Return a human-readable string identifying request.
    ///
    /// @return
    ///     Request name.
    ///
    virtual std::string
    getName() const = 0;

    /// @}
    /// @name Connection interface
    /// @{

    /// @brief Indicating whether this request type is registered.
    ///
    /// @return
    ///     True if request is registered, false if not.
    ///
    bool
    isRegistered();

    /// @brief Send request to server.
    ///
    /// @param connection
    ///     Connection object on client
    /// @param data
    ///     Callback data structure.
    ///
    void
    sendRequest( ClientConnection&   connection,
                 ClientCallbackData* data ) const;

    /// @brief Server-side callback to execute after reception.
    ///
    /// @param data
    ///     Callback data structure.
    ///
    virtual void
    processRequest( ServerCallbackData* data );

    /// @brief Send response to client
    ///
    /// @param connection
    ///     Connection object on server
    /// @param data
    ///     Callback data structure.
    ///
    void
    sendResponse( ServerConnection&   connection,
                  ServerCallbackData* data ) const;

    /// @brief Standard reply on request handling errors
    ///
    /// @param connection
    ///     Active connection object on server
    /// @param responseCode
    ///     Response code for request
    /// @param errorMessage
    ///     String message with error details
    ///
    void
    sendErrorResponse( ServerConnection&          connection,
                       NetworkRequestResponseCode responseCode,
                       const std::string&         errorMessage ) const;

    /// @brief Receive Response from server.
    ///
    /// @param connection
    ///     Connection object on client
    ///
    void
    receiveResponse( ClientConnection&   connection,
                     ClientCallbackData* data );


    /**
     * @brief receiveResponseLoop is started in a separate thread when the connection is created and reads responses from server
     * @param connection Connection object on client
     */
    static void
    receiveResponseLoop( ClientConnection& connection );

    /** @brief stopLoop() stops the loop in @see receiveResponseLoop()
     */
    static void
    stopLoop();

    /// @brief Receive request body from client.
    ///
    /// @param connection
    ///     Connection object on server
    /// @param data
    ///     Callback data structure.
    ///
    void
    receiveRequestBody( ServerConnection&   connection,
                        ServerCallbackData* data );

protected:
    /// @brief Reset sequence number (e.g., after protocol change)
    ///
    static void
    resetRequestCounter();

    /// @brief Stream information from client to server.
    ///
    /// @param connection
    ///     Reference to connection on client.
    ///
    virtual void
    sendRequestPayload( ClientConnection&   connection,
                        ClientCallbackData* data ) const;

    /// @brief Receive information from client on server.
    ///
    /// @param connection
    ///     Reference to connection on client.
    ///
    virtual void
    receiveRequestPayload( ServerConnection&   connection,
                           ServerCallbackData* data );

    /// @brief Stream information from server to client.
    ///
    /// @param connection Reference to connection on client.
    ///
    virtual void
    sendResponsePayload( ServerConnection&   connection,
                         ServerCallbackData* data ) const;

    /// @brief Receive information from server on client.
    ///
    /// @param connection
    ///     Reference to connection on client.
    ///
    virtual void
    receiveResponsePayload( ClientConnection&   connection,
                            ClientCallbackData* data );

    /// @}
    /// @name Construction & destruction
    /// @{

    /// Default constructor to control request creation
    NetworkRequest();

    /// @}


private:
    /// registered Id of this handler in a given protocol
    id_t mId;

    /// Sequence number of a specific instance
    sequence_t mSequenceNo;

    /// Static counter of request constructions
    static sequence_t mNumRequests;

    /// ---  thread synchronisation for clients, server synchronisation mutexes belong to ServerConnection ---
    static std::mutex cmutex; // mutex used for construction (incrementing sequence number)

    // mSequenceNo -> corresponding condition "responseCondition"
    static std::unordered_map<sequence_t, std::tuple<std::condition_variable*, cube::NetworkRequest*, cube::ClientCallbackData*> > conditions;

    std::mutex              responseConditionMutex;           // -> conditions hash
    std::condition_variable responseCondition;                // signals that response body can be read
    static std::mutex       responseFinishedMutex;
    static std::mutex       conditionHashMutex;
    static bool             loopIsStopped;
    /// ---  end thread synchronisation ---

    /** the reading of response headers is done in a separate thread which calls receiveResponseHeader and notifies the corresponding request */
    static sequence_t
    receiveResponseHeader( ClientConnection& connection );
    void
    receiveResponseData( ClientConnection&   connection,
                         ClientCallbackData* data );

    friend class Protocol;
};
}      /* namespace cube */

#endif /* !CUBE_NETWORKREQUEST_H */
