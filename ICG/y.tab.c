/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "1505066.y" /* yacc.c:339  */

    #include  <iostream>
	#include <algorithm>
    #include <cstdlib>
	#include <vector>
    #include "Symboltable.h"
	#define YYSTYPE SymbolInfo*
	using namespace std;
	int yyparse(void);
	int yylex(void);
	extern FILE *yyin;
	FILE *fp,*fp2,*fp3 ;
	SymbolTable symbolTable(7) ;
	extern FILE* logout ;
	extern int newline ;
	string var(""),type_term(""),se(""),re(""),le(""),type(""),arr_var("");
	int tem=0,arr = 0,ft=0;
	
	vector<parameter> params ;
	vector<string> argms ;
	vector<string> args ;
	vector<string> procedures ;
	
	vector<SymbolInfo*> vars ;
	vector<SymbolInfo*> arrays ;
	
	int total_error = 0 ;
	extern int errors ; 

	int labelCount=0;
	int tempCount=0;


	char *newLabel()
	{
		char *lb= new char[4];
		strcpy(lb,"L");
		char b[3];
		sprintf(b,"%d", labelCount);
		labelCount++;
		strcat(lb,b);
		return lb;
	}

	char *newTemp()
	{
		char *t= new char[4];
		strcpy(t,"t");
		char b[3];
		sprintf(b,"%d", tempCount);
		tempCount++;
		strcat(t,b);
		return t;
	}

	void yyerror(char *s)
	{
		total_error++ ;
		fprintf(fp3,"Error at line %d : %s\n\n",newline,s) ;
	}

	string optimize(string code){
		string optimized_code ;
		vector<string> lines = split_string(code,'\n') ;
		for(int i=0;i<lines.size();i++){
			if(lines[i].substr(0,4)=="\tMOV" && lines[i+1].substr(0,4)=="\tMOV"){
				vector<string> r1 = split_string(lines[i].substr(5,lines[i].size()-5),',') ;
				vector<string> r2 = split_string(lines[i+1].substr(5,lines[i+1].size()-5),',') ;
				if(r1[0]==r2[1] && r2[0]==r1[1]){
					optimized_code += lines[i] + "\n" ;
					i = i+1 ;
				}
				else{
					optimized_code += lines[i] + "\n" ;
				}
			}
			else{
				optimized_code += lines[i] + "\n" ;
			}
		}
		return optimized_code ;
	}

#line 150 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    RETURN = 261,
    INT = 262,
    FLOAT = 263,
    CHAR = 264,
    DOUBLE = 265,
    FOR = 266,
    CONST_FLOAT = 267,
    CONST_INT = 268,
    CONST_CHAR = 269,
    ID = 270,
    COMMA = 271,
    SEMICOLON = 272,
    ADDOP = 273,
    ASSIGNOP = 274,
    RELOP = 275,
    LPAREN = 276,
    RPAREN = 277,
    LCURL = 278,
    RCURL = 279,
    LOGICOP = 280,
    DECOP = 281,
    INCOP = 282,
    MULOP = 283,
    BITOP = 284,
    VOID = 285,
    LTHIRD = 286,
    RTHIRD = 287,
    NOT = 288,
    PRINTLN = 289,
    LTE = 290
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define RETURN 261
#define INT 262
#define FLOAT 263
#define CHAR 264
#define DOUBLE 265
#define FOR 266
#define CONST_FLOAT 267
#define CONST_INT 268
#define CONST_CHAR 269
#define ID 270
#define COMMA 271
#define SEMICOLON 272
#define ADDOP 273
#define ASSIGNOP 274
#define RELOP 275
#define LPAREN 276
#define RPAREN 277
#define LCURL 278
#define RCURL 279
#define LOGICOP 280
#define DECOP 281
#define INCOP 282
#define MULOP 283
#define BITOP 284
#define VOID 285
#define LTHIRD 286
#define RTHIRD 287
#define NOT 288
#define PRINTLN 289
#define LTE 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 271 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   154

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  123

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    92,    92,   114,   119,   125,   129,   133,   139,   156,
     171,   171,   243,   243,   297,   302,   307,   312,   319,   319,
     333,   333,   349,   353,   357,   361,   367,   385,   400,   418,
     437,   441,   448,   452,   456,   460,   475,   481,   488,   495,
     507,   514,   520,   526,   553,   584,   588,   608,   611,   639,
     643,   683,   688,   721,   727,   774,   784,   789,   795,   811,
     873,   878,   883,   888,   893,   898,   905,   909,   912,   922
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "RETURN", "INT",
  "FLOAT", "CHAR", "DOUBLE", "FOR", "CONST_FLOAT", "CONST_INT",
  "CONST_CHAR", "ID", "COMMA", "SEMICOLON", "ADDOP", "ASSIGNOP", "RELOP",
  "LPAREN", "RPAREN", "LCURL", "RCURL", "LOGICOP", "DECOP", "INCOP",
  "MULOP", "BITOP", "VOID", "LTHIRD", "RTHIRD", "NOT", "PRINTLN", "LTE",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "parameter_list", "compound_statement",
  "$@3", "$@4", "var_declaration", "type_specifier", "declaration_list",
  "statements", "statement", "expression_statement", "variable",
  "expression", "logic_expression", "rel_expression", "simple_expression",
  "term", "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -73

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define YYTABLE_NINF -21

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      11,   -73,   -73,   -73,    17,    11,   -73,   -73,   -73,   -73,
       9,   -73,   -73,   -17,    37,    -1,    15,    19,   -73,    41,
       0,    44,    28,    30,   -73,    43,    11,    47,   -73,   -73,
      54,    50,   -73,    60,   -73,    43,    49,    97,    61,   -73,
     -73,   -73,    63,    66,   121,    69,   -73,   -73,   -73,     2,
     -73,   121,   121,   121,    70,   -73,   -73,    77,    65,   -73,
     -73,    18,    76,   -73,    71,    20,    73,   -73,   -73,   -73,
     121,   121,    80,   111,   121,   121,    29,   -73,    72,   -73,
      91,    82,   -73,   -73,   121,   -73,   -73,   -73,   121,   121,
     121,   121,    85,    94,   -73,   111,   -73,    95,   103,    89,
     -73,   100,   -73,   -73,    73,   119,   -73,    97,    97,   121,
     -73,   121,   -73,   123,   134,   -73,   124,   -73,   -73,    97,
      97,   -73,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    23,    24,    25,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    28,     0,     0,     0,     0,    22,    12,
       0,    17,     0,    26,     9,     0,     0,    10,    16,    29,
       0,    18,    13,    15,     8,     0,     0,     0,     0,    14,
      11,    27,     0,     0,     0,     0,    62,    61,    63,    43,
      41,     0,     0,     0,     0,    34,    32,     0,     0,    30,
      33,    58,     0,    45,    47,    49,    51,    53,    57,    21,
       0,     0,     0,     0,    67,     0,    58,    55,     0,    56,
       0,    28,    19,    31,     0,    65,    64,    42,     0,     0,
       0,     0,     0,     0,    40,     0,    69,     0,    66,     0,
      60,     0,    46,    48,    52,    50,    54,     0,     0,     0,
      59,     0,    44,     0,    36,    38,     0,    68,    39,     0,
       0,    37,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   136,   -73,   -73,   -73,   -73,   -73,    -5,
     -73,   -73,    52,    10,   -73,   -73,   -57,   -60,   -42,   -44,
     -72,    55,    57,    56,   -48,   -73,   -73,   -73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    35,    25,    20,    55,
      37,    38,    56,    57,    14,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    97,    98
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      72,    83,    96,    77,    15,    79,     1,     2,    78,    76,
      10,    76,   102,    95,    16,    10,    26,    11,     1,     2,
      32,    19,    27,    74,    13,    21,    92,    93,    22,     3,
      40,    99,    76,    75,    23,   109,    33,    84,    89,   117,
      90,     3,    76,   106,    85,    86,    76,    76,    76,    76,
     114,   115,     9,    17,    18,    85,    86,     9,    24,    28,
      29,    30,   121,   122,    34,   116,    31,    36,    42,    76,
      43,    44,     1,     2,   -20,    39,    45,    46,    47,    48,
      49,    41,    50,    51,    70,    69,    52,    71,    31,    82,
      73,    80,    81,    87,   100,     3,    88,    94,    53,    54,
      42,    91,    43,    44,     1,     2,   101,   107,    45,    46,
      47,    48,    49,    16,    50,    51,   108,   110,    52,   111,
      31,   112,   113,    46,    47,    48,    49,     3,    50,    51,
      53,    54,    52,    46,    47,    48,    49,    89,   119,    51,
     118,    12,    52,   103,    53,   104,   120,   105,     0,     0,
       0,     0,     0,     0,    53
};

static const yytype_int8 yycheck[] =
{
      44,    58,    74,    51,    21,    53,     7,     8,    52,    51,
       0,    53,    84,    73,    31,     5,    16,     0,     7,     8,
      25,    22,    22,    21,    15,    15,    70,    71,    13,    30,
      35,    75,    74,    31,    15,    95,    26,    19,    18,   111,
      20,    30,    84,    91,    26,    27,    88,    89,    90,    91,
     107,   108,     0,    16,    17,    26,    27,     5,    17,    15,
      32,    31,   119,   120,    17,   109,    23,    13,     3,   111,
       5,     6,     7,     8,    24,    15,    11,    12,    13,    14,
      15,    32,    17,    18,    21,    24,    21,    21,    23,    24,
      21,    21,    15,    17,    22,    30,    25,    17,    33,    34,
       3,    28,     5,     6,     7,     8,    15,    22,    11,    12,
      13,    14,    15,    31,    17,    18,    22,    22,    21,    16,
      23,    32,    22,    12,    13,    14,    15,    30,    17,    18,
      33,    34,    21,    12,    13,    14,    15,    18,     4,    18,
      17,     5,    21,    88,    33,    89,    22,    90,    -1,    -1,
      -1,    -1,    -1,    -1,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    30,    37,    38,    39,    40,    41,    48,
      49,     0,    39,    15,    50,    21,    31,    16,    17,    22,
      44,    49,    13,    15,    17,    43,    16,    22,    15,    32,
      31,    23,    45,    49,    17,    42,    13,    46,    47,    15,
      45,    32,     3,     5,     6,    11,    12,    13,    14,    15,
      17,    18,    21,    33,    34,    45,    48,    49,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    24,
      21,    21,    55,    21,    21,    31,    54,    60,    55,    60,
      21,    15,    24,    52,    19,    26,    27,    17,    25,    18,
      20,    28,    55,    55,    17,    53,    56,    62,    63,    55,
      22,    15,    56,    57,    59,    58,    60,    22,    22,    53,
      22,    16,    32,    22,    52,    52,    55,    56,    17,     4,
      22,    52,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    39,    40,    40,
      42,    41,    43,    41,    44,    44,    44,    44,    46,    45,
      47,    45,    48,    49,    49,    49,    50,    50,    50,    50,
      51,    51,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    53,    53,    54,    54,    55,    55,    56,    56,    57,
      57,    58,    58,    59,    59,    60,    60,    60,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    62,    63,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       0,     3,     3,     1,     1,     1,     3,     6,     1,     4,
       1,     2,     1,     1,     1,     7,     5,     7,     5,     5,
       3,     1,     2,     1,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     2,     2,     1,     1,     4,
       3,     1,     1,     1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 92 "1505066.y" /* yacc.c:1646  */
    {
	if(errors==0 && total_error==0){
		FILE *assembly ;
		assembly = fopen("code.asm","w") ;
		fprintf(assembly,".MODEL SMALL\n.STACK 100h\n\n.DATA\n") ;
		fprintf(assembly,"return DW ?\n") ;
		for(int i=0;i<vars.size();i++){
			fprintf(assembly,"%s DW ?\n",vars[i]->getasmName().c_str()) ;
		}

		for(int i=0;i<arrays.size();i++){
			fprintf(assembly,"%s DW %d DUP(?)\n",arrays[i]->getasmName().c_str(),arrays[i]->getLength()*2) ;
		}

		fprintf(assembly,".CODE\n") ;
		string code = optimize((yyvsp[0])->getCode()) ;
		fprintf(assembly,"%s",code.c_str()) ;
		fprintf(assembly,"\n\nDECIMAL_OUT PROC NEAR\n\n\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n\tor ax,ax\n \tjge enddif\n\tpush ax\n\tmov dl,'-'\n\tmov ah,2\n\tint 21h\n\tpop ax\n\tneg ax\nenddif:\n\txor cx,cx\n\tmov bx,10d\nrepeat:\n\txor dx,dx\n\tdiv bx\n\t push dx\n\tinc cx\n\tor ax,ax\n\tjne repeat\n\tmov ah,2\nprint_loop:\n\tpop dx\n\tor dl,30h\n\tint 21h\n\tloop print_loop\n\tpop dx\n\tpop cx\n\tpop bx\n\tpop ax\n\tmov ah,2\n\tmov dl,0Dh\n\tint 21h\n\tmov dl,0Ah\n\tint 21h\n\tret\n\nDECIMAL_OUT ENDP\n") ;
		fclose(assembly) ;
	}
}
#line 1460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 114 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[-1]);
		(yyval)->setCode((yyval)->getCode()+(yyvsp[0])->getCode()) ;
		fprintf(fp2,"At line no: %d program : program unit \n\n",newline);
		}
#line 1470 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 119 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]);
		fprintf(fp2,"At line no: %d program : unit \n\n",newline);
	}
#line 1479 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 125 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]);
		fprintf(fp2,"At line no: %d unit : var_declaration \n\n",newline);
	}
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 129 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]);
	 	fprintf(fp2,"At line no: %d unit : func_declaration \n\n",newline);
	 }
#line 1497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 133 "1505066.y" /* yacc.c:1646  */
    {
	    (yyval) = (yyvsp[0]);
	 	fprintf(fp2,"At line no: %d unit : func_definition \n\n",newline);
	 }
#line 1506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 139 "1505066.y" /* yacc.c:1646  */
    {
		parameter *p = new parameter[params.size()]; 
		for(int i=0;i<params.size();i++){
			p[i]=params[i];
		}
		func_spec specs(type,params.size(),p) ; 
		SymbolInfo *symbol = symbolTable.getSymbol((yyvsp[-4])->getName()) ; 
		if(symbol==0){
			symbolTable.insertSymbol((yyvsp[-4])->getName(),(yyvsp[-4])->getType(),"function_dec",specs);
		}
		else{
			total_error++ ; 
			fprintf(fp3,"Error at line %d: Multiple declaration \n",newline);
		} 
		params.clear();
		fprintf(fp2,"At line no: %d unit : func_definition \n\n",newline);
		}
#line 1528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 156 "1505066.y" /* yacc.c:1646  */
    {
			func_spec specs(type,0,0) ; 
			SymbolInfo *symbol = symbolTable.getSymbol((yyvsp[-3])->getName()) ; 
			if(symbol==0){
				symbolTable.insertSymbol((yyvsp[-3])->getName(),(yyvsp[-3])->getType(),"function_dec",specs);
			} 
			else{
				total_error++ ; 
				fprintf(fp3,"Error at line %d: Multiple declaration\n\n",newline);
			}
			params.clear();
			fprintf(fp2,"At line no: %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON \n",newline);
			}
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 171 "1505066.y" /* yacc.c:1646  */
    { 
				parameter *p = new parameter[params.size()]; 
				for(int i=0;i<params.size();i++) 
					p[i]=params[i] ; 
				func_spec specs((yyvsp[-4])->getName(),params.size(),p) ; 
				SymbolInfo *symbol = symbolTable.getSymbol((yyvsp[-3])->getName()) ; 
				if(symbol==0){
					symbolTable.insertSymbol((yyvsp[-3])->getName(),(yyvsp[-3])->getType(),"function",specs);
					}
				else{ 
					if(symbol->get_identifier_type()!="function")
					{
						if(symbol->get_identifier_type()=="function_dec")
						{
							int a = 1 ; 
							if(specs.get_no_of_params()!=symbol->get_func_spec().get_no_of_params()){
								a=0;
							}
							else{ 
								parameter *tem = symbol->get_func_spec().get_parameters() ; 
								for(int i=0;i<specs.get_no_of_params();i++)
								{
									if(tem[i].getParamName()!=p[i].getParamName()){
										a=0;
									}
									if(tem[i].getParamType()!=p[i].getParamType()){
										a=0;
									}
								}
							}
						if(specs.get_return_type()!=symbol->get_func_spec().get_return_type()){
							a=0;
						}
					if(a==0){
						total_error++ ; 
						fprintf(fp3,"Error at line %d: Declation and definition does not match\n",newline);
						} 
					} 
					else{
						total_error++ ; 
						fprintf(fp3,"Error at line %d: Multiple declaration\n",newline);
						}
					}
					else{ 
						total_error++ ; 
						fprintf(fp3,"Error at line %d : Function already defined\n",newline);}
						}
					}
#line 1599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 218 "1505066.y" /* yacc.c:1646  */
    {
						string code ;
						
						if((yyvsp[-5])->getName()=="main"){
							code = (yyvsp[-5])->getName() + " PROC\n"+(yyvsp[0])->getCode() ;
							(yyval)->setCode(code + "\tMOV AH,4CH\n\tINT 21H\n");
							(yyval)->setCode((yyval)->getCode() + (yyvsp[-5])->getName() + " ENDP\n\n");

							for(int i = 0 ;i<procedures.size();i++){
								(yyval)->setCode((yyval)->getCode()+procedures[i]) ;
							}

							procedures.clear() ;
							
						}
						else{
							code = (yyvsp[-5])->getName() + " PROC\n" ;
							code += "\tPUSH BP\n\tMOV BP,SP\n" ;
							code += (yyvsp[0])->getCode() ;
							code += "\tPOP BP\n\tRET 2\n" ;
							code += (yyvsp[-5])->getName() + " ENDP\n\n" ;
							procedures.push_back(code) ;
						}
						fprintf(fp2,"At line no: %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n",newline);
					}
#line 1629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 243 "1505066.y" /* yacc.c:1646  */
    {
				func_spec specs(type,0,0) ;
				SymbolInfo *symbol = symbolTable.getSymbol((yyvsp[-2])->getName()) ;
				if(symbol==0){
					symbolTable.insertSymbol((yyvsp[-2])->getName(),(yyvsp[-2])->getType(),"function",specs);
					}
				else{ 
					if(symbol->get_identifier_type()!="function")
					{
						if(symbol->get_identifier_type()=="function_dec")
						{
							int a=1;
						if(specs.get_no_of_params()!=symbol->get_func_spec().get_no_of_params()){
							a=0;
						}
						if(specs.get_return_type()!=symbol->get_func_spec().get_return_type()){
							a=0;
						}
						if(a==0){
							total_error++ ;
							fprintf(fp3,"Error at line %d: Declation and definition does not match\n",newline);
						}
					} 
					else{total_error++ ;
					fprintf(fp3,"Error at line %d: Multiple declaration\n",newline);
					}
					}
					else{fprintf(fp3,"Error at line %d : Function already defined\n",newline);} 
					} 
					params.clear();
					}
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 273 "1505066.y" /* yacc.c:1646  */
    {
						string code = (yyvsp[-4])->getName() + " PROC\n"+(yyvsp[0])->getCode() ;
						
						if((yyvsp[-4])->getName()=="main"){
							(yyval)->setCode(code + "\tMOV AH,4CH\n\tINT 21H\n");
							(yyval)->setCode((yyval)->getCode() + (yyvsp[-4])->getName() + " ENDP\n\n");

							for(int i = 0 ;i<procedures.size();i++){
								(yyval)->setCode((yyval)->getCode()+procedures[i]) ;
							}

							procedures.clear() ;
							
						}
						else{
							code += "\tRET\n" ;
							code += (yyvsp[-4])->getName() + " ENDP\n\n" ;
							procedures.push_back(code) ;
						}
						
						fprintf(fp2,"At line no: %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n",newline);
					}
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 297 "1505066.y" /* yacc.c:1646  */
    { 
		parameter p((yyvsp[0])->getName(),type,(yyvsp[0])->getName()+to_string(symbolTable.getScopeNumber()+1));
		params.push_back(p);
		fprintf(fp2,"At line no: %d parameter_list  : parameter_list COMMA type_specifier ID\n",newline); 
		}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 302 "1505066.y" /* yacc.c:1646  */
    {
		parameter p("",type);
		params.push_back(p);
		fprintf(fp2,"At line no: %d parameter_list  : parameter_list COMMA type_specifier \n",newline); 
		}
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 307 "1505066.y" /* yacc.c:1646  */
    {
		 parameter p((yyvsp[0])->getName(),type,(yyvsp[0])->getName()+to_string(symbolTable.getScopeNumber()+1));
		 params.push_back(p);
		 fprintf(fp2,"At line no: %d parameter_list  : type_specifier ID\n",newline);
		 }
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 312 "1505066.y" /* yacc.c:1646  */
    {
		parameter p("",type);
		params.push_back(p);
		fprintf(fp2,"At line no: %d parameter_list  : type_specifier \n",newline); 
		}
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 319 "1505066.y" /* yacc.c:1646  */
    { fprintf(fp2,"%s",symbolTable.enterScope().c_str()); 
			for(int i=0;i<params.size();i++){
			if(params[i].getParamName()!=""){
				vars.push_back(new SymbolInfo(params[i].getParamName(),"ID",params[i].getParamType(),params[i].getParamName()+to_string(symbolTable.getScopeNumber()))) ;
				symbolTable.insertSymbol(params[i].getParamName(),"ID",params[i].getParamType(),params[i].getParamName()+to_string(symbolTable.getScopeNumber()),(i+1)*2);
			}
			}
			params.clear();
			}
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 327 "1505066.y" /* yacc.c:1646  */
    { 
			(yyval)=(yyvsp[-1]);
			fprintf(fp2,"At line no: %d compound_statement : LCURL statements RCURL\n",newline);
			fprintf(fp2,"%s",symbolTable.printAll().c_str());
			fprintf(fp2,"%s",symbolTable.exitScope().c_str());
			}
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 333 "1505066.y" /* yacc.c:1646  */
    { fprintf(fp2,"%s",symbolTable.enterScope().c_str()); 
			 for(int i=0;i<params.size();i++){
				 if(params[i].getParamName()!=""){
					 	vars.push_back(new SymbolInfo(params[i].getParamName(),"ID",params[i].getParamType(),params[i].getParamName()+to_string(symbolTable.getScopeNumber())));
					 	symbolTable.insertSymbol(params[i].getParamName(),"ID",params[i].getParamType(),params[i].getParamName()+to_string(symbolTable.getScopeNumber()),(i+1)*2);
					}
				}
				params.clear(); 
				}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 341 "1505066.y" /* yacc.c:1646  */
    {
				fprintf(fp2,"At line no: %d compound_statement : LCURL RCURL\n",newline);
				fprintf(fp2,"%s",symbolTable.printAll().c_str());
				fprintf(fp2,"%s",symbolTable.exitScope().c_str());
				}
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 349 "1505066.y" /* yacc.c:1646  */
    {
		fprintf(fp2,"At line no: %d var_declaration : type_specifier declaration_list SEMICOLON \n",newline);}
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 353 "1505066.y" /* yacc.c:1646  */
    {SymbolInfo *symbol = new SymbolInfo("int","keyword");  
		type="int"; 
		(yyval) = symbol ;
		fprintf(fp2,"At line no: %d type_specifier : INT \n",newline);}
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 357 "1505066.y" /* yacc.c:1646  */
    {SymbolInfo *symbol = new SymbolInfo("float","keyword"); 
		 type="float"; 
		 (yyval) = symbol ; 
		 fprintf(fp2,"At line no: %d type_specifier : FLOAT \n",newline);}
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 361 "1505066.y" /* yacc.c:1646  */
    {SymbolInfo *symbol = new SymbolInfo("void","keyword"); 
		 type="void";
		 (yyval) = symbol ; 
		 fprintf(fp2,"At line no: %d type_specifier : VOID \n",newline);}
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 367 "1505066.y" /* yacc.c:1646  */
    {
			if(!symbolTable.searchSymbol((yyvsp[0])->getName()))
			{
				if(type!="void"){
					vars.push_back(new SymbolInfo((yyvsp[0])->getName(),(yyvsp[0])->getType(),type,(yyvsp[0])->getName()+to_string(symbolTable.getScopeNumber())));
					symbolTable.insertSymbol((yyvsp[0])->getName(),(yyvsp[0])->getType(),type,(yyvsp[0])->getName()+to_string(symbolTable.getScopeNumber())) ;
				}
			else{
				total_error++ ;
				fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
				}
			}
			else{
				total_error++ ;
				fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,(yyvsp[0])->getName().c_str());
			} 
			fprintf(fp2,"At line no: %d declaration_list : declaration_list COMMA ID\n",newline);
			}
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 385 "1505066.y" /* yacc.c:1646  */
    { 
		   if(!symbolTable.searchSymbol((yyvsp[-3])->getName())){
			   if(type!="void"){
				   arrays.push_back(new SymbolInfo((yyvsp[-3])->getName(),(yyvsp[-3])->getType(),type,stoi((yyvsp[-1])->getName().c_str()),(yyvsp[-3])->getName()+to_string(symbolTable.getScopeNumber())));
				   symbolTable.insertSymbol((yyvsp[-3])->getName(),(yyvsp[-3])->getType(),type,stoi((yyvsp[-1])->getName().c_str()),(yyvsp[-3])->getName()+to_string(symbolTable.getScopeNumber()));
				}
			   else{
				   total_error++ ;
				   fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
				}
			   }else{
				   total_error++ ;
				   fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,(yyvsp[-3])->getName().c_str());
				} 
			   fprintf(fp2,"At line no: %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n",newline);}
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 400 "1505066.y" /* yacc.c:1646  */
    {
				if(!symbolTable.searchSymbol((yyval)->getName()))
				{
					if(type!="void"){
						vars.push_back(new SymbolInfo((yyval)->getName(),(yyval)->getType(),type,(yyval)->getName()+to_string(symbolTable.getScopeNumber())));
						symbolTable.insertSymbol((yyval)->getName(),(yyval)->getType(),type,(yyval)->getName()+to_string(symbolTable.getScopeNumber())) ;
					}
					else{
						total_error++ ;
						fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
						}
					}
				else{
					total_error++ ;
					fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,(yyval)->getName().c_str());
					} 
					fprintf(fp2,"At line no: %d declaration_list : ID\n",newline);
				}
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 418 "1505066.y" /* yacc.c:1646  */
    { 
		   		if(!symbolTable.searchSymbol((yyval)->getName())){

			   		if(type!="void"){
						arrays.push_back(new SymbolInfo((yyval)->getName(),(yyval)->getType(),type,stoi((yyvsp[-1])->getName().c_str()),(yyval)->getName()+to_string(symbolTable.getScopeNumber()))) ;
						symbolTable.insertSymbol((yyval)->getName(),(yyval)->getType(),type,stoi((yyvsp[-1])->getName().c_str()),(yyval)->getName()+to_string(symbolTable.getScopeNumber()));
					}
					else{
						total_error++ ;
						fprintf(fp3,"Error at line %d : void type declared of a variable\n",newline);
					}
				}
				else{
					total_error++ ;
					fprintf(fp3,"Error at line %d : Multiple declaration of %s\n",newline,(yyval)->getName().c_str());
				} 
				fprintf(fp2,"At line no: %d declaration_list : LTHIRD CONST_INT RTHIRD\n",newline);}
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 437 "1505066.y" /* yacc.c:1646  */
    {
			fprintf(fp2,"At line no: %d statements : statement\n",newline);
			(yyval) = (yyvsp[0]) ;
		}
#line 1912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 441 "1505066.y" /* yacc.c:1646  */
    {
		    (yyval) = (yyvsp[-1]) ;
			(yyval)->setCode((yyval)->getCode()+(yyvsp[0])->getCode()) ;
	   		fprintf(fp2,"At line no: %d statements : statements statement\n",newline);
	   }
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 448 "1505066.y" /* yacc.c:1646  */
    {
			(yyval) = (yyvsp[0]) ;
			fprintf(fp2,"At line no: %d statement : var_declaration\n",newline);
		}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 452 "1505066.y" /* yacc.c:1646  */
    {
		  	(yyval) = (yyvsp[0]) ;
	  		fprintf(fp2,"At line no: %d statement : expression_statement\n",newline);
	  }
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 456 "1505066.y" /* yacc.c:1646  */
    {
		    (yyval) = (yyvsp[0]) ;
	  		fprintf(fp2,"At line no: %d statement : compound_statement\n",newline);
	  }
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 460 "1505066.y" /* yacc.c:1646  */
    {
		  	(yyval) = (yyvsp[-4]) ;
			char *label1 = newLabel();
			char *label2 = newLabel();
			(yyval)->setCode((yyval)->getCode() + string(label1) + ":\n");
			(yyval)->setCode((yyval)->getCode() + (yyvsp[-3])->getCode() + "\n");
			(yyval)->setCode((yyval)->getCode() + "\tMOV AX,"+(yyvsp[-3])->getName()+"\n");
			(yyval)->setCode((yyval)->getCode() + "\tCMP AX , 0\n");
			(yyval)->setCode((yyval)->getCode() + "\tJE "+string(label2)+"\n");
			(yyval)->setCode((yyval)->getCode() + (yyvsp[0])->getCode());
			(yyval)->setCode((yyval)->getCode() + (yyvsp[-2])->getCode());
			(yyval)->setCode((yyval)->getCode() + "\tJMP "+string(label1)+"\n");
			(yyval)->setCode((yyval)->getCode() + string(label2)+":\n");		
			fprintf(fp2,"At line no: %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n",newline);
		}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 475 "1505066.y" /* yacc.c:1646  */
    {
	  		(yyval) = (yyvsp[-2]) ;
			char *label=newLabel();
			(yyval)->setCode((yyval)->getCode() + "\tMOV AX,"+(yyvsp[-2])->getName()+"\n\tCMP AX, 0\n\tJE "+string(label)+"\n"+(yyvsp[0])->getCode()+string(label)+":\n");
			fprintf(fp2,"At line no: %d statement : IF LPAREN expression RPAREN statement \n",newline);
	  }
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 481 "1505066.y" /* yacc.c:1646  */
    { 
		    (yyval) = (yyvsp[-4]) ;
		  	char *label1=newLabel();
			char *label2=newLabel();
			(yyval)->setCode((yyval)->getCode() + "\tMOV AX,"+(yyvsp[-4])->getName()+"\n\tCMP AX,0\n\tJE "+string(label1)+"\n"+(yyvsp[-2])->getCode() +"\tJMP "+string(label2)+"\n" + string(label1)+":\n"+(yyvsp[0])->getCode()+string(label2)+":\n");
	  		fprintf(fp2,"At line no: %d statement : IF LPAREN expression RPAREN statement ELSE statement\n",newline);
	  }
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 488 "1505066.y" /* yacc.c:1646  */
    {
		    (yyval) = (yyvsp[-2]) ;
			char * label1 = newLabel();
			char * label2 = newLabel();
			(yyval)->setCode((yyval)->getCode() + string(label1) + ":\n" +(yyvsp[-2])->getCode() + "\tMOV AX,"+(yyvsp[-2])->getName()+"\n" + "\tCMP ax , 0\n" + "\tJE "+string(label2)+"\n" + (yyvsp[0])->getCode() + "\tJMP "+string(label1)+"\n" + string(label2)+":\n");
	  		fprintf(fp2,"At line no: %d statement : WHILE LPAREN expression RPAREN statement statement\n",newline);
		}
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 495 "1505066.y" /* yacc.c:1646  */
    {
		  	SymbolInfo *temp = symbolTable.getSymbol((yyvsp[-2])->getName()) ;
			if(temp!=0){
				(yyval) = new SymbolInfo("println","PRINTFUNC") ;
		   		(yyval)->setCode("\tMOV AX," + symbolTable.getSymbol((yyvsp[-2])->getName())->getasmName() + "\n\tcall DECIMAL_OUT\n") ;
		  		fprintf(fp2,"At line no: %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n",newline);
			}
			else{
				total_error++ ;
		  		fprintf(fp3,"Error at line no %d : variable is not declared in the scope\n",newline);
			}    
		}
#line 2021 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 507 "1505066.y" /* yacc.c:1646  */
    {
		    (yyval) = (yyvsp[-1]) ;
		  	(yyval)->setCode((yyval)->getCode()+ "\tMOV AX," + (yyvsp[-1])->getName() + "\n\tMOV return,AX\n") ;
	  		fprintf(fp2,"At line no: %d statement : RETURN expression SEMICOLON\n",newline);
		}
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 514 "1505066.y" /* yacc.c:1646  */
    {
			SymbolInfo* symbol = new SymbolInfo(";","SEMICOLON") ;
			(yyval) = symbol ;
			(yyval)->setCode("") ;
			fprintf(fp2,"At line no: %d expression_statement : SEMICOLON\n",newline);
			}
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 520 "1505066.y" /* yacc.c:1646  */
    {
			(yyval) = (yyvsp[-1]) ;
			fprintf(fp2,"At line no: %d expression_statement : expression SEMICOLON\n",newline);
			}
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 526 "1505066.y" /* yacc.c:1646  */
    {
	 var=(yyvsp[0])->getName(); 
	 SymbolInfo *symbol ; 
	 symbol = symbolTable.getSymbol(var);
	 if(symbol!=0){
		 type = symbol->get_data_type(); 
	 	 if(symbol->get_identifier_type()=="array"){
			total_error++ ;
			fprintf(fp3,"Error at line %d : array-type variable declared but index not found\n",newline);
			type="";
		}
		(yyval)->setLength(-1) ;
		if(symbol->getPara()>0){
			(yyval)->setName("[BP + "+ to_string(2+symbol->getPara())+"]") ; 
		}
		else{
			(yyval)->setName(symbol->getasmName()) ; 
		}
		(yyval)->set_data_type(type);

		} 
		else{
			total_error++ ;
			fprintf(fp3,"Error at line %d : %s is not declared in the Scope\n",newline,(yyvsp[0])->getName().c_str());
		} 
		fprintf(fp2,"At line no: %d variable : ID\n",newline,var.c_str());
		}
#line 2083 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 553 "1505066.y" /* yacc.c:1646  */
    {
	 	arr_var = (yyvsp[-3])->getName() ; 
		if((yyvsp[-1])->get_data_type()!="int"){
			total_error++ ;
			fprintf(fp3,"Error at line %d : Array index is non-integer type\n",newline);
		} 
		SymbolInfo *symbol ; 
		symbol = symbolTable.getSymbol(arr_var); 
		if(symbol!=0){
			(yyval)->setName(symbol->getasmName()) ;
			(yyval)->setLength(symbol->getLength()) ;
			(yyvsp[-3])->setLength(symbol->getLength()) ;
			
			type = symbol->get_data_type(); 
			(yyval)->set_data_type(type);
			(yyval)->setCode((yyvsp[-1])->getCode()) ;
			(yyval)->setCode((yyval)->getCode() + "\tMOV BX," +(yyvsp[-1])->getName() +"\n" + "\tSHL BX, 1\n") ;
			
			delete (yyvsp[-1]);
			if(symbol->get_identifier_type()!="array"){
			 	total_error++ ;
			 	fprintf(fp3,"Error at line %d : index used but used variable is not an array\n",newline);}
			} 
			else{
				total_error++ ;
				fprintf(fp3,"Error at line %d : %s is not declared in the Scope\n",newline);
			}
			fprintf(fp2,"At line no: %d variable : ID LTHIRD expression RTHIRD\n",newline,var.c_str()); 
		}
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 584 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]) ;
		fprintf(fp2,"At line no: %d expression : logic_expression\n",newline);
		}
#line 2126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 588 "1505066.y" /* yacc.c:1646  */
    { 
	   		type = (yyvsp[-2])->get_data_type() ; 
			if(type!=(yyvsp[0])->get_data_type() && (type!="" && (yyvsp[0])->get_data_type()!="") ){
				total_error++ ;
				fprintf(fp3,"Error at line %d : Type Mismatch\n",newline);
			}  
			fprintf(fp2,"At line no: %d expression : variable ASSIGNOP logic_expression\n",newline);
			(yyval) = (yyvsp[-2]) ;
			(yyval)->setCode((yyvsp[0])->getCode()+(yyvsp[-2])->getCode() + "\tMOV AX,"+(yyvsp[0])->getName()+"\n") ;
			if((yyvsp[-2])->getLength()>=0){
				(yyval)->setCode((yyval)->getCode() + "\tMOV " + (yyvsp[-2])->getName() + "[BX],AX\n" ) ;
			}
			else{
				(yyval)->setCode((yyval)->getCode() + "\tMOV " + (yyvsp[-2])->getName() + ",AX\n" ) ;
			}

			delete (yyvsp[0]) ;
	   }
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 608 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]) ;
		fprintf(fp2,"At line no: %d logic_expression : rel_expression\n",newline);}
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 611 "1505066.y" /* yacc.c:1646  */
    {
		 (yyval) = (yyvsp[-2]) ;
		 char *temp = newTemp() ;
		 char *label1=newLabel();
		 char *label2=newLabel();
		 
		 if((yyvsp[-1])->getName()=="&&"){
			(yyval)->setCode((yyval)->getCode() + "\tMOV AX," + (yyvsp[-2])->getName() +"\n\tCMP AX , 0\n\tJE " + string(label1) +"\n\tMOV AX," + (yyvsp[0])->getName() +"\n\tCMP AX , 0\n\tJE " + string(label1) +"\n\tMOV " + string(temp) + " , 1\n");
			(yyval)->setCode((yyval)->getCode() + "\tJMP " + string(label2) + "\n" + string(label1) + ":\n" + "\tMOV " + string(temp) + ", 0\n" + string(label2) + ":\n") ;
			(yyval)->setName(temp);
			(yyval)->setasmName(string(temp));
			vars.push_back((yyval)) ;
		 }

		 if((yyvsp[-1])->getName()=="||"){
			(yyval)->setCode((yyval)->getCode() + "\tMOV AX," + (yyvsp[-2])->getName() +"\n\tCMP AX , 1\n\tJE " + string(label1) +"\n\tMOV AX," + (yyvsp[0])->getName() +"\n\tCMP AX , 1\n\tJE " + string(label1) +"\n\tMOV " + string(temp) + " , 0\n");
			(yyval)->setCode((yyval)->getCode() + "\tJMP " + string(label2) + "\n" + string(label1) + ":\n" + "\tMOV " + string(temp) + ", 1\n" + string(label2) + ":\n") ;
			(yyval)->setName(temp);
			(yyval)->setasmName(string(temp)) ;
			vars.push_back((yyval)) ;
		 }

		 (yyval)->set_data_type("int");
		 fprintf(fp2,"At line no: %d logic_expression : rel_expression LOGICOP rel_expression\n",newline);
		 delete (yyvsp[0]) ;
		 }
#line 2188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 639 "1505066.y" /* yacc.c:1646  */
    {
			(yyval) = (yyvsp[0]) ;
			fprintf(fp2,"At line no: %d rel_expression : simple_expression\n",newline);
		}
#line 2197 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 643 "1505066.y" /* yacc.c:1646  */
    {
			(yyval) = (yyvsp[-2]) ;
			char *temp=newTemp();
			char *label1=newLabel();
			char *label2=newLabel();
			
			(yyval)->setCode((yyval)->getCode() + (yyvsp[0])->getCode()) ;
			(yyval)->setCode((yyval)->getCode() + "\tMOV AX," + (yyvsp[-2])->getName()+"\n" + "\tCMP AX, " + (yyvsp[0])->getName()+"\n") ;
			if((yyvsp[-1])->getName()=="<"){
					(yyval)->setCode((yyval)->getCode() +"\tJL " + string(label1)+"\n");
			}
			else if((yyvsp[-1])->getName()=="<="){
				(yyval)->setCode((yyval)->getCode() +"\tJLE " + string(label1)+"\n");
			}
			else if((yyvsp[-1])->getName()==">"){
				(yyval)->setCode((yyval)->getCode() +"\tJG " + string(label1)+"\n");
			}
			else if((yyvsp[-1])->getName()==">="){
				(yyval)->setCode((yyval)->getCode() +"\tJGE " + string(label1)+"\n");
			}
			else if((yyvsp[-1])->getName()=="=="){
				(yyval)->setCode((yyval)->getCode() +"\tJE " + string(label1)+"\n");
			}
			else{
				(yyval)->setCode((yyval)->getCode() +"\tJNE " + string(label1)+"\n");
			}
				
			(yyval)->setCode((yyval)->getCode() + "\tMOV "+string(temp) +", 0\n" +"\tJMP "+string(label2) +"\n" + string(label1)+":\n\tMOV "+string(temp)+", 1\n" + string(label2)+":\n");
			(yyval)->set_data_type("int") ;
			(yyval)->setName(string(temp)) ;

			SymbolInfo* symbol = new SymbolInfo(string(temp),"ID") ;
			symbol->setasmName(symbol->getName()) ;
		  	vars.push_back(symbol) ;
			
			fprintf(fp2,"At line no: %d simple_expression RELOP simple_expression\n",newline);
			delete (yyvsp[0]) ;
		}
#line 2240 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 683 "1505066.y" /* yacc.c:1646  */
    {
		  (yyval) = (yyvsp[0]) ;
		  (yyval)->set_data_type(type_term);
		  fprintf(fp2,"At line no: %d simple_expression : term \n",newline,se.c_str());
		  }
#line 2250 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 688 "1505066.y" /* yacc.c:1646  */
    {
		  (yyval) = (yyvsp[-2]) ;	  
		  if(((yyval)->get_data_type()=="float" && type_term=="int")|((yyval)->get_data_type()=="int" && type_term=="float")|((yyval)->get_data_type()=="float" && type_term=="float"))
		  {
			  (yyval)->set_data_type("float");
		  }
		  else if((yyval)->get_data_type()=="int" && type_term=="int"){
			  (yyval)->set_data_type("int");
		  }
		  else (yyval)->set_data_type("") ;
		  fprintf(fp2,"At line no: %d simple_expression : simple_expression ADDOP term\n",newline);

		  (yyval)->setCode((yyval)->getCode()+(yyvsp[0])->getCode() + "\tMOV AX,"+ (yyvsp[-2])->getName()+"\n" + "\tMOV BX,"+ (yyvsp[0])->getName() +"\n") ;
		  char *temp = newTemp() ;//does it needs to be added to the vars array????
		  
		  if((yyvsp[-1])->getName()=="+"){
			  (yyval)->setCode((yyval)->getCode() + "\tADD AX,BX\n" + +"\tMOV "+ string(temp) + ",AX\n") ;  
		  }

		  if((yyvsp[-1])->getName()=="-"){
			  (yyval)->setCode((yyval)->getCode() + "\tSUB AX,BX\n" + +"\tMOV "+ string(temp) + ", AX\n") ;  
		  }	

		  (yyval)->setName(string(temp)) ; 
		  
		  SymbolInfo* symbol = new SymbolInfo(string(temp),"ID") ;
		  symbol->setasmName(symbol->getName()) ;
		  vars.push_back(symbol) ;

		  delete (yyvsp[0]) ;
		  }
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 721 "1505066.y" /* yacc.c:1646  */
    {
			(yyval) = (yyvsp[0]) ;
			type_term = type ;
			(yyval)->set_data_type(type_term) ;
			fprintf(fp2,"At line no: %d term : unary_expression\n",newline);
		}
#line 2297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 727 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[-2]) ; 
		type_term = (yyvsp[-2])->get_data_type() ; 
	 	if((type_term=="float" && type=="int")|(type_term=="int" && type=="float") | (type_term=="float" && type=="float"))
	 	{
			 type_term = "float"; 
	 	if((yyvsp[-1])->getName()=="%")
	 	{
			 type_term = "int" ; 
			 total_error++ ;
			 fprintf(fp3,"Error at line %d : Operands of % Operators are not Integers\n",newline);}
	 	} 
	 	else if((type_term=="int" && type=="int")) {
			 type_term = "int"; 
	 	}
		else {
			type_term= "" ; 
	 		if((yyvsp[-1])->getName()=="%"){
				 type_term="int"; 
				 total_error++ ;
				 fprintf(fp3,"Error at line %d : Operands of % Operators are not Integers\n",newline);
				 }
		}
		(yyval)->set_data_type(type_term) ;
		(yyval)->setCode((yyval)->getCode()+(yyvsp[0])->getCode() + "\tMOV AX,"+ (yyvsp[-2])->getName()+"\n" + "\tMOV BX,"+ (yyvsp[0])->getName() +"\n") ;
		char *temp = newTemp() ;
		if((yyvsp[-1])->getName()=="*"){
			//without using temp
			(yyval)->setCode((yyval)->getCode()+"\tMUL BX\n"+"\tMOV "+ string(temp) + ",AX\n") ;
		}
		else if((yyvsp[-1])->getName()=="/"){
			(yyval)->setCode((yyval)->getCode()+"\tMOV DX , 0\n\tDIV BX\n"+"\tMOV "+ string(temp) + ",AX\n") ;
		}

		else{
			(yyval)->setCode((yyval)->getCode()+"\tMOV DX , 0\n\tDIV BX\n"+"\tMOV "+ string(temp) + ",DX\n") ;
		}
		(yyval)->setName(string(temp)) ; 
		
		SymbolInfo* symbol = new SymbolInfo(string(temp),"ID") ;
		symbol->setasmName(symbol->getName()) ;
		vars.push_back(symbol) ;
		/// printf("%s",$$->getCode().c_str()) ; //check ICG generation
		delete (yyvsp[0]);
	 	fprintf(fp2,"At line no: %d term : term MULOP unary_expression\n",newline);}
#line 2347 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 774 "1505066.y" /* yacc.c:1646  */
    {
			 if((yyvsp[-1])->getName()=="+"){
				(yyval) = (yyvsp[0]) ;
			 }
			 else if((yyvsp[-1])->getName()=="-"){
				 (yyval) = (yyvsp[0]);
				 (yyval)->setCode((yyval)->getCode() + "\tMOV AX," + (yyvsp[0])->getName() + "\n" + "\tNEG AX\n" + "\tMOV " + (yyvsp[0])->getName() + " ,AX\n");
			 }
			 fprintf(fp2,"At line no: %d unary_expression : ADDOP factor\n",newline);
		 }
#line 2362 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 784 "1505066.y" /* yacc.c:1646  */
    {
			 (yyval) = (yyvsp[0]) ;
			 (yyval)->setCode((yyval)->getCode()+"\tMOV AX," + (yyvsp[0])->getName() + "\n" + "\tNOT AX\n" + "\tMOV "+(yyvsp[0])->getName()+",AX") ;
			 fprintf(fp2,"At line no: %d unary_expression :NOT factor\n",newline); 
			 }
#line 2372 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 789 "1505066.y" /* yacc.c:1646  */
    {
			 (yyval) = (yyvsp[0]) ;
			 fprintf(fp2,"At line no: %d unary_expression : factor\n",newline);
		}
#line 2381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 795 "1505066.y" /* yacc.c:1646  */
    {
			fprintf(fp2,"At line no: %d factor : variable\n",newline);
			if((yyvsp[0])->getLength()>=0){
				char *temp = newTemp() ;
				(yyval)->setCode((yyvsp[0])->getCode() + "\tMOV AX," + (yyvsp[0])->getName() + "[BX]\n" + "\tMOV " + string(temp) + ",AX\n") ;
				(yyval)->setName(string(temp)) ; 

				SymbolInfo* symbol = new SymbolInfo(string(temp),"ID") ;
				symbol->setasmName(symbol->getName()) ;
		  		vars.push_back(symbol) ;
			}
			else{
				(yyval) = (yyvsp[0]) ;
			}
			
		}
#line 2402 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 811 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[-1]) ;
		SymbolInfo *symbol = symbolTable.getSymbol((yyvsp[-3])->getName()) ;
		string code ; 
		if(symbol!=0){
			type=symbol->get_data_type() ; 
			if(symbol->get_identifier_type()=="function" || symbol->get_identifier_type()=="function_dec")
			{ 
				func_spec specs = symbol->get_func_spec() ; 
					if(argms.size()==specs.get_no_of_params()){ 
						parameter *p = specs.get_parameters() ; 
						int ap = 0 ; 
						for(int i=0;i<argms.size();i++){
							if(argms[i]!=p[i].getParamType())
							{
								ap=1;
								break;
							}
							if(p[i].getParamName()!=""){
								code += "\tMOV AX," + args[i] + "\n";
								code += "\tPUSH AX\n" ; 
							}
							else{
								// cause it does nothing :-) 
							}
						}


					if(ap==1){
						total_error++ ;
						fprintf(fp3,"Error at line %d : Function arguments type  does not match\n", newline);
					}
				}


				else{
					total_error++ ;
					fprintf(fp3,"Error at line %d : Function argument numbers does not match\n", newline);
				}  
			} 
			else {
				total_error++ ;
				fprintf(fp3,"Error at line %d : %s is not a function\n",newline, (yyval)->getName().c_str());
			}
		} 
		else{
			type="" ;
			total_error++ ;
			fprintf(fp3,"Error at line %d : %s not declared in the scope\n",newline);
		}  
		fprintf(fp2,"At line no: %d factor : variable\n",newline);
		char *temp = newTemp() ;
		code += "\tCALL " + (yyvsp[-3])->getName() + "\n" ;
		code += "\tMOV AX, return\n\tMOV " + string(temp) + ",AX\n" ; 
		(yyval)->setName(string(temp)) ;
		SymbolInfo* t = new SymbolInfo(string(temp),"ID") ;
		t->setasmName(string(temp)) ;
		vars.push_back(t) ;
		(yyval)->setCode((yyvsp[-1])->getCode() + code) ;
		argms.clear();
		args.clear() ;
		}
#line 2469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 873 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[-1]);
		type = (yyvsp[-1])->get_data_type() ;
		fprintf(fp2,"At line no: %d factor : LPAREN expression RPAREN\n",newline);
		}
#line 2479 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 878 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]);
		type = "int" ;
		fprintf(fp2,"At line no: %d factor : CONST_INT\n",newline);
		}
#line 2489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 883 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]);
		type = "float" ;
		fprintf(fp2,"At line no: %d factor : CONST_FLOAT\n",newline);
		}
#line 2499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 888 "1505066.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]);
		type = "char" ;
		fprintf(fp2,"At line no: %d factor : CONST_CHAR\n",newline);
		}
#line 2509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 893 "1505066.y" /* yacc.c:1646  */
    {
		fprintf(fp2,"At line no: %d factor : variable INCOP\n",newline);
		(yyval) = (yyvsp[-1]);
		(yyval)->setCode((yyval)->getCode()+"\tMOV AX ," + (yyval)->getName()+ "\n" + "\tADD AX , 1\n" + "\tMOV " + (yyval)->getName() + " ,AX\n") ;
		}
#line 2519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 898 "1505066.y" /* yacc.c:1646  */
    {
		fprintf(fp2,"At line no: %d factor : variable DECOP\n",newline);
		(yyval) = (yyvsp[-1]);
		(yyval)->setCode((yyval)->getCode()+"\tMOV AX ," + (yyval)->getName()+ "\n" + "\tSUB AX , 1\n" + "\tMOV " + (yyval)->getName() + " ,AX\n") ;
	}
#line 2529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 905 "1505066.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]) ;
					fprintf(fp2,"At line no: %d argument_list : arguments\n",newline);
				}
#line 2538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 909 "1505066.y" /* yacc.c:1646  */
    {(yyval) = new SymbolInfo();}
#line 2544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 912 "1505066.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-2]) ;
				(yyval)->setCode((yyval)->getCode() + (yyvsp[0])->getCode()) ;
			  	args.push_back((yyvsp[0])->getName()) ;
				le= (yyvsp[0])->get_data_type()  ; 
				argms.push_back(le) ; 
				fprintf(fp2,"At line no: %d arguments : arguments COMMA logic_expression\n",newline);

				delete (yyvsp[0]) ;
			}
#line 2559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 922 "1505066.y" /* yacc.c:1646  */
    {
			  (yyval) = (yyvsp[0]) ;
			  args.push_back((yyval)->getName()) ;
			  le=(yyval)->get_data_type() ;
		   	  argms.push_back(le) ; 
		   	  fprintf(fp2,"At line no: %d arguments : logic_expression\n",newline);
		   }
#line 2571 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2575 "y.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 931 "1505066.y" /* yacc.c:1906  */

int main(int argc,char *argv[])
{
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n\n");
		exit(1);
	}

	fp2= fopen(argv[2],"w");
	fclose(fp2);
	fp2= fopen(argv[2],"a");

	fp3= fopen(argv[3],"w");
	fclose(fp3);
	fp3= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	symbolTable.printAll();
	fclose(fp) ;
	fprintf(fp2,"%s",symbolTable.printAll().c_str());
	fclose(fp2);
	fprintf(fp3,"Total Error : %d",total_error);
	fclose(fp3);
	fclose(logout) ;
	return 0;
}
