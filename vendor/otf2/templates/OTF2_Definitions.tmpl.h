/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2012,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2012,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2012, 2021,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2012,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2012,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2012,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2012,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */


#ifndef OTF2_DEFINITIONS_H
#define OTF2_DEFINITIONS_H


/**
 *  @file
 *  @source     templates/OTF2_Definitions.tmpl.h
 *
 *  @brief      Data types used in the definition records.
 */


#include "otf2_compiler.h"


#include <otf2/OTF2_ErrorCodes.h>


#include <otf2/OTF2_GeneralDefinitions.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

@otf2 for enum in enums|def_enums:

/** @brief Wrapper for enum @eref{@@enum.type@@_enum}. */
typedef @@enum.type.c_orig@@ @@enum.type@@;

/**
 * @brief @@enum.doxygendoc(prefix=' * ')@@
@otf2  if enum is bitset_enum:
 *
 * This enumeration is treated as a bit field; that is, a set of flags.
@otf2  endif
 *
 * @since Version @@enum.since@@
 */
@@enum.c_decl()@@

@otf2 for alias in enum.aliases

/** @brief Alias for @eref{@@enum.type@@}. */
typedef @@enum.type@@ @@alias@@;

@otf2 endfor
@otf2 endfor

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* OTF2_DEFINITIONS_H */
