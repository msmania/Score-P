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
 *
 * \file CubeDenseIndex.cpp
 * \brief Providex methods for fast DenseIndex for dense data.
 ************************************************/

#include "config.h"
#include <iostream>
#include <istream>
#include "CubeError.h"
#include "CubeDenseIndex.h"

using namespace std;
using namespace cube;



index_t
DenseIndex::getPosition( cnode_id_t cid, thread_id_t tid )
{
// #warning "Error handling has to be done"
    if ( cid >= number_cnodes )
    {
        throw RuntimeError( "position_t DenseIndex::getPosition( cnode_id_t cid, thread_id_t tid ): Try to get a position of CID outside of maximal number of cnodes for current layout." ); // Further real Exception
    }
    if ( tid >= number_threads )
    {
        throw RuntimeError( "position_t DenseIndex::getPosition( cnode_id_t cid, thread_id_t tid ): Try to get a position of TID outside of maximal number of threads for current layout." );
    }
    ;                  // Further real Exception
    return ( index_t )( cid * number_threads + tid );
}

index_t
DenseIndex::getPosition( tuplet coords )
{
// #warning "Error handling has to be done"
    cnode_id_t  cid = coords.first;
    thread_id_t tid = coords.second;

    if ( cid >= number_cnodes )
    {
        throw RuntimeError( "position_t DenseIndex::getPosition( tuplet coords ): Try to get a position of CID outside of maximal number of cnodes for current layout." ); // Further real Exception
    }
    if ( tid >= number_threads )
    {
        throw RuntimeError( "position_t DenseIndex::getPosition( tuplet coords ): Try to get a position of TID outside of maximal number of threads for current layout." );
    }
    ;                                                                                                                // Further real Exception
    return getPosition( cid, tid );
}


index_t
DenseIndex::setPosition( cnode_id_t cid, thread_id_t tid )
{
    return getPosition( cid, tid );
}

index_t
DenseIndex::setPosition( tuplet coords )
{
    return getPosition( coords );
}


tuplet
DenseIndex::getPosition( index_t pos )
{
    tuplet coords;
    coords.first  = pos / number_threads;
    coords.second = pos % number_threads;
    return coords;
}

void
DenseIndex::readData( fstream& )
{
    read_only = true;
}
void
DenseIndex::writeData( fstream& )
{
}

void
DenseIndex::writeData( FILE* )
{
}



void
DenseIndex::printIndex()
{
}

void
DenseIndex::printSelf()
{
    cout << "Im a Dense Index" << endl;
}




void
DenseIndex::prepareOptimization()
{
};
bool
DenseIndex::toOptimize()
{
    return false;
};                                               // it is already optimal!
rows_pair
DenseIndex::exchange()
{
    rows_pair to_return;
    to_return.first  = 0;
    to_return.second = 0;
    return to_return;
}
