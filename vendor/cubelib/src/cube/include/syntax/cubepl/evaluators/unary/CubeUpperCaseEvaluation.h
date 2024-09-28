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


#ifndef CUBELIB_UPPER_CASE_EVALUATION_H
#define CUBELIB_UPPER_CASE_EVALUATION_H 0

#include "CubeStringEvaluation.h"

namespace cube
{
class UpperCaseEvaluation : public StringEvaluation
{
public:
    UpperCaseEvaluation();
    UpperCaseEvaluation( GeneralEvaluation* );

    virtual
    ~UpperCaseEvaluation();

    virtual
    std::string
    strEval() const;


    virtual
    void
    print() const
    {
        std::cout << " uppercase(";
        arguments[ 0 ]->print();
        std::cout << ")";
    };
};
};
#endif
