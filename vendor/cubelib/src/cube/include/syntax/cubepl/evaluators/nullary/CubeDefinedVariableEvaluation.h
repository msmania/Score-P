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


#ifndef CUBELIB_DEFINED_VARIABLE_EVALUATION_H
#define CUBELIB_DEFINED_VARIABLE_EVALUATION_H 0

#include "CubeStringEvaluation.h"
#include "CubePLMemoryManager.h"
#include "Cube.h"
namespace cube
{
class DefinedVariableEvaluation : public StringEvaluation
{
protected:
    CubePLMemoryManager* memory;
    Cube*                cube; // to be able to test for the existing metric
    std::string          variable_name;
public:
    DefinedVariableEvaluation( std::string          _variable,
                               CubePLMemoryManager* _manager,
                               Cube*                _cube
                               ) :  memory( _manager ), cube( _cube ), variable_name( _variable )
    {
    };

    virtual
    ~DefinedVariableEvaluation();

    virtual
    double
    eval() const
    {
        if (
            memory->defined( variable_name )  ||
            cube->get_met( variable_name ) != nullptr
            )
        {
            return 1.;
        }
        return 0.;
    }


    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour,
          const Sysres*,
          const CalculationFlavour   ) const
    {
        return eval();
    };

    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour ) const
    {
        return eval();
    };


    virtual
    std::string
    strEval() const
    {
        if (
            memory->defined( variable_name )  ||
            cube->get_met( variable_name ) != nullptr
            )
        {
            return "1";
        }
        return "0";
    }




    virtual
    double*
    eval_row( const Cnode*,
              const CalculationFlavour ) const
    {
        return NULL;
    }


    inline
    virtual
    double
    eval( const list_of_cnodes&,
          const list_of_sysresources& ) const
    {
        return eval();
    };

    virtual
    double*
    eval_row( const list_of_cnodes&,
              const list_of_sysresources& ) const
    {
        return NULL;
    };





    virtual
    void
    print() const
    {
        std::cout << "defined(" << variable_name << ")";
    };

    virtual
    double
    eval( double,
          double ) const
    {
        return eval();
    };
};
};

#endif
