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



#include "CubePL1Parser.h"

// Second part of user prologue.
#line 268 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePL1Scanner.h"
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
#include "CubePL1ParseContext.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex CubePL1Lexer.lex

// Workaround for Sun Studio C++ compilers on Solaris
#if defined(__SVR4) &&  defined(__SUNPRO_CC)
  #include <ieeefp.h>

  #define isinf(x)  (fpclass(x) == FP_NINF || fpclass(x) == FP_PINF)
  #define isnan(x)  isnand(x)
#endif


#line 86 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"



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
#line 179 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"

  /// Build a parser object.
  CubePL1Parser::CubePL1Parser (class CubePL1ParseContext& parseContext_yyarg, class CubePL1Scanner& CubePL1Lexer_yyarg)
#if CUBEPLPARSERDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      parseContext (parseContext_yyarg),
      CubePL1Lexer (CubePL1Lexer_yyarg)
  {}

  CubePL1Parser::~CubePL1Parser ()
  {}

  CubePL1Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  CubePL1Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  CubePL1Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  CubePL1Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}


  template <typename Base>
  CubePL1Parser::symbol_kind_type
  CubePL1Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  CubePL1Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  CubePL1Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  CubePL1Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  CubePL1Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  CubePL1Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  CubePL1Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  CubePL1Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  CubePL1Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  CubePL1Parser::symbol_kind_type
  CubePL1Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  CubePL1Parser::symbol_kind_type
  CubePL1Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  CubePL1Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  CubePL1Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  CubePL1Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  CubePL1Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  CubePL1Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  CubePL1Parser::symbol_kind_type
  CubePL1Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  CubePL1Parser::stack_symbol_type::stack_symbol_type ()
  {}

  CubePL1Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  CubePL1Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  CubePL1Parser::stack_symbol_type&
  CubePL1Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  CubePL1Parser::stack_symbol_type&
  CubePL1Parser::stack_symbol_type::operator= (stack_symbol_type& that)
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
  CubePL1Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if CUBEPLPARSERDEBUG
  template <typename Base>
  void
  CubePL1Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
  CubePL1Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  CubePL1Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  CubePL1Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if CUBEPLPARSERDEBUG
  std::ostream&
  CubePL1Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  CubePL1Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  CubePL1Parser::debug_level_type
  CubePL1Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  CubePL1Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // CUBEPLPARSERDEBUG

  CubePL1Parser::state_type
  CubePL1Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  CubePL1Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  CubePL1Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  CubePL1Parser::operator() ()
  {
    return parse ();
  }

  int
  CubePL1Parser::parse ()
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
#line 147 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
{
    // initialize the initial location object
}

#line 524 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"


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
#line 317 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                parseContext.result = parseContext._stack.top();
                parseContext._stack.pop();
                }
                parseContext.syntax_ok &= true;
        }
#line 669 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 3: // document: "<cubepl>" "</cubepl>"
#line 326 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
                parseContext.syntax_ok &= true;
        }
#line 677 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 23: // enclosed_expression: "(" expression ")"
#line 355 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * _arg1 = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new EncapsulationEvaluation(_arg1) );
                }
                parseContext.syntax_ok &= true;
            }
#line 691 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 24: // absolute_value: "|" expression "|"
#line 365 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 707 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 25: // sum: expression "+" expression
#line 378 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 723 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 26: // subtract: expression "-" expression
#line 391 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 739 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 27: // division: expression "/" expression
#line 405 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 755 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 28: // multiplication: expression "*" expression
#line 418 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 771 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 29: // power: expression "^" expression
#line 434 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 787 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 30: // negation: "-" expression
#line 446 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    GeneralEvaluation * arg = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new NegativeEvaluation(arg) );
                }
                parseContext.syntax_ok &= true;
            }
#line 801 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 33: // argument1: "arg1"
#line 460 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                        parseContext._stack.push(new ArgumentEvaluation(cube::FIRST_ARGUMENT) );
                }
                parseContext.syntax_ok &= true;
            }
#line 813 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 34: // argument2: "arg2"
#line 469 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                        parseContext._stack.push(new ArgumentEvaluation(cube::SECOND_ARGUMENT) );
                }
                parseContext.syntax_ok &= true;
            }
#line 825 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 48: // enclosed_boolean_expression: "(" boolean_expression ")"
#line 497 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                            GeneralEvaluation * _arg1 = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new EncapsulationEvaluation(_arg1) );
                        }
                        parseContext.syntax_ok &= true;
                    }
#line 839 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 49: // enclosed_boolean_expression: "not" "(" boolean_expression ")"
#line 507 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                            GeneralEvaluation * _arg1 = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new NotEvaluation(_arg1) );
                        }
                        parseContext.syntax_ok &= true;
                    }
#line 853 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 50: // and_expression: boolean_expression "and" boolean_expression
#line 518 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 870 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 51: // or_expression: boolean_expression "or" boolean_expression
#line 531 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 887 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 52: // xor_expression: boolean_expression "xor" boolean_expression
#line 545 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 904 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 53: // true_expression: "true"
#line 558 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._stack.push( new ConstantEvaluation(1) );
                }
                parseContext.syntax_ok &= true;
            }
#line 916 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 54: // false_expression: "false"
#line 566 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._stack.push( new ConstantEvaluation(0) );
                }
                parseContext.syntax_ok &= true;
            }
#line 928 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 55: // equality: expression "==" expression
#line 575 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 945 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 56: // not_equality: expression "!=" expression
#line 589 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 961 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 57: // bigger: expression ">" expression
#line 603 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 977 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 58: // smaller: expression "<" expression
#line 616 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 993 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 59: // halfbigger: expression ">=" expression
#line 630 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1009 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 60: // halfsmaller: expression "<=" expression
#line 644 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1025 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 64: // string_equality: expression "eq" expression
#line 667 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1041 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 65: // string_semi_equality: expression "seq" expression
#line 680 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1057 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 66: // regexp: expression "=~" regexp_expression
#line 692 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1073 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 67: // regexp_expression: REGEXP_STRING
#line 707 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1100 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 68: // quoted_string: QUOTED_STRING
#line 735 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                    parseContext._stack.push( new StringConstantEvaluation( parseContext.str.str() ));
                    parseContext.str.str("");
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1113 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 72: // lowercase: "lowercase" "(" expression ")"
#line 751 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                            GeneralEvaluation * _arg1 = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new LowerCaseEvaluation(_arg1) );
                        }
                        parseContext.syntax_ok &= true;
                    }
#line 1127 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 73: // uppercase: "uppercase" "(" expression ")"
#line 762 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                            GeneralEvaluation * _arg1 = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new UpperCaseEvaluation(_arg1) );
                        }
                        parseContext.syntax_ok &= true;
                    }
#line 1141 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 74: // getenv: "env" "(" expression ")"
#line 774 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                    {
                        if (!parseContext.test_modus)
                        {
                            GeneralEvaluation * _arg1 = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new EnvEvaluation(_arg1) );
                        }
                        parseContext.syntax_ok &= true;
                    }
#line 1155 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 75: // metric_get: "cube::metric::get::" METRIC_NAME "(" quoted_string ")"
#line 788 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                        std::string uniq_name = parseContext.name_of_metric;
                        Metric * _met = parseContext.cube->get_met(uniq_name);
                        if (_met != NULL)
                        {
                            GeneralEvaluation * _property = parseContext._stack.top();
                            parseContext._stack.pop();
                            MetricGetEvaluation * _metric_get_eval = new MetricGetEvaluation( _met, _property );
                            parseContext._stack.push( _metric_get_eval );
                        }else
                        {
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        " Metric with uniq name  %s.  doesn't exists in cube. metric::get has no action.",
                        uniq_name.c_str()
                    );
#endif
                        }
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1185 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 78: // one_variable_function: function_name "(" expression ")"
#line 820 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1201 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 79: // function_name: "sqrt"
#line 835 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new SqrtEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1213 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 80: // function_name: "sin"
#line 843 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new SinEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1225 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 81: // function_name: "asin"
#line 851 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new ASinEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1237 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 82: // function_name: "cos"
#line 859 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new CosEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1249 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 83: // function_name: "acos"
#line 867 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new ACosEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1261 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 84: // function_name: "exp"
#line 875 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new ExpEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1273 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 85: // function_name: "log"
#line 883 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new LnEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1285 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 86: // function_name: "tan"
#line 891 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new TanEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1297 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 87: // function_name: "atan"
#line 899 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new ATanEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1309 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 88: // function_name: "random"
#line 907 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new RandomEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1321 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 89: // function_name: "abs"
#line 915 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new AbsEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1333 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 90: // function_name: "sgn"
#line 923 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new SgnEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1345 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 91: // function_name: "pos"
#line 931 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new PosEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1357 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 92: // function_name: "neg"
#line 939 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new NegEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1369 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 93: // function_name: "floor"
#line 947 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new FloorEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1381 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 94: // function_name: "ceil"
#line 955 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new CeilEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1393 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 95: // two_variables_function: function2_name "(" expression "," expression ")"
#line 966 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1412 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 96: // function2_name: "min"
#line 982 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new MinEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1424 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 97: // function2_name: "max"
#line 990 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if (!parseContext.test_modus)
                    {
                            parseContext.function_call.push( new MaxEvaluation());
                    }
                    parseContext.syntax_ok &= true;
                }
#line 1436 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 98: // constant: CONSTANT
#line 1001 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
               if (!parseContext.test_modus)
               {
                double _value = atof( parseContext.value.c_str());
                parseContext._stack.push( new ConstantEvaluation(_value));
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
            }
#line 1450 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 102: // context_metric: "metric::" METRIC_NAME "(" ")"
#line 1017 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
                if (_met != NULL)
                {
                    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met ));
                    _met->isUsedByOthers( true );
                }
                else
                {
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        "Cannot connect to the metric %s. Seems that this metric is not created yet. Value of metric::%s() will be always 0",
                        parseContext.name_of_metric.c_str(),
                        parseContext.name_of_metric.c_str()
                    );
#endif
                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1482 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 103: // context_metric: "metric::" METRIC_NAME "(" calculationFlavourModificator ")"
#line 1045 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met, mod ));
                    _met->isUsedByOthers( true );
                }
                else
                {
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        "Cannot connect to the metric %s. Seems that this metric is not created yet. Value of metric::%s() will be always 0",
                        parseContext.name_of_metric.c_str(),
                        parseContext.name_of_metric.c_str()
                    );
#endif
                parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1516 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 104: // context_metric: "metric::" METRIC_NAME "(" calculationFlavourModificator "," calculationFlavourModificator ")"
#line 1075 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();

                    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met, mod1, mod2));
                    _met->isUsedByOthers( true );
                }
                else
                {
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        "Cannot connect to the metric %s. Seems that this metric is not created yet. Value of metric::%s() will be always 0",
                        parseContext.name_of_metric.c_str(),
                        parseContext.name_of_metric.c_str()
                    );
#endif
                parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1553 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 105: // fixed_metric: "metric::fixed::" METRIC_NAME "(" ")"
#line 1111 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
                if (_met != NULL)
                {
                    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_FULL_AGGR,  parseContext.cube, _met ));
                    _met->isUsedByOthers( true );
                }
                else
                {
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        "Cannot connect to the metric %s. Seems that this metric is not created yet. Value of metric::fixed::%s() will be always 0",
                        parseContext.name_of_metric.c_str(),
                        parseContext.name_of_metric.c_str()
                    );
#endif
                parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1585 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 106: // fixed_metric: "metric::fixed::" METRIC_NAME "(" calculationFlavourModificator ")"
#line 1139 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_AGGR_SYS,  parseContext.cube, _met, mod ));
                    _met->isUsedByOthers( true );

                }
                else
                {
                    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        "Cannot connect to the metric %s. Seems that this metric is not created yet. Value of metric::fixed::%s(",
                        parseContext.name_of_metric.c_str(),
                        parseContext.name_of_metric.c_str()
                    );
                    mod->print();
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        ") will be always 0"
                    );
#endif
                    delete mod;

                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1630 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 107: // fixed_metric: "metric::fixed::" METRIC_NAME "(" calculationFlavourModificator "," calculationFlavourModificator ")"
#line 1180 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();

                    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_NO_AGGR,  parseContext.cube, _met, mod1, mod2));
                    _met->isUsedByOthers( true );
                }
                else
                {
                    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        "Cannot connect to the metric %s. Seems that this metric is not created yet. Value of metric::fixed::%s(",
                        parseContext.name_of_metric.c_str(),
                        parseContext.name_of_metric.c_str()
                    );
                    mod1->print();
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        ","
                    );
                    mod2->print();
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        ") will be always 0"
                    );
#endif
                    delete mod2;
                    delete mod1;

                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1686 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 108: // metric_call: "metric::call::" METRIC_NAME "(" expression "," calculationFlavourModificator ")"
#line 1235 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    GeneralEvaluation * _cnode_id = parseContext._stack.top();
                    parseContext._stack.pop();

                    parseContext._stack.push( new DirectMetricEvaluation(cube::METRIC_CALL_CALLPATH,  parseContext.cube, _met, _cnode_id, mod ));
                    _met->isUsedByOthers( true );

                }
                else
                {
                    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();

                    GeneralEvaluation * _cnode_id = parseContext._stack.top();
                    parseContext._stack.pop();
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        "Cannot connect to the metric %s. Seems that this metric is not created yet. Value of metric::fixed::%s(",
                        parseContext.name_of_metric.c_str(),
                        parseContext.name_of_metric.c_str()
                    );
                    _cnode_id->print();
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        ","
                    );
                    mod->print();
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        ") will be always 0"
                    );
#endif
                    delete mod;
                    delete _cnode_id;

                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1744 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 109: // metric_call: "metric::call::" METRIC_NAME "(" expression "," calculationFlavourModificator "," expression "," calculationFlavourModificator ")"
#line 1289 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
                if (_met != NULL)
                {
                    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    GeneralEvaluation * _sysres_id = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _cnode_id = parseContext._stack.top();
                    parseContext._stack.pop();
                    parseContext._stack.push( new DirectMetricEvaluation(cube::METRIC_CALL_FULL,  parseContext.cube, _met, _cnode_id, mod1, _sysres_id,  mod2));
                    _met->isUsedByOthers( true );
                }
                else
                {
                    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
                    parseContext.calcFlavorModificators.pop();
                    GeneralEvaluation * _sysres_id = parseContext._stack.top();
                    parseContext._stack.pop();
                    GeneralEvaluation * _cnode_id = parseContext._stack.top();
                    parseContext._stack.pop();
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        "Cannot connect to the metric %s. Seems that this metric is not created yet. Value of metric::fixed::%s(",
                        parseContext.name_of_metric.c_str(),
                        parseContext.name_of_metric.c_str()
                    );
                    _cnode_id->print();
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        ","
                    );
                    mod1->print();
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        ","
                    );
                    _sysres_id->print();
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        ","
                    );
                    mod2->print();
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        ") will be always 0"
                    );
#endif
                    delete mod2;
                    delete mod1;
                    delete _cnode_id;
                    delete _sysres_id;

                    parseContext._stack.push( new ConstantEvaluation( 0 ));

                }
                parseContext.value = "";
                }
                parseContext.syntax_ok &= true;
        }
#line 1821 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 110: // calculationFlavourModificator: "i"
#line 1366 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                                {
                                    if (!parseContext.test_modus)
                                    {
                                        parseContext.calcFlavorModificators.push(new CalcFlavorModificatorIncl());
                                    }
                                    parseContext.syntax_ok &= true;
                                }
#line 1833 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 111: // calculationFlavourModificator: "e"
#line 1374 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                                {
                                    if (!parseContext.test_modus)
                                    {
                                        parseContext.calcFlavorModificators.push(new CalcFlavorModificatorExcl());
                                    }
                                    parseContext.syntax_ok &= true;
                                }
#line 1845 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 112: // calculationFlavourModificator: SAME_MODIFICATOR
#line 1382 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                                {
                                    if (!parseContext.test_modus)
                                    {
                                        parseContext.calcFlavorModificators.push(new CalcFlavorModificatorSame());
                                    }
                                    parseContext.syntax_ok &= true;
                                }
#line 1857 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 113: // lambda_calcul: lambda_start list_of_statements return_expression "}"
#line 1393 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1890 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 115: // lambda_start: "{"
#line 1425 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._number_of_statements.push(0);
                }
                parseContext.syntax_ok &= true;
            }
#line 1902 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 118: // statement: if_statement
#line 1442 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1917 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 119: // statement: while_statement
#line 1453 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1932 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 120: // statement: assignment
#line 1464 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1947 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 121: // statement: local_variable
#line 1475 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                parseContext.syntax_ok &= true;
            }
#line 1955 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 122: // statement: global_variable
#line 1479 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                parseContext.syntax_ok &= true;
            }
#line 1963 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 123: // statement: metric_set
#line 1483 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 1978 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 124: // statement: create_ghost_metric
#line 1494 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                parseContext.syntax_ok &= true;
            }
#line 1986 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 125: // statement: init_metric
#line 1498 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                parseContext.syntax_ok &= true;
            }
#line 1994 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 126: // statement: flex_aggr_plus
#line 1502 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                parseContext.syntax_ok &= true;
            }
#line 2002 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 127: // statement: flex_aggr_minus
#line 1506 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                parseContext.syntax_ok &= true;
            }
#line 2010 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 128: // metric_set: "cube::metric::set::" METRIC_NAME "(" quoted_string "," quoted_string ")"
#line 1512 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
{
            if (!parseContext.test_modus)
            {
                std::string uniq_name = parseContext.name_of_metric;
                Metric * _met = parseContext.cube->get_met(uniq_name);
                GeneralEvaluation * _value = parseContext._stack.top();
                parseContext._stack.pop();
                GeneralEvaluation * _property = parseContext._stack.top();
                parseContext._stack.pop();
                MetricSetEvaluation * _metric_set_eval = new MetricSetEvaluation( _met, _property , _value);
                parseContext._statements.push( _metric_set_eval );
                if (_met == NULL)
                {
#ifdef HAVE_CUBELIB_DEBUG
                    UTILS_DEBUG_PRINTF
                    (
                        ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                        " Metric with uniq name  %s.  doesn't exists in cube. metric::set has no action.",
                        uniq_name.c_str()
                    );
#endif
                }
            }
            parseContext.syntax_ok &= true;
}
#line 2040 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 133: // simple_if_statement: if_condition enclosed_list_of_statements
#line 1550 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 2070 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 134: // full_if_statement: if_condition enclosed_list_of_statements else_enclosed_list_of_statements
#line 1577 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 2112 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 135: // elseif_full_if_statement: if_condition enclosed_list_of_statements elseifs else_enclosed_list_of_statements
#line 1616 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    std::stack<std::stack<GeneralEvaluation*> > statement_blocks;
                    std::stack<GeneralEvaluation*>  statement_conditions;

                    int _num_of_false_statements = parseContext._number_of_statements.top();
                    parseContext._number_of_statements.pop();
                    std::stack<GeneralEvaluation*> _tmp_false_statements;
                    for (int i=0; i<_num_of_false_statements; i++)
                    {
                        _tmp_false_statements.push( parseContext._statements.top());
                        parseContext._statements.pop();
                    }
                    statement_blocks.push( _tmp_false_statements);

                    for (unsigned i=0; i<parseContext.number_elseif + 1 /* +1 is for the initial condition*/; ++i)
                    {
                        int _num_of_statements = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();
                        std::stack<GeneralEvaluation*> _tmp_statements;
                        for (int j=0; j<_num_of_statements; j++)
                        {
                            _tmp_statements.push( parseContext._statements.top());
                            parseContext._statements.pop();
                        }

                        GeneralEvaluation * _condition = parseContext._stack.top();
                        parseContext._stack.pop();
                        statement_blocks.push( _tmp_statements);
                        statement_conditions.push( _condition );
                    }
                    ExtendedIfEvaluation * _ext_if_calc = new ExtendedIfEvaluation(statement_conditions, statement_blocks);
                    parseContext._statements.push(_ext_if_calc);

                    parseContext.number_elseif= 0;
                }
                parseContext.syntax_ok &= true;
            }
#line 2156 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 136: // elseif_if_statement: if_condition enclosed_list_of_statements elseifs
#line 1659 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    std::stack<std::stack<GeneralEvaluation*> > statement_blocks;
                    std::stack<GeneralEvaluation*>  statement_conditions;

                    for (unsigned i=0; i<parseContext.number_elseif + 1 /* +1 is for the initial condition*/; ++i)
                    {
                        int _num_of_statements = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();
                        std::stack<GeneralEvaluation*> _tmp_statements;
                        for (int j=0; j<_num_of_statements; j++)
                        {
                            _tmp_statements.push( parseContext._statements.top());
                            parseContext._statements.pop();
                        }

                        GeneralEvaluation * _condition = parseContext._stack.top();
                        parseContext._stack.pop();
                        statement_blocks.push( _tmp_statements);
                        statement_conditions.push( _condition );
                    }
                    ExtendedIfEvaluation * _ext_if_calc = new ExtendedIfEvaluation(statement_conditions, statement_blocks);
                    parseContext._statements.push(_ext_if_calc);

                    parseContext.number_elseif= 0;
                }
                parseContext.syntax_ok &= true;
            }
#line 2190 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 139: // elseif_enclosed_list_of_statements: "elseif" "(" boolean_expression ")" enclosed_list_of_statements
#line 1696 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext.number_elseif++;
                }
                parseContext.syntax_ok &= true;
            }
#line 2202 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 143: // enclosed_list_of_statements_start: "{"
#line 1715 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._number_of_statements.push(0);
                }
                parseContext.syntax_ok &= true;
            }
#line 2214 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 144: // while_statement: "while" "(" boolean_expression ")" enclosed_list_of_statements
#line 1725 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 2245 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 145: // assignment: assignment_target "=" expression
#line 1754 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 2264 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 148: // put_variable: "$" "{" string_constant "}"
#line 1774 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
              {
                if (!parseContext.test_modus)
                {
                    parseContext._stack.push( new ConstantEvaluation(0) ); // pushed index 0 if array index is not specified
                }
                parseContext.syntax_ok &= true;
              }
#line 2276 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 153: // create_postderived_ghost_metric: "cube::metric::postderived::" METRIC_NAME GhostMetricDefinition
#line 1794 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                    {
                            if (!parseContext.test_modus)
                            {
                              std::string expression = parseContext.str.str();
                              parseContext.str.str("");
                              std::string uniq_name = parseContext.name_of_metric;
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
                                                                      true,
                                                                      cube::CUBE_METRIC_GHOST
                                                                  );
                              }else
                              {
#ifdef HAVE_CUBELIB_DEBUG
                                UTILS_DEBUG_PRINTF
                                (
                                    ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                                    " Metric with uniq name  %s. already exists in cube",
                                    uniq_name.c_str()
                                );
#endif
                              }
                           }else
                          {
                              std::string expression = parseContext.str.str();
                              std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                              cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                              std::string nested_error;
                              if (! driver->test( cubepl_program, nested_error ))
                              {
                                parseContext.syntax_ok &= false;
                              }
                              delete driver;
                            }
                            parseContext.syntax_ok &= true;

                    }
#line 2333 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 154: // create_prederived_inclusive_ghost_metric: "cube::metric::prederived::" METRIC_NAME "(" "i" ")" GhostMetricDefinition
#line 1848 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                            {
                              if (!parseContext.test_modus)
                              {
                                std::string expression = parseContext.str.str();
                                parseContext.str.str("");
                                std::string uniq_name = parseContext.name_of_metric;
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
                                                                      true,
                                                                      cube::CUBE_METRIC_GHOST
                                                                    );
                                }else
                                {
#ifdef HAVE_CUBELIB_DEBUG
                                UTILS_DEBUG_PRINTF
                                (
                                    ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                                    " Metric with uniq name  %s. already exists in cube",
                                    uniq_name.c_str()
                                );
#endif
                                }
                            }else
                            {
                                std::string expression = parseContext.str.str();
                                std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                                cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                                std::string nested_error;
                                if (! driver->test( cubepl_program, nested_error ))
                                {
                                  parseContext.syntax_ok = false;
                                }
                                delete driver;
                              }
                              parseContext.syntax_ok &= true;
                            }
#line 2389 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 155: // create_prederived_exclusive_ghost_metric: "cube::metric::prederived::" METRIC_NAME "(" "e" ")" GhostMetricDefinition
#line 1901 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                            {
                                if (!parseContext.test_modus)
                                {
                                  std::string expression = parseContext.str.str();
                                  parseContext.str.str("");
                                  std::string uniq_name = parseContext.name_of_metric;
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
                                                                        true,
                                                                        cube::CUBE_METRIC_GHOST
                                                                      );
                                  }else
                                  {
#ifdef HAVE_CUBELIB_DEBUG
                                UTILS_DEBUG_PRINTF
                                (
                                    ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                                    " Metric with uniq name  %s. already exists in cube",
                                    uniq_name.c_str()
                                );
#endif
                                }
                              }else
                              {
                                  std::string expression = parseContext.str.str();
                                  std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                                  cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                                  std::string nested_error;
                                  if (! driver->test( cubepl_program, nested_error ))
                                  {
                                    parseContext.syntax_ok = false;
                                  }
                                  delete driver;
                              }
                              parseContext.syntax_ok &= true;
                            }
#line 2446 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 158: // init_metric: "cube::init::metric::" METRIC_NAME GhostMetricDefinition
#line 1965 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                if (!parseContext.test_modus)
                {
                  std::string expression = parseContext.str.str();
                  parseContext.str.str("");
                  std::string uniq_name = parseContext.name_of_metric;
                  Metric * _met = parseContext.cube->get_met(uniq_name);

                    if (_met == NULL)
                    {
#ifdef HAVE_CUBELIB_DEBUG
                                UTILS_DEBUG_PRINTF
                                (
                                    ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                                    " Metric with uniq name  %s doesn't  exists yet. Cannot assign CubePL initialization expression. Skip.",
                                    uniq_name.c_str()
                                );
#endif
                    }else
                    {
                        _met->set_init_expression( expression );
                    }
                  }else
                  {
                  std::string expression = parseContext.str.str();
                  std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                  cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                  std::string nested_error;
                  if (! driver->test( cubepl_program, nested_error ))
                  {
                    parseContext.syntax_ok = false;
                  }
                  delete driver;
                  }
                  parseContext.syntax_ok &= true;
                }
#line 2487 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 159: // flex_aggr_plus: "cube::metric::plus::" INIT_METRIC_NAME GhostMetricDefinition
#line 2004 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                if (!parseContext.test_modus)
                {
                  std::string expression = parseContext.str.str();
                  parseContext.str.str("");
                  std::string uniq_name = parseContext.name_of_metric;
                  Metric * _met = parseContext.cube->get_met(uniq_name);

                    if (_met == NULL)
                    {
#ifdef HAVE_CUBELIB_DEBUG
                                UTILS_DEBUG_PRINTF
                                (
                                    ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                                    " Metric with uniq name  %s doesn't  exists yet. Cannot assign CubePL initialization expression. Skip.",
                                    uniq_name.c_str()
                                );
#endif
                    }else
                    {
                        _met->set_aggr_plus_expression( expression );
                    }
                  }else
                  {
                  std::string expression = parseContext.str.str();
                  std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                  cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                  std::string nested_error;
                  if (! driver->test( cubepl_program, nested_error ))
                  {
                    parseContext.syntax_ok = false;
                  }
                  delete driver;
                  }
                  parseContext.syntax_ok &= true;
                }
#line 2528 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 160: // flex_aggr_minus: "cube::metric::minus::" INIT_METRIC_NAME GhostMetricDefinition
#line 2043 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                if (!parseContext.test_modus)
                {
                  std::string expression = parseContext.str.str();
                  parseContext.str.str("");
                  std::string uniq_name = parseContext.name_of_metric;
                  Metric * _met = parseContext.cube->get_met(uniq_name);

                    if (_met == NULL)
                    {
#ifdef HAVE_CUBELIB_DEBUG
                                UTILS_DEBUG_PRINTF
                                (
                                    ( CUBELIB_DEBUG_CUBEPL_PARSER | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                                    " Metric with uniq name  %s doesn't  exists yet. Cannot assign CubePL initialization expression. Skip.",
                                    uniq_name.c_str()
                                );
#endif
                    }else
                    {
                        _met->set_aggr_minus_expression( expression );
                    }
                  }else
                  {
                  std::string expression = parseContext.str.str();
                  std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                  cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                  std::string nested_error;
                  if (! driver->test( cubepl_program, nested_error ))
                  {
                    parseContext.syntax_ok = false;
                  }
                  delete driver;
                  }
                  parseContext.syntax_ok &= true;
                }
#line 2569 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 161: // get_variable: get_variable_simple
#line 2084 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 2586 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 162: // get_variable: get_variable_indexed
#line 2097 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 2603 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 163: // get_variable_simple: "$" "{" string_constant "}"
#line 2112 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
                if (!parseContext.test_modus)
                {
                    parseContext._stack.push( new ConstantEvaluation(0) ); // pushed index 0 if array index is not specified
                }
                parseContext.syntax_ok &= true;
            }
#line 2615 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 165: // sizeof_variable: "sizeof" "(" string_constant ")"
#line 2125 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
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
#line 2630 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 166: // defined_variable: "defined" "(" string_constant ")"
#line 2137 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
            {
        if (!parseContext.test_modus)
        {
            std::string _string = parseContext.string_constants.top();
            parseContext.string_constants.pop();
            DefinedVariableEvaluation * _sizeof_var_eval = new DefinedVariableEvaluation(  _string, parseContext.cube->get_cubepl_memory_manager(), parseContext.cube  );
            parseContext._stack.push( _sizeof_var_eval );
        }
            }
#line 2644 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 167: // local_variable: "local" "(" string_constant ")"
#line 2147 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
        if (!parseContext.test_modus)
        {
            std::string _string = parseContext.string_constants.top();
           parseContext.cube->get_cubepl_memory_manager()->register_variable( _string , CUBEPL_VARIABLE);
        }
        parseContext.syntax_ok &= true;
        }
#line 2657 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 168: // global_variable: "global" "(" string_constant ")"
#line 2156 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
        if (!parseContext.test_modus)
        {
            std::string _string = parseContext.string_constants.top();
            parseContext.cube->get_cubepl_memory_manager()->register_variable( _string , CUBEPL_GLOBAL_VARIABLE);
        }
        parseContext.syntax_ok &= true;
        }
#line 2670 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;

  case 169: // string_constant: STRING_CONSTANT
#line 2166 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            if (!parseContext.test_modus)
            {
                parseContext.string_constants.push(parseContext.value);
                parseContext.value = "";
            }
            parseContext.syntax_ok &= true;
        }
#line 2683 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
    break;


#line 2687 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"

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
  CubePL1Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  CubePL1Parser::yytnamerr_ (const char *yystr)
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
  CubePL1Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // CubePL1Parser::context.
  CubePL1Parser::context::context (const CubePL1Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  CubePL1Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  CubePL1Parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  CubePL1Parser::yysyntax_error_ (const context& yyctx) const
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


  const short CubePL1Parser::yypact_ninf_ = -222;

  const signed char CubePL1Parser::yytable_ninf_ = -1;

  const short
  CubePL1Parser::yypact_[] =
  {
      18,   275,     7,  -222,   417,   417,  -222,    22,    49,   417,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
       9,   -41,   -23,   -14,    60,    78,    96,    48,  -222,  -222,
     266,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
     123,  -222,   124,  -222,  -222,  -222,  -222,  -222,  -222,   117,
    -222,  -222,  -222,  -222,  -222,  -222,     5,   209,    62,    62,
      21,    62,   134,   135,   136,   417,   417,   417,   141,  -222,
     417,   417,   417,   417,   417,   417,   417,   142,   149,   150,
     153,   152,    81,    90,    91,    93,    99,    92,   168,   169,
    -222,  -222,  -222,  -222,  -222,  -222,   175,  -222,  -222,   154,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,   190,   199,  -222,   187,    -5,    24,   417,
     216,   224,   244,   131,     5,     5,   202,   202,  -222,   251,
      31,    62,    62,   346,   346,    62,   196,   267,   196,   196,
     196,   268,   417,   211,   117,  -222,     4,   117,   417,  -222,
    -222,   222,  -222,  -222,  -222,  -222,    13,  -222,    14,    47,
    -222,  -222,  -222,   243,  -222,   417,   250,   257,   346,   270,
    -222,  -222,    66,    76,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
      88,   261,   201,  -222,   -28,  -222,  -222,  -222,   131,   163,
    -222,  -222,   272,   175,   237,   240,  -222,   276,   231,   417,
    -222,   -39,  -222,   -39,   -39,  -222,   258,  -222,  -222,    11,
      94,   346,   417,   417,   417,   417,   417,   417,   417,   417,
     198,  -222,   346,   346,   346,   175,   278,  -222,  -222,   281,
     282,   229,  -222,   346,  -222,  -222,  -222,  -222,   191,   287,
     309,    32,  -222,  -222,    97,   231,   231,   231,   231,   231,
     231,   231,   231,  -222,  -222,  -222,  -222,  -222,  -222,   417,
     196,   196,   131,   119,  -222,  -222,  -222,  -222,   417,  -222,
     200,  -222,  -222,   310,   175,   120,  -222,  -222,  -222,   -39,
     311,  -222
  };

  const unsigned char
  CubePL1Parser::yydefact_[] =
  {
       0,     0,     0,     3,     0,     0,   115,     0,     0,     0,
      33,    34,    79,    80,    81,    82,    83,    86,    87,    84,
      85,    89,    88,    90,    91,    92,    93,    94,    96,    97,
       0,     0,     0,     0,     0,     0,     0,     0,    98,    68,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    18,
      31,    32,    20,    21,    69,    70,    71,    22,    12,    76,
       0,    77,     0,    13,    14,    99,   100,   101,    15,   116,
      19,   161,   162,    16,    17,     1,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   118,   129,   130,   132,   131,     0,   119,   120,     0,
     146,   147,   124,   150,   151,   152,   125,   126,   127,   121,
     122,    23,   169,     0,     0,    24,     0,     0,     0,     0,
       0,     0,     0,     0,    25,    26,    28,    27,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   116,   143,   133,   116,     0,   165,
     166,   163,   102,   110,   111,   112,     0,   105,     0,     0,
      74,    72,    73,     0,    78,     0,     0,     0,     0,     0,
      53,    54,     0,     0,    35,    42,    43,    44,    45,    46,
      36,    37,    38,    39,    40,    41,    47,    61,    62,    63,
       0,     0,     0,   153,     0,   158,   159,   160,     0,     0,
     113,   117,     0,     0,   136,   137,   134,     0,   145,     0,
     103,     0,   106,     0,     0,    75,     0,   167,   168,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   140,     0,     0,     0,     0,   148,   157,   156,     0,
       0,     0,   114,     0,   141,   135,   138,   142,     0,     0,
       0,     0,    95,    48,     0,    57,    55,    64,    65,    59,
      60,    56,    58,    67,    66,    50,    51,    52,   144,     0,
       0,     0,     0,     0,   164,   104,   107,   108,     0,    49,
       0,   154,   155,     0,     0,     0,   149,   128,   139,     0,
       0,   109
  };

  const short
  CubePL1Parser::yypgoto_[] =
  {
    -222,  -222,    -1,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -139,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -142,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -133,  -222,
    -222,  -222,  -123,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
      98,  -222,  -222,   100,  -221,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -149,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,   -48
  };

  const short
  CubePL1Parser::yydefgoto_[] =
  {
       0,     2,   192,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   284,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,   176,    68,
     163,    69,   108,   109,   110,   111,   112,   113,   114,   115,
     224,   225,   116,   226,   166,   167,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   213,   258,   126,   127,   128,
      70,    71,    72,    73,    74,   129,   130,   133
  };

  const short
  CubePL1Parser::yytable_[] =
  {
      40,   183,   264,    76,    77,   178,   172,    75,    80,   215,
     216,   217,    92,    93,    94,   210,    90,    91,    92,    93,
      94,     1,   131,    81,   230,   232,    90,    91,    92,    93,
      94,   134,    78,   136,   288,   177,    90,    91,    92,    93,
      94,   221,    82,   297,   227,   135,   173,   174,   175,   240,
     222,   223,    90,    91,    92,    93,    94,   259,   260,    79,
      83,   242,   243,   244,   245,   246,   247,   248,   249,    84,
      85,    90,    91,    92,    93,    94,   261,   250,   231,   233,
     173,   174,   175,   308,   140,   141,   142,   251,    86,   144,
     145,   146,   147,   148,   149,   150,   185,   298,   269,   255,
     270,   271,   274,   186,   187,   273,    87,   211,   299,   173,
     174,   175,   234,   285,   286,   287,   242,   243,   244,   245,
     246,   247,   248,   249,   293,    90,    91,    92,    93,    94,
     304,    88,   250,    95,    96,   252,   253,   254,   179,    97,
      98,   301,   302,   132,   137,   138,   139,   252,   253,   254,
     303,   143,   151,   252,   253,   254,   252,   253,   254,   152,
     153,   219,    99,   154,   156,   100,   155,   228,    90,    91,
      92,    93,    94,   157,   158,   161,   310,   159,   252,   253,
     254,   101,   262,   160,   236,   309,   162,   239,   164,   165,
     102,   103,   104,   105,   106,   107,    90,    91,    92,    93,
      94,   169,   171,   168,   294,    90,    91,    92,    93,    94,
     170,    94,   212,   306,    90,    91,    92,    93,    94,    39,
     131,    90,    91,    92,    93,    94,   220,   180,   268,    90,
      91,    92,    93,    94,   229,   181,    90,    91,    92,    93,
      94,   275,   276,   277,   278,   279,   280,   281,   282,    90,
      91,    92,    93,    94,   235,   182,    90,    91,    92,    93,
      94,   237,   184,    90,    91,    92,    93,    94,   238,   272,
      89,    90,    91,    92,    93,    94,   256,   214,   218,     3,
     241,     4,   263,   257,   223,     5,   222,   283,   300,     6,
     289,   267,   290,   291,   292,     7,     8,   305,   295,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
     296,   307,   311,   266,   265,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,     0,    31,    32,    33,    34,    35,    36,     0,     0,
       0,     0,     4,     0,    37,    38,   188,     0,     0,     0,
       6,     0,     0,    39,     0,     0,     7,     8,     0,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   189,     0,     0,     0,   190,   191,
      30,     0,     0,    31,    32,    33,    34,    35,    36,     0,
       0,     0,     0,     4,     0,    37,    38,     5,     0,     0,
       0,     6,     0,     0,    39,     0,     0,     7,     8,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,     0,     0,    31,    32,    33,    34,    35,    36,
       0,     0,     0,     0,     0,     0,    37,    38,     0,     0,
       0,     0,     0,     0,     0,    39
  };

  const short
  CubePL1Parser::yycheck_[] =
  {
       1,   143,   223,     4,     5,   138,    11,     0,     9,   158,
     159,   160,     7,     8,     9,   154,     5,     6,     7,     8,
       9,     3,    11,    14,    11,    11,     5,     6,     7,     8,
       9,    79,    10,    81,   255,    11,     5,     6,     7,     8,
       9,   164,    83,    11,   167,    24,    85,    86,    87,   188,
      46,    47,     5,     6,     7,     8,     9,    85,    86,    10,
      83,    50,    51,    52,    53,    54,    55,    56,    57,    83,
      10,     5,     6,     7,     8,     9,   218,    66,    65,    65,
      85,    86,    87,   304,    85,    86,    87,    11,    10,    90,
      91,    92,    93,    94,    95,    96,    65,    65,   231,    11,
     233,   234,   241,   151,   152,    11,    10,   155,    11,    85,
      86,    87,    65,   252,   253,   254,    50,    51,    52,    53,
      54,    55,    56,    57,   263,     5,     6,     7,     8,     9,
      11,    83,    66,    10,    10,    59,    60,    61,   139,    22,
      23,   290,   291,    81,    10,    10,    10,    59,    60,    61,
     292,    10,    10,    59,    60,    61,    59,    60,    61,    10,
      10,   162,    45,    10,    83,    48,    14,   168,     5,     6,
       7,     8,     9,    83,    83,    83,   309,    84,    59,    60,
      61,    64,    19,    84,   185,    65,    18,   188,    19,    14,
      73,    74,    75,    76,    77,    78,     5,     6,     7,     8,
       9,    11,    15,    49,    13,     5,     6,     7,     8,     9,
      11,     9,    16,    13,     5,     6,     7,     8,     9,    88,
      11,     5,     6,     7,     8,     9,    15,    11,   229,     5,
       6,     7,     8,     9,    12,    11,     5,     6,     7,     8,
       9,   242,   243,   244,   245,   246,   247,   248,   249,     5,
       6,     7,     8,     9,    11,    11,     5,     6,     7,     8,
       9,    11,    11,     5,     6,     7,     8,     9,    11,    11,
       4,     5,     6,     7,     8,     9,    15,    10,    10,     4,
      10,     6,    10,    82,    47,    10,    46,    89,   289,    14,
      12,    15,    11,    11,    65,    20,    21,   298,    11,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      11,    11,    11,   225,   224,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    -1,    -1,
      -1,    -1,     6,    -1,    79,    80,    10,    -1,    -1,    -1,
      14,    -1,    -1,    88,    -1,    -1,    20,    21,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    63,
      64,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,     6,    -1,    79,    80,    10,    -1,    -1,
      -1,    14,    -1,    -1,    88,    -1,    -1,    20,    21,    -1,
      -1,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88
  };

  const unsigned char
  CubePL1Parser::yystos_[] =
  {
       0,     3,    93,     4,     6,    10,    14,    20,    21,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      64,    67,    68,    69,    70,    71,    72,    79,    80,    88,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   141,   143,
     172,   173,   174,   175,   176,     0,    94,    94,    10,    10,
      94,    14,    83,    83,    83,    10,    10,    10,    83,     4,
       5,     6,     7,     8,     9,    10,    10,    22,    23,    45,
      48,    64,    73,    74,    75,    76,    77,    78,   144,   145,
     146,   147,   148,   149,   150,   151,   154,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   169,   170,   171,   177,
     178,    11,    81,   179,   179,    24,   179,    10,    10,    10,
      94,    94,    94,    10,    94,    94,    94,    94,    94,    94,
      94,    10,    10,    10,    10,    14,    83,    83,    83,    84,
      84,    83,    18,   142,    19,    14,   156,   157,    49,    11,
      11,    15,    11,    85,    86,    87,   140,    11,   140,    94,
      11,    11,    11,   124,    11,    65,   179,   179,    10,    58,
      62,    63,    94,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     106,   179,    16,   167,    10,   167,   167,   167,    10,    94,
      15,   144,    46,    47,   152,   153,   155,   144,    94,    12,
      11,    65,    11,    65,    65,    11,    94,    11,    11,    94,
     106,    10,    50,    51,    52,    53,    54,    55,    56,    57,
      66,    11,    59,    60,    61,    11,    15,    82,   168,    85,
      86,   124,    19,    10,   156,   155,   152,    15,    94,   140,
     140,   140,    11,    11,   106,    94,    94,    94,    94,    94,
      94,    94,    94,    89,   123,   106,   106,   106,   156,    12,
      11,    11,    65,   106,    13,    11,    11,    11,    65,    11,
      94,   167,   167,   124,    11,    94,    13,    11,   156,    65,
     140,    11
  };

  const unsigned char
  CubePL1Parser::yyr1_[] =
  {
       0,    92,    93,    93,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   103,   104,   105,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   107,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   119,   119,   120,   121,   122,   123,   124,   125,
     125,   125,   126,   127,   128,   129,   130,   130,   131,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   133,   134,   134,   135,   136,
     136,   136,   137,   137,   137,   138,   138,   138,   139,   139,
     140,   140,   140,   141,   142,   143,   144,   144,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   146,   147,
     147,   147,   147,   148,   149,   150,   151,   152,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   160,   161,   162,
     163,   163,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   172,   173,   174,   175,   176,   177,   178,   179
  };

  const signed char
  CubePL1Parser::yyr2_[] =
  {
       0,     2,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       3,     3,     3,     1,     1,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     3,     3,     3,     1,     1,     1,
       1,     1,     4,     4,     4,     5,     1,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     6,     1,     1,     1,     1,
       1,     1,     4,     5,     7,     4,     5,     7,     7,    11,
       1,     1,     1,     4,     3,     1,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     7,     1,
       1,     1,     1,     2,     3,     4,     3,     1,     2,     5,
       4,     2,     3,     1,     5,     3,     1,     1,     4,     7,
       1,     1,     1,     3,     6,     6,     2,     1,     3,     3,
       3,     1,     1,     4,     7,     4,     4,     4,     4,     1
  };


#if CUBEPLPARSERDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const CubePL1Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"<cubepl>\"",
  "\"</cubepl>\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"^\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"<<\"", "\">>\"",
  "\"return\"", "\";\"", "\"sizeof\"", "\"defined\"", "\"local\"",
  "\"global\"", "\"|\"", "\"arg1\"", "\"arg2\"", "\"sqrt\"", "\"sin\"",
  "\"asin\"", "\"cos\"", "\"acos\"", "\"tan\"", "\"atan\"", "\"exp\"",
  "\"log\"", "\"abs\"", "\"random\"", "\"sgn\"", "\"pos\"", "\"neg\"",
  "\"floor\"", "\"ceil\"", "\"min\"", "\"max\"", "\"if\"", "\"elseif\"",
  "\"else\"", "\"while\"", "\"=\"", "\">\"", "\"==\"", "\"eq\"", "\"seq\"",
  "\">=\"", "\"<=\"", "\"!=\"", "\"<\"", "\"not\"", "\"and\"", "\"or\"",
  "\"xor\"", "\"true\"", "\"false\"", "\"$\"", "\",\"", "\"=~\"",
  "\"metric::\"", "\"metric::fixed::\"", "\"metric::call::\"", "\"env\"",
  "\"lowercase\"", "\"uppercase\"", "\"cube::metric::postderived::\"",
  "\"cube::metric::prederived::\"", "\"cube::init::metric::\"",
  "\"cube::metric::plus::\"", "\"cube::metric::minus::\"",
  "\"cube::metric::set::\"", "\"cube::metric::get::\"", "CONSTANT",
  "STRING_CONSTANT", "STRING_TEXT", "METRIC_NAME", "INIT_METRIC_NAME",
  "\"i\"", "\"e\"", "SAME_MODIFICATOR", "QUOTED_STRING", "REGEXP_STRING",
  "FUNC2", "SIGN", "$accept", "document", "expression",
  "enclosed_expression", "absolute_value", "sum", "subtract", "division",
  "multiplication", "power", "negation", "arguments", "argument1",
  "argument2", "boolean_expression", "enclosed_boolean_expression",
  "and_expression", "or_expression", "xor_expression", "true_expression",
  "false_expression", "equality", "not_equality", "bigger", "smaller",
  "halfbigger", "halfsmaller", "string_operation", "string_equality",
  "string_semi_equality", "regexp", "regexp_expression", "quoted_string",
  "string_function", "lowercase", "uppercase", "getenv", "metric_get",
  "function_call", "one_variable_function", "function_name",
  "two_variables_function", "function2_name", "constant", "metric_refs",
  "context_metric", "fixed_metric", "metric_call",
  "calculationFlavourModificator", "lambda_calcul", "return_expression",
  "lambda_start", "list_of_statements", "statement", "metric_set",
  "if_statement", "simple_if_statement", "full_if_statement",
  "elseif_full_if_statement", "elseif_if_statement", "elseifs",
  "elseif_enclosed_list_of_statements", "if_condition",
  "else_enclosed_list_of_statements", "enclosed_list_of_statements",
  "enclosed_list_of_statements_start", "while_statement", "assignment",
  "assignment_target", "put_variable", "put_variable_indexed",
  "create_ghost_metric", "create_postderived_ghost_metric",
  "create_prederived_inclusive_ghost_metric",
  "create_prederived_exclusive_ghost_metric", "GhostMetricDefinition",
  "CubePLGhostText", "init_metric", "flex_aggr_plus", "flex_aggr_minus",
  "get_variable", "get_variable_simple", "get_variable_indexed",
  "sizeof_variable", "defined_variable", "local_variable",
  "global_variable", "string_constant", YY_NULLPTR
  };
#endif


#if CUBEPLPARSERDEBUG
  const short
  CubePL1Parser::yyrline_[] =
  {
       0,   316,   316,   325,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   354,   364,   377,   390,   404,   417,   433,
     445,   457,   457,   459,   468,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   496,   506,
     517,   530,   544,   557,   565,   574,   588,   602,   615,   629,
     643,   659,   660,   661,   666,   679,   691,   706,   734,   745,
     745,   745,   750,   761,   773,   787,   817,   817,   819,   834,
     842,   850,   858,   866,   874,   882,   890,   898,   906,   914,
     922,   930,   938,   946,   954,   965,   981,   989,  1000,  1011,
    1011,  1011,  1016,  1044,  1074,  1110,  1138,  1179,  1234,  1288,
    1365,  1373,  1381,  1392,  1422,  1424,  1433,  1435,  1441,  1452,
    1463,  1474,  1478,  1482,  1493,  1497,  1501,  1505,  1511,  1542,
    1543,  1544,  1545,  1549,  1576,  1615,  1658,  1691,  1692,  1695,
    1705,  1708,  1711,  1714,  1724,  1753,  1770,  1770,  1773,  1783,
    1787,  1788,  1789,  1793,  1847,  1900,  1955,  1958,  1964,  2003,
    2042,  2083,  2096,  2111,  2120,  2124,  2136,  2146,  2155,  2165
  };

  void
  CubePL1Parser::yy_stack_print_ () const
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
  CubePL1Parser::yy_reduce_print_ (int yyrule) const
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

  CubePL1Parser::symbol_kind_type
  CubePL1Parser::yytranslate_ (int t) YY_NOEXCEPT
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
      80,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      81,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      82,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      83,    84,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      88,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      89,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      87,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    85,
      86,    90,    91
    };
    // Last valid token kind.
    const int code_max = 682;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // cubeplparser
#line 3535 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"

#line 2175 "../../cubelib/build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
 /*** Additional Code ***/


void cubeplparser::CubePL1Parser::error(const CubePL1Parser::location_type& l,
                                  const std::string& m)
{

    CubePL1Parser::location_type _l = l;


    _l.end.column = (_l.end.column<9)?1: _l.end.column-8;
    _l.begin.column = _l.end.column-1;

    parseContext.syntax_ok = false;
    stringstream sstr;
    string       str;
    sstr << _l;
    sstr >> str;
    parseContext.error_message = str + ":" + m;
    parseContext.error_place = _l;

/*   if (strstr(m.c_str(),"expecting <?xml")!=NULL) {
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
*/
}
