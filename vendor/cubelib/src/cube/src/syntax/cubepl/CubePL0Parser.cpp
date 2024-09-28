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
#define yylex   cubeplparserlex



#include "CubePL0Parser.h"

// Second part of user prologue.
#line 250 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"

#include <config.h>


#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePL0Scanner.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>

using namespace std;
using namespace cube;

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubePL0ParseContext.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex CubePl0Lexer.lex

// Workaround for Sun Studio C++ compilers on Solaris
#if defined(__SVR4) &&  defined(__SUNPRO_CC)
  #include <ieeefp.h>

  #define isinf(x)  (fpclass(x) == FP_NINF || fpclass(x) == FP_PINF)
  #define isnan(x)  isnand(x)
#endif


#line 89 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"



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
#if CUBEPLPARSERDEBUG

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

#else // !CUBEPLPARSERDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !CUBEPLPARSERDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace cubeplparser {
#line 182 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"

  /// Build a parser object.
  CubePL0Parser::CubePL0Parser (class CubePL0ParseContext& parseContext_yyarg, class CubePL0Scanner& CubePl0Lexer_yyarg)
#if CUBEPLPARSERDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      parseContext (parseContext_yyarg),
      CubePl0Lexer (CubePl0Lexer_yyarg)
  {}

  CubePL0Parser::~CubePL0Parser ()
  {}

  CubePL0Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  CubePL0Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  CubePL0Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  CubePL0Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}


  template <typename Base>
  CubePL0Parser::symbol_kind_type
  CubePL0Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  CubePL0Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  CubePL0Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  CubePL0Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  CubePL0Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  CubePL0Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  CubePL0Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  CubePL0Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  CubePL0Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  CubePL0Parser::symbol_kind_type
  CubePL0Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  CubePL0Parser::symbol_kind_type
  CubePL0Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  CubePL0Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  CubePL0Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  CubePL0Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  CubePL0Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  CubePL0Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  CubePL0Parser::symbol_kind_type
  CubePL0Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  CubePL0Parser::stack_symbol_type::stack_symbol_type ()
  {}

  CubePL0Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  CubePL0Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  CubePL0Parser::stack_symbol_type&
  CubePL0Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  CubePL0Parser::stack_symbol_type&
  CubePL0Parser::stack_symbol_type::operator= (stack_symbol_type& that)
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
  CubePL0Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if CUBEPLPARSERDEBUG
  template <typename Base>
  void
  CubePL0Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
  CubePL0Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  CubePL0Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  CubePL0Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if CUBEPLPARSERDEBUG
  std::ostream&
  CubePL0Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  CubePL0Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  CubePL0Parser::debug_level_type
  CubePL0Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  CubePL0Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // CUBEPLPARSERDEBUG

  CubePL0Parser::state_type
  CubePL0Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  CubePL0Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  CubePL0Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  CubePL0Parser::operator() ()
  {
    return parse ();
  }

  int
  CubePL0Parser::parse ()
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
#line 140 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
{
    // initialize the initial location object
}

#line 527 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"


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
  case 2: // document: "<cubepl>" expression "</cubepl>"
#line 302 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                parseContext.result = parseContext._stack.top();
                parseContext._stack.pop();
                }
                parseContext.syntax_ok &= true;
        }
#line 672 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 3: // document: "<cubepl>" "</cubepl>"
#line 311 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
        {
                parseContext.syntax_ok &= true;
        }
#line 680 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 19: // enclosed_expression: "(" expression ")"
#line 336 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new EncapsulationEvaluation(_arg1) );
                }
                parseContext.syntax_ok &= true;
            }
#line 694 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 20: // absolute_value: "|" expression "|"
#line 346 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _abs = new AbsEvaluation();
                    _abs->addArgument(_arg1);
                    parseContext._stack.push( _abs );
                }
                parseContext.syntax_ok &= true;
            }
#line 710 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 21: // sum: expression "+" expression
#line 359 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new PlusEvaluation(_arg1, _arg2) );
                }
                parseContext.syntax_ok &= true;
            }
#line 726 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 22: // subtract: expression "-" expression
#line 372 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new MinusEvaluation(_arg1, _arg2) );
                }
                parseContext.syntax_ok &= true;
            }
#line 742 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 23: // division: expression "/" expression
#line 386 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new DivideEvaluation(_arg1, _arg2) );
                }
                parseContext.syntax_ok &= true;
            }
#line 758 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 24: // multiplication: expression "*" expression
#line 399 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new MultEvaluation(_arg1, _arg2) );
                }
                parseContext.syntax_ok &= true;
            }
#line 774 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 25: // power: expression "^" expression
#line 415 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * power = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * base = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new PowerEvaluation(base, power) );
                }
                parseContext.syntax_ok &= true;
            }
#line 790 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 26: // negation: "-" expression
#line 427 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * arg = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new NegativeEvaluation(arg) );
                }
                parseContext.syntax_ok &= true;
            }
#line 804 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 40: // enclosed_boolean_expression: "(" boolean_expression ")"
#line 457 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                            GeneralEvaluation * _arg1 = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new EncapsulationEvaluation(_arg1) );
                        }
                        parseContext.syntax_ok &= true;
                    }
#line 818 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 41: // enclosed_boolean_expression: "not" "(" boolean_expression ")"
#line 467 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                            GeneralEvaluation * _arg1 = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new NotEvaluation(_arg1) );
                        }
                        parseContext.syntax_ok &= true;
                    }
#line 832 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 42: // and_expression: boolean_expression "and" boolean_expression
#line 478 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new AndEvaluation(_arg1, _arg2) );

                }
                parseContext.syntax_ok &= true;
            }
#line 849 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 43: // or_expression: boolean_expression "or" boolean_expression
#line 491 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new OrEvaluation(_arg1, _arg2) );

                }
                parseContext.syntax_ok &= true;
            }
#line 866 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 44: // xor_expression: boolean_expression "xor" boolean_expression
#line 505 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new XorEvaluation(_arg1, _arg2) );

                }
                parseContext.syntax_ok &= true;
            }
#line 883 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 45: // true_expression: "true"
#line 518 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._stack.push( new ConstantEvaluation(1) );
                }
                parseContext.syntax_ok &= true;
            }
#line 895 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 46: // false_expression: "false"
#line 526 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._stack.push( new ConstantEvaluation(0) );
                }
                parseContext.syntax_ok &= true;
            }
#line 907 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 47: // equality: expression "==" expression
#line 535 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new EqualEvaluation(_arg1, _arg2) );

                }
                parseContext.syntax_ok &= true;
            }
#line 924 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 48: // not_equality: expression "!=" expression
#line 549 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new NotEqualEvaluation(_arg1, _arg2) );
                }
                parseContext.syntax_ok &= true;
            }
#line 940 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 49: // bigger: expression ">" expression
#line 563 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new BiggerEvaluation(_arg1, _arg2) );
                }
                parseContext.syntax_ok &= true;
            }
#line 956 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 50: // smaller: expression "<" expression
#line 576 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new SmallerEvaluation(_arg1, _arg2) );
                }
                parseContext.syntax_ok &= true;
            }
#line 972 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 51: // halfbigger: expression ">=" expression
#line 590 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new HalfBiggerEvaluation(_arg1, _arg2) );
                }
                parseContext.syntax_ok &= true;
            }
#line 988 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 52: // halfsmaller: expression "<=" expression
#line 604 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new HalfSmallerEvaluation(_arg1, _arg2) );
                }
                parseContext.syntax_ok &= true;
            }
#line 1004 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 56: // string_equality: string_expression "eq" string_expression
#line 627 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                        GeneralEvaluation * _value2 =   parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation * _value1 =   parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new StringEqualityEvaluation(_value1, _value2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1020 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 57: // string_semi_equality: string_expression "seq" string_expression
#line 640 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                        GeneralEvaluation * _value2 =   parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation * _value1 =   parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new StringSemiEqualityEvaluation(_value1, _value2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1036 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 58: // regexp: string_expression "=~" regexp_expression
#line 652 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                        string _regexp =  parseContext.strings_stack.top();
                        parseContext.strings_stack.pop();
                        GeneralEvaluation * _value =   parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new RegexEvaluation(_value, new StringConstantEvaluation(_regexp) ) );
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1052 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 59: // regexp_expression: REGEXP_STRING
#line 667 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    string _tmp = parseContext.str.str();
            int _result = 0;
            try
            {
                std::regex self_regex( _tmp );
            }
            catch ( const std::regex_error& e )
            {
                _result=-1;
            }
                    if (_result != 0 )
                    {
                        parseContext.syntax_ok &= false;
                    }
                    if (_result==0 && !parseContext.test_modus)
                    {
                        parseContext.strings_stack.push( _tmp );
                        parseContext.str.str("");
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1079 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 63: // quoted_string: QUOTED_STRING
#line 701 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                    parseContext._stack.push( new StringConstantEvaluation( parseContext.str.str() ));
                    parseContext.str.str("");
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1092 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 66: // lowercase: "lowercase" "(" string_expression ")"
#line 717 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                            GeneralEvaluation * _arg1 = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new LowerCaseEvaluation(_arg1) );
                        }
                        parseContext.syntax_ok &= true;
                    }
#line 1106 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 67: // uppercase: "uppercase" "(" string_expression ")"
#line 728 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                            GeneralEvaluation * _arg1 = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new UpperCaseEvaluation(_arg1) );
                        }
                        parseContext.syntax_ok &= true;
                    }
#line 1120 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 70: // one_variable_function: function_name "(" expression ")"
#line 744 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                                    parseContext._stack.pop();
                                    parseContext.function_call.top()->addArgument( _arg1 );
                                    parseContext._stack.push( parseContext.function_call.top() );
                                    parseContext.function_call.pop();
                        }
                        parseContext.syntax_ok &= true;
                }
#line 1136 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 71: // function_name: "sqrt"
#line 758 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new SqrtEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1148 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 72: // function_name: "sin"
#line 766 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new SinEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1160 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 73: // function_name: "asin"
#line 774 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new ASinEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1172 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 74: // function_name: "cos"
#line 782 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new CosEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1184 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 75: // function_name: "acos"
#line 790 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new ACosEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1196 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 76: // function_name: "exp"
#line 798 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new ExpEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1208 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 77: // function_name: "log"
#line 806 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new LnEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1220 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 78: // function_name: "tan"
#line 814 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new TanEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1232 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 79: // function_name: "atan"
#line 822 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new ATanEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1244 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 80: // function_name: "random"
#line 830 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new RandomEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1256 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 81: // function_name: "abs"
#line 838 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new AbsEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1268 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 82: // function_name: "sgn"
#line 846 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new SgnEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1280 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 83: // function_name: "pos"
#line 854 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new PosEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1292 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 84: // function_name: "neg"
#line 862 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new NegEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1304 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 85: // function_name: "floor"
#line 870 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new FloorEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1316 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 86: // function_name: "ceil"
#line 878 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new CeilEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1328 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 87: // two_variables_function: function2_name "(" expression "," expression ")"
#line 889 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                        if (!parseContext.test_modus)
                        {
                                    GeneralEvaluation * _arg2 = parseContext._stack.top();
                                    parseContext._stack.pop();
                                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                                    parseContext._stack.pop();
                                    parseContext.function_call.top()->addArgument( _arg1 );
                                    parseContext.function_call.top()->addArgument( _arg2 );
                                    parseContext._stack.push( parseContext.function_call.top() );
                                    parseContext.function_call.pop();
                        }
                        parseContext.syntax_ok &= true;
                }
#line 1347 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 88: // function2_name: "min"
#line 905 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new MinEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1359 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 89: // function2_name: "max"
#line 913 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new MaxEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1371 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 90: // constant: CONSTANT
#line 924 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
               if (!parseContext.test_modus)
               {
                double _value = atof( parseContext.value.c_str());
                parseContext._stack.push( new ConstantEvaluation(_value));
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
            }
#line 1385 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 93: // context_metric: "metric::" METRIC_NAME "(" ")"
#line 940 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.value);
                if (_met != NULL)
                {
                    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met ));
                }
                else
                {
                    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "() will be always 0" << endl;
                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1408 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 94: // context_metric: "metric::" METRIC_NAME "(" calculationFlavourModificator ")"
#line 959 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.value);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met, mod ));
                }
                else
                {
                    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "( ?  ) will be always 0" << endl;
                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1433 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 95: // context_metric: "metric::" METRIC_NAME "(" calculationFlavourModificator "," calculationFlavourModificator ")"
#line 980 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.value);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();

                    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met, mod1, mod2));
                }
                else
                {
                    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "( ?, ? ) will be always 0" << endl;
                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1461 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 96: // fixed_metric: "metric::fixed::" METRIC_NAME "(" ")"
#line 1007 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.value);
                if (_met != NULL)
                {
                    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_FULL_AGGR,  parseContext.cube, _met ));
                }
                else
                {
                    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "() will be always 0" << endl;
                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1484 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 97: // fixed_metric: "metric::fixed::" METRIC_NAME "(" calculationFlavourModificator ")"
#line 1026 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.value);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_AGGR_SYS,  parseContext.cube, _met, mod ));
                }
                else
                {
                    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "( "; mod->print(); cout << " ) will be always 0" << endl;


                    delete mod;

                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1515 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 98: // fixed_metric: "metric::fixed::" METRIC_NAME "(" calculationFlavourModificator "," calculationFlavourModificator ")"
#line 1053 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.value);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();

                    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_NO_AGGR,  parseContext.cube, _met, mod1, mod2));
                }
                else
                {
                    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "( "; mod1->print(); cout << ","; mod2->print(); cout <<") will be always 0" << endl;


                    delete mod2;
                    delete mod1;

                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1552 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 99: // calculationFlavourModificator: "i"
#line 1091 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                                {
                                    if (!parseContext.test_modus)
                                    {
                                        parseContext.calcFlavorModificators.push(new CalcFlavorModificatorIncl());
                                    }
                                    parseContext.syntax_ok &= true;
                                }
#line 1564 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 100: // calculationFlavourModificator: "e"
#line 1099 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                                {
                                    if (!parseContext.test_modus)
                                    {
                                        parseContext.calcFlavorModificators.push(new CalcFlavorModificatorExcl());
                                    }
                                    parseContext.syntax_ok &= true;
                                }
#line 1576 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 101: // calculationFlavourModificator: SAME_MODIFICATOR
#line 1107 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                                {
                                    if (!parseContext.test_modus)
                                    {
                                        parseContext.calcFlavorModificators.push(new CalcFlavorModificatorSame());
                                    }
                                    parseContext.syntax_ok &= true;
                                }
#line 1588 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 102: // lambda_calcul: lambda_start list_of_statements return_expression "}"
#line 1118 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {

                    LambdaCalculEvaluation * _l_calc = new LambdaCalculEvaluation();

                    GeneralEvaluation * return_expr = parseContext._stack.top();
                    parseContext._stack.pop();

                    int _num_of_statements = parseContext._number_of_statements.top();
                    parseContext._number_of_statements.pop();

                    vector<GeneralEvaluation*> _tmp_statements;
                    for (int i=0; i<_num_of_statements; i++)
                    {
                        _tmp_statements.push_back( parseContext._statements.top());
                        parseContext._statements.pop();
                    }
                    for (int i=_num_of_statements-1; i>=0; i--)
                    {
                        _l_calc->addArgument( _tmp_statements[i]);
                    }
                    _l_calc->addArgument( return_expr);
                    parseContext._stack.push(_l_calc);
                    // create lambda calculation using number_of_statements.
                }
                parseContext.syntax_ok &= true;
            }
#line 1621 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 104: // lambda_start: "{"
#line 1150 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._number_of_statements.push(0);
                }
                parseContext.syntax_ok &= true;
            }
#line 1633 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 107: // statement: if_statement
#line 1167 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
           {
                if (!parseContext.test_modus)
                {
                    int _tmp = parseContext._number_of_statements.top();
                    parseContext._number_of_statements.pop();
                    _tmp++;
                    parseContext._number_of_statements.push(_tmp);
                }
                parseContext.syntax_ok &= true;
            }
#line 1648 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 108: // statement: while_statement
#line 1178 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
           {
                if (!parseContext.test_modus)
                {
                    int _tmp = parseContext._number_of_statements.top();
                    parseContext._number_of_statements.pop();
                    _tmp++;
                    parseContext._number_of_statements.push(_tmp);
                }
                parseContext.syntax_ok &= true;
            }
#line 1663 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 109: // statement: assignment
#line 1189 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
           {
                if (!parseContext.test_modus)
                {
                    int _tmp = parseContext._number_of_statements.top();
                    parseContext._number_of_statements.pop();
                    _tmp++;
                    parseContext._number_of_statements.push(_tmp);
                }
                parseContext.syntax_ok &= true;
            }
#line 1678 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 113: // simple_if_statement: if_condition enclosed_list_of_statements
#line 1207 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    int _num_of_statements = parseContext._number_of_statements.top();
                    parseContext._number_of_statements.pop();

                    vector<GeneralEvaluation*> _tmp_statements;
                    for (int i=0; i<_num_of_statements; i++)
                    {
                        _tmp_statements.push_back( parseContext._statements.top());
                        parseContext._statements.pop();
                    }
                    GeneralEvaluation * _condition = parseContext._stack.top();
                    parseContext._stack.pop();

                    ShortIfEvaluation * _s_if_calc = new ShortIfEvaluation(_condition);

                    for (int i=_num_of_statements-1; i>=0; i--)
                    {
                        _s_if_calc->addArgument( _tmp_statements[i]);
                    }
                    parseContext._statements.push(_s_if_calc);
                }
                parseContext.syntax_ok &= true;
            }
#line 1708 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 114: // full_if_statement: if_condition enclosed_list_of_statements else_enclosed_list_of_statements
#line 1234 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    int _num_of_false_statements = parseContext._number_of_statements.top();
                    parseContext._number_of_statements.pop();
                    int _num_of_true_statements = parseContext._number_of_statements.top();
                    parseContext._number_of_statements.pop();

                    vector<GeneralEvaluation*> _tmp_false_statements;
                    for (int i=0; i<_num_of_false_statements; i++)
                    {
                        _tmp_false_statements.push_back( parseContext._statements.top());
                        parseContext._statements.pop();
                    }
                    vector<GeneralEvaluation*> _tmp_true_statements;
                    for (int i=0; i<_num_of_true_statements; i++)
                    {
                        _tmp_true_statements.push_back( parseContext._statements.top());
                        parseContext._statements.pop();
                    }
                    GeneralEvaluation * _condition = parseContext._stack.top();
                    parseContext._stack.pop();

                    FullIfEvaluation * _f_if_calc = new FullIfEvaluation(_condition, _num_of_true_statements, _num_of_false_statements);

                    for (int i=_num_of_true_statements-1; i>=0; i--)
                    {
                        _f_if_calc->addArgument( _tmp_true_statements[i]);
                    }
                    for (int i=_num_of_false_statements-1; i>=0; i--)
                    {
                        _f_if_calc->addArgument( _tmp_false_statements[i]);
                    }
                    parseContext._statements.push(_f_if_calc);
                }
                parseContext.syntax_ok &= true;
            }
#line 1750 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 118: // enclosed_list_of_statements_start: "{"
#line 1282 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._number_of_statements.push(0);
                }
                parseContext.syntax_ok &= true;
            }
#line 1762 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 119: // while_statement: "while" "(" boolean_expression ")" enclosed_list_of_statements
#line 1292 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    int _num_of_statements = parseContext._number_of_statements.top();
                    parseContext._number_of_statements.pop();

                    vector<GeneralEvaluation*> _tmp_statements;
                    for (int i=0; i<_num_of_statements; i++)
                    {
                        _tmp_statements.push_back( parseContext._statements.top());
                        parseContext._statements.pop();
                    }
                    GeneralEvaluation * _condition = parseContext._stack.top();
                    parseContext._stack.pop();

                    WhileEvaluation * _while_calc = new WhileEvaluation(_condition);

                    for (int i=_num_of_statements-1; i>=0; i--)
                    {
                        _while_calc->addArgument( _tmp_statements[i]);
                    }
                    parseContext._statements.push(_while_calc);

                }
                parseContext.syntax_ok &= true;
            }
#line 1793 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 120: // assignment: assignment_target "=" expression
#line 1321 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                        GeneralEvaluation * _value = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation * _index = parseContext._stack.top();
                        parseContext._stack.pop();
                        std::string _string = parseContext.string_constants.top();
                        parseContext.string_constants.pop();
                        AssignmentEvaluation * _assign_eval = new AssignmentEvaluation( _string , _index, _value, parseContext.cube->get_cubepl_memory_manager()  );
                        parseContext._statements.push( _assign_eval );
                }
                parseContext.syntax_ok &= true;
            }
#line 1812 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 123: // put_variable: "$" "{" string_constant "}"
#line 1340 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
              {
                if (!parseContext.test_modus)
                {
                    parseContext._stack.push( new ConstantEvaluation(0) ); // pushed index 0 if array index is not specified
                }
                parseContext.syntax_ok &= true;
              }
#line 1824 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 128: // create_postderived_ghost_metric: "cube::metric::postderived" METRIC_NAME GhostMetricDefinition
#line 1360 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                    {
                            if (!parseContext.test_modus)
                            {
                              std::string expression = parseContext.str.str();
                              parseContext.str.str("");
                              std::string uniq_name = parseContext.value;
                              Metric * _met = parseContext.cube->get_met(uniq_name);
                              if (_met == NULL)
                              {
                                _met = parseContext.cube->def_met("",
                                                                    uniq_name,
                                                                    "DOUBLE",
                                                                    "",
                                                                    "",
                                                                    "",
                                                                    "",
                                                                    NULL,
                                                                    cube::CUBE_METRIC_POSTDERIVED,
                                                                    expression,
                                                                    "",
                                                                    "",
                                                                    "",
                                                                    "",
                                                                    cube::CUBE_METRIC_GHOST
                                                                  );
                              }else
                              {
                                cout << " Metric with uniq name " << uniq_name << " already exists in cube" << endl;
                              }
                           }else
                          {
                              std::string expression = parseContext.str.str();
                              std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                              cubeplparser::CubePL0Driver* driver         = new cubeplparser::CubePL0Driver( parseContext.cube ); // create driver for this cube
                              std::string nested_error;
                              if (! driver->test( cubepl_program, nested_error ))
                              {
                                parseContext.syntax_ok &= false;
                              }
                              delete driver;
                            }
                            parseContext.syntax_ok &= true;

                    }
#line 1873 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 129: // create_prederived_inclusive_ghost_metric: "cube::metric::prederived" METRIC_NAME "(" "i" ")" GhostMetricDefinition
#line 1406 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                            {
                              if (!parseContext.test_modus)
                              {
                                std::string expression = parseContext.str.str();
                                parseContext.str.str("");
                                std::string uniq_name = parseContext.value;
                                Metric * _met = parseContext.cube->get_met(uniq_name);
                                if (_met == NULL)
                                {
                                  _met = parseContext.cube->def_met("",
                                                                    uniq_name,
                                                                    "DOUBLE",
                                                                    "",
                                                                    "",
                                                                    "",
                                                                    "",
                                                                    NULL,
                                                                    cube::CUBE_METRIC_PREDERIVED_INCLUSIVE,
                                                                    expression,
                                                                    "",
                                                                    "",
                                                                    "",
                                                                    "",
                                                                      cube::CUBE_METRIC_GHOST
                                                                    );
                                }else
                                {
                                  cout << " Metric with uniq name " << uniq_name << " already exists in cube" << endl;
                                }
                            }else
                            {
                                std::string expression = parseContext.str.str();
                                std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                                cubeplparser::CubePL0Driver* driver         = new cubeplparser::CubePL0Driver( parseContext.cube ); // create driver for this cube
                                std::string nested_error;
                                if (! driver->test( cubepl_program, nested_error ))
                                {
                                  parseContext.syntax_ok = false;
                                }
                                delete driver;
                              }
                              parseContext.syntax_ok &= true;
                            }
#line 1921 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 130: // create_prederived_exclusive_ghost_metric: "cube::metric::prederived" METRIC_NAME "(" "e" ")" GhostMetricDefinition
#line 1451 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                            {
                                if (!parseContext.test_modus)
                                {
                                  std::string expression = parseContext.str.str();
                                  parseContext.str.str("");
                                  std::string uniq_name = parseContext.value;
                                  Metric * _met = parseContext.cube->get_met(uniq_name);

                                  if (_met == NULL)
                                  {
                                    _met = parseContext.cube->def_met("",
                                                                        uniq_name,
                                                                      "DOUBLE",
                                                                        "",
                                                                        "",
                                                                        "",
                                                                        "",
                                                                        NULL,
                                                                        cube::CUBE_METRIC_PREDERIVED_EXCLUSIVE,
                                                                        expression,
                                                                        "",
                                                                        "",
                                                                        "",
                                                                        "",
                                                                        cube::CUBE_METRIC_GHOST
                                                                      );
                                  }else
                                  {
                                    cout << " Metric with uniq name " << uniq_name << " already exists in cube" << endl;
                                  }
                              }else
                              {
                                  std::string expression = parseContext.str.str();
                                  std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                                  cubeplparser::CubePL0Driver* driver         = new cubeplparser::CubePL0Driver( parseContext.cube ); // create driver for this cube
                                  std::string nested_error;
                                  if (! driver->test( cubepl_program, nested_error ))
                                  {
                                    parseContext.syntax_ok = false;
                                  }
                                  delete driver;
                              }
                              parseContext.syntax_ok &= true;
                            }
#line 1970 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 133: // get_variable: get_variable_simple
#line 1505 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                  {
                    if (!parseContext.test_modus)
                    {
                            GeneralEvaluation * _index = parseContext._stack.top();
                            parseContext._stack.pop();
                            std::string _string = parseContext.string_constants.top();
                            parseContext.string_constants.pop();
                            VariableEvaluation * _var_eval = new VariableEvaluation(  _string, _index, parseContext.cube->get_cubepl_memory_manager()   );
                            parseContext._stack.push( _var_eval );
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1987 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 134: // get_variable: get_variable_indexed
#line 1518 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
                {
                  if (!parseContext.test_modus)
                  {
                          GeneralEvaluation * _index = parseContext._stack.top();
                          parseContext._stack.pop();
                          std::string _string = parseContext.string_constants.top();
                          parseContext.string_constants.pop();
                          VariableEvaluation * _var_eval = new VariableEvaluation(  _string, _index, parseContext.cube->get_cubepl_memory_manager()  );
                          parseContext._stack.push( _var_eval );
                  }
                  parseContext.syntax_ok &= true;
              }
#line 2004 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 135: // get_variable_simple: "$" "{" string_constant "}"
#line 1533 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._stack.push( new ConstantEvaluation(0) ); // pushed index 0 if array index is not specified
                }
                parseContext.syntax_ok &= true;
            }
#line 2016 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 137: // sizeof_variable: "sizeof" "(" string_constant ")"
#line 1546 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
        if (!parseContext.test_modus)
        {
            std::string _string = parseContext.string_constants.top();
            parseContext.string_constants.pop();
            SizeOfVariableEvaluation * _sizeof_var_eval = new SizeOfVariableEvaluation(  _string, parseContext.cube->get_cubepl_memory_manager()  );
            parseContext._stack.push( _sizeof_var_eval );
        }
        parseContext.syntax_ok &= true;
            }
#line 2031 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 138: // defined_variable: "defined" "(" string_constant ")"
#line 1558 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
        if (!parseContext.test_modus)
        {
            std::string _string = parseContext.string_constants.top();
            parseContext.string_constants.pop();
            DefinedVariableEvaluation * _sizeof_var_eval = new DefinedVariableEvaluation(  _string, parseContext.cube->get_cubepl_memory_manager(), parseContext.cube  );
            parseContext._stack.push( _sizeof_var_eval );
        }
            }
#line 2045 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;

  case 139: // string_constant: STRING_CONSTANT
#line 1570 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
            {
                parseContext.string_constants.push(parseContext.value);
                parseContext.value = "";
            }
#line 2054 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
    break;


#line 2058 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"

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
  CubePL0Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  CubePL0Parser::yytnamerr_ (const char *yystr)
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
  CubePL0Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // CubePL0Parser::context.
  CubePL0Parser::context::context (const CubePL0Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  CubePL0Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  CubePL0Parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  CubePL0Parser::yysyntax_error_ (const context& yyctx) const
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


  const short CubePL0Parser::yypact_ninf_ = -182;

  const signed char CubePL0Parser::yytable_ninf_ = -61;

  const short
  CubePL0Parser::yypact_[] =
  {
      12,   114,    24,  -182,   247,   247,  -182,    16,    30,   247,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,    17,   -34,
     -17,  -182,   327,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,    69,  -182,    70,  -182,  -182,  -182,  -182,
    -182,    62,  -182,  -182,  -182,  -182,  -182,  -182,   118,   292,
      13,    13,    28,    13,    75,    94,  -182,   247,   247,   247,
     247,   247,   247,   247,    95,    97,    98,    42,    51,    90,
     136,  -182,  -182,  -182,   102,  -182,  -182,    88,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,   153,   162,  -182,   161,
       0,    21,   118,   118,   170,   170,  -182,   312,    36,   186,
     186,    13,   164,   171,   247,   169,    62,  -182,   142,    62,
     247,  -182,  -182,   187,  -182,  -182,  -182,  -182,    -5,  -182,
      -2,  -182,   247,   186,   195,  -182,  -182,   217,   218,  -182,
     151,    43,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,   -35,  -182,
    -182,  -182,  -182,    53,    54,   219,   176,  -182,   -27,   163,
    -182,  -182,   102,  -182,   233,   332,   247,  -182,   120,  -182,
     120,   319,    11,   106,   186,   -37,   -37,   247,   247,   247,
     247,   247,   247,  -182,   186,   186,   186,   -37,   -37,   155,
     102,   221,  -182,  -182,   243,   245,  -182,  -182,  -182,   230,
     248,   249,  -182,  -182,   110,   252,  -182,   253,   332,   332,
     332,   332,   332,   332,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,   247,   164,   164,  -182,  -182,  -182,  -182,  -182,
    -182,   283,  -182,  -182,  -182
  };

  const unsigned char
  CubePL0Parser::yydefact_[] =
  {
       0,     0,     0,     3,     0,     0,   104,     0,     0,     0,
      71,    72,    73,    74,    75,    78,    79,    76,    77,    81,
      80,    82,    83,    84,    85,    86,    88,    89,     0,     0,
       0,    90,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    68,     0,    69,     0,    13,    14,    91,    92,
      15,   105,    16,   133,   134,    17,    18,     1,    26,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   107,   111,   112,     0,   108,   109,     0,   121,   122,
     110,   125,   126,   127,    19,   139,     0,     0,    20,     0,
       0,     0,    21,    22,    24,    23,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   118,   113,   105,
       0,   137,   138,   135,    93,    99,   100,   101,     0,    96,
       0,    70,     0,     0,     0,    45,    46,     0,     0,    63,
       0,     0,    27,    34,    35,    36,    37,    38,    28,    29,
      30,    31,    32,    33,    39,    53,    54,    55,     0,    61,
      62,    64,    65,    16,     0,     0,     0,   128,     0,     0,
     102,   106,     0,   114,     0,   120,     0,    94,     0,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,     0,     0,     0,     0,     0,     0,
       0,   123,   132,   131,     0,     0,   103,   116,   117,     0,
       0,     0,    87,    40,     0,     0,    60,     0,    49,    47,
      51,    52,    48,    50,    42,    43,    44,    56,    57,    59,
      58,   119,     0,     0,     0,   136,    95,    98,    41,    66,
      67,     0,   129,   130,   124
  };

  const short
  CubePL0Parser::yypgoto_[] =
  {
    -182,  -182,    -1,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -103,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,    44,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,   -96,  -182,  -182,  -182,   -68,  -182,  -182,
    -182,  -182,  -182,  -182,  -151,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -181,  -182,  -108,  -182,  -182,
    -182,  -182,   -51
  };

  const unsigned char
  CubePL0Parser::yydefgoto_[] =
  {
       0,     2,   140,    33,    34,    35,    36,    37,    38,    39,
      40,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   230,   158,
     159,   160,   161,   162,    41,    42,    43,    44,    45,    46,
      47,    48,    49,   128,    50,   115,    51,    79,    80,    81,
      82,    83,    84,   173,   118,   119,    85,    86,    87,    88,
      89,    90,    91,    92,    93,   167,   203,    52,    53,    54,
      55,    56,    96
  };

  const short
  CubePL0Parser::yytable_[] =
  {
      32,   163,   163,    58,    59,   130,   177,   164,    62,   179,
      97,   124,    99,   197,   198,     1,    67,    68,    69,    70,
      71,   207,    94,    28,    57,   163,    60,   199,   137,   138,
     183,    63,   129,    67,    68,    69,    70,    71,    64,   139,
      61,    67,    68,    69,    70,    71,   204,   205,   171,   231,
      98,   174,   242,   243,   193,    65,   178,   187,   188,   180,
     165,   189,   190,   191,   192,   200,   102,   103,   104,   105,
     106,   107,   108,   125,   126,   127,   163,   216,   216,    72,
      73,   214,   210,    95,   211,   100,   163,   163,   163,   216,
     216,   224,   225,   226,   125,   126,   127,   132,   194,   195,
     196,   -60,   -60,    74,   101,   109,    75,   110,   114,   194,
     195,   196,   111,   169,   112,   -60,   117,   213,     3,   175,
       4,   238,    76,   113,     5,    69,    70,    71,     6,    77,
      78,   181,   182,   120,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,   116,    67,    68,    69,    70,
      71,   194,   195,   196,   121,   194,   195,   196,    67,    68,
      69,    70,    71,   122,    28,   209,   123,    29,    30,    71,
     166,   168,   206,    31,   170,   172,   218,   219,   220,   221,
     222,   223,     4,   125,   126,   127,   133,   187,   188,   176,
       6,   189,   190,   191,   192,   184,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,   185,   186,   215,
     217,   241,   229,   232,   201,    67,    68,    69,    70,    71,
     134,   227,   228,   235,   135,   136,    28,   202,   208,    29,
      30,   137,   138,     4,   233,    31,   234,     5,     0,   236,
     237,     6,   139,   239,   240,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    67,    68,
      69,    70,    71,     0,     0,     0,   244,    67,    68,    69,
      70,    71,     0,    94,     0,     0,     0,    28,     0,     0,
      29,    30,     0,     0,     0,     0,    31,    67,    68,    69,
      70,    71,     0,   131,    67,    68,    69,    70,    71,     0,
     212,    66,    67,    68,    69,    70,    71,    67,    68,    69,
      70,    71
  };

  const short
  CubePL0Parser::yycheck_[] =
  {
       1,   109,   110,     4,     5,   101,    11,   110,     9,    11,
      61,    11,    63,    48,    49,     3,     5,     6,     7,     8,
       9,   172,    11,    60,     0,   133,    10,    62,    65,    66,
     133,    14,    11,     5,     6,     7,     8,     9,    72,    76,
      10,     5,     6,     7,     8,     9,    73,    74,   116,   200,
      22,   119,   233,   234,    11,    72,    61,    46,    47,    61,
     111,    50,    51,    52,    53,    11,    67,    68,    69,    70,
      71,    72,    73,    73,    74,    75,   184,   185,   186,    10,
      10,   184,   178,    70,   180,    10,   194,   195,   196,   197,
     198,   194,   195,   196,    73,    74,    75,    61,    55,    56,
      57,    48,    49,    41,    10,    10,    44,    10,    18,    55,
      56,    57,    14,   114,    72,    62,    14,    11,     4,   120,
       6,    11,    60,    72,    10,     7,     8,     9,    14,    67,
      68,   132,   133,    45,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    19,     5,     6,     7,     8,
       9,    55,    56,    57,    11,    55,    56,    57,     5,     6,
       7,     8,     9,    11,    60,   176,    15,    63,    64,     9,
      16,    10,    19,    69,    15,    43,   187,   188,   189,   190,
     191,   192,     6,    73,    74,    75,    10,    46,    47,    12,
      14,    50,    51,    52,    53,    10,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    10,    10,   185,
     186,   232,    77,    12,    15,     5,     6,     7,     8,     9,
      54,   197,   198,    13,    58,    59,    60,    71,    15,    63,
      64,    65,    66,     6,    11,    69,    11,    10,    -1,    11,
      11,    14,    76,    11,    11,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     5,     6,
       7,     8,     9,    -1,    -1,    -1,    13,     5,     6,     7,
       8,     9,    -1,    11,    -1,    -1,    -1,    60,    -1,    -1,
      63,    64,    -1,    -1,    -1,    -1,    69,     5,     6,     7,
       8,     9,    -1,    11,     5,     6,     7,     8,     9,    -1,
      11,     4,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9
  };

  const unsigned char
  CubePL0Parser::yystos_[] =
  {
       0,     3,    81,     4,     6,    10,    14,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    60,    63,
      64,    69,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     124,   126,   147,   148,   149,   150,   151,     0,    82,    82,
      10,    10,    82,    14,    72,    72,     4,     5,     6,     7,
       8,     9,    10,    10,    41,    44,    60,    67,    68,   127,
     128,   129,   130,   131,   132,   136,   137,   138,   139,   140,
     141,   142,   143,   144,    11,    70,   152,   152,    22,   152,
      10,    10,    82,    82,    82,    82,    82,    82,    82,    10,
      10,    14,    72,    72,    18,   125,    19,    14,   134,   135,
      45,    11,    11,    15,    11,    73,    74,    75,   123,    11,
     123,    11,    61,    10,    54,    58,    59,    65,    66,    76,
      82,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   109,   110,
     111,   112,   113,   147,    91,   152,    16,   145,    10,    82,
      15,   127,    43,   133,   127,    82,    12,    11,    61,    11,
      61,    82,    82,    91,    10,    10,    10,    46,    47,    50,
      51,    52,    53,    11,    55,    56,    57,    48,    49,    62,
      11,    15,    71,   146,    73,    74,    19,   134,    15,    82,
     123,   123,    11,    11,    91,   109,   147,   109,    82,    82,
      82,    82,    82,    82,    91,    91,    91,   109,   109,    77,
     108,   134,    12,    11,    11,    13,    11,    11,    11,    11,
      11,    82,   145,   145,    13
  };

  const unsigned char
  CubePL0Parser::yyr1_[] =
  {
       0,    80,    81,    81,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      92,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   104,   104,   105,   106,   107,   108,
     109,   109,   109,   110,   111,   111,   112,   113,   114,   114,
     115,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   117,   118,   118,
     119,   120,   120,   121,   121,   121,   122,   122,   122,   123,
     123,   123,   124,   125,   126,   127,   127,   128,   128,   128,
     128,   129,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   138,   139,   140,   141,   141,   141,   142,   143,
     144,   145,   146,   147,   147,   148,   149,   150,   151,   152
  };

  const signed char
  CubePL0Parser::yyr2_[] =
  {
       0,     2,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     3,     3,     1,     1,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     1,     1,
       1,     1,     1,     4,     5,     7,     4,     5,     7,     1,
       1,     1,     4,     3,     1,     0,     3,     1,     1,     1,
       1,     1,     1,     2,     3,     4,     2,     3,     1,     5,
       3,     1,     1,     4,     7,     1,     1,     1,     3,     6,
       6,     2,     1,     1,     1,     4,     7,     4,     4,     1
  };


#if CUBEPLPARSERDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const CubePL0Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"<cubepl>\"",
  "\"</cubepl>\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"^\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"<<\"", "\">>\"",
  "\"return\"", "\";\"", "\"sizeof\"", "\"defined\"", "\"|\"", "\"sqrt\"",
  "\"sin\"", "\"asin\"", "\"cos\"", "\"acos\"", "\"tan\"", "\"atan\"",
  "\"exp\"", "\"log\"", "\"abs\"", "\"random\"", "\"sgn\"", "\"pos\"",
  "\"neg\"", "\"floor\"", "\"ceil\"", "\"min\"", "\"max\"", "\"if\"",
  "\"elseif\"", "\"else\"", "\"while\"", "\"=\"", "\">\"", "\"==\"",
  "\"eq\"", "\"seq\"", "\">=\"", "\"<=\"", "\"!=\"", "\"<\"", "\"not\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"true\"", "\"false\"", "\"$\"",
  "\",\"", "\"=~\"", "\"metric::\"", "\"metric::fixed::\"",
  "\"lowercase\"", "\"uppercase\"", "\"cube::metric::postderived\"",
  "\"cube::metric::prederived\"", "CONSTANT", "STRING_CONSTANT",
  "STRING_TEXT", "METRIC_NAME", "\"i\"", "\"e\"", "SAME_MODIFICATOR",
  "QUOTED_STRING", "REGEXP_STRING", "FUNC2", "SIGN", "$accept", "document",
  "expression", "enclosed_expression", "absolute_value", "sum", "subtract",
  "division", "multiplication", "power", "negation", "boolean_expression",
  "enclosed_boolean_expression", "and_expression", "or_expression",
  "xor_expression", "true_expression", "false_expression", "equality",
  "not_equality", "bigger", "smaller", "halfbigger", "halfsmaller",
  "string_operation", "string_equality", "string_semi_equality", "regexp",
  "regexp_expression", "string_expression", "quoted_string",
  "string_function", "lowercase", "uppercase", "function_call",
  "one_variable_function", "function_name", "two_variables_function",
  "function2_name", "constant", "metric_refs", "context_metric",
  "fixed_metric", "calculationFlavourModificator", "lambda_calcul",
  "return_expression", "lambda_start", "list_of_statements", "statement",
  "if_statement", "simple_if_statement", "full_if_statement",
  "if_condition", "else_enclosed_list_of_statements",
  "enclosed_list_of_statements", "enclosed_list_of_statements_start",
  "while_statement", "assignment", "assignment_target", "put_variable",
  "put_variable_indexed", "create_ghost_metric",
  "create_postderived_ghost_metric",
  "create_prederived_inclusive_ghost_metric",
  "create_prederived_exclusive_ghost_metric", "GhostMetricDefinition",
  "CubePLGhostText", "get_variable", "get_variable_simple",
  "get_variable_indexed", "sizeof_variable", "defined_variable",
  "string_constant", YY_NULLPTR
  };
#endif


#if CUBEPLPARSERDEBUG
  const short
  CubePL0Parser::yyrline_[] =
  {
       0,   301,   301,   310,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   335,
     345,   358,   371,   385,   398,   414,   426,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     456,   466,   477,   490,   504,   517,   525,   534,   548,   562,
     575,   589,   603,   619,   620,   621,   626,   639,   651,   666,
     692,   693,   694,   700,   711,   711,   716,   727,   741,   741,
     743,   757,   765,   773,   781,   789,   797,   805,   813,   821,
     829,   837,   845,   853,   861,   869,   877,   888,   904,   912,
     923,   934,   934,   939,   958,   979,  1006,  1025,  1052,  1090,
    1098,  1106,  1117,  1147,  1149,  1158,  1160,  1166,  1177,  1188,
    1199,  1202,  1203,  1206,  1233,  1272,  1275,  1278,  1281,  1291,
    1320,  1336,  1336,  1339,  1349,  1353,  1354,  1355,  1359,  1405,
    1450,  1497,  1500,  1504,  1517,  1532,  1541,  1545,  1557,  1569
  };

  void
  CubePL0Parser::yy_stack_print_ () const
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
  CubePL0Parser::yy_reduce_print_ (int yyrule) const
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
#endif // CUBEPLPARSERDEBUG

  CubePL0Parser::symbol_kind_type
  CubePL0Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
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
      69,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      70,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      71,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      72,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      76,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      77,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      75,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    73,    74,
      78,    79
    };
    // Last valid token kind.
    const int code_max = 671;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // cubeplparser
#line 2834 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"

#line 1575 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
 /*** Additional Code ***/


void cubeplparser::CubePL0Parser::error(const CubePL0Parser::location_type& l,
                                  const std::string& m)
{

    CubePL0Parser::location_type _l = l;


    _l.end.column = (_l.end.column<9)?1: _l.end.column-8;
    _l.begin.column = _l.end.column-1;

    parseContext.syntax_ok = false;
    stringstream sstr;
    string       str;
    sstr << _l;
    sstr >> str;
    parseContext.error_message = str + ":" + m;
    parseContext.error_place = _l;

}
