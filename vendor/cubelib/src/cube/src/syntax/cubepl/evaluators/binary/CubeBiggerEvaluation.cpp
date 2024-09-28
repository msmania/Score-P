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
#include "CubeBiggerEvaluation.h"
using namespace cube;
using namespace std;

BiggerEvaluation::BiggerEvaluation()
{
};

BiggerEvaluation::BiggerEvaluation( GeneralEvaluation* _arg1,
                                    GeneralEvaluation* _arg2 ) : BinaryEvaluation( _arg1, _arg2 )
{
};


BiggerEvaluation::~BiggerEvaluation()
{
}
