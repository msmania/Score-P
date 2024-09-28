::*************************************************************************::
::  CUBE        http://www.scalasca.org/                                   ::
::*************************************************************************::
::  Copyright (c) 2009-2022                                                ::
::  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ::
::                                                                         ::
::  Copyright (c) 2009-2021                                                ::
::  German Research School for Simulation Sciences GmbH,                   ::
::  Laboratory for Parallel Programming                                    ::
::                                                                         ::
::  Copyright (c) 2009-2014                                                ::
::  RWTH Aachen University, IT Center                                      ::
::                                                                         ::
::  Copyright (c) 2009-2014                                                ::
::  Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany      ::
::                                                                         ::
::  Copyright (c) 2009-2014                                                ::
::  TU Dresden, Zentrum fuer Informationsdienste und Hochleistungsrechnen  ::
::                                                                         ::
::  Copyright (c) 2009-2014                                                ::
::  University of Oregon, Eugene, USA                                      ::
::                                                                         ::
::  Copyright (c) 2009-2014                                                ::
::  Technische Universitaet Muenchen, Germany                              ::
::                                                                         ::
::  This software may be modified and distributed under the terms of       ::
::  a BSD-style license.  See the COPYING file in the package base         ::
::  directory for details.                                                 ::
::*************************************************************************::

:: maintainer Pavel Saviankou <p.saviankou@fz-juelich.de>
set MINGW=C:\QtSDK\5.13.1\mingw73_64
set QTDIR="C:\QtSDK\5.13.1\mingw73_64"
set NSIS="C:\Program Files (x86)\NSIS"
set srcdir=..\..\
set PWD=%~dp0
set PREFIX=%1
set TARGET=C:\Scalasca-Soft\Install\Cube2.0\%PREFIX%\install


mkdir %TARGET%\bin
mkdir %TARGET%\lib
mkdir %TARGET%\include\cubew
mkdir %TARGET%\share\icons
mkdir %TARGET%\share\doc\cubew\examples

echo "Read version and SHA in VERSION and REVISION files"

cat ../../build-config/VERSION | grep "package.major"  | sed -e "s/package\.major=//g"> package.major
cat ../../build-config/VERSION | grep "package.minor"  | sed -e "s/package\.minor=//g"> package.minor
cat ../../build-config/VERSION | grep "package.bugfix" | sed -e "s/package\.bugfix=//g"> package.bugfix
cat ../../build-config/VERSION | grep "package.suffix" | sed -e "s/package\.suffix=//g"> package.suffix

set /p REVISION=<../../build-config/REVISION

echo "Read Cube version"
set /p PACKAGEMAJOR=<package.major

set /p PACKAGEMINOR=<package.minor

set /p PACKAGEBUGIX=<package.bugfix

set /p PACKAGESUFFIX=<package.suffix

del package.major
del package.minor
del package.bugfix
del package.suffix

echo "Backup"
cp ./include/cubew-version.h ./cubew-version.source
ls
echo "Fix version and SHA in version.h"
cat cubew-version.source | sed -e "s/<REVISION SHA>/%REVISION%/g" | sed -e "s/<PACKAGE MAJOR>/%PACKAGEMAJOR%/g" |   sed -e "s/<PACKAGE MINOR>/%PACKAGEMINOR%/g" |   sed -e "s/<PACKAGE BUGFIX>/%PACKAGEBUGIX%/g" |   sed -e "s/<PACKAGE SUFFIX>/%PACKAGESUFFIX%/g"  > ./include/cubew-version.h

for %%f in (
cubew
) do (
cd  %%f
qmake || goto :error
mingw32-make clean || goto :error
mingw32-make || goto :error
cd %PWD%
echo "Copy %%f..."
copy %%f\release\*.dll %TARGET%\bin || goto :error
copy %%f\release\*.a   %TARGET%\lib || goto :error
)


echo "Copy system libraries..."
copy %MINGW%\bin\libgcc_s_*.dll %TARGET%\bin || goto :error
copy %MINGW%\bin\libstd*.dll %TARGET%\bin || goto :error
echo "Copy c-writer header files..."
copy %srcdir%\src\cubew\*.h  %TARGET%\include\cubew\. || goto :error
echo "Copy generated header files..."
copy %srcdir%\vendor\windows\include\*.h %TARGET%\include\cubew\. || goto :error
@echo "Copy Cube license..."
copy  %srcdir%\COPYING %TARGET%\license.txt || goto :error
echo "NOW COMPILE NSIS script..."

:; exit 0
exit /b 0

:error
if errorlevel 1 (
   echo "Failure during copy : %errorlevel%"
   exit /b %errorlevel%
)
