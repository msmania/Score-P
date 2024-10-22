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
/**
 * \file cubew_compat_platform.c
 * \brief Source code of the  definitions for missiong calls on some platform different than linux.
 *
 *
 *
 */
#include "cubew_compat_platform.h"

#ifdef __MINGW32__ // for windows we compile only on MinGW32. Here are some calls different or missing



#warning "On MinGW32 Platform we redefine fseeko using standard fseek".

#endif

// "We create cube reports using faked user and group id = 131071 (6th Marsenne prime number)"
gid_t
cube_getgid( void )
{
    return 131071; // faked gid on MinGW32
}

uid_t
cube_getuid( void )
{
    return 131071; // faked uid on MinGW32
}
