/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2013,
 * Technische Universitaet Dresden, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 */

#ifndef OTF2_CONFIG_H
#define OTF2_CONFIG_H

#include <string>
#include <deque>

#define OTF2_TOOL_NAME "otf2-config"

#include <otf2_tools.hpp>

void
remove_multiple_whitespaces( std::string& str );

void
replace_all( std::string&       str,
             const std::string& pattern,
             const std::string& replacement );

std::string
deque_to_string( const std::deque<std::string>& input,
                 const std::string&             head,
                 const std::string&             delimiter,
                 const std::string&             tail );

std::deque<std::string>
convert_to_string_list( const std::string& input,
                        const std::string& delimiter );

std::string
strip_leading_whitespace( const std::string& input );


std::string
strip_head( const std::string& input,
            const std::string& head_orig,
            const std::string& delimiter_orig );

bool
has_item( const std::deque<std::string>& input,
          const std::string&             item );

std::deque<std::string>
remove_double_entries( const std::deque<std::string>& input );

#endif /* OTF2_CONFIG_H */
