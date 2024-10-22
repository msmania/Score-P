##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 1998-2021                                                ##
##  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ##
##                                                                         ##
##  Copyright (c) 2009-2015                                                ##
##  German Research School for Simulation Sciences GmbH,                   ##
##  Laboratory for Parallel Programming                                    ##
##                                                                         ##
##  This software may be modified and distributed under the terms of       ##
##  a BSD-style license.  See the COPYING file in the package base         ##
##  directory for details.                                                 ##
##*************************************************************************##



# SYNOPSIS
#
# AC_CUBE_RESET_LIB_CACHE(headers ...)
#
# DESCRIPTION
#
# This macro invalidates the headers cache variables created by previous AC_CHECK_HEADER/AC_CHECK_HEADERS checks.
#
AC_DEFUN([AC_CUBE_RESET_LIB_CACHE], [
    AS_FOR([AX_var], [ax_var], [$1], [
        dnl You can replace "ac_cv_lib_" with any prefix from http://www.gnu.org/software/autoconf/manual/html_node/Cache-Variable-Index.html
        AS_VAR_PUSHDEF([ax_Var], [ac_cv_lib_${ax_var}_$2])
        AS_UNSET([ax_Var])
        AS_VAR_POPDEF([ax_Var])
    ])
]) # AX_RESET_LIB_CACHE

AC_DEFUN([AC_CUBE_RESET_HEADERS_CACHE], [
    AS_FOR([AX_var], [ax_var], [$1], [
        dnl You can replace "ac_cv_lib_" with any prefix from http://www.gnu.org/software/autoconf/manual/html_node/Cache-Variable-Index.html
        AS_VAR_PUSHDEF([ax_Var], [ac_cv_header_${ax_var}])
        AS_UNSET([ax_Var])
        AS_VAR_POPDEF([ax_Var])
    ])
]) # AX_RESET_LIB_CACHE


AC_DEFUN([AC_CUBE_LIBZ_DETECTION],
[
    dnl If after run of this macro is still empty - lib wasn't found
    LIB_RETURN="__NOT_FOUND__"
    AS_IF([ test "x$1" == "x" ],[
    AC_MSG_NOTICE([Try pkg-config zlib for library...])
        PKG_CONFIG_AVAILABLE=`which pkg-config`
        #here we try tu use pkg-config
        AS_IF([ test "x$PKG_CONFIG_AVAILABLE" != "x" ],[
            ZLIBCHECK=`pkg-config --libs-only-L zlib 2>&1| grep "No package "`
            AS_IF([ test "x$ZLIBCHECK" = "x" ],[
                LIB_RETURN=$ZLIBCHECK
                AC_MSG_NOTICE([Found zlib. Library linked  via ${LIB_RETURN} -lz])
                ])
        ])
    ], [
    AS_IF([ test -e $1 ],[
      AS_IF([ test -f $1 ],[
         ZLIB_PATH=`dirname $1`
         ZLIB_PATH=`dirname $ZLIB_PATH`
        ],[
        ZLIB_PATH=$1
        ])

        PATH_CANDIDATES=`find $ZLIB_PATH/ -type d `


      for zlib_path in $PATH_CANDIDATES; do

          dnl Save the current state
          ax_probe_library_save_LDFLAGS=${LDFLAGS}

          LDFLAGS="-L$zlib_path"
          dnl $LDFLAGS
          AC_MSG_CHECKING([zlib in $zlib_path])
          AS_ECHO()
          _AS_ECHO_LOG([LDFLAGS="${LDFLAGS}"])

          AC_CHECK_LIB(z, zlibVersion, [ZLIB_FOUND="yes"], [ZLIB_FOUND="no"])

          dnl Restore the state to original in case of unsuccessful attempt
          LDFLAGS=${ax_probe_library_save_LDFLAGS}
          AC_CUBE_RESET_LIB_CACHE([z], [zlibVersion])

          dnl We have found the location, leave the loop:
          AS_IF([ test "x$ZLIB_FOUND" == "xyes" ],[
                  AC_MSG_NOTICE([FOUND zlib at $1])
                  LIB_RETURN="-L$zlib_path"
                  break;
          ])
      done
    ],[
      AC_MSG_ERROR(["Error: $1 doesn't exist"])
    ])
    ])
])


AC_DEFUN([AC_CUBE_LIBZ_HEADERS_DETECTION],
[
    dnl If after run of this macro is still empty - lib wasn't found
    HEADER_RETURN="__NOT_FOUND__"

    AS_IF([ test "x$1" == "x" ],[
        AC_MSG_NOTICE([Try pkg-config zlib for headers...])
        PKG_CONFIG_AVAILABLE=`which pkg-config`
        #here we try tu use pkg-config
        AS_IF([ test "x$PKG_CONFIG_AVAILABLE" != "x" ],[
            ZLIBCHECK=`pkg-config --cflags zlib 2>&1| grep "No package "`
            AS_IF([ test "x$ZLIBCHECK" = "x" ],[
                HEADER_RETURN=$ZLIBCHECK
                AC_MSG_NOTICE([Found zlib. Headers are included via $HEADER_RETURN])
                ])
            ])
    ], [
    AS_IF([ test -e $1 ],[
     AS_IF([ test -f $1 ],[
       ZLIB_PATH=`dirname $1`
       ZLIB_PATH=`dirname $ZLIB_PATH`
      ],[
        ZLIB_PATH=$1
       ])

      PATH_CANDIDATES=`find $ZLIB_PATH/ -type d `

      for zlib_path in $PATH_CANDIDATES; do

          dnl Save the current state
          ax_probe_header_save_CXXFLAGS=${CXXFLAGS}
          ax_probe_header_save_CFLAGS=${CFLAGS}

          CXXFLAGS="-I$zlib_path"
          CFLAGS="-I$zlib_path"
          dnl $LDFLAGS
          AC_MSG_CHECKING([zlib.h in $zlib_path])
          AS_ECHO()
          _AS_ECHO_LOG([CXXFLAGS="${CXXFLAGS}"])
          _AS_ECHO_LOG([CFLAGS="${CFLAGS}"])

          AC_CHECK_HEADER(zlib.h, [ZLIB_HEADER_FOUND="yes"], [ZLIB_HEADER_FOUND="no"])

          dnl Restore the state to original in case of unsuccessful attempt
          CXXFLAGS=${ax_probe_header_save_CXXFLAGS}
          CFLAGS=${ax_probe_header_save_CFLAGS}
          AC_CUBE_RESET_HEADERS_CACHE([zlib.h])

          dnl We have found the location, leave the loop:
          AS_IF([ test "x$ZLIB_HEADER_FOUND" == "xyes" ],[
                  AC_MSG_NOTICE([FOUND zlib.h at $1])
                  HEADER_RETURN="-I$zlib_path"
                  break;
          ])
      done
    ],[
    # here is not $1 given or test is failed
    AC_MSG_ERROR(["Error: $1 doesn't exist"])
    ])
    ])
])



AC_DEFUN([AC_CUBE_LIBZ_FRONTEND_SEARCH], [
    dnl if variable is empty, we do not change FRONTEND_LIBZ_LD
    AC_CUBE_RESET_LIB_CACHE([z], [zlibVersion])
    AC_CUBE_RESET_HEADERS_CACHE([zlib.h])
    AC_CUBE_LIBZ_DETECTION([$FRONTEND_PATH])
    AC_CUBE_LIBZ_HEADERS_DETECTION([$FRONTEND_PATH])
    AS_IF([ test "x$HEADER_RETURN"  != "x__NOT_FOUND__" && test "x$LIB_RETURN"  != "x__NOT_FOUND__" ],[
            FRONTEND_LIBZ_LDFLAGS="$LIB_RETURN "
            FRONTEND_LIBZ_LIBS="-lz"
            FRONTEND_LIBZ_HEADERS="$HEADER_RETURN"

            AS_IF([ test "x$FRONTEND_COMPRESSION_ON" = "xfull"],[
              COMPRESSION="$COMPRESSION -DFRONTEND_CUBE_COMPRESSED=yes "
              MSG_FRONTEND_COMPRESSION=full
            ])
            AS_IF([test "x$FRONTEND_COMPRESSION_ON" = "xro"],[
              COMPRESSION="$COMPRESSION -DFRONTEND_CUBE_COMPRESSED_READONLY=yes "
              MSG_FRONTEND_COMPRESSION=readonly
            ])
             AC_DEFINE(COMPRESSION, 1, [Compression is enabled])
        ],[
            AC_MSG_WARN([ Cannot find zlib under $FRONTEND_PATH. CUBE uses zlib compression and this library is needed, if you create a frontend application.])
            FRONTEND_LIBZ_LDFLAGS=""
            FRONTEND_LIBZ_LIBS=""
            FRONTEND_LIBZ_HEADERS=""
            MSG_FRONTEND_COMPRESSION=no
            COMPRESSION="$COMPRESSION"
        ])
    AC_CUBE_RESET_LIB_CACHE([z], [zlibVersion])
    AC_CUBE_RESET_HEADERS_CACHE([zlib.h])



])



AC_DEFUN([AC_CUBE_LIBZ_FRONTEND_SELECTION], [
AC_ARG_WITH(frontend-zlib, [AS_HELP_STRING([--with-frontend-zlib="path to frontrend zlib"], [Defines the zlib library, used by cube c++ library])],[FRONTEND_PATH=$withval ; FRONTEND_LIBZ_LDFLAGS="-L$withval/lib"; FRONTEND_LIBZ_LIBS="-lz" ; FRONTEND_LIBZ_HEADERS="-I$withval/include"],[FRONTEND_PATH= ; FRONTEND_LIBZ_LDFLAGS=""; FRONTEND_LIBZ_LIBS="-lz" ; FRONTEND_LIBZ_HEADERS=""])

AC_ARG_WITH(compression, [AS_HELP_STRING([--with-compression=full|ro|none], [Setup the level of compression support:  "full" - all parts (tools, GUI and c-writer)  create compressed cubes; "ro" - tools and GUI can still read compressed cube files, but write uncompressed version. "none" - neither read not write of compressed cube files is possible. ])],[FRONTEND_COMPRESSION_ON=$withval],[
FRONTEND_COMPRESSION_ON="ro"
])

dnl "looks for libz.a or libz.so in pathes, wich are under the $BACKEND_PATH or $FRONTEND_PATH"
AS_IF([ test "x$FRONTEND_COMPRESSION_ON" = "xfull" || test "x$FRONTEND_COMPRESSION_ON" = "xro" ],
[
AC_CUBE_LIBZ_FRONTEND_SEARCH
],
[
COMPRESSION=""
FRONTEND_LIBZ_HEADERS=""
FRONTEND_LIBZ_LDFLAGS=""
FRONTEND_LIBZ_LIBS=""
MSG_FRONTEND_COMPRESSION="no"
])




AC_MSG_NOTICE([ Compression support in tools and GUI : $MSG_FRONTEND_COMPRESSION])
AS_IF([ test "x$MSG_FRONTEND_COMPRESSION" != "xno" ],[
AC_MSG_NOTICE([ Frontend zlib get linked  as: $FRONTEND_LIBZ_LDFLAGS $FRONTEND_LIBZ_LIBS])
AC_MSG_NOTICE([ Frontend zlib headers included as: $FRONTEND_LIBZ_HEADERS])
])
AC_SUBST([FRONTEND_LIBZ_LDFLAGS])
AC_SUBST([FRONTEND_LIBZ_LIBS])
AC_SUBST([FRONTEND_LIBZ_HEADERS])
AC_SUBST([COMPRESSION])
AC_SUBST([MSG_FRONTEND_COMPRESSION])

])
