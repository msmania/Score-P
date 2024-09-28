##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 2023                                                     ##
##  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ##
##                                                                         ##
##  This software may be modified and distributed under the terms of       ##
##  a BSD-style license.  See the COPYING file in the package base         ##
##  directory for details.                                                 ##
##*************************************************************************##


AC_DEFUN([AC_CUBE_POSIX_FUNCTIONS], [

AFS_POSIX_GETHOSTID
AFS_POSIX_GETHOSTNAME
AFS_POSIX_FSEEKO
AFS_C_DECL_POSIX_FSEEKO64
AFS_POSIX_GETCWD
AM_CONDITIONAL([HAVE_GETHOSTID], [test "x${afs_cv_have_posix_gethostid}" = "xyes"])
AM_CONDITIONAL([HAVE_GETHOSTNAME], [test "x${afs_cv_have_posix_gethostname}" = "xyes"])
AM_CONDITIONAL([HAVE_FSEEKO], [test "x${afs_cv_have_posix_fseeko}" = "xyes"])
AM_CONDITIONAL([HAVE_FSEEKO64], [test "x${afs_cv_have_posix_fseeko64}" = "xyes"])
AM_CONDITIONAL([HAVE_GETCWD], [test "x${afs_cv_have_posix_getcwd}" = "xyes"])
])