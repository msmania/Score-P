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
#include <algorithm>

#include "CubeMaxEvaluation.h"
using namespace cube;
using namespace std;


MaxEvaluation::MaxEvaluation()
{
};


MaxEvaluation::~MaxEvaluation()
{
}

double
MaxEvaluation::eval() const
{
    return std::max( arguments[ 0 ]->eval(), arguments[ 1 ]->eval() );
}


double
MaxEvaluation::eval( const cube::Cnode*       _cnode,
                     const CalculationFlavour _cf,
                     const cube::Sysres*      _sf,
                     const CalculationFlavour _tf   ) const
{
    return std::max( arguments[ 0 ]->eval(    _cnode, _cf,
                                              _sf, _tf
                                              ),
                     arguments[ 1 ]->eval( _cnode, _cf,
                                           _sf, _tf
                                           )
                     );
}

double
MaxEvaluation::eval( const cube::Cnode*       _cnode,
                     const CalculationFlavour _cf ) const
{
    return std::max( arguments[ 0 ]->eval(    _cnode, _cf
                                              ),
                     arguments[ 1 ]->eval(     _cnode, _cf
                                               )
                     );
}

double
MaxEvaluation::eval( double arg1, double arg2 ) const
{
    return std::max( arguments[ 0 ]->eval( arg1, arg2 ),
                     arguments[ 1 ]->eval( arg1, arg2 )
                     );
}

double*
MaxEvaluation::eval_row( const Cnode*             _cnode,
                         const CalculationFlavour _cf ) const
{
    double* result  = arguments[ 0 ]->eval_row( _cnode, _cf );
    double* _result = arguments[ 1 ]->eval_row( _cnode, _cf );
    if ( result == NULL && _result == NULL )
    {
        return NULL;
    }
    if ( result == NULL )
    {
        result = _result;
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = std::max( result[ i ],  0.  );
        }
    }
    else
    if ( _result == NULL )
    {
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = std::max( result[ i ], 0.  );
        }
    }
    else
    {
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = std::max( result[ i ],  _result[ i ] );
        }
        delete[] _result;
    }
    return result;
}


double
MaxEvaluation::eval(   const list_of_cnodes&       lc,
                       const list_of_sysresources& ls  ) const
{
    return std::max( arguments[ 0 ]->eval( lc, ls ),
                     arguments[ 1 ]->eval( lc, ls )
                     );
}

double*
MaxEvaluation::eval_row(   const list_of_cnodes&       lc,
                           const list_of_sysresources& ls  ) const
{
    double* result  = arguments[ 0 ]->eval_row( lc, ls );
    double* _result = arguments[ 1 ]->eval_row( lc, ls );
    if ( result == NULL && _result == NULL )
    {
        return NULL;
    }
    if ( result == NULL )
    {
        result = _result;
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = std::max( result[ i ],  0.  );
        }
    }
    else
    if ( _result == NULL )
    {
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = std::max( result[ i ], 0.  );
        }
    }
    else
    {
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = std::max( result[ i ],  _result[ i ] );
        }
        delete[] _result;
    }
    return result;
}
