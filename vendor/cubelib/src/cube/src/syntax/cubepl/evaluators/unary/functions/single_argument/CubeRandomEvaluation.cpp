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



#include "config.h"
#include <cmath>
#include <cstdlib>
#include "CubeRandomEvaluation.h"
using namespace cube;
using namespace std;


RandomEvaluation::RandomEvaluation()
{
};


RandomEvaluation::~RandomEvaluation()
{
}

double
RandomEvaluation::eval() const
{
    double                           scale = arguments[ 0 ]->eval();
    std::uniform_real_distribution<> random_position( 0, scale );
    return random_position( gen );
}



double
RandomEvaluation::eval( const cube::Cnode*       _cnode,
                        const CalculationFlavour _cf,
                        const cube::Sysres*      _sf,
                        const CalculationFlavour _tf   ) const
{
    double _scale = arguments[ 0 ]->eval(     _cnode, _cf,
                                              _sf, _tf
                                              );
    std::uniform_real_distribution<> random_position( 0, _scale );
    return random_position( gen );
}



double
RandomEvaluation::eval( const cube::Cnode*       _cnode,
                        const CalculationFlavour _cf ) const
{
    double _scale = arguments[ 0 ]->eval(     _cnode, _cf
                                              );

    std::uniform_real_distribution<> random_position( 0, _scale );
    return random_position( gen );
}

double
RandomEvaluation::eval( double arg1, double arg2 ) const
{
    double                           _scale = arguments[ 0 ]->eval( arg1, arg2 );
    std::uniform_real_distribution<> random_position( 0, _scale );
    return random_position( gen );
}
double*
RandomEvaluation::eval_row( const Cnode*             _cnode,
                            const CalculationFlavour _cf ) const
{
    double* result =  arguments[ 0 ]->eval_row( _cnode, _cf );
    if ( result == NULL )
    {
        return NULL;
    }
    for ( size_t i = 0; i < row_size; i++ )
    {
        double                           _scale = result[ i ];
        std::uniform_real_distribution<> random_position( 0, _scale );
        result[ i ] =  random_position( gen );
    }
    return result;
}


double
RandomEvaluation::eval( const list_of_cnodes&       lc,
                        const list_of_sysresources& ls ) const
{
    double                           _scale = arguments[ 0 ]->eval( lc, ls );
    std::uniform_real_distribution<> random_position( 0, _scale );
    return random_position( gen );
}
double*
RandomEvaluation::eval_row( const list_of_cnodes&       lc,
                            const list_of_sysresources& ls ) const
{
    double* result =  arguments[ 0 ]->eval_row( lc, ls );
    if ( result == NULL )
    {
        return NULL;
    }
    for ( size_t i = 0; i < row_size; i++ )
    {
        double                           _scale = result[ i ];
        std::uniform_real_distribution<> random_position( 0, _scale );
        result[ i ] =  random_position( gen );
    }
    return result;
}
