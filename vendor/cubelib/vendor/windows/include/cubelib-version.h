/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



#ifndef CUBELIB_VERSION_H
#define CUBELIB_VERSION_H


/*-------------------------------------------------------------------------*/
/**
 *  @file  cubelib-version.h
 *  @brief Provides the Cube package version information.
 **/
/*-------------------------------------------------------------------------*/


/// @name Cube version information
/// @{

/// Cube revision number
#define CUBELIB_REVISION "<REVISION SHA>"

/// Cube revision number
#define CUBELIB_REVISION_NUMBER <REVISION SHA>

/// Cube revision number
#define CUBELIB_REVISION_STRING CUBELIB_REVISION


/// Cube major version number
#define CUBELIB_MAJOR_NUM   <PACKAGE MAJOR>

/// Cube minor version number
#define CUBELIB_MINOR_NUM   <PACKAGE MINOR>

/// Cube bugfix version number
#define CUBELIB_BUGFIX_NUM  <PACKAGE BUGFIX>

/// Cube major version number
#define CUBELIB_MAJOR   "<PACKAGE MAJOR>"

/// Cube minor version number
#define CUBELIB_MINOR   "<PACKAGE MINOR>"

/// Cube bugfix version number
#define CUBELIB_BUGFIX   "<PACKAGE BUGFIX>"

/// Cube suffix
#define CUBELIB_SUFFIX   "<PACKAGE SUFFIX>"

/// Cube suffix_internally
#define CUBELIB_SUFFIX_INTERNAL

/// Cube version number (<i>major</i>.<i>minor</i>)
#define CUBELIB_SHORT_VERSION   CUBELIB_MAJOR "." CUBELIB_MINOR

/// Cube full version number (<i>major</i>.<i>minor</i>.<i>bugfix</i>)
#define CUBELIB_FULL_VERSION   CUBELIB_SHORT_VERSION "." CUBELIB_BUGFIX

/// Cube version number
#define CUBELIB_VERSION "<PACKAGE MAJOR>.<PACKAGE MINOR>"

/// Cube package name "cube"
#define CUBELIB_SHORT_NAME  "CubeLib"

/// Cube package name "cube-4.x.1-XX"
#define CUBELIB_FULL_NAME   CUBELIB_SHORT_NAME "-" CUBELIB_FULL_VERSION CUBELIB_SUFFIX

/// usage: #if (CUBELIB_VERSION_NUMBER >= CUBELIB_VERSION_CHECK(4, 5, 0))'
/// Macro to build a single number out of major.minor.bugfix
#define CUBELIB_VERSION_CHECK( major, minor, bugfix ) ( ( major << 16 ) | ( minor << 8 ) | ( bugfix ) )

/// usage: #if (CUBELIB_VERSION_NUMBER >= CUBELIB_VERSION_CHECK(4, 5, 0))'
/// Cube package version as a single number
#define CUBELIB_VERSION_NUMBER CUBELIB_VERSION_CHECK( CUBELIB_MAJOR_NUM, CUBELIB_MINOR_NUM, CUBELIB_BUGFIX_NUM )

/// Cube library interface information
#define LIBRARY_CURRENT "10"
#define LIBRARY_REVISION "0"
#define LIBRARY_AGE "3"

/// @}


#endif   // !CUBELIB_VERSION_H
