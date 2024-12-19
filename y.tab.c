/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#define YYSTYPE_IS_DECLARED 1
typedef long YYSTYPE;

#include "type.h"
#include <stdio.h>
#include <stddef.h>

// 신택스 분석 관련 선언
extern int line_no;		// 라인 번호를 위한 변수
extern int syntax_err;		// 신택스 에러 횟수 저장을 위한 변수
extern A_NODE *root;		// 시작 노드
extern A_ID *current_id;	// 현재 가리키고 있는 심볼테이블 주소 
extern int current_level;	// 스코프를 위한 레벨값에 대한 변수
extern A_TYPE *int_type; 

// 시멘틱 분석 관련 선언
extern int semantic_err;

// 코드생성기 관련 선언
extern FILE *yyin;
FILE *fout;

void yyerror(const char *);
int yylex(); 

//=========================== 신택스 분석관련 함수 프로토타입 ===============================

A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE *);	// 새로운 노드를 만드는 함수
A_NODE *makeNodeList(NODE_NAME, A_NODE *, A_NODE *);		// 두 개 이상의 단일 노드를 연결하는 함수
A_ID *makeIdentifier(char *);					// 새로운 명칭 추가 함수
A_ID *makeDummyIdentifier();					// 명칭없이 타입만 선언되는 경우 호출됨
A_TYPE *makeType(T_KIND);
A_SPECIFIER *makeSpecifier(A_TYPE *, S_KIND);                   // 선언 지시자 생성하는 함수

A_ID *searchIdentifier(char *, A_ID *);
A_ID *searchIdentifierAtCurrentLevel(char *, A_ID *); // 현재 레벨에서 같은 명칭을 갖고 있는 심볼테이블을 반환하는 함수

A_SPECIFIER *updateSpecifier(A_SPECIFIER *, A_TYPE *, S_KIND); // 명시자 테이블을 합치는 함수
void checkForwardReference();			// 전방참조에 대한 완전한 선언 여부 확인하는 함수
void setDefaultSpecifier(A_SPECIFIER *);	// 반환타입이나 storage class가 지정되지 않은 경우 기본값으로 설정하는 함수
A_ID *linkDeclaratorList(A_ID *, A_ID *);	// 인자로 받은 두 개의 심볼테이블 목록을 연결하는 함수
A_ID *getIdentifierDeclared(char *);		// 명칭의 사용 가능 여부 검사하는 함수
A_TYPE *getTypeOfStructOrEnumIdentifier(T_KIND, char *, ID_KIND);

A_ID *setDeclaratorInit(A_ID *, A_NODE *);	 // 심볼테이블에 신택스 트리 연결하는 함수
A_ID *setDeclaratorKind(A_ID *, ID_KIND );
A_ID *setDeclaratorType(A_ID *, A_TYPE *);	 // 심볼테이블의 타입 정보 설정하는 함수
A_ID *setDeclaratorElementType(A_ID*, A_TYPE *); // 선언문이나 element의 타입을 설정하는 함수
A_ID *setDeclaratorTypeAndKind(A_ID *, A_TYPE *, ID_KIND);
A_ID *setDeclaratorListSpecifier(A_ID *, A_SPECIFIER *);	// 심볼테이블들을 검사하고, 명시자 테이블로부터 심볼테이블 속성을 결정하고 저장하는 함수
A_ID *setFunctionDeclaratorSpecifier(A_ID *, A_SPECIFIER *);	// 함수 명칭 심볼테이블과 몸체에 대한 신택스 트리 연결하는 함수
A_ID *setFunctionDeclaratorBody(A_ID *, A_NODE *);		// 함수 몸체에서 명칭에 대한 심볼테이블과 신택스 트리 연결하는 함수
A_ID *setParameterDeclaratorSpecifier(A_ID *, A_SPECIFIER *);	// 심볼테이블의 타입 정보를 설정하고 명칭 종류를 ID_PARAM으로 설정하며 파라미터 검사
A_ID *setStructDeclaratorListSpecifier(A_ID *, A_TYPE *);
A_TYPE *setTypeNameSpecifier(A_TYPE *, A_SPECIFIER *);	// 타입명시자의 기억 장소 명시자 포함 여부 검사 후, 주어진 타입의 엘리먼트 타입으로 타입명시자 지정
A_TYPE *setTypeElementType(A_TYPE *, A_TYPE *);		// 첫 번째 인자로 주어진 타입 테이블의 엘리먼트 타입으로 두 번째 인자로 주어진 타입테이블을 연결하는 함수
A_TYPE *setTypeField(A_TYPE *, A_ID *);
A_TYPE *setTypeExpr(A_TYPE *, A_NODE *); // 타입테이블의 <expr> 필드에 신택스 트리 연결
A_TYPE *setTypeAndKindOfDeclarator(A_TYPE *, ID_KIND, A_ID *);
A_TYPE *setTypeStructOrEnumIdentifier(T_KIND, char *, ID_KIND);

BOOLEAN isNotSameFormalParameters(A_ID *, A_ID *);	// 전달 받은 두 심볼테이블(파라미터 정보를 담은)이 같은지 확인하는 함수
BOOLEAN isNotSameType(A_TYPE *, A_TYPE*);		// 전달받은 두 타입이 같은지 확인하는 함수
BOOLEAN isPointerOrArrayType(A_TYPE *);			// 타입이 pointer인지 array인지 확인하는 함수

void syntax_error();
void initialize();

//===========================================================================================


#line 143 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    TYPE_IDENTIFIER = 259,
    INTEGER_CONSTANT = 260,
    FLOAT_CONSTANT = 261,
    CHARACTER_CONSTANT = 262,
    STRING_LITERAL = 263,
    PLUS = 264,
    MINUS = 265,
    PLUSPLUS = 266,
    MINUSMINUS = 267,
    BAR = 268,
    BARBAR = 269,
    AMP = 270,
    AMPAMP = 271,
    ARROW = 272,
    LSS = 273,
    GTR = 274,
    LEQ = 275,
    GEQ = 276,
    EQL = 277,
    NEQ = 278,
    DOTDOTDOT = 279,
    SEMICOLON = 280,
    COLON = 281,
    LP = 282,
    RP = 283,
    LB = 284,
    RB = 285,
    LR = 286,
    RR = 287,
    PERIOD = 288,
    COMMA = 289,
    EXCL = 290,
    STAR = 291,
    SLASH = 292,
    PERCENT = 293,
    ASSIGN = 294,
    AUTO_SYM = 295,
    STATIC_SYM = 296,
    TYPEDEF_SYM = 297,
    STRUCT_SYM = 298,
    UNION_SYM = 299,
    ENUM_SYM = 300,
    SIZEOF_SYM = 301,
    IF_SYM = 302,
    ELSE_SYM = 303,
    FOR_SYM = 304,
    WHILE_SYM = 305,
    DO_SYM = 306,
    CONTINUE_SYM = 307,
    BREAK_SYM = 308,
    RETURN_SYM = 309,
    SWITCH_SYM = 310,
    CASE_SYM = 311,
    DEFAULT_SYM = 312
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define TYPE_IDENTIFIER 259
#define INTEGER_CONSTANT 260
#define FLOAT_CONSTANT 261
#define CHARACTER_CONSTANT 262
#define STRING_LITERAL 263
#define PLUS 264
#define MINUS 265
#define PLUSPLUS 266
#define MINUSMINUS 267
#define BAR 268
#define BARBAR 269
#define AMP 270
#define AMPAMP 271
#define ARROW 272
#define LSS 273
#define GTR 274
#define LEQ 275
#define GEQ 276
#define EQL 277
#define NEQ 278
#define DOTDOTDOT 279
#define SEMICOLON 280
#define COLON 281
#define LP 282
#define RP 283
#define LB 284
#define RB 285
#define LR 286
#define RR 287
#define PERIOD 288
#define COMMA 289
#define EXCL 290
#define STAR 291
#define SLASH 292
#define PERCENT 293
#define ASSIGN 294
#define AUTO_SYM 295
#define STATIC_SYM 296
#define TYPEDEF_SYM 297
#define STRUCT_SYM 298
#define UNION_SYM 299
#define ENUM_SYM 300
#define SIZEOF_SYM 301
#define IF_SYM 302
#define ELSE_SYM 303
#define FOR_SYM 304
#define WHILE_SYM 305
#define DO_SYM 306
#define CONTINUE_SYM 307
#define BREAK_SYM 308
#define RETURN_SYM 309
#define SWITCH_SYM 310
#define CASE_SYM 311
#define DEFAULT_SYM 312

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
typedef yytype_int16 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   454

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  173
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  290

#define YYUNDEFTOK  2
#define YYMAXUTOK   312


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    92,    92,    99,   100,   104,   105,   111,   111,   113,
     113,   121,   122,   126,   127,   131,   135,   136,   137,   138,
     142,   143,   144,   148,   149,   155,   156,   160,   161,   167,
     168,   172,   173,   179,   180,   181,   187,   188,   186,   190,
     190,   190,   192,   202,   203,   207,   208,   212,   216,   217,
     221,   226,   226,   228,   228,   230,   234,   235,   239,   240,
     240,   248,   249,   253,   254,   260,   261,   262,   264,   264,
     273,   274,   278,   279,   283,   284,   289,   290,   295,   296,
     300,   301,   302,   306,   307,   308,   309,   310,   315,   316,
     320,   321,   325,   326,   327,   328,   329,   330,   335,   336,
     341,   341,   352,   353,   359,   360,   361,   367,   368,   369,
     373,   378,   379,   384,   385,   386,   392,   393,   397,   398,
     404,   405,   409,   414,   418,   422,   423,   427,   432,   433,
     437,   438,   442,   443,   444,   449,   450,   451,   452,   453,
     457,   463,   464,   465,   469,   470,   471,   472,   477,   478,
     484,   485,   486,   487,   488,   489,   490,   491,   492,   493,
     499,   500,   501,   502,   503,   504,   505,   511,   512,   513,
     514,   515,   516,   521
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "TYPE_IDENTIFIER",
  "INTEGER_CONSTANT", "FLOAT_CONSTANT", "CHARACTER_CONSTANT",
  "STRING_LITERAL", "PLUS", "MINUS", "PLUSPLUS", "MINUSMINUS", "BAR",
  "BARBAR", "AMP", "AMPAMP", "ARROW", "LSS", "GTR", "LEQ", "GEQ", "EQL",
  "NEQ", "DOTDOTDOT", "SEMICOLON", "COLON", "LP", "RP", "LB", "RB", "LR",
  "RR", "PERIOD", "COMMA", "EXCL", "STAR", "SLASH", "PERCENT", "ASSIGN",
  "AUTO_SYM", "STATIC_SYM", "TYPEDEF_SYM", "STRUCT_SYM", "UNION_SYM",
  "ENUM_SYM", "SIZEOF_SYM", "IF_SYM", "ELSE_SYM", "FOR_SYM", "WHILE_SYM",
  "DO_SYM", "CONTINUE_SYM", "BREAK_SYM", "RETURN_SYM", "SWITCH_SYM",
  "CASE_SYM", "DEFAULT_SYM", "$accept", "program", "translation_unit",
  "external_declaration", "function_definition", "@1", "@2",
  "declaration_list_opt", "declaration_list", "declaration",
  "declaration_specifiers", "storage_class_specifier",
  "init_declarator_list_opt", "init_declarator_list", "init_declarator",
  "initializer", "initializer_list", "type_specifier",
  "struct_type_specifier", "@3", "@4", "@5", "@6", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "enum_type_specifier",
  "@7", "@8", "enumerator_list", "enumerator", "@9", "declarator",
  "pointer", "direct_declarator", "@10", "parameter_type_list_opt",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "abstract_declarator_opt", "abstract_declarator",
  "direct_abstract_declarator", "statement_list_opt", "statement_list",
  "statement", "labeled_statement", "compound_statement", "@11",
  "expression_statement", "selection_statement", "iteration_statement",
  "for_expression", "expression_opt", "jump_statement",
  "arg_expression_list_opt", "arg_expression_list",
  "constant_expression_opt", "constant_expression", "expression",
  "comma_expression", "assignment_expression", "conditional_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "cast_expression", "unary_expression",
  "postfix_expression", "primary_expression", "type_name", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312
};
# endif

#define YYPACT_NINF (-211)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-60)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     231,  -211,  -211,    28,   -14,  -211,  -211,  -211,  -211,  -211,
      31,    37,   231,  -211,  -211,  -211,    28,    87,    87,  -211,
      54,  -211,  -211,    17,     9,    42,  -211,    46,    62,  -211,
    -211,    15,    69,  -211,    23,  -211,  -211,    76,    79,    82,
       9,  -211,   168,  -211,    94,    70,  -211,    28,   353,    82,
     117,  -211,  -211,  -211,    87,  -211,  -211,  -211,  -211,  -211,
     168,   168,   366,   366,   168,   309,   168,   168,   408,   133,
    -211,  -211,  -211,  -211,  -211,   187,   196,    74,    99,  -211,
     172,   131,  -211,   177,   209,  -211,    70,   178,    72,  -211,
    -211,   179,   353,  -211,  -211,  -211,  -211,    43,    87,    24,
     191,  -211,   188,  -211,  -211,  -211,  -211,   168,  -211,  -211,
    -211,    12,   195,   197,  -211,  -211,   309,  -211,  -211,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,  -211,  -211,   221,   168,   168,   224,   112,
     189,  -211,    70,  -211,   162,    43,    28,    39,  -211,   254,
      87,  -211,    28,   405,   168,  -211,    29,  -211,  -211,   173,
    -211,   166,    97,   186,  -211,  -211,   168,   201,   196,    74,
      99,    99,  -211,  -211,  -211,  -211,   131,   131,  -211,  -211,
    -211,  -211,  -211,   202,   198,  -211,   210,  -211,  -211,   168,
    -211,  -211,   353,   111,     8,  -211,  -211,  -211,  -211,  -211,
     212,   214,   241,   254,   245,   252,   168,   251,   168,   256,
     248,   254,  -211,  -211,  -211,  -211,  -211,  -211,  -211,   258,
    -211,   259,   260,   262,   173,    87,   168,  -211,  -211,  -211,
    -211,  -211,   168,  -211,  -211,  -211,  -211,  -211,    28,   168,
     168,   168,   234,  -211,  -211,   261,  -211,   168,   267,   254,
    -211,  -211,  -211,  -211,  -211,  -211,   266,   265,  -211,  -211,
     268,   269,   273,   271,   275,  -211,   294,   254,  -211,  -211,
    -211,   254,   254,   168,   254,   168,   254,  -211,   277,  -211,
     298,  -211,   299,  -211,   254,   168,   301,  -211,  -211,  -211
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    65,    35,     0,    63,    20,    21,    22,    43,    44,
      53,     0,     2,     3,     5,     6,    23,    17,    16,    33,
      39,    34,     9,     0,    62,     0,    64,    55,     0,     1,
       4,     0,    24,    25,    27,    19,    18,    42,     0,     0,
      61,    68,   120,    66,     0,     0,    15,     0,     0,     0,
       0,    40,   100,    10,    70,   167,   168,   169,   170,   171,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   127,   128,   130,   132,   135,
     140,   141,   144,   148,   150,   160,     0,    58,     0,    56,
      26,    27,     0,    28,    29,     8,    37,     0,    11,    78,
       0,    71,    72,    74,   157,   148,   156,     0,   151,   152,
     153,    78,     0,     0,   155,   154,     0,   158,    67,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   165,   166,     0,   116,     0,     0,     0,
       0,    54,     0,    31,     0,     0,     0,     0,    45,    88,
      12,    13,    23,    70,   120,    76,    81,    77,    79,    80,
      69,     0,    70,    81,   173,   172,     0,     0,   129,   131,
     133,   134,   136,   137,   138,   139,   142,   143,   145,   146,
     147,   126,   164,     0,   117,   118,     0,   163,    52,     0,
      57,    30,     0,     0,     0,    48,    50,    41,    46,   102,
       0,     0,     0,     0,     0,     0,   111,     0,     0,     0,
       0,    89,    90,    92,    93,    94,    95,    96,    97,     0,
      14,     0,     0,     0,    82,    70,   120,    73,    75,   149,
     159,   162,     0,   161,    60,    32,    38,    47,     0,     0,
     111,     0,     0,   114,   115,     0,   112,     0,     0,     0,
     101,    91,   103,    86,    83,    84,     0,     0,   119,    49,
       0,     0,     0,     0,     0,   113,     0,     0,    99,    87,
      85,     0,     0,   111,     0,     0,     0,    98,   104,   109,
       0,   107,     0,   106,     0,   111,     0,   105,   110,   108
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -211,  -211,  -211,   316,  -211,  -211,  -211,  -211,  -211,   -72,
       7,  -211,  -211,  -211,   282,   -83,  -211,   -79,  -211,  -211,
    -211,  -211,  -211,  -211,   185,  -134,  -211,    93,  -211,  -211,
    -211,   246,   192,  -211,    -1,     0,   -20,  -211,   -53,  -211,
    -211,   174,   222,  -101,   -87,  -211,  -211,  -182,  -211,    -4,
    -211,  -211,  -211,  -211,  -211,  -210,  -211,  -211,  -211,  -126,
     -43,   -42,  -211,  -124,  -211,  -211,   218,   219,    13,    35,
    -211,    -6,   -50,   125,  -211,  -211,   225
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,    14,    49,    39,   149,   150,    15,
      99,    17,    31,    32,    33,    93,   144,    18,    19,    50,
     145,    38,    97,    20,   147,   148,   194,   195,    21,    44,
      28,    88,    89,   140,    22,    23,    24,    54,   221,   101,
     102,   103,   157,   158,   159,   210,   211,   212,   213,   214,
      98,   215,   216,   217,   261,   245,   218,   183,   184,    69,
      70,   219,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,   113
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   100,    25,    40,    26,    94,    71,    16,   181,   143,
     104,   106,   185,   198,   110,    34,   114,   115,   146,    16,
       1,   242,     4,   112,    35,    36,   151,     1,   223,   251,
     262,     1,     1,   237,    27,    53,    41,    29,    42,   162,
      46,   154,   238,     2,     3,    95,    91,     2,     4,    94,
      71,   153,   222,   154,    -7,     3,   153,    37,   154,   198,
       4,   222,    48,   280,     4,   112,   146,   268,   146,   224,
      43,   197,   111,    87,   112,   288,   224,   -51,   220,   178,
     179,   180,     8,     9,    10,   277,     8,     9,    10,   278,
     279,     2,   281,    45,   283,   186,   121,   122,   155,   156,
     257,     2,   287,    47,   141,   152,   142,   -36,   258,   235,
      51,   163,    71,    52,   146,     2,   229,   123,   124,   125,
     126,   176,   177,   111,   162,    86,   154,     5,     6,     7,
       8,     9,    10,     4,   170,   171,    40,     5,     6,     7,
       8,     9,    10,   236,   188,   196,   142,   234,    96,    94,
      71,    91,    25,   156,     8,     9,    10,   152,   172,   173,
     174,   175,   163,   118,   246,   248,    71,   129,   130,   131,
       2,    55,   256,    56,    57,    58,    59,    60,    61,    62,
      63,   127,   128,    64,    71,   105,   105,   108,   109,   105,
     227,   105,   105,   117,   191,    65,   192,   260,   246,   263,
     225,   119,   226,    66,    67,   266,     5,     6,     7,     8,
       9,    10,   120,   162,    68,   154,   132,   -59,    48,   160,
     133,   134,   161,   165,   182,   166,   135,   187,   189,   230,
     231,   246,   232,   282,     1,     2,   136,   196,   137,   239,
     233,   240,   138,   246,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,    55,     3,    56,
      57,    58,    59,    60,    61,    62,    63,     4,   241,    64,
     243,     5,     6,     7,     8,     9,    10,   244,   247,   199,
     250,    65,   249,   252,   264,    52,   265,   253,   254,    66,
      67,   105,   255,   267,   269,   270,   271,   272,   273,   274,
      68,   200,   275,   201,   202,   203,   204,   205,   206,   207,
     208,   209,    55,     2,    56,    57,    58,    59,    60,    61,
      62,    63,   276,   285,    64,   284,   289,   286,    30,    90,
     193,   259,   139,   164,   190,   228,    65,   168,     0,   169,
       0,   167,     0,     0,    66,    67,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    68,    55,     0,    56,    57,
      58,    59,    60,    61,    62,    63,     0,     0,    64,    55,
       0,    56,    57,    58,    59,    60,    61,    62,    63,     0,
      65,    64,     0,     0,    92,     0,     0,     0,    66,    67,
       0,     0,     0,   107,     0,     0,     0,     0,     0,    68,
       0,    66,    67,     0,     0,     0,     0,     0,     1,     2,
       0,    55,    68,    56,    57,    58,    59,    60,    61,    62,
      63,     0,     0,    64,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,   154,   116,     0,     0,     0,     0,
       0,     4,     0,    66,    67,     5,     6,     7,     8,     9,
      10,     0,     0,     0,    68
};

static const yytype_int16 yycheck[] =
{
      42,    54,     3,    23,     4,    48,    48,     0,   132,    92,
      60,    61,   136,   147,    64,    16,    66,    67,    97,    12,
       3,   203,    36,    65,    17,    18,    98,     3,   154,   211,
     240,     3,     3,    25,     3,    39,    27,     0,    29,    27,
      25,    29,    34,     4,    27,    49,    47,     4,    36,    92,
      92,    27,   153,    29,    31,    27,    27,     3,    29,   193,
      36,   162,    39,   273,    36,   107,   145,   249,   147,   156,
      28,    32,    65,     3,   116,   285,   163,    31,   150,   129,
     130,   131,    43,    44,    45,   267,    43,    44,    45,   271,
     272,     4,   274,    31,   276,   137,    22,    23,    99,    99,
     226,     4,   284,    34,    32,    98,    34,    31,   232,   192,
      31,   111,   154,    31,   193,     4,   166,    18,    19,    20,
      21,   127,   128,   116,    27,    31,    29,    40,    41,    42,
      43,    44,    45,    36,   121,   122,   156,    40,    41,    42,
      43,    44,    45,    32,    32,   146,    34,   189,    31,   192,
     192,   152,   153,   153,    43,    44,    45,   150,   123,   124,
     125,   126,   162,    30,   206,   208,   208,    36,    37,    38,
       4,     3,   225,     5,     6,     7,     8,     9,    10,    11,
      12,     9,    10,    15,   226,    60,    61,    62,    63,    64,
      24,    66,    67,    68,    32,    27,    34,   239,   240,   241,
      27,    14,    29,    35,    36,   247,    40,    41,    42,    43,
      44,    45,    16,    27,    46,    29,    39,    39,    39,    28,
      11,    12,    34,    28,     3,    28,    17,     3,    39,    28,
      28,   273,    34,   275,     3,     4,    27,   238,    29,    27,
      30,    27,    33,   285,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,     3,    27,     5,
       6,     7,     8,     9,    10,    11,    12,    36,    27,    15,
      25,    40,    41,    42,    43,    44,    45,    25,    27,    25,
      32,    27,    26,    25,    50,    31,    25,    28,    28,    35,
      36,   166,    30,    26,    28,    30,    28,    28,    25,    28,
      46,    47,    27,    49,    50,    51,    52,    53,    54,    55,
      56,    57,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    28,    25,    15,    48,    25,    28,    12,    47,
     145,   238,    86,   111,   142,   161,    27,   119,    -1,   120,
      -1,   116,    -1,    -1,    35,    36,    -1,    -1,    -1,    40,
      41,    42,    43,    44,    45,    46,     3,    -1,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    -1,    15,     3,
      -1,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      27,    15,    -1,    -1,    31,    -1,    -1,    -1,    35,    36,
      -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    35,    36,    -1,    -1,    -1,    -1,    -1,     3,     4,
      -1,     3,    46,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    29,    27,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    35,    36,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    27,    36,    40,    41,    42,    43,    44,
      45,    59,    60,    61,    62,    67,    68,    69,    75,    76,
      81,    86,    92,    93,    94,    92,    93,     3,    88,     0,
      61,    70,    71,    72,    92,    68,    68,     3,    79,    64,
      94,    27,    29,    28,    87,    31,    25,    34,    39,    63,
      77,    31,    31,   107,    95,     3,     5,     6,     7,     8,
       9,    10,    11,    12,    15,    27,    35,    36,    46,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    31,     3,    89,    90,
      72,    92,    31,    73,   118,   107,    31,    80,   108,    68,
      96,    97,    98,    99,   130,   131,   130,    27,   131,   131,
     130,    68,   119,   134,   130,   130,    27,   131,    30,    14,
      16,    22,    23,    18,    19,    20,    21,     9,    10,    36,
      37,    38,    39,    11,    12,    17,    27,    29,    33,    89,
      91,    32,    34,    73,    74,    78,    75,    82,    83,    65,
      66,    67,    68,    27,    29,    92,    93,   100,   101,   102,
      28,    34,    27,    93,   100,    28,    28,   134,   124,   125,
     126,   126,   127,   127,   127,   127,   129,   129,   130,   130,
     130,   121,     3,   115,   116,   121,   119,     3,    32,    39,
      90,    32,    34,    82,    84,    85,    92,    32,    83,    25,
      47,    49,    50,    51,    52,    53,    54,    55,    56,    57,
     103,   104,   105,   106,   107,   109,   110,   111,   114,   119,
      67,    96,   101,   117,   102,    27,    29,    24,    99,   130,
      28,    28,    34,    30,   119,    73,    32,    25,    34,    27,
      27,    27,   105,    25,    25,   113,   119,    27,   118,    26,
      32,   105,    25,    28,    28,    30,    96,   117,   121,    85,
     119,   112,   113,   119,    50,    25,   119,    26,   105,    28,
      30,    28,    28,    25,    28,    27,    28,   105,   105,   105,
     113,   105,   119,   105,    48,    25,    28,   105,   113,    25
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    63,    62,    64,
      62,    65,    65,    66,    66,    67,    68,    68,    68,    68,
      69,    69,    69,    70,    70,    71,    71,    72,    72,    73,
      73,    74,    74,    75,    75,    75,    77,    78,    76,    79,
      80,    76,    76,    81,    81,    82,    82,    83,    84,    84,
      85,    87,    86,    88,    86,    86,    89,    89,    90,    91,
      90,    92,    92,    93,    93,    94,    94,    94,    95,    94,
      96,    96,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   101,   102,   102,   102,   102,   102,   103,   103,
     104,   104,   105,   105,   105,   105,   105,   105,   106,   106,
     108,   107,   109,   109,   110,   110,   110,   111,   111,   111,
     112,   113,   113,   114,   114,   114,   115,   115,   116,   116,
     117,   117,   118,   119,   120,   121,   121,   122,   123,   123,
     124,   124,   125,   125,   125,   126,   126,   126,   126,   126,
     127,   128,   128,   128,   129,   129,   129,   129,   130,   130,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     132,   132,   132,   132,   132,   132,   132,   133,   133,   133,
     133,   133,   133,   134
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     0,     4,     0,
       3,     0,     1,     1,     2,     3,     1,     1,     2,     2,
       1,     1,     1,     0,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     0,     0,     7,     0,
       0,     6,     2,     1,     1,     1,     2,     3,     1,     3,
       1,     0,     6,     0,     5,     2,     1,     3,     1,     0,
       4,     2,     1,     1,     2,     1,     3,     4,     0,     5,
       0,     1,     1,     3,     1,     3,     2,     2,     0,     1,
       1,     1,     2,     3,     3,     4,     3,     4,     0,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     4,     3,
       0,     5,     1,     2,     5,     7,     5,     5,     7,     5,
       5,     0,     1,     3,     2,     2,     0,     1,     1,     3,
       0,     1,     1,     1,     1,     1,     3,     1,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     1,     3,     3,     1,     3,     3,     3,     1,     4,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       1,     4,     4,     3,     3,     2,     2,     1,     1,     1,
       1,     1,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 93 "parser.y"
      {root = makeNode(N_PROGRAM,NIL,yyvsp[0],NIL); checkForwardReference();}
#line 1747 "y.tab.c"
    break;

  case 3:
#line 99 "parser.y"
                                            {yyval = yyvsp[0];}
#line 1753 "y.tab.c"
    break;

  case 4:
#line 100 "parser.y"
                                            {yyval = linkDeclaratorList(yyvsp[-1], yyvsp[0]);}
#line 1759 "y.tab.c"
    break;

  case 5:
#line 104 "parser.y"
                          {yyval=yyvsp[0];}
#line 1765 "y.tab.c"
    break;

  case 6:
#line 105 "parser.y"
                          {yyval=yyvsp[0];}
#line 1771 "y.tab.c"
    break;

  case 7:
#line 111 "parser.y"
                                       {yyval=setFunctionDeclaratorSpecifier(yyvsp[0],yyvsp[-1]);}
#line 1777 "y.tab.c"
    break;

  case 8:
#line 112 "parser.y"
                         {yyval=setFunctionDeclaratorBody(yyvsp[-1],yyvsp[0]);}
#line 1783 "y.tab.c"
    break;

  case 9:
#line 113 "parser.y"
                 {yyval=setFunctionDeclaratorSpecifier(yyvsp[0],makeSpecifier(int_type,0));}
#line 1789 "y.tab.c"
    break;

  case 10:
#line 114 "parser.y"
                         {yyval=setFunctionDeclaratorBody(yyvsp[-1],yyvsp[0]);}
#line 1795 "y.tab.c"
    break;

  case 11:
#line 121 "parser.y"
                                  {yyval=NIL;}
#line 1801 "y.tab.c"
    break;

  case 12:
#line 122 "parser.y"
                                  {yyval=yyvsp[0];}
#line 1807 "y.tab.c"
    break;

  case 13:
#line 126 "parser.y"
                                   {yyval=yyvsp[0];}
#line 1813 "y.tab.c"
    break;

  case 14:
#line 127 "parser.y"
                                   {yyval=linkDeclaratorList(yyvsp[-1],yyvsp[0]);}
#line 1819 "y.tab.c"
    break;

  case 15:
#line 131 "parser.y"
                                                                {yyval=setDeclaratorListSpecifier(yyvsp[-1],yyvsp[-2]);}
#line 1825 "y.tab.c"
    break;

  case 16:
#line 135 "parser.y"
                                                        {yyval=makeSpecifier(yyvsp[0],0);}
#line 1831 "y.tab.c"
    break;

  case 17:
#line 136 "parser.y"
                                                        {yyval=makeSpecifier(0,yyvsp[0]);}
#line 1837 "y.tab.c"
    break;

  case 18:
#line 137 "parser.y"
                                                        {yyval=updateSpecifier(yyvsp[0],yyvsp[-1],0);}
#line 1843 "y.tab.c"
    break;

  case 19:
#line 138 "parser.y"
                                                        {yyval=updateSpecifier(yyvsp[0],0,yyvsp[-1]);}
#line 1849 "y.tab.c"
    break;

  case 20:
#line 142 "parser.y"
                        {yyval=S_AUTO;}
#line 1855 "y.tab.c"
    break;

  case 21:
#line 143 "parser.y"
                        {yyval=S_STATIC;}
#line 1861 "y.tab.c"
    break;

  case 22:
#line 144 "parser.y"
                        {yyval=S_TYPEDEF;}
#line 1867 "y.tab.c"
    break;

  case 23:
#line 148 "parser.y"
                                {yyval=makeDummyIdentifier();}
#line 1873 "y.tab.c"
    break;

  case 24:
#line 149 "parser.y"
                                {yyval=yyvsp[0];}
#line 1879 "y.tab.c"
    break;

  case 25:
#line 155 "parser.y"
                                                 {yyval=yyvsp[0];}
#line 1885 "y.tab.c"
    break;

  case 26:
#line 156 "parser.y"
                                                 {yyval=linkDeclaratorList(yyvsp[-2],yyvsp[0]);}
#line 1891 "y.tab.c"
    break;

  case 27:
#line 160 "parser.y"
                                    {yyval=yyvsp[0];}
#line 1897 "y.tab.c"
    break;

  case 28:
#line 161 "parser.y"
                                    {yyval=setDeclaratorInit(yyvsp[-2],yyvsp[0]);}
#line 1903 "y.tab.c"
    break;

  case 29:
#line 167 "parser.y"
                                {yyval=makeNode(N_INIT_LIST_ONE, NIL, yyvsp[0], NIL);}
#line 1909 "y.tab.c"
    break;

  case 30:
#line 168 "parser.y"
                                {yyval=yyvsp[-1];}
#line 1915 "y.tab.c"
    break;

  case 31:
#line 172 "parser.y"
                                         {yyval=makeNode(N_INIT_LIST,yyvsp[0],NIL,makeNode(N_INIT_LIST_NIL, NIL,NIL,NIL));}
#line 1921 "y.tab.c"
    break;

  case 32:
#line 173 "parser.y"
                                         {yyval=makeNodeList(N_INIT_LIST,yyvsp[-2],yyvsp[0]);}
#line 1927 "y.tab.c"
    break;

  case 33:
#line 179 "parser.y"
                                {yyval=yyvsp[0];}
#line 1933 "y.tab.c"
    break;

  case 34:
#line 180 "parser.y"
                                {yyval=yyvsp[0];}
#line 1939 "y.tab.c"
    break;

  case 35:
#line 181 "parser.y"
                                {yyval=yyvsp[0];}
#line 1945 "y.tab.c"
    break;

  case 36:
#line 187 "parser.y"
      {yyval = setTypeStructOrEnumIdentifier(yyvsp[-1],yyvsp[0],ID_STRUCT);}
#line 1951 "y.tab.c"
    break;

  case 37:
#line 188 "parser.y"
         {yyval=current_id; current_level++;}
#line 1957 "y.tab.c"
    break;

  case 38:
#line 189 "parser.y"
      {checkForwardReference(); yyval=setTypeField(yyvsp[-4],yyvsp[-1]); current_level--; current_id=yyvsp[-2];}
#line 1963 "y.tab.c"
    break;

  case 39:
#line 190 "parser.y"
                      {yyval=makeType(yyvsp[0]);}
#line 1969 "y.tab.c"
    break;

  case 40:
#line 190 "parser.y"
                                            {yyval=current_id; current_level++;}
#line 1975 "y.tab.c"
    break;

  case 41:
#line 191 "parser.y"
                                 {checkForwardReference(); yyval=setTypeField(yyvsp[-4],yyvsp[-1]); current_level--; current_id=yyvsp[-2];}
#line 1981 "y.tab.c"
    break;

  case 42:
#line 192 "parser.y"
                                 {yyval=getTypeOfStructOrEnumIdentifier(yyvsp[-1],yyvsp[0],ID_STRUCT);}
#line 1987 "y.tab.c"
    break;

  case 43:
#line 202 "parser.y"
                  {yyval=T_STRUCT;}
#line 1993 "y.tab.c"
    break;

  case 44:
#line 203 "parser.y"
                  {yyval=T_UNION;}
#line 1999 "y.tab.c"
    break;

  case 45:
#line 207 "parser.y"
                                                 {yyval=yyvsp[0];}
#line 2005 "y.tab.c"
    break;

  case 46:
#line 208 "parser.y"
                                                 {yyval=linkDeclaratorList(yyvsp[-1],yyvsp[0]);}
#line 2011 "y.tab.c"
    break;

  case 47:
#line 212 "parser.y"
                                                      {yyval=setStructDeclaratorListSpecifier(yyvsp[-1],yyvsp[-2]);}
#line 2017 "y.tab.c"
    break;

  case 48:
#line 216 "parser.y"
                                                     {yyval=yyvsp[0];}
#line 2023 "y.tab.c"
    break;

  case 49:
#line 217 "parser.y"
                                                     {yyval=linkDeclaratorList(yyvsp[-2],yyvsp[0]);}
#line 2029 "y.tab.c"
    break;

  case 50:
#line 221 "parser.y"
                 {yyval=yyvsp[0];}
#line 2035 "y.tab.c"
    break;

  case 51:
#line 226 "parser.y"
                                        {yyval=setTypeStructOrEnumIdentifier(T_ENUM, yyvsp[0], ID_ENUM);}
#line 2041 "y.tab.c"
    break;

  case 52:
#line 227 "parser.y"
                                        {yyval=setTypeField(yyvsp[-3],yyvsp[-1]);}
#line 2047 "y.tab.c"
    break;

  case 53:
#line 228 "parser.y"
                                        {yyval=makeType(T_ENUM);}
#line 2053 "y.tab.c"
    break;

  case 54:
#line 229 "parser.y"
                                        {yyval=setTypeField(yyvsp[-3],yyvsp[-1]);}
#line 2059 "y.tab.c"
    break;

  case 55:
#line 230 "parser.y"
                                        {yyval=getTypeOfStructOrEnumIdentifier(T_ENUM, yyvsp[0], ID_ENUM);}
#line 2065 "y.tab.c"
    break;

  case 56:
#line 234 "parser.y"
                                        {yyval=yyvsp[0];}
#line 2071 "y.tab.c"
    break;

  case 57:
#line 235 "parser.y"
                                        {yyval=linkDeclaratorList(yyvsp[-2],yyvsp[0]);}
#line 2077 "y.tab.c"
    break;

  case 58:
#line 239 "parser.y"
                 {yyval=setDeclaratorKind(makeIdentifier(yyvsp[0]), ID_ENUM_LITERAL);}
#line 2083 "y.tab.c"
    break;

  case 59:
#line 240 "parser.y"
                 {yyval=setDeclaratorKind(makeIdentifier(yyvsp[0]), ID_ENUM_LITERAL);}
#line 2089 "y.tab.c"
    break;

  case 60:
#line 241 "parser.y"
                        {yyval=setDeclaratorInit(yyvsp[-2],yyvsp[0]);}
#line 2095 "y.tab.c"
    break;

  case 61:
#line 248 "parser.y"
                                {yyval=setDeclaratorElementType(yyvsp[0],yyvsp[-1]);}
#line 2101 "y.tab.c"
    break;

  case 62:
#line 249 "parser.y"
                                {yyval=yyvsp[0];}
#line 2107 "y.tab.c"
    break;

  case 63:
#line 253 "parser.y"
                                {yyval=makeType(T_POINTER);}
#line 2113 "y.tab.c"
    break;

  case 64:
#line 254 "parser.y"
                                {yyval=setTypeElementType(yyvsp[0], makeType(T_POINTER));}
#line 2119 "y.tab.c"
    break;

  case 65:
#line 260 "parser.y"
                         {yyval=makeIdentifier(yyvsp[0]);}
#line 2125 "y.tab.c"
    break;

  case 66:
#line 261 "parser.y"
                         {yyval=yyvsp[-1];}
#line 2131 "y.tab.c"
    break;

  case 67:
#line 263 "parser.y"
      {yyval = setDeclaratorElementType(yyvsp[-3], setTypeExpr(makeType(T_ARRAY),yyvsp[-1]));}
#line 2137 "y.tab.c"
    break;

  case 68:
#line 264 "parser.y"
                           {yyval=current_id; current_level++;}
#line 2143 "y.tab.c"
    break;

  case 69:
#line 266 "parser.y"
      {checkForwardReference(); current_level--; current_id=yyvsp[-2];
      yyval=setDeclaratorElementType(yyvsp[-4], setTypeField(makeType(T_FUNC),yyvsp[-1]));}
#line 2150 "y.tab.c"
    break;

  case 70:
#line 273 "parser.y"
                                {yyval=NIL;}
#line 2156 "y.tab.c"
    break;

  case 71:
#line 274 "parser.y"
                                {yyval=yyvsp[0];}
#line 2162 "y.tab.c"
    break;

  case 72:
#line 278 "parser.y"
                                        {yyval=yyvsp[0];}
#line 2168 "y.tab.c"
    break;

  case 73:
#line 279 "parser.y"
                                        {yyval=linkDeclaratorList(yyvsp[-2], setDeclaratorKind(makeDummyIdentifier(),ID_PARM));}
#line 2174 "y.tab.c"
    break;

  case 74:
#line 283 "parser.y"
                                                 {yyval=yyvsp[0];}
#line 2180 "y.tab.c"
    break;

  case 75:
#line 284 "parser.y"
                                                 {yyval=linkDeclaratorList(yyvsp[-2],yyvsp[0]);}
#line 2186 "y.tab.c"
    break;

  case 76:
#line 289 "parser.y"
                                                     {yyval=setParameterDeclaratorSpecifier(yyvsp[0],yyvsp[-1]);}
#line 2192 "y.tab.c"
    break;

  case 77:
#line 290 "parser.y"
                                                     {yyval=setParameterDeclaratorSpecifier(setDeclaratorType(makeDummyIdentifier(),yyvsp[0]),yyvsp[-1]);}
#line 2198 "y.tab.c"
    break;

  case 78:
#line 295 "parser.y"
                           {yyval=NIL;}
#line 2204 "y.tab.c"
    break;

  case 79:
#line 296 "parser.y"
                           {yyval=yyvsp[0];}
#line 2210 "y.tab.c"
    break;

  case 80:
#line 300 "parser.y"
                                          {yyval=yyvsp[0];}
#line 2216 "y.tab.c"
    break;

  case 81:
#line 301 "parser.y"
                                          {yyval=makeType(T_POINTER);}
#line 2222 "y.tab.c"
    break;

  case 82:
#line 302 "parser.y"
                                          {yyval=setTypeElementType(yyvsp[0], makeType(T_POINTER));}
#line 2228 "y.tab.c"
    break;

  case 83:
#line 306 "parser.y"
                                {yyval=yyvsp[-1];}
#line 2234 "y.tab.c"
    break;

  case 84:
#line 307 "parser.y"
                                    {yyval=setTypeExpr(makeType(T_ARRAY),yyvsp[-1]);}
#line 2240 "y.tab.c"
    break;

  case 85:
#line 308 "parser.y"
                                                                {yyval=setTypeElementType(yyvsp[-3],setTypeExpr(makeType(T_ARRAY),yyvsp[-1]));}
#line 2246 "y.tab.c"
    break;

  case 86:
#line 309 "parser.y"
                                    {yyval=setTypeExpr(makeType(T_FUNC),yyvsp[-1]);}
#line 2252 "y.tab.c"
    break;

  case 87:
#line 310 "parser.y"
                                                               {yyval=setTypeElementType(yyvsp[-3],setTypeExpr(makeType(T_FUNC),yyvsp[-1]));}
#line 2258 "y.tab.c"
    break;

  case 88:
#line 315 "parser.y"
                     {yyval=makeNode(N_STMT_LIST_NIL, NIL, NIL, NIL);}
#line 2264 "y.tab.c"
    break;

  case 89:
#line 316 "parser.y"
                     {yyval=yyvsp[0];}
#line 2270 "y.tab.c"
    break;

  case 90:
#line 320 "parser.y"
                                {yyval=makeNode(N_STMT_LIST, yyvsp[0], NIL, makeNode(N_STMT_LIST_NIL,NIL,NIL,NIL));}
#line 2276 "y.tab.c"
    break;

  case 91:
#line 321 "parser.y"
                                {yyval=makeNodeList(N_STMT_LIST, yyvsp[-1], yyvsp[0]);}
#line 2282 "y.tab.c"
    break;

  case 92:
#line 325 "parser.y"
                           {yyval=yyvsp[0];}
#line 2288 "y.tab.c"
    break;

  case 93:
#line 326 "parser.y"
                           {yyval=yyvsp[0];}
#line 2294 "y.tab.c"
    break;

  case 94:
#line 327 "parser.y"
                           {yyval=yyvsp[0];}
#line 2300 "y.tab.c"
    break;

  case 95:
#line 328 "parser.y"
                           {yyval=yyvsp[0];}
#line 2306 "y.tab.c"
    break;

  case 96:
#line 329 "parser.y"
                           {yyval=yyvsp[0];}
#line 2312 "y.tab.c"
    break;

  case 97:
#line 330 "parser.y"
                           {yyval=yyvsp[0];}
#line 2318 "y.tab.c"
    break;

  case 98:
#line 335 "parser.y"
                                                   {yyval=makeNode(N_STMT_LABEL_CASE, yyvsp[-2], NIL, yyvsp[0]);}
#line 2324 "y.tab.c"
    break;

  case 99:
#line 336 "parser.y"
                                  {yyval=makeNode(N_STMT_LABEL_DEFAULT, NIL, yyvsp[0], NIL);}
#line 2330 "y.tab.c"
    break;

  case 100:
#line 341 "parser.y"
        {yyval=current_id; current_level++;}
#line 2336 "y.tab.c"
    break;

  case 101:
#line 342 "parser.y"
                           {checkForwardReference(); 
      yyval=makeNode(N_STMT_COMPOUND, yyvsp[-2], NIL, yyvsp[-1]); current_id=yyvsp[-3]; current_level--;}
#line 2343 "y.tab.c"
    break;

  case 102:
#line 352 "parser.y"
                           {yyval=makeNode(N_STMT_EMPTY, NIL,NIL,NIL);}
#line 2349 "y.tab.c"
    break;

  case 103:
#line 353 "parser.y"
                           {yyval=makeNode(N_STMT_EXPRESSION, NIL, yyvsp[-1], NIL);}
#line 2355 "y.tab.c"
    break;

  case 104:
#line 359 "parser.y"
                                                           {yyval=makeNode(N_STMT_IF, yyvsp[-2], NIL, yyvsp[0]);}
#line 2361 "y.tab.c"
    break;

  case 105:
#line 360 "parser.y"
                                                           {yyval=makeNode(N_STMT_IF_ELSE, yyvsp[-4], yyvsp[-2], yyvsp[0]);}
#line 2367 "y.tab.c"
    break;

  case 106:
#line 361 "parser.y"
                                                           {yyval=makeNode(N_STMT_SWITCH, yyvsp[-2], NIL, yyvsp[0]);}
#line 2373 "y.tab.c"
    break;

  case 107:
#line 367 "parser.y"
                                                            {yyval=makeNode(N_STMT_WHILE, yyvsp[-2], NIL, yyvsp[0]);}
#line 2379 "y.tab.c"
    break;

  case 108:
#line 368 "parser.y"
                                                            {yyval=makeNode(N_STMT_DO, yyvsp[-5], NIL, yyvsp[-2]);}
#line 2385 "y.tab.c"
    break;

  case 109:
#line 369 "parser.y"
                                                            {yyval=makeNode(N_STMT_FOR, yyvsp[-2], NIL, yyvsp[0]);}
#line 2391 "y.tab.c"
    break;

  case 110:
#line 374 "parser.y"
      {yyval=makeNode(N_FOR_EXP, yyvsp[-4], yyvsp[-2], yyvsp[0]);}
#line 2397 "y.tab.c"
    break;

  case 111:
#line 378 "parser.y"
                 {yyval=NIL;}
#line 2403 "y.tab.c"
    break;

  case 112:
#line 379 "parser.y"
                 {yyval=yyvsp[0];}
#line 2409 "y.tab.c"
    break;

  case 113:
#line 384 "parser.y"
                                          {yyval=makeNode(N_STMT_RETURN, NIL,yyvsp[-1],NIL);}
#line 2415 "y.tab.c"
    break;

  case 114:
#line 385 "parser.y"
                                          {yyval=makeNode(N_STMT_CONTINUE, NIL,NIL,NIL);}
#line 2421 "y.tab.c"
    break;

  case 115:
#line 386 "parser.y"
                                          {yyval=makeNode(N_STMT_BREAK, NIL,NIL,NIL);}
#line 2427 "y.tab.c"
    break;

  case 116:
#line 392 "parser.y"
                          {yyval=makeNode(N_ARG_LIST_NIL, NIL,NIL,NIL);}
#line 2433 "y.tab.c"
    break;

  case 117:
#line 393 "parser.y"
                          {yyval=yyvsp[0];}
#line 2439 "y.tab.c"
    break;

  case 118:
#line 397 "parser.y"
                            {yyval=makeNode(N_ARG_LIST, yyvsp[0], NIL, makeNode(N_ARG_LIST_NIL, NIL,NIL,NIL));}
#line 2445 "y.tab.c"
    break;

  case 119:
#line 398 "parser.y"
                                                      {yyval=makeNodeList(N_ARG_LIST, yyvsp[-2], yyvsp[0]);}
#line 2451 "y.tab.c"
    break;

  case 120:
#line 404 "parser.y"
                          {yyval=NIL;}
#line 2457 "y.tab.c"
    break;

  case 121:
#line 405 "parser.y"
                          {yyval=yyvsp[0];}
#line 2463 "y.tab.c"
    break;

  case 122:
#line 409 "parser.y"
                 {yyval=yyvsp[0];}
#line 2469 "y.tab.c"
    break;

  case 123:
#line 414 "parser.y"
                       {yyval=yyvsp[0];}
#line 2475 "y.tab.c"
    break;

  case 124:
#line 418 "parser.y"
                            {yyval=yyvsp[0];}
#line 2481 "y.tab.c"
    break;

  case 125:
#line 422 "parser.y"
                             {yyval=yyvsp[0];}
#line 2487 "y.tab.c"
    break;

  case 126:
#line 423 "parser.y"
                                                    {yyval=makeNode(N_EXP_ASSIGN, yyvsp[-2], NIL, yyvsp[0]);}
#line 2493 "y.tab.c"
    break;

  case 127:
#line 427 "parser.y"
                            {yyval=yyvsp[0];}
#line 2499 "y.tab.c"
    break;

  case 128:
#line 432 "parser.y"
                             {yyval=yyvsp[0];}
#line 2505 "y.tab.c"
    break;

  case 129:
#line 433 "parser.y"
                                                          {yyval=makeNode(N_EXP_OR, yyvsp[-2], NIL, yyvsp[0]);}
#line 2511 "y.tab.c"
    break;

  case 130:
#line 437 "parser.y"
                          {yyval=yyvsp[0];}
#line 2517 "y.tab.c"
    break;

  case 131:
#line 438 "parser.y"
                                                        {yyval=makeNode(N_EXP_AND, yyvsp[-2], NIL, yyvsp[0]);}
#line 2523 "y.tab.c"
    break;

  case 132:
#line 442 "parser.y"
                            {yyval=yyvsp[0];}
#line 2529 "y.tab.c"
    break;

  case 133:
#line 443 "parser.y"
                                                    {yyval=makeNode(N_EXP_EQL, yyvsp[-2], NIL, yyvsp[0]);}
#line 2535 "y.tab.c"
    break;

  case 134:
#line 444 "parser.y"
                                                    {yyval=makeNode(N_EXP_NEQ, yyvsp[-2], NIL, yyvsp[0]);}
#line 2541 "y.tab.c"
    break;

  case 135:
#line 449 "parser.y"
                       {yyval=yyvsp[0];}
#line 2547 "y.tab.c"
    break;

  case 136:
#line 450 "parser.y"
                                                 {yyval=makeNode(N_EXP_LSS, yyvsp[-2], NIL, yyvsp[0]);}
#line 2553 "y.tab.c"
    break;

  case 137:
#line 451 "parser.y"
                                                 {yyval=makeNode(N_EXP_GTR, yyvsp[-2], NIL, yyvsp[0]);}
#line 2559 "y.tab.c"
    break;

  case 138:
#line 452 "parser.y"
                                                 {yyval=makeNode(N_EXP_LEQ, yyvsp[-2], NIL, yyvsp[0]);}
#line 2565 "y.tab.c"
    break;

  case 139:
#line 453 "parser.y"
                                                 {yyval=makeNode(N_EXP_GEQ, yyvsp[-2], NIL, yyvsp[0]);}
#line 2571 "y.tab.c"
    break;

  case 140:
#line 457 "parser.y"
                          {yyval=yyvsp[0];}
#line 2577 "y.tab.c"
    break;

  case 141:
#line 463 "parser.y"
                                {yyval=yyvsp[0];}
#line 2583 "y.tab.c"
    break;

  case 142:
#line 464 "parser.y"
                                                          {yyval=makeNode(N_EXP_ADD, yyvsp[-2], NIL, yyvsp[0]);}
#line 2589 "y.tab.c"
    break;

  case 143:
#line 465 "parser.y"
                                                          {yyval=makeNode(N_EXP_SUB, yyvsp[-2], NIL, yyvsp[0]);}
#line 2595 "y.tab.c"
    break;

  case 144:
#line 469 "parser.y"
                      {yyval=yyvsp[0];}
#line 2601 "y.tab.c"
    break;

  case 145:
#line 470 "parser.y"
                                                        {yyval=makeNode(N_EXP_MUL, yyvsp[-2], NIL, yyvsp[0]);}
#line 2607 "y.tab.c"
    break;

  case 146:
#line 471 "parser.y"
                                                        {yyval=makeNode(N_EXP_DIV, yyvsp[-2], NIL, yyvsp[0]);}
#line 2613 "y.tab.c"
    break;

  case 147:
#line 472 "parser.y"
                                                        {yyval=makeNode(N_EXP_MOD, yyvsp[-2], NIL, yyvsp[0]);}
#line 2619 "y.tab.c"
    break;

  case 148:
#line 477 "parser.y"
                        {yyval=yyvsp[0];}
#line 2625 "y.tab.c"
    break;

  case 149:
#line 478 "parser.y"
                                      {yyval=makeNode(N_EXP_CAST, yyvsp[-2], NIL, yyvsp[0]);}
#line 2631 "y.tab.c"
    break;

  case 150:
#line 484 "parser.y"
                                  {yyval=yyvsp[0];}
#line 2637 "y.tab.c"
    break;

  case 151:
#line 485 "parser.y"
                                  {yyval=makeNode(N_EXP_PRE_INC, NIL, yyvsp[0], NIL);}
#line 2643 "y.tab.c"
    break;

  case 152:
#line 486 "parser.y"
                                  {yyval=makeNode(N_EXP_PRE_DEC, NIL, yyvsp[0], NIL);}
#line 2649 "y.tab.c"
    break;

  case 153:
#line 487 "parser.y"
                                  {yyval=makeNode(N_EXP_AMP, NIL, yyvsp[0], NIL);}
#line 2655 "y.tab.c"
    break;

  case 154:
#line 488 "parser.y"
                                  {yyval=makeNode(N_EXP_STAR, NIL, yyvsp[0], NIL);}
#line 2661 "y.tab.c"
    break;

  case 155:
#line 489 "parser.y"
                                  {yyval=makeNode(N_EXP_NOT, NIL, yyvsp[0], NIL);}
#line 2667 "y.tab.c"
    break;

  case 156:
#line 490 "parser.y"
                                  {yyval=makeNode(N_EXP_MINUS, NIL, yyvsp[0], NIL);}
#line 2673 "y.tab.c"
    break;

  case 157:
#line 491 "parser.y"
                                  {yyval=makeNode(N_EXP_PLUS, NIL, yyvsp[0], NIL);}
#line 2679 "y.tab.c"
    break;

  case 158:
#line 492 "parser.y"
                                  {yyval=makeNode(N_EXP_SIZE_EXP, NIL, yyvsp[0], NIL);}
#line 2685 "y.tab.c"
    break;

  case 159:
#line 493 "parser.y"
                                  {yyval=makeNode(N_EXP_SIZE_TYPE, NIL, yyvsp[-1], NIL);}
#line 2691 "y.tab.c"
    break;

  case 160:
#line 499 "parser.y"
                                           {yyval=yyvsp[0];}
#line 2697 "y.tab.c"
    break;

  case 161:
#line 500 "parser.y"
                                           {yyval=makeNode(N_EXP_ARRAY, yyvsp[-3], NIL, yyvsp[-1]);}
#line 2703 "y.tab.c"
    break;

  case 162:
#line 501 "parser.y"
                                                       {yyval=makeNode(N_EXP_FUNCTION_CALL, yyvsp[-3], NIL, yyvsp[-1]);}
#line 2709 "y.tab.c"
    break;

  case 163:
#line 502 "parser.y"
                                           {yyval=makeNode(N_EXP_STRUCT, yyvsp[-2], NIL, yyvsp[0]);}
#line 2715 "y.tab.c"
    break;

  case 164:
#line 503 "parser.y"
                                           {yyval=makeNode(N_EXP_ARROW, yyvsp[-2], NIL, yyvsp[0]);}
#line 2721 "y.tab.c"
    break;

  case 165:
#line 504 "parser.y"
                                           {yyval=makeNode(N_EXP_POST_INC, NIL, yyvsp[-1], NIL);}
#line 2727 "y.tab.c"
    break;

  case 166:
#line 505 "parser.y"
                                           {yyval=makeNode(N_EXP_POST_DEC, NIL, yyvsp[-1], NIL);}
#line 2733 "y.tab.c"
    break;

  case 167:
#line 511 "parser.y"
                          {yyval=makeNode(N_EXP_IDENT, NIL, getIdentifierDeclared(yyvsp[0]),NIL);}
#line 2739 "y.tab.c"
    break;

  case 168:
#line 512 "parser.y"
                          {yyval=makeNode(N_EXP_INT_CONST, NIL, yyvsp[0], NIL);}
#line 2745 "y.tab.c"
    break;

  case 169:
#line 513 "parser.y"
                          {yyval=makeNode(N_EXP_FLOAT_CONST, NIL, yyvsp[0], NIL);}
#line 2751 "y.tab.c"
    break;

  case 170:
#line 514 "parser.y"
                          {yyval=makeNode(N_EXP_CHAR_CONST, NIL, yyvsp[0], NIL);}
#line 2757 "y.tab.c"
    break;

  case 171:
#line 515 "parser.y"
                          {yyval=makeNode(N_EXP_STRING_LITERAL, NIL, yyvsp[0], NIL);}
#line 2763 "y.tab.c"
    break;

  case 172:
#line 516 "parser.y"
                          {yyval=yyvsp[-1];}
#line 2769 "y.tab.c"
    break;

  case 173:
#line 521 "parser.y"
                                                     {yyval=setTypeNameSpecifier(yyvsp[0],yyvsp[-1]);}
#line 2775 "y.tab.c"
    break;


#line 2779 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 525 "parser.y"


extern char *yytext;

void yyerror(const char *s) {
    syntax_err ++;
    printf("line %d : %s near %s\n",line_no, s, yytext);
}


// main 변경
// 메인 함수
void main(int argc, char *argv[])
{
	if (argc<2){
		printf("source file not given\n");
		exit(1);}
		
	if (strcmp(argv[1],"-o")==0)
		if (argc>3)
			if ((fout=fopen(argv[2],"w"))==NULL) {
				printf("can not open output file: %s\n",argv[3]);
				exit(1);}
			else ;
		else  { printf("out file not given\n");
		exit(1);}
	else if (argc==2)
		if ((fout=fopen("a.asm","w"))==NULL) {
			printf("can not open output file: a.asm\n");
			exit(1);}
			
	if ((yyin=fopen(argv[argc-1],"r"))==NULL){
		printf("can not open input file: %s\n",argv[argc-1]);
		exit(1);}
		
	printf("\nstart syntax analysis\n");
	
	initialize();
	
	yyparse();
	
	if (syntax_err) exit(1);
	
	// print_ast(root);
  
	printf("\nstart semantic analysis\n");
  
	semantic_analysis(root);
  
	if (semantic_err) exit(1);
  
	// print_sem_ast(root);

	printf("start code generation\n");
	code_generation(root);

	exit(0);

}
