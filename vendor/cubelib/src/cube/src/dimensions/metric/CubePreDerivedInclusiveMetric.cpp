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
 * \file CubePreDerivedInclusiveMetric.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric is defined as an expression. Expression gets calculated first, then the value gets aggregated.

 ********************************************/


#include "config.h"
#include "config.h"
#include <iostream>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePreDerivedInclusiveMetric.h"
#include "CubeServices.h"


using namespace std;
using namespace cube;


PreDerivedInclusiveMetric::~PreDerivedInclusiveMetric()
{
}


void
PreDerivedInclusiveMetric::initialize()
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



Serializable*
cube::PreDerivedInclusiveMetric::create( Connection&      connection,
                                         const CubeProxy& cubeProxy )
{
    return new PreDerivedInclusiveMetric( connection, cubeProxy );
}

cube::PreDerivedInclusiveMetric::PreDerivedInclusiveMetric( Connection&      connection,
                                                            const CubeProxy& cubeProxy )
    : InclusiveBuildInTypeMetric<double>( connection, cubeProxy )
{
    /// @note Full packing and unpacking is done by Metric class.
}

std::string
cube::PreDerivedInclusiveMetric::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::PreDerivedInclusiveMetric::get_static_serialization_key()
{
    return "PreDerivedMetric|Inclusive";
}


void
PreDerivedInclusiveMetric::post_calculation_cleanup()
{
    cubepl_memory_manager->get_memory_initializer()->memory_cleanup( get_id() );
}

void
PreDerivedInclusiveMetric::pre_calculation_preparation( const list_of_cnodes& cnodes )
{
    setup_cubepl_memory();
    setup_cubepl_memory_for_itself();
    for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
    {
        setup_cubepl_memory_for_cnode( c_iter->first, c_iter->second );
    }
}

void
PreDerivedInclusiveMetric::pre_calculation_preparation( const list_of_cnodes&       cnodes,
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
PreDerivedInclusiveMetric::pre_calculation_preparation_atomic( const Cnode*             cnode,
                                                               const CalculationFlavour cf,
                                                               const Sysres*            sys,
                                                               const CalculationFlavour sf  )
{
    ( void )cnode;
    ( void )cf;
    setup_cubepl_memory_for_sysres( sys, sf );
}

void
PreDerivedInclusiveMetric::pre_calculation_preparation( const Cnode*             cnode,
                                                        const CalculationFlavour cf,
                                                        const Sysres*            sys,
                                                        const CalculationFlavour sf  )
{
    setup_cubepl_memory();
    setup_cubepl_memory_for_itself();
    setup_cubepl_memory_for_cnode( cnode, cf );
    setup_cubepl_memory_for_sysres( sys, sf );
}

void
PreDerivedInclusiveMetric::setup_cubepl_memory()
{
    cubepl_memory_manager->get_memory_initializer()->memory_new( get_id() );
}

void
PreDerivedInclusiveMetric::setup_cubepl_memory_for_itself()
{
    cubepl_memory_manager->get_memory_initializer()->memory_setup( this, get_id() );
}

void
PreDerivedInclusiveMetric::setup_cubepl_memory_for_cnode( const Cnode*             cnode,
                                                          const CalculationFlavour cf  )
{
    cubepl_memory_manager->get_memory_initializer()->memory_setup(  cnode, cf, get_id() );
    setup_cubepl_memory_for_region( cnode->get_callee() );
}

void
PreDerivedInclusiveMetric::setup_cubepl_memory_for_region( const Region* region )
{
    cubepl_memory_manager->get_memory_initializer()->memory_setup( region, get_id()  );
}

void
PreDerivedInclusiveMetric::setup_cubepl_memory_for_sysres( const Sysres*            sysres,
                                                           const CalculationFlavour sf  )
{
    cubepl_memory_manager->get_memory_initializer()->memory_setup(  sysres, sf, get_id() );
}
