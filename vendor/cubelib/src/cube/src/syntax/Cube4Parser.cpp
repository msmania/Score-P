// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   cubeparserlex



#include "Cube4Parser.h"

// Second part of user prologue.
#line 242 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"

#include <config.h>

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeRegion.h"

#include "CubeDriver.h"
#include "Cube4Scanner.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <string>


#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubeServices.h"
#include "CubeParseContext.h"
#include "CubeMetric.h"
#include "Cube.h"
#include "CubeCartesian.h"

using namespace std;

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex Cube4Lexer.lex

// Workaround for Sun Studio C++ compilers on Solaris
#if defined(__SVR4) &&  defined(__SUNPRO_CC)
  #include <ieeefp.h>

  #define isinf(x)  (fpclass(x) == FP_NINF || fpclass(x) == FP_PINF)
  #define isnan(x)  isnand(x)
#endif


cubeparser::Cube4Parser::location_type cubeparserloc;



#line 102 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"



#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if CUBEPARSERDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !CUBEPARSERDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !CUBEPARSERDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace cubeparser {
#line 195 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"

  /// Build a parser object.
  Cube4Parser::Cube4Parser (class Driver& driver_yyarg, class ParseContext& parseContext_yyarg, class Cube4Scanner& Cube4Lexer_yyarg, class cube::Cube& cube_yyarg, bool& clustering_on_yyarg)
#if CUBEPARSERDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg),
      parseContext (parseContext_yyarg),
      Cube4Lexer (Cube4Lexer_yyarg),
      cube (cube_yyarg),
      clustering_on (clustering_on_yyarg)
  {}

  Cube4Parser::~Cube4Parser ()
  {}

  Cube4Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Cube4Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Cube4Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Cube4Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}


  template <typename Base>
  Cube4Parser::symbol_kind_type
  Cube4Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Cube4Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Cube4Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  Cube4Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Cube4Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Cube4Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Cube4Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Cube4Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Cube4Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Cube4Parser::symbol_kind_type
  Cube4Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Cube4Parser::symbol_kind_type
  Cube4Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Cube4Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Cube4Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Cube4Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Cube4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Cube4Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Cube4Parser::symbol_kind_type
  Cube4Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Cube4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Cube4Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Cube4Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Cube4Parser::stack_symbol_type&
  Cube4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  Cube4Parser::stack_symbol_type&
  Cube4Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Cube4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if CUBEPARSERDEBUG
  template <typename Base>
  void
  Cube4Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Cube4Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Cube4Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Cube4Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if CUBEPARSERDEBUG
  std::ostream&
  Cube4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Cube4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Cube4Parser::debug_level_type
  Cube4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Cube4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // CUBEPARSERDEBUG

  Cube4Parser::state_type
  Cube4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Cube4Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Cube4Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Cube4Parser::operator() ()
  {
    return parse ();
  }

  int
  Cube4Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 77 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
    clustering_on = false;
}

#line 545 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // version_attr: "attribute name version" "attribute value"
#line 306 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                              {
        if (parseContext.versionSeen)
          error(cubeparserloc,"Multiple version attributes defines!");
        else parseContext.versionSeen = true;
        parseContext.version = parseContext.str.str();
}
#line 688 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 3: // encoding_attr: "attribute name encoding" "attribute value"
#line 313 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                               {
        if (parseContext.encodingSeen)
          error(cubeparserloc,"Multiple encoding attributes defines!");
        else parseContext.encodingSeen = true;
        parseContext.encoding = parseContext.str.str();
}
#line 699 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 4: // key_attr: "attribute name key" "attribute value"
#line 320 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                          {
        if (parseContext.keySeen)
          error(cubeparserloc,"Multiple key attributes defines!");
        else parseContext.keySeen = true;
        parseContext.key = parseContext.str.str();
}
#line 710 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 5: // value_attr: "attribute name value" "attribute value"
#line 327 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                            {
        if (parseContext.valueSeen)
          error(cubeparserloc,"Multiple value attributes defines!");
        else parseContext.valueSeen = true;
        parseContext.value = parseContext.str.str();
}
#line 721 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 6: // mod_attr: "attribute name mod" "attribute value"
#line 334 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                          {
        if (parseContext.modSeen)
          error(cubeparserloc,"Multiple module attributes defines!");
        else parseContext.modSeen = true;
        parseContext.mod = parseContext.str.str(); }
#line 731 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 7: // metric_type_attr: "attribute name type" "attribute value"
#line 341 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                  {
    if (parseContext.metricTypeSeen)
      error(cubeparserloc,"Multiple metric type attributes defines!");
    else parseContext.metricTypeSeen = true;
    parseContext.metricType = parseContext.str.str(); }
#line 741 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 8: // metric_viz_type_attr: "attribute name viztype" "attribute value"
#line 349 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                      {
    if (parseContext.metricVizTypeSeen)
      error(cubeparserloc,"Multiple metric visibilty type attributes defines!");
    else parseContext.metricVizTypeSeen = true;
    parseContext.metricVizType = parseContext.str.str(); }
#line 751 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 9: // metric_convertible_attr: "attribute name convertible" "true"
#line 357 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                               {
    if (parseContext.metricConvertibleSeen)
      error(cubeparserloc,"Multiple metric convertible type attributes defines!");
    else parseContext.metricConvertibleSeen = true;
    parseContext.metricConvertible = true; }
#line 761 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 10: // metric_convertible_attr: "attribute name convertible" "false"
#line 363 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                {
    if (parseContext.metricConvertibleSeen)
      error(cubeparserloc,"Multiple metric convertible type attributes defines!");
    else parseContext.metricConvertibleSeen = true;
    parseContext.metricConvertible = false; }
#line 771 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 11: // metric_cacheable_attr: "attribute name cacheable" "true"
#line 371 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                             {
    if (parseContext.metricCacheableSeen)
      error(cubeparserloc,"Multiple metric cacheable type attributes defines!");
    else parseContext.metricCacheableSeen = true;
    parseContext.metricCacheable = true; }
#line 781 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 12: // metric_cacheable_attr: "attribute name cacheable" "false"
#line 377 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                              {
    if (parseContext.metricCacheableSeen)
      error(cubeparserloc,"Multiple metric cacheable type attributes defines!");
    else parseContext.metricCacheableSeen = true;
    parseContext.metricCacheable = false; }
#line 791 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 13: // cnode_par_type_attr: "attribute name partype" "attribute value"
#line 387 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                               {
    if (parseContext.cnodeParTypeSeen)
      error(cubeparserloc,"Multiple cnode parameter type attributes defines!");
    else parseContext.cnodeParTypeSeen = true;
    parseContext.cnode_parameter_type = parseContext.str.str();
}
#line 802 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 14: // cnode_par_key_attr: "attribute name parkey" "attribute value"
#line 396 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                              {
    if (parseContext.cnodeParKeySeen)
      error(cubeparserloc,"Multiple cnode parameter keys defines!");
    else parseContext.cnodeParKeySeen = true;
    parseContext.cnode_parameter_key = parseContext.str.str();
}
#line 813 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 15: // cnode_par_value_attr: "attribute name parvalue" "attribute value"
#line 405 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                {
    if (parseContext.cnodeParValueSeen)
      error(cubeparserloc,"Multiple cnode parameter values defines!");
    else parseContext.cnodeParValueSeen = true;
    parseContext.cnode_parameter_value = parseContext.str.str();
}
#line 824 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 16: // cart_name_attr: "attribute name name" "attribute value"
#line 414 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                           {
    if (parseContext.cartNameSeen)
      error(cubeparserloc,"Multiple topology names  defines!");
    else parseContext.cartNameSeen = true;
    parseContext.cartName = parseContext.str.str();
}
#line 835 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 17: // dim_name_attr: "attribute name name" "attribute value"
#line 424 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                           {
        if (parseContext.dimNameSeen)
          error(cubeparserloc,"Multiple names for dimension attributes defines!");
        else parseContext.dimNameSeen = true;
        parseContext.dimNamesCount++;
        parseContext.dimName = cube::services::escapeFromXML(parseContext.str.str());
}
#line 847 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 19: // metrics_title_attr: "attribute name title" "attribute value"
#line 434 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                            {
    if (parseContext.metricsTitleSeen)
      error(cubeparserloc,"Multiple metrics titles defined!");
    else parseContext.metricsTitleSeen = true;
    parseContext.metricsTitle = parseContext.str.str();
}
#line 858 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 21: // calltree_title_attr: "attribute name title" "attribute value"
#line 443 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                            {
    if (parseContext.calltreeTitleSeen)
      error(cubeparserloc,"Multiple calltree titles defined!");
    else parseContext.calltreeTitleSeen = true;
    parseContext.calltreeTitle = parseContext.str.str();
}
#line 869 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 23: // systemtree_title_attr: "attribute name title" "attribute value"
#line 453 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                            {
    if (parseContext.systemtreeTitleSeen)
      error(cubeparserloc,"Multiple system tree titles defined!");
    else parseContext.systemtreeTitleSeen = true;
    parseContext.systemtreeTitle = parseContext.str.str();
}
#line 880 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 25: // expression_attr: "attribute name rowwise" "false"
#line 463 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                       {
    if (parseContext.cubeplTypeSeen)
      error(cubeparserloc,"Multiple cubepl type attributes defines!");
    else parseContext.cubeplTypeSeen = true;
    parseContext.rowwise = false;

}
#line 892 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 29: // expression_aggr_attr_plus: "attribute name cubeplaggrtype" "plus"
#line 482 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                              {
    if (parseContext.expressionAggrPlusSeen)
      error(cubeparserloc,"Multiple cubepl plus-aggregation attributes defines!");
    else parseContext.expressionAggrPlusSeen = true;
    parseContext.cubeplAggrType = ParseContext::CUBEPL_AGGR_PLUS;

}
#line 904 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 30: // expression_aggr_attr_minus: "attribute name cubeplaggrtype" "minus"
#line 492 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                               {
    if (parseContext.expressionAggrMinusSeen)
      error(cubeparserloc,"Multiple cubepl minus-aggregation attributes defines!");
    else parseContext.expressionAggrMinusSeen = true;
    parseContext.cubeplAggrType = ParseContext::CUBEPL_AGGR_MINUS;

}
#line 916 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 31: // expression_aggr_attr_aggr: "attribute name cubeplaggrtype" "aggr"
#line 503 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                              {
    if (parseContext.expressionAggrAggrSeen)
      error(cubeparserloc,"Multiple cubepl aggr-aggregation attributes defines!");
    else parseContext.expressionAggrAggrSeen = true;
    parseContext.cubeplAggrType = ParseContext::CUBEPL_AGGR_AGGR;

}
#line 928 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 32: // id_attr: "attribute name id" "attribute value"
#line 515 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                         {
        if (parseContext.idSeen)
          error(cubeparserloc,"Multiple id attributes defines!");
        else parseContext.idSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"Ids must be non-negative!");
        parseContext.id = (int)parseContext.longAttribute;
}
#line 940 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 33: // calleeid_attr: "attribute name calleeid" "attribute value"
#line 524 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                               {
        if (parseContext.calleeidSeen)
          error(cubeparserloc,"Multiple callee id attributes defines!");
        else parseContext.calleeidSeen = true;
        if (parseContext.longAttribute<0)
          error(cubeparserloc,"Callee ids of regions must be non-negative!");
        parseContext.calleeid = (int)parseContext.longAttribute;
}
#line 953 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 34: // locid_attr: "attribute name locId" "attribute value"
#line 536 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                 {
        if (parseContext.locidSeen)
          error(cubeparserloc,"Multiple location id attributes defines!");
        else parseContext.locidSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"Location ids must be non-negative!");
        parseContext.locid = (int)parseContext.longAttribute;
}
#line 965 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 35: // lgid_attr: "attribute name lgId" "attribute value"
#line 545 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                      {
        if (parseContext.lgidSeen)
          error(cubeparserloc,"Multiple location group id attributes defines!");
        else parseContext.lgidSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"Location group ids must be non-negative!");
        parseContext.lgid = (int)parseContext.longAttribute;
}
#line 977 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 36: // stnid_attr: "attribute name stnId" "attribute value"
#line 554 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                               {
        if (parseContext.stnidSeen)
          error(cubeparserloc,"Multiple system tree node id attributes defines!");
        else parseContext.stnidSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"System tree node ids must be non-negative!");
        parseContext.stnid = (int)parseContext.longAttribute;
}
#line 989 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 37: // thrdid_attr: "attribute name thrdId" "attribute value"
#line 565 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                             {
        if (parseContext.locidSeen)
          error(cubeparserloc,"Multiple thread id attributes defines!");
        else parseContext.locidSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"Thread ids must be non-negative!");
        parseContext.thrdid = (int)parseContext.longAttribute;
}
#line 1001 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 38: // procid_attr: "attribute name procId" "attribute value"
#line 574 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                             {
        if (parseContext.lgidSeen)
          error(cubeparserloc,"Multiple process id attributes defines!");
        else parseContext.lgidSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"Process ids must be non-negative!");
        parseContext.procid = (int)parseContext.longAttribute;
}
#line 1013 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 39: // nodeid_attr: "attribute name nodeId" "attribute value"
#line 583 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                             {
        if (parseContext.stnidSeen)
          error(cubeparserloc,"Multiple node id attributes defines!");
        else parseContext.stnidSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"Node ids must be non-negative!");
        parseContext.nodeid = (int)parseContext.longAttribute;
}
#line 1025 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 40: // machid_attr: "attribute name machId" "attribute value"
#line 592 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                             {
        if (parseContext.stnidSeen)
          error(cubeparserloc,"Multiple machine id attributes defines!");
        else parseContext.stnidSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"Machine ids must be non-negative!");
        parseContext.machid = (int)parseContext.longAttribute;
}
#line 1037 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 41: // metricid_attr: "attribute name metricId" "attribute value"
#line 604 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                               {
        if (parseContext.metricidSeen)
          error(cubeparserloc,"Multiple metric id attributes defines!");
        else parseContext.metricidSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"Metric ids must be non-negative!");
        parseContext.metricid = parseContext.longAttribute;
}
#line 1049 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 42: // cnodeid_attr: "attribute name cnodeId" "attribute value"
#line 613 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                              {
        if (parseContext.cnodeidSeen)
          error(cubeparserloc,"Multiple cnode id attributes defines!");
        else parseContext.cnodeidSeen = true;
        if (parseContext.longAttribute<0) error(cubeparserloc,"Cnode ids must be non-negative!");
        parseContext.cnodeid = (int)parseContext.longAttribute;
}
#line 1061 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 43: // begin_attr: "attribute name begin" "attribute value"
#line 624 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                            {
        if (parseContext.beginSeen)
          error(cubeparserloc,"Multiple begin attributes defines!");
        else parseContext.beginSeen = true;
        parseContext.beginln = parseContext.longAttribute; }
#line 1071 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 44: // end_attr: "attribute name end" "attribute value"
#line 632 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                          {
        if (parseContext.endSeen)
          error(cubeparserloc,"Multiple end attributes defines!");
        else parseContext.endSeen = true;
        parseContext.endln = parseContext.longAttribute; }
#line 1081 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 45: // line_attr: "attribute name line" "attribute value"
#line 640 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                           {
        if (parseContext.lineSeen)
          error(cubeparserloc,"Multiple line attributes defines!");
        else parseContext.lineSeen = true;
        parseContext.line = parseContext.longAttribute; }
#line 1091 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 46: // ndims_attr: "attribute name ndims" "attribute value"
#line 648 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                            {
        if (parseContext.ndimsSeen)
          error(cubeparserloc,"Multiple ndims attributes defines!");
        else parseContext.ndimsSeen = true;
        if (parseContext.longAttribute<=0)
           error(cubeparserloc,"Topology dimensions must be positive numbers!");
        parseContext.ndims = parseContext.longAttribute;
}
#line 1104 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 47: // size_attr: "attribute name size" "attribute value"
#line 658 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                           {
        if (parseContext.sizeSeen)
          error(cubeparserloc,"Multiple size attributes defines!");
        else parseContext.sizeSeen = true;
        if (parseContext.longAttribute<=0)
          error(cubeparserloc,"Dimension sizes must be positive numbers!");
        parseContext.dimVec.push_back(parseContext.longAttribute);
}
#line 1117 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 48: // periodic_attr: "attribute name periodic" "false"
#line 670 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                      {
        if (parseContext.periodicSeen)
          error(cubeparserloc,"Multiple periodic attributes defines!");
        else parseContext.periodicSeen = true;
        parseContext.periodicVec.push_back(false);
}
#line 1128 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 49: // periodic_attr: "attribute name periodic" "true"
#line 676 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                       {
        if (parseContext.periodicSeen)
          error(cubeparserloc,"Multiple periodic attributes defined!");
        else parseContext.periodicSeen = true;
        parseContext.periodicVec.push_back(true);
}
#line 1139 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 50: // murl_tag: "<murl>" "</murl>"
#line 687 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                     {
        if (parseContext.murlSeen)
          error(cubeparserloc,"Multiple murl tags defined!");
        else parseContext.murlSeen = true;
        parseContext.murl = parseContext.str.str(); }
#line 1149 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 51: // disp_name_tag: "<disp_name>" "</disp_name>"
#line 697 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                               {
        if (parseContext.dispnameSeen)
          error(cubeparserloc,"Multiple disp_name tags defined!");
        else parseContext.dispnameSeen = true;
        parseContext.disp_name = parseContext.str.str(); }
#line 1159 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 52: // uniq_name_tag: "<uniq_name>" "</uniq_name>"
#line 704 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                               {
        if (parseContext.uniqnameSeen)
          error(cubeparserloc,"Multiple uniq_name tags defined!");
        else parseContext.uniqnameSeen = true;
        parseContext.uniq_name = parseContext.str.str(); }
#line 1169 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 53: // dtype_tag: "<dtype>" "</dtype>"
#line 710 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                       {
        if (parseContext.dtypeSeen)
          error(cubeparserloc,"Multiple dtype tags defined!");
        else parseContext.dtypeSeen = true;
        parseContext.dtype = parseContext.str.str(); }
#line 1179 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 54: // uom_tag: "<uom>" "</uom>"
#line 717 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                   {
        if (parseContext.uomSeen)
          error(cubeparserloc,"Multiple uom tags defined!");
        else parseContext.uomSeen = true;
        parseContext.uom = parseContext.str.str(); }
#line 1189 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 55: // val_tag: "<val>" "</val>"
#line 724 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                   {
        if (parseContext.valSeen)
          error(cubeparserloc,"Multiple val tags defined!");
        else parseContext.valSeen = true;
        parseContext.val = parseContext.str.str(); }
#line 1199 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 56: // url_tag: "<url>" "</url>"
#line 731 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                   {
        if (parseContext.urlSeen)
          error(cubeparserloc,"Multiple url tags defined!");
        else parseContext.urlSeen = true;
        parseContext.url = parseContext.str.str(); }
#line 1209 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 59: // expression_tag: "<cubepl" expression_attr ">" "</cubepl>"
#line 743 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                                {
        if (parseContext.expressionSeen)
          error(cubeparserloc,"Multiple expressions defined!");
        else parseContext.expressionSeen = true;
        parseContext.expression = cube::services::escapeFromXML(parseContext.str.str());
        }
#line 1220 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 60: // expression_init_tag: "<cubeplinit>" "</cubeplinit>"
#line 751 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                            {
    if (parseContext.expressionInitSeen)
      error(cubeparserloc,"Multiple expression initializations defined!");
    else parseContext.expressionInitSeen = true;
    parseContext.expressionInit = cube::services::escapeFromXML(parseContext.str.str());
    }
#line 1231 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 61: // expression_aggr_tag: "<cubeplaggr" expression_aggr_attr ">" "</cubeplaggr>"
#line 759 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                                               {
        if ( parseContext.cubeplAggrType == ParseContext::CUBEPL_AGGR_PLUS)
            parseContext.expressionAggrPlus = cube::services::escapeFromXML(parseContext.str.str());
        else
        if ( parseContext.cubeplAggrType == ParseContext::CUBEPL_AGGR_MINUS)
            parseContext.expressionAggrMinus = cube::services::escapeFromXML(parseContext.str.str());
        else
        if ( parseContext.cubeplAggrType == ParseContext::CUBEPL_AGGR_AGGR)
            parseContext.expressionAggrAggr = cube::services::escapeFromXML(parseContext.str.str());
        }
#line 1246 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 62: // descr_tag: "<descr>" "</descr>"
#line 770 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                       {
        if (parseContext.descrSeen)
          error(cubeparserloc,"Multiple descr tags defined!");
        else parseContext.descrSeen = true;
        parseContext.descr = parseContext.str.str(); }
#line 1256 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 63: // name_tag: "<name>" "</name>"
#line 777 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                     {
        if (parseContext.nameSeen)
          error(cubeparserloc,"Multiple name tags defined!");
        else parseContext.nameSeen = true;
        parseContext.name = parseContext.str.str();
        parseContext.mangled_name = parseContext.name;
}
#line 1268 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 64: // mangled_name_tag: "<mangled_name>" "</mangled_name>"
#line 787 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                     {
        if (parseContext.mangledNameSeen)
          error(cubeparserloc,"Multiple mangled name tags defined!");
        else parseContext.mangledNameSeen = true;
        parseContext.mangled_name = parseContext.str.str(); }
#line 1278 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 65: // paradigm_tag: "<paradigm>" "</paradigm>"
#line 795 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                             {
    if (parseContext.paradigmSeen)
      error(cubeparserloc,"Multiple paradigm tags defined!");
    else parseContext.paradigmSeen = true;
    parseContext.paradigm = parseContext.str.str(); }
#line 1288 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 66: // role_tag: "<role>" "</role>"
#line 803 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                     {
    if (parseContext.roleSeen)
      error(cubeparserloc,"Multiple role tags defined!");
    else parseContext.roleSeen = true;
    parseContext.role = parseContext.str.str(); }
#line 1298 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 67: // class_tag: "<class>" "</class>"
#line 812 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                       {
        if (parseContext.classSeen)
          error(cubeparserloc,"Multiple class tags defined!");
        else parseContext.classSeen = true;
        parseContext.stn_class = parseContext.str.str(); }
#line 1308 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 68: // type_tag: "<type>" "</type>"
#line 821 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                     {
        if (parseContext.typeSeen)
          error(cubeparserloc,"Multiple type tags defined!");
        else parseContext.typeSeen = true;
        parseContext.type = parseContext.str.str(); }
#line 1318 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 69: // rank_tag: "<rank>" "</rank>"
#line 828 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                     {
        if (parseContext.rankSeen)
          error(cubeparserloc,"Multiple rank tags defined!");
        else parseContext.rankSeen = true;
        if (parseContext.longValues.size()==0)
          error(cubeparserloc,"No rank is given in a rank tag!");
        if (parseContext.longValues.size()>1)
          error(cubeparserloc,"Multiple ranks are given in a rank tag!");
        int rank = (int)parseContext.longValues[0];
        if (rank<0)
          error(cubeparserloc,"Ranks must be non-negative!");
        parseContext.rank = rank;
}
#line 1336 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 70: // parameter_tag: "<parameter" cnode_par_type_attr cnode_par_key_attr cnode_par_value_attr "/>"
#line 845 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                                                                  {
    unsigned nparameters = 0;
    if (parseContext.cnode_parameter_type == "numeric")
    {
        if (!parseContext.n_cnode_num_parameters.empty())
        {
            nparameters = parseContext.n_cnode_num_parameters.top();
            parseContext.n_cnode_num_parameters.pop();
        }
        nparameters++;
        parseContext.n_cnode_num_parameters.push(nparameters);
        std::pair<std::string, std::string > _key ;
        _key.first  =  cube::services::escapeFromXML(parseContext.cnode_parameter_key);
        _key.second =  cube::services::escapeFromXML(parseContext.cnode_parameter_value) ;
        parseContext.cnode_num_parameters.push( _key );

    }
    if (parseContext.cnode_parameter_type == "string")
    {
        if ( !parseContext.n_cnode_str_parameters.empty() )
        {
            nparameters = parseContext.n_cnode_str_parameters.top();
            parseContext.n_cnode_str_parameters.pop();
        }
        nparameters++;
        parseContext.n_cnode_str_parameters.push(nparameters);

        std::pair<std::string, std::string > _key ;
        _key.first  =  cube::services::escapeFromXML(parseContext.cnode_parameter_key);
        _key.second =  cube::services::escapeFromXML(parseContext.cnode_parameter_value) ;
        parseContext.cnode_str_parameters.push( _key );
    }
    parseContext.stringContent = false;
    parseContext.cnodeParTypeSeen= false;
    parseContext.cnodeParKeySeen= false;
    parseContext.cnodeParValueSeen= false;
}
#line 1378 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 72: // xml_tag: "<?xml" xml_attributes "?>"
#line 896 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                  {
        //check for attributes
        if (!parseContext.versionSeen)
           error(cubeparserloc,"Missing version attribute!");
        else parseContext.versionSeen = false;
        if (!parseContext.encodingSeen)
          error(cubeparserloc,"Missing encoding attribute!");
        else parseContext.encodingSeen = false;
        int valid = strcmp(parseContext.version.c_str(),"1.0");
        if (valid!=0) error(cubeparserloc,"XML version is expected to be 1.0!");
        valid = strcmp(parseContext.encoding.c_str(),"UTF-8");
        if (valid!=0) error(cubeparserloc,"XML encoding is expected to be UTF-8!");
        cube.get_operation_progress()->start_step(0., 1.);
}
#line 1397 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 77: // cube_tag: cube_begin cube_content "</cube>"
#line 926 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    cube.get_operation_progress()->finish_step("Finished parsing");
}
#line 1405 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 78: // cube_begin: "<cube version=\"4.0\""
#line 932 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
           {
        parseContext.cubeVersion = 4;
        cube.def_attr( "Cube anchor.xml syntax version", "4" );
}
#line 1414 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 79: // cube_begin: "<cube version=\"4.1\""
#line 936 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
              {
    parseContext.cubeVersion = 4.1;
    cube.def_attr( "Cube anchor.xml syntax version", "4.1" );
}
#line 1423 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 80: // cube_begin: "<cube version=\"4.2\""
#line 940 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
              {
    parseContext.cubeVersion = 4.2;
    cube.def_attr( "Cube anchor.xml syntax version", "4.2" );
}
#line 1432 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 81: // cube_begin: "<cube version=\"4.3\""
#line 944 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
              {
    parseContext.cubeVersion = 4.3;
    cube.def_attr( "Cube anchor.xml syntax version", "4.3" );
}
#line 1441 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 82: // cube_begin: "<cube version=\"4.4\""
#line 948 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
              {
    parseContext.cubeVersion = 4.4;
    cube.def_attr( "Cube anchor.xml syntax version", "4.4" );
}
#line 1450 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 83: // cube_begin: "<cube version=\"4.5\""
#line 952 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
              {
    parseContext.cubeVersion = 4.5;
    cube.def_attr( "Cube anchor.xml syntax version", "4.5" );
}
#line 1459 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 84: // cube_begin: "<cube version=\"4.7\""
#line 956 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
              {
    parseContext.cubeVersion = 4.7;
    cube.def_attr( "Cube anchor.xml syntax version", "4.7" );
}
#line 1468 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 85: // cube_begin: "<cube version=\"3.0\""
#line 960 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
             {
    parseContext.cubeVersion = 3;
    cube.def_attr( "Cube syntax version", "3" );
}
#line 1477 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 86: // cube_begin: "<cube version=\"" CUBE_OPEN_NOT_SUPPORTED
#line 964 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                    {
     throw cube::NotSupportedVersionError(parseContext.str.str());
}
#line 1485 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 93: // attr_tag: "<attr" attr_attributes "/>"
#line 984 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                         {
        //check for attributes
        if (!parseContext.keySeen)
          error(cubeparserloc,"Missing key attribute!");
        else parseContext.keySeen = false;
        if (!parseContext.valueSeen)
          error(cubeparserloc,"Missing value attribute!");
        else parseContext.valueSeen = false;
        string attrkey = cube::services::escapeFromXML(parseContext.key);
        string attrvalue = cube::services::escapeFromXML(parseContext.value);
        cube.def_attr( attrkey, attrvalue );

        if (attrkey.compare(CUBEPL_VERSION_KEY) == 0)
        {
        cube.select_cubepl_engine( attrvalue );
        }
}
#line 1507 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 104: // murl_tags: murl_tag
#line 1031 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
         {parseContext.murlSeen = false; cube.def_mirror(cube::services::escapeFromXML(parseContext.murl));}
#line 1513 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 105: // murl_tags: murl_tags murl_tag
#line 1032 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                     {parseContext.murlSeen = false; cube.def_mirror(cube::services::escapeFromXML(parseContext.murl));}
#line 1519 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 106: // $@1: %empty
#line 1041 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
  clustering_on = false;
  cube.get_operation_progress()->progress_step("Parse metrics");
  if ( cube.is_clustering_on() )
  {
    cube.get_operation_progress()->start_step(0., 1.);
    cube.get_operation_progress()->progress_step("Start parsing clusters");
    clustering_on = true;
    std::map<uint64_t, std::map<uint64_t, uint64_t> > clusters_counter;

    const std::map<std::string, std::string> & attrs = cube.get_attrs();
    std::map<std::string, std::string>::const_iterator _iter = attrs.find("CLUSTERING");
    if ( _iter  != attrs.end() && (*_iter).second.compare("ON") == 0)
    {
      std::map<std::string, std::string>::const_iterator _iter = attrs.find("CLUSTER ITERATION COUNT");
      if (_iter != attrs.end() )
      {
        parseContext.number_of_iterations = cube::services::string2int((*_iter).second);
        std::map<std::string, std::string>::const_iterator _iter = attrs.find("CLUSTER ROOT CNODE ID");
        if (_iter != attrs.end() )
        {
            parseContext.clustering_root_cnode_id = cube::services::string2int((*_iter).second);
            for (uint64_t iteration = 0; iteration < parseContext.number_of_iterations; iteration ++)
            {
                cube.get_operation_progress()->progress_step(iteration/parseContext.number_of_iterations, "Reading clusters mapping");
                std::string iteration_number = cube::services::numeric2string(iteration);
                std::string key = "CLUSTER MAPPING " + iteration_number;
                std::map<std::string, std::string>::const_iterator _iter = attrs.find(key);
                if (_iter != attrs.end())
                {
                    std::string value = (*_iter).second;
                    uint64_t iteration_key = iteration;
                    std::vector<uint64_t> _cluster_id = cube::services::parse_clustering_value( value );
                    std::vector<uint64_t> _collapsed_cluster_id = cube::services::sort_and_collapse_clusters( _cluster_id );
                    parseContext.cluster_mapping[ iteration_key] = _cluster_id;
                    parseContext.cluster_positions[ iteration_key ] = cube::services::get_cluster_positions( _cluster_id );
                    parseContext.collapsed_cluster_mapping[ iteration_key ] = _collapsed_cluster_id;
                    uint64_t process_rank = 0;
                    for (std::vector<uint64_t>::iterator iter = _cluster_id.begin(); iter!= _cluster_id.end(); ++iter, ++process_rank)
                    {
                        uint64_t _id = *iter;
                        clusters_counter[_id][process_rank]++;
                    }
                }
                else
                {
                cerr << "Clustering mapping is not continuous." << endl;
                clustering_on = false;
                cube.enable_clustering(false);
                break;
                }
            }
                cube.set_clusters_count(clusters_counter);
            }
            else
            {
                cerr << "Cannot find cluster root cnode" << endl;
                clustering_on = false;
                cube.enable_clustering(false);
            }
        }
        else
        {
            cerr << "Cannot find number of clustered iterations" << endl;
            clustering_on = false;
            cube.enable_clustering(false);
        }
        cube.get_operation_progress()->finish_step("Parsing cluster mappings finished");
    }
    else
    {
        clustering_on = false;
        cube.enable_clustering(false);
    }

  }
}
#line 1601 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 107: // metrics_tag: "<metrics" $@1 metrics_title_attr ">" metric_tag "</metrics>"
#line 1119 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    if (parseContext.metricsTitle != "")
        cube.set_metrics_title(cube::services::escapeFromXML(parseContext.metricsTitle));
    cube.get_operation_progress()->progress_step(0.2, "Finished parsing metrics");
}
#line 1611 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 111: // metric_begin: "<metric" id_attrs metric_attrs ">" tags_of_metric_attr
#line 1136 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                                    {
        //check for attributes
            parseContext.idSeen = false;
        //check for tags
        if (parseContext.metricTypeSeen) parseContext.metricTypeSeen = false;
        else parseContext.metricType = "";
        if (parseContext.metricVizTypeSeen) parseContext.metricVizTypeSeen = false;
        else parseContext.metricVizType = "";
        if (parseContext.dispnameSeen) parseContext.dispnameSeen = false;
        else parseContext.disp_name = "";
        if (parseContext.uniqnameSeen) parseContext.uniqnameSeen = false;
        else parseContext.uniq_name = "";
        if (parseContext.dtypeSeen) parseContext.dtypeSeen = false;
        else parseContext.dtype = "";
        if (parseContext.uomSeen) parseContext.uomSeen = false;
        else parseContext.uom = "";
        if (parseContext.valSeen) parseContext.valSeen = false;
        else parseContext.val = "";
        if (parseContext.urlSeen) parseContext.urlSeen = false;
        else parseContext.url = "";
        if (parseContext.descrSeen) parseContext.descrSeen = false;
        else parseContext.descr = "";
        if (parseContext.expressionSeen) parseContext.expressionSeen = false;
        else parseContext.expression = "";
        if (parseContext.expressionInitSeen) parseContext.expressionInitSeen = false;
        else parseContext.expressionInit = "";
        if (parseContext.expressionAggrPlusSeen) parseContext.expressionAggrPlusSeen = false;
        else parseContext.expressionAggrPlus = "";
        if (parseContext.expressionAggrMinusSeen) parseContext.expressionAggrMinusSeen = false;
        else parseContext.expressionAggrMinus = "";
        if (parseContext.expressionAggrAggrSeen) parseContext.expressionAggrAggrSeen = false;
        else parseContext.expressionAggrAggr = "";
        if (parseContext.metricConvertibleSeen) parseContext.metricConvertibleSeen = false;
        else parseContext.metricConvertible = true;
        if (parseContext.metricCacheableSeen) parseContext.metricCacheableSeen = false;
        else parseContext.metricCacheable = true;
        if (parseContext.cubeplTypeSeen) parseContext.cubeplTypeSeen = false;
        else parseContext.rowwise = true;

        while ((int)parseContext.metricVec.size()<=parseContext.id)
                parseContext.metricVec.push_back(NULL);
        if (parseContext.metricVec[parseContext.id]!=NULL)
          error(cubeparserloc,"Re-declared metric!");

            parseContext.currentMetric =
                    cube.def_met(
                            cube::services::escapeFromXML(parseContext.disp_name),
                            cube::services::escapeFromXML(parseContext.uniq_name),
                            cube::services::escapeFromXML(parseContext.dtype),
                            cube::services::escapeFromXML(parseContext.uom),
                            cube::services::escapeFromXML(parseContext.val),
                            cube::services::escapeFromXML(parseContext.url),
                            cube::services::escapeFromXML(parseContext.descr),
                            parseContext.currentMetric,
                            cube::Metric::get_type_of_metric(parseContext.metricType),
                            cube::services::escapeFromXML(parseContext.expression),
                            cube::services::escapeFromXML(parseContext.expressionInit),
                            cube::services::escapeFromXML(parseContext.expressionAggrPlus),
                            cube::services::escapeFromXML(parseContext.expressionAggrMinus),
                            cube::services::escapeFromXML(parseContext.expressionAggrAggr),
                            parseContext.rowwise,
                            cube::Metric::get_viz_type_of_metric(parseContext.metricVizType));
        if (parseContext.currentMetric != NULL)
        {
            parseContext.currentMetric->setConvertible( parseContext.metricConvertible );
            parseContext.currentMetric->setCacheable( parseContext.metricCacheable );
            parseContext.currentMetric->set_filed_id( parseContext.id );
            if (parseContext.n_attributes.size() > 0)
            {
                unsigned nattributes = parseContext.n_attributes.top();
                parseContext.n_attributes.pop();

                if (nattributes > parseContext.attributes.size())
                {
                error(cubeparserloc, "Number of saved attributes for metric " + parseContext.uniq_name + " is more, than number of actual saved parameters.");
                }
                std::stack<std::pair<std::string, std::string> > reversed;
                for (unsigned i=0; i< nattributes; i++)
                {
                    std::pair< std::string, std::string>  attr = parseContext.attributes.top();
                    parseContext.attributes.pop();
                    reversed.push(attr);
                }
                for (unsigned i=0; i< nattributes; i++)
                {
                    std::pair< std::string, std::string>  attr = reversed.top();
                    reversed.pop();
                    parseContext.currentMetric->def_attr(attr.first, attr.second);
                }
            }
        parseContext.metricVec[parseContext.id] = parseContext.currentMetric;
        }
        else
        {
            std::string _error = "Cannot create metric  " + parseContext.uniq_name + ". Ignore it.";
            cerr << _error << endl;
/*             error(cubeparserloc,_error.c_str()); */
        }
}
#line 1715 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 135: // generic_attr_tag: "<attr" key_attr value_attr "/>"
#line 1277 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                             {
    //check for attributes
    if (!parseContext.keySeen)
      error(cubeparserloc,"Missing key attribute!");
    else parseContext.keySeen = false;
    if (!parseContext.valueSeen)
      error(cubeparserloc,"Missing value attribute!");
    else parseContext.valueSeen = false;

    unsigned nattributes = 0;
    if (parseContext.n_attributes.size() != 0  )
    {
        nattributes = parseContext.n_attributes.top();
        parseContext.n_attributes.pop();
    }
    nattributes++;
    parseContext.n_attributes.push(nattributes);
    std::pair<std::string, std::string > _key ;
    _key.first  =  cube::services::escapeFromXML(parseContext.key);
    _key.second =  cube::services::escapeFromXML(parseContext.value) ;
    parseContext.attributes.push( _key );
}
#line 1742 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 136: // metric_end: "</metric>"
#line 1305 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
             {
        if (parseContext.currentMetric!=NULL)
        parseContext.currentMetric =
            (parseContext.currentMetric)->get_parent();
}
#line 1752 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 137: // $@2: %empty
#line 1317 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    cube.get_operation_progress()->progress_step(0.2, "Start parsing program dimension");
}
#line 1760 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 138: // $@3: %empty
#line 1321 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    cube.get_operation_progress()->progress_step(0.3, "Start parsing regions");
}
#line 1768 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 139: // $@4: %empty
#line 1326 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    cube.get_operation_progress()->progress_step(0.4, "Start parsing call tree");
}
#line 1776 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 140: // program_tag: "<program" $@2 calltree_title_attr ">" $@3 region_tags $@4 cnode_tag "</program>"
#line 1330 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    if (parseContext.calltreeTitle != "")
        cube.set_calltree_title(cube::services::escapeFromXML(parseContext.calltreeTitle));

  if (clustering_on) // here look for region template  and create subtrees for iterations
  {
          cube.get_operation_progress()->start_step(0., 1.);
    cube.get_operation_progress()->progress_step("Start declustering");
    // after parsing, whole stored calltree is stored not within cube, but separatelly, in parseContext.oroginal_tree_roots.
    // here we create first a copy of the original tree without clustering subtrees
    cube::Cnode * clusters_root = NULL;
    cube.set_original_root_cnodev( parseContext.original_tree_roots );
    int step = 0;
    for (std::vector<cube::Cnode*>::iterator citer= parseContext.original_tree_roots.begin(); citer!=parseContext.original_tree_roots.end(); ++citer, ++step )
    {
        cube::Cnode* cnode = *citer;
        cube::Cnode * _clusters_root = NULL;
        cube::services::copy_tree( cnode, _clusters_root, parseContext.clustering_root_cnode_id,  NULL, &cube);
        if (_clusters_root != NULL )
            clusters_root = _clusters_root;
    }
    parseContext.clustering_root_cnode = clusters_root;

    if (cube::services::get_children( parseContext.original_tree_roots,
        parseContext.clustering_root_cnode_id,
        parseContext.clusters_trees))
    {
        int i = 0;
        for (std::vector<cube::Cnode*>::iterator citer= parseContext.clusters_trees.begin(); citer!=parseContext.clusters_trees.end(); ++citer, ++i )
        {
            parseContext.id2cluster[ (*citer)->get_id() ] = i;
        }

    }else
    {
        clustering_on = false;
        break;
    }

    cube.get_operation_progress()->progress_step(0.1, "Create iteration template");

     // here we are going througs registered sofar regions and look for first cluster to take its region as a template for iterations
     for (std::vector<cube::Region*>::const_iterator riter= cube.get_regv().begin(); riter!=cube.get_regv().end(); ++riter )
     {
      cube::Region* region = *riter;
      if (region->get_name().compare("instance=1")==0)
      {
        parseContext.iterationRegionTemplate = region;
        break;
      }
     }
     // if we didn't found any regions, but clustering was "on" -> fatal error appeared.
     if (parseContext.iterationRegionTemplate == NULL ) // we didnt find any template for iteration subtree, bad cube layout
      throw cube::CubeClusteringLayoutError("Cannot find a template for iteration calltree.");

    // here we merge different combinations of clusters.
    // one can reduce amount of merges if one finds ont set of different collapsed rows - improvements for future.
     cube.get_operation_progress()->progress_step(0.2, "Create iterations");

      // here we create regions for iterations
     std::map<uint64_t,   std::map<uint64_t, uint64_t> > cluster_counter = cube.get_clusters_counter();
      for (unsigned i=0; i< parseContext.number_of_iterations; i++)
      {
        std::stringstream sstr;
        std::string iteration_name;
        sstr << i;
        sstr >> iteration_name;
        // we create a regions
        cube::Region * region =  cube.def_region(
                            "iteration="+iteration_name,
                            "iteration="+iteration_name,
                            parseContext.iterationRegionTemplate->get_paradigm(),
                            parseContext.iterationRegionTemplate->get_role(),
                            parseContext.iterationRegionTemplate->get_begn_ln(),
                            parseContext.iterationRegionTemplate->get_end_ln(),
                            parseContext.iterationRegionTemplate->get_url(),
                            parseContext.iterationRegionTemplate->get_descr(),
                            parseContext.iterationRegionTemplate->get_mod()
                            );
        parseContext.iteration_regions.push_back( region );
        // create its cnode
        cube::Cnode* iteration_cnode = cube.def_cnode(
                            region,
                            region->get_mod(),
                            region->get_begn_ln(),
                            parseContext.clustering_root_cnode
                            );

        // here we merge all subtrees of all clusters to this callpath.
        std::vector<cube::Cnode*> subtrees;
        for ( std::vector< uint64_t>::iterator iter= parseContext.collapsed_cluster_mapping[i].begin(); iter != parseContext.collapsed_cluster_mapping[i].end(); ++iter  )
        {
            subtrees.clear();
            uint64_t _cluster_id = *iter;
            std::map<uint64_t, uint64_t> _cluster_normalization = cluster_counter[ _cluster_id ];
            uint64_t _cluster_position = parseContext.id2cluster[_cluster_id];
            cube::Cnode* cluster_root = parseContext.clusters_trees[_cluster_position];
            cube.store_ghost_cnode( cluster_root );
            for ( size_t j = 0; j <  parseContext.cluster_positions[ i ][ _cluster_id ].size(); ++j )
            {
                iteration_cnode->set_remapping_cnode( parseContext.cluster_positions[ i ][ _cluster_id ][j], cluster_root,  _cluster_normalization[parseContext.cluster_positions[ i ][ _cluster_id ][j]] );
            }
            cube::services::gather_children( subtrees, cluster_root );
            cube::services::merge_trees(subtrees, iteration_cnode, &cube, &_cluster_normalization, &(parseContext.cluster_positions[ i ][ _cluster_id ]) );
        }
        cube.get_operation_progress()->progress_step(0.2 + ((i*0.8)/parseContext.number_of_iterations), "Create iterations");
      }
    cube.get_operation_progress()->finish_step("Declustering is done");
  }
    cube.get_operation_progress()->progress_step(0.4, "Finished parsing program dimension");
}
#line 1892 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 143: // region_tag: "<region" region_attributes ">" tags_of_region_attr "</region>"
#line 1449 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                                             {
        //check for the attributes
        if (!parseContext.idSeen)
          error(cubeparserloc,"Missing id attribute!");
        else parseContext.idSeen = false;
        if (!parseContext.modSeen)
                parseContext.mod = "";
        else parseContext.modSeen = false;
        if (!parseContext.beginSeen)
                parseContext.beginln = -1;
        else parseContext.beginSeen = false;
        if (!parseContext.endSeen)
                parseContext.endln = -1;
        else parseContext.endSeen = false;
    if (!parseContext.paradigmSeen)
        parseContext.paradigm = "unknown";
    else parseContext.paradigmSeen = false;
    if (!parseContext.roleSeen)
        parseContext.role = "unknown";
    else parseContext.roleSeen = false;
        //check for tags
        if (parseContext.nameSeen) parseContext.nameSeen = false;
        else parseContext.name = "";
        if (parseContext.mangledNameSeen) parseContext.mangledNameSeen = false;
        else parseContext.mangled_name = parseContext.name;
        if (parseContext.urlSeen) parseContext.urlSeen = false;
        else parseContext.url = "";
        if (parseContext.descrSeen) parseContext.descrSeen = false;
        else parseContext.descr = "";

        while ((int)parseContext.regionVec.size()<=parseContext.id)
                parseContext.regionVec.push_back(NULL);
        if (parseContext.regionVec[parseContext.id]!=NULL)
          error(cubeparserloc,"Re-declared region!");

        cube::Region * _region =
        cube.def_region(
                 cube::services::escapeFromXML(parseContext.name),
                 cube::services::escapeFromXML(parseContext.mangled_name),
                 cube::services::escapeFromXML(parseContext.paradigm),
                 cube::services::escapeFromXML(parseContext.role),
                        parseContext.beginln,
                        parseContext.endln,
                        parseContext.url,
                 cube::services::escapeFromXML(parseContext.descr),
                 cube::services::escapeFromXML(parseContext.mod),
                        parseContext.id);
    if (parseContext.n_attributes.size() > 0)
    {
        unsigned nattributes = parseContext.n_attributes.top();
        parseContext.n_attributes.pop();

        if (nattributes > parseContext.attributes.size())
        {
        error(cubeparserloc, "Number of saved attributes for region " + parseContext.name + " is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            _region->def_attr(attr.first, attr.second);
        }
    }
    parseContext.regionVec[parseContext.id] = _region;
}
#line 1969 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 163: // cnode_tag: cnode_tag cnode_parameters cnode_attr_tags "</cnode>"
#line 1560 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    if (parseContext.n_attributes.size() > 0)
    {
        unsigned nattributes = parseContext.n_attributes.top();
        parseContext.n_attributes.pop();

        if (nattributes > parseContext.attributes.size())
        {
            error(cubeparserloc, "Number of saved attributes for cnode is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            parseContext.currentCnode->def_attr(attr.first, attr.second);
        }
    }


    if (!clustering_on)
    {

          if (parseContext.currentCnode==NULL)
            error(cubeparserloc,"Cnode definitions are not correctly nested!");


          if (!parseContext.n_cnode_num_parameters.empty()  )
          {
              unsigned nparameters = parseContext.n_cnode_num_parameters.top();
              parseContext.n_cnode_num_parameters.pop();

              if (nparameters > parseContext.cnode_num_parameters.size())
              {
                  error(cubeparserloc, "Number of saved numeric parameters for current cnode is more, than number of actual saved parameters.");
              }
              std::stack<std::pair<std::string, std::string> > reversed;
              for (unsigned i=0; i< nparameters; ++i)
              {
                  std::pair< std::string, std::string>  param = parseContext.cnode_num_parameters.top();

                  parseContext.cnode_num_parameters.pop();
                  reversed.push(param);
              }
              for (unsigned i=0; i< nparameters; ++i)
              {
                  std::pair< std::string, std::string> param = reversed.top();
                  reversed.pop();

                  double d_value = atof(param.second.data());
                  parseContext.currentCnode->add_num_parameter(param.first, d_value);
              }
          }
          if (!parseContext.n_cnode_str_parameters.empty()  )
          {
              unsigned nparameters = parseContext.n_cnode_str_parameters.top();
              parseContext.n_cnode_str_parameters.pop();

              if (nparameters > parseContext.cnode_str_parameters.size())
              {
                  error(cubeparserloc, "Number of saved string parameters for current cnode is more, than number of actual saved parameters.");
              }
              std::stack<std::pair<std::string, std::string> > reversed;
              for (unsigned i=0; i< nparameters; ++i)
              {

                  std::pair< std::string, std::string>  param = parseContext.cnode_str_parameters.top();
                  parseContext.cnode_str_parameters.pop();
                  reversed.push(param);
              }
              for (unsigned i=0; i< nparameters; ++i)
              {
                  std::pair< std::string, std::string> param = reversed.top();
                  reversed.pop();
                  parseContext.currentCnode->add_str_parameter(param.first, param.second);
              }
          }

          parseContext.currentCnode =
                  parseContext.currentCnode->get_parent();
          parseContext.start_parse_clusters = false;
    }
    else
    {
        if (parseContext.clusterCurrentCnode==NULL)
          error(cubeparserloc,"Cluster cnode definitions are not correctly nested!");


        if (!parseContext.n_cnode_num_parameters.empty()  )
        {
            unsigned nparameters = parseContext.n_cnode_num_parameters.top();
            parseContext.n_cnode_num_parameters.pop();

            if (nparameters > parseContext.cnode_num_parameters.size())
            {
                error(cubeparserloc, "Number of saved numeric parameters for current cnode is more, than number of actual saved parameters.");
            }
            std::stack<std::pair<std::string, std::string> > reversed;
            for (unsigned i=0; i< nparameters; ++i)
            {
                std::pair< std::string, std::string>  param = parseContext.cnode_num_parameters.top();

                parseContext.cnode_num_parameters.pop();
                reversed.push( param );
            }
            for ( unsigned i = 0; i < nparameters; ++i )
            {
                std::pair< std::string, std::string> param = reversed.top();
                reversed.pop();

                double d_value = atof(param.second.data());
                parseContext.clusterCurrentCnode->add_num_parameter(param.first, d_value);
            }
        }
        if (!parseContext.n_cnode_str_parameters.empty()  )
        {
            unsigned nparameters = parseContext.n_cnode_str_parameters.top();
            parseContext.n_cnode_str_parameters.pop();

            if (nparameters > parseContext.cnode_str_parameters.size())
            {
                error(cubeparserloc, "Number of saved string parameters for current cnode is more, than number of actual saved parameters.");
            }
            std::stack<std::pair<std::string, std::string> > reversed;
            for (unsigned i=0; i< nparameters; ++i)
            {
                std::pair< std::string, std::string>  param = parseContext.cnode_str_parameters.top();
                parseContext.cnode_str_parameters.pop();
                reversed.push( param );
            }
            for ( unsigned i = 0; i < nparameters; ++i )
            {
                std::pair< std::string, std::string> param = reversed.top();
                reversed.pop();
                parseContext.clusterCurrentCnode->add_str_parameter(param.first, param.second);
            }
        }

        parseContext.clusterCurrentCnode =
                parseContext.clusterCurrentCnode->get_parent();
        if (parseContext.clusterCurrentCnode == NULL)
        {
          parseContext.parse_clusters = false;
        }

    }

}
#line 2128 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 164: // cnode_begin: "<cnode" cnode_attributes ">"
#line 1717 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                           {
        //check for the attributes
        if (!parseContext.idSeen)
          error(cubeparserloc,"Missing id attribute in cnode definition!");
        else parseContext.idSeen = false;
        if (!parseContext.calleeidSeen)
          error(cubeparserloc,"Missing callee id attribute in cnode definition!");
        else parseContext.calleeidSeen = false;
        if (!parseContext.lineSeen)
                  parseContext.line = -1;
        else parseContext.lineSeen = false;
        if (!parseContext.modSeen)
                  parseContext.mod = "";
        else parseContext.modSeen = false;
        //check if the region is defined
        if ((int)parseContext.regionVec.size()<=parseContext.calleeid)
          error(cubeparserloc,"Undefined region in cnode definition!");
        if (parseContext.regionVec[parseContext.calleeid]==NULL)
          error(cubeparserloc,"Undefined region in cnode definition!");
        //extend the cnode vector if necessary
        while ((int)parseContext.cnodeVec.size()<=parseContext.id)
                parseContext.cnodeVec.push_back(NULL);
        if (parseContext.cnodeVec[parseContext.id]!=NULL)
          error(cubeparserloc,"Re-declared cnode!");
        //define the cnode

    parseContext.cnodeParTypeSeen= false;
    parseContext.cnodeParKeySeen= false;
    parseContext.cnodeParValueSeen= false;

    if (clustering_on)
    {
          parseContext.clusterCurrentCnode = new cube::Cnode( parseContext.regionVec[parseContext.calleeid] ,
                                                            cube::services::escapeFromXML(parseContext.mod),
                                                            parseContext.line,
                                                            parseContext.clusterCurrentCnode,
                                                            parseContext.id );
        if (parseContext.clusterCurrentCnode->get_parent() == NULL) // store root call path for cluster in a vector.
        {
        parseContext.original_tree_roots.push_back(parseContext.clusterCurrentCnode );
        }
    }
    else
    {
      parseContext.currentCnode = cube.def_cnode(
                        parseContext.regionVec[parseContext.calleeid],
                 cube::services::escapeFromXML(parseContext.mod),
                        parseContext.line,
                        parseContext.currentCnode,
                        parseContext.id);

        parseContext.cnodeVec[parseContext.id] =
                parseContext.currentCnode;
    }
}
#line 2188 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 175: // $@5: %empty
#line 1802 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
  cube.get_operation_progress()->start_step(0., 1.);
}
#line 2196 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 176: // system_tag: "<system" $@5 systemtree_title_attr ">" systemtree_tags topologies_tag_attr "</system>"
#line 1806 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    cube.get_operation_progress()->finish_step("Finished parsing system tree");
    if (parseContext.systemtreeTitle != "")
        cube.set_systemtree_title(cube::services::escapeFromXML(parseContext.systemtreeTitle));

    // at this moment all dimensionis are loadeed -> we can initialize containers
    cube.initialize();


}
#line 2211 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 181: // $@6: %empty
#line 1832 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
    cube.get_operation_progress()->start_step(0.7, 1.);
    cube.get_operation_progress()->progress_step("Start parsing system tree");
}
#line 2220 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 182: // $@7: %empty
#line 1836 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                                            {
        //check for attributes
        parseContext.idSeen = false;
        //check for tags
        parseContext.nameSeen = false;
        if (!parseContext.classSeen )
           error(cubeparserloc,"No class of system tree node declared.");
        parseContext.classSeen = false;
        if (parseContext.descrSeen) parseContext.descrSeen = false;
        else parseContext.descr = "";

        cube::SystemTreeNode * _stn = cube.def_system_tree_node(
                                    cube::services::escapeFromXML(parseContext.name),
                                    cube::services::escapeFromXML(parseContext.descr),
                                    cube::services::escapeFromXML(parseContext.stn_class),
                                    (parseContext.currentSystemTreeNode.size() == 0)? NULL : parseContext.currentSystemTreeNode.top() );
    if (parseContext.n_attributes.size() > 0)
    {
        unsigned nattributes = parseContext.n_attributes.top();
        parseContext.n_attributes.pop();

        if (nattributes > parseContext.attributes.size())
        {
        error(cubeparserloc, "Number of saved attributes for metric " + parseContext.uniq_name + " is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            _stn->def_attr(attr.first, attr.second);
        }
    }


        parseContext.currentSystemTreeNode.push(_stn);
         while ((unsigned int)parseContext.stnVec.size()<=_stn->get_id())
                 parseContext.stnVec.push_back(NULL);
        if (parseContext.stnVec[_stn->get_id()]!=NULL)
          error(cubeparserloc,"Re-declared system tree node!");
        parseContext.stnVec[_stn->get_id()] =_stn;


        std::string _step = "Created system tree node " + cube::services::escapeFromXML(parseContext.name);

        cube.get_operation_progress()->progress_step(  _step );


}
#line 2280 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 183: // systemtree_tag: "<systemtreenode" $@6 id_attr ">" name_tag class_tag descr_tag_opt systree_attr_tags $@7 location_group_tags systemtree_sub_tags "</systemtreenode>"
#line 1894 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{

  parseContext.currentSystemTreeNode.pop();
        //check for attributes
  parseContext.idSeen = false;
        //check for tags
        parseContext.nameSeen = false;
  if (parseContext.descrSeen) parseContext.descrSeen = false;
      else parseContext.descr = "";
    cube.get_operation_progress()->finish_step("Finished parsing system tree");
}
#line 2296 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 190: // $@8: %empty
#line 1930 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                 {
        //check for attributes
        parseContext.idSeen = false;
        //check for tags
        parseContext.nameSeen = false;
        parseContext.rankSeen = false;
        if (!parseContext.typeSeen )
           error(cubeparserloc,"No type of location group declared.");
        parseContext.typeSeen = false;

        if (parseContext.descrSeen) parseContext.descrSeen = false;
          else parseContext.descr = "";

        parseContext.currentLocationGroup = cube.def_location_group(
         cube::services::escapeFromXML(parseContext.name),
                parseContext.rank,
                cube::LocationGroup::getLocationGroupType(cube::services::escapeFromXML(parseContext.type)),
                parseContext.currentSystemTreeNode.top());
    if (parseContext.n_attributes.size() > 0)
    {
        unsigned nattributes = parseContext.n_attributes.top();
        parseContext.n_attributes.pop();

        if (nattributes > parseContext.attributes.size())
        {
        error(cubeparserloc, "Number of saved attributes for location group " + parseContext.name + " is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            parseContext.currentLocationGroup->def_attr(attr.first, attr.second);
        }
    }


        while ((unsigned int)parseContext.locGroup.size()<=parseContext.currentLocationGroup->get_id())
                parseContext.locGroup.push_back(NULL);
        if (parseContext.locGroup[parseContext.currentLocationGroup->get_id()]!=NULL)
          error(cubeparserloc,"Re-declared location group!");
        parseContext.locGroup[parseContext.currentLocationGroup->get_id()] = parseContext.currentLocationGroup;

        std::string _step =  "Created location group " + cube::services::escapeFromXML(parseContext.name);
        cube.get_operation_progress()->progress_step( _step );
        }
#line 2353 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 198: // location_tag: "<location" id_attr ">" loc_tags "</location>"
#line 2004 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                             {
        //check for attributes
        parseContext.idSeen = false;
        //check for tags
        parseContext.nameSeen = false;
        parseContext.rankSeen = false;

        if (!parseContext.typeSeen )
           error(cubeparserloc,"No type of location group declared.");
        parseContext.typeSeen = false;
        parseContext.currentLocation = cube.def_location(
         cube::services::escapeFromXML(parseContext.name),
                parseContext.rank,
                cube::Location::getLocationType(cube::services::escapeFromXML(parseContext.type)),
                parseContext.currentLocationGroup,
                parseContext.id);
    if (parseContext.n_attributes.size() > 0)
    {
        unsigned nattributes = parseContext.n_attributes.top();
        parseContext.n_attributes.pop();

        if (nattributes > parseContext.attributes.size())
        {
        error(cubeparserloc, "Number of saved attributes for location " + parseContext.name + " is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i)
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            parseContext.currentLocation->def_attr(attr.first, attr.second);
        }
    }

        while (( unsigned int)parseContext.locVec.size()<=parseContext.currentLocation->get_id())
                parseContext.locVec.push_back(NULL);
        if (parseContext.locVec[parseContext.currentLocation->get_id()]!=NULL)
          error(cubeparserloc,"Re-declared location!");
        parseContext.locVec[parseContext.currentLocation->get_id()] = parseContext.currentLocation;
        if ( parseContext.currentLocation->get_id() % 1024 == 0)
        {
           std::string _step =  "Created location " + cube::services::escapeFromXML(parseContext.name);
           cube.get_operation_progress()->progress_step( _step );
        }
}
#line 2409 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 201: // $@9: %empty
#line 2067 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                          {
        //check for attributes
        parseContext.idSeen = false;
        //check for tags
        parseContext.nameSeen = false;
        if (parseContext.descrSeen) parseContext.descrSeen = false;
        else parseContext.descr = "";

        parseContext.currentMachine = cube.def_mach(
         cube::services::escapeFromXML(parseContext.name),
         cube::services::escapeFromXML(parseContext.descr));
        while ((unsigned int)parseContext.stnVec.size()<=parseContext.currentMachine->get_id())
                parseContext.stnVec.push_back(NULL);
        if (parseContext.stnVec[parseContext.currentMachine->get_id()]!=NULL)
          error(cubeparserloc,"Re-declared machine!");
        parseContext.stnVec[parseContext.currentMachine->get_id()] = parseContext.currentMachine;
}
#line 2431 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 205: // $@10: %empty
#line 2092 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                        {
        //check for attributes
        parseContext.idSeen = false;
        //check for tags
        parseContext.nameSeen = false;
    if (parseContext.descrSeen) parseContext.descrSeen = false;
    else parseContext.descr = "";

        parseContext.currentNode = cube.def_node(
         cube::services::escapeFromXML(parseContext.name),
                parseContext.currentMachine);
        while ((unsigned int)parseContext.stnVec.size()<=parseContext.currentNode->get_id())
                parseContext.stnVec.push_back(NULL);
        if (parseContext.stnVec[parseContext.currentNode->get_id()]!=NULL)
          error(cubeparserloc,"Re-declared node!");
        parseContext.stnVec[parseContext.currentNode->get_id()] = parseContext.currentNode;
}
#line 2453 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 209: // $@11: %empty
#line 2117 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                    {
        //check for attributes
        parseContext.idSeen = false;
        //check for tags
        if (parseContext.nameSeen) parseContext.nameSeen = false;
        else parseContext.name = "";
        if (parseContext.rankSeen) parseContext.rankSeen = false;
        else parseContext.rank = 0;

        std::ostringstream name;
        if (parseContext.name.empty()) {
          name << "Process " << parseContext.rank;
        } else {
          name << parseContext.name;
        }
        parseContext.currentProc = cube.def_proc(
         cube::services::escapeFromXML(name.str()),
                parseContext.rank,
                parseContext.currentNode);
        while ((unsigned int)parseContext.locGroup.size()<=parseContext.currentProc->get_id())
                parseContext.locGroup.push_back(NULL);
        if (parseContext.locGroup[parseContext.currentProc->get_id()]!=NULL)
          error(cubeparserloc,"Re-declared process!");
        parseContext.locGroup[parseContext.currentProc->get_id()] = parseContext.currentProc;
}
#line 2483 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 217: // thread_tag: "<thread" id_attr ">" tags_of_process "</thread>"
#line 2159 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                                               {
        //check for attributes
        parseContext.idSeen = false;
        //check for tags
        if (parseContext.nameSeen) parseContext.nameSeen = false;
        else parseContext.name = "";
        if (parseContext.rankSeen) parseContext.rankSeen = false;
        else parseContext.rank = 0;

        std::ostringstream name;
        if (parseContext.name.empty()) {
          name << "Thread " << parseContext.rank;
        } else {
          name << parseContext.name;
        }


        parseContext.currentThread = cube.def_thrd(
         cube::services::escapeFromXML(name.str()),
                parseContext.rank,
                parseContext.currentProc,
                parseContext.id);
        while ((unsigned int)parseContext.locVec.size()<=parseContext.currentThread->get_id())
                parseContext.locVec.push_back(NULL);
        if (parseContext.locVec[parseContext.currentThread->get_id()]!=NULL)
          error(cubeparserloc,"Re-declared thread!");
        parseContext.locVec[parseContext.currentThread->get_id()] = parseContext.currentThread;
}
#line 2516 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 220: // $@12: %empty
#line 2197 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
        if (!parseContext.checkThreadIds())
          error(cubeparserloc,"Thread ids must cover an interval [0,n] without gap!");
}
#line 2525 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 228: // $@13: %empty
#line 2219 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
        //check for attributes
        parseContext.ndimsSeen = false;

        if (parseContext.ndims!=(int)parseContext.dimVec.size())
          error(cubeparserloc,"Too few or too many topology dimensions are declared!");
        parseContext.currentCart = cube.def_cart(
                parseContext.ndims,
                parseContext.dimVec,
                parseContext.periodicVec);

        if (parseContext.cartNameSeen)
        {
            (parseContext.currentCart)->set_name(cube::services::escapeFromXML(parseContext.cartName));
            parseContext.cartNameSeen=false;
        }
        if(parseContext.dimNamesCount>0)
        {
            parseContext.dimNamesCount = 0;
            (parseContext.currentCart)->set_namedims(parseContext.dimNameVec);
        }
        parseContext.dimNameVec.clear();

}
#line 2554 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 230: // cart_open: "<cart"
#line 2246 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
          {parseContext.dimVec.clear();
           parseContext.periodicVec.clear();
        parseContext.cartNameSeen=false;
}
#line 2563 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 233: // dim_tag: "<dim" dim_attributes "/>"
#line 2258 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                         {
        //check for attributes
        if (!parseContext.sizeSeen)
          error(cubeparserloc,"Missing size attribute!");
        else parseContext.sizeSeen = false;
        if (!parseContext.periodicSeen)
          error(cubeparserloc,"Missing periodic attribute!");
        else parseContext.periodicSeen = false;
        if (parseContext.dimNameSeen )
            parseContext.dimNameVec.push_back(parseContext.dimName);
        else
            parseContext.dimNameVec.push_back("");
        parseContext.dimNameSeen= false;
  }
#line 2582 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 248: // coord_tag_loc: locid_attr ">" "</coord>"
#line 2312 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                      {
        //check for attributes
        parseContext.locidSeen = false;

        if (parseContext.dimVec.size()!=parseContext.longValues.size())
          error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!");
        for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
            if (parseContext.longValues[i]>=parseContext.dimVec[i])
          error(cubeparserloc,"Topology coordinate is out of range!");
        }
        if (parseContext.locid>=(int)parseContext.locVec.size())
          error(cubeparserloc,"Location of the topology coordinates wasn't declared!");
        if (parseContext.locVec[parseContext.locid]==NULL)
          error(cubeparserloc,"Location of the topology coordinates wasn't declared!");
        cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.locVec[parseContext.locid]),
                         parseContext.longValues);
}
#line 2605 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 249: // coord_tag_lg: lgid_attr ">" "</coord>"
#line 2333 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                     {
        //check for attributes
        parseContext.lgidSeen = false;

        if (parseContext.dimVec.size()!=parseContext.longValues.size())
          error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!");
        for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
            if (parseContext.longValues[i]>=parseContext.dimVec[i])
          error(cubeparserloc,"Topology coordinate is out of range!");
        }
        if (parseContext.lgid>=(int)parseContext.locGroup.size())
          error(cubeparserloc,"Location group of the topology coordinates wasn't declared!");
        if (parseContext.locGroup[parseContext.lgid]==NULL)
          error(cubeparserloc,"Location group of the topology coordinates wasn't declared!");
        cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.locGroup[parseContext.lgid]),
                         parseContext.longValues);
}
#line 2628 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 250: // coord_tag_stn: stnid_attr ">" "</coord>"
#line 2354 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                      {
        //check for attributes
        parseContext.stnidSeen = false;

        if (parseContext.dimVec.size()!=parseContext.longValues.size())
          error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!");
        for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
            if (parseContext.longValues[i]>=parseContext.dimVec[i])
          error(cubeparserloc,"Topology coordinate is out of range!");
        }
        if (parseContext.stnid>=(int)parseContext.stnVec.size())
          error(cubeparserloc,"System tree node of the topology coordinates wasn't declared!");
        if (parseContext.nodeVec[parseContext.stnid]==NULL)
          error(cubeparserloc,"System tree node of the topology coordinates wasn't declared!");
        cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.nodeVec[parseContext.stnid]),
                         parseContext.longValues);
}
#line 2651 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 251: // coord_tag_thrd: thrdid_attr ">" "</coord>"
#line 2376 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                       {
        //check for attributes
        parseContext.locidSeen = false;

        if (parseContext.dimVec.size()!=parseContext.longValues.size())
          error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!");
        for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
            if (parseContext.longValues[i]>=parseContext.dimVec[i])
          error(cubeparserloc,"Topology coordinate is out of range!");
        }
        if (parseContext.thrdid>=(int)parseContext.locVec.size())
          error(cubeparserloc,"Thread of the topology coordinates wasn't declared!");
        if (parseContext.locVec[parseContext.thrdid]==NULL)
          error(cubeparserloc,"Thread of the topology coordinates wasn't declared!");
        cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.locVec[parseContext.thrdid]),
                         parseContext.longValues);
}
#line 2674 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 252: // coord_tag_proc: procid_attr ">" "</coord>"
#line 2397 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                       {
        //check for attributes
        parseContext.lgidSeen = false;

        if (parseContext.dimVec.size()!=parseContext.longValues.size())
          error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!");
        for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
            if (parseContext.longValues[i]>=parseContext.dimVec[i])
          error(cubeparserloc,"Topology coordinate is out of range!");
        }
        if (parseContext.procid>=(int)parseContext.locGroup.size())
          error(cubeparserloc,"Process of the topology coordinates wasn't declared!");
        if (parseContext.locGroup[parseContext.procid]==NULL)
          error(cubeparserloc,"Process of the topology coordinates wasn't declared!");
        cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.locGroup[parseContext.procid]),
                         parseContext.longValues);
}
#line 2697 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 253: // coord_tag_node: nodeid_attr ">" "</coord>"
#line 2418 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                       {
        //check for attributes
        parseContext.stnidSeen = false;

        if (parseContext.dimVec.size()!=parseContext.longValues.size())
          error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!");
        for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
            if (parseContext.longValues[i]>=parseContext.dimVec[i])
          error(cubeparserloc,"Topology coordinate is out of range!");
        }

        if (parseContext.nodeid >= (int)cube.get_non_root_stnv().size())
          error(cubeparserloc,"Node of the topology coordinates wasn't declared!");
        if (cube.get_non_root_stnv().at(parseContext.nodeid)==NULL)
          error(cubeparserloc,"Node of the topology coordinates wasn't declared!");
        cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(cube.get_non_root_stnv().at(parseContext.nodeid)),
                         parseContext.longValues);
}
#line 2721 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 254: // coord_tag_mach: machid_attr ">" "</coord>"
#line 2440 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                       {
        //check for attributes
        parseContext.stnidSeen = false;

        if (parseContext.dimVec.size()!=parseContext.longValues.size())
          error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!");
        for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
            if (parseContext.longValues[i]>=parseContext.dimVec[i])
          error(cubeparserloc,"Topology coordinate is out of range!");
        }
        if (parseContext.machid>=(int)cube.get_root_stnv().size())
          error(cubeparserloc,"Machine of the topology coordinates wasn't declared!");
        if (cube.get_root_stnv().at(parseContext.nodeid)==NULL)
          error(cubeparserloc,"Machine of the topology coordinates wasn't declared!");
        cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(cube.get_root_stnv().at(parseContext.machid)),
                         parseContext.longValues);
}
#line 2744 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 257: // $@14: %empty
#line 2470 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
              {
// if (parseContext.dynamicMetricLoading) return 0;
std::string _step = "Start reading data";
cube.get_operation_progress()->progress_step( _step );
}
#line 2754 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 258: // severity_part: "<severity>" $@14 matrix_tags "</severity>"
#line 2475 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
{
cube.get_operation_progress()->finish_step("Finished reading data");
}
#line 2762 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 261: // $@15: %empty
#line 2487 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                        {
        //check for attributes
        parseContext.metricidSeen = false;

        if ((int)parseContext.metricVec.size()<=parseContext.metricid)
          error(cubeparserloc,"Metric of the severity matrix wasn't declared!");
        if (parseContext.metricVec[parseContext.metricid]==NULL)
          error(cubeparserloc,"Metric of the severity matrix wasn't declared!");
        parseContext.currentMetric =
                parseContext.metricVec[parseContext.metricid];

        parseContext.ignoreMetric = false;
        cube::Metric* metric = parseContext.currentMetric;
        while (metric!=NULL) {
                    if (metric->get_val() == "VOID") {
                        parseContext.ignoreMetric = true;
                        break;
                    }
                    metric = metric->get_parent();
          }
}
#line 2788 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 267: // $@16: %empty
#line 2520 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                                    {
        //check for attributes
        parseContext.cnodeidSeen = false;

        if (!parseContext.ignoreMetric){
                if ((int)parseContext.cnodeVec.size()<=parseContext.cnodeid)
                  error(cubeparserloc,"Cnode of the severity row wasn't declared!");
                if (parseContext.cnodeVec[parseContext.cnodeid]==NULL)
                  error(cubeparserloc,"Cnode of the severity row wasn't declared!");
                parseContext.currentCnode =
                        parseContext.cnodeVec[parseContext.cnodeid];
        }
}
#line 2806 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;

  case 268: // row_tag: "<row" cnodeid_attr ">" $@16 "</row>"
#line 2532 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
            {
        if (!parseContext.ignoreMetric)
    {
                  std::vector<double> & v = parseContext.realValues;
                std::vector<cube::Thread*> & t = parseContext.locVec;
        if (v.size()>t.size())
                error(cubeparserloc,"Too many values in severity row!");
        std::vector<cube::Thread*> t_sorted = t;
        sort(t_sorted.begin(), t_sorted.end(), &cube::IdentObject::id_compare);


                cube::Metric* metric = parseContext.currentMetric;
                cube::Cnode * cnode = parseContext.currentCnode;
        for (unsigned i=0; i<v.size(); ++i)
        {
            cube.set_sev(metric,
                            cnode,
                            t_sorted[i],
                            v[i]);
        }
        }
}
#line 2833 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
    break;


#line 2837 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Cube4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Cube4Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Cube4Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Cube4Parser::context.
  Cube4Parser::context::context (const Cube4Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Cube4Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Cube4Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Cube4Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short Cube4Parser::yypact_ninf_ = -398;

  const signed char Cube4Parser::yytable_ninf_ = -1;

  const short
  Cube4Parser::yypact_[] =
  {
      36,   -13,    52,   109,    53,    59,  -398,  -398,    -9,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,    60,
    -398,     0,  -398,  -398,  -398,  -398,  -398,   -62,    23,  -398,
      81,     0,  -398,    83,    73,   159,   160,  -398,  -398,    -7,
    -398,   100,   104,  -398,    55,  -398,  -398,    83,    73,    73,
    -398,    71,  -398,  -398,  -398,  -398,   103,  -398,   106,   100,
    -398,   167,   163,    73,    71,    71,    61,  -398,    72,  -398,
    -398,  -398,  -398,   148,    71,    72,    72,   172,   168,    66,
    -398,  -398,  -398,    64,    -8,  -398,    72,  -398,  -398,  -398,
    -398,   176,   173,  -398,   177,  -398,   -24,  -398,  -398,  -398,
    -398,  -398,   149,  -398,    11,   -40,  -398,   180,   181,   110,
     143,  -398,  -398,  -398,  -398,   178,   -24,    26,   149,  -398,
    -398,    64,    85,   151,  -398,   144,  -398,    57,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,     1,  -398,   187,   188,
     189,  -398,  -398,  -398,  -398,     5,  -398,   158,  -398,    64,
     186,  -398,    98,  -398,  -398,  -398,   193,   190,    91,    63,
     170,    65,   132,   133,   130,   131,   134,   128,   127,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,
       1,  -398,  -398,  -398,  -398,  -398,    -4,  -398,   -25,   -22,
    -398,   201,   122,   156,  -398,  -398,  -398,   102,   212,   206,
    -398,    95,   208,  -398,  -398,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,   135,   136,   137,   126,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,   185,    -4,  -398,   217,   219,
    -398,  -398,  -398,  -398,  -398,    -1,   117,  -398,   191,  -398,
     122,   145,  -398,   129,   156,  -398,   -91,   179,   222,  -398,
     204,  -398,  -398,  -398,   202,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,   232,   138,  -398,     6,   147,
    -398,  -398,  -398,  -398,   233,   234,   120,  -398,   235,   107,
     194,   179,  -398,  -398,  -398,  -398,  -398,   238,   139,  -398,
    -398,  -398,   157,   145,   198,  -398,  -398,  -398,   240,   246,
     244,  -398,  -398,  -398,   250,   245,  -398,  -398,    64,   101,
    -398,   -76,   240,  -398,  -398,  -398,  -398,  -398,   247,   248,
    -398,  -398,   252,   255,   150,  -398,  -398,  -398,    -6,  -398,
    -398,  -398,   205,  -398,  -398,   122,  -398,  -398,  -398,  -398,
    -398,  -398,    96,  -398,    32,   145,  -398,    10,    64,   151,
     220,  -398,  -398,   258,   259,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,   273,  -398,   221,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,   211,   213,   214,   223,   224,
     225,   226,   122,    64,   108,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,   192,  -398,  -398,   278,  -398,  -398,   195,
     197,   229,   -63,  -398,   200,   247,    64,   116,  -398,  -398,
    -398,   -63,  -398,  -398,   247,  -398,   279,  -398,  -398,   239,
    -398,  -398,   122,    64,   111,  -398,   249,   280,  -398,  -398,
    -398,   -63,   -31,  -398
  };

  const short
  Cube4Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,    75,    76,     0,    73,
       1,    78,    79,    80,    81,    82,    83,    84,    85,     0,
      71,     0,     2,     3,    72,    74,    86,     0,    99,   106,
       0,     0,    91,     0,     0,     0,     0,    96,    97,     0,
      94,   102,     0,   100,    18,    77,    92,     0,     0,     0,
     137,     0,     4,     5,    93,    95,     0,   104,     0,   103,
      98,     0,     0,     0,     0,     0,    20,   175,   255,    50,
     101,   105,    19,     0,     0,   255,   255,     0,     0,    22,
     257,    90,   256,   112,     0,   108,   255,    88,    89,    21,
     138,     0,     0,   259,     0,   113,   114,   136,   107,   109,
     110,    87,     0,    23,     0,     0,    32,     0,     0,     0,
       0,   116,   117,   118,   119,     0,   114,     0,   139,   141,
     181,     0,   218,   178,   179,   177,   199,     0,   258,   260,
       7,     8,    10,     9,    12,    11,   120,   115,     0,     0,
       0,   158,   157,   159,   160,     0,   155,     0,   142,     0,
       0,   220,     0,   219,   180,   200,     0,     0,     0,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   124,
     125,   126,   127,   128,   129,   131,   132,   133,   130,   111,
     121,   122,   134,     6,    43,    44,   144,   156,     0,   165,
     161,     0,     0,   222,   176,    41,   261,     0,     0,     0,
      60,     0,     0,    26,    27,    28,    51,    52,    53,    54,
      55,    56,    62,   123,     0,     0,     0,     0,   152,   153,
     148,   149,   150,   151,   154,     0,   145,   146,     0,     0,
     171,   169,   172,   170,   173,     0,     0,   140,   165,   167,
       0,    57,   230,     0,   223,   224,     0,   263,     0,    25,
       0,    29,    30,    31,     0,    65,    66,    63,    64,   143,
     147,    45,    33,   164,   174,     0,     0,   166,     0,     0,
     201,    58,   221,   225,     0,     0,     0,   226,     0,     0,
       0,   264,   265,   135,    59,    61,    13,     0,     0,   163,
     168,   162,     0,    57,     0,    16,    46,   227,     0,     0,
       0,   262,   266,    14,     0,     0,    67,   184,     0,     0,
     203,     0,   228,   231,    42,   267,    15,    70,   182,     0,
     202,   204,     0,     0,     0,   236,   237,   238,     0,   234,
     239,   232,     0,   185,   188,     0,    17,    47,    48,    49,
     233,   235,     0,   268,   186,    57,   229,     0,     0,   187,
       0,   189,   205,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   240,   245,   246,
     247,   241,   242,   243,   244,     0,   183,     0,    34,    35,
      36,    37,    38,    39,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   207,   248,   249,   250,   251,
     252,   253,   254,     0,   190,   192,     0,   206,   208,     0,
       0,     0,     0,    69,     0,   194,     0,     0,   196,   213,
     214,   209,   211,    68,   194,   193,     0,   191,   197,     0,
     212,   195,     0,     0,     0,   215,     0,     0,   210,   216,
     198,     0,     0,   217
  };

  const short
  Cube4Parser::yypgoto_[] =
  {
    -398,  -398,  -398,   140,   105,  -165,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,   -83,  -398,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,    19,  -398,  -398,
     241,  -398,  -398,  -398,  -398,  -398,  -170,  -282,  -398,  -398,
    -398,  -126,  -185,  -398,  -398,  -398,  -398,  -398,  -104,  -398,
    -398,  -398,  -398,   293,  -398,  -398,  -398,  -398,   274,  -398,
     275,   276,  -398,  -398,  -398,  -398,     2,  -398,  -398,   227,
    -398,   196,  -398,  -398,  -398,   123,  -184,  -398,   -23,  -398,
    -398,  -398,  -398,   199,  -398,  -398,    78,  -398,   161,  -398,
      40,    75,  -398,    74,  -398,    25,  -398,  -398,   -29,  -120,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -116,  -398,  -106,
    -398,   -98,  -398,   203,  -398,  -398,    12,  -398,  -398,   -74,
    -398,  -119,  -397,  -398,  -111,  -398,  -398,  -398,  -398,  -398,
    -398,    80,  -398,  -398,  -398,    13,  -398,    -2,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,   -47,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,    46,  -398
  };

  const short
  Cube4Parser::yydefgoto_[] =
  {
       0,     6,     7,    37,    38,   141,   111,   112,   113,   114,
     266,   288,   305,   276,   325,    62,    78,    92,   199,   202,
     203,   204,   205,   142,   232,   360,   361,   362,   363,   364,
     365,   366,   157,   300,   143,   144,   233,   277,   326,   327,
      57,   169,   170,   171,   172,   173,   174,   270,   175,   176,
     177,   271,   419,   221,   222,   223,   293,   415,   420,   238,
       2,     3,     8,     9,    20,    21,    30,    31,    32,    39,
      40,    33,    42,    43,    58,    59,    34,    44,    84,    85,
      96,   115,   116,   179,   180,   181,   182,   100,    51,    66,
     102,   147,   118,   119,   225,   226,   227,   145,   146,   189,
     190,   239,   268,   234,   235,    68,    79,   122,   123,   124,
     149,   334,   318,   350,   344,   351,   411,   404,   405,   425,
     417,   418,   125,   126,   294,   309,   310,   377,   394,   395,
     429,   421,   422,   434,   435,   152,   153,   193,   243,   244,
     278,   245,   330,   246,   312,   313,   328,   329,   342,   367,
     368,   369,   370,   371,   372,   373,   374,    81,    82,    93,
     105,   129,   247,   280,   281,   282,   332
  };

  const short
  Cube4Parser::yytable_[] =
  {
      95,   220,   224,   154,    54,   340,    24,   241,   158,   263,
     178,   307,    27,   158,   127,   186,   218,   236,   158,    83,
      97,   274,   443,   230,   430,    64,    65,   216,    87,    88,
     159,   275,   160,    48,   161,    49,   322,   409,   150,   101,
      74,   220,   224,   188,   289,   430,    35,   323,   324,    63,
       1,   120,    10,    36,   178,   269,   218,   121,    22,   216,
     219,    98,    28,   352,    23,   128,   191,   237,    29,   409,
     230,   162,   120,   163,   348,   164,   167,   165,   168,   166,
     214,   167,   215,   168,   290,    26,   216,    41,   217,    75,
      76,    94,   138,     4,     5,   228,   229,     4,     5,    86,
     219,    35,   251,   252,   253,   231,   322,    45,    36,   107,
     108,   109,   110,   132,   133,    94,   138,   323,   324,   228,
     229,    94,   138,   139,   140,    11,    12,    13,    14,    15,
      16,    17,    18,    19,   333,   353,   354,   355,   356,   357,
     358,   359,    94,   138,   139,   140,   134,   135,   320,   308,
     345,    29,   231,   338,   339,   346,   347,   407,   393,   427,
     416,    50,   438,   433,    52,    53,    56,    60,    61,    67,
      69,    70,    72,    73,    77,    83,    80,    89,    90,    91,
      94,   103,   106,   104,   117,   130,   131,   151,   136,   156,
     121,   120,   183,   184,   185,   188,   192,   194,   195,    35,
     196,   198,   200,   206,   201,   208,   207,   403,   209,   211,
     212,   240,   216,   210,   242,   249,   250,    36,   254,   258,
     255,   259,   261,   256,   262,   319,   265,   168,   257,   154,
     236,   424,   272,   283,   284,   279,   285,   286,   295,   296,
     424,   292,   275,   303,   299,   298,   308,   403,   287,   301,
     304,   314,   306,   311,   315,   316,   317,   336,   335,   158,
     337,   376,   343,   378,   379,   375,   380,   381,   382,   383,
     384,   393,   396,   416,   397,   398,   385,   386,   387,   388,
     389,   390,   391,   392,   399,   400,   401,   402,   412,   432,
     441,   433,   409,   414,   440,   297,   413,   423,   197,   410,
      71,    25,   248,   213,   260,    46,   187,    47,   291,   264,
     406,    99,   137,   267,    55,   349,   436,   148,   431,   428,
     408,   321,   442,   439,   273,   331,   341,   302,   155,     0,
       0,     0,     0,   426,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     437
  };

  const short
  Cube4Parser::yycheck_[] =
  {
      83,   186,   186,   123,    11,    11,    15,   192,    12,    10,
     136,   293,    12,    12,    54,    10,   186,    39,    12,    27,
      28,   112,    53,   188,   421,    48,    49,    90,    75,    76,
      29,   122,    31,    31,    33,    33,   112,   100,   121,    86,
      63,   226,   226,    37,    38,   442,   108,   123,   124,    47,
      14,    40,     0,   115,   180,   240,   226,    46,     5,    90,
     186,    69,    62,   345,     5,   105,   149,    89,    68,   100,
     235,    70,    40,    72,    42,    74,    80,    76,    82,    78,
      84,    80,    86,    82,   268,    25,    90,    64,    92,    64,
      65,   116,   117,   106,   107,   120,   121,   106,   107,    74,
     226,   108,     7,     8,     9,   188,   112,    26,   115,   133,
     134,   135,   136,     3,     4,   116,   117,   123,   124,   120,
     121,   116,   117,   118,   119,    16,    17,    18,    19,    20,
      21,    22,    23,    24,   318,   125,   126,   127,   128,   129,
     130,   131,   116,   117,   118,   119,     3,     4,    47,    48,
     335,    68,   235,     3,     4,    59,    60,    49,    50,    43,
      44,    88,    51,    52,     5,     5,    66,    63,   113,    98,
      67,    65,     5,    10,   113,    27,   104,     5,    10,   113,
     116,     5,     5,    10,    35,     5,     5,   102,    10,   132,
      46,    40,     5,     5,     5,    37,    10,    99,     5,   108,
      10,   138,    32,    71,   139,    75,    73,   392,    77,    81,
      83,    10,    90,    79,    58,     3,    10,   115,    10,    93,
      85,    36,     5,    87,     5,   308,   109,    82,    91,   349,
      39,   415,   103,    11,    30,    56,    34,     5,     5,     5,
     424,    94,   122,     5,   137,    10,    48,   432,   110,    55,
     111,     5,    95,    13,    10,     5,    11,     5,    10,    12,
       5,    41,    57,     5,     5,   348,     5,     5,     5,     5,
       5,    50,    61,    44,    61,    61,    10,    10,    10,    10,
      10,    10,    10,    10,    61,    61,    61,    61,    10,    10,
      10,    52,   100,    96,    45,   276,   101,    97,   158,   403,
      59,     8,   197,   180,   226,    31,   145,    31,   268,   235,
     393,    84,   116,   238,    39,   344,   432,   118,   424,   417,
     394,   309,   441,   434,   244,   312,   328,   281,   125,    -1,
      -1,    -1,    -1,   416,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     433
  };

  const short
  Cube4Parser::yystos_[] =
  {
       0,    14,   200,   201,   106,   107,   141,   142,   202,   203,
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
     204,   205,     5,     5,    15,   203,    25,    12,    62,    68,
     206,   207,   208,   211,   216,   108,   115,   143,   144,   209,
     210,    64,   212,   213,   217,    26,   208,   211,   216,   216,
      88,   228,     5,     5,    11,   210,    66,   180,   214,   215,
      63,   113,   155,   216,   228,   228,   229,    98,   245,    67,
      65,   180,     5,    10,   228,   245,   245,   113,   156,   246,
     104,   297,   298,    27,   218,   219,   245,   297,   297,     5,
      10,   113,   157,   299,   116,   163,   220,    28,    69,   219,
     227,   297,   230,     5,    10,   300,     5,   133,   134,   135,
     136,   146,   147,   148,   149,   221,   222,    35,   232,   233,
      40,    46,   247,   248,   249,   262,   263,    54,   105,   301,
       5,     5,     3,     4,     3,     4,    10,   221,   117,   118,
     119,   145,   163,   174,   175,   237,   238,   231,   233,   250,
     163,   102,   275,   276,   249,   263,   132,   172,    12,    29,
      31,    33,    70,    72,    74,    76,    78,    80,    82,   181,
     182,   183,   184,   185,   186,   188,   189,   190,   191,   223,
     224,   225,   226,     5,     5,     5,    10,   238,    37,   239,
     240,   163,    10,   277,    99,     5,    10,   143,   138,   158,
      32,   139,   159,   160,   161,   162,    71,    73,    75,    77,
      79,    81,    83,   225,    84,    86,    90,    92,   186,   191,
     192,   193,   194,   195,   226,   234,   235,   236,   120,   121,
     145,   163,   164,   176,   243,   244,    39,    89,   199,   241,
      10,   192,    58,   278,   279,   281,   283,   302,   144,     3,
      10,     7,     8,     9,    10,    85,    87,    91,    93,    36,
     236,     5,     5,    10,   243,   109,   150,   241,   242,   192,
     187,   191,   103,   281,   112,   122,   153,   177,   280,    56,
     303,   304,   305,    11,    30,    34,     5,   110,   151,    38,
     226,   240,    94,   196,   264,     5,     5,   177,    10,   137,
     173,    55,   305,     5,   111,   152,    95,   187,    48,   265,
     266,    13,   284,   285,     5,    10,     5,    11,   252,   163,
      47,   266,   112,   123,   124,   154,   178,   179,   286,   287,
     282,   285,   306,   226,   251,    10,     5,     5,     3,     4,
      11,   287,   288,    57,   254,   192,    59,    60,    42,   248,
     253,   255,   187,   125,   126,   127,   128,   129,   130,   131,
     165,   166,   167,   168,   169,   170,   171,   289,   290,   291,
     292,   293,   294,   295,   296,   163,    41,   267,     5,     5,
       5,     5,     5,     5,     5,    10,    10,    10,    10,    10,
      10,    10,    10,    50,   268,   269,    61,    61,    61,    61,
      61,    61,    61,   192,   257,   258,   163,    49,   269,   100,
     198,   256,    10,   101,    96,   197,    44,   260,   261,   192,
     198,   271,   272,    97,   226,   259,   163,    43,   261,   270,
     272,   259,    10,    52,   273,   274,   257,   163,    51,   274,
      45,    10,   271,    53
  };

  const short
  Cube4Parser::yyr1_[] =
  {
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     148,   149,   149,   150,   151,   152,   153,   154,   155,   155,
     156,   156,   157,   157,   158,   158,   159,   159,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   202,   203,   203,   204,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   206,   206,   206,
     206,   207,   207,   208,   209,   209,   210,   210,   211,   212,
     212,   213,   214,   214,   215,   215,   217,   216,   218,   218,
     218,   219,   220,   220,   221,   221,   222,   222,   222,   222,
     223,   223,   224,   224,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   226,   227,   229,   230,   231,
     228,   232,   232,   233,   234,   234,   235,   235,   236,   236,
     236,   236,   236,   236,   236,   237,   237,   238,   238,   238,
     238,   239,   239,   239,   240,   241,   241,   242,   242,   243,
     243,   243,   243,   244,   244,   246,   245,   247,   247,   248,
     248,   250,   251,   249,   252,   252,   253,   253,   254,   254,
     256,   255,   257,   258,   259,   259,   260,   260,   261,   262,
     262,   264,   263,   265,   265,   267,   266,   268,   268,   270,
     269,   271,   271,   272,   272,   273,   273,   274,   275,   275,
     277,   276,   278,   278,   279,   279,   280,   280,   282,   281,
     283,   284,   284,   285,   286,   286,   287,   287,   287,   288,
     288,   289,   289,   289,   289,   289,   289,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   297,   299,   298,   300,
     300,   302,   301,   303,   303,   304,   304,   306,   305
  };

  const signed char
  Cube4Parser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     0,     1,     4,
       2,     4,     2,     2,     2,     2,     2,     2,     2,     2,
       5,     2,     3,     1,     2,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     6,     5,     5,
       4,     1,     2,     3,     1,     2,     1,     1,     3,     0,
       1,     3,     0,     1,     1,     2,     0,     6,     1,     2,
       2,     5,     0,     1,     0,     2,     1,     1,     1,     1,
       0,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     0,     0,     0,
       9,     1,     2,     5,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     4,     4,     3,     0,     2,     0,     2,     1,
       1,     1,     1,     1,     2,     0,     7,     1,     1,     1,
       2,     0,     0,    12,     0,     2,     0,     1,     0,     2,
       0,     7,     1,     4,     0,     2,     1,     2,     5,     1,
       2,     0,     8,     1,     2,     0,     8,     1,     2,     0,
       7,     1,     2,     1,     1,     1,     2,     5,     0,     1,
       0,     4,     0,     1,     1,     2,     1,     2,     0,     7,
       1,     1,     2,     3,     1,     2,     1,     1,     1,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     0,     1,     0,     4,     0,
       2,     0,     6,     0,     1,     1,     2,     0,     5
  };


#if CUBEPARSERDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Cube4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"false\"",
  "\"true\"", "\"attribute value\"", "\"error\"", "\"plus\"", "\"minus\"",
  "\"aggr\"", "\">\"", "\"/>\"", "\"<attr\"", "\"<dim\"", "\"<?xml\"",
  "\"?>\"", "\"<cube version=\\\"4.0\\\"\"",
  "\"<cube version=\\\"4.1\\\"\"", "\"<cube version=\\\"4.2\\\"\"",
  "\"<cube version=\\\"4.3\\\"\"", "\"<cube version=\\\"4.4\\\"\"",
  "\"<cube version=\\\"4.5\\\"\"", "\"<cube version=\\\"4.7\\\"\"",
  "\"<cube version=\\\"3.0\\\"\"", "\"<cube version=\\\"\"",
  "CUBE_OPEN_NOT_SUPPORTED", "\"</cube>\"", "\"<metric\"", "\"</metric>\"",
  "\"<cubepl\"", "\"</cubepl>\"", "\"<cubeplinit>\"", "\"</cubeplinit>\"",
  "\"<cubeplaggr\"", "\"</cubeplaggr>\"", "\"<region\"", "\"</region>\"",
  "\"<cnode\"", "\"</cnode>\"", "\"<parameter\"", "\"<systemtreenode\"",
  "\"</systemtreenode>\"", "\"<locationgroup\"", "\"</locationgroup>\"",
  "\"<location\"", "\"</location>\"", "\"<machine\"", "\"</machine>\"",
  "\"<node\"", "\"</node>\"", "\"<process\"", "\"</process>\"",
  "\"<thread\"", "\"</thread>\"", "\"<matrix\"", "\"</matrix>\"",
  "\"<row\"", "\"</row>\"", "\"<cart\"", "\"</cart>\"", "\"<coord\"",
  "\"</coord>\"", "\"<doc>\"", "\"</doc>\"", "\"<mirrors>\"",
  "\"</mirrors>\"", "\"<murl>\"", "\"</murl>\"", "\"<metrics\"",
  "\"</metrics>\"", "\"<disp_name>\"", "\"</disp_name>\"",
  "\"<uniq_name>\"", "\"</uniq_name>\"", "\"<dtype>\"", "\"</dtype>\"",
  "\"<uom>\"", "\"</uom>\"", "\"<val>\"", "\"</val>\"", "\"<url>\"",
  "\"</url>\"", "\"<descr>\"", "\"</descr>\"", "\"<paradigm>\"",
  "\"</paradigm>\"", "\"<role>\"", "\"</role>\"", "\"<program\"",
  "\"</program>\"", "\"<name>\"", "\"</name>\"", "\"<mangled_name>\"",
  "\"</mangled_name>\"", "\"<class>\"", "\"</class>\"", "\"<type>\"",
  "\"</type>\"", "\"<system\"", "\"</system>\"", "\"<rank>\"",
  "\"</rank>\"", "\"<topologies>\"", "\"</topologies>\"", "\"<severity>\"",
  "\"</severity>\"", "\"attribute name version\"",
  "\"attribute name encoding\"", "\"attribute name key\"",
  "\"attribute name partype\"", "\"attribute name parkey\"",
  "\"attribute name parvalue\"", "\"attribute name name\"",
  "\"attribute name title\"", "\"attribute name file\"",
  "\"attribute name value\"", "\"attribute name id\"",
  "\"attribute name mod\"", "\"attribute name begin\"",
  "\"attribute name end\"", "\"attribute name line\"",
  "\"attribute name calleeid\"", "\"attribute name ndims\"",
  "\"attribute name size\"", "\"attribute name periodic\"",
  "\"attribute name locId\"", "\"attribute name lgId\"",
  "\"attribute name stnId\"", "\"attribute name thrdId\"",
  "\"attribute name procId\"", "\"attribute name nodeId\"",
  "\"attribute name machId\"", "\"attribute name metricId\"",
  "\"attribute name type\"", "\"attribute name viztype\"",
  "\"attribute name convertible\"", "\"attribute name cacheable\"",
  "\"attribute name cnodeId\"", "\"attribute name rowwise\"",
  "\"attribute name cubeplaggrtype\"", "$accept", "version_attr",
  "encoding_attr", "key_attr", "value_attr", "mod_attr",
  "metric_type_attr", "metric_viz_type_attr", "metric_convertible_attr",
  "metric_cacheable_attr", "cnode_par_type_attr", "cnode_par_key_attr",
  "cnode_par_value_attr", "cart_name_attr", "dim_name_attr",
  "metrics_title_attr", "calltree_title_attr", "systemtree_title_attr",
  "expression_attr", "expression_aggr_attr", "expression_aggr_attr_plus",
  "expression_aggr_attr_minus", "expression_aggr_attr_aggr", "id_attr",
  "calleeid_attr", "locid_attr", "lgid_attr", "stnid_attr", "thrdid_attr",
  "procid_attr", "nodeid_attr", "machid_attr", "metricid_attr",
  "cnodeid_attr", "begin_attr", "end_attr", "line_attr", "ndims_attr",
  "size_attr", "periodic_attr", "murl_tag", "disp_name_tag",
  "uniq_name_tag", "dtype_tag", "uom_tag", "val_tag", "url_tag",
  "descr_tag_opt", "expression_tag", "expression_init_tag",
  "expression_aggr_tag", "descr_tag", "name_tag", "mangled_name_tag",
  "paradigm_tag", "role_tag", "class_tag", "type_tag", "rank_tag",
  "parameter_tag", "document", "xml_tag", "xml_attributes",
  "xml_attribute", "cube_tag", "cube_begin", "cube_content", "attr_tags",
  "attr_tag", "attr_attributes", "attr_attribute", "doc_tag",
  "mirrors_tag_attr", "mirrors_tag", "murl_tags_attr", "murl_tags",
  "metrics_tag", "$@1", "metric_tag", "metric_begin", "id_attrs",
  "metric_attrs", "metric_attr", "tags_of_metric_attr", "tags_of_metric",
  "tag_of_metric", "generic_attr_tag", "metric_end", "program_tag", "$@2",
  "$@3", "$@4", "region_tags", "region_tag", "tags_of_region_attr",
  "tags_of_region", "tag_of_region", "region_attributes",
  "region_attribute", "cnode_tag", "cnode_begin", "cnode_parameters",
  "cnode_attr_tags", "cnode_attribute", "cnode_attributes", "system_tag",
  "$@5", "systemtree_tags", "flexsystemtree_tags", "systemtree_tag", "$@6",
  "$@7", "systree_attr_tags", "systemtree_sub_tags", "location_group_tags",
  "location_group_tag", "$@8", "loc_tags", "loc_tag", "lg_attr_tags",
  "location_tags", "location_tag", "machine_tags", "machine_tag", "$@9",
  "node_tags", "node_tag", "$@10", "process_tags", "process_tag", "$@11",
  "tags_of_process", "tag_of_process", "thread_tags", "thread_tag",
  "topologies_tag_attr", "topologies_tag", "$@12", "cart_tags_attr",
  "cart_tags", "cart_attrs", "cart_tag", "$@13", "cart_open", "dim_tags",
  "dim_tag", "dim_attributes", "dim_attribute", "coord_tags", "coord_tag",
  "coord_tag_loc", "coord_tag_lg", "coord_tag_stn", "coord_tag_thrd",
  "coord_tag_proc", "coord_tag_node", "coord_tag_mach", "severity_tag",
  "severity_part", "$@14", "matrix_tags", "matrix_tag", "$@15",
  "row_tags_attr", "row_tags", "row_tag", "$@16", YY_NULLPTR
  };
#endif


#if CUBEPARSERDEBUG
  const short
  Cube4Parser::yyrline_[] =
  {
       0,   306,   306,   313,   320,   327,   334,   341,   349,   357,
     363,   371,   377,   387,   396,   405,   414,   424,   432,   434,
     441,   443,   451,   453,   461,   463,   473,   475,   477,   482,
     492,   503,   515,   524,   536,   545,   554,   565,   574,   583,
     592,   604,   613,   624,   632,   640,   648,   658,   670,   676,
     687,   697,   704,   710,   717,   724,   731,   737,   738,   743,
     751,   759,   770,   777,   787,   795,   803,   812,   821,   828,
     845,   890,   896,   913,   914,   918,   919,   925,   932,   936,
     940,   944,   948,   952,   956,   960,   964,   970,   971,   972,
     973,   979,   980,   984,  1004,  1005,  1009,  1010,  1016,  1018,
    1019,  1023,  1026,  1027,  1031,  1032,  1041,  1040,  1128,  1129,
    1130,  1136,  1237,  1238,  1242,  1243,  1246,  1247,  1248,  1249,
    1252,  1253,  1257,  1258,  1262,  1263,  1264,  1265,  1266,  1267,
    1268,  1269,  1270,  1271,  1272,  1277,  1305,  1317,  1321,  1326,
    1316,  1444,  1445,  1449,  1523,  1524,  1528,  1529,  1533,  1534,
    1535,  1536,  1537,  1538,  1539,  1545,  1546,  1550,  1551,  1552,
    1553,  1557,  1558,  1559,  1717,  1774,  1775,  1780,  1782,  1787,
    1788,  1789,  1790,  1794,  1795,  1802,  1801,  1820,  1822,  1826,
    1827,  1832,  1836,  1831,  1907,  1909,  1918,  1920,  1923,  1925,
    1930,  1930,  1985,  1989,  1992,  1994,  2000,  2001,  2004,  2062,
    2063,  2067,  2067,  2087,  2088,  2092,  2092,  2112,  2113,  2117,
    2117,  2145,  2146,  2149,  2150,  2154,  2155,  2159,  2192,  2193,
    2197,  2197,  2203,  2204,  2208,  2209,  2213,  2214,  2219,  2218,
    2246,  2253,  2254,  2258,  2275,  2276,  2280,  2281,  2282,  2285,
    2286,  2299,  2300,  2301,  2302,  2303,  2304,  2305,  2312,  2333,
    2354,  2376,  2397,  2418,  2440,  2466,  2467,  2470,  2470,  2480,
    2482,  2487,  2487,  2510,  2511,  2515,  2516,  2520,  2520
  };

  void
  Cube4Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Cube4Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // CUBEPARSERDEBUG

  Cube4Parser::symbol_kind_type
  Cube4Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const unsigned char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      25,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139
    };
    // Last valid token kind.
    const int code_max = 1137;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // cubeparser
#line 3825 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"

#line 2558 "../../cubelib/build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
 /*** Additional Code ***/


void cubeparser::Cube4Parser::error(const Cube4Parser::location_type& l,
                            const std::string& m)
{
   if (strstr(m.c_str(),"expecting <?xml")!=NULL) {
     driver.error_just_message("The cube file is probably empty or filled with wrong content. The file has ended before the header of cube started. \n");
    }
   if (strstr(m.c_str()," expecting </row>")!=NULL) {
     driver.error_just_message("One of the possible reasons is \n    1) that the severity value is malformed. CUBE expects the \"double\" value in C_LOCALE with dot instead of comma;. \n    2) that the CUBE file is not properly ended. Probably the writing of CUBE file was interrupted.");
    }
   if (strstr(m.c_str()," expecting <matrix")!=NULL ||
        (strstr(m.c_str()," expecting <severity>")!=NULL) ) {
     driver.error_just_message("The cube file has probably a proper structure, but doesn't contain any severity values.");
    }
   if (strstr(m.c_str()," expecting <metric")!=NULL) {
     driver.error_just_message("The cube file doesn't contain any information about metric dimension.");
    }
   if (strstr(m.c_str()," expecting <region")!=NULL) {
     driver.error_just_message("The cube file doesn't contain any information about program dimension.");
    }

    // Cube3 compatibility mode
   if (strstr(m.c_str()," expecting <machine")!=NULL) {
     driver.error_just_message("The cube file doesn't contain any information about system dimension.");
    }
   if (strstr(m.c_str()," expecting <thread")!=NULL) {
     driver.error_just_message("The system dimension of the cube file is malformed. It contains a process without any threads.");
    }
   if (strstr(m.c_str()," expecting <process")!=NULL) {
     driver.error_just_message("The system dimension of the cube file is malformed. It contains a node without any processes.");
    }
   if (strstr(m.c_str()," expecting <node")!=NULL) {
     driver.error_just_message("The system dimension of the cube file is malformed. It contains a machine without any computing nodes.");
    }
    driver.error(l, m);

}
