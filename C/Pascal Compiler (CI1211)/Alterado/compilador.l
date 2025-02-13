
/* -------------------------------------------------------------------
 *            Arquivo: compilador.l
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [09/08/2020, 19h:01m]
 *
 * -------------------------------------------------------------------
 *
 * Tipos, protótipos e variáveis globais do compilador (via extern)
 *
 * ------------------------------------------------------------------- */

%{


#include<stdio.h>
#include<string.h>

#include "compilador.h"
#include "compilador.tab.h"

//#define IMPRIME(STR) {};
#define IMPRIME(STR) printf("%s    # %s \n", STR, token);

int nl = 1;

%}

pulo_linha [\n]

descarte [\t ]+

ident [a-zA-Z][a-zA-Z0-9]*

numero [0-9]+

comentario "(*".*"*)"

%%

{pulo_linha} {nl++;}

{descarte}

{comentario}

program { simbolo  = simb_program;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("program ");
          return PROGRAM;
 }

var      { simbolo = simb_var;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("var  ");
          return VAR;
 }

begin { simbolo = simb_begin;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("begin ");
          return T_BEGIN;
 }

end { simbolo = simb_end;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("end  ");
          return T_END;
 }

:= { simbolo = simb_atribuicao;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" atribuicao  ");
          return ATRIBUICAO;
 }

\; { simbolo = simb_ponto_e_virgula;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" pt_virgula  ");
          return PONTO_E_VIRGULA;
 }

\: { simbolo = simb_dois_pontos;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" dois pontos ");
          return DOIS_PONTOS;
 }

\, { simbolo = simb_virgula;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" virgula  ");
          return VIRGULA;
 }


\. { simbolo = simb_ponto;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" ponto  ");
          return PONTO;
    }

\(  { simbolo = simb_abre_parenteses;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" abre_parenteses  ");
          return ABRE_PARENTESES;
    }

\)  { simbolo = simb_fecha_parenteses;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" fecha_parenteses ");
          return FECHA_PARENTESES;
 }

div {
	simbolo = simb_div;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" div  ");
	return DIV;
}

or {
	simbolo = simb_or;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" or  ");
	return OR;
}

and {
	simbolo = simb_and;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" and  ");
	return AND;
}

not {
	simbolo = simb_not;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" not  ");
	return NOT;
}

while {
	simbolo = simb_while;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" while  ");
	return WHILE;
}

do {
	simbolo = simb_do;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" do  ");
	return DO;
}

if {
	simbolo = simb_if;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" if  ");
	return IF;
}

then {
	simbolo = simb_then;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" then  ");
	return THEN;
}

else {
	simbolo = simb_else;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" else  ");
	return ELSE;
}

procedure {
	simbolo = simb_procedure;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" procedure  ");
	return PROCEDURE;
}

function {
	simbolo = simb_function;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" function  ");
	return FUNCTION;
}

read {
	simbolo = simb_read;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" read  ");
	return READ;
}

write {
	simbolo = simb_write;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" write  ");
	return WRITE;
}

type {
	simbolo = simb_type;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" type  ");
	return TYPE;
}

{ident} { simbolo = simb_identificador;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" ident  ");
          return IDENT;
        }

{numero} {
		simbolo = simb_numero;
		strncpy (token, yytext, TAM_TOKEN);
		IMPRIME(" numero ");
		return NUMERO;

}

\= {
	simbolo = simb_cmp_igual;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" cmp_igual  ");
	return CMP_IGUAL;
}

\<> {
	simbolo = simb_cmp_diff;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" cmp_diff  ");
	return CMP_DIFF;
}

\< {
	simbolo = simb_cmp_menor;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" cmp_menor  ");
	return CMP_MENOR;
}

\<= {
	simbolo = simb_cmp_menor_igual;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" cmp_menor_igual  ");
	return CMP_MENOR_IGUAL;
}

\>= {
	simbolo = simb_cmp_maior_igual;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" cmp_maior_igual  ");
	return CMP_MAIOR_IGUAL;
}

\> {
	simbolo = simb_cmp_maior;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" cmp_maior  ");
	return CMP_MAIOR;
}

\+ {
	simbolo = simb_mais;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" mais  ");
	return MAIS;
}

\- {
	simbolo = simb_menos;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" menos  ");
	return MENOS;
}



\* {
	simbolo = simb_mult;
	strncpy (token, yytext, TAM_TOKEN);
	IMPRIME(" mult  ");
	return MULT;
}





%%
