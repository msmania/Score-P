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


#ifndef CUBELIB_AND_EVALUATION_H
#define CUBELIB_AND_EVALUATION_H 0

#include <vector>
#include "CubeBinaryEvaluation.h"

namespace cube
{
class AndEvaluation : public BinaryEvaluation
{
public:
    AndEvaluation();
    AndEvaluation( GeneralEvaluation*,
                   GeneralEvaluation* );
    virtual
    ~AndEvaluation()
    {
    };

    inline
    virtual
    double
    eval() const
    {
        double result = arguments[ 0 ]->eval();
        if ( result == 0. )
        {
            return 0.;
        }
        double _result = arguments[ 1 ]->eval();
        if ( _result == 0. )
        {
            return 0.;
        }
        return 1.;
    }
    ;

    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf,
          const Sysres*            _sf,
          const CalculationFlavour _tf  ) const
    {
        double result = arguments[ 0 ]->eval( _cnode, _cf,
                                              _sf, _tf );
        if ( result == 0. )
        {
            return 0.;
        }
        double _result = arguments[ 1 ]->eval( _cnode, _cf,
                                               _sf, _tf );
        if ( _result == 0. )
        {
            return 0.;
        }
        return 1.;
    }

    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf ) const
    {
        double result = arguments[ 0 ]->eval( _cnode, _cf );
        if ( result == 0. )
        {
            return 0.;
        }
        double _result = arguments[ 1 ]->eval( _cnode, _cf );
        if ( _result == 0. )
        {
            return 0.;
        }
        return 1.;
    }

    inline
    virtual
    double*
    eval_row( const Cnode*             _cnode,
              const CalculationFlavour _cf ) const
    {
        double* result  = arguments[ 0 ]->eval_row( _cnode, _cf );
        double* _result = arguments[ 1 ]->eval_row( _cnode, _cf );
        if ( result == NULL || _result == NULL )
        {
            return NULL;
        }
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = ( result[ i ] != 0. &&  _result[ i ] != 0. ) ? 1. : 0.;
        }
        delete[] _result;
        return result;
    }

    inline
    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        double result = arguments[ 0 ]->eval( lc, ls );
        if ( result == 0. )
        {
            return 0.;
        }
        double _result = arguments[ 1 ]->eval( lc, ls );
        if ( _result == 0. )
        {
            return 0.;
        }
        return 1.;
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        double* result  = arguments[ 0 ]->eval_row( lc, ls );
        double* _result = arguments[ 1 ]->eval_row( lc, ls );
        if ( result == NULL || _result == NULL )
        {
            return NULL;
        }
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = ( result[ i ] != 0. &&  _result[ i ] != 0. ) ? 1. : 0.;
        }
        delete[] _result;
        return result;
    };


    virtual
    void
    print() const
    {
        arguments[ 0 ]->print();
        std::cout << " and ";
        arguments[ 1 ]->print();
    };

    inline
    virtual
    double
    eval( double arg1,
          double arg2 ) const
    {
        double result = arguments[ 0 ]->eval( arg1, arg2 );
        if ( result == 0. )
        {
            return 0.;
        }
        double _result = arguments[ 1 ]->eval( arg1, arg2 );
        if ( _result == 0. )
        {
            return 0.;
        }
        return 1.;
    }
};
};

#endif
