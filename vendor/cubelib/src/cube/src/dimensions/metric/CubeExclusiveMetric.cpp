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
 * \file CubeExclusiveMetric.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric contains only exclusive values

 ********************************************/


#include "config.h"
#include <iostream>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"

#include "CubeExclusiveMetric.h"
#include "CubeServices.h"


using namespace std;
using namespace cube;


ExclusiveMetric::~ExclusiveMetric()
{
}


row_of_objects_t*
ExclusiveMetric::create_calltree_id_maps( IDdeliverer* ids, Cnode* root, row_of_objects_t* _row  )
{
    ids->reset();
    DeepSearchEnumerator enumerator;
    _row = enumerator.get_objects_to_enumerate( root, _row );
    for ( row_of_objects_t::iterator iter = _row->begin(); iter < _row->end(); ++iter )
    {
        if ( calltree_local_ids.size() <= ( *iter )->get_id() )
        {
            calltree_local_ids.resize( ( *iter )->get_id() + 1  );
        }
        calltree_local_ids[ ( *iter )->get_id() ] = ids->get_next_id();
    }

    return _row;
}




// pointlike means the vaue is not aggregated, but corresponds to the combination (cnode, location)
Value*
ExclusiveMetric::get_sev_pointlike( const Cnode*             cnode,
                                    const CalculationFlavour cnf,
                                    const Sysres*            sys,
                                    const CalculationFlavour sf )
{
    Value* v =  nullptr;

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
        std::vector<const Cnode*>_cnodes;   // collection of cnodes for the calculation
        _cnodes.push_back( cnode );
        for ( cnode_id_t cid = 0; cid < cnode->num_children(); cid++  )
        {
            const Cnode* tmp_c = cnode->get_child( cid );
            bool         _add  = ( tmp_c->isHidden() ) || ( cnf == CUBE_CALCULATE_INCLUSIVE ); // either it is hidden, or we calculate inclusive value
            if ( _add )
            {
                _cnodes.push_back( tmp_c );
                const std::vector<Cnode*>& _vc = tmp_c->get_whole_subtree();
                for ( std::vector<Cnode*>::const_iterator _iter = _vc.begin(); _iter != _vc.end(); ++_iter )
                {
                    _cnodes.push_back( *_iter );
                }
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
                operator+=( _v );

                delete _v;
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
ExclusiveMetric::get_sev_aggregated( const cube::Cnode*       cnode,
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
    std::vector<const Cnode*>_cnodes;   // collection of cnodes for the calculation
    _cnodes.push_back( cnode );
    for ( cnode_id_t cid = 0; cid < cnode->num_children(); cid++  )
    {
        const Cnode* tmp_c = cnode->get_child( cid );
        bool         _add  = ( tmp_c->isHidden() ) || ( cnf == CUBE_CALCULATE_INCLUSIVE ); // either it is hidden, or we calculate inclusive value
        if ( _add )
        {
            _cnodes.push_back( tmp_c );
            const std::vector<Cnode*>& _vc = tmp_c->get_whole_subtree();
            for ( std::vector<Cnode*>::const_iterator _iter = _vc.begin(); _iter != _vc.end(); ++_iter )
            {
                _cnodes.push_back( *_iter );
            }
        }
    }

    for ( std::vector<const Cnode*>::const_iterator _iter = _cnodes.begin(); _iter != _cnodes.end(); ++_iter )
    {
        const Cnode* tmp_c     = *_iter;
        size_t       sysv_size = this->sysv.size();
        for ( size_t i = 0; i < sysv_size; i++ )
        {
            Location* _loc = this->sysv[ i ];
            Value*    tmp  = get_sev_elementary( tmp_c, _loc );
            if ( v == nullptr )
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
    }
    if ( isCacheable() )
    {
        cache->setCachedValue( v,  cnode, cnf );
    }
    return v;
}





Value*
ExclusiveMetric::get_sev_native(
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
cube::ExclusiveMetric::create( Connection&      connection,
                               const CubeProxy& cubeProxy )
{
    return new ExclusiveMetric( connection, cubeProxy );
}

std::string
cube::ExclusiveMetric::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::ExclusiveMetric::get_static_serialization_key()
{
    return "Metric|Exclusive|Generic";
}

cube::ExclusiveMetric::ExclusiveMetric( Connection&      connection,
                                        const CubeProxy& cubeProxy )
    : ValueMetric( connection, cubeProxy )
{
    /// @note Full packing and unpacking is done by Metric class.
}
