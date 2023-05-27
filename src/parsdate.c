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
#line 1 "./parsdate.y"


#include <LYLeaks.h>

/*
 *  $LynxId: parsdate.y,v 1.31 2021/06/08 23:01:28 tom Exp $
 *
 *  This module is adapted and extended from tin, to use for LYmktime().
 *
 *  Project   : tin - a Usenet reader
 *  Module    : parsedate.y
 *  Author    : S. Bellovin, R. $alz, J. Berets, P. Eggert
 *  Created   : 1990-08-01
 *  Updated   : 2019-08-28 (by Thomas Dickey, for Lynx)
 *  Notes     : This grammar has 8 shift/reduce conflicts.
 *
 *              Originally written by Steven M. Bellovin <smb@research.att.com>
 *              while at the University of North Carolina at Chapel Hill.
 *              Later tweaked by a couple of people on Usenet.  Completely
 *              overhauled by Rich $alz <rsalz@osf.org> and Jim Berets
 *              <jberets@bbn.com> in August, 1990.
 *
 *              Further revised (removed obsolete constructs and cleaned up
 *              timezone names) in August, 1991, by Rich.
 *              Paul Eggert <eggert@twinsun.com> helped in September 1992.
 *              Roland Rosenfeld added MET DST code in April 1994.
 *
 *  Revision  : 1.13
 *  Copyright : This code is in the public domain and has no copyright.
 */

/* SUPPRESS 530 */ /* Empty body for statement */
/* SUPPRESS 593 on yyerrlab */ /* Label was not used */
/* SUPPRESS 593 on yynewstate */ /* Label was not used */
/* SUPPRESS 595 on yypvt */ /* Automatic variable may be used before set */

#undef alloca			/* conflicting def may be set by yacc */
#include <parsdate.h>

/*
**  Get the number of elements in a fixed-size array, or a pointer just
**  past the end of it.
*/
#define ENDOF(array)	(&array[ARRAY_SIZE(array)])

#ifdef EBCDIC
#define TO_ASCII(c)	TOASCII(c)
#define TO_LOCAL(c)	FROMASCII(c)
#else
#define TO_ASCII(c)	(c)
#define TO_LOCAL(c)	(c)
#endif

#define IS7BIT(x)		((unsigned) TO_ASCII(x) < 128)
#define CTYPE(isXXXXX, c)	(IS7BIT(c) && isXXXXX(((unsigned char)c)))

typedef char *PD_STRING;

extern int date_parse(void);

#define yyparse		date_parse
#define yylex		date_lex
#define yyerror		date_error

#define BAD_TIME	((time_t)-1)
#define isBadTime(n)	((n) != 0 && (((n) == BAD_TIME) || !((n) > 0)))

    /* See the LeapYears table in Convert. */
#define EPOCH		1970
#define END_OF_TIME	2200

    /* Constants for general time calculations. */
#define DST_OFFSET	1
#define SECSPERDAY	(24L * 60L * 60L)
    /* Readability for TABLE stuff. */
#define HOUR(x)		(x * 60)

#define LPAREN		'('
#define RPAREN		')'

/*
**  Daylight-savings mode:  on, off, or not yet known.
*/
typedef enum _DSTMODE {
    DSTon, DSToff, DSTmaybe
} DSTMODE;

/*
**  Meridian:  am, pm, or 24-hour style.
*/
typedef enum _MERIDIAN {
    MERam, MERpm, MER24
} MERIDIAN;

/*
**  Global variables.  We could get rid of most of them by using a yacc
**  union, but this is more efficient.  (This routine predates the
**  yacc %union construct.)
*/
static char *yyInput;
static DSTMODE yyDSTmode;
static int yyHaveDate;
static int yyHaveRel;
static int yyHaveTime;
static time_t yyTimezone;
static time_t yyDay;
static time_t yyHour;
static time_t yyMinutes;
static time_t yyMonth;
static time_t yySeconds;
static time_t yyYear;
static MERIDIAN yyMeridian;
static time_t yyRelMonth;
static time_t yyRelSeconds;

static time_t ToSeconds(time_t, time_t, time_t, MERIDIAN);
static time_t Convert(time_t, time_t, time_t, time_t, time_t, time_t,
		      MERIDIAN, DSTMODE);
static time_t DSTcorrect(time_t, time_t);
static time_t RelativeMonth(time_t, time_t);
static int LookupWord(char *, int);
static int date_lex(void);
static int GetTimeInfo(TIMEINFO * Now);

/*
 * The 'date_error()' function is declared here to work around a defect in
 * bison 1.22, which redefines 'const' further down in this file, making it
 * impossible to put a prototype here, and the function later.  We're using
 * 'const' on the parameter to quiet gcc's -Wwrite-strings warning.
 */
/*ARGSUSED*/
static void date_error(const char GCC_UNUSED *s)
{
    /*NOTREACHED */
}


#line 209 "y.tab.c"

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
#ifndef YYDEBUG
# define YYDEBUG 0
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
    tDAY = 258,                    /* tDAY  */
    tDAYZONE = 259,                /* tDAYZONE  */
    tMERIDIAN = 260,               /* tMERIDIAN  */
    tMONTH = 261,                  /* tMONTH  */
    tMONTH_UNIT = 262,             /* tMONTH_UNIT  */
    tSEC_UNIT = 263,               /* tSEC_UNIT  */
    tSNUMBER = 264,                /* tSNUMBER  */
    tUNUMBER = 265,                /* tUNUMBER  */
    tZONE = 266,                   /* tZONE  */
    tDST = 267                     /* tDST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define tDAY 258
#define tDAYZONE 259
#define tMERIDIAN 260
#define tMONTH 261
#define tMONTH_UNIT 262
#define tSEC_UNIT 263
#define tSNUMBER 264
#define tUNUMBER 265
#define tZONE 266
#define tDST 267

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 139 "./parsdate.y"

    time_t		Number;
    enum _MERIDIAN	Meridian;

#line 288 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tDAY = 3,                       /* tDAY  */
  YYSYMBOL_tDAYZONE = 4,                   /* tDAYZONE  */
  YYSYMBOL_tMERIDIAN = 5,                  /* tMERIDIAN  */
  YYSYMBOL_tMONTH = 6,                     /* tMONTH  */
  YYSYMBOL_tMONTH_UNIT = 7,                /* tMONTH_UNIT  */
  YYSYMBOL_tSEC_UNIT = 8,                  /* tSEC_UNIT  */
  YYSYMBOL_tSNUMBER = 9,                   /* tSNUMBER  */
  YYSYMBOL_tUNUMBER = 10,                  /* tUNUMBER  */
  YYSYMBOL_tZONE = 11,                     /* tZONE  */
  YYSYMBOL_tDST = 12,                      /* tDST  */
  YYSYMBOL_13_ = 13,                       /* ':'  */
  YYSYMBOL_14_ = 14,                       /* '/'  */
  YYSYMBOL_15_ = 15,                       /* ','  */
  YYSYMBOL_16_ = 16,                       /* '-'  */
  YYSYMBOL_YYACCEPT = 17,                  /* $accept  */
  YYSYMBOL_spec = 18,                      /* spec  */
  YYSYMBOL_item = 19,                      /* item  */
  YYSYMBOL_time = 20,                      /* time  */
  YYSYMBOL_zone = 21,                      /* zone  */
  YYSYMBOL_numzone = 22,                   /* numzone  */
  YYSYMBOL_date = 23,                      /* date  */
  YYSYMBOL_both = 24,                      /* both  */
  YYSYMBOL_rel = 25,                       /* rel  */
  YYSYMBOL_o_merid = 26                    /* o_merid  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   56

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  17
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  10
/* YYNRULES -- Number of rules.  */
#define YYNRULES  36
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  60

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   267


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
       2,     2,     2,     2,    15,    16,     2,    14,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    13,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   153,   153,   154,   157,   166,   170,   173,   177,   182,
     187,   199,   205,   212,   218,   228,   232,   236,   240,   248,
     254,   275,   279,   291,   295,   300,   304,   309,   314,   319,
     328,   338,   341,   344,   347,   352,   355
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
  "\"end of file\"", "error", "\"invalid token\"", "tDAY", "tDAYZONE",
  "tMERIDIAN", "tMONTH", "tMONTH_UNIT", "tSEC_UNIT", "tSNUMBER",
  "tUNUMBER", "tZONE", "tDST", "':'", "'/'", "','", "'-'", "$accept",
  "spec", "item", "time", "zone", "numzone", "date", "both", "rel",
  "o_merid", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-36)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -36,     2,   -36,     0,    -6,    22,    12,   -36,    24,   -36,
      24,   -36,    26,    27,    -8,   -36,   -36,   -36,    28,   -36,
     -36,    13,    29,    30,   -36,    20,   -36,    25,   -36,   -36,
     -36,    31,    -3,    32,   -36,   -36,    18,    33,   -36,   -36,
      35,    34,    37,   -36,    36,   -36,   -36,    39,    40,   -36,
      42,     5,   -36,    41,   -36,   -36,   -36,    43,    45,   -36
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,    35,     3,     4,     6,
       7,     9,     0,     0,    23,    33,    31,    36,    25,    34,
      32,     0,     0,     0,    10,    16,    20,    15,     5,    19,
       8,     0,     0,     0,    26,    29,    35,    21,    17,    18,
       0,     0,     0,    24,     0,    12,    11,     0,     0,    27,
       0,    35,    22,     0,    28,    14,    13,     0,     0,    30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -36,   -36,   -36,   -36,    46,   -27,   -36,   -36,   -36,   -35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     7,     8,    28,    29,     9,    10,    11,    24
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      39,    46,     2,    41,    14,     3,    12,    33,     4,    45,
      17,     5,     6,    42,    26,    13,    56,    17,    18,    19,
      20,    21,    35,    17,    55,    22,    23,    26,    25,    15,
      16,    44,    38,    26,    26,    27,    31,    32,    34,    36,
      37,    40,    43,    50,    49,     0,    51,    47,    48,    52,
      53,    54,     0,    58,    57,    59,    30
};

static const yytype_int8 yycheck[] =
{
      27,    36,     0,     6,    10,     3,     6,    15,     6,    36,
       5,     9,    10,    16,     9,    15,    51,     5,     6,     7,
       8,     9,     9,     5,    51,    13,    14,     9,     4,     7,
       8,    13,    12,     9,     9,    11,    10,    10,    10,    10,
      10,    10,    10,     6,    10,    -1,    10,    14,    13,    10,
      10,     9,    -1,    10,    13,    10,    10
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    18,     0,     3,     6,     9,    10,    19,    20,    23,
      24,    25,     6,    15,    10,     7,     8,     5,     6,     7,
       8,     9,    13,    14,    26,     4,     9,    11,    21,    22,
      21,    10,    10,    15,    10,     9,    10,    10,    12,    22,
      10,     6,    16,    10,    13,    22,    26,    14,    13,    10,
       6,    10,    10,    10,     9,    22,    26,    13,    10,    10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    17,    18,    18,    19,    19,    19,    19,    19,    19,
      20,    20,    20,    20,    20,    21,    21,    21,    21,    21,
      22,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      24,    25,    25,    25,    25,    26,    26
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     2,     1,
       2,     4,     4,     6,     6,     1,     1,     2,     2,     1,
       1,     3,     5,     2,     4,     2,     3,     5,     6,     3,
       9,     2,     2,     2,     2,     0,     1
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
  case 4: /* item: time  */
#line 157 "./parsdate.y"
               {
	    yyHaveTime++;
#if	defined(lint)
	    /* I am compulsive about lint natterings... */
	    if (yyHaveTime == -1) {
		YYERROR;
	    }
#endif	/* defined(lint) */
	}
#line 1325 "y.tab.c"
    break;

  case 5: /* item: time zone  */
#line 166 "./parsdate.y"
                    {
	    yyHaveTime++;
	    yyTimezone = (yyvsp[0].Number);
	}
#line 1334 "y.tab.c"
    break;

  case 6: /* item: date  */
#line 170 "./parsdate.y"
               {
	    yyHaveDate++;
	}
#line 1342 "y.tab.c"
    break;

  case 7: /* item: both  */
#line 173 "./parsdate.y"
               {
	    yyHaveDate++;
	    yyHaveTime++;
	}
#line 1351 "y.tab.c"
    break;

  case 8: /* item: both zone  */
#line 177 "./parsdate.y"
                    {
	    yyHaveDate++;
	    yyHaveTime++;
	    yyTimezone = (yyvsp[0].Number);
	}
#line 1361 "y.tab.c"
    break;

  case 9: /* item: rel  */
#line 182 "./parsdate.y"
              {
	    yyHaveRel = 1;
	}
#line 1369 "y.tab.c"
    break;

  case 10: /* time: tUNUMBER o_merid  */
#line 187 "./parsdate.y"
                           {
	    if ((yyvsp[-1].Number) < 100) {
		yyHour = (yyvsp[-1].Number);
		yyMinutes = 0;
	    }
	    else {
		yyHour = (yyvsp[-1].Number) / 100;
		yyMinutes = (yyvsp[-1].Number) % 100;
	    }
	    yySeconds = 0;
	    yyMeridian = (yyvsp[0].Meridian);
	}
#line 1386 "y.tab.c"
    break;

  case 11: /* time: tUNUMBER ':' tUNUMBER o_merid  */
#line 199 "./parsdate.y"
                                        {
	    yyHour = (yyvsp[-3].Number);
	    yyMinutes = (yyvsp[-1].Number);
	    yySeconds = 0;
	    yyMeridian = (yyvsp[0].Meridian);
	}
#line 1397 "y.tab.c"
    break;

  case 12: /* time: tUNUMBER ':' tUNUMBER numzone  */
#line 205 "./parsdate.y"
                                        {
	    yyHour = (yyvsp[-3].Number);
	    yyMinutes = (yyvsp[-1].Number);
	    yyTimezone = (yyvsp[0].Number);
	    yyMeridian = MER24;
	    yyDSTmode = DSToff;
	}
#line 1409 "y.tab.c"
    break;

  case 13: /* time: tUNUMBER ':' tUNUMBER ':' tUNUMBER o_merid  */
#line 212 "./parsdate.y"
                                                     {
	    yyHour = (yyvsp[-5].Number);
	    yyMinutes = (yyvsp[-3].Number);
	    yySeconds = (yyvsp[-1].Number);
	    yyMeridian = (yyvsp[0].Meridian);
	}
#line 1420 "y.tab.c"
    break;

  case 14: /* time: tUNUMBER ':' tUNUMBER ':' tUNUMBER numzone  */
#line 218 "./parsdate.y"
                                                     {
	    yyHour = (yyvsp[-5].Number);
	    yyMinutes = (yyvsp[-3].Number);
	    yySeconds = (yyvsp[-1].Number);
	    yyTimezone = (yyvsp[0].Number);
	    yyMeridian = MER24;
	    yyDSTmode = DSToff;
	}
#line 1433 "y.tab.c"
    break;

  case 15: /* zone: tZONE  */
#line 228 "./parsdate.y"
                {
	    (yyval.Number) = (yyvsp[0].Number);
	    yyDSTmode = DSToff;
	}
#line 1442 "y.tab.c"
    break;

  case 16: /* zone: tDAYZONE  */
#line 232 "./parsdate.y"
                   {
	    (yyval.Number) = (yyvsp[0].Number);
	    yyDSTmode = DSTon;
	}
#line 1451 "y.tab.c"
    break;

  case 17: /* zone: tDAYZONE tDST  */
#line 236 "./parsdate.y"
                        {
	    yyTimezone = (yyvsp[-1].Number);
	    yyDSTmode = DSTon;
	}
#line 1460 "y.tab.c"
    break;

  case 18: /* zone: tZONE numzone  */
#line 240 "./parsdate.y"
                        {
	    /* Only allow "GMT+300" and "GMT-0800" */
	    if ((yyvsp[-1].Number) != 0) {
		YYABORT;
	    }
	    (yyval.Number) = (yyvsp[0].Number);
	    yyDSTmode = DSToff;
	}
#line 1473 "y.tab.c"
    break;

  case 19: /* zone: numzone  */
#line 248 "./parsdate.y"
                  {
	    (yyval.Number) = (yyvsp[0].Number);
	    yyDSTmode = DSToff;
	}
#line 1482 "y.tab.c"
    break;

  case 20: /* numzone: tSNUMBER  */
#line 254 "./parsdate.y"
                   {
	    int	i;

	    /* Unix and GMT and numeric timezones -- a little confusing. */
	    if ((int)(yyvsp[0].Number) < 0) {
		/* Don't work with negative modulus. */
		(yyvsp[0].Number) = -(int)(yyvsp[0].Number);
		if ((yyvsp[0].Number) > 9999 || (i = (int) ((yyvsp[0].Number) % 100)) >= 60) {
			YYABORT;
		}
		(yyval.Number) = ((yyvsp[0].Number) / 100) * 60 + i;
	    }
	    else {
		if ((yyvsp[0].Number) > 9999 || (i = (int) ((yyvsp[0].Number) % 100)) >= 60) {
			YYABORT;
		}
		(yyval.Number) = -(((yyvsp[0].Number) / 100) * 60 + i);
	    }
	}
#line 1506 "y.tab.c"
    break;

  case 21: /* date: tUNUMBER '/' tUNUMBER  */
#line 275 "./parsdate.y"
                                {
	    yyMonth = (yyvsp[-2].Number);
	    yyDay = (yyvsp[0].Number);
	}
#line 1515 "y.tab.c"
    break;

  case 22: /* date: tUNUMBER '/' tUNUMBER '/' tUNUMBER  */
#line 279 "./parsdate.y"
                                             {
	    if ((yyvsp[-4].Number) > 100) {
		yyYear = (yyvsp[-4].Number);
		yyMonth = (yyvsp[-2].Number);
		yyDay = (yyvsp[0].Number);
	    }
	    else {
		yyMonth = (yyvsp[-4].Number);
		yyDay = (yyvsp[-2].Number);
		yyYear = (yyvsp[0].Number);
	    }
	}
#line 1532 "y.tab.c"
    break;

  case 23: /* date: tMONTH tUNUMBER  */
#line 291 "./parsdate.y"
                          {
	    yyMonth = (yyvsp[-1].Number);
	    yyDay = (yyvsp[0].Number);
	}
#line 1541 "y.tab.c"
    break;

  case 24: /* date: tMONTH tUNUMBER ',' tUNUMBER  */
#line 295 "./parsdate.y"
                                       {
	    yyMonth = (yyvsp[-3].Number);
	    yyDay = (yyvsp[-2].Number);
	    yyYear = (yyvsp[0].Number);
	}
#line 1551 "y.tab.c"
    break;

  case 25: /* date: tUNUMBER tMONTH  */
#line 300 "./parsdate.y"
                          {
	    yyDay = (yyvsp[-1].Number);
	    yyMonth = (yyvsp[0].Number);
	}
#line 1560 "y.tab.c"
    break;

  case 26: /* date: tUNUMBER tMONTH tUNUMBER  */
#line 304 "./parsdate.y"
                                   {
	    yyDay = (yyvsp[-2].Number);
	    yyMonth = (yyvsp[-1].Number);
	    yyYear = (yyvsp[0].Number);
	}
#line 1570 "y.tab.c"
    break;

  case 27: /* date: tDAY ',' tUNUMBER tMONTH tUNUMBER  */
#line 309 "./parsdate.y"
                                            {
	    yyDay = (yyvsp[-2].Number);
	    yyMonth = (yyvsp[-1].Number);
	    yyYear = (yyvsp[0].Number);
	}
#line 1580 "y.tab.c"
    break;

  case 28: /* date: tDAY ',' tUNUMBER '-' tMONTH tSNUMBER  */
#line 314 "./parsdate.y"
                                                {
	    yyDay = (yyvsp[-3].Number);
	    yyMonth = (yyvsp[-1].Number);
	    yyYear = -(yyvsp[0].Number);
	}
#line 1590 "y.tab.c"
    break;

  case 29: /* date: tUNUMBER tSNUMBER tSNUMBER  */
#line 319 "./parsdate.y"
                                     {
	    yyDay = (yyvsp[-2].Number);
	    yyMonth = -(yyvsp[-1].Number);
	    yyYear = -(yyvsp[0].Number);
	    yyDSTmode = DSToff;	/* assume midnight if no time given */
	    yyTimezone = 0;	/* Lynx assumes GMT for this format */
	}
#line 1602 "y.tab.c"
    break;

  case 30: /* both: tDAY tMONTH tUNUMBER tUNUMBER ':' tUNUMBER ':' tUNUMBER tUNUMBER  */
#line 328 "./parsdate.y"
                                                                           {
	    yyMonth = (yyvsp[-7].Number);
	    yyDay = (yyvsp[-6].Number);
	    yyYear = (yyvsp[0].Number);
	    yyHour = (yyvsp[-5].Number);
	    yyMinutes = (yyvsp[-3].Number);
	    yySeconds = (yyvsp[-1].Number);
	}
#line 1615 "y.tab.c"
    break;

  case 31: /* rel: tSNUMBER tSEC_UNIT  */
#line 338 "./parsdate.y"
                             {
	    yyRelSeconds += (yyvsp[-1].Number) * (yyvsp[0].Number);
	}
#line 1623 "y.tab.c"
    break;

  case 32: /* rel: tUNUMBER tSEC_UNIT  */
#line 341 "./parsdate.y"
                             {
	    yyRelSeconds += (yyvsp[-1].Number) * (yyvsp[0].Number);
	}
#line 1631 "y.tab.c"
    break;

  case 33: /* rel: tSNUMBER tMONTH_UNIT  */
#line 344 "./parsdate.y"
                               {
	    yyRelMonth += (yyvsp[-1].Number) * (yyvsp[0].Number);
	}
#line 1639 "y.tab.c"
    break;

  case 34: /* rel: tUNUMBER tMONTH_UNIT  */
#line 347 "./parsdate.y"
                               {
	    yyRelMonth += (yyvsp[-1].Number) * (yyvsp[0].Number);
	}
#line 1647 "y.tab.c"
    break;

  case 35: /* o_merid: %empty  */
#line 352 "./parsdate.y"
                     {
	    (yyval.Meridian) = MER24;
	}
#line 1655 "y.tab.c"
    break;

  case 36: /* o_merid: tMERIDIAN  */
#line 355 "./parsdate.y"
                    {
	    (yyval.Meridian) = (yyvsp[0].Meridian);
	}
#line 1663 "y.tab.c"
    break;


#line 1667 "y.tab.c"

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

#line 360 "./parsdate.y"



/*
**  An entry in the lexical lookup table.
*/
/* *INDENT-OFF* */
typedef struct _TABLE {
    const char *name;
    int		type;
    time_t	value;
} TABLE;

/* Month and day table. */
static const TABLE MonthDayTable[] = {
    { "january",	tMONTH,  1 },
    { "february",	tMONTH,  2 },
    { "march",		tMONTH,  3 },
    { "april",		tMONTH,  4 },
    { "may",		tMONTH,  5 },
    { "june",		tMONTH,  6 },
    { "july",		tMONTH,  7 },
    { "august",		tMONTH,  8 },
    { "september",	tMONTH,  9 },
    { "october",	tMONTH, 10 },
    { "november",	tMONTH, 11 },
    { "december",	tMONTH, 12 },
	/* The value of the day isn't used... */
    { "sunday",		tDAY, 0 },
    { "monday",		tDAY, 0 },
    { "tuesday",	tDAY, 0 },
    { "wednesday",	tDAY, 0 },
    { "thursday",	tDAY, 0 },
    { "friday",		tDAY, 0 },
    { "saturday",	tDAY, 0 },
};

/* Time units table. */
static const TABLE	UnitsTable[] = {
    { "year",		tMONTH_UNIT,	12 },
    { "month",		tMONTH_UNIT,	1 },
    { "week",		tSEC_UNIT,	7 * 24 * 60 * 60 },
    { "day",		tSEC_UNIT,	1 * 24 * 60 * 60 },
    { "hour",		tSEC_UNIT,	60 * 60 },
    { "minute",		tSEC_UNIT,	60 },
    { "min",		tSEC_UNIT,	60 },
    { "second",		tSEC_UNIT,	1 },
    { "sec",		tSEC_UNIT,	1 },
};

/* Timezone table. */
static const TABLE	TimezoneTable[] = {
    { "gmt",	tZONE,     HOUR( 0) },	/* Greenwich Mean */
    { "ut",	tZONE,     HOUR( 0) },	/* Universal */
    { "utc",	tZONE,     HOUR( 0) },	/* Universal Coordinated */
    { "cut",	tZONE,     HOUR( 0) },	/* Coordinated Universal */
    { "z",	tZONE,     HOUR( 0) },	/* Greenwich Mean */
    { "wet",	tZONE,     HOUR( 0) },	/* Western European */
    { "bst",	tDAYZONE,  HOUR( 0) },	/* British Summer */
    { "nst",	tZONE,     HOUR(3)+30 }, /* Newfoundland Standard */
    { "ndt",	tDAYZONE,  HOUR(3)+30 }, /* Newfoundland Daylight */
    { "ast",	tZONE,     HOUR( 4) },	/* Atlantic Standard */
    { "adt",	tDAYZONE,  HOUR( 4) },	/* Atlantic Daylight */
    { "est",	tZONE,     HOUR( 5) },	/* Eastern Standard */
    { "edt",	tDAYZONE,  HOUR( 5) },	/* Eastern Daylight */
    { "cst",	tZONE,     HOUR( 6) },	/* Central Standard */
    { "cdt",	tDAYZONE,  HOUR( 6) },	/* Central Daylight */
    { "mst",	tZONE,     HOUR( 7) },	/* Mountain Standard */
    { "mdt",	tDAYZONE,  HOUR( 7) },	/* Mountain Daylight */
    { "pst",	tZONE,     HOUR( 8) },	/* Pacific Standard */
    { "pdt",	tDAYZONE,  HOUR( 8) },	/* Pacific Daylight */
    { "yst",	tZONE,     HOUR( 9) },	/* Yukon Standard */
    { "ydt",	tDAYZONE,  HOUR( 9) },	/* Yukon Daylight */
    { "akst",	tZONE,     HOUR( 9) },	/* Alaska Standard */
    { "akdt",	tDAYZONE,  HOUR( 9) },	/* Alaska Daylight */
    { "hst",	tZONE,     HOUR(10) },	/* Hawaii Standard */
    { "hast",	tZONE,     HOUR(10) },	/* Hawaii-Aleutian Standard */
    { "hadt",	tDAYZONE,  HOUR(10) },	/* Hawaii-Aleutian Daylight */
    { "ces",	tDAYZONE,  -HOUR(1) },	/* Central European Summer */
    { "cest",	tDAYZONE,  -HOUR(1) },	/* Central European Summer */
    { "mez",	tZONE,     -HOUR(1) },	/* Middle European */
    { "mezt",	tDAYZONE,  -HOUR(1) },	/* Middle European Summer */
    { "cet",	tZONE,     -HOUR(1) },	/* Central European */
    { "met",	tZONE,     -HOUR(1) },	/* Middle European */
/* Additional aliases for MET / MET DST *************************************/
    { "mez",    tZONE,     -HOUR(1) },  /* Middle European */
    { "mewt",   tZONE,     -HOUR(1) },  /* Middle European Winter */
    { "mest",   tDAYZONE,  -HOUR(1) },  /* Middle European Summer */
    { "mes",    tDAYZONE,  -HOUR(1) },  /* Middle European Summer */
    { "mesz",   tDAYZONE,  -HOUR(1) },  /* Middle European Summer */
    { "msz",    tDAYZONE,  -HOUR(1) },  /* Middle European Summer */
    { "metdst", tDAYZONE,  -HOUR(1) },  /* Middle European Summer */
/****************************************************************************/
    { "eet",	tZONE,     -HOUR(2) },	/* Eastern Europe */
    { "msk",	tZONE,     -HOUR(3) },	/* Moscow Winter */
    { "msd",	tDAYZONE,  -HOUR(3) },	/* Moscow Summer */
    { "wast",	tZONE,     -HOUR(8) },	/* West Australian Standard */
    { "wadt",	tDAYZONE,  -HOUR(8) },	/* West Australian Daylight */
    { "hkt",	tZONE,     -HOUR(8) },	/* Hong Kong */
    { "cct",	tZONE,     -HOUR(8) },	/* China Coast */
    { "jst",	tZONE,     -HOUR(9) },	/* Japan Standard */
    { "kst",	tZONE,     -HOUR(9) },	/* Korean Standard */
    { "kdt",	tZONE,     -HOUR(9) },	/* Korean Daylight */
    { "cast",	tZONE,     -(HOUR(9)+30) }, /* Central Australian Standard */
    { "cadt",	tDAYZONE,  -(HOUR(9)+30) }, /* Central Australian Daylight */
    { "east",	tZONE,     -HOUR(10) },	/* Eastern Australian Standard */
    { "eadt",	tDAYZONE,  -HOUR(10) },	/* Eastern Australian Daylight */
    { "nzst",	tZONE,     -HOUR(12) },	/* New Zealand Standard */
    { "nzdt",	tDAYZONE,  -HOUR(12) },	/* New Zealand Daylight */

    /* For completeness we include the following entries. */
#if	0

    /* Duplicate names.  Either they conflict with a zone listed above
     * (which is either more likely to be seen or just been in circulation
     * longer), or they conflict with another zone in this section and
     * we could not reasonably choose one over the other. */
    { "fst",	tZONE,     HOUR( 2) },	/* Fernando De Noronha Standard */
    { "fdt",	tDAYZONE,  HOUR( 2) },	/* Fernando De Noronha Daylight */
    { "bst",	tZONE,     HOUR( 3) },	/* Brazil Standard */
    { "est",	tZONE,     HOUR( 3) },	/* Eastern Standard (Brazil) */
    { "edt",	tDAYZONE,  HOUR( 3) },	/* Eastern Daylight (Brazil) */
    { "wst",	tZONE,     HOUR( 4) },	/* Western Standard (Brazil) */
    { "wdt",	tDAYZONE,  HOUR( 4) },	/* Western Daylight (Brazil) */
    { "cst",	tZONE,     HOUR( 5) },	/* Chile Standard */
    { "cdt",	tDAYZONE,  HOUR( 5) },	/* Chile Daylight */
    { "ast",	tZONE,     HOUR( 5) },	/* Acre Standard */
    { "adt",	tDAYZONE,  HOUR( 5) },	/* Acre Daylight */
    { "cst",	tZONE,     HOUR( 5) },	/* Cuba Standard */
    { "cdt",	tDAYZONE,  HOUR( 5) },	/* Cuba Daylight */
    { "est",	tZONE,     HOUR( 6) },	/* Easter Island Standard */
    { "edt",	tDAYZONE,  HOUR( 6) },	/* Easter Island Daylight */
    { "sst",	tZONE,     HOUR(11) },	/* Samoa Standard */
    { "ist",	tZONE,     -HOUR(2) },	/* Israel Standard */
    { "idt",	tDAYZONE,  -HOUR(2) },	/* Israel Daylight */
    { "idt",	tDAYZONE,  -(HOUR(3)+30) }, /* Iran Daylight */
    { "ist",	tZONE,     -(HOUR(3)+30) }, /* Iran Standard */
    { "cst",	 tZONE,     -HOUR(8) },	/* China Standard */
    { "cdt",	 tDAYZONE,  -HOUR(8) },	/* China Daylight */
    { "sst",	 tZONE,     -HOUR(8) },	/* Singapore Standard */

    /* Dubious (e.g., not in Olson's TIMEZONE package) or obsolete. */
    { "gst",	tZONE,     HOUR( 3) },	/* Greenland Standard */
    { "wat",	tZONE,     -HOUR(1) },	/* West Africa */
    { "at",	tZONE,     HOUR( 2) },	/* Azores */
    { "gst",	tZONE,     -HOUR(10) },	/* Guam Standard */
    { "nft",	tZONE,     HOUR(3)+30 }, /* Newfoundland */
    { "idlw",	tZONE,     HOUR(12) },	/* International Date Line West */
    { "mewt",	tZONE,     -HOUR(1) },	/* Middle European Winter */
    { "mest",	tDAYZONE,  -HOUR(1) },	/* Middle European Summer */
    { "swt",	tZONE,     -HOUR(1) },	/* Swedish Winter */
    { "sst",	tDAYZONE,  -HOUR(1) },	/* Swedish Summer */
    { "fwt",	tZONE,     -HOUR(1) },	/* French Winter */
    { "fst",	tDAYZONE,  -HOUR(1) },	/* French Summer */
    { "bt",	tZONE,     -HOUR(3) },	/* Baghdad */
    { "it",	tZONE,     -(HOUR(3)+30) }, /* Iran */
    { "zp4",	tZONE,     -HOUR(4) },	/* USSR Zone 3 */
    { "zp5",	tZONE,     -HOUR(5) },	/* USSR Zone 4 */
    { "ist",	tZONE,     -(HOUR(5)+30) }, /* Indian Standard */
    { "zp6",	tZONE,     -HOUR(6) },	/* USSR Zone 5 */
    { "nst",	tZONE,     -HOUR(7) },	/* North Sumatra */
    { "sst",	tZONE,     -HOUR(7) },	/* South Sumatra */
    { "jt",	tZONE,     -(HOUR(7)+30) }, /* Java (3pm in Cronusland!) */
    { "nzt",	tZONE,     -HOUR(12) },	/* New Zealand */
    { "idle",	tZONE,     -HOUR(12) },	/* International Date Line East */
    { "cat",	tZONE,     HOUR(10) },	/* -- expired 1967 */
    { "nt",	tZONE,     HOUR(11) },	/* -- expired 1967 */
    { "ahst",	tZONE,     HOUR(10) },	/* -- expired 1983 */
    { "hdt",	tDAYZONE,  HOUR(10) },	/* -- expired 1986 */
#endif	/* 0 */
};
/* *INDENT-ON* */

static time_t ToSeconds(time_t Hours, time_t Minutes, time_t Seconds, MERIDIAN Meridian)
{
    if (isBadTime(Minutes) || Minutes > 59 || isBadTime(Seconds) || Seconds > 61)
	return BAD_TIME;
    if (Meridian == MER24) {
	if (isBadTime(Hours) || Hours > 23)
	    return BAD_TIME;
    } else {
	if (Hours < 1 || Hours > 12)
	    return BAD_TIME;
	if (Hours == 12)
	    Hours = 0;
	if (Meridian == MERpm)
	    Hours += 12;
    }
    return (Hours * 60L + Minutes) * 60L + Seconds;
}

static time_t Convert(time_t Month, time_t Day, time_t Year, time_t Hours,
		      time_t Minutes, time_t Seconds, MERIDIAN Meridian,
		      DSTMODE dst)
{
    static const int DaysNormal[13] =
    {
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    static const int DaysLeap[13] =
    {
	0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    /* *INDENT-OFF* */
    static const int LeapYears[] =
    {
	1972, 1976, 1980, 1984, 1988, 1992, 1996,
	2000, 2004, 2008, 2012, 2016, 2020, 2024, 2028, 2032, 2036,
	2040, 2044, 2048, 2052, 2056, 2060, 2064, 2068, 2072, 2076,
	2080, 2084, 2088, 2092, 2096, /***/ 2104, 2108, 2112, 2116,
	2120, 2124, 2128, 2132, 2136, 2140, 2144, 2148, 2152, 2156,
	2160, 2164, 2168, 2172, 2176, 2180, 2184, 2188, 2192, 2196,
    };
    /* *INDENT-ON* */

    const int *yp;
    const int *mp;
    int i;
    time_t Julian;
    time_t tod;

    if (isBadTime(Year))
	Year = -Year;
    if (Year < 70)
	Year += 2000;
    if (Year < 100)
	Year += 1900;
    if (Year < EPOCH)
	Year += 100;
    for (mp = DaysNormal, yp = LeapYears; yp < ENDOF(LeapYears); yp++)
	if (Year == *yp) {
	    mp = DaysLeap;
	    break;
	}
    if (Year < EPOCH || Year > END_OF_TIME
	|| Month < 1 || Month > 12
    /* NOSTRICT */
    /* conversion from long may lose accuracy */
	|| Day < 1 || Day > mp[(int) Month]) {
	return BAD_TIME;
    }

    Julian = Day - 1 + (Year - EPOCH) * 365;
    for (yp = LeapYears; yp < ENDOF(LeapYears); yp++, Julian++) {
	if (Year <= *yp)
	    break;
    }
    for (i = 1; i < Month; i++)
	Julian += *++mp;
    Julian *= SECSPERDAY;
    Julian += yyTimezone * 60L;
    tod = ToSeconds(Hours, Minutes, Seconds, Meridian);
    if (isBadTime(tod)) {
	return BAD_TIME;
    }
    Julian += tod;
    tod = Julian;
    if (dst == DSTon) {
	Julian -= DST_OFFSET * 60 * 60;
    } else if (dst == DSTmaybe) {
	struct tm *tm = localtime(&tod);

	if (tm != NULL) {
	    if (tm->tm_isdst)
		Julian -= DST_OFFSET * 60 * 60;
	} else {
	    Julian = BAD_TIME;
	}
    }
    return Julian;
}

static time_t DSTcorrect(time_t Start, time_t Future)
{
    struct tm *tm;
    time_t StartDay;
    time_t FutureDay;

    if ((tm = localtime(&Start)) == NULL)
	return BAD_TIME;
    StartDay = (tm->tm_hour + 1) % 24;

    if ((tm = localtime(&Future)) == NULL)
	return BAD_TIME;
    FutureDay = (tm->tm_hour + 1) % 24;

    return (Future - Start) + (StartDay - FutureDay) * DST_OFFSET * 60 * 60;
}

static time_t RelativeMonth(time_t Start, time_t RelMonth)
{
    struct tm *tm;
    time_t Month;
    time_t Year;

    if ((tm = localtime(&Start)) == NULL)
	return BAD_TIME;

    Month = 12 * tm->tm_year + tm->tm_mon + RelMonth;
    Year = Month / 12 + 1900;
    Month = Month % 12 + 1;
    return DSTcorrect(Start,
		      Convert(Month, (time_t) tm->tm_mday, Year,
			      (time_t) tm->tm_hour, (time_t) tm->tm_min,
			      (time_t) tm->tm_sec,
			      MER24, DSTmaybe));
}

static int LookupWord(char *buff,
		      int length)
{
    char *p;
    const char *q;
    const TABLE *tp;
    int c;

    p = buff;
    c = p[0];

    /* See if we have an abbreviation for a month. */
    if (length == 3 || (length == 4 && p[3] == '.')) {
	for (tp = MonthDayTable; tp < ENDOF(MonthDayTable); tp++) {
	    q = tp->name;
	    if (c == q[0] && p[1] == q[1] && p[2] == q[2]) {
		yylval.Number = tp->value;
		return tp->type;
	    }
	}
    } else {
	for (tp = MonthDayTable; tp < ENDOF(MonthDayTable); tp++) {
	    if (c == tp->name[0] && strcmp(p, tp->name) == 0) {
		yylval.Number = tp->value;
		return tp->type;
	    }
	}
    }

    /* Try for a timezone. */
    for (tp = TimezoneTable; tp < ENDOF(TimezoneTable); tp++) {
	if (c == tp->name[0] && p[1] == tp->name[1]
	    && strcmp(p, tp->name) == 0) {
	    yylval.Number = tp->value;
	    return tp->type;
	}
    }

    if (strcmp(buff, "dst") == 0)
	return tDST;

    /* Try the units table. */
    for (tp = UnitsTable; tp < ENDOF(UnitsTable); tp++) {
	if (c == tp->name[0] && strcmp(p, tp->name) == 0) {
	    yylval.Number = tp->value;
	    return tp->type;
	}
    }

    /* Strip off any plural and try the units table again. */
    if (--length > 0 && p[length] == 's') {
	p[length] = '\0';
	for (tp = UnitsTable; tp < ENDOF(UnitsTable); tp++) {
	    if (c == tp->name[0] && strcmp(p, tp->name) == 0) {
		p[length] = 's';
		yylval.Number = tp->value;
		return tp->type;
	    }
	}
	p[length] = 's';
    }
    length++;

    /* Drop out any periods. */
    for (p = buff, q = (PD_STRING) buff; *q; q++) {
	if (*q != '.')
	    *p++ = *q;
    }
    *p = '\0';

    /* Try the meridians. */
    if (buff[1] == 'm' && buff[2] == '\0') {
	if (buff[0] == 'a') {
	    yylval.Meridian = MERam;
	    return tMERIDIAN;
	}
	if (buff[0] == 'p') {
	    yylval.Meridian = MERpm;
	    return tMERIDIAN;
	}
    }

    /* If we saw any periods, try the timezones again. */
    if (p - buff != length) {
	c = buff[0];
	for (p = buff, tp = TimezoneTable; tp < ENDOF(TimezoneTable); tp++) {
	    if (c == tp->name[0] && p[1] == tp->name[1]
		&& strcmp(p, tp->name) == 0) {
		yylval.Number = tp->value;
		return tp->type;
	    }
	}
    }

    /* Unknown word -- assume GMT timezone. */
    yylval.Number = 0;
    return tZONE;
}

/*
 * This returns characters as-is (the ones that are not part of some token),
 * and codes greater than 256 (the token values).
 *
 * yacc generates tables that may use the character value.  In particular,
 * byacc's yycheck[] table contains integer values for the expected codes from
 * this function, which (unless byacc is run locally) are ASCII codes.
 *
 * The TO_LOCAL() function assumes its input is in ASCII, and the output is
 * whatever native encoding is used on the machine, e.g., EBCDIC.
 *
 * The TO_ASCII() function is the inverse of TO_LOCAL().
 */
static int date_lex(void)
{
    int c;
    char *p;
    char buff[20];
    int sign;
    int i;
    int nesting;

    /* Get first character after the whitespace. */
    for (;;) {
	while (CTYPE(isspace, *yyInput))
	    yyInput++;
	c = *yyInput;

	/* Ignore RFC 822 comments, typically time zone names. */
	if (c != LPAREN)
	    break;
	for (nesting = 1;
	     (c = *++yyInput) != RPAREN || --nesting;
	    ) {
	    if (c == LPAREN) {
		nesting++;
	    } else if (!IS7BIT(c) || c == '\0' || c == '\r'
		       || (c == '\\'
			   && ((c = *++yyInput) == '\0'
			       || !IS7BIT(c)))) {
		/* Lexical error: bad comment. */
		return '?';
	    }
	}
	yyInput++;
    }

    /* A number? */
    if (CTYPE(isdigit, c) || c == '-' || c == '+') {
	if (c == '-' || c == '+') {
	    sign = c == '-' ? -1 : 1;
	    yyInput++;
	    if (!CTYPE(isdigit, *yyInput)) {
		/* Return the isolated plus or minus sign. */
		--yyInput;
		return *yyInput++;
	    }
	} else {
	    sign = 0;
	}
	for (p = buff;
	     (c = *yyInput++) != '\0' && CTYPE(isdigit, c);
	    ) {
	    if (p < &buff[sizeof buff - 1])
		*p++ = (char) c;
	}
	*p = '\0';
	i = atoi(buff);

	yyInput--;
	yylval.Number = sign < 0 ? -i : i;
	return sign ? tSNUMBER : tUNUMBER;
    }

    /* A word? */
    if (CTYPE(isalpha, c)) {
	for (p = buff;
	     (c = *yyInput++) == '.' || CTYPE(isalpha, c);
	    ) {
	    if (p < &buff[sizeof buff - 1])
		*p++ = (char) (CTYPE(isupper, c) ? tolower(c) : c);
	}
	*p = '\0';
	yyInput--;
	return LookupWord(buff, (int) (p - buff));
    }

    return *yyInput++;
}

static int GetTimeInfo(TIMEINFO * Now)
{
    static time_t LastTime;
    static long LastTzone;
    struct tm *tm;

#if	defined(HAVE_GETTIMEOFDAY)
    struct timeval tv;
#endif /* defined(HAVE_GETTIMEOFDAY) */
#if	defined(DONT_HAVE_TM_GMTOFF)
    struct tm local;
    struct tm gmt;
#endif /* !defined(DONT_HAVE_TM_GMTOFF) */

    /* Get the basic time. */
    memset(Now, 0, sizeof(TIMEINFO));
#if defined(HAVE_GETTIMEOFDAY)
    if (gettimeofday(&tv, (struct timezone *) NULL) == -1)
	return -1;
    Now->time = tv.tv_sec;
    Now->usec = tv.tv_usec;
#else
    /* Can't check for -1 since that might be a time, I guess. */
    (void) time(&Now->time);
    Now->usec = 0;
#endif /* defined(HAVE_GETTIMEOFDAY) */

    /* Now get the timezone if it's been an hour since the last time. */
    if (Now->time - LastTime > 60 * 60) {
	LastTime = Now->time;
	if ((tm = localtime(&Now->time)) == NULL)
	    return -1;
#if	defined(DONT_HAVE_TM_GMTOFF)
	/* To get the timezone, compare localtime with GMT. */
	local = *tm;
	if ((tm = gmtime(&Now->time)) == NULL)
	    return -1;
	gmt = *tm;

	/* Assume we are never more than 24 hours away. */
	LastTzone = gmt.tm_yday - local.tm_yday;
	if (LastTzone > 1)
	    LastTzone = -24;
	else if (LastTzone < -1)
	    LastTzone = 24;
	else
	    LastTzone *= 24;

	/* Scale in the hours and minutes; ignore seconds. */
	LastTzone += gmt.tm_hour - local.tm_hour;
	LastTzone *= 60;
	LastTzone += gmt.tm_min - local.tm_min;
#else
	LastTzone = (0 - tm->tm_gmtoff) / 60;
#endif /* defined(DONT_HAVE_TM_GMTOFF) */
    }
    Now->tzone = LastTzone;
    return 0;
}

#if defined(YYBYACC) && defined(YYPURE) && defined(LY_FIND_LEAKS)
#undef YYPURE
#define YYPURE 1
static void yyfreestack(YYSTACKDATA *);
static void parsedate_leaks(void)
{
    yyfreestack(&yystack);
}
#endif

time_t parsedate(char *p,
		 TIMEINFO * now)
{
    struct tm *tm;
    TIMEINFO ti;
    time_t Start;

#if defined(YYBYACC) && defined(YYPURE) && defined(LY_FIND_LEAKS)
    static int initialized;

    if (!initialized) {
	initialized = 1;
	atexit(parsedate_leaks);
    }
#endif

    yyInput = p;
    if (now == NULL) {
	now = &ti;
	(void) GetTimeInfo(&ti);
    }

    if ((tm = localtime(&now->time)) == NULL)
	return BAD_TIME;

    /* *INDENT-EQLS* */
    yyYear       = tm->tm_year + 1900;
    yyMonth      = tm->tm_mon + 1;
    yyDay        = tm->tm_mday;
    yyTimezone   = now->tzone;
    if (tm->tm_isdst)		/* Correct timezone offset for DST */
	yyTimezone   += DST_OFFSET * 60;
    yyDSTmode    = DSTmaybe;
    yyHour       = 0;
    yyMinutes    = 0;
    yySeconds    = 0;
    yyMeridian   = MER24;
    yyRelSeconds = 0;
    yyRelMonth   = 0;
    yyHaveDate   = 0;
    yyHaveRel    = 0;
    yyHaveTime   = 0;

    if (date_parse() || yyHaveTime > 1 || yyHaveDate > 1)
	return BAD_TIME;

    if (yyHaveDate || yyHaveTime) {
	Start = Convert(yyMonth, yyDay, yyYear, yyHour, yyMinutes, yySeconds,
			yyMeridian, yyDSTmode);
	if (isBadTime(Start))
	    return BAD_TIME;
    } else {
	Start = now->time;
	if (!yyHaveRel)
	    Start -= (tm->tm_hour * 60L + tm->tm_min) * 60L + tm->tm_sec;
    }

    Start += yyRelSeconds;
    if (yyRelMonth)
	Start += RelativeMonth(Start, yyRelMonth);

    /* Have to do *something* with a legitimate -1 so it's distinguishable
     * from the error return value.  (Alternately could set errno on error.) */
    return (Start == BAD_TIME) ? 0 : Start;
}
