/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2013,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2013,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2015, 2019, 2022,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2013,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2014,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2013,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2013,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */


/**
 * @file
 *
 * @brief Declaration of definition functions to be used by the adapter layer.
 *
 */


#include <config.h>


#include <SCOREP_Definitions.h>
#include <SCOREP_Memory.h>
#include "scorep_definitions_private.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <inttypes.h>


#include <UTILS_Error.h>
#define SCOREP_DEBUG_MODULE_NAME DEFINITIONS
#include <UTILS_Debug.h>


#include <jenkins_hash.h>


#include <SCOREP_DefinitionHandles.h>
#include <scorep_substrates_definition.h>
#include <scorep_type_utils.h>


SCOREP_StringHandle
SCOREP_Definitions_NewString( const char* str )
{
    UTILS_ASSERT( str );

    UTILS_DEBUG_ENTRY( "%s", str );

    SCOREP_Definitions_Lock();

    SCOREP_StringHandle new_handle = scorep_definitions_new_string(
        &scorep_local_definition_manager, str );

    SCOREP_Definitions_Unlock();

    return new_handle;
}


SCOREP_StringHandle
SCOREP_Definitions_NewStringGenerator( size_t                             stringLength,
                                       scorep_string_definition_generator generator,
                                       void*                              generatorArg )
{
    UTILS_ASSERT( generator );

    UTILS_DEBUG_ENTRY( "%zu", stringLength );

    SCOREP_Definitions_Lock();

    SCOREP_StringHandle new_handle = scorep_definitions_new_string_generator(
        &scorep_local_definition_manager,
        stringLength, generator, generatorArg );

    SCOREP_Definitions_Unlock();

    return new_handle;
}


void
scorep_definitions_unify_string( SCOREP_StringDef*             definition,
                                 SCOREP_Allocator_PageManager* handlesPageManager )
{
    UTILS_ASSERT( definition );
    UTILS_ASSERT( handlesPageManager );

    definition->unified = scorep_definitions_new_string(
        scorep_unified_definition_manager,
        definition->string_data );
}


static bool
equal_string( const SCOREP_StringDef* existingDefinition,
              const SCOREP_StringDef* newDefinition )
{
    return existingDefinition->string_length == newDefinition->string_length
           && 0 == memcmp( existingDefinition->string_data,
                           newDefinition->string_data,
                           existingDefinition->string_length );
}


SCOREP_StringHandle
scorep_definitions_new_string_generator( SCOREP_DefinitionManager*          definition_manager,
                                         size_t                             stringLength,
                                         scorep_string_definition_generator generator,
                                         void*                              generatorArg )
{
    UTILS_ASSERT( definition_manager );
    UTILS_ASSERT( generator );

    SCOREP_StringDef*   new_definition = NULL;
    SCOREP_StringHandle new_handle     = SCOREP_INVALID_STRING;

    /* 1) Get storage for new definition */
    SCOREP_DEFINITION_ALLOC_VARIABLE_ARRAY( String,
                                            char,
                                            stringLength + 1 );

    /* 2) Let the caller generate its string content */
    generator( stringLength, new_definition->string_data, generatorArg );
    new_definition->string_length = strlen( new_definition->string_data );
    new_definition->hash_value    = jenkins_hash( new_definition->string_data, new_definition->string_length, 0 );

    /*
     * 3) search in existing definitions and return found
     *    - discard new if an old one was found
     *    - if not, link new one into the hash chain and into definition list
     */
    /* Does return if it is a duplicate */
    SCOREP_DEFINITIONS_MANAGER_ADD_DEFINITION( String, string );

    if ( definition_manager == &scorep_local_definition_manager )
    {
        SCOREP_CALL_SUBSTRATE_MGMT( NewDefinitionHandle, NEW_DEFINITION_HANDLE,
                                    ( new_handle, SCOREP_HANDLE_TYPE_STRING ) );
    }

    return new_handle;
}


static void
generator_memcpy( size_t stringLength,
                  char*  stringStorage,
                  void*  arg )
{
    memcpy( stringStorage, arg, stringLength + 1 );
}


SCOREP_StringHandle
scorep_definitions_new_string( SCOREP_DefinitionManager* definition_manager,
                               const char*               string )
{
    UTILS_ASSERT( definition_manager );
    UTILS_ASSERT( string );

    return scorep_definitions_new_string_generator( definition_manager,
                                                    strlen( string ),
                                                    generator_memcpy,
                                                    ( void* )string );
}

struct generator_vsnprintf_args
{
    const char* string_format;
    va_list     va;
};

static void
generator_vsnprintf( size_t stringLength,
                     char*  stringStorage,
                     void*  arg )
{
    struct generator_vsnprintf_args* args = arg;
    vsnprintf( stringStorage, stringLength + 1, args->string_format, args->va );
}

SCOREP_StringHandle
scorep_definitions_new_string_va( SCOREP_DefinitionManager* definition_manager,
                                  size_t                    stringLength,
                                  const char*               formatString,
                                  va_list                   vaList )
{
    UTILS_ASSERT( definition_manager );
    UTILS_ASSERT( formatString );

    struct generator_vsnprintf_args args;
    args.string_format = formatString;
    /* Based on N1256 §7.15 footnote 221, taking the address of `va_list` is valid,
       but GCC issues a warning and segfaults, thus `va_copy` is used, which works. */
    va_copy( args.va, vaList );

    return scorep_definitions_new_string_generator( definition_manager,
                                                    stringLength,
                                                    generator_vsnprintf,
                                                    &args );
}

const char*
SCOREP_StringHandle_Get( SCOREP_StringHandle handle )
{
    SCOREP_StringDef* str = SCOREP_LOCAL_HANDLE_DEREF( handle, String );

    return str->string_data;
}

const char*
SCOREP_StringHandle_GetById( uint32_t id )
{
    SCOREP_DEFINITIONS_MANAGER_FOREACH_DEFINITION_BEGIN( &scorep_local_definition_manager, String, string )
    {
        if ( id == definition->sequence_number )
        {
            return definition->string_data;
        }
    }
    SCOREP_DEFINITIONS_MANAGER_FOREACH_DEFINITION_END();
    return NULL;
}
