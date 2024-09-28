##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 1998-2023                                                ##
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


## Set up Autoconf
AC_PREREQ([2.69])
AC_INIT([CubeLib], m4_esyscmd([../build-config/common/generate-package-version.sh ../build-config/VERSION]), [scalasca@fz-juelich.de],[cubelib],[http://www.scalasca.org])
AC_CONFIG_AUX_DIR([../build-config])
## See also ACLOCAL_AMFLAGS in Makefile.am
AC_CONFIG_MACRO_DIRS([../build-config/m4 ../build-config/common/m4 ../vendor/googletest/extensions/m4])

## Set up AFS
AFS_PACKAGE_BUILD_INIT([frontend])
AFS_SUMMARY_INIT

## Define frontend-specific environment variables
AC_ARG_VAR(CC_FOR_BUILD, [C compiler command for the frontend build])
AC_ARG_VAR(CXX_FOR_BUILD, [C++ compiler command for the frontend build])
AC_ARG_VAR(CPPFLAGS_FOR_BUILD, [(Objective) C/C++ preprocessor flags for the frontend build, e.g. -I<include dir> if you have headers in a nonstandard directory <include dir>])
AC_ARG_VAR(CFLAGS_FOR_BUILD, [C compiler flags for the frontend build])
AC_ARG_VAR(CXXFLAGS_FOR_BUILD, [C++ compiler flags for the frontend build])
AC_ARG_VAR(LDFLAGS_FOR_BUILD, [linker flags for the frontend build, e.g. -L<lib dir> if you have libraries in a nonstandard directory <lib dir>])
AC_ARG_VAR(LIBS_FOR_BUILD, [libraries to pass to the linker for the frontend build, e.g. -l<library>])

## Convert compilers & flags
AS_IF([ test "x${ac_scorep_cross_compiling}" = "xyes" ],[
AC_SCOREP_CONVERT_FOR_BUILD_COMPILER([CC])
AC_SCOREP_CONVERT_FOR_BUILD_COMPILER([CXX])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([CPPFLAGS])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([CFLAGS])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([CXXFLAGS])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([LDFLAGS])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([LIBS])
])

## Set up Automake
AM_INIT_AUTOMAKE([1.13.4 -Wall foreign color-tests tar-pax])
AM_SILENT_RULES([yes])
AFS_MAINTAINER_MODE

## Set up compilers
AFS_PROG_CC([99], [ext], [mandatory])
AFS_PROG_CXX([11], [noext], [mandatory])

## Set up Libtool
AM_PROG_AR
LT_PREREQ([2.4.6])
LT_INIT([])
AC_SUBST([LIBTOOL_DEPS])

## Set convenience variables for macros
ac_scorep_frontend=yes


##--- Package-specific configuration ----------------------------------------
AC_SCOREP_PACKAGE_AND_LIBRARY_VERSION
AC_SCOREP_DEFINE_REVISIONS
AC_SCOREP_CUBE_VARS
AC_SUBST([LIBRARY_INTERFACE_VERSION], m4_esyscmd([../build-config/common/generate-library-version.sh ../build-config/VERSION]))
AC_DEFINE_UNQUOTED([LIBRARY_INTERFACE_VERSION], ["$LIBRARY_INTERFACE_VERSION"], [Interface version number])
adl_RECURSIVE_EVAL([${libexecdir}/${PACKAGE}], [PKGLIBEXECDIR])
AC_DEFINE_UNQUOTED([PKGLIBEXECDIR],
                   ["${PKGLIBEXECDIR}"],
                   [Directory where ]AC_PACKAGE_NAME[ executables to be run by other programs rather than by users are installed])
adl_RECURSIVE_EVAL([${bindir}], [BINDIR])
AC_SUBST([BINDIR])
adl_RECURSIVE_EVAL([${includedir}], [INCLUDEDIR])
AC_SUBST([INCLUDEDIR])
adl_RECURSIVE_EVAL([${libdir}/${PACKAGE}], [PKGLIBDIR])
AC_SUBST([PKGLIBDIR])
adl_RECURSIVE_EVAL([${libdir}${backend_suffix}/${PACKAGE}], [BACKEND_PKGLIBDIR])
AC_SUBST([BACKEND_PKGLIBDIR])
adl_RECURSIVE_EVAL([${datadir}/${PACKAGE}], [PKGDATADIR])
AC_SUBST([PKGDATADIR])
AC_DEFINE_UNQUOTED([PKGDATADIR],
                  ["${PKGDATADIR}"],
                   [Directory where ]AC_PACKAGE_NAME[ data is stored])
adl_RECURSIVE_EVAL([${docdir}], [DOCDIR])
AC_SUBST([DOCDIR])

AC_SUBST([FRONTEND_CXX], [${CXX}])
AC_SUBST([FRONTEND_CC], [${CC}])

## Checks for programs
AC_LANG([C++])
AM_PROG_LEX
AC_PROG_YACC

## Checks for STL characteristics
CUBE_CXX_REGEX

AFS_DEBUG_OPTION
AC_CUBE_IO_BUFFERSIZE
AC_CUBE_STRATEGY_SELECTION

# check for network availability
AC_CUBE_NETWORK
AC_CUBE_ENABLE_CACHE

AC_SEARCH_LIBS([ceil], [m])
AC_CUBE_POSIX_FUNCTIONS
AC_CHECK_FUNCS_ONCE([readlink])
AX_PTHREAD


AC_CUBE_CONSTUCT_LIST_OF_LIB_DIRS
AC_CUBE_FRONTEND_SELECTION
AC_CUBE_LIBZ_FRONTEND_SELECTION
AC_SCOREP_CONFIG_SELECTION_REPORT([frontend])

## Setup Testing
AX_GTEST([../vendor/googletest])
AX_GMOCK
# disable backend tests (as there is no backend)
AM_CONDITIONAL([BACKEND_TEST_RUNS], [test 1 -eq 0])

#check for examples
AC_CUBE_EXAMPLES


dnl Predicate to use HARDCODE_LIBDIR_FLAG_* only if linker needs it.
AS_IF([test "x${hardcode_into_libs}" = "xyes"],
      [ac_scorep_hardcode_into_libs=1],
      [ac_scorep_hardcode_into_libs=0])
AC_SUBST([HARDCODE_INTO_LIBS], [${ac_scorep_hardcode_into_libs}])
dnl Flag to hardcode libdir into a binary during linking, C version.
AC_SUBST([HARDCODE_LIBDIR_FLAG_CC], [${hardcode_libdir_flag_spec}])
dnl Flag to hardcode libdir into a binary during linking, C++ version.
AC_SUBST([HARDCODE_LIBDIR_FLAG_CXX], [${hardcode_libdir_flag_spec_CXX}])
dnl The ${wl} part of the HARDCODE_LIBDIR_FLAG_* defines.
AC_SUBST([HARDCODE_LIBDIR_WL], [${wl}])
dnl The ${aix_libpath} part of the HARDCODE_LIBDIR_FLAG_* defines. Only available on AIX.
AC_SUBST([HARDCODE_LIBDIR_AIX_LIBPATH], [${aix_libpath}])


AC_SUBST([SYS_LIB_DLSEARCH_PATH_SPEC], [${sys_lib_dlsearch_path_spec}])

AC_CUBELIB_ERROR_CODES


AC_CONFIG_HEADERS([../src/cubelib-config-frontend.h])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([../examples/Makefile.frontend])
AC_CONFIG_FILES([../src/cubelib-version.h:../src/cubelib-version.h.in])
AC_CONFIG_FILES([../src/tools/tools/0002.Config/cubelib_config_data_]AFS_PACKAGE_BUILD_name[.cpp:../src/tools/tools/0002.Config/cubelib_config_data_build.cpp.in])


AC_CONFIG_FILES([../test/cpp-constructors/run_test.sh
                 ], \
                [chmod +x ../test/cpp-constructors/run_test.sh
                ])
AC_CONFIG_FILES([../test/cpp-constructors/cube_unite_test0.0.cpp
                 ])

AC_CONFIG_FILES([../test/tau-metrics/run_test.sh
                 ], \
                [chmod +x ../test/tau-metrics/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_cmp/run_test.sh
                 ], \
                [chmod +x ../test/cube_cmp/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_is_empty/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_is_empty/run_test.sh
                ])
AC_CONFIG_FILES([../test/gzip/run_test.sh
                 ], \
                [
                 chmod +x ../test/gzip/run_test.sh
                ])
AC_CONFIG_FILES([../test/cpp-lib/run_test.sh
                 ], \
                [
                 chmod +x ../test/cpp-lib/run_test.sh
                ])
AC_CONFIG_FILES([../test/excl-incl-values/run_test.sh
                 ], \
                [
                 chmod +x ../test/excl-incl-values/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube4to3/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube4to3/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube3to4/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube3to4/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_inclusify/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_inclusify/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_exclusify/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_exclusify/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_diff/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_diff/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_cut/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_cut/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_mean/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_mean/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_merge/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_merge/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_remap2_first/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_remap2_first/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_stat/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_stat/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_calltree/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_calltree/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_canonize/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_canonize/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_info/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_info/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_regioninfo/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_regioninfo/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_sanity/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_sanity/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_topoassistant/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_topoassistant/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_part/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_part/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_test/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_test/run_test.sh
                ])
AC_CONFIG_FILES([../test/tau2cube4/run_test.sh
                 ], \
                [
                 chmod +x ../test/tau2cube4/run_test.sh
                ])
AC_CONFIG_FILES([../test/cube_remap2_second/run_test.sh
                 ], \
                [
                 chmod +x ../test/cube_remap2_second/run_test.sh
                ])
AC_CONFIG_FILES([../test/ScaleFuncValue/run_test.sh
                 ], \
                [
                 chmod +x ../test/ScaleFuncValue/run_test.sh
                ])
AC_CONFIG_FILES([../test/histograms/run_test.sh
                 ], \
                [
                 chmod +x ../test/histograms/run_test.sh
                ])
AS_IF([ test "x$CUBE_DUMP_R_SELECTED" == "xyes" ],[
        AC_CONFIG_FILES([../test/r-binding/run_test.sh
                 ], \
                [
                 chmod +x ../test/r-binding/run_test.sh
                ])
])
AC_CONFIG_FILES([../test/cube_server/run_io_test.sh
                 ], \
                [
                 chmod +x ../test/cube_server/run_io_test.sh
                ])
AC_CONFIG_FILES([../test/cube_server/run_network_test.sh
                 ], \
                [
                 chmod +x ../test/cube_server/run_network_test.sh
                ])
AC_CONFIG_FILES([../test/cube_server/cube_selftest_CubeProxy_io.cpp]
                [../test/cube_server/cube_selftest_CubeProxy_network.cpp])
AC_OUTPUT
