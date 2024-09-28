/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2023                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



/**
 * \file CubeInclusiveMetric.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric contains only inclusive values

 ********************************************/


#include "config.h"
#include <iostream>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"

#include "CubeInclusiveMetric.h"
#include "CubeServices.h"


using namespace std;
using namespace cube;


InclusiveMetric::~InclusiveMetric()
{
}


row_of_objects_t*
InclusiveMetric::create_calltree_id_maps( IDdeliverer* ids, Cnode* root, row_of_objects_t*   _row )
{
    WideSearchEnumerator enumerator;
    ids->reset();
    _row = enumerator.get_objects_to_enumerate( root, _row );

    for ( row_of_objects_t::iterator iter = _row->begin(); iter < _row->end(); ++iter )
    {
        if ( calltree_local_ids.size() <= ( *iter )->get_id() )
        {
            calltree_local_ids.resize( ( *iter )->get_id() + 1 );
        }
        calltree_local_ids[ ( *iter )->get_id() ] = ids->get_next_id();
    }

    return _row;
}









// pointlike means the vaue is not aggregated, but corresponds to the combination (cnode, location)
Value*
InclusiveMetric::get_sev_pointlike( const Cnode*             cnode,
                                    const CalculationFlavour cnf,
                                    const Sysres*            sys,
                                    const CalculationFlavour sf )
{
    Value* v = nullptr;

    if ( !active )   //  if value == VOID
    {
        return v;
    }

    if ( ( sys->isSystemTreeNode() || sys->isLocationGroup() ) && sf == cube::CUBE_CALCULATE_EXCLUSIVE )
    {
        return v;
    }
    if ( isCacheable() )
    {
        Value* cached_value = cache->getCachedValue( cnode, cnf, sys, sf );
        if ( cached_value != nullptr )
        {
            delete v;
            return cached_value;
        }
    }
    if ( sys->isSystemTreeNode() )
    {
        SystemTreeNode* _sys = ( SystemTreeNode* )sys;
        // first add values of all sub system nodes
        for ( unsigned i = 0; i < _sys->num_children(); ++i )
        {
            Value* _v = get_sev_pointlike( cnode, cnf, _sys->get_child( i ), cube::CUBE_CALCULATE_INCLUSIVE );
            if ( v == nullptr )
            {
                v = _v;
            }
            else
            {
                v->
                operator+=( _v );

                delete _v;
            }
        }
        // then add all values of all sub local groups
        for ( unsigned i = 0; i < _sys->num_groups(); ++i )
        {
            Value* _v = get_sev_pointlike( cnode, cnf, _sys->get_location_group( i ), cube::CUBE_CALCULATE_INCLUSIVE );
            if ( v == nullptr )
            {
                v = _v;
            }
            else
            {
                v->
                operator+=( _v );

                delete _v;
            }
        }
    }
    if ( sys->isLocationGroup() )
    {
        LocationGroup* _lg = ( LocationGroup* )sys;
        for ( unsigned i = 0; i < _lg->num_children(); ++i )
        {
            Value* _v = get_sev_pointlike( cnode, cnf, _lg->get_child( i ), cube::CUBE_CALCULATE_INCLUSIVE );
            if ( v == nullptr )
            {
                v = _v;
            }
            else
            {
                v->
                operator+=( _v );

                delete _v;
            }
        }
    }
    if ( sys->isLocation() )
    {
        Location* _loc = ( Location* )sys;
        Value*    _v   =  get_sev_elementary( cnode, _loc );
        v = _v;

        // if we calculate exclusive value, we have to substract all inclusive values of all not-hidden children (in call tree)
        if ( cnf == CUBE_CALCULATE_EXCLUSIVE &&  ( cnode->num_children() > 0 ) )
        {
            std::vector<const Cnode*>_cnodes;   // collection of cnodes for the calculation
            for ( cnode_id_t cid = 0; cid < cnode->num_children(); cid++  )
            {
                const Cnode* tmp_c = cnode->get_child( cid );
                bool         _add  = ( !tmp_c->isHidden() ); // skip hidden elements
                if ( _add )
                {
                    _cnodes.push_back( tmp_c );
                }
            }
            for ( std::vector<const Cnode*>::const_iterator _iter = _cnodes.begin(); _iter != _cnodes.end(); ++_iter )
            {
                const Cnode* tmp_c = *_iter;

                Location* _loc = ( Location* )sys;
                Value*    _v   =  get_sev_elementary( tmp_c, _loc );
                if ( v == nullptr )
                {
                    v = _v;
                }
                else
                {
                    v->
                    operator-=( _v ); // subtract value of every child using metrics "-" operator

                    delete _v;
                }
            }
        }
    }
    if ( isCacheable() )
    {
        cache->setCachedValue( v, cnode, cnf, sys, sf );
    }
    return v;
}




// aggregated means the value corresponds to the whole system tree for the selected cnode
Value*
InclusiveMetric::get_sev_aggregated( const Cnode*             cnode,
                                     const CalculationFlavour cnf )
{
    if ( !active )   //  if value == VOID
    {
        return adv_sev_mat->getValue();
    }
    Value* v = nullptr;
    if ( isCacheable() )
    {
        v = cache->getCachedValue( cnode, cnf );
        if ( v != nullptr )
        {
            return v;
        }
    }
    size_t sysv_size = this->sysv.size();
    for ( size_t i = 0; i < sysv_size; i++ )
    {
        Location* _loc = this->sysv[ i ];
        Value*    tmp  = get_sev_elementary( cnode, _loc );
        if ( v == 0 )
        {
            v = tmp;
        }
        else
        {
            v->
            operator+=( tmp );

            delete tmp;
        }
    }


    if ( cnf == CUBE_CALCULATE_EXCLUSIVE &&  ( cnode->num_children() > 0 ) )
    {
        std::vector<Cnode*>_cnodes;   // collection of cnodes for the calculation
        for ( cnode_id_t cid = 0; cid < cnode->num_children(); cid++  )
        {
            Cnode* tmp_c = cnode->get_child( cid );
            if ( !tmp_c->isHidden() )
            {
                _cnodes.push_back( tmp_c );
            }
        }
        for ( std::vector<Cnode*>::const_iterator _iter = _cnodes.begin(); _iter != _cnodes.end(); ++_iter )
        {
            Cnode* tmp_c     = *_iter;
            size_t sysv_size = this->sysv.size();
            for ( size_t i = 0; i < sysv_size; i++ )
            {
                Location* _loc = this->sysv[ i ];
                Value*    tmp  = get_sev_elementary( tmp_c, _loc );
                v->
                operator-=( tmp );

                delete tmp;
            }
        }
    }
    if ( isCacheable() )
    {
        cache->setCachedValue( v,  cnode, cnf );
    }
    return v;
}




Value*
InclusiveMetric::get_sev_native(
    const cube::Cnode*       cnode,
    const CalculationFlavour cnf,
    const cube::Sysres*      sys,
    const CalculationFlavour sf
    )
{
    if ( sys == nullptr )
    {
        return get_sev_aggregated( cnode, cnf );
    }
    return get_sev_pointlike( cnode, cnf, sys, sf );
}



Serializable*
cube::InclusiveMetric::create( Connection&      connection,
                               const CubeProxy& cubeProxy )
{
    return new InclusiveMetric( connection, cubeProxy );
}

std::string
cube::InclusiveMetric::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::InclusiveMetric::get_static_serialization_key()
{
    return "Metric|Inclusive|Generic";
}

cube::InclusiveMetric::InclusiveMetric( Connection&      connection,
                                        const CubeProxy& cubeProxy )
    : ValueMetric( connection, cubeProxy )
{
}
