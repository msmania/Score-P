##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 2020-2021                                                ##
##  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ##
##                                                                         ##
##  This software may be modified and distributed under the terms of       ##
##  a BSD-style license.  See the COPYING file in the package base         ##
##  directory for details.                                                 ##
##*************************************************************************##


# CUBE_CXX_REGEX
# --------------
# Checks whether the C++11 compiler's regular expression support is able to
# handle regular expressions that are known to trigger bugs in certain STL
# libraries.  In non-cross-compile mode, the macro will error out if such
# a buggy STL is detected.
#
AC_DEFUN([CUBE_CXX_REGEX], [
    AC_LANG_PUSH([C++])
    AC_CACHE_CHECK([whether $CXX regular expression support works],
        [ac_cv_cube_cxx_regex],
        [AC_RUN_IFELSE(
            [AC_LANG_PROGRAM(
                [_CUBE_CXX_REGEX_testheader],
                [_CUBE_CXX_REGEX_testbody])],
            [ac_cv_cube_cxx_regex=yes],
            [ac_cv_cube_cxx_regex=no],
            [ac_cv_cube_cxx_regex=maybe])])
    AS_CASE([$ac_cv_cube_cxx_regex],
        [maybe],
            [AC_MSG_WARN([Cross-compiling: Unable to check whether $CXX regex support works.])],
        [no],
            [AC_MSG_ERROR([$CXX regular expression support is buggy.])])
    AC_LANG_POP([C++])
])


dnl Test for checking C++11 regular expression support

m4_define([_CUBE_CXX_REGEX_testheader], [[
    #include <cstdlib>
    #include <iostream>
    #include <regex>
    #include <string>
]])

m4_define([_CUBE_CXX_REGEX_testbody], [[
    std::string reg("^!\\\\\$omp ordered\\\\s@");
    std::string reg2("\\\\.cubex|\\\\.cube|\\\\.cube\\\\.gz");
    try
    {
        std::regex self_regex( reg );
    }
    catch ( const std::regex_error& e )
    {
        std::cout << "Cannot create regex " << reg << ": " << e.what();
        std::exit(-1);
    }
    try
    {
        std::regex self_regex( reg2 );
    }
    catch ( const std::regex_error& e )
    {
        std::cout << "Cannot create regex " << reg2 << ": " << e.what();
        std::exit(-1);
    }
]])
