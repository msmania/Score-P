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


#ifndef CUBELIB_REGEX_EVALUATION_H
#define CUBELIB_REGEX_EVALUATION_H 0

#include <sys/types.h>
#include <regex>
#include <string>
#include "CubeBinaryEvaluation.h"

using namespace std;
namespace cube
{
class RegexEvaluation : public BinaryEvaluation
{
public:
    RegexEvaluation();
    RegexEvaluation( GeneralEvaluation*,
                     StringEvaluation* );
    virtual
    ~RegexEvaluation();

    inline
    virtual
    double
    eval() const
    {
        double            _return = 0.;
        StringEvaluation* _reg    = dynamic_cast<StringEvaluation*>( arguments[ 1 ] );
        StringEvaluation* _val    = dynamic_cast<StringEvaluation*>( arguments[ 0 ] );

        if ( _reg == NULL )
        {
            return 0.;
        }
        if ( _val == NULL )
        {
            return 0.;
        }

        string reg = ( _reg )->strEval();
        string val = ( _val )->strEval();
        try
        {
            std::regex self_regex( reg );
            _return = std::regex_search( val, self_regex ) ? 1. : 0.;
        }
        catch ( const std::regex_error& e )
        {
            std::cerr << "Cannot compile Regular expression (" << reg << "). Error is " << e.what() << '\n';
            _return = 0.;
        }
        return _return;
    }

    inline
    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour,
          const Sysres*,
          const CalculationFlavour ) const
    {
        return eval();
    }

    inline
    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour ) const
    {
        return eval();
    }


    inline
    virtual
    double
    eval( const list_of_cnodes&, const list_of_sysresources& ) const
    {
        return eval();
    };





    inline
    virtual
    void
    print() const
    {
        arguments[ 0 ]->print();
        std::cout << " =~ /";
        arguments[ 1 ]->print();
        std::cout << "/";
    };

    virtual
    double
    eval( double,
          double ) const
    {
        return eval();
    }
};
};

#endif
