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


#include <config.h>
#include <sys/types.h>
#include <cstdlib>
#include <cstdio>
#include <assert.h>
#include <unistd.h>
#include <inttypes.h>
#include <algorithm>
#include "scaling_calls.h"
#include "algebra4.h"


using namespace std;
using namespace cube;

static
bool
systemTreeCompare( const std::pair<cube::Cube*, cube::CubeMapping*>& a, const std::pair<cube::Cube*, cube::CubeMapping*>& b )
{
    return a.first->get_locationv().size() < b.first->get_locationv().size();
}



static
void
createScalingSystemTree( cube::Cube*           scaled,
                         const cube::Cube*     input,
                         cube::SystemTreeNode* root
                         )
{
    size_t n    = input->get_locationv().size();
    char*  name = new char[ 20 ]();
    snprintf( name, 20, "Measurement %zu", n );
    cube::SystemTreeNode* top = scaled->def_system_tree_node( name,
                                                              "",
                                                              "",
                                                              root );
    cube::LocationGroup* group = scaled->def_location_group( name,
                                                             n,
                                                             CUBE_LOCATION_GROUP_TYPE_PROCESS,
                                                             top );
    scaled->def_location( name,
                          n,
                          CUBE_LOCATION_TYPE_CPU_THREAD,
                          group );
    delete[] name;
}

static
void
copyData( cube::Cube*              scaled,
          cube::Cube&              input,
          const cube::CubeMapping& cubeMap,
          bool                     aggregation                 // vs. Maximum
          )
{
    std::map<cube::Metric*, cube::Metric*>::const_iterator miter;
    std::map<cube::Cnode*, cube::Cnode*>::const_iterator   citer;
    size_t                                                 num_metrics     = cubeMap.metm.size();
    size_t                                                 num_cnodes      = cubeMap.cnodem.size();
    size_t                                                 num_locations   = input.get_locationv().size();
    cube::Location*                                        target_location = NULL;
    const std::vector<cube::Location*>&                    _locs           = scaled->get_locationv();
    std::vector<cube::Location*>::const_iterator           siter           = _locs.begin();
    while ( siter != _locs.end() )
    {
        if ( ( size_t )( ( *siter )->get_rank() ) == num_locations )
        {
            target_location = *siter;
            break;
        }
        ++siter;
    }
    assert( target_location != NULL ); // should never happen

    size_t cnode_step = ( num_cnodes / 20 );
    cnode_step = ( cnode_step == 0 ) ? 1 : cnode_step;
    size_t i = 0;
    for ( miter = cubeMap.metm.begin(); miter != cubeMap.metm.end(); ++miter, ++i )
    {
        size_t j = 0;
        if ( miter->second->get_type_of_metric() == CUBE_METRIC_POSTDERIVED ||
             miter->second->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE ||
             miter->second->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE
             )
        {
            std::cerr << "\r     Skip " << i << "th metric "  << miter->first->get_uniq_name() << "( derived )" << std::endl;
            continue;
        }
        cube::CalculationFlavour calc_flavor = ( miter->second->get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
                                               ? cube::CUBE_CALCULATE_INCLUSIVE : cube::CUBE_CALCULATE_EXCLUSIVE;

        for ( citer = cubeMap.cnodem.begin(); citer != cubeMap.cnodem.end(); ++citer, ++j  )
        {
            if ( j % cnode_step == 0 )
            {
                std::cerr << "\r     Copy " << i << "th metric "  << miter->first->get_uniq_name() << " of " << num_metrics << " " << citer->first->get_id() << "(" << j << "/" << num_cnodes << ")" << std::flush;
            }

            Value* val = NULL;
            if ( aggregation )
            {
                val = input.get_sev_adv( miter->first, cube::CUBE_CALCULATE_INCLUSIVE, citer->first, calc_flavor );
            }
            else
            {
                const std::vector<cube::Location*>&          input_locs  = input.get_locationv();
                std::vector<cube::Location*>::const_iterator input_siter = input_locs.begin();
                for ( input_siter = input_locs.begin(); input_siter != input_locs.end(); ++input_siter )
                {
                    Value* _val = input.get_sev_adv( miter->first, cube::CUBE_CALCULATE_INCLUSIVE, citer->first, calc_flavor, *input_siter, cube::CUBE_CALCULATE_INCLUSIVE );
                    if ( val == NULL )
                    {
                        val = _val;
                    }
                    else if ( val->getDouble() < _val->getDouble() )
                    {
                        delete val;
                        val = _val;
                    }
                }
            }

            scaled->set_sev( miter->second, citer->second, target_location, val );
            delete val;
        }
    }
}



void
cube::create_for_scaling_plugin(  cube::Cube*    scaled,
                                  cube::Cube**   cubes,
                                  bool           aggregation,
                                  const unsigned num )
{
// TODO check whether we need to refresh the current preview or will it be changed by a new one

    scaled->set_post_initialization( true );
    std::vector<std::pair<cube::Cube*, cube::CubeMapping*> > cubeList;
    for ( size_t i = 0; i < num; i++ )
    {
        cube::CubeMapping*                         _cubeMapping = new CubeMapping();
        std::pair<cube::Cube*, cube::CubeMapping*> pair         = std::make_pair( cubes[ i ], _cubeMapping );
        cubeList.push_back( pair );
    }
    try
    {
        scaled->set_systemtree_title( "Scaling Tree" );
        cube::SystemTreeNode* top = scaled->def_system_tree_node( "All measurements",
                                                                  "",
                                                                  ""
                                                                  );
        for ( size_t i = 0; i < num; i++ )
        {
            metric_merge( *scaled, *( cubeList[ i ].first ), *( cubeList[ i ].second ) );
            region_merge( *scaled, *( cubeList[ i ].first ), *( cubeList[ i ].second ) );
            cnode_merge( *scaled, *( cubeList[ i ].first ), *( cubeList[ i ].second ) );
        }

        std::sort( cubeList.begin(), cubeList.end(), systemTreeCompare );

        for ( std::vector<std::pair<cube::Cube*, cube::CubeMapping*> >::const_iterator iter = cubeList.begin(); iter != cubeList.end(); ++iter )
        {
            createScalingSystemTree( scaled, ( iter->first ), top );
        }

        scaled->initialize();
        scaled->set_post_initialization( false );
        for ( std::vector<std::pair<cube::Cube*, cube::CubeMapping*> >::const_iterator iter = cubeList.begin(); iter != cubeList.end(); ++iter )
        {
            copyData( scaled, *( iter->first ), *( iter->second ), aggregation );
            iter->first->dropAllRowsInAllMetrics();
        }

        if ( !aggregation )
        {
            if ( scaled->get_met( "execution" ) != NULL )
            {
                // add speedup metric if wallclock time selected
                cube::Metric* met = scaled->def_met( "Speedup",
                                                     "speedup",
                                                     "DOUBLE",
                                                     "%",
                                                     "",
                                                     "",
                                                     "Calculates speedup using metric \"Execution\"",
                                                     NULL,
                                                     CUBE_METRIC_POSTDERIVED,
                                                     "{ return metric::call::execution(${calculation::callpath::id},i,3,i)/metric::execution(); }",
                                                     "",
                                                     "",
                                                     "",
                                                     "",
                                                     false );
                met->setCacheable( false );
                met->setConvertible( false );
            }
            else if ( scaled->get_met( "time" ) != NULL )
            {
                // add speedup metric if wallclock time selected
                cube::Metric* met = scaled->def_met( "Speedup",
                                                     "speedup",
                                                     "DOUBLE",
                                                     "%",
                                                     "",
                                                     "",
                                                     "Calculates speedup using metric \"Time\"",
                                                     NULL,
                                                     CUBE_METRIC_POSTDERIVED,
                                                     "{ return metric::call::time(${calculation::callpath::id},i,3,i)/metric::time(); }",
                                                     "",
                                                     "",
                                                     "",
                                                     "",
                                                     false );
                met->setCacheable( false );
                met->setConvertible( false );
            }
        }
    }
    catch ( const RuntimeError& e )
    {
        std::cerr << e.what() << std::endl;
    }

    for ( size_t i = 0; i < num; i++ )
    {
        delete cubeList[ i ].second;
    }
}
