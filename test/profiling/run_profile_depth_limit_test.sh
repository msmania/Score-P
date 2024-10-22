#!/bin/bash

##
## This file is part of the Score-P software (http://www.score-p.org)
##
## Copyright (c) 2009-2011,
## RWTH Aachen University, Germany
##
## Copyright (c) 2009-2011,
## Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
##
## Copyright (c) 2009-2011, 2015, 2022,
## Technische Universitaet Dresden, Germany
##
## Copyright (c) 2009-2011,
## University of Oregon, Eugene, USA
##
## Copyright (c) 2009-2011, 2016,
## Forschungszentrum Juelich GmbH, Germany
##
## Copyright (c) 2009-2011,
## German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
##
## Copyright (c) 2009-2011,
## Technische Universitaet Muenchen, Germany
##
## This software may be modified and distributed under the terms of
## a BSD-style license. See the COPYING file in the package base
## directory for details.
##

## file       run_profile_depth_limit_test.sh

RESULT_DIR=scorep-profile-depth-limit-test-dir
rm -rf $RESULT_DIR

# Run test
SCOREP_EXPERIMENT_DIRECTORY=$RESULT_DIR SCOREP_PROFILING_MAX_CALLPATH_DEPTH=5 SCOREP_ENABLE_PROFILING=true SCOREP_ENABLE_TRACING=false ./profile_depth_limit_test

# Check output
if [ ! -e $RESULT_DIR/profile.cubex ]; then
  echo "Error: No profile generated."
  exit 1
fi

#NUM_CNODES=`GREP_OPTIONS= grep -c "<cnode id=" $RESULT_DIR/profile.cubex`
NUM_CNODES=`"../vendor/cubelib/build-frontend/cube_calltree" -m visits -f $RESULT_DIR/profile.cubex | wc -l`
if [ ! x$NUM_CNODES = x6 ]; then
  echo "Expected 6 callpath definitions, but found $NUM_CNODES"
  exit 1
fi

rm -rf $RESULT_DIR
exit 0
