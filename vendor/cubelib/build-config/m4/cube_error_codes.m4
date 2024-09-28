##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 1998-2016                                                ##
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




AC_DEFUN([AC_CUBELIB_ERROR_CODES], [
AC_SUBST([PACKAGE_ERROR_CODES_INCDIR], [../include/cubelib])
AC_DEFINE_UNQUOTED(
    [PACKAGE_ERROR_CODES_HEADER],
    [<CubeErrorCodes.h>],
    [The #include argument used to include this packages error codes header.]
)
])
