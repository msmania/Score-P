/**
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2016,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2016,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 */

/**
 * Implementation of all __wrap_* functions used by the memory library wrapper
 */

#include <config.h>

#include "scorep_memory_event_functions.h"

SCOREP_MEMORY_WRAP_FREE( _ZdlPv, DELETE )
SCOREP_MEMORY_WRAP_FREE( _ZdaPv, DELETE_ARRAY )
