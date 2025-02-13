/* A Bison parser, made by GNU Bison 3.7.5.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 8 "compilador.y"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "tabela_simbolos.c"
#include "pilha_rotulos.c"
#include "pilha_tipos.c"
#include "pilha_operacoes.c"

Token_Stack *s;
Label_Stack *l;
Type_Stack *types;

int n_types;

char *temp_type;

Op_Stack *op_relacao;
Op_Stack *op_expressao;
Op_Stack *op_fatores;

int num_vars;
int num_vars_global;
char *l_elem;

int n_lexico;
int deslocamento;

int pf_counter;

int op_termo;
int op_fator;
int op_bool;

int n_rotulos;

int is_ref;

int func_call;
char *func_call_ident;
char *temp_ident;
int proc_call;
char *proc_call_ident;
int param_index;

int n_procedimentos;

int tipo_fator;

int imprimeErro ( char* erro );


#line 126 "compilador.tab.c"

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

#include "compilador.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_ABRE_PARENTESES = 4,            /* ABRE_PARENTESES  */
  YYSYMBOL_FECHA_PARENTESES = 5,           /* FECHA_PARENTESES  */
  YYSYMBOL_VIRGULA = 6,                    /* VIRGULA  */
  YYSYMBOL_PONTO_E_VIRGULA = 7,            /* PONTO_E_VIRGULA  */
  YYSYMBOL_DOIS_PONTOS = 8,                /* DOIS_PONTOS  */
  YYSYMBOL_PONTO = 9,                      /* PONTO  */
  YYSYMBOL_T_BEGIN = 10,                   /* T_BEGIN  */
  YYSYMBOL_T_END = 11,                     /* T_END  */
  YYSYMBOL_VAR = 12,                       /* VAR  */
  YYSYMBOL_IDENT = 13,                     /* IDENT  */
  YYSYMBOL_ATRIBUICAO = 14,                /* ATRIBUICAO  */
  YYSYMBOL_NUMERO = 15,                    /* NUMERO  */
  YYSYMBOL_CMP_IGUAL = 16,                 /* CMP_IGUAL  */
  YYSYMBOL_CMP_DIFF = 17,                  /* CMP_DIFF  */
  YYSYMBOL_CMP_MENOR = 18,                 /* CMP_MENOR  */
  YYSYMBOL_CMP_MENOR_IGUAL = 19,           /* CMP_MENOR_IGUAL  */
  YYSYMBOL_CMP_MAIOR_IGUAL = 20,           /* CMP_MAIOR_IGUAL  */
  YYSYMBOL_CMP_MAIOR = 21,                 /* CMP_MAIOR  */
  YYSYMBOL_MAIS = 22,                      /* MAIS  */
  YYSYMBOL_MENOS = 23,                     /* MENOS  */
  YYSYMBOL_OR = 24,                        /* OR  */
  YYSYMBOL_MULT = 25,                      /* MULT  */
  YYSYMBOL_DIV = 26,                       /* DIV  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_DO = 30,                        /* DO  */
  YYSYMBOL_IF = 31,                        /* IF  */
  YYSYMBOL_THEN = 32,                      /* THEN  */
  YYSYMBOL_ELSE = 33,                      /* ELSE  */
  YYSYMBOL_PROCEDURE = 34,                 /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 35,                  /* FUNCTION  */
  YYSYMBOL_READ = 36,                      /* READ  */
  YYSYMBOL_WRITE = 37,                     /* WRITE  */
  YYSYMBOL_TYPE = 38,                      /* TYPE  */
  YYSYMBOL_LOWER_THAN_ELSE = 39,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_programa = 41,                  /* programa  */
  YYSYMBOL_42_1 = 42,                      /* $@1  */
  YYSYMBOL_bloco = 43,                     /* bloco  */
  YYSYMBOL_44_2 = 44,                      /* $@2  */
  YYSYMBOL_parte_declara_tipos = 45,       /* parte_declara_tipos  */
  YYSYMBOL_definicao_tipo = 46,            /* definicao_tipo  */
  YYSYMBOL_47_3 = 47,                      /* $@3  */
  YYSYMBOL_parte_declara_vars = 48,        /* parte_declara_vars  */
  YYSYMBOL_parte_declara_subrotinas = 49,  /* parte_declara_subrotinas  */
  YYSYMBOL_50_4 = 50,                      /* $@4  */
  YYSYMBOL_declara_subrotinas = 51,        /* declara_subrotinas  */
  YYSYMBOL_declaracao_funcao = 52,         /* declaracao_funcao  */
  YYSYMBOL_53_5 = 53,                      /* $@5  */
  YYSYMBOL_54_6 = 54,                      /* $@6  */
  YYSYMBOL_55_7 = 55,                      /* $@7  */
  YYSYMBOL_declaracao_procedimento = 56,   /* declaracao_procedimento  */
  YYSYMBOL_57_8 = 57,                      /* $@8  */
  YYSYMBOL_58_9 = 58,                      /* $@9  */
  YYSYMBOL_parametros_formais_opc = 59,    /* parametros_formais_opc  */
  YYSYMBOL_60_10 = 60,                     /* $@10  */
  YYSYMBOL_parametros_formais = 61,        /* parametros_formais  */
  YYSYMBOL_secao_parametros_formais = 62,  /* secao_parametros_formais  */
  YYSYMBOL_var_opc = 63,                   /* var_opc  */
  YYSYMBOL_var = 64,                       /* var  */
  YYSYMBOL_65_11 = 65,                     /* $@11  */
  YYSYMBOL_66_12 = 66,                     /* $@12  */
  YYSYMBOL_declara_vars = 67,              /* declara_vars  */
  YYSYMBOL_declara_var = 68,               /* declara_var  */
  YYSYMBOL_69_13 = 69,                     /* $@13  */
  YYSYMBOL_70_14 = 70,                     /* $@14  */
  YYSYMBOL_tipo = 71,                      /* tipo  */
  YYSYMBOL_lista_id_var = 72,              /* lista_id_var  */
  YYSYMBOL_lista_idents = 73,              /* lista_idents  */
  YYSYMBOL_comando_composto = 74,          /* comando_composto  */
  YYSYMBOL_comandos = 75,                  /* comandos  */
  YYSYMBOL_comando = 76,                   /* comando  */
  YYSYMBOL_comando_sem_rotulo = 77,        /* comando_sem_rotulo  */
  YYSYMBOL_fatoracao = 78,                 /* fatoracao  */
  YYSYMBOL_79_15 = 79,                     /* $@15  */
  YYSYMBOL_fatoracao_continua = 80,        /* fatoracao_continua  */
  YYSYMBOL_comando_condicional = 81,       /* comando_condicional  */
  YYSYMBOL_82_16 = 82,                     /* $@16  */
  YYSYMBOL_83_17 = 83,                     /* $@17  */
  YYSYMBOL_pv_opc = 84,                    /* pv_opc  */
  YYSYMBOL_else_opc = 85,                  /* else_opc  */
  YYSYMBOL_atribuicao = 86,                /* atribuicao  */
  YYSYMBOL_87_18 = 87,                     /* $@18  */
  YYSYMBOL_chamada_procedimento = 88,      /* chamada_procedimento  */
  YYSYMBOL_89_19 = 89,                     /* $@19  */
  YYSYMBOL_proc_args_opc = 90,             /* proc_args_opc  */
  YYSYMBOL_91_20 = 91,                     /* $@20  */
  YYSYMBOL_comando_repetitivo = 92,        /* comando_repetitivo  */
  YYSYMBOL_93_21 = 93,                     /* $@21  */
  YYSYMBOL_94_22 = 94,                     /* $@22  */
  YYSYMBOL_lista_expressoes_opcional = 95, /* lista_expressoes_opcional  */
  YYSYMBOL_lista_expressoes = 96,          /* lista_expressoes  */
  YYSYMBOL_97_23 = 97,                     /* $@23  */
  YYSYMBOL_leitura = 98,                   /* leitura  */
  YYSYMBOL_escrita = 99,                   /* escrita  */
  YYSYMBOL_expressao = 100,                /* expressao  */
  YYSYMBOL_relacao_expressao_simples = 101, /* relacao_expressao_simples  */
  YYSYMBOL_relacao = 102,                  /* relacao  */
  YYSYMBOL_expressao_simples = 103,        /* expressao_simples  */
  YYSYMBOL_pos_neg_opc = 104,              /* pos_neg_opc  */
  YYSYMBOL_pos_neg = 105,                  /* pos_neg  */
  YYSYMBOL_pos_neg_or = 106,               /* pos_neg_or  */
  YYSYMBOL_termo = 107,                    /* termo  */
  YYSYMBOL_mult_div_and = 108,             /* mult_div_and  */
  YYSYMBOL_fator = 109,                    /* fator  */
  YYSYMBOL_variavel_funcao = 110,          /* variavel_funcao  */
  YYSYMBOL_111_24 = 111,                   /* @24  */
  YYSYMBOL_112_25 = 112,                   /* @25  */
  YYSYMBOL_funcao_opc = 113,               /* funcao_opc  */
  YYSYMBOL_114_26 = 114,                   /* $@26  */
  YYSYMBOL_proc_args = 115,                /* proc_args  */
  YYSYMBOL_116_27 = 116,                   /* $@27  */
  YYSYMBOL_chamada_funcao = 117,           /* chamada_funcao  */
  YYSYMBOL_rot_goto = 118,                 /* rot_goto  */
  YYSYMBOL_numero = 119                    /* numero  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    80,    80,    80,   124,   122,   137,   138,   138,   143,
     142,   163,   163,   166,   166,   184,   187,   188,   189,   190,
     194,   236,   250,   193,   284,   325,   283,   356,   355,   374,
     377,   380,   383,   401,   402,   405,   405,   408,   408,   409,
     409,   409,   413,   414,   417,   420,   417,   448,   451,   458,
     466,   481,   499,   500,   501,   505,   505,   508,   511,   512,
     513,   514,   515,   516,   519,   519,   526,   527,   531,   553,
     530,   580,   580,   583,   583,   586,   586,   652,   652,   673,
     673,   680,   684,   699,   683,   737,   737,   740,   740,   741,
     744,   754,   766,   767,   774,   791,   822,   825,   831,   837,
     843,   849,   855,   863,   881,   885,   885,   888,   888,   891,
     897,   903,   911,   929,   933,   939,   945,   953,   954,   964,
     965,   969,   977,   969,  1074,  1074,  1088,  1091,  1091,  1104,
    1122,  1122,  1125,  1126
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
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM",
  "ABRE_PARENTESES", "FECHA_PARENTESES", "VIRGULA", "PONTO_E_VIRGULA",
  "DOIS_PONTOS", "PONTO", "T_BEGIN", "T_END", "VAR", "IDENT", "ATRIBUICAO",
  "NUMERO", "CMP_IGUAL", "CMP_DIFF", "CMP_MENOR", "CMP_MENOR_IGUAL",
  "CMP_MAIOR_IGUAL", "CMP_MAIOR", "MAIS", "MENOS", "OR", "MULT", "DIV",
  "AND", "NOT", "WHILE", "DO", "IF", "THEN", "ELSE", "PROCEDURE",
  "FUNCTION", "READ", "WRITE", "TYPE", "LOWER_THAN_ELSE", "$accept",
  "programa", "$@1", "bloco", "$@2", "parte_declara_tipos",
  "definicao_tipo", "$@3", "parte_declara_vars",
  "parte_declara_subrotinas", "$@4", "declara_subrotinas",
  "declaracao_funcao", "$@5", "$@6", "$@7", "declaracao_procedimento",
  "$@8", "$@9", "parametros_formais_opc", "$@10", "parametros_formais",
  "secao_parametros_formais", "var_opc", "var", "$@11", "$@12",
  "declara_vars", "declara_var", "$@13", "$@14", "tipo", "lista_id_var",
  "lista_idents", "comando_composto", "comandos", "comando",
  "comando_sem_rotulo", "fatoracao", "$@15", "fatoracao_continua",
  "comando_condicional", "$@16", "$@17", "pv_opc", "else_opc",
  "atribuicao", "$@18", "chamada_procedimento", "$@19", "proc_args_opc",
  "$@20", "comando_repetitivo", "$@21", "$@22",
  "lista_expressoes_opcional", "lista_expressoes", "$@23", "leitura",
  "escrita", "expressao", "relacao_expressao_simples", "relacao",
  "expressao_simples", "pos_neg_opc", "pos_neg", "pos_neg_or", "termo",
  "mult_div_and", "fator", "variavel_funcao", "@24", "@25", "funcao_opc",
  "$@26", "proc_args", "$@27", "chamada_funcao", "rot_goto", "numero", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
#endif

#define YYPACT_NINF (-159)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-125)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -159,    11,    25,  -159,     6,    64,    63,  -159,    33,    70,
      65,    41,  -159,    68,    71,    32,  -159,    75,  -159,    76,
    -159,    72,    77,    74,  -159,  -159,    78,    79,  -159,    80,
      82,    23,  -159,    81,  -159,    83,  -159,     9,  -159,    84,
      85,    23,  -159,  -159,    81,  -159,  -159,    57,  -159,  -159,
      26,  -159,    -2,    -1,  -159,  -159,  -159,  -159,    86,    87,
      90,  -159,    88,  -159,    48,    91,    98,  -159,  -159,  -159,
      92,  -159,  -159,  -159,  -159,   100,   100,  -159,  -159,  -159,
    -159,  -159,    48,  -159,  -159,  -159,    31,     2,  -159,    93,
      48,    73,    -3,   101,    99,   102,    89,    94,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,    48,     2,
      48,  -159,     2,    16,  -159,  -159,    97,  -159,    67,    69,
    -159,  -159,  -159,   103,  -159,   107,  -159,    63,    63,   105,
    -159,    63,    41,   108,  -159,  -159,    -2,    38,    16,   109,
    -159,  -159,  -159,  -159,     2,  -159,  -159,   110,  -159,    48,
      48,  -159,   111,   112,    58,    -3,   115,    61,  -159,  -159,
      -2,   106,  -159,  -159,   118,  -159,  -159,  -159,     0,   114,
    -159,  -159,   116,   106,   117,  -159,  -159,  -159,  -159,  -159,
     120,   122,  -159,  -159,  -159,  -159,    41,   104,  -159,   126,
    -159,  -159,  -159,  -159,    -2,  -159,     0,    48,   106,  -159,
     127,  -159,  -159,  -159
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    51,     0,     0,
       0,     8,    50,     0,     0,    12,     9,     0,     3,     0,
       4,    11,     0,     0,     7,     6,    13,     0,    44,     0,
       0,     0,    44,    40,    43,     0,    10,   131,     5,     0,
       0,    14,    19,    17,    38,    42,    49,     0,    54,   133,
      72,    56,    64,     0,    24,    20,    18,    16,     0,     0,
      71,    52,   131,    82,   106,     0,     0,    60,    57,    58,
       0,    61,    59,   130,   132,    29,    29,    48,    47,    45,
      53,    55,   106,   107,   108,    68,    96,   121,   105,     0,
     106,    77,    36,     0,     0,     0,     0,     0,    97,    98,
      99,   100,   101,   102,   109,   110,   111,    94,   106,   121,
     106,   118,   121,   104,   113,   117,     0,    91,     0,     0,
      93,    65,    66,     0,    67,    81,    35,     0,     0,    27,
      31,     0,     8,     0,    46,    83,    64,    95,   103,     0,
     120,   114,   115,   116,   121,   122,    63,     0,    62,   106,
     106,    78,     0,    34,     0,    36,     0,     0,    25,    21,
      64,    72,   119,   112,   126,    90,    92,    76,   106,     0,
      30,    28,     0,    72,     0,    84,    71,    69,   123,   127,
       0,    85,    89,    33,    32,    26,     8,    74,   129,     0,
     125,    80,    87,    22,    64,    70,   106,   106,    72,    73,
       0,    88,    23,   128
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,  -159,  -159,  -130,  -159,  -159,   119,  -159,  -159,  -159,
    -159,  -159,    95,  -159,  -159,  -159,   113,  -159,  -159,    40,
    -159,  -159,   -24,  -159,  -159,  -159,  -159,   121,   -23,  -159,
    -159,  -159,  -159,  -115,   125,  -159,    96,  -135,  -159,  -159,
    -159,  -159,  -159,  -159,  -158,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,   -61,  -159,  -159,  -159,  -159,
     -64,  -159,  -159,    30,  -159,  -159,  -159,    34,  -159,  -108,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,    26,    15,    17,    23,    20,    30,
      31,    41,    42,    76,   174,   198,    43,    75,   173,    93,
     156,   129,   130,   131,    21,    27,    22,    33,    34,    35,
      95,    79,    47,     8,    67,    50,    51,    68,    69,    70,
     121,    71,    97,   187,    62,   195,   122,   123,   124,   125,
     151,   152,    72,    82,   160,   180,   181,   197,   118,   119,
     182,   107,   108,    86,    87,    88,   109,   113,   144,   114,
     115,   116,   164,   178,   179,   188,   189,   190,    52,    53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      85,   161,   158,   177,   140,   -86,   110,    73,    37,   126,
      45,     3,   153,   154,    74,   185,   157,   111,    96,     5,
      48,    45,    83,    84,    49,   175,   120,    63,     4,    64,
     112,   127,   128,    60,    65,    66,   163,    61,     9,    10,
     202,   141,   142,   143,   -39,    16,   139,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   193,    39,    40,   199,
     104,   105,   106,    58,    10,    59,   169,    10,     6,   172,
      83,    84,   146,   147,   148,   149,     7,    11,    12,    13,
      18,    16,    24,    25,   -37,   166,   167,   -75,   -15,    28,
      29,    32,    37,    36,   -44,    89,    46,    54,    55,    77,
      78,    80,    90,    49,    92,    91,   117,   133,   132,   134,
     145,   -79,   155,   176,   162,   168,    94,   150,    10,   135,
     171,   159,  -124,   165,   186,   191,   136,   183,   192,   184,
     196,   170,   203,   201,    19,   200,    56,   194,   137,     0,
       0,     0,     0,   138,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,    57,    38,     0,     0,    81
};

static const yytype_int16 yycheck[] =
{
      64,   136,   132,   161,   112,     5,     4,     8,    10,    12,
      33,     0,   127,   128,    15,   173,   131,    15,    82,    13,
      11,    44,    22,    23,    15,   160,    90,    29,     3,    31,
      28,    34,    35,     7,    36,    37,   144,    11,     5,     6,
     198,    25,    26,    27,    12,    13,   110,    16,    17,    18,
      19,    20,    21,    22,    23,    24,   186,    34,    35,   194,
      22,    23,    24,     6,     6,     8,     8,     6,     4,     8,
      22,    23,     5,     6,     5,     6,    13,     7,    13,    38,
       9,    13,     7,     7,    12,   149,   150,    14,    10,    12,
      16,    12,    10,    13,    13,     4,    13,    13,    13,    13,
      13,    11,     4,    15,     4,    13,    13,     8,     7,     7,
      13,     4,     7,     7,     5,     4,    76,    14,     6,    30,
       5,    13,     4,    13,     7,     5,    32,    13,     6,    13,
       4,   155,     5,   197,    15,   196,    41,    33,   108,    -1,
      -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    41,    30,    -1,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    41,    42,     0,     3,    13,     4,    13,    73,     5,
       6,     7,    13,    38,    43,    45,    13,    46,     9,    46,
      48,    64,    66,    47,     7,     7,    44,    65,    12,    16,
      49,    50,    12,    67,    68,    69,    13,    10,    74,    34,
      35,    51,    52,    56,    67,    68,    13,    72,    11,    15,
      75,    76,   118,   119,    13,    13,    52,    56,     6,     8,
       7,    11,    84,    29,    31,    36,    37,    74,    77,    78,
      79,    81,    92,     8,    15,    57,    53,    13,    13,    71,
      11,    76,    93,    22,    23,   100,   103,   104,   105,     4,
       4,    13,     4,    59,    59,    70,   100,    82,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   101,   102,   106,
       4,    15,    28,   107,   109,   110,   111,    13,    98,    99,
     100,    80,    86,    87,    88,    89,    12,    34,    35,    61,
      62,    63,     7,     8,     7,    30,    32,   103,   107,   100,
     109,    25,    26,    27,   108,    13,     5,     6,     5,     6,
      14,    90,    91,    73,    73,     7,    60,    73,    43,    13,
      94,    77,     5,   109,   112,    13,   100,   100,     4,     8,
      62,     5,     8,    58,    54,    77,     7,    84,   113,   114,
      95,    96,   100,    13,    13,    84,     7,    83,   115,   116,
     117,     5,     6,    43,    33,    85,     4,    97,    55,    77,
      95,   100,    84,     5
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    42,    41,    44,    43,    45,    45,    45,    47,
      46,    48,    48,    50,    49,    49,    51,    51,    51,    51,
      53,    54,    55,    52,    57,    58,    56,    60,    59,    59,
      61,    61,    62,    62,    62,    63,    63,    65,    64,    66,
      64,    64,    67,    67,    69,    70,    68,    71,    72,    72,
      73,    73,    74,    74,    74,    75,    75,    76,    77,    77,
      77,    77,    77,    77,    79,    78,    80,    80,    82,    83,
      81,    84,    84,    85,    85,    87,    86,    89,    88,    91,
      90,    90,    93,    94,    92,    95,    95,    97,    96,    96,
      98,    98,    99,    99,   100,   101,   101,   102,   102,   102,
     102,   102,   102,   103,   103,   104,   104,   105,   105,   106,
     106,   106,   107,   107,   108,   108,   108,   109,   109,   109,
     109,   111,   112,   110,   114,   113,   113,   116,   115,   117,
     118,   118,   119,   119
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     5,     3,     3,     0,     0,
       4,     1,     0,     0,     2,     0,     2,     1,     2,     1,
       0,     0,     0,    11,     0,     0,     8,     0,     4,     0,
       3,     1,     4,     4,     2,     1,     0,     0,     4,     0,
       3,     0,     2,     1,     0,     0,     6,     1,     3,     1,
       3,     1,     3,     4,     2,     3,     1,     2,     1,     1,
       1,     1,     4,     4,     0,     3,     1,     1,     0,     0,
       8,     1,     0,     2,     0,     0,     3,     0,     2,     0,
       4,     0,     0,     0,     6,     1,     0,     0,     4,     1,
       3,     1,     3,     1,     2,     2,     0,     1,     1,     1,
       1,     1,     1,     3,     2,     1,     0,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       2,     0,     0,     4,     0,     2,     0,     0,     4,     1,
       2,     0,     2,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
  case 2: /* $@1: %empty  */
#line 80 "compilador.y"
                        {
				n_procedimentos = 0;
				n_types = 2;	// presumindo int e boolean (embora eu não tenha implementado boolean)
				n_lexico = 0;
				deslocamento = 0;
				num_vars_global = 0;
				n_rotulos = 0;
				is_ref = 0;
				proc_call = 0;
				proc_call_ident = malloc(sizeof(char) * 100);
				param_index = 0;
				geraCodigo (NULL, "INPP");
				//testLabels();

				tipo_fator = 0;
			}
#line 1412 "compilador.tab.c"
    break;

  case 3: /* programa: $@1 PROGRAM IDENT ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  */
#line 98 "compilador.y"
                                    {
				//printTokenStack(s);
				//printTypeStack(types);

				int n_dmem = 0;
				while (s->top != NULL){
					if (!strcmp(s->top->data->cat, "VS"))
						n_dmem++;
					popToken(s);
				}

				if (n_dmem > 0){
					char *temp_dmem = malloc(sizeof(char) * 100);
					sprintf(temp_dmem, "DMEM %d", n_dmem);
					geraCodigo (NULL, temp_dmem);
					free(temp_dmem);
				}
				geraCodigo (NULL, "PARA");
				//printTokenStack(s);
				//printTypeStack(types);
			}
#line 1438 "compilador.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 124 "compilador.y"
            {
            }
#line 1445 "compilador.tab.c"
    break;

  case 5: /* bloco: parte_declara_tipos parte_declara_vars $@2 parte_declara_subrotinas comando_composto  */
#line 129 "compilador.y"
                        {
				if (s->top != NULL)
					if (!strcmp(s->top->data->cat, "PROC"))
						popToken(s);
			}
#line 1455 "compilador.tab.c"
    break;

  case 9: /* $@3: %empty  */
#line 143 "compilador.y"
        {
		temp_type = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(temp_type, token);
	}
#line 1464 "compilador.tab.c"
    break;

  case 10: /* definicao_tipo: IDENT $@3 CMP_IGUAL IDENT  */
#line 149 "compilador.y"
        {
		n_types++;
		int orig_type_id;
		if (!strcmp(token, "integer"))
			orig_type_id = 1;
		else if (!strcmp(token, "boolean"))
			orig_type_id = 2;
		pushType(types, newType(n_types, temp_type, orig_type_id, token));

		free(temp_type);
	}
#line 1480 "compilador.tab.c"
    break;

  case 11: /* parte_declara_vars: var  */
#line 163 "compilador.y"
                         {deslocamento = 0;}
#line 1486 "compilador.tab.c"
    break;

  case 13: /* $@4: %empty  */
#line 166 "compilador.y"
                                {n_procedimentos = 0;}
#line 1492 "compilador.tab.c"
    break;

  case 14: /* parte_declara_subrotinas: $@4 declara_subrotinas  */
#line 168 "compilador.y"
                                                        {
								if (n_lexico == 0){
									Token_Node *temp = s->top;
									while (temp){
										if (!strcmp(temp->data->cat, "PROC") and l->top->data->label_id != 0)
											//printf("\n\n\n%s\n\n\n", popLabel(l)->data->label);
											popLabel(l);
										temp = temp->next;
									}
								}
									

								Label_Node *node = l->top;
								//char *temp_rotulo = malloc(sizeof(char) * 100);
								//sprintf(temp_rotulo, "%s: NADA", node->data->label);
								geraCodigo(node->data->label, "NADA");
							}
#line 1514 "compilador.tab.c"
    break;

  case 20: /* $@5: %empty  */
#line 194 "compilador.y"
                                        {
						n_procedimentos++;
						
						num_vars = 0;
						n_lexico++;

						Label *label = newLabel(n_rotulos, token);
						pushLabel(l, label);
						n_rotulos++;

						char *temp_rotulo = malloc(sizeof(char) * 100);
						sprintf(temp_rotulo, "DSVS %s", label->label);

						if (n_procedimentos < 2)
							geraCodigo(NULL, temp_rotulo);

						label = newLabel(n_rotulos, token);
						pushLabel(l, label);
						n_rotulos++;

						//sprintf(temp_rotulo, "%s: ENPR %d", label->label, n_lexico);
						sprintf(temp_rotulo, "ENPR %d", n_lexico);

						geraCodigo(label->label, temp_rotulo);

						Token *new_token = newFunc(
							token, 
							"FUNC",  
							label->label, 
							n_lexico,
							0, 
							"placeholder_func",
							0,
							NULL
						);

						pushToken(s, new_token);
						num_vars++;
						//deslocamento++;
					}
#line 1559 "compilador.tab.c"
    break;

  case 21: /* $@6: %empty  */
#line 236 "compilador.y"
                                        {
						Token_Node *t = s->top;
						while (strcmp(t->data->cat, "FUNC"))
							t = t->next;
						//free(t->data->type);
						//t->data->type = malloc(sizeof(char) * (strlen(token) + 1));
						if (!strcmp(token, "integer"))
							strcpy(t->data->type, "int");
						else
							strcpy(t->data->type, token);
						//printTokenStack(s);
					}
#line 1576 "compilador.tab.c"
    break;

  case 22: /* $@7: %empty  */
#line 250 "compilador.y"
                                        {
						n_lexico--;
						Token_Node *t = s->top;
						int n_dmem = 0;
						while (
							strcmp(t->data->cat, "PROC") and 
							strcmp(t->data->cat, "FUNC")
						){
							popToken(s);
							if (!strcmp(t->data->cat, "VS"))
								n_dmem++;
							t = t->next;
						}

						if (n_dmem > 0){
							char *temp_dmem = malloc(sizeof(char) * 100);
							sprintf(temp_dmem, "DMEM %d", n_dmem);
							geraCodigo(NULL, temp_dmem);
							free(temp_dmem);
						}

						char *temp_rtpr = malloc(sizeof(char) * 100);
						sprintf(temp_rtpr, "RTPR %d, %d", t->data->level, t->data->n_params);
						geraCodigo(NULL, temp_rtpr);
						free(temp_rtpr);

						

						free(popLabel(l));

					}
#line 1612 "compilador.tab.c"
    break;

  case 24: /* $@8: %empty  */
#line 284 "compilador.y"
                                                        {
								n_procedimentos++;

								num_vars = 0;
								n_lexico++;

								Label *label = newLabel(n_rotulos, token);
								pushLabel(l, label);
								n_rotulos++;

								char *temp_rotulo = malloc(sizeof(char) * 100);
								sprintf(temp_rotulo, "DSVS %s", label->label);

								if (n_procedimentos < 2)
									geraCodigo(NULL, temp_rotulo);

								label = newLabel(n_rotulos, token);
								pushLabel(l, label);
								n_rotulos++;

								//sprintf(temp_rotulo, "%s: ENPR %d", label->label, n_lexico);
								sprintf(temp_rotulo, "ENPR %d", n_lexico);

								geraCodigo(label->label, temp_rotulo);

								Token *new_token = newProc(
									token, 
									"PROC", 
									n_lexico, 
									label->label, 
									0, 
									NULL
								);

								pushToken(s, new_token);
								num_vars++;
								//deslocamento++;

							}
#line 1656 "compilador.tab.c"
    break;

  case 25: /* $@9: %empty  */
#line 325 "compilador.y"
                                                        {
								n_lexico--;
								Token_Node *t = s->top;
								int n_dmem = 0;
								while (strcmp(t->data->cat, "PROC")){
									popToken(s);
									if (!strcmp(t->data->cat, "VS"))
										n_dmem++;
									t = t->next;
								}

								if (n_dmem > 0){
									char *temp_dmem = malloc(sizeof(char) * 100);
									sprintf(temp_dmem, "DMEM %d", n_dmem);
									geraCodigo(NULL, temp_dmem);
									free(temp_dmem);
								}

								char *temp_rtpr = malloc(sizeof(char) * 100);
								sprintf(temp_rtpr, "RTPR %d, %d", t->data->level, t->data->n_params);
								geraCodigo(NULL, temp_rtpr);
								free(temp_rtpr);

								

								free(popLabel(l));

							}
#line 1689 "compilador.tab.c"
    break;

  case 27: /* $@10: %empty  */
#line 356 "compilador.y"
                                                {
							Token_Node *t = s->top;
							pf_counter = -4;
							while (t != NULL and !strcmp(t->data->cat, "PF")){
								t->data->shift = pf_counter;
								pf_counter--;
								t = t->next;
							}
							if (!strcmp(t->data->cat, "FUNC"))
								t->data->shift = pf_counter;
							t->data->n_params = abs(pf_counter) - 4;

							//printf("updating params...\n");
							updateParams(s);
							//printf("updated.\nparams:\n");
							//for(int i = 0; i < t->data->n_params; i++)
							//	printf("[%s, %s] ", t->data->formal_params[i].type, t->data->formal_params[i].mech);
							//printf("\n\n\n");
						}
#line 1713 "compilador.tab.c"
    break;

  case 32: /* secao_parametros_formais: var_opc lista_idents DOIS_PONTOS IDENT  */
#line 384 "compilador.y"
                                                        {
								Token_Node *temp = s->top;
								while (temp){
									if (temp->data->type)
										if (!strcmp(temp->data->type, "placeholder_ident")){
											free(temp->data->type);
											temp->data->type = malloc(sizeof(char) * (strlen(token) + 1));
											if (!strcmp(token, "integer"))
												strcpy(temp->data->type, "int");
											else 
												strcpy(temp->data->type, token);
										}
									else break;
									temp = temp->next;
									is_ref = 0;
								}
							}
#line 1735 "compilador.tab.c"
    break;

  case 35: /* var_opc: VAR  */
#line 405 "compilador.y"
             {is_ref = 1;}
#line 1741 "compilador.tab.c"
    break;

  case 37: /* $@11: %empty  */
#line 408 "compilador.y"
                  {num_vars = 0; }
#line 1747 "compilador.tab.c"
    break;

  case 39: /* $@12: %empty  */
#line 409 "compilador.y"
                                {num_vars = 0; }
#line 1753 "compilador.tab.c"
    break;

  case 44: /* $@13: %empty  */
#line 417 "compilador.y"
              { }
#line 1759 "compilador.tab.c"
    break;

  case 45: /* $@14: %empty  */
#line 420 "compilador.y"
              { 
				Token_Node *t = s->top;
				//printf("%s,%s,%s\n", t->data->cat, t->data->type, token);
				while (!strcmp(t->data->type,"") and !strcmp(t->data->cat, "VS")){
					free(t->data->type);
					t->data->type = malloc(sizeof(char) * (strlen(token) + 1));
					if (!strcmp(token, "integer"))
						strcpy(t->data->type, "int");
					else if (!strcmp(token, "boolean"))
						strcpy(t->data->type, "bool");
					else 
						strcpy(t->data->type, token);
					if (t->next == NULL or strcmp(t->next->data->cat, "VS")) break;
					t = t->next;
				}

				//printTokenStack(s);

				char *temp_amem = malloc(sizeof(char) * 100);
				sprintf(temp_amem, "AMEM %d", num_vars);
				geraCodigo (NULL, temp_amem);
				free(temp_amem);
				num_vars_global += num_vars;
				num_vars = 0;
              }
#line 1789 "compilador.tab.c"
    break;

  case 48: /* lista_id_var: lista_id_var VIRGULA IDENT  */
#line 452 "compilador.y"
              { /* insere �ltima vars na tabela de s�mbolos */
			  Token *new_token = newVar(token, "VS", n_lexico, "", deslocamento);
			  pushToken(s, new_token);
			  num_vars++;
			  deslocamento++;
			   }
#line 1800 "compilador.tab.c"
    break;

  case 49: /* lista_id_var: IDENT  */
#line 458 "compilador.y"
                    { /* insere vars na tabela de s�mbolos */
			Token *new_token = newVar(token, "VS", n_lexico, "", deslocamento);
			pushToken(s, new_token);
			num_vars++;
			deslocamento++;
			}
#line 1811 "compilador.tab.c"
    break;

  case 50: /* lista_idents: lista_idents VIRGULA IDENT  */
#line 467 "compilador.y"
                                {
					if (strcmp(token,"input") and strcmp(token, "output")){
						char *fp_pass = malloc(sizeof(char) * 100);
						if (is_ref)
							strcpy(fp_pass, "ref");
						else
							strcpy(fp_pass, "val");

						Token *new_token = newFP(token, "PF", n_lexico, "placeholder_ident", deslocamento, fp_pass);
			  			pushToken(s, new_token);

						free(fp_pass);
					}
				}
#line 1830 "compilador.tab.c"
    break;

  case 51: /* lista_idents: IDENT  */
#line 482 "compilador.y"
                                {
					if (strcmp(token,"input") and strcmp(token, "output")){
						char *fp_pass = malloc(sizeof(char) * 100);
						if (is_ref)
							strcpy(fp_pass, "ref");
						else
							strcpy(fp_pass, "val");

						Token *new_token = newFP(token, "PF", n_lexico, "placeholder_ident", deslocamento, fp_pass);
						pushToken(s, new_token);

						free(fp_pass);
					}
				}
#line 1849 "compilador.tab.c"
    break;

  case 64: /* $@15: %empty  */
#line 519 "compilador.y"
            {
				l_elem = malloc(sizeof(char) * (strlen(token) + 1));
				strcpy(l_elem, token);
			}
#line 1858 "compilador.tab.c"
    break;

  case 66: /* fatoracao_continua: atribuicao  */
#line 526 "compilador.y"
                                   {/*printTokenStack(s);*/}
#line 1864 "compilador.tab.c"
    break;

  case 67: /* fatoracao_continua: chamada_procedimento  */
#line 527 "compilador.y"
                                                             {/*printTokenStack(s);*/}
#line 1870 "compilador.tab.c"
    break;

  case 68: /* $@16: %empty  */
#line 531 "compilador.y"
                                        {
						if (tipo_fator != 2){
							//printf("erro if na linha %d\n\n\n", nl);
							//printf("$2: %d\n\n", tipo_fator);
							//exit(0);
							imprimeErro("if com tipo incorreto");
						}

						pushLabel(l, newLabel(n_rotulos, "if"));
						n_rotulos++;
						pushLabel(l, newLabel(n_rotulos, "if"));
						n_rotulos++;

						Label_Node *node = l->top->next;
						char *temp_rotulo = malloc(sizeof(char) * 100);
						sprintf(temp_rotulo, "DSVF %s", node->data->label);

						geraCodigo(NULL, temp_rotulo);

						free(temp_rotulo);
					}
#line 1896 "compilador.tab.c"
    break;

  case 69: /* $@17: %empty  */
#line 553 "compilador.y"
                                        {
						Label_Node *node = l->top;
						char *temp_rotulo = malloc(sizeof(char) * 100);
						sprintf(temp_rotulo, "DSVS %s", node->data->label);

						geraCodigo(NULL, temp_rotulo);

						node = l->top->next;
						//sprintf(temp_rotulo, "%s: NADA", node->data->label);

						geraCodigo(node->data->label, "NADA");

						free(temp_rotulo);
					}
#line 1915 "compilador.tab.c"
    break;

  case 70: /* comando_condicional: IF expressao $@16 THEN comando_sem_rotulo pv_opc $@17 else_opc  */
#line 567 "compilador.y"
                                        {
						Label_Node *node = l->top;
						char *temp_rotulo = malloc(sizeof(char) * 100);
						//sprintf(temp_rotulo, "%s: NADA", node->data->label);

						geraCodigo(node->data->label, "NADA");

						free(temp_rotulo);
						free(popLabel(l));
						free(popLabel(l));
					}
#line 1931 "compilador.tab.c"
    break;

  case 75: /* $@18: %empty  */
#line 586 "compilador.y"
            {
				//printf("=====|%s|=====", l_elem);
			}
#line 1939 "compilador.tab.c"
    break;

  case 76: /* atribuicao: $@18 ATRIBUICAO expressao  */
#line 590 "compilador.y"
                        {
				Token_Node *t = searchTokenStack(s, l_elem);
				char *temp_armz = malloc(sizeof(char) * 100);
				//printTokenStack(s);
				//printf("%s", l_elem);

				int l_type = -1;
				Type_Node *n;
				if (!strcmp(t->data->type, "int"))
					l_type = 1;
				else if (!strcmp(t->data->type, "bool"))
					l_type = 2;
				else{
					n = getType(types, t->data->type);
					//printf("\t(%d, %s, %d, %s),\n", n->data->type_id, n->data->ident, n->data->orig_type_id, n->data->orig_type);
					l_type = n->data->type_id;
				}

				if (l_type != tipo_fator){
					// Ambos são tipos padrão (int (id = 1) ou bool (id = 2))
					if (l_type < 3 and tipo_fator < 3)
						imprimeErro("Atribuição de tipo incorreto (tipos incompatíveis entre si)");
					// Demais casos
					else {
						// Ambos são tipos novos
						if (l_type >= 3 and tipo_fator >= 3)
							// São diferentes entre si
							if (l_type != tipo_fator)
								imprimeErro("Atribuição de tipo incorreto (tipos derivados incompatíveis entre si)");
						//printf("tipos encontrados: %d %d\n", l_type, tipo_fator);
						int l_type_orig = l_type, tipo_fator_orig = tipo_fator;
						if (l_type >= 3)
							l_type_orig = n->data->orig_type_id;
						if (tipo_fator >= 3)
							tipo_fator_orig = getTypeByID(types, tipo_fator)->data->orig_type_id;
						//printf("tipos originais:  %d %d\n\n", l_type_orig, tipo_fator_orig);

						if (l_type_orig != tipo_fator_orig)
							imprimeErro("Atribuição de tipo incorreto (tipos incompatíveis entre si)");
					}
					//printf("erro atribuição %d %d\n\n\n", l_type, $2);
					//exit(-1);
					//imprimeErro("Atribuição de tipo incorreto");
					//printf("l_type: %d\ntipo_fator: %d\n", l_type, tipo_fator);
					//printf("arrumar erro aqui\n\n\n");
				}

				if (!strcmp(t->data->cat, "PF")){
					if (!strcmp(t->data->pass, "ref"))
						sprintf(temp_armz, "ARMI %d, %d", t->data->level, t->data->shift);
					else
						sprintf(temp_armz, "ARMZ %d, %d", t->data->level, t->data->shift);
				}
				else
					sprintf(temp_armz, "ARMZ %d, %d", t->data->level, t->data->shift);
				geraCodigo(NULL, temp_armz);
				free(l_elem);
				free(temp_armz);
			}
#line 2003 "compilador.tab.c"
    break;

  case 77: /* $@19: %empty  */
#line 652 "compilador.y"
                        {
				func_call_ident = malloc(sizeof(char) * (strlen(l_elem) + 1));
				strcpy(func_call_ident, l_elem);
			}
#line 2012 "compilador.tab.c"
    break;

  case 78: /* chamada_procedimento: $@19 proc_args_opc  */
#line 657 "compilador.y"
                        {
				Token_Node *t = searchTokenStack(s, l_elem);

				if (!strcmp(t->data->cat, "FUNC")){
					geraCodigo(NULL, "AMEM 1");
				}

				char *temp_chpr = malloc(sizeof(char) * 100);
				sprintf(temp_chpr, "CHPR %s, %d", t->data->label, n_lexico);
				geraCodigo(NULL, temp_chpr);

				free(l_elem);
				free(temp_chpr);
			}
#line 2031 "compilador.tab.c"
    break;

  case 79: /* $@20: %empty  */
#line 673 "compilador.y"
                {
					proc_call = 1;
				}
#line 2039 "compilador.tab.c"
    break;

  case 80: /* proc_args_opc: $@20 ABRE_PARENTESES lista_expressoes_opcional FECHA_PARENTESES  */
#line 677 "compilador.y"
                                {
					param_index = 0;
					proc_call = 0;
				}
#line 2048 "compilador.tab.c"
    break;

  case 82: /* $@21: %empty  */
#line 684 "compilador.y"
                                        {
						pushLabel(l, newLabel(n_rotulos, "while"));
						n_rotulos++;
						pushLabel(l, newLabel(n_rotulos, "while"));
						n_rotulos++;

						Label_Node *node = l->top->next;
						char *temp_rotulo = malloc(sizeof(char) * 100);
						//sprintf(temp_rotulo, "%s: NADA", node->data->label);

						geraCodigo(node->data->label, "NADA");

						free(temp_rotulo);
					}
#line 2067 "compilador.tab.c"
    break;

  case 83: /* $@22: %empty  */
#line 699 "compilador.y"
                                        {
						if (tipo_fator != 2){
							printf("erro while\n\n\n");
							printf("$2: %d\n\n", tipo_fator);
							exit(-1);
						}

						Label_Node *node = l->top;
						char *temp_rotulo = malloc(sizeof(char) * 100);
						sprintf(temp_rotulo, "DSVF %s", node->data->label);

						geraCodigo(NULL, temp_rotulo);

						free(temp_rotulo);
					}
#line 2087 "compilador.tab.c"
    break;

  case 84: /* comando_repetitivo: WHILE $@21 expressao DO $@22 comando_sem_rotulo  */
#line 715 "compilador.y"
                                        {
						Label_Node *nada = popLabel(l);
						Label_Node *dsvs = popLabel(l);

						char *temp_rotulo = malloc(sizeof(char) * 100);
						sprintf(temp_rotulo, "DSVS %s", dsvs->data->label);

						geraCodigo(NULL, temp_rotulo);

						//sprintf(temp_rotulo, "%s: NADA", nada->data->label);

						geraCodigo(nada->data->label, "NADA");

						free(temp_rotulo);
						free(nada);
						free(dsvs);
					}
#line 2109 "compilador.tab.c"
    break;

  case 87: /* $@23: %empty  */
#line 740 "compilador.y"
                                                 {param_index++;}
#line 2115 "compilador.tab.c"
    break;

  case 90: /* leitura: leitura VIRGULA IDENT  */
#line 745 "compilador.y"
                {
			geraCodigo(NULL, "LEIT");

			Token_Node *t = searchTokenStack(s, token);
			char *temp_armz = malloc(sizeof(char) * 100);
			sprintf(temp_armz, "ARMZ %d, %d", t->data->level, t->data->shift);
			geraCodigo(NULL, temp_armz);
			free(temp_armz);
		}
#line 2129 "compilador.tab.c"
    break;

  case 91: /* leitura: IDENT  */
#line 755 "compilador.y"
                {
			geraCodigo(NULL, "LEIT");

			Token_Node *t = searchTokenStack(s, token);
			char *temp_armz = malloc(sizeof(char) * 100);
			sprintf(temp_armz, "ARMZ %d, %d", t->data->level, t->data->shift);
			geraCodigo(NULL, temp_armz);
			free(temp_armz);
		}
#line 2143 "compilador.tab.c"
    break;

  case 92: /* escrita: escrita VIRGULA expressao  */
#line 766 "compilador.y"
                                          {geraCodigo(NULL, "IMPR");}
#line 2149 "compilador.tab.c"
    break;

  case 93: /* escrita: expressao  */
#line 767 "compilador.y"
                                  {geraCodigo(NULL, "IMPR");}
#line 2155 "compilador.tab.c"
    break;

  case 94: /* expressao: expressao_simples relacao_expressao_simples  */
#line 775 "compilador.y"
        {
		//printf("expressão: %d %d\n\n\n", $1, $2);
		yyval = yyvsp[-1];
		tipo_fator = yyvsp[-1];
		if (yyvsp[0] != -1){
			//if ($1 != $2){
			//	printf("error? %d %d\n\n", $1, $2);
			//	exit(0);
			//}
			yyval = yyvsp[0];
			tipo_fator = yyvsp[0];
		}

	}
#line 2174 "compilador.tab.c"
    break;

  case 95: /* relacao_expressao_simples: relacao expressao_simples  */
#line 792 "compilador.y"
        {
		if (yyvsp[0] != 1){
			if (yyvsp[0] < 3)
				imprimeErro("Expressão simples entre tipos incompatíveis");
			else if (getTypeByID(types, yyvsp[0])->data->orig_type_id != 1)
				imprimeErro("Expressão simples entre tipos incompatíveis");
				//printf("error: $2 == %d\n", $2);
				//printf("       $1 == %d\n\n", $1);
				//exit(-1);
		}

		//printf("relação expressão simples:: %d\n\n", $1);
		yyval = yyvsp[-1];

		op_bool = popOp(op_relacao);

		if (op_bool == 1)
			geraCodigo(NULL, "CMIG");
		else if (op_bool == 2)
			geraCodigo(NULL, "CMDG");
		else if (op_bool == 3)
			geraCodigo(NULL, "CMME");
		else if (op_bool == 4)
			geraCodigo(NULL, "CMEG");
		else if (op_bool == 5)
			geraCodigo(NULL, "CMAG");
		else if (op_bool == 6)
			geraCodigo(NULL, "CMMA");
		op_bool = 0;	
	}
#line 2209 "compilador.tab.c"
    break;

  case 96: /* relacao_expressao_simples: %empty  */
#line 822 "compilador.y"
           {yyval = -1;}
#line 2215 "compilador.tab.c"
    break;

  case 97: /* relacao: CMP_IGUAL  */
#line 826 "compilador.y"
                {
			op_bool = 1;
			pushOp(op_relacao, 1);
			yyval = 2;
		}
#line 2225 "compilador.tab.c"
    break;

  case 98: /* relacao: CMP_DIFF  */
#line 832 "compilador.y"
                {
			op_bool = 2;
			pushOp(op_relacao, 2);
			yyval = 2;
		}
#line 2235 "compilador.tab.c"
    break;

  case 99: /* relacao: CMP_MENOR  */
#line 838 "compilador.y"
                {
			op_bool = 3;
			pushOp(op_relacao, 3);
			yyval = 2;
		}
#line 2245 "compilador.tab.c"
    break;

  case 100: /* relacao: CMP_MENOR_IGUAL  */
#line 844 "compilador.y"
                {
			op_bool = 4;
			pushOp(op_relacao, 4);
			yyval = 2;
		}
#line 2255 "compilador.tab.c"
    break;

  case 101: /* relacao: CMP_MAIOR_IGUAL  */
#line 850 "compilador.y"
                {
			op_bool = 5;
			pushOp(op_relacao, 5);
			yyval = 2;
		}
#line 2265 "compilador.tab.c"
    break;

  case 102: /* relacao: CMP_MAIOR  */
#line 856 "compilador.y"
                {
			op_bool = 6;
			pushOp(op_relacao, 6);
			yyval = 2;
		}
#line 2275 "compilador.tab.c"
    break;

  case 103: /* expressao_simples: expressao_simples pos_neg_or termo  */
#line 864 "compilador.y"
        {
		if (yyvsp[0] != yyvsp[-1]){
			printf("error\n\n\n");
			exit(0);
		}
		//printf("expressão simples: %d\n\n", $3);
		yyval = yyvsp[0];

		op_termo = popOp(op_expressao);
		
		if (op_termo == 1)
			geraCodigo(NULL, "SOMA");
		else if (op_termo == 2)
			geraCodigo(NULL, "SUBT");
		else if (op_termo == 3)
			geraCodigo(NULL, "OR");
		op_termo = 0;
	}
#line 2298 "compilador.tab.c"
    break;

  case 104: /* expressao_simples: pos_neg_opc termo  */
#line 881 "compilador.y"
                              {yyval = yyvsp[0]; /*printf("termo $2: %d\n\n", $2);*/}
#line 2304 "compilador.tab.c"
    break;

  case 109: /* pos_neg_or: MAIS  */
#line 892 "compilador.y"
                        {
				op_termo = 1;
				pushOp(op_expressao, 1);
				yyval = 1;
			}
#line 2314 "compilador.tab.c"
    break;

  case 110: /* pos_neg_or: MENOS  */
#line 898 "compilador.y"
                        {
				op_termo = 2;
				pushOp(op_expressao, 2);
				yyval = 1;
			}
#line 2324 "compilador.tab.c"
    break;

  case 111: /* pos_neg_or: OR  */
#line 904 "compilador.y"
                        {
				op_termo = 3;
				pushOp(op_expressao, 3);
				yyval = 2;
			}
#line 2334 "compilador.tab.c"
    break;

  case 112: /* termo: termo mult_div_and fator  */
#line 912 "compilador.y"
        {
		//printf("termo * fator: %d %d\n\n", $1, $3);
		if (yyvsp[0] != yyvsp[-1]){
			printf("error\n\n\n");
			exit(0);
		}
		yyval = yyvsp[0];

		op_fator = popOp(op_fatores);

		if (op_fator == 1)
			geraCodigo(NULL, "MULT");
		else if (op_fator == 2)
			geraCodigo(NULL, "DIVI");
		else if (op_fator == 3)
			geraCodigo(NULL, "CONJ");
		op_fator = 0;
	}
#line 2357 "compilador.tab.c"
    break;

  case 113: /* termo: fator  */
#line 929 "compilador.y"
                  {yyval = yyvsp[0]; /*printf("fator: %d\n\n\n", $1);*/}
#line 2363 "compilador.tab.c"
    break;

  case 114: /* mult_div_and: MULT  */
#line 934 "compilador.y"
        {
		op_fator = 1;
		pushOp(op_fatores, 1);
		yyval = 1;
	}
#line 2373 "compilador.tab.c"
    break;

  case 115: /* mult_div_and: DIV  */
#line 940 "compilador.y"
        {
		op_fator = 2;
		pushOp(op_fatores, 2);
		yyval = 1;
	}
#line 2383 "compilador.tab.c"
    break;

  case 116: /* mult_div_and: AND  */
#line 946 "compilador.y"
        {
		op_fator = 3;
		pushOp(op_fatores, 3);
		yyval = 2;
	}
#line 2393 "compilador.tab.c"
    break;

  case 117: /* fator: variavel_funcao  */
#line 953 "compilador.y"
                        {yyval = yyvsp[0]; /*printf("$1: %d\n\n", $1);*/}
#line 2399 "compilador.tab.c"
    break;

  case 118: /* fator: NUMERO  */
#line 955 "compilador.y"
                {
			tipo_fator = 1;
			yyval = 1;

			char *temp_crct = malloc(sizeof(char) * 100);
			sprintf(temp_crct, "CRCT %s", token);
			geraCodigo(NULL, temp_crct);
			free(temp_crct);
		}
#line 2413 "compilador.tab.c"
    break;

  case 119: /* fator: ABRE_PARENTESES expressao FECHA_PARENTESES  */
#line 964 "compilador.y"
                                                           {yyval = yyvsp[-1];}
#line 2419 "compilador.tab.c"
    break;

  case 121: /* @24: %empty  */
#line 969 "compilador.y"
        {
		temp_ident = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(temp_ident, token);
		
		//func_call_ident = malloc(sizeof(char) * (strlen(token) + 1));
		//strcpy(func_call_ident, token);
	}
#line 2431 "compilador.tab.c"
    break;

  case 122: /* @25: %empty  */
#line 977 "compilador.y"
        {
		Token_Node *t = searchTokenStack(s, token);
		char *temp_crvl = malloc(sizeof(char) * 100);

		if (!strcmp(t->data->type, "int")){
			tipo_fator = 1;
			yyval = 1;
			yyvsp[-1]= 1;	// WHYYYYYYYY?????
			//printf("\nis_int\n\n");
		}
		else if (!strcmp(t->data->type, "bool")){
			tipo_fator = 2;
			yyval = 2;
			yyvsp[-1] = 2;	// WHYYYYYYYY?????
		}
		else{
			Type_Node *n = getType(types, t->data->type);
			//printf("\t(%d, %s, %d, %s),\n", n->data->type_id, n->data->ident, n->data->orig_type_id, n->data->orig_type);
			tipo_fator = n->data->type_id;
			yyval = tipo_fator;
			yyvsp[-1] = tipo_fator;
		}
		if (strcmp(t->data->cat, "FUNC")){
			if (proc_call){
				Token_Node *left = searchTokenStack(s, func_call_ident);
				if (left->data->formal_params){
					if (
						!strcmp(
							left->data->formal_params[param_index].mech,
							"ref"
						)
					){
						if (t->data->pass){
							if (!strcmp(t->data->pass, "ref"))
								sprintf(
									temp_crvl, 
									"CRVL %d, %d", 
									t->data->level, t->data->shift
								);
							else
								sprintf(
									temp_crvl, 
									"CREN %d, %d", 
									t->data->level, t->data->shift
								);
						}
						else
							sprintf(
								temp_crvl, 
								"CREN %d, %d", 
								t->data->level, t->data->shift
							);
					}
					else 
						sprintf(
							temp_crvl, 
							"CRVL %d, %d", 
							t->data->level, t->data->shift
						);
				}
			}
			else{
				if (t->data->pass){
					if (!strcmp(t->data->pass, "ref"))
						sprintf(
							temp_crvl, 
							"CRVI %d, %d", 
							t->data->level, t->data->shift
						);
					else
						sprintf(
							temp_crvl, 
							"CRVL %d, %d", 
							t->data->level, t->data->shift
						);
				}
				else
					sprintf(
						temp_crvl, 
						"CRVL %d, %d", 
						t->data->level, t->data->shift
					);
			}
			//sprintf(temp_crvl, "CRVL %d, %d", t->data->level, t->data->shift);
			geraCodigo(NULL, temp_crvl);
			free(temp_crvl);
			//free(t);
		}
	}
#line 2525 "compilador.tab.c"
    break;

  case 123: /* variavel_funcao: @24 IDENT @25 funcao_opc  */
#line 1067 "compilador.y"
        {
	//	if (strlen(func_call_ident) > 0)
	//		free(func_call_ident);
	}
#line 2534 "compilador.tab.c"
    break;

  case 124: /* $@26: %empty  */
#line 1074 "compilador.y"
        {
		func_call_ident = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(func_call_ident, temp_ident);

		//printf("%s\n\n\n", l_elem);
		Token_Node *t = searchTokenStack(s, func_call_ident);
		//printf("token: %s\n\n\n", func_call_ident);
		if (!strcmp(t->data->cat, "FUNC")){
			geraCodigo(NULL, "AMEM 1");
			func_call = 1;
		}
		//printf("\n\nchamada_funcao\n\n");

	}
#line 2553 "compilador.tab.c"
    break;

  case 127: /* $@27: %empty  */
#line 1091 "compilador.y"
                {
					proc_call = 1;
				}
#line 2561 "compilador.tab.c"
    break;

  case 128: /* proc_args: $@27 ABRE_PARENTESES lista_expressoes_opcional FECHA_PARENTESES  */
#line 1095 "compilador.y"
                                {
					//printf("FIM ARGS\n\n\n");
					param_index = 0;
					proc_call = 0;
				}
#line 2571 "compilador.tab.c"
    break;

  case 129: /* chamada_funcao: proc_args  */
#line 1105 "compilador.y"
                        {
				//printf("func_call_ident: %s\n", func_call_ident);
				//printf("l_elem: %s\n\n\n", l_elem);
				Token_Node *t = searchTokenStack(s, func_call_ident);

				

				char *temp_chpr = malloc(sizeof(char) * 100);
				//printf("CHAMANDO FUNCAO\n\n\n\n");
				sprintf(temp_chpr, "CHPR %s, %d", t->data->label, n_lexico);
				geraCodigo(NULL, temp_chpr);

				//free(l_elem);
				free(temp_chpr);
			}
#line 2591 "compilador.tab.c"
    break;


#line 2595 "compilador.tab.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1129 "compilador.y"


int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   s = newTokenStack();
   l = newLabelStack();
   types = newTypeStack();

   op_relacao = newOpStack();
   op_expressao = newOpStack();
   op_fatores = newOpStack();

   yyin=fp;
   yyparse();

   return 0;
}
