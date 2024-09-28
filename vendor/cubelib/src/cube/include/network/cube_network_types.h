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
 *  @brief   Declaration of types used for Cube networking.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_NETWORK_TYPES_H
#define CUBE_NETWORK_TYPES_H

#include <inttypes.h>

#include <memory>

namespace cube
{
/// @name Pointer types
/// @{

class ClientConnection;


typedef std::shared_ptr< ClientConnection > ClientConnectionPtr;

class Connection;


typedef std::shared_ptr< Connection > ConnectionPtr;

class NetworkRequest;


typedef std::shared_ptr< NetworkRequest > NetworkRequestPtr;

class ServerConnection;


typedef std::shared_ptr< ServerConnection > ServerConnectionPtr;

class Socket;


typedef std::shared_ptr< Socket > SocketPtr;

/// @}
/// @name Integer types
/// @{

/// Type used for protocol version numbers
typedef uint32_t protocol_version_t;

/// Type used for general ids
typedef uint64_t id_t;

/// Type used for request ids
typedef uint32_t request_id_t;

/// Type used for request sequence numbers
typedef uint64_t request_seq_t;


/// @}
/// @name Enumerations
/// @{

/**
 * List of network request IDs
 */
enum NetworkRequestId
{
    DISCONNECT_REQUEST = 0,        ///< Disconnect from server
    NEGOTIATE_PROTOCOL_REQUEST,    ///< Negotiate protocol version with server
    GET_VERSION_STRING_REQUEST,    ///< Exchange version strings
    OPEN_CUBE_REQUEST,             ///< Open Cube file
    CLOSE_CUBE_REQUEST,            ///< Close Cube file
    SAVE_CUBE_REQUEST,             ///< Save a copy of the Cube report
    DEFINE_METRIC_REQUEST,         ///< Define a new Metric
    METRIC_TREE_VALUES_REQUEST,    ///< Get Metric tree values based on cnode/region and system selections.
    CALL_TREE_VALUES_REQUEST,      ///< Get Call tree values based on metric and system selections.
    REGION_TREE_VALUES_REQUEST,    ///< Get Region/Flat tree values based on metric and system selections.
    SYSTEM_TREE_VALUES_REQUEST,    ///< Get System tree values based on metric and cnode/region selections.
    METRIC_SUBTREE_VALUES_REQUEST, ///< Get values for a subtree of the metric tree
    SUB_CALL_TREE_VALUES_REQUEST,  ///< Get values for a subtree of the call tree
    FILESYSTEM_REQUEST,            ///< Get remote file system information
    TREE_VALUE_REQUEST,            ///< Get tree value based on metric, call and system selections.
    MISC_DATA_REQUEST,             ///< Get misc data as byte array
    VERSION_REQUEST,               ///< Get CUBELIB_VERSION_NUMBER
    NUM_NETWORK_REQUESTS           ///< Number of network requests defined
};


/**
 * List of valid request acknowledgments
 */
enum NetworkRequestResponseCode
{
    REQUEST_OK = 0,              ///< The request could be processed.
    REQUEST_ERROR_RECOVERABLE,   ///< The request could not be processed, but data stream is still in a defined state.
    REQUEST_ERROR_UNRECOVERABLE, ///< The request could not be processed, and data stream is in undefined state.
};


/// @}
}

#endif    /* !CUBE_NETWORK_FWD_H */
