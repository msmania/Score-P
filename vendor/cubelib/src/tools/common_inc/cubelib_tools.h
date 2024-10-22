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


/** @internal
 *
 *  @file
 *
 *  @brief      Helper class for CUBEW tools.
 */

#ifndef CUBELIB_TOOLS_H
#define CUBELIB_TOOLS_H

#ifndef CUBELIB_TOOL_NAME
#error No CUBELIB_TOOL_NAME given
#endif

/* ___ Output handling. _____________________________________________________ */

#define out( msg ) \
    do { \
        std::cout << CUBELIB_TOOL_NAME << ": " <<  ( msg ) << std::endl; \
    } while ( 0 )

#define err( msg ) \
    do { \
        std::cerr << CUBELIB_TOOL_NAME << ": " << ( msg ) << std::endl; \
    } while ( 0 )

#define warn( msg ) \
    do { \
        std::cerr << CUBELIB_TOOL_NAME << ": warning: " << ( msg ) << std::endl; \
    } while ( 0 )

#define die( msg ) \
    do { \
        err( msg ); \
        std::cerr << "Try '" << CUBELIB_TOOL_NAME << " --help' for more information." << std::endl; \
        exit( EXIT_FAILURE ); \
    } while ( 0 )

#endif // CUBELIB_TOOLS_HPP
