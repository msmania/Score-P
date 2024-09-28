/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2021                                                **
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
#include "tau2cube_calls.h"



using namespace std;
using namespace cube;


typedef std::map<const TauMetric*, const cube::Metric*> t_tmet2cmet;     // /< Connects metrics in TAU und CUBE
typedef std::map<const TauRegion*, const cube::Region*> t_treg2creg;     // /< Connects regione in TAU und CUBE
typedef std::map<const TauCpath*, const cube::Cnode*>   t_tcpath2ccnode; // /< Connects callpaths in TAU und CUBE
typedef std::map<const TauLoc*, const cube::Thread*>    t_tloc2cthrd;    // /< Connects threads in TAU und CUBE

// call tree structure
typedef std::map<const TauCpath*, const TauCpath*>          t_tcpath2parent; // /< Creates a tree structure of TAU callpath (object->parent)
typedef std::map<const TauCpath*, vector<const TauCpath*> > t_tcpath2childv; // /< Creates a tree structure of TAU callpath (object->child)

typedef cube::Metric*                                       t_met_calls;







/**
 * Looks in TAU profile for such root, which contains "cpath" and returns it.
 *
 * It runs over second level of cpath[i] and checks, if "cpath" is saved and identical.
   If not -> breaks and returns NULL. If yes und size of cpath[i] the same -> returns cpath[i];

 */
static
const TauCpath*
get_parent_cpath( const TauProfile* tauprof, const TauCpath* cpath )
{
    const TauCpath* result = NULL;

    // is root?
    if ( cpath->size() == 1 )
    {
        return NULL;
    }
    for ( int i = 0; i < tauprof->get_ncpaths(); i++ )
    {
        if ( tauprof->get_cpath( i )->size() + 1 !=  cpath->size() )
        {
            continue;
        }

        for ( size_t j = 0; j < cpath->size(); j++ )
        {
            if ( j == cpath->size() - 1 )
            {
                result = tauprof->get_cpath( i );
            }
            else if ( *( *cpath )[ j ] != *( *tauprof->get_cpath( i ) )[ j ] )
            {
                break;
            }
        }
    }
    if ( result == NULL )
    {
        cerr << endl;
        cerr << "ERROR: Incomplete TAU call tree." << endl;
        cerr << "Only 1-level, 2-level or full call-path profiles supported." << endl;
        cerr << *cpath << endl;
    }
    return result;
}









/**
 * Creates metrics in cube with the same name, character (time or not) and so on
   and saves it in the "connection TAU metric -> CUBE metric"
 */
static
void
create_metric_dim( const TauProfile* tauprof, cube::Cube* cube, t_tmet2cmet& tmet2cmet, t_met_calls& met_calls )
{
    for ( int i = 0; i < tauprof->get_nmets(); i++ )
    {
        string uom, descr;
        if ( tauprof->get_met( i )->is_time() )
        {
            descr = "Time in seconds";
            uom   = "sec";
        }
        else
        {
            descr = "";
            uom   = "occ";
        }
        tmet2cmet[ tauprof->get_met( i ) ] = cube->def_met( tauprof->get_met( i )->get_name(), tauprof->get_met( i )->get_name(), "INTEGER", uom, "", "", descr, NULL, cube::CUBE_METRIC_INCLUSIVE );
    }
    met_calls = cube->def_met( "CALLS", "CALLS", "INTEGER", "occ", "", "", "Number of calls", NULL, cube::CUBE_METRIC_INCLUSIVE );
}








/**
 * Recursiv creating of cnode's in cube, corresponding to the TAU call path.
 */
static
void
create_call_tree( const TauCpath*  cpath,
                  cube::Cube*      cube,
                  t_treg2creg&     treg2creg,
                  t_tcpath2ccnode& tcpath2ccnode,
                  t_tcpath2parent& tcpath2parent,
                  t_tcpath2childv& tcpath2childv
                  )
{
    const TauRegion* callee = ( *cpath )[ cpath->size() - 1 ];
    tcpath2ccnode[ cpath ] = cube->def_cnode( const_cast<cube::Region*> ( treg2creg[ callee ] ), "", -1, const_cast<cube::Cnode*> ( tcpath2ccnode[ tcpath2parent[ cpath ] ] ) );

    for ( size_t i = 0; i < tcpath2childv[ cpath ].size(); i++ )
    {
        create_call_tree( tcpath2childv[ cpath ][ i ], cube, treg2creg, tcpath2ccnode, tcpath2parent, tcpath2childv );
    }
}








/**
 * Creates the dimension "programm" in cube
 */
static
void
create_program_dim( const TauProfile* tauprof,
                    cube::Cube*       cube,
                    t_treg2creg&      treg2creg,
                    t_tcpath2ccnode&  tcpath2ccnode,
                    t_tcpath2parent&  tcpath2parent,
                    t_tcpath2childv&  tcpath2childv )
{
    // identify parent and child nodes
    for ( int i = 0; i < tauprof->get_ncpaths(); i++ )
    {
        const TauCpath* child  = tauprof->get_cpath( i );
        const TauCpath* parent = get_parent_cpath( tauprof, child );
        tcpath2parent[ child ] = parent;
        tcpath2childv[ parent ].push_back( child ); // tcpath2childv[NULL] = root vector
    }
    // create regions
    for ( int i = 0; i < tauprof->get_nregions(); i++ )
    {
        treg2creg[ tauprof->get_region( i ) ] = cube->def_region( tauprof->get_region( i )->get_name(), tauprof->get_region( i )->get_name(), "tau", "unknown", -1, -1, "", "", "" );
    }

    // create call tree
    tcpath2ccnode[ NULL ] = NULL;

    // determine whether the profile is a true call-path profile
    bool is_flat = true;
    for ( size_t i = 0; i < tcpath2childv[ NULL ].size(); i++ )
    {
        if ( !tcpath2childv[ tcpath2childv[ NULL ][ i ] ].empty() )
        {
            is_flat = false;
        }
    }

    vector<const TauCpath*> rootv;

    // if true call-path profile then eliminate all roots without children
    for ( size_t i = 0; i < tcpath2childv[ NULL ].size(); i++ )
    {
        if ( is_flat  ||  ( !tcpath2childv[ tcpath2childv[ NULL ][ i ] ].empty() ) )
        {
            rootv.push_back( tcpath2childv[ NULL ][ i ] );
        }
    }
    for ( size_t i = 0; i < rootv.size(); i++ )
    {
        create_call_tree( rootv[ i ], cube, treg2creg, tcpath2ccnode, tcpath2parent, tcpath2childv );
    }
}







/**
 * Create a fictional one-node machine, corresponding to the TAU location.
 */
static
void
create_system_dim( const TauProfile* tauprof, cube::Cube* cube, t_tloc2cthrd& tloc2cthrd )
{
    // create machine with one node
    // Cube3 compatibility mode, should be reconsidered
    const cube::Node* node = cube->def_node( "Node", cube->def_mach( "Machine", "Created by tau2cube" ) );

    // create processes & threads
    std::map<int, const cube::Process*> proc_id2cproc;

    for ( int i = 0; i < tauprof->get_nlocs(); i++ )
    {
        const TauLoc* loc = tauprof->get_loc( i );

        long proc_id = loc->get_proc_id();
        long thrd_id = loc->get_thrd_id();


        // create process if needed
        const cube::Process*                                cproc = NULL;
        std::map<int, const cube::Process*>::const_iterator pit   = proc_id2cproc.find( proc_id );
        if ( pit != proc_id2cproc.end() )
        {
            cproc = pit->second;
        }
        else
        {
            cproc                    = cube->def_proc( "", proc_id, const_cast<cube::Node*>( node ) );
            proc_id2cproc[ proc_id ] = cproc;
        }
        // create thread if needed
        tloc2cthrd[ loc ] = cube->def_thrd( "", thrd_id, const_cast<cube::Process*>( cproc ) );
    }
}





/**
 * Fill the severieties matrix in the cube with values in TAU profile.
 */
static
void
enter_severity( const TauProfile* tauprof,
                cube::Cube*       cube,
                t_tmet2cmet&      tmet2cmet,
                t_tcpath2ccnode&  tcpath2ccnode,
                t_tloc2cthrd&     tloc2cthrd,
                t_met_calls&      met_calls )
{
    for ( int i = 0; i < tauprof->get_nmets(); i++ )
    {
        for ( int j = 0; j < tauprof->get_ncpaths(); j++ )
        {
            for ( int k = 0; k < tauprof->get_nlocs(); k++ )
            {
                const TauMetric* met   = tauprof->get_met( i );
                const TauCpath*  cpath = tauprof->get_cpath( j );
                const TauLoc*    loc   = tauprof->get_loc( k );
                const TauData*   data  = tauprof->get_data( met, cpath, loc );

                // check whether call path has been removed
                if ( tcpath2ccnode.find( cpath ) == tcpath2ccnode.end() )
                {
                    continue;
                }

                double value  = 0.;
                long   ncalls = 0;

// / --------- new code , for CUBE 4 --------------
                if ( data != NULL )
                {
                    value  = data->get_incl();
                    ncalls = data->get_ncalls();
                }

                // convert time values from microseconds to seconds
                if ( met->is_time() )
                {
                    value = value / 1000000;
                }

                cube->set_sev( const_cast<cube::Metric*>( tmet2cmet[ met ] ),
                               const_cast<cube::Cnode*>( tcpath2ccnode[ cpath ] ),
                               const_cast<cube::Thread*>( tloc2cthrd[ loc ] ),
                               value );

                // take number of calls from first metric
                if ( i == 0 )
                {
                    cube->set_sev( const_cast<cube::Metric*>( met_calls ),
                                   const_cast<cube::Cnode*>( tcpath2ccnode[ cpath ] ),
                                   const_cast<cube::Thread*>( tloc2cthrd[ loc ] ),
                                   ncalls );
                }
            }
        }
    }
}

/**
 * @brief create_from_tau reads a tau profile and creates a cube with it's data
 * @param cube cube object with tau data
 * @param path path of the tau measurements
 */
void
cube::create_from_tau( cube::Cube* cube, const char* path )
{
    t_tmet2cmet     tmet2cmet;     // /< Connects metrics in TAU und CUBE
    t_treg2creg     treg2creg;     // /< Connects regione in TAU und CUBE
    t_tcpath2ccnode tcpath2ccnode; // /< Connects callpaths in TAU und CUBE
    t_tloc2cthrd    tloc2cthrd;    // /< Connects threads in TAU und CUBE

    // call tree structure
    t_tcpath2parent tcpath2parent; // /< Creates a tree structure of TAU callpath (object->parent)
    t_tcpath2childv tcpath2childv; // /< Creates a tree structure of TAU callpath (object->child)

    t_met_calls met_calls;



    TauProfile tauprof( path );
    // create metric dimension
    create_metric_dim( &tauprof, cube, tmet2cmet, met_calls );
    // create program dimension
    create_program_dim( &tauprof, cube, treg2creg, tcpath2ccnode, tcpath2parent, tcpath2childv );
    // create system dimension
    create_system_dim( &tauprof, cube, tloc2cthrd );
    // enter severity data
    cube->initialize();
    enter_severity( &tauprof, cube, tmet2cmet, tcpath2ccnode, tloc2cthrd, met_calls );
}
