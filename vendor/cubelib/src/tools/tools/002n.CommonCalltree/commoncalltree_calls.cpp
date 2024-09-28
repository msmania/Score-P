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
 * \file commoncalltree_calls.h
 * \brief provides calls  for cube_commoncalltree tool
 *
 */

#include "config.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <algorithm>

#include "Cube.h"
#include "CubeCnode.h"
#include "CubeMachine.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "algebra4-internals.h"

#include "commoncalltree_calls.h"

using namespace cube;
using namespace std;


bool
cube::CallPathAlphaLess( Vertex* a, Vertex* b )
{
    Cnode* _a = dynamic_cast<Cnode*> ( a );
    Cnode* _b = dynamic_cast<Cnode*> ( b );
    if ( ( _a == NULL ) || ( _b == NULL ) )
    {
        throw std::exception();
    }
    return
        (   ( _a->get_level() == _b->get_level() ) &&
            ( _a->get_callee()->get_name().compare( _b->get_callee()->get_name() ) <= 0 )
        )
        ||
        (
        ( _a->get_level() == _b->get_level() )
        &&
        ( _a->get_callee()->get_name() == _b->get_callee()->get_name()  )
        &&
        ( _a->get_callee()->get_mod().compare( _b->get_callee()->get_mod() ) < 0 )
        )
        ||
        (
        ( _a->get_level() == _b->get_level() )
        &&
        ( _a->get_callee()->get_name() ==  _b->get_callee()->get_name()  )
        &&
        ( _a->get_callee()->get_mod() ==  _b->get_callee()->get_mod()  )
        &&
        ( _a->get_callee()->get_begn_ln() < _b->get_callee()->get_begn_ln() )
        )
        ||
        (
        ( _a->get_level() == _b->get_level() )
        &&
        ( _a->get_callee()->get_name() ==  _b->get_callee()->get_name() )
        &&
        ( _a->get_callee()->get_mod() ==  _b->get_callee()->get_mod()  )
        &&
        ( _a->get_callee()->get_begn_ln() == _b->get_callee()->get_begn_ln() )
        &&
        ( _a->get_callee()->get_end_ln() < _b->get_callee()->get_end_ln() )
        )
    ;
}

bool
cube::CallPathAlphaEqual( Vertex* a, Vertex* b )
{
    Cnode* _a = dynamic_cast<Cnode*> ( a );
    Cnode* _b = dynamic_cast<Cnode*> ( b );
    if ( ( _a == NULL ) || ( _b == NULL ) )
    {
        throw std::exception();
    }

    return ( _a->get_level() == _b->get_level() )
           &&
           (  _a->get_callee()->get_name() ==  _b->get_callee()->get_name()  )
           &&
           (  _a->get_callee()->get_mod() ==  _b->get_callee()->get_mod() )
           &&
           ( _a->get_callee()->get_begn_ln() == _b->get_callee()->get_begn_ln() )
           &&
           ( _a->get_callee()->get_end_ln() == _b->get_callee()->get_end_ln() )
    ;
}





uint64_t
cube::update_strided_tree( Cnode* cnode, StridedCallTree& tree )
{
    StridedPair own_pair;
    own_pair.callpath = cnode;
    tree.push_back( own_pair );
    size_t   own_idx    = tree.size() - 1;
    uint64_t sum_stride = 0;

    vector<Vertex*>children =  cnode->get_children();
    if ( !children.empty() )
    {
        sort( children.begin(), children.end(), CallPathAlphaLess );
        for ( vector<Vertex*>::iterator c_iter = children.begin(); c_iter != children.end(); ++c_iter )
        {
            Cnode*   cnode  = dynamic_cast<Cnode*>( *c_iter );
            uint64_t stride = update_strided_tree( cnode, tree );
            sum_stride += stride;
        }
    }
    tree[ own_idx ].stride = sum_stride + 1;
    return sum_stride + 1;
};



StridedCallTree
cube::get_strided_tree( Cube& inCube )
{
    StridedCallTree tree;

    vector<Cnode*>roots = inCube.get_root_cnodev();
    sort( roots.begin(), roots.end(), CallPathAlphaLess );
    for ( vector<Cnode*>::iterator c_iter = roots.begin(); c_iter != roots.end(); ++c_iter )
    {
        Cnode* cnode = *c_iter;
        update_strided_tree( cnode, tree );
    }
    return tree;
};


MarkedForrest
cube::align_trees( StridedForrest& trees, vector<vector<size_t> >& running_indices )
{
    MarkedForrest markers;
    markers.resize( trees.size() );
    bool          run = true;
    vector<size_t>indices_set;
    indices_set.resize( trees.size(), 0 );

    while ( run ) // run till end of the first strided tree
    {
        size_t pivot = indices_set[ 0 ];
        bool   equal = true;
        for ( size_t idx = 1; idx < trees.size(); idx++ )
        {
            while ( !CallPathAlphaLess(
                        trees[ 0 ][ pivot ].callpath,
                        trees[ idx ][ indices_set[ idx ] ].callpath ) )
            {
                indices_set[ idx ] += trees[ idx ][ indices_set[ idx ] ].stride;
                if ( indices_set[ idx ] >= trees[ idx ].size() )
                {
                    equal = false;
                    run   = false;
                    break;
                }
            }
            if ( !run )
            {
                break;
            }

            if ( CallPathAlphaEqual(
                     trees[ 0 ][ pivot ].callpath,
                     trees[ idx ][ indices_set[ idx ] ].callpath ) )
            {
                equal &= true;
            }
            else
            {
                equal = false;
                break;
            }
        }
        if ( equal )
        {
            vector<size_t>indices_set_to_store = indices_set;
            running_indices.push_back( indices_set_to_store );
            for ( size_t idx = 0; idx < trees.size(); idx++ )
            {
                markers[ idx ][ trees[ idx ][ indices_set[ idx ] ].callpath ] =  cube::CUBE_CALLPATH_INCLUDE;
                indices_set[ idx ]++;
            }
        }
        else
        {
            indices_set[ 0 ] += trees[ 0 ][ pivot ].stride;
        }
        // step to next
        if ( !run )
        {
            break;
        }
        run &= ( indices_set[ 0 ] < trees[ 0 ].size() );
    }
    // here we have running_indices, which do point synchroniously on equal callpaths
    return markers;
}



void
cube::cube_common_calltree( Cube** incubes, Cube** outcubes, uint64_t num )
{
    vector<CubeMapping>mappings;
    mappings.resize( num );

    StridedForrest trees;
    trees.resize( num );

    vector<vector<size_t> >running_indices;
    ;
    running_indices.resize( num );


    StridedForrest reduced_trees;
    reduced_trees.resize( num );

    for ( uint64_t i = 0; i < num; ++i )
    {
        mirrors_copy( ( outcubes[ i ] ), ( incubes[ i ] ) );
        metric_merge( ( *outcubes[ i ] ), ( *incubes[ i ] ), mappings[ i ] );
        sysres_merge( ( *outcubes[ i ] ), ( *incubes[ i ] ), mappings[ i ], false, false );
        region_merge( ( *outcubes[ i ] ), ( *incubes[ i ] ), mappings[ i ]  );
        add_top( ( *outcubes[ i ] ), ( *incubes[ i ] ), mappings[ i ]  );
        trees[ i ] = get_strided_tree( ( *incubes[ i ] ) );
    }


    MarkedForrest markers = align_trees( trees, running_indices );
    const char*   output  = "_commoncalltree";
    for ( uint64_t i = 0; i < num; ++i )
    {
        create_common_calltree( ( *outcubes[ i ] ), ( *incubes[ i ] ), mappings[ i ], markers[ i ] );
        outcubes[ i ]->initialize();
        fill_with_data( ( *outcubes[ i ] ), ( *incubes[ i ] ), mappings[ i ], markers[ i ] );
        std::string newname = services::get_cube4_name( incubes[ i ]->get_cubename() ) + output;
        delete incubes[ i ];
        incubes[ i ] = nullptr;
        cout << "Writing " << ( newname ) << flush;
        outcubes[ i ]->writeCubeReport( newname );
        cout << "done." << endl;
        delete outcubes[ i ];
        outcubes[ i ] = nullptr;
    }
}; /* cube_common_calltree(...) */

void
cube::create_common_calltree(  Cube& outCube, Cube& inCube, CubeMapping& mapping, MarkedCallTree&  markers )
{
    vector<Cnode*>cnodes = inCube.get_cnodev();
    for ( vector<Cnode*>::iterator citer = cnodes.begin(); citer != cnodes.end(); ++citer )
    {
        Cnode*                   _cnode     = *citer;
        MarkedCallTree::iterator found_pair =  markers.find( _cnode );
        if ( found_pair != markers.end() )
        {
            if ( found_pair->second == cube::CUBE_CALLPATH_INCLUDE )
            {
                Cnode* tmp_cnode = found_pair->first;

                Region* _reg    = tmp_cnode->get_callee();
                Cnode*  _parent = tmp_cnode->get_parent();

                Cnode* newCnode = outCube.def_cnode( mapping.regionm[ _reg ],
                                                     tmp_cnode->get_mod(),
                                                     tmp_cnode->get_line(),
                                                     ( _parent == NULL ) ? NULL : mapping.cnodem[ _parent ] );
                mapping.cnodem[ tmp_cnode ]  = newCnode;
                mapping.r_cnodem[ newCnode ] = tmp_cnode;
            }
        }
    }
}; /* create_common_calltree(...) */


void
cube::fill_with_data(  Cube& outCube, Cube& inCube, CubeMapping& mapping, MarkedCallTree& markers )
{
    map<Metric*, Metric*>::iterator miter;
    map<Cnode*, Cnode*>::iterator   citer;
    map<Thread*, Thread*>::iterator siter;
    size_t                          num_metrics = mapping.metm.size();
    size_t                          num_cnodes  = mapping.cnodem.size();
    size_t                          cnode_step  = ( num_cnodes / 20 );
    cnode_step = ( cnode_step == 0 ) ? 1 : cnode_step;
    size_t i = 0;
    for ( miter = mapping.metm.begin(); miter != mapping.metm.end(); ++miter, ++i )
    {
        size_t                   j           = 0;
        cube::CalculationFlavour calc_flavor = ( miter->second->get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
                                               ? cube::CUBE_CALCULATE_INCLUSIVE : cube::CUBE_CALCULATE_EXCLUSIVE;
        for ( citer = mapping.cnodem.begin(); citer != mapping.cnodem.end(); ++citer, ++j  )
        {
            if ( j % cnode_step == 0 )
            {
                cerr << "\r     Copy " << i << "th metric "  << miter->first->get_uniq_name() << " of " << num_metrics << " (" << j << "/" << num_cnodes << ")" << flush;
            }
            std::vector<Cnode*>to_include;
            if ( calc_flavor == cube::CUBE_CALCULATE_EXCLUSIVE ) // for the exclusive metric we have to add explicitely all missing children
            {
                for ( size_t child_idx = 0; child_idx < citer->first->num_children(); child_idx++ )
                {
                    Cnode*                   _child      = citer->first->get_child( child_idx );
                    MarkedCallTree::iterator _found_pair =  markers.find( _child );
                    if ( _found_pair != markers.end()  && ( _found_pair->second != cube::CUBE_CALLPATH_INCLUDE ) )
                    {
                        to_include.push_back( _child );
                    }
                }
            }
            for ( siter = mapping.sysm.begin(); siter != mapping.sysm.end(); ++siter )
            {
                Value* val = inCube.get_sev_adv( miter->first, cube::CUBE_CALCULATE_INCLUSIVE, citer->first, calc_flavor,  siter->first, cube::CUBE_CALCULATE_EXCLUSIVE );
                if ( val == NULL )
                {
                    continue;
                }
                for ( std::vector<Cnode*>::iterator _children = to_include.begin(); _children != to_include.end(); ++_children )
                {
                    Value* _val = inCube.get_sev_adv( miter->first, cube::CUBE_CALCULATE_INCLUSIVE, *_children, cube::CUBE_CALCULATE_INCLUSIVE,  siter->first, cube::CUBE_CALCULATE_EXCLUSIVE );
                    ( *val ) += _val;
                    delete _val;
                }
                outCube.set_sev( miter->second, citer->second, siter->second, val );
                delete val;
            }
        }
        cerr << "\r     Copy " << i << "th metric "  << miter->first->get_uniq_name() << " of " << num_metrics << " (" << num_cnodes << "/" << num_cnodes << ")";
        cerr << endl;
    }
}

void
cube::print_strided_tree( StridedCallTree& tree )
{
    int i = 0;
    for ( StridedCallTree::iterator iter = tree.begin(); iter != tree.end(); ++iter, i++ )
    {
        StridedPair pair = *iter;
        cout << i << " (" << pair.callpath->get_id() << ":" << pair.callpath->get_callee()->get_name() << ":" << pair.stride << ")" << endl;
    }
};



void
cube::print_alligned_forrest( MarkedForrest& markers, StridedForrest& trees )
{
    size_t maxsize = 0;
    for ( size_t i = 0; i < trees.size(); i++ )
    {
        maxsize = std::max( maxsize, trees[ i ].size() );
    }


    for ( size_t j = 0; j < maxsize; j++ )
    {
        for ( size_t i = 0; i < trees.size(); i++ )
        {
            if ( j >= trees[ i ].size() )
            {
                cout << "  :- - ";
                continue;
            }
            cout << j << " " <<  markers[ i ][ trees[ i ][ j ].callpath ] << ":" << trees[ i ][ j ].callpath->get_id() << " " << trees[ i ][ j ].stride << " ";
        }
        cout << endl;
    }
};
