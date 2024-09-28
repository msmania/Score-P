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
AC_INIT([CubeLib], m4_esyscmd([build-config/common/generate-package-version.sh build-config/VERSION]), [scalasca@fz-juelich.de],[cubelib],[http://www.scalasca.org])
AC_PREFIX_DEFAULT([/opt/cubelib])
AC_CONFIG_AUX_DIR([build-config])
## See also ACLOCAL_AMFLAGS in Makefile.am
AC_CONFIG_MACRO_DIRS([build-config/m4 build-config/common/m4])

## Set up AFS
AFS_PACKAGE_INIT
AFS_SUMMARY_INIT

## Save user provided arguments for use by sub-configures
AC_SCOREP_TOPLEVEL_ARGS

## Set up Automake
AM_INIT_AUTOMAKE([foreign color-tests 1.13.4 -Wall tar-pax])
AM_SILENT_RULES([yes])
AFS_MAINTAINER_MODE


##--- Package-specific configuration ----------------------------------------

## Working from git? Get revision info
AC_SCOREP_GIT_CONTROLLED
AC_SCOREP_UNCRUSTIFY
#AC_SCOREP_DEBUG_OPTION


AC_SCOREP_IS_ANOTHER_CUBE_INSTALLED
##
## Detect whether there is an another cube installation and warn user about it but do not stop configuration
##
AM_CONDITIONAL([ANOTHER_CUBE], [test "x$ANOTHER_CUBE_PRESENT" = "xyes"])
AM_CONDITIONAL([OVERWRITE_CUBE], [test "x$ANOTHER_CUBE_OVERWRITE" = "xyes"])



if test "x$prefix" = "xNONE"; then
AFS_SUMMARY( [Cube installed into],[$ac_default_prefix])
else
AFS_SUMMARY( [Cube installed into],[$prefix])
fi



AS_IF([ test "x$ANOTHER_CUBE_PRESENT" = "xyes"],[
AFS_SUMMARY([ Another installation of CUBE was detected under], [$anothercube])
])

AS_IF([ test "x$ANOTHER_CUBE_OVERWRITE" = "xyes"],[
AFS_SUMMARY([ This configuration will overwrite a present installation of cube under], [$overwritecube])
])




######################
AC_SCOREP_REVISION


## Platform detection
AC_SCOREP_DETECT_PLATFORMS
AC_SCOREP_PLATFORM_SETTINGS
AFS_CROSSCOMPILING



## Don't detect and load defaults in nested configures
AS_IF([test ! -n "$ac_scorep_platform_data_provided" || \
       test "x${ac_scorep_platform_data_provided}" = "xno"],
      [AFS_CUSTOM_COMPILERS
       AS_IF([test "x${afs_custom_compilers_given}" = "xno"],
             [dnl AFS_COMPILER_BACKEND([CC, CXX, F77, FC])
              AC_SCOREP_WITH_COMPILER_SUITE
              AS_CASE([${afs_custom_compilers_given},${ac_scorep_platform}],
                  [no,mac64|no,mingw64],
                      [AC_MSG_ERROR([have no suitable defaults to build Scalasca on $afs_scorep_platform_name yet. Please use --with-custom-compilers and provide settings to <AC_PACKAGE_BUGREPORT> on success. Thanks.])],
                  [no,unknown],
                      [AC_MSG_ERROR([cannot detect platform to set suitable defaults. Please use --with-custom-compilers and provide settings and platform to <AC_PACKAGE_BUGREPORT> on success. Thanks.])
                  ])
             ])
       # Determine arguments for subdir configures
       args="`$AWK -f $srcdir/build-config/common/process_arguments.awk \
              $ac_scorep_compilers_mpi                                         \
              $ac_scorep_compilers_frontend                                    \
              $ac_scorep_compilers_backend                                     \
              user_provided_configure_args`"
      ],
      [AC_MSG_NOTICE([platform data provided by toplevel configure.])
       AFS_SUMMARY([Platform], [$ac_scorep_platform (provided)])
       # Determine arguments for subdir configures
       args="`$AWK -f $srcdir/build-config/common/process_arguments.awk \
              user_provided_configure_args`"
      ])


AC_SUBST([backend_suffix])
AC_SUBST([target])

## Check for programs
AC_SCOREP_DOXYGEN



## Handle own package's subdir configures


AX_CONFIG_SUBDIR([build-frontend],
                                    [${args} ac_scorep_platform=${ac_scorep_platform} ac_scorep_cross_compiling=${ac_scorep_cross_compiling} ])


##--- Generate output -------------------------------------------------------


AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/config.h:src/config.h.in])
AC_CONFIG_FILES([src/cubelib-config-common.h:build-config/common/config-common.h])

AM_COND_IF([HAVE_DOXYGEN],
           [AC_CONFIG_FILES([doc/doxygen-common/config.tex
                             doc/doxygen-common/doxygen-common.cfg
                             doc/doxygen-common/doxygen-cubelib.cfg
                             doc/doxygen-dev/cubelib/doxygen-cubelib-dev.cfg
                             doc/doxygen-user/tools-dev/doxygen-tools-dev.cfg
                             doc/doxygen-user/tools-guide/doxygen-tools-guide.cfg
                             doc/doxygen-user/derived/doxygen-derived.cfg
                             ])])

# generate the OTF2 error codes header
AC_CONFIG_FILES(
    [include/cubelib/CubeErrorCodes.h:common/utils/src/exception/ErrorCodes.tmpl.h],
    [$srcdir/common/utils/src/exception/finalize_error_codes.sh CUBELIB $srcdir/share/cubelib/cubelib.errors include/cubelib/CubeErrorCodes.h include/cubelib/cubelib_error_decls.gen.h])

CUBE_CORPORATE_STY

AM_CONDITIONAL([INSTALL_MODULE_FILE], [test "x$INSTALL_MODULE_FILE" = "xyes"])


AC_OUTPUT


AFS_SUMMARY([cubelib-config], [ $prefix/bin])
AFS_SUMMARY([For detailed information], ["$prefix/bin/cubelib-config --help"])

AFS_SUMMARY([Examples], [$prefix/share/doc/cubelib/example ])



AFS_SUMMARY_COLLECT([test "x${afs_externally_triggered}" != "xyes"])
