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
#line 1 "src/gocompiler.y"

    /*  
    *   João Afonso dos Santos Simões   -  2022236316
    *   Rodrigo Miguel Santos Rodrigues -  2022233032
    */

    #include <stdio.h>
    #include "ast.h"
    
    int yylex(void);
    extern char* yytext;

    void yyerror(char* s);

    struct node* program;
    struct node* aux_node;
    struct node* aux_node2;

    int errors_count = 0;

#line 92 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    COMMA = 259,                   /* COMMA  */
    BLANKID = 260,                 /* BLANKID  */
    ASSIGN = 261,                  /* ASSIGN  */
    STAR = 262,                    /* STAR  */
    DIV = 263,                     /* DIV  */
    MINUS = 264,                   /* MINUS  */
    PLUS = 265,                    /* PLUS  */
    EQ = 266,                      /* EQ  */
    GE = 267,                      /* GE  */
    GT = 268,                      /* GT  */
    LBRACE = 269,                  /* LBRACE  */
    LE = 270,                      /* LE  */
    LPAR = 271,                    /* LPAR  */
    LSQ = 272,                     /* LSQ  */
    LT = 273,                      /* LT  */
    MOD = 274,                     /* MOD  */
    NE = 275,                      /* NE  */
    NOT = 276,                     /* NOT  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    RBRACE = 279,                  /* RBRACE  */
    RPAR = 280,                    /* RPAR  */
    RSQ = 281,                     /* RSQ  */
    PACKAGE = 282,                 /* PACKAGE  */
    RETURN = 283,                  /* RETURN  */
    ELSE = 284,                    /* ELSE  */
    FOR = 285,                     /* FOR  */
    IF = 286,                      /* IF  */
    VAR = 287,                     /* VAR  */
    INT = 288,                     /* INT  */
    FLOAT32 = 289,                 /* FLOAT32  */
    BOOL = 290,                    /* BOOL  */
    STRING = 291,                  /* STRING  */
    PRINT = 292,                   /* PRINT  */
    PARSEINT = 293,                /* PARSEINT  */
    FUNC = 294,                    /* FUNC  */
    CMDARGS = 295,                 /* CMDARGS  */
    IDENTIFIER = 296,              /* IDENTIFIER  */
    STRLIT = 297,                  /* STRLIT  */
    NATURAL = 298,                 /* NATURAL  */
    DECIMAL = 299,                 /* DECIMAL  */
    RESERVED = 300,                /* RESERVED  */
    ELSE_IF = 301                  /* ELSE_IF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define SEMICOLON 258
#define COMMA 259
#define BLANKID 260
#define ASSIGN 261
#define STAR 262
#define DIV 263
#define MINUS 264
#define PLUS 265
#define EQ 266
#define GE 267
#define GT 268
#define LBRACE 269
#define LE 270
#define LPAR 271
#define LSQ 272
#define LT 273
#define MOD 274
#define NE 275
#define NOT 276
#define AND 277
#define OR 278
#define RBRACE 279
#define RPAR 280
#define RSQ 281
#define PACKAGE 282
#define RETURN 283
#define ELSE 284
#define FOR 285
#define IF 286
#define VAR 287
#define INT 288
#define FLOAT32 289
#define BOOL 290
#define STRING 291
#define PRINT 292
#define PARSEINT 293
#define FUNC 294
#define CMDARGS 295
#define IDENTIFIER 296
#define STRLIT 297
#define NATURAL 298
#define DECIMAL 299
#define RESERVED 300
#define ELSE_IF 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "src/gocompiler.y"

    char* token;
    struct node* node;

#line 242 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_COMMA = 4,                      /* COMMA  */
  YYSYMBOL_BLANKID = 5,                    /* BLANKID  */
  YYSYMBOL_ASSIGN = 6,                     /* ASSIGN  */
  YYSYMBOL_STAR = 7,                       /* STAR  */
  YYSYMBOL_DIV = 8,                        /* DIV  */
  YYSYMBOL_MINUS = 9,                      /* MINUS  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_EQ = 11,                        /* EQ  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_GT = 13,                        /* GT  */
  YYSYMBOL_LBRACE = 14,                    /* LBRACE  */
  YYSYMBOL_LE = 15,                        /* LE  */
  YYSYMBOL_LPAR = 16,                      /* LPAR  */
  YYSYMBOL_LSQ = 17,                       /* LSQ  */
  YYSYMBOL_LT = 18,                        /* LT  */
  YYSYMBOL_MOD = 19,                       /* MOD  */
  YYSYMBOL_NE = 20,                        /* NE  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_RPAR = 25,                      /* RPAR  */
  YYSYMBOL_RSQ = 26,                       /* RSQ  */
  YYSYMBOL_PACKAGE = 27,                   /* PACKAGE  */
  YYSYMBOL_RETURN = 28,                    /* RETURN  */
  YYSYMBOL_ELSE = 29,                      /* ELSE  */
  YYSYMBOL_FOR = 30,                       /* FOR  */
  YYSYMBOL_IF = 31,                        /* IF  */
  YYSYMBOL_VAR = 32,                       /* VAR  */
  YYSYMBOL_INT = 33,                       /* INT  */
  YYSYMBOL_FLOAT32 = 34,                   /* FLOAT32  */
  YYSYMBOL_BOOL = 35,                      /* BOOL  */
  YYSYMBOL_STRING = 36,                    /* STRING  */
  YYSYMBOL_PRINT = 37,                     /* PRINT  */
  YYSYMBOL_PARSEINT = 38,                  /* PARSEINT  */
  YYSYMBOL_FUNC = 39,                      /* FUNC  */
  YYSYMBOL_CMDARGS = 40,                   /* CMDARGS  */
  YYSYMBOL_IDENTIFIER = 41,                /* IDENTIFIER  */
  YYSYMBOL_STRLIT = 42,                    /* STRLIT  */
  YYSYMBOL_NATURAL = 43,                   /* NATURAL  */
  YYSYMBOL_DECIMAL = 44,                   /* DECIMAL  */
  YYSYMBOL_RESERVED = 45,                  /* RESERVED  */
  YYSYMBOL_ELSE_IF = 46,                   /* ELSE_IF  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_Program = 48,                   /* Program  */
  YYSYMBOL_Declarations = 49,              /* Declarations  */
  YYSYMBOL_VarDeclaration = 50,            /* VarDeclaration  */
  YYSYMBOL_VarSpec = 51,                   /* VarSpec  */
  YYSYMBOL_VarSpecAux = 52,                /* VarSpecAux  */
  YYSYMBOL_Type = 53,                      /* Type  */
  YYSYMBOL_FuncDeclaration = 54,           /* FuncDeclaration  */
  YYSYMBOL_Parameters = 55,                /* Parameters  */
  YYSYMBOL_ParametersAux = 56,             /* ParametersAux  */
  YYSYMBOL_FuncBody = 57,                  /* FuncBody  */
  YYSYMBOL_VarsAndStatements = 58,         /* VarsAndStatements  */
  YYSYMBOL_Statement = 59,                 /* Statement  */
  YYSYMBOL_StatementAux = 60,              /* StatementAux  */
  YYSYMBOL_ParseArgs = 61,                 /* ParseArgs  */
  YYSYMBOL_FuncInvocation = 62,            /* FuncInvocation  */
  YYSYMBOL_FuncInvocationAux = 63,         /* FuncInvocationAux  */
  YYSYMBOL_Expr = 64                       /* Expr  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   326

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    50,    50,    54,    55,    56,    59,    60,    64,    75,
      80,    84,    85,    86,    87,    91,   103,   114,   125,   140,
     154,   160,   163,   167,   168,   169,   170,   174,   179,   191,
     206,   217,   227,   236,   237,   238,   239,   240,   241,   242,
     246,   247,   250,   258,   268,   277,   281,   293,   294,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "COMMA",
  "BLANKID", "ASSIGN", "STAR", "DIV", "MINUS", "PLUS", "EQ", "GE", "GT",
  "LBRACE", "LE", "LPAR", "LSQ", "LT", "MOD", "NE", "NOT", "AND", "OR",
  "RBRACE", "RPAR", "RSQ", "PACKAGE", "RETURN", "ELSE", "FOR", "IF", "VAR",
  "INT", "FLOAT32", "BOOL", "STRING", "PRINT", "PARSEINT", "FUNC",
  "CMDARGS", "IDENTIFIER", "STRLIT", "NATURAL", "DECIMAL", "RESERVED",
  "ELSE_IF", "$accept", "Program", "Declarations", "VarDeclaration",
  "VarSpec", "VarSpecAux", "Type", "FuncDeclaration", "Parameters",
  "ParametersAux", "FuncBody", "VarsAndStatements", "Statement",
  "StatementAux", "ParseArgs", "FuncInvocation", "FuncInvocationAux",
  "Expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-67)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-42)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -7,   -26,    26,    27,   -67,    -5,   -12,    -2,   -67,    38,
      40,     4,    56,   -67,    28,    -5,    -5,    59,    31,   126,
     -13,   -67,   -67,    48,    56,   -67,   -67,   -67,   -67,   -67,
      32,   126,    52,   -67,   -67,   -67,    64,   -67,    78,    32,
      96,   -67,    50,   -67,    64,   -67,   -67,   -67,   111,   -67,
     137,   122,   137,    76,     1,    90,    93,   -67,   -67,   126,
     -67,    97,    81,   137,   137,    74,   137,    86,   -67,   -67,
     -67,   273,   111,   239,   256,   113,   102,   137,    60,   -67,
     -67,    78,   111,   -67,   -67,   -67,    83,   201,   -67,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,    87,   111,   111,    88,   220,   108,   273,    91,
     -67,   164,   -67,   -67,   -67,   -67,   -67,   -67,     6,     6,
      79,    79,    79,    79,    79,   -67,    79,   306,   290,   -67,
      95,   106,   -67,   -67,   107,   -67,   137,   115,   -67,    92,
     128,   164,   -67,   135,     0,   -67,   111,   125,   134,   140,
     -67,   137,   -67,   181,   142,   -67
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     5,     0,     0,     2,     0,
       0,     0,    10,     6,     0,     5,     5,     0,     0,     0,
       0,     3,     4,     0,    10,    11,    12,    13,    14,     8,
       0,     0,     0,     7,     9,    26,     0,    16,    21,     0,
       0,    18,     0,    19,     0,    17,    39,    25,     0,    22,
      34,     0,     0,     0,     0,     0,     0,    36,    35,     0,
      15,     0,     0,     0,     0,     0,     0,    67,    65,    66,
      68,    33,     0,     0,     0,     0,     0,     0,     0,    23,
      24,    21,     0,    28,    63,    64,     0,     0,    62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,     0,
      45,    48,    20,    40,    70,    69,    59,    60,    58,    57,
      53,    56,    52,    55,    51,    61,    54,    50,    49,    32,
       0,     0,    38,    37,     0,    46,     0,     0,    31,    30,
       0,    48,    44,     0,     0,    47,     0,     0,     0,     0,
      43,     0,    29,     0,     0,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,     3,   129,   159,   161,   -28,   -67,   -67,   114,
      35,   -67,   157,   -66,   -67,   -40,    57,   -42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     8,     9,    13,    19,    29,    10,    32,    43,
      37,    40,    61,    62,    57,    70,   137,    71
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,   147,    36,    38,    11,    76,   102,    77,    58,    73,
      74,    44,    30,    89,    90,     3,   113,    78,    21,    22,
       1,    84,    85,    87,    88,    98,     4,     6,    31,    12,
       5,    81,    58,   106,     7,   108,   111,   130,   131,    14,
     148,    15,    58,    16,    20,    12,    35,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
      18,   109,    23,    58,    58,    25,    26,    27,    28,    63,
      64,    41,    24,    33,    45,    86,    65,    39,    35,    60,
     149,    66,    42,    63,    64,   110,    89,    90,    91,    92,
      65,    59,    75,    79,   141,    66,    80,    46,    98,    47,
      82,    67,    78,    68,    69,    83,    58,   107,   114,   153,
      48,   129,    46,   132,   134,    67,   135,    68,    69,   138,
      49,   143,    63,    64,    50,    48,    51,    52,     6,    65,
     139,    63,    64,    53,    66,   -41,    72,    54,    65,    50,
     142,    51,    52,    66,   144,   140,    63,    64,    53,   146,
     150,   151,    54,    65,    67,   105,    68,    69,    66,    25,
      26,    27,    28,    67,   152,    68,    69,   155,   136,    55,
      17,    89,    90,    91,    92,    93,    94,    95,    67,    96,
      68,    69,    97,    98,    99,    34,   100,   101,    89,    90,
      91,    92,    93,    94,    95,   112,    96,    56,   145,    97,
      98,    99,     0,   100,   101,     0,     0,   154,    89,    90,
      91,    92,    93,    94,    95,     0,    96,     0,     0,    97,
      98,    99,     0,   100,   101,     0,   115,    89,    90,    91,
      92,    93,    94,    95,     0,    96,     0,     0,    97,    98,
      99,     0,   100,   101,     0,   133,    89,    90,    91,    92,
      93,    94,    95,   103,    96,     0,     0,    97,    98,    99,
       0,   100,   101,    89,    90,    91,    92,    93,    94,    95,
     104,    96,     0,     0,    97,    98,    99,     0,   100,   101,
      89,    90,    91,    92,    93,    94,    95,     0,    96,     0,
       0,    97,    98,    99,     0,   100,   101,    89,    90,    91,
      92,    93,    94,    95,     0,    96,     0,     0,    97,    98,
      99,     0,   100,    89,    90,    91,    92,    93,    94,    95,
       0,    96,     0,     0,    97,    98,    99
};

static const yytype_int16 yycheck[] =
{
      40,     1,    30,    31,    16,     4,    72,     6,    48,    51,
      52,    39,    25,     7,     8,    41,    82,    16,    15,    16,
      27,    63,    64,    65,    66,    19,     0,    32,    41,    41,
       3,    59,    72,    75,    39,    77,    78,   103,   104,    41,
      40,     3,    82,     3,    16,    41,    14,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
       4,     1,     3,   103,   104,    33,    34,    35,    36,     9,
      10,    36,    41,    25,    39,     1,    16,    25,    14,    44,
     146,    21,     4,     9,    10,    25,     7,     8,     9,    10,
      16,    41,    16,     3,   136,    21,     3,     1,    19,     3,
       3,    41,    16,    43,    44,    24,   146,     5,    25,   151,
      14,    24,     1,    25,     6,    41,    25,    43,    44,    24,
      24,    29,     9,    10,    28,    14,    30,    31,    32,    16,
      24,     9,    10,    37,    21,    24,    14,    41,    16,    28,
      25,    30,    31,    21,    16,    38,     9,    10,    37,    14,
      25,    17,    41,    16,    41,    42,    43,    44,    21,    33,
      34,    35,    36,    41,    24,    43,    44,    25,     4,    40,
      11,     7,     8,     9,    10,    11,    12,    13,    41,    15,
      43,    44,    18,    19,    20,    24,    22,    23,     7,     8,
       9,    10,    11,    12,    13,    81,    15,    40,   141,    18,
      19,    20,    -1,    22,    23,    -1,    -1,    26,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    -1,    -1,    18,
      19,    20,    -1,    22,    23,    -1,    25,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    -1,    -1,    18,    19,
      20,    -1,    22,    23,    -1,    25,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    18,    19,    20,
      -1,    22,    23,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    19,    20,    -1,    22,    23,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    -1,
      -1,    18,    19,    20,    -1,    22,    23,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    -1,    -1,    18,    19,
      20,    -1,    22,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    -1,    -1,    18,    19,    20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    27,    48,    41,     0,     3,    32,    39,    49,    50,
      54,    16,    41,    51,    41,     3,     3,    51,     4,    52,
      16,    49,    49,     3,    41,    33,    34,    35,    36,    53,
      25,    41,    55,    25,    52,    14,    53,    57,    53,    25,
      58,    57,     4,    56,    53,    57,     1,     3,    14,    24,
      28,    30,    31,    37,    41,    50,    59,    61,    62,    41,
      57,    59,    60,     9,    10,    16,    21,    41,    43,    44,
      62,    64,    14,    64,    64,    16,     4,     6,    16,     3,
       3,    53,     3,    24,    64,    64,     1,    64,    64,     7,
       8,     9,    10,    11,    12,    13,    15,    18,    19,    20,
      22,    23,    60,    14,    14,    42,    64,     5,    64,     1,
      25,    64,    56,    60,    25,    25,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    24,
      60,    60,    25,    25,     6,    25,     4,    63,    24,    24,
      38,    64,    25,    29,    16,    63,    14,     1,    40,    60,
      25,    17,    24,    64,    26,    25
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    49,    50,    50,    51,    52,
      52,    53,    53,    53,    53,    54,    54,    54,    54,    55,
      56,    56,    57,    58,    58,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      60,    60,    61,    61,    62,    62,    62,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     3,     0,     2,     5,     3,     3,
       0,     1,     1,     1,     1,     7,     5,     6,     6,     3,
       4,     0,     3,     3,     3,     2,     0,     3,     3,     9,
       5,     5,     4,     2,     1,     1,     1,     4,     4,     1,
       3,     0,    11,     8,     5,     3,     4,     3,     0,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     1,     1,     1,     1,     3,
       3
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: PACKAGE IDENTIFIER SEMICOLON Declarations  */
#line 50 "src/gocompiler.y"
                                                { (yyval.node) = program = new_node(Program, NULL); add_child(program, (yyvsp[0].node)); }
#line 1417 "y.tab.c"
    break;

  case 3: /* Declarations: VarDeclaration SEMICOLON Declarations  */
#line 54 "src/gocompiler.y"
                                                    { (yyval.node) = (yyvsp[-2].node); add_brother((yyval.node), (yyvsp[0].node)); }
#line 1423 "y.tab.c"
    break;

  case 4: /* Declarations: FuncDeclaration SEMICOLON Declarations  */
#line 55 "src/gocompiler.y"
                                                    { (yyval.node) = (yyvsp[-2].node); add_brother((yyval.node), (yyvsp[0].node)); }
#line 1429 "y.tab.c"
    break;

  case 5: /* Declarations: %empty  */
#line 56 "src/gocompiler.y"
                                                    { (yyval.node) = NULL; }
#line 1435 "y.tab.c"
    break;

  case 6: /* VarDeclaration: VAR VarSpec  */
#line 59 "src/gocompiler.y"
                                              { (yyval.node) = (yyvsp[0].node); }
#line 1441 "y.tab.c"
    break;

  case 7: /* VarDeclaration: VAR LPAR VarSpec SEMICOLON RPAR  */
#line 60 "src/gocompiler.y"
                                              { (yyval.node) = (yyvsp[-2].node); }
#line 1447 "y.tab.c"
    break;

  case 8: /* VarSpec: IDENTIFIER VarSpecAux Type  */
#line 64 "src/gocompiler.y"
                                           {    
                                                (yyval.node) = new_node(VarDecl, NULL); 
                                                add_child((yyval.node), (yyvsp[0].node)); 
                                                add_child((yyval.node), new_node(Identifier, (yyvsp[-2].token))); 
                                                add_brother((yyval.node), (yyvsp[-1].node));

                                                add_type_to_brothers((yyval.node), (yyvsp[0].node)->category);   // Add the type to all the brothers
                                            }
#line 1460 "y.tab.c"
    break;

  case 9: /* VarSpecAux: COMMA IDENTIFIER VarSpecAux  */
#line 75 "src/gocompiler.y"
                                    { 
                                        (yyval.node) = new_node(VarDecl, NULL); 
                                        add_child((yyval.node), new_node(Identifier, (yyvsp[-1].token))); 
                                        add_brother((yyval.node), (yyvsp[0].node));
                                    }
#line 1470 "y.tab.c"
    break;

  case 10: /* VarSpecAux: %empty  */
#line 80 "src/gocompiler.y"
                                    { (yyval.node) = NULL; }
#line 1476 "y.tab.c"
    break;

  case 11: /* Type: INT  */
#line 84 "src/gocompiler.y"
                      { (yyval.node) = new_node(Int, NULL); }
#line 1482 "y.tab.c"
    break;

  case 12: /* Type: FLOAT32  */
#line 85 "src/gocompiler.y"
                      { (yyval.node) = new_node(Float32, NULL); }
#line 1488 "y.tab.c"
    break;

  case 13: /* Type: BOOL  */
#line 86 "src/gocompiler.y"
                      { (yyval.node) = new_node(Bool, NULL); }
#line 1494 "y.tab.c"
    break;

  case 14: /* Type: STRING  */
#line 87 "src/gocompiler.y"
                      { (yyval.node) = new_node(String, NULL); }
#line 1500 "y.tab.c"
    break;

  case 15: /* FuncDeclaration: FUNC IDENTIFIER LPAR Parameters RPAR Type FuncBody  */
#line 91 "src/gocompiler.y"
                                                        {   
                                                            (yyval.node) = new_node(FuncDecl, NULL);

                                                            // Create the FuncHeader node (Identifier, FuncParams, Type)
                                                            aux_node = new_node(FuncHeader, NULL);
                                                            add_child(aux_node, new_node(Identifier, (yyvsp[-5].token)));
                                                            add_child(aux_node, (yyvsp[-1].node));
                                                            add_child(aux_node, (yyvsp[-3].node));

                                                            add_child((yyval.node), aux_node);
                                                            add_child((yyval.node), (yyvsp[0].node));
                                                        }
#line 1517 "y.tab.c"
    break;

  case 16: /* FuncDeclaration: FUNC IDENTIFIER LPAR RPAR FuncBody  */
#line 103 "src/gocompiler.y"
                                                        { 
                                                            (yyval.node) = new_node(FuncDecl, NULL);

                                                            // Create the FuncHeader node (Identifier, FuncParams = NULL)
                                                            aux_node = new_node(FuncHeader, NULL); 
                                                            add_child(aux_node, new_node(Identifier, (yyvsp[-3].token)));
                                                            add_child(aux_node, new_node(FuncParams, NULL));

                                                            add_child((yyval.node), aux_node);
                                                            add_child((yyval.node), (yyvsp[0].node));
                                                        }
#line 1533 "y.tab.c"
    break;

  case 17: /* FuncDeclaration: FUNC IDENTIFIER LPAR Parameters RPAR FuncBody  */
#line 114 "src/gocompiler.y"
                                                        { 
                                                            (yyval.node) = new_node(FuncDecl, NULL);

                                                            // Create the FuncHeader node (Identifier, FuncParams)
                                                            aux_node = new_node(FuncHeader, NULL);                                                            
                                                            add_child(aux_node, new_node(Identifier, (yyvsp[-4].token)));
                                                            add_child(aux_node, (yyvsp[-2].node));

                                                            add_child((yyval.node), aux_node);
                                                            add_child((yyval.node), (yyvsp[0].node));
                                                        }
#line 1549 "y.tab.c"
    break;

  case 18: /* FuncDeclaration: FUNC IDENTIFIER LPAR RPAR Type FuncBody  */
#line 125 "src/gocompiler.y"
                                                        { 
                                                            (yyval.node) = new_node(FuncDecl, NULL);
                                                            
                                                            // Create the FuncHeader node (Identifier, FuncParams = NULL, Type)
                                                            aux_node = new_node(FuncHeader, NULL);
                                                            add_child(aux_node, new_node(Identifier, (yyvsp[-4].token)));
                                                            add_child(aux_node, (yyvsp[-1].node));
                                                            add_child(aux_node, new_node(FuncParams, NULL));

                                                            add_child((yyval.node), aux_node);
                                                            add_child((yyval.node), (yyvsp[0].node));
                                                        }
#line 1566 "y.tab.c"
    break;

  case 19: /* Parameters: IDENTIFIER Type ParametersAux  */
#line 140 "src/gocompiler.y"
                                    { 
                                        (yyval.node) = new_node(FuncParams, NULL); 

                                        // Create ParamDecl node (Identifier, Type)
                                        aux_node = new_node(ParamDecl, NULL);
                                        add_child(aux_node, (yyvsp[-1].node)); 
                                        add_child(aux_node, new_node(Identifier, (yyvsp[-2].token))); 

                                        add_child((yyval.node), aux_node);
                                        add_child((yyval.node), (yyvsp[0].node));
                                    }
#line 1582 "y.tab.c"
    break;

  case 20: /* ParametersAux: COMMA IDENTIFIER Type ParametersAux  */
#line 154 "src/gocompiler.y"
                                            { 
                                                (yyval.node) = new_node(ParamDecl, NULL);
                                                add_child((yyval.node), (yyvsp[-1].node)); 
                                                add_child((yyval.node), new_node(Identifier, (yyvsp[-2].token))); 
                                                add_brother((yyval.node), (yyvsp[0].node));
                                            }
#line 1593 "y.tab.c"
    break;

  case 21: /* ParametersAux: %empty  */
#line 160 "src/gocompiler.y"
                                            { (yyval.node) = NULL; }
#line 1599 "y.tab.c"
    break;

  case 22: /* FuncBody: LBRACE VarsAndStatements RBRACE  */
#line 163 "src/gocompiler.y"
                                        { (yyval.node) = new_node(FuncBody, NULL); add_child((yyval.node), (yyvsp[-1].node)); }
#line 1605 "y.tab.c"
    break;

  case 23: /* VarsAndStatements: VarsAndStatements VarDeclaration SEMICOLON  */
#line 167 "src/gocompiler.y"
                                                    { if((yyvsp[-2].node) == NULL) { (yyval.node) = (yyvsp[-1].node); } else { (yyval.node) = (yyvsp[-2].node); add_brother((yyvsp[-2].node), (yyvsp[-1].node)); } }
#line 1611 "y.tab.c"
    break;

  case 24: /* VarsAndStatements: VarsAndStatements Statement SEMICOLON  */
#line 168 "src/gocompiler.y"
                                                    { if((yyvsp[-2].node) == NULL) { (yyval.node) = (yyvsp[-1].node); } else { (yyval.node) = (yyvsp[-2].node); add_brother((yyvsp[-2].node), (yyvsp[-1].node)); } }
#line 1617 "y.tab.c"
    break;

  case 25: /* VarsAndStatements: VarsAndStatements SEMICOLON  */
#line 169 "src/gocompiler.y"
                                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1623 "y.tab.c"
    break;

  case 26: /* VarsAndStatements: %empty  */
#line 170 "src/gocompiler.y"
                                                    { (yyval.node) = NULL; }
#line 1629 "y.tab.c"
    break;

  case 27: /* Statement: IDENTIFIER ASSIGN Expr  */
#line 174 "src/gocompiler.y"
                                                                            { 
                                                                                (yyval.node) = new_node(Assign, NULL);
                                                                                add_child((yyval.node), new_node(Identifier, (yyvsp[-2].token)));
                                                                                add_child((yyval.node), (yyvsp[0].node));
                                                                            }
#line 1639 "y.tab.c"
    break;

  case 28: /* Statement: LBRACE StatementAux RBRACE  */
#line 179 "src/gocompiler.y"
                                                                            {
                                                                                if((yyvsp[-1].node) == NULL){
                                                                                    (yyval.node) = NULL;
                                                                                } else {
                                                                                    if(count_brothers((yyvsp[-1].node)) > 1){
                                                                                        (yyval.node) = new_node(Block, NULL);
                                                                                        add_child((yyval.node), (yyvsp[-1].node)); 
                                                                                    } else { 
                                                                                        (yyval.node) = (yyvsp[-1].node); 
                                                                                    }
                                                                                }
                                                                            }
#line 1656 "y.tab.c"
    break;

  case 29: /* Statement: IF Expr LBRACE StatementAux RBRACE ELSE LBRACE StatementAux RBRACE  */
#line 191 "src/gocompiler.y"
                                                                            {
                                                                                (yyval.node) = new_node(If, NULL);

                                                                                // Create the If block
                                                                                aux_node = new_node(Block, NULL);
                                                                                add_child(aux_node, (yyvsp[-5].node));

                                                                                // Create the Else block
                                                                                aux_node2 = new_node(Block, NULL);
                                                                                add_child(aux_node2, (yyvsp[-1].node));

                                                                                add_child((yyval.node), (yyvsp[-7].node));
                                                                                add_child((yyval.node), aux_node);
                                                                                add_child((yyval.node), aux_node2);
                                                                            }
#line 1676 "y.tab.c"
    break;

  case 30: /* Statement: IF Expr LBRACE StatementAux RBRACE  */
#line 206 "src/gocompiler.y"
                                                                            { 
                                                                                (yyval.node) = new_node(If, NULL);

                                                                                // Create the If block
                                                                                aux_node = new_node(Block, NULL);
                                                                                add_child(aux_node, (yyvsp[-1].node));

                                                                                add_child((yyval.node), (yyvsp[-3].node));
                                                                                add_child((yyval.node), aux_node);
                                                                                add_child((yyval.node), new_node(Block, NULL));
                                                                            }
#line 1692 "y.tab.c"
    break;

  case 31: /* Statement: FOR Expr LBRACE StatementAux RBRACE  */
#line 217 "src/gocompiler.y"
                                                                            { 
                                                                                (yyval.node) = new_node(For, NULL);

                                                                                // Create the For block
                                                                                aux_node = new_node(Block, NULL);
                                                                                add_child(aux_node, (yyvsp[-1].node));

                                                                                add_child((yyval.node), (yyvsp[-3].node));
                                                                                add_child((yyval.node), aux_node); 
                                                                            }
#line 1707 "y.tab.c"
    break;

  case 32: /* Statement: FOR LBRACE StatementAux RBRACE  */
#line 227 "src/gocompiler.y"
                                                                            { 
                                                                                (yyval.node) = new_node(For, NULL);

                                                                                // Create the For block
                                                                                aux_node = new_node(Block, NULL);
                                                                                add_child(aux_node, (yyvsp[-1].node));

                                                                                add_child((yyval.node), aux_node); 
                                                                            }
#line 1721 "y.tab.c"
    break;

  case 33: /* Statement: RETURN Expr  */
#line 236 "src/gocompiler.y"
                                                                            { (yyval.node) = new_node(Return, NULL); add_child((yyval.node), (yyvsp[0].node)); }
#line 1727 "y.tab.c"
    break;

  case 34: /* Statement: RETURN  */
#line 237 "src/gocompiler.y"
                                                                            { (yyval.node) = new_node(Return, NULL); }
#line 1733 "y.tab.c"
    break;

  case 35: /* Statement: FuncInvocation  */
#line 238 "src/gocompiler.y"
                                                                            { (yyval.node) = (yyvsp[0].node); }
#line 1739 "y.tab.c"
    break;

  case 36: /* Statement: ParseArgs  */
#line 239 "src/gocompiler.y"
                                                                            { (yyval.node) = (yyvsp[0].node); }
#line 1745 "y.tab.c"
    break;

  case 37: /* Statement: PRINT LPAR Expr RPAR  */
#line 240 "src/gocompiler.y"
                                                                            { (yyval.node) = new_node(Print, NULL); add_child((yyval.node), (yyvsp[-1].node)); }
#line 1751 "y.tab.c"
    break;

  case 38: /* Statement: PRINT LPAR STRLIT RPAR  */
#line 241 "src/gocompiler.y"
                                                                            { (yyval.node) = new_node(Print, NULL); add_child((yyval.node), new_node(StrLit, (yyvsp[-1].token))); }
#line 1757 "y.tab.c"
    break;

  case 39: /* Statement: error  */
#line 242 "src/gocompiler.y"
                                                                            { errors_count++; (yyval.node) = new_node(Error, NULL); }
#line 1763 "y.tab.c"
    break;

  case 40: /* StatementAux: Statement SEMICOLON StatementAux  */
#line 246 "src/gocompiler.y"
                                         { if((yyval.node) == NULL){ (yyval.node) = (yyvsp[0].node); } else { (yyval.node) = (yyvsp[-2].node); add_brother((yyvsp[-2].node), (yyvsp[0].node)); } }
#line 1769 "y.tab.c"
    break;

  case 41: /* StatementAux: %empty  */
#line 247 "src/gocompiler.y"
                                         { (yyval.node) = NULL; }
#line 1775 "y.tab.c"
    break;

  case 42: /* ParseArgs: IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR  */
#line 250 "src/gocompiler.y"
                                                                                {   
                                                                                    (yyval.node) = new_node(ParseArgs, NULL);

                                                                                    aux_node = new_node(Identifier, (yyvsp[-10].token));
                                                                                    add_brother(aux_node, (yyvsp[-2].node)); 

                                                                                    add_child((yyval.node), aux_node);
                                                                                }
#line 1788 "y.tab.c"
    break;

  case 43: /* ParseArgs: IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR  */
#line 258 "src/gocompiler.y"
                                                                                { 
                                                                                    (yyval.node) = new_node(ParseArgs, NULL);

                                                                                    aux_node = new_node(Identifier, (yyvsp[-7].token));
                                                                                    add_brother(aux_node, new_node(Error, NULL));
                                                                                    errors_count++;
                                                                                }
#line 1800 "y.tab.c"
    break;

  case 44: /* FuncInvocation: IDENTIFIER LPAR Expr FuncInvocationAux RPAR  */
#line 268 "src/gocompiler.y"
                                                    {
                                                        (yyval.node) = new_node(Call, NULL);

                                                        aux_node = new_node(Identifier, (yyvsp[-4].token));
                                                        add_brother(aux_node, (yyvsp[-2].node));
                                                        add_brother((yyvsp[-2].node), (yyvsp[-1].node));

                                                        add_child((yyval.node), aux_node);
                                                    }
#line 1814 "y.tab.c"
    break;

  case 45: /* FuncInvocation: IDENTIFIER LPAR RPAR  */
#line 277 "src/gocompiler.y"
                                                    { 
                                                        (yyval.node) = new_node(Call, NULL); 
                                                        add_child((yyval.node), new_node(Identifier, (yyvsp[-2].token)));
                                                    }
#line 1823 "y.tab.c"
    break;

  case 46: /* FuncInvocation: IDENTIFIER LPAR error RPAR  */
#line 281 "src/gocompiler.y"
                                                    { 
                                                        (yyval.node) = new_node(Call, NULL); 

                                                        aux_node = new_node(Identifier, (yyvsp[-3].token));
                                                        add_brother(aux_node, new_node(Error, NULL));

                                                        add_child((yyval.node), aux_node);
                                                        errors_count++;
                                                    }
#line 1837 "y.tab.c"
    break;

  case 47: /* FuncInvocationAux: COMMA Expr FuncInvocationAux  */
#line 293 "src/gocompiler.y"
                                     { (yyval.node) = (yyvsp[-1].node); add_brother((yyval.node), (yyvsp[0].node)); }
#line 1843 "y.tab.c"
    break;

  case 48: /* FuncInvocationAux: %empty  */
#line 294 "src/gocompiler.y"
                                     { (yyval.node) = NULL; }
#line 1849 "y.tab.c"
    break;

  case 49: /* Expr: Expr OR Expr  */
#line 297 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Or, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1855 "y.tab.c"
    break;

  case 50: /* Expr: Expr AND Expr  */
#line 298 "src/gocompiler.y"
                                    { (yyval.node) = new_node(And, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1861 "y.tab.c"
    break;

  case 51: /* Expr: Expr LT Expr  */
#line 299 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Lt, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1867 "y.tab.c"
    break;

  case 52: /* Expr: Expr GT Expr  */
#line 300 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Gt, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1873 "y.tab.c"
    break;

  case 53: /* Expr: Expr EQ Expr  */
#line 301 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Eq, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1879 "y.tab.c"
    break;

  case 54: /* Expr: Expr NE Expr  */
#line 302 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Ne, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1885 "y.tab.c"
    break;

  case 55: /* Expr: Expr LE Expr  */
#line 303 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Le, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1891 "y.tab.c"
    break;

  case 56: /* Expr: Expr GE Expr  */
#line 304 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Ge, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1897 "y.tab.c"
    break;

  case 57: /* Expr: Expr PLUS Expr  */
#line 305 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Add, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1903 "y.tab.c"
    break;

  case 58: /* Expr: Expr MINUS Expr  */
#line 306 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Sub, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1909 "y.tab.c"
    break;

  case 59: /* Expr: Expr STAR Expr  */
#line 307 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Mul, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1915 "y.tab.c"
    break;

  case 60: /* Expr: Expr DIV Expr  */
#line 308 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Div, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1921 "y.tab.c"
    break;

  case 61: /* Expr: Expr MOD Expr  */
#line 309 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Mod, NULL); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1927 "y.tab.c"
    break;

  case 62: /* Expr: NOT Expr  */
#line 310 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Not, NULL); add_child((yyval.node), (yyvsp[0].node)); }
#line 1933 "y.tab.c"
    break;

  case 63: /* Expr: MINUS Expr  */
#line 311 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Minus, NULL); add_child((yyval.node), (yyvsp[0].node)); }
#line 1939 "y.tab.c"
    break;

  case 64: /* Expr: PLUS Expr  */
#line 312 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Plus, NULL); add_child((yyval.node), (yyvsp[0].node)); }
#line 1945 "y.tab.c"
    break;

  case 65: /* Expr: NATURAL  */
#line 313 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Natural, (yyvsp[0].token)); }
#line 1951 "y.tab.c"
    break;

  case 66: /* Expr: DECIMAL  */
#line 314 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Decimal, (yyvsp[0].token)); }
#line 1957 "y.tab.c"
    break;

  case 67: /* Expr: IDENTIFIER  */
#line 315 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Identifier, (yyvsp[0].token)); }
#line 1963 "y.tab.c"
    break;

  case 68: /* Expr: FuncInvocation  */
#line 316 "src/gocompiler.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1969 "y.tab.c"
    break;

  case 69: /* Expr: LPAR Expr RPAR  */
#line 317 "src/gocompiler.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1975 "y.tab.c"
    break;

  case 70: /* Expr: LPAR error RPAR  */
#line 318 "src/gocompiler.y"
                                    { (yyval.node) = new_node(Error, NULL); errors_count++; }
#line 1981 "y.tab.c"
    break;


#line 1985 "y.tab.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 320 "src/gocompiler.y"
