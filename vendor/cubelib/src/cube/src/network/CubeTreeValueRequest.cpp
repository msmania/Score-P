/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2015                                                     **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2015                                                     **
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
 *  @brief   Definition of the class cube::CubeTreeValueRequest
 **/
/*-------------------------------------------------------------------------*/


 #include <config.h>

#include "CubeTreeValueRequest.h"

#include <cassert>
#include <string>

#include "CubeClientConnection.h"
#include "CubeCnode.h"
#include "CubeError.h"
#include "CubeIoProxy.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeTypes.h"
#include "CubeValue.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;

NetworkRequestPtr
CubeTreeValueRequest::create()
{
    return std::shared_ptr<CubeTreeValueRequest>( new CubeTreeValueRequest() );
}


string
CubeTreeValueRequest::getName() const
{
    return "TreeValue";
}


NetworkRequest::id_t
CubeTreeValueRequest::getId() const
{
    return TREE_VALUE_REQUEST;
}


void
CubeTreeValueRequest::sendRequestPayload( ClientConnection& connection,
                                          ClientCallbackData* ) const
{
    // Send Metric selections
    connection << uint32_t( mMetricSelections.size() );
    for ( size_t i = 0; i < mMetricSelections.size(); ++i )
    {
        connection << mMetricSelections[ i ].first->get_id();
        connection << uint8_t( mMetricSelections[ i ].second );
    }

    // Send Cnode selections
    connection << uint32_t( mCnodeSelections.size() );
    for ( size_t i = 0; i < mCnodeSelections.size(); ++i )
    {
        connection << mCnodeSelections[ i ].first->get_id();
        connection << uint8_t( mCnodeSelections[ i ].second );
    }

    // Send Sysres selections
    connection << uint32_t( mSysresSelections.size() );
    for ( size_t i = 0; i < mSysresSelections.size(); ++i )
    {
        connection << mSysresSelections[ i ].first->get_id();
        connection << uint8_t( mSysresSelections[ i ].second );
    }
}


void
CubeTreeValueRequest::receiveRequestPayload( ServerConnection&   connection,
                                             ServerCallbackData* data )
{
    /// @pre Valid CallbackData object.
    assert( data );

    /// @pre Valid Cube file
    assert( data->getCube() );

    // Receive metric selections
    uint32_t numMetricSelections = connection.get< uint32_t >();
    for ( size_t i = 0; i < numMetricSelections; ++i )
    {
        uint32_t metric_id = connection.get< uint32_t >();
        Metric*  metric    = data->getCube()->getMetrics()[ metric_id ];

        uint8_t flavour = connection.get< uint8_t >();

        mMetricSelections.push_back( make_pair( metric, CalculationFlavour( flavour ) ) );
    }

    // Receive Cnode selections
    uint32_t numCnodeSelections = connection.get< uint32_t >();
    for ( size_t i = 0; i < numCnodeSelections; ++i )
    {
        uint32_t cnode_id = connection.get< uint32_t >();
        assert( cnode_id < data->getCube()->getCnodes().size() );

        Cnode* cnode = data->getCube()->getCnodes()[ cnode_id ];

        uint8_t flavour = connection.get< uint8_t >();

        mCnodeSelections.push_back( make_pair( cnode, CalculationFlavour( flavour ) ) );
    }

    // Receive system resource selections
    uint32_t numSysresSelections = connection.get< uint32_t >();
    for ( size_t i = 0; i < numSysresSelections; i++ )
    {
        uint32_t sysres_id = connection.get< uint32_t >();
        assert( sysres_id < data->getCube()->getSystemResources().size() );
        Sysres* sysres = data->getCube()->getSystemResources()[ sysres_id ];

        uint8_t flavour = connection.get< uint8_t >();

        mSysresSelections.push_back( make_pair( sysres, CalculationFlavour( flavour ) ) );
    }
}


void
CubeTreeValueRequest::processRequest( ServerCallbackData* data )
{
    /// @pre Valid CallbackData.
    assert( data );

    /// @pre Valid Cube object.
    assert( data->getCube() );

    try
    {
        valuePtr  = new Value * ( );
        *valuePtr = data->getCube()->calculateValue( mMetricSelections,
                                                     mCnodeSelections,
                                                     mSysresSelections );
    }
    catch ( const std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
}


void
CubeTreeValueRequest::sendResponsePayload( ServerConnection& connection,
                                           ServerCallbackData* ) const
{
    Value* value = *valuePtr;
    // Send value type first (all values have the same type)

    connection << uint32_t( value->myDataType() );

    value->toStream( connection );

    delete value;
}


void
CubeTreeValueRequest::receiveResponsePayload(
    ClientConnection& connection,
    ClientCallbackData* )
{
    uint32_t datatype_id = connection.get< uint32_t >();

    Value* value;
    value = selectValueOnDataType( DataType( datatype_id ) );
    value->fromStream( connection );
    *valuePtr = value;
}

CubeTreeValueRequest::CubeTreeValueRequest( const list_of_metrics&      metric_selections,
                                            const list_of_cnodes&       cnode_selections,
                                            const list_of_sysresources& sysres_selections,
                                            Value**                     value ) :
    mMetricSelections( metric_selections ),
    mCnodeSelections( cnode_selections ),
    mSysresSelections( sysres_selections ),
    valuePtr( value )
{
}


CubeTreeValueRequest::CubeTreeValueRequest()
{
    valuePtr = nullptr;
}


CubeTreeValueRequest::~CubeTreeValueRequest()
{
}


NetworkRequestPtr
cube::CubeTreeValueRequest::create( const list_of_metrics&      metric_selections,
                                    const list_of_cnodes&       cnode_selections,
                                    const list_of_sysresources& sysres_selections,
                                    Value**                     value )
{
    return std::shared_ptr<CubeTreeValueRequest>(
        new CubeTreeValueRequest( metric_selections,
                                  cnode_selections,
                                  sysres_selections,
                                  value ) );
}
