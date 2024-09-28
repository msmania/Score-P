// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file ../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp
 ** Define the cubeplparser::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_CUBEPLPARSER_CUBELIB_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBEPL_CUBEPL1PARSER_HPP_INCLUDED
# define YY_CUBEPLPARSER_CUBELIB_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBEPL_CUBEPL1PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 17 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"

/*** C/C++ Declarations ***/
#include <cubelib-config-common.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include <regex>

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePL1ParseContext.h"

#include "CubeEncapsulation.h"
#include "CubeNegativeEvaluation.h"
#include "CubeConstantEvaluation.h"
#include "CubeStringConstantEvaluation.h"

#include "CubeDirectMetricEvaluation.h"
#include "CubePlusEvaluation.h"
#include "CubeMinusEvaluation.h"
#include "CubeMultEvaluation.h"
#include "CubeDivideEvaluation.h"
#include "CubePowerEvaluation.h"

#include "CubeAndEvaluation.h"
#include "CubeOrEvaluation.h"
#include "CubeXorEvaluation.h"
#include "CubeNotEvaluation.h"

#include "CubeStringEqualityEvaluation.h"
#include "CubeStringSemiEqualityEvaluation.h"
#include "CubeRegexEvaluation.h"
#include "CubeLowerCaseEvaluation.h"
#include "CubeUpperCaseEvaluation.h"
#include "CubeMetricGetEvaluation.h"
#include "CubeEnvEvaluation.h"


#include "CubeBiggerEvaluation.h"
#include "CubeSmallerEvaluation.h"
#include "CubeHalfBiggerEvaluation.h"
#include "CubeHalfSmallerEvaluation.h"
#include "CubeEqualEvaluation.h"
#include "CubeNotEqualEvaluation.h"

#include "CubeArgumentEvaluation.h"
#include "CubeATanEvaluation.h"
#include "CubeTanEvaluation.h"
#include "CubeACosEvaluation.h"
#include "CubeASinEvaluation.h"
#include "CubeCosEvaluation.h"
#include "CubeSinEvaluation.h"
#include "CubeAbsEvaluation.h"

#include "CubeLnEvaluation.h"
#include "CubeExpEvaluation.h"

#include "CubeRandomEvaluation.h"
#include "CubeSqrtEvaluation.h"

#include "CubeSgnEvaluation.h"
#include "CubePosEvaluation.h"
#include "CubeNegEvaluation.h"
#include "CubeFloorEvaluation.h"
#include "CubeCeilEvaluation.h"

#include "CubeMinEvaluation.h"
#include "CubeMaxEvaluation.h"

#include "CubeLambdaCalculEvaluation.h"
#include "CubeAssignmentEvaluation.h"
#include "CubeVariableEvaluation.h"
#include "CubeShortIfEvaluation.h"
#include "CubeFullIfEvaluation.h"
#include "CubeExtendedIfEvaluation.h"
#include "CubeWhileEvaluation.h"
#include "CubeMetricSetEvaluation.h"

#include "CubeSizeOfVariableEvaluation.h"
#include "CubeDefinedVariableEvaluation.h"
#include "CubePL1Driver.h"
#define CUBELIB_DEBUG_MODULE_NAME CUBEPL_PARSER
#include <UTILS_Debug.h>

#ifdef HAVE_CUBELIB_DEBUG
#include <sstream>
#endif



#line 147 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef CUBEPLPARSERDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define CUBEPLPARSERDEBUG 1
#  else
#   define CUBEPLPARSERDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define CUBEPLPARSERDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined CUBEPLPARSERDEBUG */

namespace cubeplparser {
#line 290 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp"




  /// A Bison parser.
  class CubePL1Parser
  {
  public:
#ifdef CUBEPLPARSERSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define CUBEPLPARSERSTYPE in C++, use %define api.value.type"
# endif
    typedef CUBEPLPARSERSTYPE value_type;
#else
    /// Symbol semantic values.
    union value_type
    {
#line 161 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"

#line 310 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp"

    };
#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        CUBEPLPARSEREMPTY = -2,
    END = 0,                       // "end of file"
    CUBEPLPARSERerror = 256,       // error
    CUBEPLPARSERUNDEF = 601,       // "invalid token"
    START_DOCUMENT = 602,          // "<cubepl>"
    END_DOCUMENT = 603,            // "</cubepl>"
    OP_PLUS = 604,                 // "+"
    OP_MINUS = 605,                // "-"
    OP_MULT = 606,                 // "*"
    OP_DIVIDE = 607,               // "/"
    OP_POWER = 608,                // "^"
    OPEN_EXP = 609,                // "("
    CLOSE_EXP = 610,               // ")"
    OPEN_ARRAY_INDEX = 611,        // "["
    CLOSE_ARRAY_INDEX = 612,       // "]"
    OPEN_LCALC = 613,              // "{"
    CLOSE_LCALC = 614,             // "}"
    OPEN_GM_CUBEPL = 615,          // "<<"
    CLOSE_GM_CUBEPL = 616,         // ">>"
    RETURN_EXP = 617,              // "return"
    STATEMENT_SEP = 618,           // ";"
    SIZEOF = 619,                  // "sizeof"
    DEFINED = 620,                 // "defined"
    LOCAL_VAR = 621,               // "local"
    GLOBAL_VAR = 622,              // "global"
    ABS_MARK = 623,                // "|"
    ARGUMENT1 = 624,               // "arg1"
    ARGUMENT2 = 625,               // "arg2"
    FUN_SQRT = 626,                // "sqrt"
    FUN_SIN = 627,                 // "sin"
    FUN_ASIN = 628,                // "asin"
    FUN_COS = 629,                 // "cos"
    FUN_ACOS = 630,                // "acos"
    FUN_TAN = 631,                 // "tan"
    FUN_ATAN = 632,                // "atan"
    FUN_EXP = 633,                 // "exp"
    FUN_LOG = 634,                 // "log"
    FUN_ABS = 635,                 // "abs"
    FUN_RANDOM = 636,              // "random"
    FUN_SGN = 637,                 // "sgn"
    FUN_POS = 638,                 // "pos"
    FUN_NEG = 639,                 // "neg"
    FUN_FLOOR = 640,               // "floor"
    FUN_CEIL = 641,                // "ceil"
    FUN_MIN = 642,                 // "min"
    FUN_MAX = 643,                 // "max"
    KEYWORD_IF = 644,              // "if"
    KEYWORD_ELSEIF = 645,          // "elseif"
    KEYWORD_ELSE = 646,            // "else"
    KEYWORD_WHILE = 647,           // "while"
    KEYWORD_ASSIGN = 648,          // "="
    KEYWORD_BIGGER = 649,          // ">"
    KEYWORD_EQUAL = 650,           // "=="
    KEYWORD_STRING_EQUAL = 651,    // "eq"
    KEYWORD_STRING_SEMI_EQUAL = 652, // "seq"
    KEYWORD_HALFBIGGER = 653,      // ">="
    KEYWORD_HALFSMALLER = 654,     // "<="
    KEYWORD_NOT_EQUAL = 655,       // "!="
    KEYWORD_SMALLER = 656,         // "<"
    KEYWORD_NOT = 657,             // "not"
    KEYWORD_AND = 658,             // "and"
    KEYWORD_OR = 659,              // "or"
    KEYWORD_XOR = 660,             // "xor"
    KEYWORD_TRUE = 661,            // "true"
    KEYWORD_FALSE = 662,           // "false"
    KEYWORD_VAR = 663,             // "$"
    COMMA = 664,                   // ","
    KEYWORD_REGEXP = 665,          // "=~"
    KEYWORD_METRIC = 666,          // "metric::"
    KEYWORD_FIXED_METRIC = 667,    // "metric::fixed::"
    KEYWORD_METRIC_CALL = 668,     // "metric::call::"
    KEYWORD_ENV = 669,             // "env"
    KEYWORD_LOWERCASE = 670,       // "lowercase"
    KEYWORD_UPPERCASE = 671,       // "uppercase"
    KEYWORD_GHOST_POSTMETRIC = 672, // "cube::metric::postderived::"
    KEYWORD_GHOST_PREMETRIC = 673, // "cube::metric::prederived::"
    KEYWORD_METRIC_INIT = 674,     // "cube::init::metric::"
    KEYWORD_METRIC_FLEX_AGGR_PLUS = 675, // "cube::metric::plus::"
    KEYWORD_METRIC_FLEX_AGGR_MINUS = 676, // "cube::metric::minus::"
    KEYWORD_METRIC_SET = 677,      // "cube::metric::set::"
    KEYWORD_METRIC_GET = 678,      // "cube::metric::get::"
    CONSTANT = 100,                // CONSTANT
    STRING_CONSTANT = 200,         // STRING_CONSTANT
    STRING_TEXT = 210,             // STRING_TEXT
    METRIC_NAME = 300,             // METRIC_NAME
    INIT_METRIC_NAME = 301,        // INIT_METRIC_NAME
    INCL_MODIFICATOR = 679,        // "i"
    EXCL_MODIFICATOR = 680,        // "e"
    SAME_MODIFICATOR = 600,        // SAME_MODIFICATOR
    QUOTED_STRING = 400,           // QUOTED_STRING
    REGEXP_STRING = 500,           // REGEXP_STRING
    FUNC2 = 681,                   // FUNC2
    SIGN = 682                     // SIGN
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 92, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_START_DOCUMENT = 3,                    // "<cubepl>"
        S_END_DOCUMENT = 4,                      // "</cubepl>"
        S_OP_PLUS = 5,                           // "+"
        S_OP_MINUS = 6,                          // "-"
        S_OP_MULT = 7,                           // "*"
        S_OP_DIVIDE = 8,                         // "/"
        S_OP_POWER = 9,                          // "^"
        S_OPEN_EXP = 10,                         // "("
        S_CLOSE_EXP = 11,                        // ")"
        S_OPEN_ARRAY_INDEX = 12,                 // "["
        S_CLOSE_ARRAY_INDEX = 13,                // "]"
        S_OPEN_LCALC = 14,                       // "{"
        S_CLOSE_LCALC = 15,                      // "}"
        S_OPEN_GM_CUBEPL = 16,                   // "<<"
        S_CLOSE_GM_CUBEPL = 17,                  // ">>"
        S_RETURN_EXP = 18,                       // "return"
        S_STATEMENT_SEP = 19,                    // ";"
        S_SIZEOF = 20,                           // "sizeof"
        S_DEFINED = 21,                          // "defined"
        S_LOCAL_VAR = 22,                        // "local"
        S_GLOBAL_VAR = 23,                       // "global"
        S_ABS_MARK = 24,                         // "|"
        S_ARGUMENT1 = 25,                        // "arg1"
        S_ARGUMENT2 = 26,                        // "arg2"
        S_FUN_SQRT = 27,                         // "sqrt"
        S_FUN_SIN = 28,                          // "sin"
        S_FUN_ASIN = 29,                         // "asin"
        S_FUN_COS = 30,                          // "cos"
        S_FUN_ACOS = 31,                         // "acos"
        S_FUN_TAN = 32,                          // "tan"
        S_FUN_ATAN = 33,                         // "atan"
        S_FUN_EXP = 34,                          // "exp"
        S_FUN_LOG = 35,                          // "log"
        S_FUN_ABS = 36,                          // "abs"
        S_FUN_RANDOM = 37,                       // "random"
        S_FUN_SGN = 38,                          // "sgn"
        S_FUN_POS = 39,                          // "pos"
        S_FUN_NEG = 40,                          // "neg"
        S_FUN_FLOOR = 41,                        // "floor"
        S_FUN_CEIL = 42,                         // "ceil"
        S_FUN_MIN = 43,                          // "min"
        S_FUN_MAX = 44,                          // "max"
        S_KEYWORD_IF = 45,                       // "if"
        S_KEYWORD_ELSEIF = 46,                   // "elseif"
        S_KEYWORD_ELSE = 47,                     // "else"
        S_KEYWORD_WHILE = 48,                    // "while"
        S_KEYWORD_ASSIGN = 49,                   // "="
        S_KEYWORD_BIGGER = 50,                   // ">"
        S_KEYWORD_EQUAL = 51,                    // "=="
        S_KEYWORD_STRING_EQUAL = 52,             // "eq"
        S_KEYWORD_STRING_SEMI_EQUAL = 53,        // "seq"
        S_KEYWORD_HALFBIGGER = 54,               // ">="
        S_KEYWORD_HALFSMALLER = 55,              // "<="
        S_KEYWORD_NOT_EQUAL = 56,                // "!="
        S_KEYWORD_SMALLER = 57,                  // "<"
        S_KEYWORD_NOT = 58,                      // "not"
        S_KEYWORD_AND = 59,                      // "and"
        S_KEYWORD_OR = 60,                       // "or"
        S_KEYWORD_XOR = 61,                      // "xor"
        S_KEYWORD_TRUE = 62,                     // "true"
        S_KEYWORD_FALSE = 63,                    // "false"
        S_KEYWORD_VAR = 64,                      // "$"
        S_COMMA = 65,                            // ","
        S_KEYWORD_REGEXP = 66,                   // "=~"
        S_KEYWORD_METRIC = 67,                   // "metric::"
        S_KEYWORD_FIXED_METRIC = 68,             // "metric::fixed::"
        S_KEYWORD_METRIC_CALL = 69,              // "metric::call::"
        S_KEYWORD_ENV = 70,                      // "env"
        S_KEYWORD_LOWERCASE = 71,                // "lowercase"
        S_KEYWORD_UPPERCASE = 72,                // "uppercase"
        S_KEYWORD_GHOST_POSTMETRIC = 73,         // "cube::metric::postderived::"
        S_KEYWORD_GHOST_PREMETRIC = 74,          // "cube::metric::prederived::"
        S_KEYWORD_METRIC_INIT = 75,              // "cube::init::metric::"
        S_KEYWORD_METRIC_FLEX_AGGR_PLUS = 76,    // "cube::metric::plus::"
        S_KEYWORD_METRIC_FLEX_AGGR_MINUS = 77,   // "cube::metric::minus::"
        S_KEYWORD_METRIC_SET = 78,               // "cube::metric::set::"
        S_KEYWORD_METRIC_GET = 79,               // "cube::metric::get::"
        S_CONSTANT = 80,                         // CONSTANT
        S_STRING_CONSTANT = 81,                  // STRING_CONSTANT
        S_STRING_TEXT = 82,                      // STRING_TEXT
        S_METRIC_NAME = 83,                      // METRIC_NAME
        S_INIT_METRIC_NAME = 84,                 // INIT_METRIC_NAME
        S_INCL_MODIFICATOR = 85,                 // "i"
        S_EXCL_MODIFICATOR = 86,                 // "e"
        S_SAME_MODIFICATOR = 87,                 // SAME_MODIFICATOR
        S_QUOTED_STRING = 88,                    // QUOTED_STRING
        S_REGEXP_STRING = 89,                    // REGEXP_STRING
        S_FUNC2 = 90,                            // FUNC2
        S_SIGN = 91,                             // SIGN
        S_YYACCEPT = 92,                         // $accept
        S_document = 93,                         // document
        S_expression = 94,                       // expression
        S_enclosed_expression = 95,              // enclosed_expression
        S_absolute_value = 96,                   // absolute_value
        S_sum = 97,                              // sum
        S_subtract = 98,                         // subtract
        S_division = 99,                         // division
        S_multiplication = 100,                  // multiplication
        S_power = 101,                           // power
        S_negation = 102,                        // negation
        S_arguments = 103,                       // arguments
        S_argument1 = 104,                       // argument1
        S_argument2 = 105,                       // argument2
        S_boolean_expression = 106,              // boolean_expression
        S_enclosed_boolean_expression = 107,     // enclosed_boolean_expression
        S_and_expression = 108,                  // and_expression
        S_or_expression = 109,                   // or_expression
        S_xor_expression = 110,                  // xor_expression
        S_true_expression = 111,                 // true_expression
        S_false_expression = 112,                // false_expression
        S_equality = 113,                        // equality
        S_not_equality = 114,                    // not_equality
        S_bigger = 115,                          // bigger
        S_smaller = 116,                         // smaller
        S_halfbigger = 117,                      // halfbigger
        S_halfsmaller = 118,                     // halfsmaller
        S_string_operation = 119,                // string_operation
        S_string_equality = 120,                 // string_equality
        S_string_semi_equality = 121,            // string_semi_equality
        S_regexp = 122,                          // regexp
        S_regexp_expression = 123,               // regexp_expression
        S_quoted_string = 124,                   // quoted_string
        S_string_function = 125,                 // string_function
        S_lowercase = 126,                       // lowercase
        S_uppercase = 127,                       // uppercase
        S_getenv = 128,                          // getenv
        S_metric_get = 129,                      // metric_get
        S_function_call = 130,                   // function_call
        S_one_variable_function = 131,           // one_variable_function
        S_function_name = 132,                   // function_name
        S_two_variables_function = 133,          // two_variables_function
        S_function2_name = 134,                  // function2_name
        S_constant = 135,                        // constant
        S_metric_refs = 136,                     // metric_refs
        S_context_metric = 137,                  // context_metric
        S_fixed_metric = 138,                    // fixed_metric
        S_metric_call = 139,                     // metric_call
        S_calculationFlavourModificator = 140,   // calculationFlavourModificator
        S_lambda_calcul = 141,                   // lambda_calcul
        S_return_expression = 142,               // return_expression
        S_lambda_start = 143,                    // lambda_start
        S_list_of_statements = 144,              // list_of_statements
        S_statement = 145,                       // statement
        S_metric_set = 146,                      // metric_set
        S_if_statement = 147,                    // if_statement
        S_simple_if_statement = 148,             // simple_if_statement
        S_full_if_statement = 149,               // full_if_statement
        S_elseif_full_if_statement = 150,        // elseif_full_if_statement
        S_elseif_if_statement = 151,             // elseif_if_statement
        S_elseifs = 152,                         // elseifs
        S_elseif_enclosed_list_of_statements = 153, // elseif_enclosed_list_of_statements
        S_if_condition = 154,                    // if_condition
        S_else_enclosed_list_of_statements = 155, // else_enclosed_list_of_statements
        S_enclosed_list_of_statements = 156,     // enclosed_list_of_statements
        S_enclosed_list_of_statements_start = 157, // enclosed_list_of_statements_start
        S_while_statement = 158,                 // while_statement
        S_assignment = 159,                      // assignment
        S_assignment_target = 160,               // assignment_target
        S_put_variable = 161,                    // put_variable
        S_put_variable_indexed = 162,            // put_variable_indexed
        S_create_ghost_metric = 163,             // create_ghost_metric
        S_create_postderived_ghost_metric = 164, // create_postderived_ghost_metric
        S_create_prederived_inclusive_ghost_metric = 165, // create_prederived_inclusive_ghost_metric
        S_create_prederived_exclusive_ghost_metric = 166, // create_prederived_exclusive_ghost_metric
        S_GhostMetricDefinition = 167,           // GhostMetricDefinition
        S_CubePLGhostText = 168,                 // CubePLGhostText
        S_init_metric = 169,                     // init_metric
        S_flex_aggr_plus = 170,                  // flex_aggr_plus
        S_flex_aggr_minus = 171,                 // flex_aggr_minus
        S_get_variable = 172,                    // get_variable
        S_get_variable_simple = 173,             // get_variable_simple
        S_get_variable_indexed = 174,            // get_variable_indexed
        S_sizeof_variable = 175,                 // sizeof_variable
        S_defined_variable = 176,                // defined_variable
        S_local_variable = 177,                  // local_variable
        S_global_variable = 178,                 // global_variable
        S_string_constant = 179                  // string_constant
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value (std::move (that.value))
        , location (std::move (that.location))
      {}
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);
      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t,
                    YY_MOVE_REF (location_type) l);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    YY_RVREF (value_type) v,
                    YY_RVREF (location_type) l);

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return CubePL1Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {};

    /// Build a parser object.
    CubePL1Parser (class CubePL1ParseContext& parseContext_yyarg, class CubePL1Scanner& CubePL1Lexer_yyarg);
    virtual ~CubePL1Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    CubePL1Parser (const CubePL1Parser&) = delete;
    /// Non copyable.
    CubePL1Parser& operator= (const CubePL1Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if CUBEPLPARSERDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);



    class context
    {
    public:
      context (const CubePL1Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const CubePL1Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    CubePL1Parser (const CubePL1Parser&);
    /// Non copyable.
    CubePL1Parser& operator= (const CubePL1Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const unsigned char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if CUBEPLPARSERDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 505,     ///< Last index in yytable_.
      yynnts_ = 88,  ///< Number of nonterminal symbols.
      yyfinal_ = 75 ///< Termination state number.
    };


    // User arguments.
    class CubePL1ParseContext& parseContext;
    class CubePL1Scanner& CubePL1Lexer;

  };


} // cubeplparser
#line 1159 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp"




#endif // !YY_CUBEPLPARSER_CUBELIB_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBEPL_CUBEPL1PARSER_HPP_INCLUDED
