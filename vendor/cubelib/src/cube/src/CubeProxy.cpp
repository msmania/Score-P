/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2019-2023                                                **
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
 *  @ingroup CUBE_lib.base
 *  @brief   Definition of the class CubeProxy.
 **/
/*-------------------------------------------------------------------------*/

#include "config.h"
#include "CubeProxy.h"

#include <cassert>
#include <iostream>
#include <limits>

#include "CubeIoProxy.h"
#include "CubeNetworkProxy.h"
#include "CubeUrl.h"
#include "Cube.h"

using namespace std;
using namespace cube;

namespace cube
{
void
cube4_diff( Cube* outCube,
            Cube* minCube,
            Cube* subCube,
            bool  subset,
            bool  collapse );
void
cube4_mean( Cube*          outCube,
            Cube**         cubes,
            const unsigned num,
            bool           subset,
            bool           collapse );

void
cube4_clean( Cube* outCube,
             Cube* lhsCube,
             bool  subset,
             bool  collapse );

void
cube4_merge( Cube*          outCube,
             Cube**         cubes,
             const unsigned num,
             bool           subset,
             bool           collapse,
             bool           strict = true );

void
create_from_tau( cube::Cube* cube,
                 const char* path );

void
create_for_scaling_plugin(  cube::Cube*    scaled,
                            cube::Cube**   cubes,
                            bool           aggregation,
                            const unsigned num );

const list_of_metrics      CubeProxy::ALL_METRICS;
const list_of_cnodes       CubeProxy::ALL_CNODES;
const list_of_regions      CubeProxy::ALL_REGIONS;
const list_of_sysresources CubeProxy::ALL_SYSTEMNODES;

CubeProxy::CubeProxy()
    : mUrl( "" ),
    mInitialized( false )
{
}


CubeProxy::~CubeProxy()
{
}

CubeProxy*
CubeProxy::create( std::string url_string )
{
    CubeProxy* obj = NULL;
    Url        url = Url( url_string );
    if ( url.getProtocol() == "cube" )
    {
        // open remote Cube via Client/Server
        obj = new CubeNetworkProxy( url.toString() );
        obj->defineAttribute( "cubename", obj->mUrl.toString() );
    }
    else
    {
        // open local Cube
        obj = new CubeIoProxy();
        obj->defineAttribute( "cubename", obj->mUrl.getPath() );
    }

    obj->mUrl = url;
    obj->setInitialized( true );

    return obj;
}

CubeProxy*
CubeProxy::create( Algorithm algo, std::vector<std::string> fileNames, std::vector<string> options )
{
    if ( fileNames.empty() )
    {
        throw cube::Error( "empty list of files in CubeProxy::create" );
    }
    if ( algo == ALGORITHM_DIFF && fileNames.size() != 2 )
    {
        throw cube::Error( "diff requires two filenames as argument" );
    }

    string protocol = Url( fileNames[ 0 ] ).getProtocol();
    for ( size_t i = 0; i < fileNames.size(); i++ )
    {
        Url url = Url( fileNames[ i ] );
        if ( url.getProtocol() != protocol )
        {
            throw cube::Error( "all files have to be either local or be placed on the same server" );
        }
    }

    CubeProxy* obj = NULL;
    if ( protocol == "file" )
    {
        cube::Cube** cubeList = NULL;
        cubeList = new Cube*[ fileNames.size() ];
        for ( size_t i = 0; i < fileNames.size(); i++ )
        {
            cubeList[ i ] = new Cube();
        }
        if ( algo != ALGORITHM_TAU )
        {
            for ( size_t i = 0; i < fileNames.size(); i++ )
            {
                cubeList[ i ]->openCubeReport( fileNames[ i ] );
            }
        }
        bool        collapse = false, reduce = false, aggregate = false;
        cube::Cube* result   = new Cube();
        switch ( algo ) // handle options of the algorithms
        {
            case ALGORITHM_DIFF:
            case ALGORITHM_MERGE:
            case ALGORITHM_MEAN:
            case ALGORITHM_SCALING:
                for ( size_t i = 0; i < options.size(); i++ )
                {
                    reduce    = ( options[ i ] == "reduce" ) ? true : reduce;
                    collapse  = ( options[ i ] == "collapse" ) ? true : collapse;
                    aggregate = ( options[ i ] == "aggregate" ) ? true : aggregate;
                }
                break;
            case  ALGORITHM_TAU:
            default:
                break;
        }
        switch ( algo )
        {
            case ALGORITHM_DIFF:
                cube4_diff( result, cubeList[ 0 ], cubeList[ 1 ], reduce, collapse );
                break;
            case ALGORITHM_MERGE:
                cube4_merge( result, cubeList, fileNames.size(), reduce, collapse );
                break;
            case ALGORITHM_MEAN:
                cube4_mean( result, cubeList, fileNames.size(), reduce, collapse );
                break;
            case ALGORITHM_TAU:
                if ( fileNames.size() > 1 )
                {
                    for ( size_t i = 0; i < fileNames.size(); i++ )
                    {
                        create_from_tau( cubeList[ i ], fileNames[ i ].c_str() );
                    }
                    cube4_merge( result, cubeList, fileNames.size(), reduce, collapse );
                }
                else
                {
                    create_from_tau( result, fileNames[ 0 ].c_str() );
                }
                break;
            case ALGORITHM_SCALING:
                create_for_scaling_plugin( result, cubeList, aggregate, fileNames.size() );
                break;
            default:
                break;
        }
        for ( size_t i = 0; i < fileNames.size(); i++ )
        {
            delete cubeList[ i ];
        }
        delete[] cubeList;

        obj = new CubeIoProxy( result );
        obj->setInitialized( true );
    }
    else if ( protocol == "cube" )
    {
        throw cube::Error( "not yet implemented" );
    }

    return obj;
}

bool
CubeProxy::isInitialized() const
{
    return mInitialized;
}


void
CubeProxy::setInitialized( bool initialized )
{
    mInitialized = initialized;
}


const Url&
CubeProxy::getUrl() const
{
    return mUrl;
}


void
CubeProxy::setUrlPath( const std::string& path )
{
    mUrl.setPath( path );
}
}    /* namespace cube */
