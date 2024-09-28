/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2020                                                     **
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
 *  @brief   Declaration of the class cube::CubeTreeValueRequest.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_TREEVALUEREQUEST
#define CUBE_TREEVALUEREQUEST

#include "CubeCnode.h"
#include "CubeMetric.h"
#include "CubeSysres.h"
#include "CubeNetworkRequest.h"

namespace cube
{
// Forward declarations
class Value;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::TreeValueRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Retrieve the inclusive and/or exclusive values for a Cnode subtree.
 **/
/*-------------------------------------------------------------------------*/

class CubeTreeValueRequest
    : public NetworkRequest
{
public:
    /// @brief Virtual destructor.
    ///
    virtual
    ~CubeTreeValueRequest();

    /// Client-side factory method.
    ///
    /// @param metric_selections
    ///     The selected metrics
    /// @param cnode_selections
    ///     The selected cnodes
    /// @param sysres_selections
    ///     The selected system resources
    /// @param value
    ///     Result
    /// @return
    ///     Pointer to created request
    ///
    static NetworkRequestPtr
    create( const list_of_metrics&      metric_selections,
            const list_of_cnodes&       cnode_selections,
            const list_of_sysresources& sysres_selections,
            Value**                     value );

    /// @brief Server-side factory method.
    ///
    /// @return Pointer to created request
    ///
    static NetworkRequestPtr
    create();

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
    /// @param[in,out] connection
    ///     Reference to connection on client.
    /// @param[in,out] data
    ///     Pointer to callback data.
    ///
    virtual void
    receiveRequestPayload( ServerConnection&   connection,
                           ServerCallbackData* data );

    /// @brief Server-side callback to execute after reception.
    ///
    /// @param data
    ///     Callback data structure.
    ///
    virtual void
    processRequest( ServerCallbackData* data );

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
    /// @brief Client-side constructor used by factory method
    CubeTreeValueRequest( const list_of_metrics&      metric_selections,
                          const list_of_cnodes&       cnode_selections,
                          const list_of_sysresources& sysres_selections,
                          Value**                     value );

    /// @brief Server-side constructor.
    ///
    CubeTreeValueRequest();

    /// Metric selections
    list_of_metrics mMetricSelections;

    /// Cnode selections
    list_of_cnodes mCnodeSelections;

    /// Sysres selections
    list_of_sysresources mSysresSelections;

    Value** valuePtr;
};
}      // namespace cube

#endif // ! CUBE_CALLSUBTREEVALUESREQUEST_H
