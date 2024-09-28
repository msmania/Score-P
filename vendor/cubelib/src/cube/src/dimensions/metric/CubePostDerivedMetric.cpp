/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2022                                                **
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
 * \file CubePostDerivedMetric.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric is defined as an expression

 ********************************************/


#include "config.h"
#include <iostream>
#include <cassert>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePostDerivedMetric.h"
#include "CubeServices.h"

using namespace std;
using namespace cube;


PostDerivedMetric::~PostDerivedMetric()
{
}


void
PostDerivedMetric::initialize()
{
    if ( evaluation != NULL )
    {
        evaluation->setRowSize( ntid );
    }
    if ( init_evaluation != NULL )
    {
        init_evaluation->setRowSize( ntid );
        init_evaluation->eval();
        delete init_evaluation;
        init_evaluation = NULL;
    }
}


double
PostDerivedMetric::aggr_operator( double a, double b ) const
{
    if ( aggr_aggr_evaluation != NULL )
    {
        return aggr_aggr_evaluation->eval( a, b );
    }
    return a + b;
}



double
PostDerivedMetric::get_sev_native(
    const list_of_cnodes&       cnodes,
    const list_of_sysresources& sysres
    )
{
    double to_return = 0;
    if ( !active ) //  if value == VOID
    {
        return to_return;
    }
    if ( aggr_aggr_evaluation == NULL  )
    {
        pre_calculation_preparation( cnodes, sysres );
        if ( evaluation != NULL )
        {
            to_return = evaluation->eval( cnodes, sysres );
        }
        post_calculation_cleanup();
    }
    else  // we specified aggr operator
    {
        list_of_sysresources _sysres;
        if ( sysres.empty() )
        {
            for ( size_t i = 0; i < sysv.size(); ++i )
            {
                sysres_pair pair;
                pair.first  = sysv[ i ];
                pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
                _sysres.push_back( pair );
            }
        }
        else
        {
            for ( list_of_sysresources::const_iterator siter = sysres.begin(); siter != sysres.end(); ++siter )
            {
                if ( siter->second == cube::CUBE_CALCULATE_INCLUSIVE )
                {
                    const std::vector<cube::Sysres*>& _s = siter->first->get_whole_subtree();
                    for ( std::vector<cube::Sysres*>::const_iterator _siter = _s.begin(); _siter != _s.end(); ++_siter )
                    {
                        sysres_pair pair;
                        pair.first  = *_siter;
                        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
                        _sysres.push_back( pair );
                    }
                }
            }
        }
        for ( list_of_sysresources::const_iterator siter = _sysres.begin(); siter != _sysres.end(); ++siter )
        {
            list_of_sysresources tmp_sysres;
            tmp_sysres.push_back( *siter );
            pre_calculation_preparation( cnodes, tmp_sysres );
            double _to_return = 0.;
            if ( evaluation != NULL )
            {
                _to_return = evaluation->eval( cnodes, tmp_sysres );
            }
            to_return = aggr_aggr_evaluation->eval( to_return, _to_return );
            post_calculation_cleanup();
        }
    }
    return to_return;
}

// -----------------row wise ----------------------------------------
double*
PostDerivedMetric::get_sevs_native(
    const list_of_cnodes& cnodes
    )
{
    double* to_return = NULL;
    if ( !active ) //  if value == VOID
    {
        return to_return;
    }
    pre_calculation_preparation( cnodes );
    list_of_sysresources sysres;

    if ( evaluation != NULL )
    {
        to_return = evaluation->eval_row( cnodes, sysres );
    }
    post_calculation_cleanup();
    return to_return;
}

//  --massive calculation of a system tree
void
PostDerivedMetric::get_system_tree_sevs_native( const list_of_cnodes&  cnodes,
                                                std::vector< double >& inclusive_values,
                                                std::vector< double >& exclusive_values
                                                )
{
    double* to_return = NULL;
    if ( !active ) //  if value == VOID
    {
        return;
    }
    pre_calculation_preparation( cnodes );

    inclusive_values.resize( sysresv.size(), 0. );
    exclusive_values.resize( sysresv.size(), 0. );

    list_of_sysresources sysres;

    if ( evaluation != NULL )
    {
        to_return = evaluation->eval_row( cnodes, sysres );
        if ( to_return != NULL )
        {
            for ( size_t i = 0; i < ntid; ++i )
            {
                exclusive_values[ sysv[ i ]->get_sys_id() ] = to_return[ i ];
                inclusive_values[ sysv[ i ]->get_sys_id() ] = to_return[ i ];
            }
            services::delete_raw_row( to_return );
        }
        for ( size_t i = 0; i < lgv.size(); ++i )
        {
            LocationGroup* lg = lgv[ i ];
            if ( aggr_aggr_evaluation == NULL )
            {
                sysres.clear();
                sysres_pair pair;
                pair.first  = lg;
                pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
                sysres.push_back( pair );
                pre_calculation_preparation_atomic( sysres );
                double to_return_incl = evaluation->eval( cnodes, sysres  );
                sysres.clear();
                pair.first  = lg;
                pair.second = cube::CUBE_CALCULATE_EXCLUSIVE;
                sysres.push_back( pair );
                pre_calculation_preparation_atomic( sysres );
                double to_return_excl = evaluation->eval( cnodes, sysres  );
                exclusive_values[ lg->get_sys_id() ] = to_return_excl;
                inclusive_values[ lg->get_sys_id() ] = to_return_incl;
            }
            else
            {
                for ( size_t s = 0; s < lg->num_children(); ++s )
                {
                    cube::Location* _loc = lg->get_child( s );
                    exclusive_values[ lg->get_sys_id() ] = 0;
                    inclusive_values[ lg->get_sys_id() ] = aggr_operator( inclusive_values[ lg->get_sys_id() ], inclusive_values[ _loc->get_sys_id() ] );
                }
            }
        }
        for ( size_t i = 0; i < stnv.size(); ++i )
        {
            SystemTreeNode* stn = stnv[ i ];
            if ( aggr_aggr_evaluation == NULL )
            {
                sysres.clear();
                sysres_pair pair;
                pair.first  = stn;
                pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
                sysres.push_back( pair );
                pre_calculation_preparation_atomic( sysres );
                double to_return_incl = evaluation->eval( cnodes, sysres  );
                pair.first  = stn;
                pair.second = cube::CUBE_CALCULATE_EXCLUSIVE;
                sysres.clear();
                sysres.push_back( pair );
                pre_calculation_preparation_atomic( sysres );
                double to_return_excl = evaluation->eval( cnodes, sysres  );
                exclusive_values[ stn->get_sys_id() ] = to_return_excl;
                inclusive_values[ stn->get_sys_id() ] = to_return_incl;
            }
            else
            {
                std::vector<Sysres*>& locs = stn->get_all_locations();
                for ( std::vector<Sysres*>::iterator siter = locs.begin(); siter != locs.end(); ++siter )
                {
                    cube::Location* _loc = static_cast<cube::Location*>( *siter );
                    exclusive_values[ stn->get_sys_id() ] = 0.;
                    inclusive_values[ stn->get_sys_id() ] = aggr_operator( inclusive_values[ stn->get_sys_id() ], inclusive_values[ _loc->get_sys_id() ] );
                }
            }
        }
    }
    post_calculation_cleanup();
}






Serializable*
cube::PostDerivedMetric::create( Connection&      connection,
                                 const CubeProxy& cubeProxy )
{
    return new PostDerivedMetric( connection, cubeProxy );
}

std::string
cube::PostDerivedMetric::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::PostDerivedMetric::get_static_serialization_key()
{
    return "PostDerivedMetric";
}

cube::PostDerivedMetric::PostDerivedMetric( Connection&      connection,
                                            const CubeProxy& cubeProxy )
    : BuildInTypeMetric<double>( connection, cubeProxy )
{
}


void
PostDerivedMetric::post_calculation_cleanup()
{
    cubepl_memory_manager->get_memory_initializer()->memory_cleanup( get_id() );
}


void
PostDerivedMetric::pre_calculation_preparation( const list_of_cnodes& cnodes )
{
    setup_cubepl_memory();
    setup_cubepl_memory_for_itself();
    for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
    {
        setup_cubepl_memory_for_cnode( c_iter->first, c_iter->second );
    }
}

void
PostDerivedMetric::pre_calculation_preparation( const list_of_cnodes&       cnodes,
                                                const list_of_sysresources& sysres
                                                )
{
    setup_cubepl_memory();
    setup_cubepl_memory_for_itself();
    for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
    {
        setup_cubepl_memory_for_cnode( c_iter->first, c_iter->second );
    }
    for ( list_of_sysresources::const_iterator s_iter = sysres.begin(); s_iter != sysres.end(); ++s_iter )
    {
        setup_cubepl_memory_for_sysres( s_iter->first, s_iter->second );
    }
}

void
PostDerivedMetric::pre_calculation_preparation_atomic( const list_of_sysresources& sysres
                                                       )
{
    for ( list_of_sysresources::const_iterator s_iter = sysres.begin(); s_iter != sysres.end(); ++s_iter )
    {
        setup_cubepl_memory_for_sysres( s_iter->first, s_iter->second );
    }
}



void
PostDerivedMetric::pre_calculation_preparation( const Cnode*             cnode,
                                                const CalculationFlavour cf,
                                                const Sysres*            sys,
                                                const CalculationFlavour sf  )
{
    ( void )sys;
    ( void )sf;
    setup_cubepl_memory();
    setup_cubepl_memory_for_itself();
    setup_cubepl_memory_for_cnode( cnode, cf );
}


void
PostDerivedMetric::pre_calculation_preparation_atomic( const Cnode*             cnode,
                                                       const CalculationFlavour cf,
                                                       const Sysres*            sys,
                                                       const CalculationFlavour sf  )
{
    ( void )cnode;
    ( void )cf;
    setup_cubepl_memory_for_sysres( sys, sf );
}

void
PostDerivedMetric::setup_cubepl_memory()
{
    cubepl_memory_manager->get_memory_initializer()->memory_new( get_id() );
}

void
PostDerivedMetric::setup_cubepl_memory_for_itself()
{
    cubepl_memory_manager->get_memory_initializer()->memory_setup( this, get_id() );
}

void
PostDerivedMetric::setup_cubepl_memory_for_cnode( const Cnode*             cnode,
                                                  const CalculationFlavour cf  )
{
    cubepl_memory_manager->get_memory_initializer()->memory_setup(  cnode, cf, get_id() );
    setup_cubepl_memory_for_region( cnode->get_callee() );
}

void
PostDerivedMetric::setup_cubepl_memory_for_region( const Region* region )
{
    cubepl_memory_manager->get_memory_initializer()->memory_setup( region, get_id()  );
}

void
PostDerivedMetric::setup_cubepl_memory_for_sysres( const Sysres*            sysres,
                                                   const CalculationFlavour sf  )
{
    cubepl_memory_manager->get_memory_initializer()->memory_setup(  sysres, sf, get_id() );
}
