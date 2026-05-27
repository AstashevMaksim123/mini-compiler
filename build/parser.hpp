/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_MATVEEVDA_PROJECTS_MINI_COMPILER_BUILD_PARSER_HPP_INCLUDED
# define YY_YY_HOME_MATVEEVDA_PROJECTS_MINI_COMPILER_BUILD_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 35 "/home/matveevda/projects/mini_compiler/src/parser.y"

#include "ast.hpp"
#include "parser_context.hpp"

#include <cstdint>
#include <vector>

#ifndef YYLTYPE_IS_DECLARED
struct MiniYYLType {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};

#define YYLTYPE MiniYYLType
#define YYLTYPE_IS_DECLARED 1
#endif

#line 69 "/home/matveevda/projects/mini_compiler/build/parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENT = 258,                   /* IDENT  */
    INT_LITERAL = 259,             /* INT_LITERAL  */
    FN = 260,                      /* FN  */
    LET = 261,                     /* LET  */
    MUT = 262,                     /* MUT  */
    IF = 263,                      /* IF  */
    ELSE = 264,                    /* ELSE  */
    FOR = 265,                     /* FOR  */
    RETURN = 266,                  /* RETURN  */
    SWITCH = 267,                  /* SWITCH  */
    CASE = 268,                    /* CASE  */
    DEFAULT = 269,                 /* DEFAULT  */
    BREAK = 270,                   /* BREAK  */
    CONTINUE = 271,                /* CONTINUE  */
    TRUE = 272,                    /* TRUE  */
    FALSE = 273,                   /* FALSE  */
    INT_TY = 274,                  /* INT_TY  */
    BOOL_TY = 275,                 /* BOOL_TY  */
    EQ = 276,                      /* EQ  */
    NE = 277,                      /* NE  */
    LE = 278,                      /* LE  */
    GE = 279,                      /* GE  */
    ANDAND = 280,                  /* ANDAND  */
    OROR = 281,                    /* OROR  */
    ARROW = 282,                   /* ARROW  */
    UMINUS = 283                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 59 "/home/matveevda/projects/mini_compiler/src/parser.y"

    char* str;
    std::int64_t int_val;
    mini::TypeKind type;
    mini::Expr* expr;
    mini::Stmt* stmt;
    mini::BlockStmt* block;
    mini::CaseClause* case_clause;
    mini::FunctionDecl* function;
    mini::Param* param;
    std::vector<mini::Expr*>* expr_list;
    std::vector<mini::Stmt*>* stmt_list;
    std::vector<mini::CaseClause*>* case_list;
    std::vector<mini::FunctionDecl*>* function_list;
    std::vector<mini::Param*>* param_list;

#line 131 "/home/matveevda/projects/mini_compiler/build/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (mini::ParserContext& ctx);


#endif /* !YY_YY_HOME_MATVEEVDA_PROJECTS_MINI_COMPILER_BUILD_PARSER_HPP_INCLUDED  */
