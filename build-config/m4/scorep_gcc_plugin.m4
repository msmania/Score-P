dnl -*- mode: autoconf -*-

dnl
dnl This file is part of the Score-P software (http://www.score-p.org)
dnl
dnl Copyright (c) 2012-2016, 2022,
dnl Technische Universitaet Dresden, Germany
dnl
dnl Copyright (c) 2021-2023,
dnl Forschungszentrum Juelich GmbH, Germany
dnl
dnl This software may be modified and distributed under the terms of
dnl a BSD-style license.  See the COPYING file in the package base
dnl directory for details.
dnl


# SCOREP_GCC_PLUGIN_VENDORS()
# ---------------------------
# Provide scorep_gcc_plugin_target_vendor_c|cxx|fc. Sets
# scorep_gcc_plugin_target_vendor to gnu if one of the
# language-specific vendors is gnu.
#
AC_DEFUN([SCOREP_GCC_PLUGIN_VENDORS], [
AS_UNSET([scorep_gcc_plugin_target_vendor])
save_CPPFLAGS=$CPPFLAGS
CPPFLAGS=$GCC_PLUGIN_TARGET_CPPFLAGS
dnl
AC_LANG_PUSH([C])
_GCC_PLUGIN_VENDOR
AC_LANG_POP([C])
dnl
AC_LANG_PUSH([C++])
_GCC_PLUGIN_VENDOR
AC_LANG_POP([C++])
dnl
# Fortran is optional, FC and therefore GCC_PLUGIN_TARGET_FC might not
# be set. If set, check if in PATH.
AS_IF([test "x${GCC_PLUGIN_TARGET_FC}" != x && which "${GCC_PLUGIN_TARGET_FC}" > /dev/null 2>&1],
    [AC_LANG_PUSH([Fortran])
     AC_FC_PP_SRCEXT([F])
     _GCC_PLUGIN_VENDOR
     AC_LANG_POP([Fortran])])
dnl
CPPFLAGS=$save_CPPFLAGS
])dnl SCOREP_GCC_PLUGIN_VENDORS


# _GCC_PLUGIN_VENDOR()
# --------------------
#
m4_define([_GCC_PLUGIN_VENDOR], [
AS_IF([test "x${ax_cv_[]_AC_LANG_ABBREV[]_compiler_vendor}" != x],
    [AC_MSG_ERROR([ax_cv_[]_AC_LANG_ABBREV[]_compiler_vendor must not be set])])
save_[]_AC_CC[]=$[]_AC_CC
save_[]_AC_LANG_PREFIX[]FLAGS=$[]_AC_LANG_PREFIX[]FLAGS
_AC_CC[]=$GCC_PLUGIN_TARGET_[]_AC_CC
_AC_LANG_PREFIX[]FLAGS=$GCC_PLUGIN_TARGET_[]_AC_LANG_PREFIX[]FLAGS
AX_COMPILER_VENDOR
scorep_gcc_plugin_target_vendor_[]_AC_LANG_ABBREV[]="${ax_cv_[]_AC_LANG_ABBREV[]_compiler_vendor}"
AS_UNSET([ax_cv_[]_AC_LANG_ABBREV[]_compiler_vendor])
_AC_CC[]=$save_[]_AC_CC[]
_AC_LANG_PREFIX[]FLAGS=$save_[]_AC_LANG_PREFIX[]FLAGS
AS_IF([test "x${scorep_gcc_plugin_target_vendor_[]_AC_LANG_ABBREV[]}" = xgnu],
    [scorep_gcc_plugin_target_vendor=gnu])
])dnl _GCC_PLUGIN_VENDOR


# _GCC_PLUGIN_CHECK()
# -------------------
#
m4_define([_GCC_PLUGIN_CHECK], [
AC_REQUIRE([LT_OUTPUT])

AC_LANG_PUSH($1)

save_CPPFLAGS=$CPPFLAGS
CPPFLAGS="$CPPFLAGS -I${scorep_gcc_plugin_includedir} -isystem ${scorep_gcc_plugin_includedir} -I$srcdir/../src/adapters/compiler/gcc-plugin/fake-gmp"

AC_CHECK_HEADERS([gcc-plugin.h],
    [AC_CHECK_HEADERS([tree.h],
        [scorep_gcc_have_plugin_headers=yes],
        [scorep_gcc_have_plugin_headers=no],
        [[
#undef PACKAGE_NAME
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef PACKAGE_STRING
#undef PACKAGE_BUGREPORT
#undef PACKAGE_URL
#include <gcc-plugin.h>
]])],
    [scorep_gcc_have_plugin_headers=no],
    [[
/* no default includes */
#undef PACKAGE_NAME
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef PACKAGE_STRING
#undef PACKAGE_BUGREPORT
#undef PACKAGE_URL
]])

AC_MSG_CHECKING([for GCC $1 plug-in headers])
AC_MSG_RESULT([${scorep_gcc_have_plugin_headers}])

scorep_gcc_have_working_plugin=no
AS_IF([test "x${scorep_gcc_have_plugin_headers}" = "xyes"], [

    # minimalistic GCC plug-in
    AC_LANG_CONFTEST([AC_LANG_SOURCE([[
#undef PACKAGE_NAME
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef PACKAGE_STRING
#undef PACKAGE_BUGREPORT
#undef PACKAGE_URL
#include "gcc-plugin.h"
#include "tree.h"

int plugin_is_GPL_compatible = 1;

static void
body( void )
{
    ( void )build_fn_decl( "", NULL_TREE );
}

int
plugin_init( struct plugin_name_args*   plugin_info,
             struct plugin_gcc_version* version )
{
    body();
    return 0;
}]])])

    # build plug-in with libtool to get an shared object
    # -rpath is needed, else libool will only build an convenient library
    AC_MSG_CHECKING([to build a $1 plug-in])
    plugin_compile='$SHELL ./libtool --mode=compile --tag=_AC_CC [$]_AC_CC $CPPFLAGS [$]_AC_LANG_PREFIX[FLAGS] -c -o conftest.lo conftest.$ac_ext >&AS_MESSAGE_LOG_FD'
    plugin_link='$SHELL ./libtool --mode=link --tag=_AC_CC [$]_AC_CC [$]_AC_LANG_PREFIX[FLAGS] -module -avoid-version $LDFLAGS -rpath $PWD/lib -o confmodule.la conftest.lo >&AS_MESSAGE_LOG_FD'
    plugin_mkdir='$MKDIR_P lib >&AS_MESSAGE_LOG_FD'
    plugin_install='$SHELL ./libtool --mode=install $INSTALL confmodule.la $PWD/lib/confmodule.la >&AS_MESSAGE_LOG_FD'
    plugin_clean='$SHELL ./libtool --mode=clean $RM conftest.lo confmodule.la >&AS_MESSAGE_LOG_FD'
    AS_IF([_AC_DO_VAR([plugin_compile]) &&
        _AC_DO_VAR([plugin_link]) &&
        _AC_DO_VAR([plugin_mkdir]) &&
        _AC_DO_VAR([plugin_install])],
    [
        AC_MSG_RESULT([yes])

        # now try to use this plug-in in a compile test, always use the C
        # compiler, $1 is about in what language the compiler is written,
        # not what language the compiler should compile
        AC_LANG_PUSH([C])

        save_target_CC=$CC
        save_target_CPPFLAGS=$CPPFLAGS
        save_target_CFLAGS=$CFLAGS
        CC=$GCC_PLUGIN_TARGET_CC
        CPPFLAGS=$GCC_PLUGIN_TARGET_CPPFLAGS
        CFLAGS="$GCC_PLUGIN_TARGET_CFLAGS -fplugin=$PWD/lib/confmodule.so"

        AC_MSG_CHECKING([to load a $1 plug-in])
        AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [])],
            [scorep_gcc_have_working_plugin=yes
            AC_MSG_RESULT([yes])
            ],
            [scorep_gcc_plugin_support_reason="no, failed to load plug-in"
            AC_MSG_RESULT([no])
            ])

        CC=$save_target_CC
        CPPFLAGS=$save_target_CPPFLAGS
        CFLAGS=$save_target_CFLAGS

        AS_UNSET([save_target_CC])
        AS_UNSET([save_target_CPPFLAGS])
        AS_UNSET([save_target_CFLAGS])

        AC_LANG_POP([C])

        plugin_uninstall='$SHELL ./libtool --mode=uninstall $RM $PWD/lib/confmodule.la >&AS_MESSAGE_LOG_FD'
        _AC_DO_VAR([plugin_uninstall])
        plugin_rmdir='rmdir lib >&AS_MESSAGE_LOG_FD'
        _AC_DO_VAR([plugin_rmdir])
    ], [_AC_MSG_LOG_CONFTEST
        AC_MSG_RESULT([no])
    ])

    _AC_DO_VAR([plugin_clean])
    $RM conftest.$ac_ext

    AS_UNSET([plugin_compile])
    AS_UNSET([plugin_link])
    AS_UNSET([plugin_mkdir])
    AS_UNSET([plugin_install])
    AS_UNSET([plugin_clean])
    AS_UNSET([plugin_uninstall])
    AS_UNSET([plugin_rmdir])
], [
    scorep_gcc_plugin_support_reason="no, missing plug-in headers. We highly recommend installing the GCC plug-in development files, see INSTALL."
])

CPPFLAGS=$save_CPPFLAGS

AS_UNSET([save_CPPFLAGS])

AC_LANG_POP($1)

AC_MSG_CHECKING([for working GCC $1 plug-in support])
AS_IF([test "x${scorep_gcc_have_working_plugin}" = "xyes"],
    [AC_MSG_RESULT([yes])
    scorep_gcc_plugin_support_reason="yes, using the $1 compiler and -I${scorep_gcc_plugin_includedir}"
    $2
    :],
    [AC_MSG_RESULT([no])
    $3
    :])

AS_UNSET([scorep_gcc_have_plugin_headers])
AS_UNSET([scorep_gcc_have_working_plugin])
])dnl _GCC_PLUGIN_CHECK()


# _GCC_PLUGIN_TARGET_VERSION()
# ----------------------------
# Provides the GCC version for the target GCC as a number
# version = major * 1000 + minor
m4_define([_GCC_PLUGIN_TARGET_VERSION], [

# -dumpversion gives us only ever major.minor
scorep_gcc_plugin_target_version_dump_[]_AC_LANG_ABBREV[]="$($GCC_PLUGIN_TARGET_[]_AC_CC -dumpversion)"

scorep_gcc_plugin_target_version_[]_AC_LANG_ABBREV[]=0
AS_IF([test "x${scorep_gcc_plugin_target_version_dump_[]_AC_LANG_ABBREV[]}" != "x"],
      [scorep_gcc_plugin_target_version_major_[]_AC_LANG_ABBREV[]=${scorep_gcc_plugin_target_version_dump_[]_AC_LANG_ABBREV[]%%.*}
       scorep_gcc_plugin_target_version_minor_[]_AC_LANG_ABBREV[]=${scorep_gcc_plugin_target_version_dump_[]_AC_LANG_ABBREV[]#*.}
       scorep_gcc_plugin_target_version_minor_[]_AC_LANG_ABBREV[]=${scorep_gcc_plugin_target_version_minor_[]_AC_LANG_ABBREV[]%%.*}
       scorep_gcc_plugin_target_version_[]_AC_LANG_ABBREV[]=$(expr ${scorep_gcc_plugin_target_version_major_[]_AC_LANG_ABBREV[]} "*" 1000 + ${scorep_gcc_plugin_target_version_minor_[]_AC_LANG_ABBREV[]})])

AS_IF([test "x${scorep_gcc_plugin_target_version}" = x],
    [scorep_gcc_plugin_target_version="${scorep_gcc_plugin_target_version_[]_AC_LANG_ABBREV[]}"
     scorep_gcc_plugin_target_version_dump="scorep_gcc_plugin_target_version_dump_[]_AC_LANG_ABBREV[]"],
    [AS_IF([test "x${scorep_gcc_plugin_target_version}" != "x${scorep_gcc_plugin_target_version_[]_AC_LANG_ABBREV[]}"],
         [scorep_gcc_plugin_version_match=no])])
])dnl _GCC_PLUGIN_TARGET_VERSION


# SCOREP_GCC_PLUGIN()
# -------------------
# Performs checks whether the GCC compiler has plug-in support, and with which
# compiler it was built. Produces the AFS conditional HAVE_GCC_PLUGIN_SUPPORT.
# Communicate the support per language via the file gcc_plugin_supported_c|cxx|fc.
#
AC_DEFUN([SCOREP_GCC_PLUGIN], [
dnl
scorep_gcc_plugin_version_match=yes
AS_IF([test "x${scorep_gcc_plugin_target_vendor_c}" = xgnu],
    [AC_LANG_PUSH([C])
     _GCC_PLUGIN_TARGET_VERSION
     AC_LANG_POP([C])])
dnl
AS_IF([test "x${scorep_gcc_plugin_target_vendor_cxx}" = xgnu],
    [AC_LANG_PUSH([C++])
     _GCC_PLUGIN_TARGET_VERSION
     AC_LANG_POP([C++])])
dnl
AS_IF([test "x${scorep_gcc_plugin_target_vendor_fc}" = xgnu],
    [AC_LANG_PUSH([Fortran])
     _GCC_PLUGIN_TARGET_VERSION
     AC_LANG_POP([Fortran])])
dnl
scorep_gcc_plugin_support="no"
AS_IF([test "x${scorep_gcc_plugin_version_match}" = xno],
    [AC_MSG_WARN([GCC plug-in target compiler versions do not match: ${scorep_gcc_plugin_target_version_c}|${scorep_gcc_plugin_target_version_cxx}|${scorep_gcc_plugin_target_version_fc}. Disabling GCC plug-in.])
     scorep_gcc_plugin_support_reason="no, target compiler versions do not match: ${scorep_gcc_plugin_target_version_c}|${scorep_gcc_plugin_target_version_cxx}|${scorep_gcc_plugin_target_version_fc}"],
    [# target compiler versions do match
     AC_DEFINE_UNQUOTED([SCOREP_GCC_PLUGIN_TARGET_VERSION],
         [${scorep_gcc_plugin_target_version}],
         [The GCC version for what we build the plug-in.])

     # we need the include directory from the target CC
     scorep_gcc_plugin_includedir=$($GCC_PLUGIN_TARGET_CC -print-file-name=plugin/include)
     AS_IF([test ${scorep_gcc_plugin_target_version} -lt 4005],
         [scorep_gcc_plugin_support_reason="no, GCC ${scorep_gcc_plugin_target_version_dump} is too old, no plug-in support"],
         [test ${scorep_gcc_plugin_target_version} -lt 4009],
         [scorep_gcc_plugin_support_reason="no, GCC ${scorep_gcc_plugin_target_version_dump} is unsupported"],
         [# GCC 4.9 and onwards are always compiled with the C++ compiler
          _GCC_PLUGIN_CHECK([C++], [scorep_gcc_plugin_support="yes"])])])

AFS_AM_CONDITIONAL([HAVE_GCC_PLUGIN_SUPPORT], [test "x${scorep_gcc_plugin_support}" = "xyes"], [false])

AM_COND_IF([HAVE_GCC_PLUGIN_SUPPORT],
    [AS_IF([test "x${scorep_gcc_plugin_target_vendor_c}" = xgnu],
         [touch gcc_plugin_supported_c])
     AS_IF([test "x${scorep_gcc_plugin_target_vendor_cxx}" = xgnu],
         [touch gcc_plugin_supported_cxx])
     AS_IF([test "x${scorep_gcc_plugin_target_vendor_fc}" = xgnu],
         [touch gcc_plugin_supported_fc])
     AC_SUBST([SCOREP_GCC_PLUGIN_CXXFLAGS], ["-fno-rtti"])
     AC_SUBST([SCOREP_GCC_PLUGIN_CPPFLAGS], ["-I${scorep_gcc_plugin_includedir} -isystem ${scorep_gcc_plugin_includedir} -I$srcdir/../src/adapters/compiler/gcc-plugin/fake-gmp"])
     AC_LANG_PUSH([C++])

     AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [[
        __builtin_unreachable();
]])], [AC_DEFINE([HAVE_BUILTIN_UNREACHABLE], [1], [Compiler provides __builtin_unreachable()])])

     AC_LANG_POP([C++])
     AFS_PROG_CXX_SUMMARY
     AFS_COMMON_UTILS([build], [<SCOREP_ErrorCodes.h>], [../src/utils/include])
])

AS_UNSET([scorep_gcc_plugin_includedir])
])dnl SCOREP_GCC_PLUGIN
