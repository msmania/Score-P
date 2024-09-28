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

#include "CubeUpperCaseEvaluation.h"
#include "CubeServices.h"
using namespace cube;
using namespace std;



UpperCaseEvaluation::UpperCaseEvaluation()
{
};

UpperCaseEvaluation::UpperCaseEvaluation( GeneralEvaluation* _val )
{
    arguments.push_back( _val );
};

UpperCaseEvaluation::~UpperCaseEvaluation()
{
};

string
UpperCaseEvaluation::strEval() const
{
    StringEvaluation* _val = dynamic_cast<StringEvaluation*>( arguments[ 0 ] );

    return services::uppercase( _val->strEval() );
}
