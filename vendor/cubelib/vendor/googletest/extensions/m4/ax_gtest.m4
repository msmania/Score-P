##*************************************************************************##
##  Copyright (c) 2013-2021                                                ##
##  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ##
##                                                                         ##
##  This software may be modified and distributed under the terms of       ##
##  a BSD-style license.  See the COPYING file in the package base         ##
##  directory for details.                                                 ##
##*************************************************************************##


# AX_GTEST(TOPDIR)
# ----------------
# Configures the Google C++ Testing Framework.  Requires the path to the
# top-level GoogleTest source directory (including both GoogleTest and
# GoogleMock) relative to the location of the calling configure.ac.
#
# List of provided automake substitutions:
#   `GTEST_PATH`::      Top-level GoogleTest source directory
#   `GTEST_CPPFLAGS`::  Preprocessor flags to be used when compiling tests
#   `GTEST_CXXFLAGS`::  C++ compiler flags to be used when compiling tests
#   `GTEST_LIBS`::      Libraries/linker flags to be used when linking tests
#
# List of configure variables set:
#   `ax_gtest_path`::  Top-level GoogleTest source directory
#
AC_DEFUN([AX_GTEST], [
    m4_ifblank([$1],
        [m4_fatal([Path to GoogleTest directory relative to configure.ac required])])
    AC_REQUIRE([AX_PTHREAD])
    AC_BEFORE([$0], [AX_GMOCK])

    ax_gtest_path=$1

    AS_VAR_SET([gtest_cppflags], ["-I$srcdir/$ax_gtest_path/googletest/include"])
    AS_IF([test "x$ax_pthread_ok" = xyes],
        [AS_VAR_APPEND([gtest_cppflags], [" -DGTEST_HAS_PTHREAD=1"])],
        [AS_VAR_APPEND([gtest_cppflags], [" -DGTEST_HAS_PTHREAD=0"])])

    AC_SUBST([GTEST_PATH],     ["$ax_gtest_path"])
    AC_SUBST([GTEST_CPPFLAGS], ["$gtest_cppflags"])
    AC_SUBST([GTEST_CXXFLAGS], ["$PTHREAD_CFLAGS"])
    AC_SUBST([GTEST_LIBS],     ["$PTHREAD_LIBS"])
])
