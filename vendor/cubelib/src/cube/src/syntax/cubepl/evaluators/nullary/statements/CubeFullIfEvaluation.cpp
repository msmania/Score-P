/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
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

#include "CubeFullIfEvaluation.h"

using namespace cube;


FullIfEvaluation::~FullIfEvaluation()
{
    delete condition;
}

double
FullIfEvaluation::eval() const
{
    if ( condition->eval() != 0. )
    {
        for ( unsigned i = 0; i < n_true; ++i )
        {
            arguments[ i ]->eval();
        }
    }
    else
    {
        for ( unsigned i = n_true; i < n_true + n_false; ++i )
        {
            arguments[ i ]->eval();
        }
    }
    return 0.;
}
