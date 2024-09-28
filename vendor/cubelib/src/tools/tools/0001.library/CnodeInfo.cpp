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
 *  \file CnodeInfo.cpp
 *  \brief Defines a CNodoInfo class.
 */

#include "config.h"
#include "CnodeInfo.h"
#include "Cube.h"
#include "CubeCnode.h"
#include "CubeRegion.h"

using namespace std;

namespace cube
{
CCnodeInfo::CCnodeInfo( const Cube* cube )
    : InfoObj( cube->get_cnodev().size() ),
    m_cnodes( cube->get_cnodev() )
{
    size_t ccnt( m_cnodes.size() );
    for ( size_t i = 0; i < ccnt; i++ )
    {
        /* don't forget to iterate from back to front
           or the algorithm may not work */
        classify_cnode( m_cnodes[ ccnt - i - 1 ] );
    }
}

const vector<Cnode*>&
CCnodeInfo::get_cnodev()
{
    return m_cnodes;
}
/**
 * Marks for "cnode", whether it is a general COM or MPI (OMP).
 */
void
CCnodeInfo::classify_cnode( Cnode* cnode )
{
    size_t        nodeId = cnode->get_id();
    CallpathType& typeref( m_types[ nodeId ] );
    if ( typeref == COM )
    {
        return;
    }
    const Region* region = cnode->get_callee();
    if ( region->get_descr() == "MPI" )
    {
        typeref = MPI;
        propagate_com( cnode );
        return;
    }
    if ( region->get_descr() == "OMP" )
    {
        typeref = OMP;
        propagate_com( cnode );
        return;
    }
}
/**
 * Set type of cnode for all parents of "cnode" as "COM".
 */
void
CCnodeInfo::propagate_com( Cnode* cnode )
{
    Cnode* parent = cnode->get_parent();
    while ( parent )
    {
        size_t parentId = parent->get_id();
        m_types[ parentId ] = COM;

        parent = parent->get_parent();
    }
}
}
