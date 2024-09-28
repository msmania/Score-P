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
 * \file RegionInfo.cpp
 * \brief Provides a class with an information about all callers for every
   region in a cube.s
 */


#include "config.h"
#include "Cube.h"
#include "CnodeInfo.h"
#include "RegionInfo.h"
#include "CubeRegion.h"
#include "helper.h"

namespace cube
{
using namespace std;
/**
 * Creates an object with region information and sets for all related callees
   a type (COM, MPI or OMP).
 */
CRegionInfo::CRegionInfo( const Cube* cube )
    : InfoObj( cube->get_regv().size() )
{
    const vector<Region*>& regions( cube->get_regv() );
    CCnodeInfo             cninfo( cube );
    size_t                 rcnt = regions.size();

    for ( size_t i = 0; i < rcnt; i++ )
    {
        Region*       region   = regions[ i ];
        size_t        regionId = region->get_id();
        CallpathType& typeref( m_types[ regionId ] );

        if ( region->get_descr() == "MPI" )
        {
            typeref = MPI;
            continue;
        }
        if ( region->get_descr() == "OMP" )
        {
            typeref = OMP;
            continue;
        }
        if ( region->get_descr() == "EPIK" )
        {
            typeref = EPK;
            continue;
        }

        const vector<Cnode*>& cnodev = region->get_cnodev();
        for ( size_t j = 0; j < cnodev.size(); j++ )
        {
            Cnode*       cnode   = cnodev[ j ];
            size_t       cnodeId = cnode->get_id();
            CallpathType cnodeType( cninfo[ cnodeId ] );
            if ( typeref == COM )
            {
                break;
            }
            typeref = cnodeType;
        }
    }
}
}
