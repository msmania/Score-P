##*************************************************************************##
##  Copyright (c) 2016-2021                                                ##
##  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ##
##                                                                         ##
##  This software may be modified and distributed under the terms of       ##
##  a BSD-style license.  See the COPYING file in the package base         ##
##  directory for details.                                                 ##
##*************************************************************************##


# AX_GMOCK
# --------
# Configures the GoogleTest Mocking Framework.  Requires that the Google C++
# Testing Framework is configured first, using AX_GTEST.
#
# List of provided automake substitutions:
#  `GMOCK_CPPFLAGS`::  Preprocessor flags to be used when compiling tests
#  `GMOCK_CXXFLAGS`::  C++ compiler flags to be used when compiling tests
#  `GMOCK_LIBS`::      Libraries/linker flags to be used when linking tests
#
AC_DEFUN([AX_GMOCK], [
    AS_VAR_SET([gmock_cppflags], ["-I$srcdir/$ax_gtest_path/googlemock/include"])

    AC_SUBST([GMOCK_CPPFLAGS], ["$gmock_cppflags"])
    AC_SUBST([GMOCK_CXXFLAGS], [])dnl For consistency only
    AC_SUBST([GMOCK_LIBS],     [])dnl For consistency only
])
