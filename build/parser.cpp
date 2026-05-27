/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/matveevda/projects/mini_compiler/src/parser.y"

#include "ast.hpp"
#include "parser_context.hpp"

#include <cstdlib>
#include <string>
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

int yylex(void);
void yyerror(mini::ParserContext& ctx, const char* msg);
extern YYLTYPE yylloc;

static mini::SourceRange makeRange(const YYLTYPE& loc) {
    mini::SourceRange range;
    range.begin.line = loc.first_line;
    range.begin.column = loc.first_column;
    range.end.line = loc.last_line;
    range.end.column = loc.last_column;
    return range;
}

#line 105 "/home/matveevda/projects/mini_compiler/build/parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENT = 3,                      /* IDENT  */
  YYSYMBOL_INT_LITERAL = 4,                /* INT_LITERAL  */
  YYSYMBOL_FN = 5,                         /* FN  */
  YYSYMBOL_LET = 6,                        /* LET  */
  YYSYMBOL_MUT = 7,                        /* MUT  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_SWITCH = 12,                    /* SWITCH  */
  YYSYMBOL_CASE = 13,                      /* CASE  */
  YYSYMBOL_DEFAULT = 14,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 16,                  /* CONTINUE  */
  YYSYMBOL_TRUE = 17,                      /* TRUE  */
  YYSYMBOL_FALSE = 18,                     /* FALSE  */
  YYSYMBOL_INT_TY = 19,                    /* INT_TY  */
  YYSYMBOL_BOOL_TY = 20,                   /* BOOL_TY  */
  YYSYMBOL_EQ = 21,                        /* EQ  */
  YYSYMBOL_NE = 22,                        /* NE  */
  YYSYMBOL_LE = 23,                        /* LE  */
  YYSYMBOL_GE = 24,                        /* GE  */
  YYSYMBOL_ANDAND = 25,                    /* ANDAND  */
  YYSYMBOL_OROR = 26,                      /* OROR  */
  YYSYMBOL_ARROW = 27,                     /* ARROW  */
  YYSYMBOL_28_ = 28,                       /* '<'  */
  YYSYMBOL_29_ = 29,                       /* '>'  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '*'  */
  YYSYMBOL_33_ = 33,                       /* '/'  */
  YYSYMBOL_34_ = 34,                       /* '%'  */
  YYSYMBOL_UMINUS = 35,                    /* UMINUS  */
  YYSYMBOL_36_ = 36,                       /* '!'  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_38_ = 38,                       /* ')'  */
  YYSYMBOL_39_ = 39,                       /* ','  */
  YYSYMBOL_40_ = 40,                       /* ':'  */
  YYSYMBOL_41_ = 41,                       /* '{'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
  YYSYMBOL_43_ = 43,                       /* ';'  */
  YYSYMBOL_44_ = 44,                       /* '='  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_function_list = 47,             /* function_list  */
  YYSYMBOL_function = 48,                  /* function  */
  YYSYMBOL_params = 49,                    /* params  */
  YYSYMBOL_param_list_nonempty = 50,       /* param_list_nonempty  */
  YYSYMBOL_param = 51,                     /* param  */
  YYSYMBOL_type = 52,                      /* type  */
  YYSYMBOL_block = 53,                     /* block  */
  YYSYMBOL_stmt_list = 54,                 /* stmt_list  */
  YYSYMBOL_stmt = 55,                      /* stmt  */
  YYSYMBOL_simple_stmt = 56,               /* simple_stmt  */
  YYSYMBOL_var_decl_stmt = 57,             /* var_decl_stmt  */
  YYSYMBOL_assign_stmt = 58,               /* assign_stmt  */
  YYSYMBOL_return_stmt = 59,               /* return_stmt  */
  YYSYMBOL_break_stmt = 60,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 61,             /* continue_stmt  */
  YYSYMBOL_expr_stmt = 62,                 /* expr_stmt  */
  YYSYMBOL_if_stmt = 63,                   /* if_stmt  */
  YYSYMBOL_for_stmt = 64,                  /* for_stmt  */
  YYSYMBOL_switch_stmt = 65,               /* switch_stmt  */
  YYSYMBOL_case_list = 66,                 /* case_list  */
  YYSYMBOL_case_clause = 67,               /* case_clause  */
  YYSYMBOL_expr = 68,                      /* expr  */
  YYSYMBOL_logical_or = 69,                /* logical_or  */
  YYSYMBOL_logical_and = 70,               /* logical_and  */
  YYSYMBOL_equality = 71,                  /* equality  */
  YYSYMBOL_relational = 72,                /* relational  */
  YYSYMBOL_additive = 73,                  /* additive  */
  YYSYMBOL_multiplicative = 74,            /* multiplicative  */
  YYSYMBOL_unary = 75,                     /* unary  */
  YYSYMBOL_call = 76,                      /* call  */
  YYSYMBOL_arg_list = 77,                  /* arg_list  */
  YYSYMBOL_arg_list_nonempty = 78,         /* arg_list_nonempty  */
  YYSYMBOL_primary = 79                    /* primary  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


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


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   134

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   283


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,     2,     2,    34,     2,     2,
      37,    38,    32,    30,    39,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    43,
      28,    44,    29,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   107,   107,   114,   118,   125,   134,   137,   143,   147,
     154,   162,   163,   167,   174,   177,   184,   185,   186,   187,
     188,   192,   193,   194,   195,   196,   197,   201,   206,   214,
     222,   228,   234,   240,   246,   249,   255,   258,   264,   271,
     275,   282,   285,   291,   295,   296,   300,   301,   305,   306,
     307,   311,   312,   313,   314,   315,   319,   320,   321,   325,
     326,   327,   328,   332,   333,   334,   338,   344,   348,   351,
     355,   359,   366,   367,   368,   369,   374
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "IDENT", "INT_LITERAL", "FN",
  "LET", "MUT", "IF", "ELSE", "FOR", "RETURN", "SWITCH", "CASE", "DEFAULT",
  "BREAK", "CONTINUE", "TRUE", "FALSE", "INT_TY", "BOOL_TY", "EQ", "NE",
  "LE", "GE", "ANDAND", "OROR", "ARROW", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "UMINUS", "'!'", "'('", "')'", "','", "':'", "'{'", "'}'",
  "';'", "'='", "$accept", "program", "function_list", "function",
  "params", "param_list_nonempty", "param", "type", "block", "stmt_list",
  "stmt", "simple_stmt", "var_decl_stmt", "assign_stmt", "return_stmt",
  "break_stmt", "continue_stmt", "expr_stmt", "if_stmt", "for_stmt",
  "switch_stmt", "case_list", "case_clause", "expr", "logical_or",
  "logical_and", "equality", "relational", "additive", "multiplicative",
  "unary", "call", "arg_list", "arg_list_nonempty", "primary", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-33)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      11,    20,    42,    11,   -33,    12,   -33,   -33,    57,    33,
      36,    40,   -33,    28,    53,    57,   -33,   -33,   -33,    28,
     -33,    43,   -33,   -33,     9,   -30,   -33,    15,    35,    38,
      35,    35,   -33,   -33,   -33,   -33,    35,    35,    35,   -33,
     -33,   -33,   -33,    44,    45,    46,    47,    48,    49,   -33,
     -33,   -33,   -33,    55,    58,    37,     5,    34,    -2,   -33,
     -33,   -33,    35,    35,    56,    82,    60,    43,    50,    52,
      59,   -33,    65,   -33,   -33,    62,   -33,   -33,   -33,   -33,
     -33,   -33,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,   -33,    63,    68,   -33,    28,
      69,    77,    35,    35,    54,   -33,    58,    37,     5,     5,
      34,    34,    34,    34,    -2,    -2,   -33,   -33,   -33,   -33,
      35,    64,    28,    43,    67,    70,    94,    43,    -5,   -33,
     -33,    35,    73,   -33,   108,   108,    43,   -33,   -33,   -33,
     -33,    35,    43,    43,   -33,   -33,   -33,   -33
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     4,     6,     0,
       0,     7,     8,     0,     0,     0,    11,    12,    10,     0,
       9,     0,    14,     5,     0,    75,    72,     0,     0,     0,
       0,     0,    31,    32,    73,    74,     0,     0,     0,    13,
      17,    15,    16,     0,     0,     0,     0,     0,     0,    18,
      19,    20,    33,    43,    45,    47,    50,    55,    58,    62,
      65,    67,    68,     0,     0,     0,    75,     0,     0,     0,
       0,    30,     0,    63,    64,     0,    21,    22,    23,    24,
      25,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,     0,    69,    29,     0,
       0,    35,     0,     0,     0,    76,    44,    46,    48,    49,
      53,    54,    51,    52,    56,    57,    59,    60,    61,    66,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    39,
      71,     0,     0,    34,     0,     0,     0,    42,    38,    40,
      28,     0,     0,     0,    41,    27,    36,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -33,   -33,   -33,   117,   -33,   -33,   106,   -17,   -24,   -33,
     -33,   -33,    93,   -19,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,    -4,   -27,   -33,    41,    51,   -15,   -32,   -13,
     -31,   -33,   -33,   -33,   -33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    10,    11,    12,    18,    23,    24,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,   128,   129,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    96,    97,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    67,    21,    71,    72,    73,    74,    62,   126,   127,
      70,    75,    25,    26,    63,    27,     1,    28,    64,    29,
      30,    31,    65,     5,    32,    33,    34,    35,    86,    87,
      92,    93,    94,    88,    89,    95,    98,   138,    66,    26,
      36,    68,     6,   101,    27,    37,    38,    16,    17,     8,
      22,    39,    34,    35,   110,   111,   112,   113,    84,    85,
       9,   116,   117,   118,    90,    91,    36,   126,   127,   108,
     109,    37,    38,    13,    14,   124,   125,   114,   115,    15,
      19,    82,   121,    83,    22,   100,   123,    76,    77,    78,
      79,    80,    81,   130,    63,   102,    99,    62,   136,   133,
     105,   119,   103,   137,   140,   132,   104,   120,   131,   122,
     134,    68,   144,   135,   145,   142,   143,   141,   146,   147,
       7,    20,    69,   106,   139,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   107
};

static const yytype_int16 yycheck[] =
{
      24,    28,    19,    30,    31,    36,    37,    37,    13,    14,
      29,    38,     3,     4,    44,     6,     5,     8,     3,    10,
      11,    12,     7,     3,    15,    16,    17,    18,    23,    24,
      32,    33,    34,    28,    29,    62,    63,    42,     3,     4,
      31,     3,     0,    67,     6,    36,    37,    19,    20,    37,
      41,    42,    17,    18,    86,    87,    88,    89,    21,    22,
       3,    92,    93,    94,    30,    31,    31,    13,    14,    84,
      85,    36,    37,    40,    38,   102,   103,    90,    91,    39,
      27,    26,    99,    25,    41,     3,     9,    43,    43,    43,
      43,    43,    43,   120,    44,    43,    40,    37,     4,   123,
      38,    38,    43,   127,   131,   122,    41,    39,    44,    40,
      43,     3,   136,    43,   141,   134,   135,    44,   142,   143,
       3,    15,    29,    82,   128,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    46,    47,    48,     3,     0,    48,    37,     3,
      49,    50,    51,    40,    38,    39,    19,    20,    52,    27,
      51,    52,    41,    53,    54,     3,     4,     6,     8,    10,
      11,    12,    15,    16,    17,    18,    31,    36,    37,    42,
      53,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    79,    37,    44,     3,     7,     3,    68,     3,    57,
      58,    68,    68,    75,    75,    68,    43,    43,    43,    43,
      43,    43,    26,    25,    21,    22,    23,    24,    28,    29,
      30,    31,    32,    33,    34,    68,    77,    78,    68,    40,
       3,    53,    43,    43,    41,    38,    70,    71,    72,    72,
      73,    73,    73,    73,    74,    74,    75,    75,    75,    38,
      39,    52,    40,     9,    68,    68,    13,    14,    66,    67,
      68,    44,    52,    53,    43,    43,     4,    53,    42,    67,
      68,    44,    58,    58,    53,    68,    53,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    49,    49,    50,    50,
      51,    52,    52,    53,    54,    54,    55,    55,    55,    55,
      55,    56,    56,    56,    56,    56,    56,    57,    57,    58,
      59,    60,    61,    62,    63,    63,    64,    64,    65,    66,
      66,    67,    67,    68,    69,    69,    70,    70,    71,    71,
      71,    72,    72,    72,    72,    72,    73,    73,    73,    74,
      74,    74,    74,    75,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    79,    79,    79
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     8,     0,     1,     1,     3,
       3,     1,     1,     3,     0,     2,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     7,     6,     3,
       2,     1,     1,     1,     5,     3,     7,     7,     5,     1,
       2,     3,     2,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     1,     4,     1,     0,     1,
       1,     3,     1,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (ctx, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, ctx); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mini::ParserContext& ctx)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (ctx);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mini::ParserContext& ctx)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, ctx);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, mini::ParserContext& ctx)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), ctx);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, ctx); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, mini::ParserContext& ctx)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (ctx);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_IDENT: /* IDENT  */
#line 95 "/home/matveevda/projects/mini_compiler/src/parser.y"
            { free(((*yyvaluep).str)); }
#line 1314 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (mini::ParserContext& ctx)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: function_list  */
#line 107 "/home/matveevda/projects/mini_compiler/src/parser.y"
                  {
        ctx.program = std::make_unique<mini::Program>(*(yyvsp[0].function_list));
        delete (yyvsp[0].function_list);
    }
#line 1615 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 3: /* function_list: function  */
#line 114 "/home/matveevda/projects/mini_compiler/src/parser.y"
             {
        (yyval.function_list) = new std::vector<mini::FunctionDecl*>();
        (yyval.function_list)->push_back((yyvsp[0].function));
    }
#line 1624 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 4: /* function_list: function_list function  */
#line 118 "/home/matveevda/projects/mini_compiler/src/parser.y"
                             {
        (yyvsp[-1].function_list)->push_back((yyvsp[0].function));
        (yyval.function_list) = (yyvsp[-1].function_list);
    }
#line 1633 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 5: /* function: FN IDENT '(' params ')' ARROW type block  */
#line 125 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                             {
        std::string name((yyvsp[-6].str));
        free((yyvsp[-6].str));
        (yyval.function) = new mini::FunctionDecl(makeRange((yyloc)), name, *(yyvsp[-4].param_list), (yyvsp[-1].type), (yyvsp[0].block));
        delete (yyvsp[-4].param_list);
    }
#line 1644 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 6: /* params: %empty  */
#line 134 "/home/matveevda/projects/mini_compiler/src/parser.y"
    {
        (yyval.param_list) = new std::vector<mini::Param*>();
    }
#line 1652 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 7: /* params: param_list_nonempty  */
#line 137 "/home/matveevda/projects/mini_compiler/src/parser.y"
                          {
        (yyval.param_list) = (yyvsp[0].param_list);
    }
#line 1660 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 8: /* param_list_nonempty: param  */
#line 143 "/home/matveevda/projects/mini_compiler/src/parser.y"
          {
        (yyval.param_list) = new std::vector<mini::Param*>();
        (yyval.param_list)->push_back((yyvsp[0].param));
    }
#line 1669 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 9: /* param_list_nonempty: param_list_nonempty ',' param  */
#line 147 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                    {
        (yyvsp[-2].param_list)->push_back((yyvsp[0].param));
        (yyval.param_list) = (yyvsp[-2].param_list);
    }
#line 1678 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 10: /* param: IDENT ':' type  */
#line 154 "/home/matveevda/projects/mini_compiler/src/parser.y"
                   {
        std::string name((yyvsp[-2].str));
        free((yyvsp[-2].str));
        (yyval.param) = new mini::Param(makeRange((yyloc)), name, (yyvsp[0].type));
    }
#line 1688 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 11: /* type: INT_TY  */
#line 162 "/home/matveevda/projects/mini_compiler/src/parser.y"
           { (yyval.type) = mini::TypeKind::Int; }
#line 1694 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 12: /* type: BOOL_TY  */
#line 163 "/home/matveevda/projects/mini_compiler/src/parser.y"
              { (yyval.type) = mini::TypeKind::Bool; }
#line 1700 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 13: /* block: '{' stmt_list '}'  */
#line 167 "/home/matveevda/projects/mini_compiler/src/parser.y"
                      {
        (yyval.block) = new mini::BlockStmt(makeRange((yyloc)), *(yyvsp[-1].stmt_list));
        delete (yyvsp[-1].stmt_list);
    }
#line 1709 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 14: /* stmt_list: %empty  */
#line 174 "/home/matveevda/projects/mini_compiler/src/parser.y"
    {
        (yyval.stmt_list) = new std::vector<mini::Stmt*>();
    }
#line 1717 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 15: /* stmt_list: stmt_list stmt  */
#line 177 "/home/matveevda/projects/mini_compiler/src/parser.y"
                     {
        (yyvsp[-1].stmt_list)->push_back((yyvsp[0].stmt));
        (yyval.stmt_list) = (yyvsp[-1].stmt_list);
    }
#line 1726 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 16: /* stmt: simple_stmt  */
#line 184 "/home/matveevda/projects/mini_compiler/src/parser.y"
                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1732 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 17: /* stmt: block  */
#line 185 "/home/matveevda/projects/mini_compiler/src/parser.y"
            { (yyval.stmt) = (yyvsp[0].block); }
#line 1738 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 18: /* stmt: if_stmt  */
#line 186 "/home/matveevda/projects/mini_compiler/src/parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1744 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 19: /* stmt: for_stmt  */
#line 187 "/home/matveevda/projects/mini_compiler/src/parser.y"
               { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1750 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 20: /* stmt: switch_stmt  */
#line 188 "/home/matveevda/projects/mini_compiler/src/parser.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1756 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 21: /* simple_stmt: var_decl_stmt ';'  */
#line 192 "/home/matveevda/projects/mini_compiler/src/parser.y"
                      { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1762 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 22: /* simple_stmt: assign_stmt ';'  */
#line 193 "/home/matveevda/projects/mini_compiler/src/parser.y"
                      { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1768 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 23: /* simple_stmt: return_stmt ';'  */
#line 194 "/home/matveevda/projects/mini_compiler/src/parser.y"
                      { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1774 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 24: /* simple_stmt: break_stmt ';'  */
#line 195 "/home/matveevda/projects/mini_compiler/src/parser.y"
                     { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1780 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 25: /* simple_stmt: continue_stmt ';'  */
#line 196 "/home/matveevda/projects/mini_compiler/src/parser.y"
                        { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1786 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 26: /* simple_stmt: expr_stmt ';'  */
#line 197 "/home/matveevda/projects/mini_compiler/src/parser.y"
                    { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1792 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 27: /* var_decl_stmt: LET MUT IDENT ':' type '=' expr  */
#line 201 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                    {
        std::string name((yyvsp[-4].str));
        free((yyvsp[-4].str));
        (yyval.stmt) = new mini::VarDeclStmt(makeRange((yyloc)), name, (yyvsp[-2].type), true, (yyvsp[0].expr));
    }
#line 1802 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 28: /* var_decl_stmt: LET IDENT ':' type '=' expr  */
#line 206 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                  {
        std::string name((yyvsp[-4].str));
        free((yyvsp[-4].str));
        (yyval.stmt) = new mini::VarDeclStmt(makeRange((yyloc)), name, (yyvsp[-2].type), false, (yyvsp[0].expr));
    }
#line 1812 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 29: /* assign_stmt: IDENT '=' expr  */
#line 214 "/home/matveevda/projects/mini_compiler/src/parser.y"
                   {
        std::string name((yyvsp[-2].str));
        free((yyvsp[-2].str));
        (yyval.stmt) = new mini::AssignStmt(makeRange((yyloc)), name, (yyvsp[0].expr));
    }
#line 1822 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 30: /* return_stmt: RETURN expr  */
#line 222 "/home/matveevda/projects/mini_compiler/src/parser.y"
                {
        (yyval.stmt) = new mini::ReturnStmt(makeRange((yyloc)), (yyvsp[0].expr));
    }
#line 1830 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 31: /* break_stmt: BREAK  */
#line 228 "/home/matveevda/projects/mini_compiler/src/parser.y"
          {
        (yyval.stmt) = new mini::BreakStmt(makeRange((yyloc)));
    }
#line 1838 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 32: /* continue_stmt: CONTINUE  */
#line 234 "/home/matveevda/projects/mini_compiler/src/parser.y"
             {
        (yyval.stmt) = new mini::ContinueStmt(makeRange((yyloc)));
    }
#line 1846 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 33: /* expr_stmt: expr  */
#line 240 "/home/matveevda/projects/mini_compiler/src/parser.y"
         {
        (yyval.stmt) = new mini::ExprStmt(makeRange((yyloc)), (yyvsp[0].expr));
    }
#line 1854 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 34: /* if_stmt: IF expr block ELSE block  */
#line 246 "/home/matveevda/projects/mini_compiler/src/parser.y"
                             {
        (yyval.stmt) = new mini::IfStmt(makeRange((yyloc)), (yyvsp[-3].expr), (yyvsp[-2].block), (yyvsp[0].block));
    }
#line 1862 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 35: /* if_stmt: IF expr block  */
#line 249 "/home/matveevda/projects/mini_compiler/src/parser.y"
                    {
        (yyval.stmt) = new mini::IfStmt(makeRange((yyloc)), (yyvsp[-1].expr), (yyvsp[0].block), nullptr);
    }
#line 1870 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 36: /* for_stmt: FOR var_decl_stmt ';' expr ';' assign_stmt block  */
#line 255 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                                     {
        (yyval.stmt) = new mini::ForStmt(makeRange((yyloc)), (yyvsp[-5].stmt), (yyvsp[-3].expr), (yyvsp[-1].stmt), (yyvsp[0].block));
    }
#line 1878 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 37: /* for_stmt: FOR assign_stmt ';' expr ';' assign_stmt block  */
#line 258 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                                     {
        (yyval.stmt) = new mini::ForStmt(makeRange((yyloc)), (yyvsp[-5].stmt), (yyvsp[-3].expr), (yyvsp[-1].stmt), (yyvsp[0].block));
    }
#line 1886 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 38: /* switch_stmt: SWITCH expr '{' case_list '}'  */
#line 264 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                  {
        (yyval.stmt) = new mini::SwitchStmt(makeRange((yyloc)), (yyvsp[-3].expr), *(yyvsp[-1].case_list));
        delete (yyvsp[-1].case_list);
    }
#line 1895 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 39: /* case_list: case_clause  */
#line 271 "/home/matveevda/projects/mini_compiler/src/parser.y"
                {
        (yyval.case_list) = new std::vector<mini::CaseClause*>();
        (yyval.case_list)->push_back((yyvsp[0].case_clause));
    }
#line 1904 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 40: /* case_list: case_list case_clause  */
#line 275 "/home/matveevda/projects/mini_compiler/src/parser.y"
                            {
        (yyvsp[-1].case_list)->push_back((yyvsp[0].case_clause));
        (yyval.case_list) = (yyvsp[-1].case_list);
    }
#line 1913 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 41: /* case_clause: CASE INT_LITERAL block  */
#line 282 "/home/matveevda/projects/mini_compiler/src/parser.y"
                           {
        (yyval.case_clause) = new mini::CaseClause(makeRange((yyloc)), false, (yyvsp[-1].int_val), (yyvsp[0].block));
    }
#line 1921 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 42: /* case_clause: DEFAULT block  */
#line 285 "/home/matveevda/projects/mini_compiler/src/parser.y"
                    {
        (yyval.case_clause) = new mini::CaseClause(makeRange((yyloc)), true, 0, (yyvsp[0].block));
    }
#line 1929 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 43: /* expr: logical_or  */
#line 291 "/home/matveevda/projects/mini_compiler/src/parser.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1935 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 44: /* logical_or: logical_or OROR logical_and  */
#line 295 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "||", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1941 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 45: /* logical_or: logical_and  */
#line 296 "/home/matveevda/projects/mini_compiler/src/parser.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 1947 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 46: /* logical_and: logical_and ANDAND equality  */
#line 300 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "&&", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1953 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 47: /* logical_and: equality  */
#line 301 "/home/matveevda/projects/mini_compiler/src/parser.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1959 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 48: /* equality: equality EQ relational  */
#line 305 "/home/matveevda/projects/mini_compiler/src/parser.y"
                           { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "==", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1965 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 49: /* equality: equality NE relational  */
#line 306 "/home/matveevda/projects/mini_compiler/src/parser.y"
                             { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "!=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1971 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 50: /* equality: relational  */
#line 307 "/home/matveevda/projects/mini_compiler/src/parser.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 1977 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 51: /* relational: relational '<' additive  */
#line 311 "/home/matveevda/projects/mini_compiler/src/parser.y"
                            { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "<", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1983 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 52: /* relational: relational '>' additive  */
#line 312 "/home/matveevda/projects/mini_compiler/src/parser.y"
                              { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), ">", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1989 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 53: /* relational: relational LE additive  */
#line 313 "/home/matveevda/projects/mini_compiler/src/parser.y"
                             { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "<=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1995 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 54: /* relational: relational GE additive  */
#line 314 "/home/matveevda/projects/mini_compiler/src/parser.y"
                             { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), ">=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2001 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 55: /* relational: additive  */
#line 315 "/home/matveevda/projects/mini_compiler/src/parser.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 2007 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 56: /* additive: additive '+' multiplicative  */
#line 319 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "+", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2013 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 57: /* additive: additive '-' multiplicative  */
#line 320 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                  { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "-", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2019 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 58: /* additive: multiplicative  */
#line 321 "/home/matveevda/projects/mini_compiler/src/parser.y"
                     { (yyval.expr) = (yyvsp[0].expr); }
#line 2025 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 59: /* multiplicative: multiplicative '*' unary  */
#line 325 "/home/matveevda/projects/mini_compiler/src/parser.y"
                             { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "*", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2031 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 60: /* multiplicative: multiplicative '/' unary  */
#line 326 "/home/matveevda/projects/mini_compiler/src/parser.y"
                               { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "/", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2037 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 61: /* multiplicative: multiplicative '%' unary  */
#line 327 "/home/matveevda/projects/mini_compiler/src/parser.y"
                               { (yyval.expr) = new mini::BinaryExpr(makeRange((yyloc)), "%", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2043 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 62: /* multiplicative: unary  */
#line 328 "/home/matveevda/projects/mini_compiler/src/parser.y"
            { (yyval.expr) = (yyvsp[0].expr); }
#line 2049 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 63: /* unary: '-' unary  */
#line 332 "/home/matveevda/projects/mini_compiler/src/parser.y"
                           { (yyval.expr) = new mini::UnaryExpr(makeRange((yyloc)), "-", (yyvsp[0].expr)); }
#line 2055 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 64: /* unary: '!' unary  */
#line 333 "/home/matveevda/projects/mini_compiler/src/parser.y"
                { (yyval.expr) = new mini::UnaryExpr(makeRange((yyloc)), "!", (yyvsp[0].expr)); }
#line 2061 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 65: /* unary: call  */
#line 334 "/home/matveevda/projects/mini_compiler/src/parser.y"
           { (yyval.expr) = (yyvsp[0].expr); }
#line 2067 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 66: /* call: IDENT '(' arg_list ')'  */
#line 338 "/home/matveevda/projects/mini_compiler/src/parser.y"
                           {
        std::string callee((yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.expr) = new mini::CallExpr(makeRange((yyloc)), callee, *(yyvsp[-1].expr_list));
        delete (yyvsp[-1].expr_list);
    }
#line 2078 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 67: /* call: primary  */
#line 344 "/home/matveevda/projects/mini_compiler/src/parser.y"
              { (yyval.expr) = (yyvsp[0].expr); }
#line 2084 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 68: /* arg_list: %empty  */
#line 348 "/home/matveevda/projects/mini_compiler/src/parser.y"
    {
        (yyval.expr_list) = new std::vector<mini::Expr*>();
    }
#line 2092 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 69: /* arg_list: arg_list_nonempty  */
#line 351 "/home/matveevda/projects/mini_compiler/src/parser.y"
                        { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 2098 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 70: /* arg_list_nonempty: expr  */
#line 355 "/home/matveevda/projects/mini_compiler/src/parser.y"
         {
        (yyval.expr_list) = new std::vector<mini::Expr*>();
        (yyval.expr_list)->push_back((yyvsp[0].expr));
    }
#line 2107 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 71: /* arg_list_nonempty: arg_list_nonempty ',' expr  */
#line 359 "/home/matveevda/projects/mini_compiler/src/parser.y"
                                 {
        (yyvsp[-2].expr_list)->push_back((yyvsp[0].expr));
        (yyval.expr_list) = (yyvsp[-2].expr_list);
    }
#line 2116 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 72: /* primary: INT_LITERAL  */
#line 366 "/home/matveevda/projects/mini_compiler/src/parser.y"
                { (yyval.expr) = new mini::IntLiteralExpr(makeRange((yyloc)), (yyvsp[0].int_val)); }
#line 2122 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 73: /* primary: TRUE  */
#line 367 "/home/matveevda/projects/mini_compiler/src/parser.y"
           { (yyval.expr) = new mini::BoolLiteralExpr(makeRange((yyloc)), true); }
#line 2128 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 74: /* primary: FALSE  */
#line 368 "/home/matveevda/projects/mini_compiler/src/parser.y"
            { (yyval.expr) = new mini::BoolLiteralExpr(makeRange((yyloc)), false); }
#line 2134 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 75: /* primary: IDENT  */
#line 369 "/home/matveevda/projects/mini_compiler/src/parser.y"
            {
        std::string name((yyvsp[0].str));
        free((yyvsp[0].str));
        (yyval.expr) = new mini::VarExpr(makeRange((yyloc)), name);
    }
#line 2144 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;

  case 76: /* primary: '(' expr ')'  */
#line 374 "/home/matveevda/projects/mini_compiler/src/parser.y"
                   { (yyval.expr) = (yyvsp[-1].expr); }
#line 2150 "/home/matveevda/projects/mini_compiler/build/parser.cpp"
    break;


#line 2154 "/home/matveevda/projects/mini_compiler/build/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (ctx, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, ctx);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, ctx);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (ctx, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, ctx);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, ctx);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 377 "/home/matveevda/projects/mini_compiler/src/parser.y"


void yyerror(mini::ParserContext& ctx, const char* msg) {
    ctx.report(makeRange(yylloc), msg);
}
