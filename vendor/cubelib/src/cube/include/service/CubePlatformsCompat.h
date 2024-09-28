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


/**
 * \file>CubePlatformsCompat.h...
 * \brief Header with definitions and on other than linux platforms missing calls or with different declaration.
 *
 *
 *
 */

#include <unistd.h>
#include <sys/types.h>

#ifndef CUBELIB_PLATFORMS_COMPAT_H
#define CUBELIB_PLATFORMS_COMPAT_H

#ifdef __MINGW32__ // for windows we compile only on MinGW32. Here are some calls different or missing
#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <string.h>

// on windows there is no "mode" for directory creation
#define CUBELIB_MKDIR( path, mode ) ::mkdir( path )
// #define S_IRWXU 0
//#define S_IROTH 0
//#define S_IXOTH 0
//#define S_IRGRP 0
//#define S_IXGRP 0
//#define EOVERFLOW -1


// redefine fopen and stat to be able to open files on windows
#define  CUBELIB_STRUCT_STAT  struct _stat

#define  CUBELIB_STAT( result, path, pointer ) result = ::_stat( path, pointer );

// keep this version of macro for future atempt to resolve unicode problem
#define  CUBELIB_WSTAT( result, path, pointer )  std::wcout << "trying  " << path << std::flush <<  std::endl; \
    wchar_t* wcpath = ( wchar_t* )calloc( strlen( path ), sizeof( wchar_t ) ); \
    size_t   _size  = mbstowcs( wcpath, path, strlen( path ) ); \
    std::wcout << "Convereted1 succe " << _size << " " << strlen( path ) << " " << wcpath << std::flush << std::endl; \
    result = ::_wstat( wcpath, pointer ); \
    std::wcout << "Opened stat " << ( int64_t )result << std::flush << std::endl; \
    free( wcpath );


#define  CUBELIB_FOPEN( result, path, mode )  result = ::fopen( path, mode );

// keep this version of macro for future atempt to resolve unicode problem
#define  CUBELIB_WFOPEN( result, path, mode )   { \
        std::wcout << "trying  " << path << std::endl; \
        wchar_t* wcpath = ( wchar_t* )calloc( strlen( path ), sizeof( wchar_t ) ); \
        size_t   _size  = mbstowcs( wcpath, path, strlen( path ) ); \
        std::wcout << "Convereted2 succe " << _size << " " << strlen( path ) << " " << wcpath << std::endl; \
        wchar_t* wcmode = ( wchar_t* )calloc( strlen( mode ), sizeof( wchar_t ) ); \
        _size = mbstowcs( wcmode, mode, strlen( path ) ); \
        std::wcout << "Convereted22 succe " << _size << " " << strlen( mode ) << " " << wcmode << std::endl; \
        result = ::_wfopen( wcpath, wcmode ); \
        std::wcout << "Opened wfopen" << ( uint64_t )result << std::endl; \
        free( wcpath ); \
        free( wcmode ); \
}






// redefine fseeko with standart fseek
// #warning "On MinGW Platform we redefine fseeko using standard fseek."
//#define fseeko fseek


typedef unsigned int gid_t;
typedef unsigned int uid_t;
extern "C" {     // another way
//##define PATH_MAX MAX_PATH
char*
realpath( const char*,
          char* );

const char CUBE_PATH_SEPARATOR = ';';
/*
   int
   gethostname( char*  name,
             size_t len );*/
};

#define FNM_NOMATCH 1

#define fnmatch( s1, s2, mode ) strcmp( s1, s2 )

#endif


#ifndef __MINGW32__

// on windows there is no "mode" for directory creation
#define CUBELIB_MKDIR( path, mode ) ::mkdir( path, mode )
//  fopen and stat to be able to open files on windows
#define  CUBELIB_STRUCT_STAT  struct stat
#define  CUBELIB_STAT( result, path, pointer ) result = ::stat( path, pointer );
#define  CUBELIB_FOPEN( result, path, mode )  result = ::fopen( path, mode );

const char CUBE_PATH_SEPARATOR = ':';

#endif


gid_t
cube_getgid();

uid_t
cube_getuid();

#endif
