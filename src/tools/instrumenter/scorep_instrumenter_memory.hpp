/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2016-2017, 2022,
 * Technische Universitaet Dresden, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */

#ifndef SCOREP_INSTRUMENTER_MEMORY_HPP
#define SCOREP_INSTRUMENTER_MEMORY_HPP

/**
 * @file
 *
 * Defines the class for memory tracking.
 */

#include "scorep_instrumenter_adapter.hpp"

#include <set>

/* **************************************************************************************
 * class SCOREP_Instrumenter_MemoryAdapter
 * *************************************************************************************/

/**
 * This class represents the Memory support.
 */
class SCOREP_Instrumenter_MemoryAdapter : public SCOREP_Instrumenter_Adapter
{
public:
    SCOREP_Instrumenter_MemoryAdapter( void );

    void
    printHelp( void ) override;

    std::string
    getConfigToolFlag( SCOREP_Instrumenter_CmdLine& cmdLine,
                       const std::string&           inputFile ) override;

    void
    checkObjects( SCOREP_Instrumenter& instrumenter ) override;

    bool
    isInterpositionLibrary( const std::string& libraryName ) override;

private:
    std::set<std::string> m_categories;
};

#endif // SCOREP_INSTRUMENTER_MEMORY_HPP
