
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.

// André Miguel Sikora Marques


%{
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

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO NUMERO
%token CMP_IGUAL CMP_DIFF CMP_MENOR CMP_MENOR_IGUAL CMP_MAIOR_IGUAL CMP_MAIOR
%token MAIS MENOS OR MULT DIV AND NOT
%token WHILE DO
%token IF THEN ELSE
%token PROCEDURE FUNCTION
%token READ WRITE
%token TYPE

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

programa    :
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
			PROGRAM IDENT
			ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
			bloco PONTO {
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
;

bloco       :
			parte_declara_tipos
            parte_declara_vars
            {
            }
			  
			parte_declara_subrotinas
            comando_composto
			{
				if (s->top != NULL)
					if (!strcmp(s->top->data->cat, "PROC"))
						popToken(s);
			}
            ;

parte_declara_tipos :
	parte_declara_tipos definicao_tipo PONTO_E_VIRGULA |
	TYPE definicao_tipo PONTO_E_VIRGULA |
;

definicao_tipo:
	IDENT 
	{
		temp_type = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(temp_type, token);
	}
	CMP_IGUAL
	IDENT
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
;


parte_declara_vars:  var {deslocamento = 0;} |
;

parte_declara_subrotinas:	{n_procedimentos = 0;}
							declara_subrotinas 
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
							} |
;

declara_subrotinas: declara_subrotinas declaracao_procedimento | 
					declaracao_procedimento |
					declara_subrotinas declaracao_funcao |
					declaracao_funcao
;

declaracao_funcao: 	FUNCTION IDENT
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
					parametros_formais_opc
					DOIS_PONTOS IDENT
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
					PONTO_E_VIRGULA
					bloco
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

					} pv_opc
;

declaracao_procedimento:	PROCEDURE IDENT 
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
							parametros_formais_opc 
							PONTO_E_VIRGULA bloco
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

							} pv_opc
;

parametros_formais_opc: ABRE_PARENTESES parametros_formais
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
						} FECHA_PARENTESES |
;

parametros_formais: parametros_formais 
					PONTO_E_VIRGULA 
					secao_parametros_formais |
					secao_parametros_formais
;

secao_parametros_formais:	var_opc lista_idents DOIS_PONTOS IDENT
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
							} |
							FUNCTION lista_idents DOIS_PONTOS IDENT |
							PROCEDURE lista_idents
;

var_opc: VAR {is_ref = 1;} |
;

var         : var {num_vars = 0; } VAR declara_vars |
				{num_vars = 0; } VAR declara_vars	|
				
;

declara_vars: declara_vars declara_var
            | declara_var
;

declara_var : { }
              lista_id_var DOIS_PONTOS
              tipo
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
              PONTO_E_VIRGULA
;

tipo        : IDENT
;

lista_id_var: lista_id_var VIRGULA IDENT
              { /* insere �ltima vars na tabela de s�mbolos */
			  Token *new_token = newVar(token, "VS", n_lexico, "", deslocamento);
			  pushToken(s, new_token);
			  num_vars++;
			  deslocamento++;
			   }
            | IDENT { /* insere vars na tabela de s�mbolos */
			Token *new_token = newVar(token, "VS", n_lexico, "", deslocamento);
			pushToken(s, new_token);
			num_vars++;
			deslocamento++;
			}
;

lista_idents: 	lista_idents VIRGULA IDENT 
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
            | IDENT 
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
;


comando_composto: T_BEGIN comandos T_END |
				  T_BEGIN comandos PONTO_E_VIRGULA T_END |
				  T_BEGIN T_END



comandos: comandos pv_opc comando | comando
;

comando: rot_goto comando_sem_rotulo
;

comando_sem_rotulo: fatoracao |
					comando_repetitivo |
					comando_composto |
					comando_condicional |
					WRITE ABRE_PARENTESES escrita FECHA_PARENTESES |
					READ ABRE_PARENTESES leitura FECHA_PARENTESES
;

fatoracao:  {
				l_elem = malloc(sizeof(char) * (strlen(token) + 1));
				strcpy(l_elem, token);
			}
			IDENT fatoracao_continua
;

fatoracao_continua:	atribuicao {/*printTokenStack(s);*/} | 
					chamada_procedimento {/*printTokenStack(s);*/} 
;

comando_condicional: IF expressao 
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
					} THEN comando_sem_rotulo pv_opc 
					%prec LOWER_THAN_ELSE
					{
						Label_Node *node = l->top;
						char *temp_rotulo = malloc(sizeof(char) * 100);
						sprintf(temp_rotulo, "DSVS %s", node->data->label);

						geraCodigo(NULL, temp_rotulo);

						node = l->top->next;
						//sprintf(temp_rotulo, "%s: NADA", node->data->label);

						geraCodigo(node->data->label, "NADA");

						free(temp_rotulo);
					} else_opc
					{
						Label_Node *node = l->top;
						char *temp_rotulo = malloc(sizeof(char) * 100);
						//sprintf(temp_rotulo, "%s: NADA", node->data->label);

						geraCodigo(node->data->label, "NADA");

						free(temp_rotulo);
						free(popLabel(l));
						free(popLabel(l));
					}
;

pv_opc: PONTO_E_VIRGULA |
;

else_opc: ELSE comando_sem_rotulo |
;

atribuicao: {
				//printf("=====|%s|=====", l_elem);
			}
			ATRIBUICAO expressao 
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
;

chamada_procedimento: 	
			{
				func_call_ident = malloc(sizeof(char) * (strlen(l_elem) + 1));
				strcpy(func_call_ident, l_elem);
			}
			proc_args_opc 
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
;

proc_args_opc: 	{
					proc_call = 1;
				} 
				ABRE_PARENTESES lista_expressoes_opcional FECHA_PARENTESES
				{
					param_index = 0;
					proc_call = 0;
				} |
;

comando_repetitivo: WHILE 
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
					expressao DO 
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
					comando_sem_rotulo
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
;

//variavel: IDENT lista_expressoes_opcional
//;

lista_expressoes_opcional:	lista_expressoes |
;

lista_expressoes:	lista_expressoes VIRGULA {param_index++;} expressao | 
					expressao
;

leitura: leitura VIRGULA IDENT 
		{
			geraCodigo(NULL, "LEIT");

			Token_Node *t = searchTokenStack(s, token);
			char *temp_armz = malloc(sizeof(char) * 100);
			sprintf(temp_armz, "ARMZ %d, %d", t->data->level, t->data->shift);
			geraCodigo(NULL, temp_armz);
			free(temp_armz);
		} |
		IDENT 
		{
			geraCodigo(NULL, "LEIT");

			Token_Node *t = searchTokenStack(s, token);
			char *temp_armz = malloc(sizeof(char) * 100);
			sprintf(temp_armz, "ARMZ %d, %d", t->data->level, t->data->shift);
			geraCodigo(NULL, temp_armz);
			free(temp_armz);
		}
;

escrita:	escrita VIRGULA expressao {geraCodigo(NULL, "IMPR");} |
			expressao {geraCodigo(NULL, "IMPR");}
;

//lista_expressoes_opcional:	lista_expressoes_opcional VIRGULA expressao |
//							expressao
//;

expressao: expressao_simples relacao_expressao_simples 
	{
		//printf("expressão: %d %d\n\n\n", $1, $2);
		$$ = $1;
		tipo_fator = $1;
		if ($2 != -1){
			//if ($1 != $2){
			//	printf("error? %d %d\n\n", $1, $2);
			//	exit(0);
			//}
			$$ = $2;
			tipo_fator = $2;
		}

	}
;

relacao_expressao_simples: relacao expressao_simples
	{
		if ($2 != 1){
			if ($2 < 3)
				imprimeErro("Expressão simples entre tipos incompatíveis");
			else if (getTypeByID(types, $2)->data->orig_type_id != 1)
				imprimeErro("Expressão simples entre tipos incompatíveis");
				//printf("error: $2 == %d\n", $2);
				//printf("       $1 == %d\n\n", $1);
				//exit(-1);
		}

		//printf("relação expressão simples:: %d\n\n", $1);
		$$ = $1;

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
	 | {$$ = -1;}
;

relacao: CMP_IGUAL 
		{
			op_bool = 1;
			pushOp(op_relacao, 1);
			$$ = 2;
		} |
		CMP_DIFF 
		{
			op_bool = 2;
			pushOp(op_relacao, 2);
			$$ = 2;
		} |
		CMP_MENOR 
		{
			op_bool = 3;
			pushOp(op_relacao, 3);
			$$ = 2;
		} |
		CMP_MENOR_IGUAL 
		{
			op_bool = 4;
			pushOp(op_relacao, 4);
			$$ = 2;
		} |
		CMP_MAIOR_IGUAL 
		{
			op_bool = 5;
			pushOp(op_relacao, 5);
			$$ = 2;
		} |
		CMP_MAIOR 
		{
			op_bool = 6;
			pushOp(op_relacao, 6);
			$$ = 2;
		} 
;

expressao_simples: expressao_simples pos_neg_or termo 
	{
		if ($3 != $2){
			printf("error\n\n\n");
			exit(0);
		}
		//printf("expressão simples: %d\n\n", $3);
		$$ = $3;

		op_termo = popOp(op_expressao);
		
		if (op_termo == 1)
			geraCodigo(NULL, "SOMA");
		else if (op_termo == 2)
			geraCodigo(NULL, "SUBT");
		else if (op_termo == 3)
			geraCodigo(NULL, "OR");
		op_termo = 0;
	} | pos_neg_opc termo {$$ = $2; /*printf("termo $2: %d\n\n", $2);*/}
	
;

pos_neg_opc: pos_neg |
;

pos_neg: MAIS | MENOS
;

pos_neg_or: MAIS 
			{
				op_termo = 1;
				pushOp(op_expressao, 1);
				$$ = 1;
			} | 
			MENOS 
			{
				op_termo = 2;
				pushOp(op_expressao, 2);
				$$ = 1;
			} | 
			OR 
			{
				op_termo = 3;
				pushOp(op_expressao, 3);
				$$ = 2;
			}
;

termo: termo mult_div_and fator 
	{
		//printf("termo * fator: %d %d\n\n", $1, $3);
		if ($3 != $2){
			printf("error\n\n\n");
			exit(0);
		}
		$$ = $3;

		op_fator = popOp(op_fatores);

		if (op_fator == 1)
			geraCodigo(NULL, "MULT");
		else if (op_fator == 2)
			geraCodigo(NULL, "DIVI");
		else if (op_fator == 3)
			geraCodigo(NULL, "CONJ");
		op_fator = 0;
	} | fator {$$ = $1; /*printf("fator: %d\n\n\n", $1);*/}
;

mult_div_and: 
	MULT 
	{
		op_fator = 1;
		pushOp(op_fatores, 1);
		$$ = 1;
	} | 
	DIV 
	{
		op_fator = 2;
		pushOp(op_fatores, 2);
		$$ = 1;
	} | 
	AND 
	{
		op_fator = 3;
		pushOp(op_fatores, 3);
		$$ = 2;
	}
;

fator:	variavel_funcao {$$ = $1; /*printf("$1: %d\n\n", $1);*/} |
		NUMERO	
		{
			tipo_fator = 1;
			$$ = 1;

			char *temp_crct = malloc(sizeof(char) * 100);
			sprintf(temp_crct, "CRCT %s", token);
			geraCodigo(NULL, temp_crct);
			free(temp_crct);
		}	|
		ABRE_PARENTESES expressao FECHA_PARENTESES {$$ = $2;} |
		NOT fator
;

variavel_funcao:
	{
		temp_ident = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(temp_ident, token);
		
		//func_call_ident = malloc(sizeof(char) * (strlen(token) + 1));
		//strcpy(func_call_ident, token);
	}
	IDENT	
	{
		Token_Node *t = searchTokenStack(s, token);
		char *temp_crvl = malloc(sizeof(char) * 100);

		if (!strcmp(t->data->type, "int")){
			tipo_fator = 1;
			$$ = 1;
			$1= 1;	// WHYYYYYYYY?????
			//printf("\nis_int\n\n");
		}
		else if (!strcmp(t->data->type, "bool")){
			tipo_fator = 2;
			$$ = 2;
			$1 = 2;	// WHYYYYYYYY?????
		}
		else{
			Type_Node *n = getType(types, t->data->type);
			//printf("\t(%d, %s, %d, %s),\n", n->data->type_id, n->data->ident, n->data->orig_type_id, n->data->orig_type);
			tipo_fator = n->data->type_id;
			$$ = tipo_fator;
			$1 = tipo_fator;
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
	funcao_opc
	{
	//	if (strlen(func_call_ident) > 0)
	//		free(func_call_ident);
	}
;

funcao_opc:	
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
	chamada_funcao |
;

proc_args:	{
					proc_call = 1;
				} 
				ABRE_PARENTESES lista_expressoes_opcional FECHA_PARENTESES
				{
					//printf("FIM ARGS\n\n\n");
					param_index = 0;
					proc_call = 0;
				}
;

chamada_funcao: 	
			
			proc_args 
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
;

rot_goto:	numero DOIS_PONTOS |
;

numero: numero NUMERO |
		NUMERO
;

%%

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
