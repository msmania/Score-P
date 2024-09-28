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
 ** \file ../../cubelib/build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.hh
 ** Define the remapparser::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_REMAPPARSER_CUBELIB_BUILD_FRONTEND_SRC_TOOLS_TOOLS_0031_REMAP2_REMAPPARSER_HH_INCLUDED
# define YY_REMAPPARSER_CUBELIB_BUILD_FRONTEND_SRC_TOOLS_TOOLS_0031_REMAP2_REMAPPARSER_HH_INCLUDED
// "%code requires" blocks.
#line 18 "../../cubelib/build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"

/*** C/C++ Declarations ***/
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubeServices.h"
#include "ReMapParseContext.h"
#include "CubeMetric.h"
#include "Cube.h"
#include "CubeCartesian.h"


#line 65 "../../cubelib/build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.hh"


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
#ifndef REMAPPARSERDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define REMAPPARSERDEBUG 1
#  else
#   define REMAPPARSERDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define REMAPPARSERDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined REMAPPARSERDEBUG */

namespace remapparser {
#line 208 "../../cubelib/build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.hh"




  /// A Bison parser.
  class ReMapParser
  {
  public:
#ifdef REMAPPARSERSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define REMAPPARSERSTYPE in C++, use %define api.value.type"
# endif
    typedef REMAPPARSERSTYPE value_type;
#else
    /// Symbol semantic values.
    union value_type
    {
#line 85 "../../cubelib/build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"

#line 228 "../../cubelib/build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.hh"

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
        REMAPPARSEREMPTY = -2,
    END = 0,                       // "end of file"
    REMAPPARSERerror = 256,        // error
    REMAPPARSERUNDEF = 257,        // "invalid token"
    FFALSE = 258,                  // "false"
    TTRUE = 259,                   // "true"
    ATTRIBUTE_VALUE = 260,         // "attribute value"
    ERROR = 261,                   // "error"
    ACUBEPL_AGGR_ATTR_PLUS = 262,  // "plus"
    ACUBEPL_AGGR_ATTR_MINUS = 263, // "minus"
    ACUBEPL_AGGR_ATTR_AGGR = 264,  // "aggr"
    OPENTAG_RIGHT = 265,           // ">"
    CLOSETAG_RIGHT = 266,          // "/>"
    METRIC_OPEN = 267,             // "<metric"
    METRIC_CLOSE = 268,            // "</metric>"
    EXPRESSION_OPEN = 269,         // "<cubepl"
    EXPRESSION_CLOSE = 270,        // "</cubepl>"
    EXPRESSION_INIT_OPEN = 271,    // "<cubeplinit>"
    EXPRESSION_INIT_CLOSE = 272,   // "</cubeplinit>"
    EXPRESSION_AGGR_OPEN = 273,    // "<cubeplaggr"
    EXPRESSION_AGGR_CLOSE = 274,   // "</cubeplaggr>"
    METRICS_OPEN = 275,            // "<metrics"
    METRICS_CLOSE = 276,           // "</metrics>"
    DISP_NAME_OPEN = 277,          // "<disp_name>"
    DISP_NAME_CLOSE = 278,         // "</disp_name>"
    UNIQ_NAME_OPEN = 279,          // "<uniq_name>"
    UNIQ_NAME_CLOSE = 280,         // "</uniq_name>"
    DTYPE_OPEN = 281,              // "<dtype>"
    DTYPE_CLOSE = 282,             // "</dtype>"
    UOM_OPEN = 283,                // "<uom>"
    UOM_CLOSE = 284,               // "</uom>"
    VAL_OPEN = 285,                // "<val>"
    VAL_CLOSE = 286,               // "</val>"
    URL_OPEN = 287,                // "<url>"
    URL_CLOSE = 288,               // "</url>"
    DESCR_OPEN = 289,              // "<descr>"
    DESCR_CLOSE = 290,             // "</descr>"
    PROGRAM_OPEN = 291,            // "<program"
    PROGRAM_CLOSE = 292,           // "</program>"
    NAME_OPEN = 293,               // "<name>"
    NAME_CLOSE = 294,              // "</name>"
    DOC_OPEN = 295,                // "<doc>"
    DOC_CLOSE = 296,               // "</doc>"
    MIRRORS_OPEN = 297,            // "<mirrors>"
    MIRRORS_CLOSE = 298,           // "</mirrors>"
    MURL_OPEN = 299,               // "<murl>"
    MURL_CLOSE = 300,              // "</murl>"
    ANAME_TITLE = 301,             // "attribute name title"
    ANAME_METRICID = 302,          // "attribute name metricId"
    ANAME_METRIC_TYPE = 303,       // "attribute name type"
    ANAME_METRIC_VIZ_TYPE = 304,   // "attribute name viztype"
    ANAME_METRIC_CONVERTIBLE = 305, // "attribute name convertible"
    ANAME_METRIC_CACHEABLE = 306,  // "attribute name cacheable"
    ACUBEPL_ROWWISE = 307,         // "attribute name rowwise"
    ACUBEPL_AGGR_ATTRIBUTE = 308   // "attribute name cubeplaggrtype"
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
        YYNTOKENS = 54, ///< Number of tokens.
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
        S_METRIC_OPEN = 12,                      // "<metric"
        S_METRIC_CLOSE = 13,                     // "</metric>"
        S_EXPRESSION_OPEN = 14,                  // "<cubepl"
        S_EXPRESSION_CLOSE = 15,                 // "</cubepl>"
        S_EXPRESSION_INIT_OPEN = 16,             // "<cubeplinit>"
        S_EXPRESSION_INIT_CLOSE = 17,            // "</cubeplinit>"
        S_EXPRESSION_AGGR_OPEN = 18,             // "<cubeplaggr"
        S_EXPRESSION_AGGR_CLOSE = 19,            // "</cubeplaggr>"
        S_METRICS_OPEN = 20,                     // "<metrics"
        S_METRICS_CLOSE = 21,                    // "</metrics>"
        S_DISP_NAME_OPEN = 22,                   // "<disp_name>"
        S_DISP_NAME_CLOSE = 23,                  // "</disp_name>"
        S_UNIQ_NAME_OPEN = 24,                   // "<uniq_name>"
        S_UNIQ_NAME_CLOSE = 25,                  // "</uniq_name>"
        S_DTYPE_OPEN = 26,                       // "<dtype>"
        S_DTYPE_CLOSE = 27,                      // "</dtype>"
        S_UOM_OPEN = 28,                         // "<uom>"
        S_UOM_CLOSE = 29,                        // "</uom>"
        S_VAL_OPEN = 30,                         // "<val>"
        S_VAL_CLOSE = 31,                        // "</val>"
        S_URL_OPEN = 32,                         // "<url>"
        S_URL_CLOSE = 33,                        // "</url>"
        S_DESCR_OPEN = 34,                       // "<descr>"
        S_DESCR_CLOSE = 35,                      // "</descr>"
        S_PROGRAM_OPEN = 36,                     // "<program"
        S_PROGRAM_CLOSE = 37,                    // "</program>"
        S_NAME_OPEN = 38,                        // "<name>"
        S_NAME_CLOSE = 39,                       // "</name>"
        S_DOC_OPEN = 40,                         // "<doc>"
        S_DOC_CLOSE = 41,                        // "</doc>"
        S_MIRRORS_OPEN = 42,                     // "<mirrors>"
        S_MIRRORS_CLOSE = 43,                    // "</mirrors>"
        S_MURL_OPEN = 44,                        // "<murl>"
        S_MURL_CLOSE = 45,                       // "</murl>"
        S_ANAME_TITLE = 46,                      // "attribute name title"
        S_ANAME_METRICID = 47,                   // "attribute name metricId"
        S_ANAME_METRIC_TYPE = 48,                // "attribute name type"
        S_ANAME_METRIC_VIZ_TYPE = 49,            // "attribute name viztype"
        S_ANAME_METRIC_CONVERTIBLE = 50,         // "attribute name convertible"
        S_ANAME_METRIC_CACHEABLE = 51,           // "attribute name cacheable"
        S_ACUBEPL_ROWWISE = 52,                  // "attribute name rowwise"
        S_ACUBEPL_AGGR_ATTRIBUTE = 53,           // "attribute name cubeplaggrtype"
        S_YYACCEPT = 54,                         // $accept
        S_metric_type_attr = 55,                 // metric_type_attr
        S_metric_viz_type_attr = 56,             // metric_viz_type_attr
        S_metric_convertible_attr = 57,          // metric_convertible_attr
        S_metric_cacheable_attr = 58,            // metric_cacheable_attr
        S_metrics_title_attr = 59,               // metrics_title_attr
        S_expression_attr = 60,                  // expression_attr
        S_expression_aggr_attr = 61,             // expression_aggr_attr
        S_expression_aggr_attr_plus = 62,        // expression_aggr_attr_plus
        S_expression_aggr_attr_minus = 63,       // expression_aggr_attr_minus
        S_expression_aggr_attr_aggr = 64,        // expression_aggr_attr_aggr
        S_murl_tag = 65,                         // murl_tag
        S_disp_name_tag = 66,                    // disp_name_tag
        S_uniq_name_tag = 67,                    // uniq_name_tag
        S_dtype_tag = 68,                        // dtype_tag
        S_uom_tag = 69,                          // uom_tag
        S_val_tag = 70,                          // val_tag
        S_url_tag = 71,                          // url_tag
        S_expression_tag = 72,                   // expression_tag
        S_expression_init_tag = 73,              // expression_init_tag
        S_expression_aggr_tag = 74,              // expression_aggr_tag
        S_descr_tag = 75,                        // descr_tag
        S_document = 76,                         // document
        S_doc_tag = 77,                          // doc_tag
        S_mirrors_tag_opt = 78,                  // mirrors_tag_opt
        S_mirrors_tag = 79,                      // mirrors_tag
        S_murl_tags_opt = 80,                    // murl_tags_opt
        S_murl_tags = 81,                        // murl_tags
        S_metrics_tag = 82,                      // metrics_tag
        S_metric_tag = 83,                       // metric_tag
        S_metric_begin = 84,                     // metric_begin
        S_metric_attrs = 85,                     // metric_attrs
        S_metric_attr = 86,                      // metric_attr
        S_tags_of_metric_opt = 87,               // tags_of_metric_opt
        S_tags_of_metric = 88,                   // tags_of_metric
        S_tag_of_metric = 89,                    // tag_of_metric
        S_metric_end = 90                        // metric_end
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
        return ReMapParser::symbol_name (this->kind ());
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
    ReMapParser (class ReMapDriver& driver_yyarg, class ReMapParseContext& parseContext_yyarg, class ReMapScanner& ReMapLexer_yyarg, class cube::Cube& cube_yyarg);
    virtual ~ReMapParser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    ReMapParser (const ReMapParser&) = delete;
    /// Non copyable.
    ReMapParser& operator= (const ReMapParser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if REMAPPARSERDEBUG
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
      context (const ReMapParser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const ReMapParser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    ReMapParser (const ReMapParser&);
    /// Non copyable.
    ReMapParser& operator= (const ReMapParser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef signed char state_type;

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

    static const signed char yypact_ninf_;
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
    static const signed char yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const signed char yytable_[];

    static const signed char yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if REMAPPARSERDEBUG
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
      yylast_ = 64,     ///< Last index in yytable_.
      yynnts_ = 37,  ///< Number of nonterminal symbols.
      yyfinal_ = 11 ///< Termination state number.
    };


    // User arguments.
    class ReMapDriver& driver;
    class ReMapParseContext& parseContext;
    class ReMapScanner& ReMapLexer;
    class cube::Cube& cube;

  };


} // remapparser
#line 952 "../../cubelib/build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.hh"




#endif // !YY_REMAPPARSER_CUBELIB_BUILD_FRONTEND_SRC_TOOLS_TOOLS_0031_REMAP2_REMAPPARSER_HH_INCLUDED
