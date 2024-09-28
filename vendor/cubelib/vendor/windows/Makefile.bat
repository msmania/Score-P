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
set NSIS="C:\Program Files (x86)\NSIS"
set srcdir=..\..\
set PWD=%~dp0
set PREFIX=%1
set TARGET=C:\Scalasca-Soft\Install\Cube2.0\%PREFIX%\install


mkdir  %TARGET%\bin
mkdir  %TARGET%\lib
mkdir  %TARGET%\include\cubelib
mkdir  %TARGET%\share\icons
mkdir  %TARGET%\share\doc\cube\examples


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
cp ./include/cubelib-version.h ./cubelib-version.source
ls
echo "Fix version and SHA in version.h"
cat cubelib-version.source | sed -e "s/<REVISION SHA>/%REVISION%/g" | sed -e "s/<PACKAGE MAJOR>/%PACKAGEMAJOR%/g" |   sed -e "s/<PACKAGE MINOR>/%PACKAGEMINOR%/g" |   sed -e "s/<PACKAGE BUGFIX>/%PACKAGEBUGIX%/g" |   sed -e "s/<PACKAGE SUFFIX>/%PACKAGESUFFIX%/g"  > ./include/cubelib-version.h


for %%f in (
cube
tools\calltree
tools\canonize
tools\clean
tools\cmp
tools\commoncalltree
tools\cube3to4
tools\cube4to3
tools\cut
tools\derive
tools\diff
tools\dump
tools\exclusify
tools\inclusify
tools\info
tools\isempty
tools\mean
tools\merge
tools\nodeview
tools\part
tools\rank
tools\regioninfo
tools\remap2
tools\sanity
tools\server
tools\stat
tools\tau2cube
tools\test
tools\topoassist
) do (
cd  %%f
qmake || goto :error
mingw32-make clean || goto :error
mingw32-make || goto :error
cd %PWD%
echo "Copy %%f..."
copy %%f\release\*.exe %TARGET%\bin
copy %%f\release\*.dll %TARGET%\bin
copy %%f\release\*.a   %TARGET%\lib
)


echo "Copy system libraries..."
copy %MINGW%\bin\libgcc_s_*.dll %TARGET%\bin || goto :error
copy %MINGW%\bin\libstdc*-6.dll %TARGET%\bin || goto :error
copy %MINGW%\bin\libwinpthread*.dll %TARGET%\bin || goto :error
echo "Copy c++ header files..."
for %%f in (
%srcdir%\src\cube\include\service
%srcdir%\src\cube\include\service\cubelayout
%srcdir%\src\cube\include\service\cubelayout\layout
%srcdir%\src\cube\include\service\cubelayout\readers
%srcdir%\src\cube\include\dimensions\metric
%srcdir%\src\cube\include\dimensions\metric\strategies
%srcdir%\src\cube\include\dimensions\metric\data
%srcdir%\src\cube\include\dimensions\metric\cache
%srcdir%\src\cube\include\dimensions\metric\data\rows
%srcdir%\src\cube\include\dimensions\metric\matrix
%srcdir%\src\cube\include\dimensions\metric\index
%srcdir%\src\cube\include\dimensions\metric\value
%srcdir%\src\cube\include\dimensions\metric\value\trafo\single_value
%srcdir%\src\cube\include\dimensions\calltree
%srcdir%\src\cube\include\dimensions\system
%srcdir%\src\cube\include\dimensions
%srcdir%\src\cube\include\network
%srcdir%\src\cube\include\syntax
%srcdir%\src\cube\include\syntax\cubepl\evaluators
%srcdir%\src\cube\include\syntax\cubepl\evaluators\nullary
%srcdir%\src\cube\include\syntax\cubepl\evaluators\nullary\statements
%srcdir%\src\cube\include\syntax\cubepl\evaluators\unary
%srcdir%\src\cube\include\syntax\cubepl\evaluators\unary\functions\single_argument
%srcdir%\src\cube\include\syntax\cubepl\evaluators\unary\functions\two_arguments
%srcdir%\src\cube\include\syntax\cubepl\evaluators\unary\functions\lambda_calcul
%srcdir%\src\cube\include\syntax\cubepl\evaluators\binary
%srcdir%\src\cube\include\syntax\cubepl
%srcdir%\src\cube\include\derivated
%srcdir%\src\cube\include\topologies
%srcdir%\src\cube\include\
%srcdir%\src\tools\common_inc\
) do (
copy %%f  %TARGET%\include\cubelib\. || goto :error
)
echo "Copy generated header files..."
copy %srcdir%\vendor\windows\include\*.h %TARGET%\include\cubelib\. || goto :error


echo Copy Cube documentation..."
copy  %srcdir%\doc\*.pdf %TARGET%\share\doc\cube || goto :error
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
