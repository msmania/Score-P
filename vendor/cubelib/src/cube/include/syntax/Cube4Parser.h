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
 ** \file ../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.hpp
 ** Define the cubeparser::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_CUBEPARSER_CUBELIB_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBE4PARSER_HPP_INCLUDED
# define YY_CUBEPARSER_CUBELIB_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBE4PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 18 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"

/*** C/C++ Declarations ***/

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"

#include "CubeRegion.h"

#include "CubeError.h"
#include "CubeServices.h"
#include "CubeError.h"
#include "CubeParseContext.h"
#include "CubeMetric.h"
#include "Cube.h"
#include "CubeCartesian.h"


#line 76 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.hpp"


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
#ifndef CUBEPARSERDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define CUBEPARSERDEBUG 1
#  else
#   define CUBEPARSERDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define CUBEPARSERDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined CUBEPARSERDEBUG */

namespace cubeparser {
#line 219 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.hpp"




  /// A Bison parser.
  class Cube4Parser
  {
  public:
#ifdef CUBEPARSERSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define CUBEPARSERSTYPE in C++, use %define api.value.type"
# endif
    typedef CUBEPARSERSTYPE value_type;
#else
    /// Symbol semantic values.
    union value_type
    {
#line 96 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"

#line 239 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.hpp"

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
        CUBEPARSEREMPTY = -2,
    END = 0,                       // "end of file"
    CUBEPARSERerror = 256,         // error
    CUBEPARSERUNDEF = 1001,        // "invalid token"
    FFALSE = 1002,                 // "false"
    TTRUE = 1003,                  // "true"
    ATTRIBUTE_VALUE = 1004,        // "attribute value"
    ERROR = 1005,                  // "error"
    ACUBEPL_AGGR_ATTR_PLUS = 1006, // "plus"
    ACUBEPL_AGGR_ATTR_MINUS = 1007, // "minus"
    ACUBEPL_AGGR_ATTR_AGGR = 1008, // "aggr"
    OPENTAG_RIGHT = 1009,          // ">"
    CLOSETAG_RIGHT = 1010,         // "/>"
    ATTR_OPEN = 1011,              // "<attr"
    DIM_OPEN = 1012,               // "<dim"
    XML_OPEN = 1013,               // "<?xml"
    XML_CLOSE = 1014,              // "?>"
    CUBE_OPEN4 = 1015,             // "<cube version=\"4.0\""
    CUBE_OPEN41 = 1016,            // "<cube version=\"4.1\""
    CUBE_OPEN42 = 1017,            // "<cube version=\"4.2\""
    CUBE_OPEN43 = 1018,            // "<cube version=\"4.3\""
    CUBE_OPEN44 = 1019,            // "<cube version=\"4.4\""
    CUBE_OPEN45 = 1020,            // "<cube version=\"4.5\""
    CUBE_OPEN47 = 1021,            // "<cube version=\"4.7\""
    CUBE_OPEN3 = 1022,             // "<cube version=\"3.0\""
    CUBE_OPEN = 1023,              // "<cube version=\""
    CUBE_OPEN_NOT_SUPPORTED = 1000, // CUBE_OPEN_NOT_SUPPORTED
    CUBE_CLOSE = 1024,             // "</cube>"
    METRIC_OPEN = 1025,            // "<metric"
    METRIC_CLOSE = 1026,           // "</metric>"
    EXPRESSION_OPEN = 1027,        // "<cubepl"
    EXPRESSION_CLOSE = 1028,       // "</cubepl>"
    EXPRESSION_INIT_OPEN = 1029,   // "<cubeplinit>"
    EXPRESSION_INIT_CLOSE = 1030,  // "</cubeplinit>"
    EXPRESSION_AGGR_OPEN = 1031,   // "<cubeplaggr"
    EXPRESSION_AGGR_CLOSE = 1032,  // "</cubeplaggr>"
    REGION_OPEN = 1033,            // "<region"
    REGION_CLOSE = 1034,           // "</region>"
    CNODE_OPEN = 1035,             // "<cnode"
    CNODE_CLOSE = 1036,            // "</cnode>"
    CNODE_PARAMETER_OPEN = 1037,   // "<parameter"
    SYSTEM_TREE_NODE_OPEN = 1038,  // "<systemtreenode"
    SYSTEM_TREE_NODE_CLOSE = 1039, // "</systemtreenode>"
    LOCATIONGROUP_OPEN = 1040,     // "<locationgroup"
    LOCATIONGROUP_CLOSE = 1041,    // "</locationgroup>"
    LOCATION_OPEN = 1042,          // "<location"
    LOCATION_CLOSE = 1043,         // "</location>"
    MACHINE_OPEN = 1044,           // "<machine"
    MACHINE_CLOSE = 1045,          // "</machine>"
    NODE_OPEN = 1046,              // "<node"
    NODE_CLOSE = 1047,             // "</node>"
    PROCESS_OPEN = 1048,           // "<process"
    PROCESS_CLOSE = 1049,          // "</process>"
    THREAD_OPEN = 1050,            // "<thread"
    THREAD_CLOSE = 1051,           // "</thread>"
    MATRIX_OPEN = 1052,            // "<matrix"
    MATRIX_CLOSE = 1053,           // "</matrix>"
    ROW_OPEN = 1054,               // "<row"
    ROW_CLOSE = 1055,              // "</row>"
    CART_OPEN = 1056,              // "<cart"
    CART_CLOSE = 1057,             // "</cart>"
    COORD_OPEN = 1058,             // "<coord"
    COORD_CLOSE = 1059,            // "</coord>"
    DOC_OPEN = 1060,               // "<doc>"
    DOC_CLOSE = 1061,              // "</doc>"
    MIRRORS_OPEN = 1062,           // "<mirrors>"
    MIRRORS_CLOSE = 1063,          // "</mirrors>"
    MURL_OPEN = 1064,              // "<murl>"
    MURL_CLOSE = 1065,             // "</murl>"
    METRICS_OPEN = 1066,           // "<metrics"
    METRICS_CLOSE = 1067,          // "</metrics>"
    DISP_NAME_OPEN = 1068,         // "<disp_name>"
    DISP_NAME_CLOSE = 1069,        // "</disp_name>"
    UNIQ_NAME_OPEN = 1070,         // "<uniq_name>"
    UNIQ_NAME_CLOSE = 1071,        // "</uniq_name>"
    DTYPE_OPEN = 1072,             // "<dtype>"
    DTYPE_CLOSE = 1073,            // "</dtype>"
    UOM_OPEN = 1074,               // "<uom>"
    UOM_CLOSE = 1075,              // "</uom>"
    VAL_OPEN = 1076,               // "<val>"
    VAL_CLOSE = 1077,              // "</val>"
    URL_OPEN = 1078,               // "<url>"
    URL_CLOSE = 1079,              // "</url>"
    DESCR_OPEN = 1080,             // "<descr>"
    DESCR_CLOSE = 1081,            // "</descr>"
    PARADIGM_OPEN = 1082,          // "<paradigm>"
    PARADIGM_CLOSE = 1083,         // "</paradigm>"
    ROLE_OPEN = 1084,              // "<role>"
    ROLE_CLOSE = 1085,             // "</role>"
    PROGRAM_OPEN = 1086,           // "<program"
    PROGRAM_CLOSE = 1087,          // "</program>"
    NAME_OPEN = 1088,              // "<name>"
    NAME_CLOSE = 1089,             // "</name>"
    MANGLED_NAME_OPEN = 1090,      // "<mangled_name>"
    MANGLED_NAME_CLOSE = 1091,     // "</mangled_name>"
    CLASS_OPEN = 1092,             // "<class>"
    CLASS_CLOSE = 1093,            // "</class>"
    TYPE_OPEN = 1094,              // "<type>"
    TYPE_CLOSE = 1095,             // "</type>"
    SYSTEM_OPEN = 1096,            // "<system"
    SYSTEM_CLOSE = 1097,           // "</system>"
    RANK_OPEN = 1098,              // "<rank>"
    RANK_CLOSE = 1099,             // "</rank>"
    TOPOLOGIES_OPEN = 1100,        // "<topologies>"
    TOPOLOGIES_CLOSE = 1101,       // "</topologies>"
    SEVERITY_OPEN = 1102,          // "<severity>"
    SEVERITY_CLOSE = 1103,         // "</severity>"
    ANAME_VERSION = 1104,          // "attribute name version"
    ANAME_ENCODING = 1105,         // "attribute name encoding"
    ANAME_KEY = 1106,              // "attribute name key"
    ANAME_PAR_TYPE = 1107,         // "attribute name partype"
    ANAME_PAR_KEY = 1108,          // "attribute name parkey"
    ANAME_PAR_VALUE = 1109,        // "attribute name parvalue"
    ANAME_NAME = 1110,             // "attribute name name"
    ANAME_TITLE = 1111,            // "attribute name title"
    ANAME_FILE = 1112,             // "attribute name file"
    ANAME_VALUE = 1113,            // "attribute name value"
    ANAME_ID = 1114,               // "attribute name id"
    ANAME_MOD = 1115,              // "attribute name mod"
    ANAME_BEGIN = 1116,            // "attribute name begin"
    ANAME_END = 1117,              // "attribute name end"
    ANAME_LINE = 1118,             // "attribute name line"
    ANAME_CALLEEID = 1119,         // "attribute name calleeid"
    ANAME_NDIMS = 1120,            // "attribute name ndims"
    ANAME_SIZE = 1121,             // "attribute name size"
    ANAME_PERIODIC = 1122,         // "attribute name periodic"
    ANAME_LOCATIONID = 1123,       // "attribute name locId"
    ANAME_LOCATIONGROUPID = 1124,  // "attribute name lgId"
    ANAME_STNODEID = 1125,         // "attribute name stnId"
    ANAME_THRDID = 1126,           // "attribute name thrdId"
    ANAME_PROCID = 1127,           // "attribute name procId"
    ANAME_NODEID = 1128,           // "attribute name nodeId"
    ANAME_MACHID = 1129,           // "attribute name machId"
    ANAME_METRICID = 1130,         // "attribute name metricId"
    ANAME_METRIC_TYPE = 1131,      // "attribute name type"
    ANAME_METRIC_VIZ_TYPE = 1132,  // "attribute name viztype"
    ANAME_METRIC_CONVERTIBLE = 1133, // "attribute name convertible"
    ANAME_METRIC_CACHEABLE = 1134, // "attribute name cacheable"
    ANAME_CNODEID = 1135,          // "attribute name cnodeId"
    ACUBEPL_ROWWISE = 1136,        // "attribute name rowwise"
    ACUBEPL_AGGR_ATTRIBUTE = 1137  // "attribute name cubeplaggrtype"
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
        YYNTOKENS = 140, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_FFALSE = 3,                            // "false"
        S_TTRUE = 4,                             // "true"
        S_ATTRIBUTE_VALUE = 5,                   // "attribute value"
        S_ERROR = 6,                             // "error"
        S_ACUBEPL_AGGR_ATTR_PLUS = 7,            // "plus"
        S_ACUBEPL_AGGR_ATTR_MINUS = 8,           // "minus"
        S_ACUBEPL_AGGR_ATTR_AGGR = 9,            // "aggr"
        S_OPENTAG_RIGHT = 10,                    // ">"
        S_CLOSETAG_RIGHT = 11,                   // "/>"
        S_ATTR_OPEN = 12,                        // "<attr"
        S_DIM_OPEN = 13,                         // "<dim"
        S_XML_OPEN = 14,                         // "<?xml"
        S_XML_CLOSE = 15,                        // "?>"
        S_CUBE_OPEN4 = 16,                       // "<cube version=\"4.0\""
        S_CUBE_OPEN41 = 17,                      // "<cube version=\"4.1\""
        S_CUBE_OPEN42 = 18,                      // "<cube version=\"4.2\""
        S_CUBE_OPEN43 = 19,                      // "<cube version=\"4.3\""
        S_CUBE_OPEN44 = 20,                      // "<cube version=\"4.4\""
        S_CUBE_OPEN45 = 21,                      // "<cube version=\"4.5\""
        S_CUBE_OPEN47 = 22,                      // "<cube version=\"4.7\""
        S_CUBE_OPEN3 = 23,                       // "<cube version=\"3.0\""
        S_CUBE_OPEN = 24,                        // "<cube version=\""
        S_CUBE_OPEN_NOT_SUPPORTED = 25,          // CUBE_OPEN_NOT_SUPPORTED
        S_CUBE_CLOSE = 26,                       // "</cube>"
        S_METRIC_OPEN = 27,                      // "<metric"
        S_METRIC_CLOSE = 28,                     // "</metric>"
        S_EXPRESSION_OPEN = 29,                  // "<cubepl"
        S_EXPRESSION_CLOSE = 30,                 // "</cubepl>"
        S_EXPRESSION_INIT_OPEN = 31,             // "<cubeplinit>"
        S_EXPRESSION_INIT_CLOSE = 32,            // "</cubeplinit>"
        S_EXPRESSION_AGGR_OPEN = 33,             // "<cubeplaggr"
        S_EXPRESSION_AGGR_CLOSE = 34,            // "</cubeplaggr>"
        S_REGION_OPEN = 35,                      // "<region"
        S_REGION_CLOSE = 36,                     // "</region>"
        S_CNODE_OPEN = 37,                       // "<cnode"
        S_CNODE_CLOSE = 38,                      // "</cnode>"
        S_CNODE_PARAMETER_OPEN = 39,             // "<parameter"
        S_SYSTEM_TREE_NODE_OPEN = 40,            // "<systemtreenode"
        S_SYSTEM_TREE_NODE_CLOSE = 41,           // "</systemtreenode>"
        S_LOCATIONGROUP_OPEN = 42,               // "<locationgroup"
        S_LOCATIONGROUP_CLOSE = 43,              // "</locationgroup>"
        S_LOCATION_OPEN = 44,                    // "<location"
        S_LOCATION_CLOSE = 45,                   // "</location>"
        S_MACHINE_OPEN = 46,                     // "<machine"
        S_MACHINE_CLOSE = 47,                    // "</machine>"
        S_NODE_OPEN = 48,                        // "<node"
        S_NODE_CLOSE = 49,                       // "</node>"
        S_PROCESS_OPEN = 50,                     // "<process"
        S_PROCESS_CLOSE = 51,                    // "</process>"
        S_THREAD_OPEN = 52,                      // "<thread"
        S_THREAD_CLOSE = 53,                     // "</thread>"
        S_MATRIX_OPEN = 54,                      // "<matrix"
        S_MATRIX_CLOSE = 55,                     // "</matrix>"
        S_ROW_OPEN = 56,                         // "<row"
        S_ROW_CLOSE = 57,                        // "</row>"
        S_CART_OPEN = 58,                        // "<cart"
        S_CART_CLOSE = 59,                       // "</cart>"
        S_COORD_OPEN = 60,                       // "<coord"
        S_COORD_CLOSE = 61,                      // "</coord>"
        S_DOC_OPEN = 62,                         // "<doc>"
        S_DOC_CLOSE = 63,                        // "</doc>"
        S_MIRRORS_OPEN = 64,                     // "<mirrors>"
        S_MIRRORS_CLOSE = 65,                    // "</mirrors>"
        S_MURL_OPEN = 66,                        // "<murl>"
        S_MURL_CLOSE = 67,                       // "</murl>"
        S_METRICS_OPEN = 68,                     // "<metrics"
        S_METRICS_CLOSE = 69,                    // "</metrics>"
        S_DISP_NAME_OPEN = 70,                   // "<disp_name>"
        S_DISP_NAME_CLOSE = 71,                  // "</disp_name>"
        S_UNIQ_NAME_OPEN = 72,                   // "<uniq_name>"
        S_UNIQ_NAME_CLOSE = 73,                  // "</uniq_name>"
        S_DTYPE_OPEN = 74,                       // "<dtype>"
        S_DTYPE_CLOSE = 75,                      // "</dtype>"
        S_UOM_OPEN = 76,                         // "<uom>"
        S_UOM_CLOSE = 77,                        // "</uom>"
        S_VAL_OPEN = 78,                         // "<val>"
        S_VAL_CLOSE = 79,                        // "</val>"
        S_URL_OPEN = 80,                         // "<url>"
        S_URL_CLOSE = 81,                        // "</url>"
        S_DESCR_OPEN = 82,                       // "<descr>"
        S_DESCR_CLOSE = 83,                      // "</descr>"
        S_PARADIGM_OPEN = 84,                    // "<paradigm>"
        S_PARADIGM_CLOSE = 85,                   // "</paradigm>"
        S_ROLE_OPEN = 86,                        // "<role>"
        S_ROLE_CLOSE = 87,                       // "</role>"
        S_PROGRAM_OPEN = 88,                     // "<program"
        S_PROGRAM_CLOSE = 89,                    // "</program>"
        S_NAME_OPEN = 90,                        // "<name>"
        S_NAME_CLOSE = 91,                       // "</name>"
        S_MANGLED_NAME_OPEN = 92,                // "<mangled_name>"
        S_MANGLED_NAME_CLOSE = 93,               // "</mangled_name>"
        S_CLASS_OPEN = 94,                       // "<class>"
        S_CLASS_CLOSE = 95,                      // "</class>"
        S_TYPE_OPEN = 96,                        // "<type>"
        S_TYPE_CLOSE = 97,                       // "</type>"
        S_SYSTEM_OPEN = 98,                      // "<system"
        S_SYSTEM_CLOSE = 99,                     // "</system>"
        S_RANK_OPEN = 100,                       // "<rank>"
        S_RANK_CLOSE = 101,                      // "</rank>"
        S_TOPOLOGIES_OPEN = 102,                 // "<topologies>"
        S_TOPOLOGIES_CLOSE = 103,                // "</topologies>"
        S_SEVERITY_OPEN = 104,                   // "<severity>"
        S_SEVERITY_CLOSE = 105,                  // "</severity>"
        S_ANAME_VERSION = 106,                   // "attribute name version"
        S_ANAME_ENCODING = 107,                  // "attribute name encoding"
        S_ANAME_KEY = 108,                       // "attribute name key"
        S_ANAME_PAR_TYPE = 109,                  // "attribute name partype"
        S_ANAME_PAR_KEY = 110,                   // "attribute name parkey"
        S_ANAME_PAR_VALUE = 111,                 // "attribute name parvalue"
        S_ANAME_NAME = 112,                      // "attribute name name"
        S_ANAME_TITLE = 113,                     // "attribute name title"
        S_ANAME_FILE = 114,                      // "attribute name file"
        S_ANAME_VALUE = 115,                     // "attribute name value"
        S_ANAME_ID = 116,                        // "attribute name id"
        S_ANAME_MOD = 117,                       // "attribute name mod"
        S_ANAME_BEGIN = 118,                     // "attribute name begin"
        S_ANAME_END = 119,                       // "attribute name end"
        S_ANAME_LINE = 120,                      // "attribute name line"
        S_ANAME_CALLEEID = 121,                  // "attribute name calleeid"
        S_ANAME_NDIMS = 122,                     // "attribute name ndims"
        S_ANAME_SIZE = 123,                      // "attribute name size"
        S_ANAME_PERIODIC = 124,                  // "attribute name periodic"
        S_ANAME_LOCATIONID = 125,                // "attribute name locId"
        S_ANAME_LOCATIONGROUPID = 126,           // "attribute name lgId"
        S_ANAME_STNODEID = 127,                  // "attribute name stnId"
        S_ANAME_THRDID = 128,                    // "attribute name thrdId"
        S_ANAME_PROCID = 129,                    // "attribute name procId"
        S_ANAME_NODEID = 130,                    // "attribute name nodeId"
        S_ANAME_MACHID = 131,                    // "attribute name machId"
        S_ANAME_METRICID = 132,                  // "attribute name metricId"
        S_ANAME_METRIC_TYPE = 133,               // "attribute name type"
        S_ANAME_METRIC_VIZ_TYPE = 134,           // "attribute name viztype"
        S_ANAME_METRIC_CONVERTIBLE = 135,        // "attribute name convertible"
        S_ANAME_METRIC_CACHEABLE = 136,          // "attribute name cacheable"
        S_ANAME_CNODEID = 137,                   // "attribute name cnodeId"
        S_ACUBEPL_ROWWISE = 138,                 // "attribute name rowwise"
        S_ACUBEPL_AGGR_ATTRIBUTE = 139,          // "attribute name cubeplaggrtype"
        S_YYACCEPT = 140,                        // $accept
        S_version_attr = 141,                    // version_attr
        S_encoding_attr = 142,                   // encoding_attr
        S_key_attr = 143,                        // key_attr
        S_value_attr = 144,                      // value_attr
        S_mod_attr = 145,                        // mod_attr
        S_metric_type_attr = 146,                // metric_type_attr
        S_metric_viz_type_attr = 147,            // metric_viz_type_attr
        S_metric_convertible_attr = 148,         // metric_convertible_attr
        S_metric_cacheable_attr = 149,           // metric_cacheable_attr
        S_cnode_par_type_attr = 150,             // cnode_par_type_attr
        S_cnode_par_key_attr = 151,              // cnode_par_key_attr
        S_cnode_par_value_attr = 152,            // cnode_par_value_attr
        S_cart_name_attr = 153,                  // cart_name_attr
        S_dim_name_attr = 154,                   // dim_name_attr
        S_metrics_title_attr = 155,              // metrics_title_attr
        S_calltree_title_attr = 156,             // calltree_title_attr
        S_systemtree_title_attr = 157,           // systemtree_title_attr
        S_expression_attr = 158,                 // expression_attr
        S_expression_aggr_attr = 159,            // expression_aggr_attr
        S_expression_aggr_attr_plus = 160,       // expression_aggr_attr_plus
        S_expression_aggr_attr_minus = 161,      // expression_aggr_attr_minus
        S_expression_aggr_attr_aggr = 162,       // expression_aggr_attr_aggr
        S_id_attr = 163,                         // id_attr
        S_calleeid_attr = 164,                   // calleeid_attr
        S_locid_attr = 165,                      // locid_attr
        S_lgid_attr = 166,                       // lgid_attr
        S_stnid_attr = 167,                      // stnid_attr
        S_thrdid_attr = 168,                     // thrdid_attr
        S_procid_attr = 169,                     // procid_attr
        S_nodeid_attr = 170,                     // nodeid_attr
        S_machid_attr = 171,                     // machid_attr
        S_metricid_attr = 172,                   // metricid_attr
        S_cnodeid_attr = 173,                    // cnodeid_attr
        S_begin_attr = 174,                      // begin_attr
        S_end_attr = 175,                        // end_attr
        S_line_attr = 176,                       // line_attr
        S_ndims_attr = 177,                      // ndims_attr
        S_size_attr = 178,                       // size_attr
        S_periodic_attr = 179,                   // periodic_attr
        S_murl_tag = 180,                        // murl_tag
        S_disp_name_tag = 181,                   // disp_name_tag
        S_uniq_name_tag = 182,                   // uniq_name_tag
        S_dtype_tag = 183,                       // dtype_tag
        S_uom_tag = 184,                         // uom_tag
        S_val_tag = 185,                         // val_tag
        S_url_tag = 186,                         // url_tag
        S_descr_tag_opt = 187,                   // descr_tag_opt
        S_expression_tag = 188,                  // expression_tag
        S_expression_init_tag = 189,             // expression_init_tag
        S_expression_aggr_tag = 190,             // expression_aggr_tag
        S_descr_tag = 191,                       // descr_tag
        S_name_tag = 192,                        // name_tag
        S_mangled_name_tag = 193,                // mangled_name_tag
        S_paradigm_tag = 194,                    // paradigm_tag
        S_role_tag = 195,                        // role_tag
        S_class_tag = 196,                       // class_tag
        S_type_tag = 197,                        // type_tag
        S_rank_tag = 198,                        // rank_tag
        S_parameter_tag = 199,                   // parameter_tag
        S_document = 200,                        // document
        S_xml_tag = 201,                         // xml_tag
        S_xml_attributes = 202,                  // xml_attributes
        S_xml_attribute = 203,                   // xml_attribute
        S_cube_tag = 204,                        // cube_tag
        S_cube_begin = 205,                      // cube_begin
        S_cube_content = 206,                    // cube_content
        S_attr_tags = 207,                       // attr_tags
        S_attr_tag = 208,                        // attr_tag
        S_attr_attributes = 209,                 // attr_attributes
        S_attr_attribute = 210,                  // attr_attribute
        S_doc_tag = 211,                         // doc_tag
        S_mirrors_tag_attr = 212,                // mirrors_tag_attr
        S_mirrors_tag = 213,                     // mirrors_tag
        S_murl_tags_attr = 214,                  // murl_tags_attr
        S_murl_tags = 215,                       // murl_tags
        S_metrics_tag = 216,                     // metrics_tag
        S_217_1 = 217,                           // $@1
        S_metric_tag = 218,                      // metric_tag
        S_metric_begin = 219,                    // metric_begin
        S_id_attrs = 220,                        // id_attrs
        S_metric_attrs = 221,                    // metric_attrs
        S_metric_attr = 222,                     // metric_attr
        S_tags_of_metric_attr = 223,             // tags_of_metric_attr
        S_tags_of_metric = 224,                  // tags_of_metric
        S_tag_of_metric = 225,                   // tag_of_metric
        S_generic_attr_tag = 226,                // generic_attr_tag
        S_metric_end = 227,                      // metric_end
        S_program_tag = 228,                     // program_tag
        S_229_2 = 229,                           // $@2
        S_230_3 = 230,                           // $@3
        S_231_4 = 231,                           // $@4
        S_region_tags = 232,                     // region_tags
        S_region_tag = 233,                      // region_tag
        S_tags_of_region_attr = 234,             // tags_of_region_attr
        S_tags_of_region = 235,                  // tags_of_region
        S_tag_of_region = 236,                   // tag_of_region
        S_region_attributes = 237,               // region_attributes
        S_region_attribute = 238,                // region_attribute
        S_cnode_tag = 239,                       // cnode_tag
        S_cnode_begin = 240,                     // cnode_begin
        S_cnode_parameters = 241,                // cnode_parameters
        S_cnode_attr_tags = 242,                 // cnode_attr_tags
        S_cnode_attribute = 243,                 // cnode_attribute
        S_cnode_attributes = 244,                // cnode_attributes
        S_system_tag = 245,                      // system_tag
        S_246_5 = 246,                           // $@5
        S_systemtree_tags = 247,                 // systemtree_tags
        S_flexsystemtree_tags = 248,             // flexsystemtree_tags
        S_systemtree_tag = 249,                  // systemtree_tag
        S_250_6 = 250,                           // $@6
        S_251_7 = 251,                           // $@7
        S_systree_attr_tags = 252,               // systree_attr_tags
        S_systemtree_sub_tags = 253,             // systemtree_sub_tags
        S_location_group_tags = 254,             // location_group_tags
        S_location_group_tag = 255,              // location_group_tag
        S_256_8 = 256,                           // $@8
        S_loc_tags = 257,                        // loc_tags
        S_loc_tag = 258,                         // loc_tag
        S_lg_attr_tags = 259,                    // lg_attr_tags
        S_location_tags = 260,                   // location_tags
        S_location_tag = 261,                    // location_tag
        S_machine_tags = 262,                    // machine_tags
        S_machine_tag = 263,                     // machine_tag
        S_264_9 = 264,                           // $@9
        S_node_tags = 265,                       // node_tags
        S_node_tag = 266,                        // node_tag
        S_267_10 = 267,                          // $@10
        S_process_tags = 268,                    // process_tags
        S_process_tag = 269,                     // process_tag
        S_270_11 = 270,                          // $@11
        S_tags_of_process = 271,                 // tags_of_process
        S_tag_of_process = 272,                  // tag_of_process
        S_thread_tags = 273,                     // thread_tags
        S_thread_tag = 274,                      // thread_tag
        S_topologies_tag_attr = 275,             // topologies_tag_attr
        S_topologies_tag = 276,                  // topologies_tag
        S_277_12 = 277,                          // $@12
        S_cart_tags_attr = 278,                  // cart_tags_attr
        S_cart_tags = 279,                       // cart_tags
        S_cart_attrs = 280,                      // cart_attrs
        S_cart_tag = 281,                        // cart_tag
        S_282_13 = 282,                          // $@13
        S_cart_open = 283,                       // cart_open
        S_dim_tags = 284,                        // dim_tags
        S_dim_tag = 285,                         // dim_tag
        S_dim_attributes = 286,                  // dim_attributes
        S_dim_attribute = 287,                   // dim_attribute
        S_coord_tags = 288,                      // coord_tags
        S_coord_tag = 289,                       // coord_tag
        S_coord_tag_loc = 290,                   // coord_tag_loc
        S_coord_tag_lg = 291,                    // coord_tag_lg
        S_coord_tag_stn = 292,                   // coord_tag_stn
        S_coord_tag_thrd = 293,                  // coord_tag_thrd
        S_coord_tag_proc = 294,                  // coord_tag_proc
        S_coord_tag_node = 295,                  // coord_tag_node
        S_coord_tag_mach = 296,                  // coord_tag_mach
        S_severity_tag = 297,                    // severity_tag
        S_severity_part = 298,                   // severity_part
        S_299_14 = 299,                          // $@14
        S_matrix_tags = 300,                     // matrix_tags
        S_matrix_tag = 301,                      // matrix_tag
        S_302_15 = 302,                          // $@15
        S_row_tags_attr = 303,                   // row_tags_attr
        S_row_tags = 304,                        // row_tags
        S_row_tag = 305,                         // row_tag
        S_306_16 = 306                           // $@16
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
        return Cube4Parser::symbol_name (this->kind ());
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
    Cube4Parser (class Driver& driver_yyarg, class ParseContext& parseContext_yyarg, class Cube4Scanner& Cube4Lexer_yyarg, class cube::Cube& cube_yyarg, bool& clustering_on_yyarg);
    virtual ~Cube4Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Cube4Parser (const Cube4Parser&) = delete;
    /// Non copyable.
    Cube4Parser& operator= (const Cube4Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if CUBEPARSERDEBUG
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
      context (const Cube4Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Cube4Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Cube4Parser (const Cube4Parser&);
    /// Non copyable.
    Cube4Parser& operator= (const Cube4Parser&);
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
    static const short yydefact_[];

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
    static const short yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const short yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if CUBEPARSERDEBUG
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
      yylast_ = 350,     ///< Last index in yytable_.
      yynnts_ = 167,  ///< Number of nonterminal symbols.
      yyfinal_ = 10 ///< Termination state number.
    };


    // User arguments.
    class Driver& driver;
    class ParseContext& parseContext;
    class Cube4Scanner& Cube4Lexer;
    class cube::Cube& cube;
    bool& clustering_on;

  };


} // cubeparser
#line 1266 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.hpp"




#endif // !YY_CUBEPARSER_CUBELIB_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBE4PARSER_HPP_INCLUDED
