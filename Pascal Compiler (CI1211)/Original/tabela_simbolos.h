#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iso646.h>
/**
 * @brief Tipo e mecanismo de passagem do parâmetro formal
 * @note ```type``` – Tipo
 * @note ```mech``` – Mecanismo
 */
typedef struct Formal_Parameter
{
	char *type; // Tipo
	char *mech; // Mecanismo
} Formal_Parameter;

/**
 * @brief Símbolo. Pode ser Variável simples, Parâmetro formal, ou procedimento
 *
 * @note Comum a todos:
 * @note ```ident``` – Identificador
 * @note ```cat``` – Categoria
 * @note ```level``` – Nível
 *
 * @note Variável simples e parâmetro formal:
 * @note ```type``` – Tipo
 * @note ```shift``` – Deslocamento
 *
 * @note Parâmetro formal:
 * @note ```pass``` – Passagem
 *
 * @note Procedimento:
 * @note ```label``` – Rótulo
 * @note ```n_params``` – Número de parâmetros formais
 * @note ```formal_params``` – Lista de parâmetros formais
 */
typedef struct Token
{
	// Atributos Comuns
	char *ident; // Identificador
	char *cat;	 // Categoria
	int level;	 // Nível

	// Variável simples e parâmetro formal
	char *type; // Tipo
	int shift;	// Deslocamento

	// Parâmetro formal
	char *pass; // Passagem

	// Procedimento
	char *label;					 // Rótulo
	int n_params;					 // Número de parâmetros formais
	Formal_Parameter *formal_params; // Parâmetros formais

} Token;

/**
 * @brief Nodo da pilha de símbolos
 * @note ```data``` – Símbolo que contém as informações do nodo
 * @note ```next``` – Próximo nodo
 */
typedef struct Token_Node
{
	Token *data;			 // Informações do nodo
	struct Token_Node *next; // Próximo nodo
} Token_Node;

/**
 * @brief Pilha de símbolos
 * @note ```top``` – Nodo que está no topo da pilha
 * @note ```size``` – Número de nodos na pilha
 */
typedef struct Token_Stack
{
	Token_Node *top;
	int size;
} Token_Stack;

/**
 * @brief Cria uma nova pilha de símbolos
 *
 * @return Token_Stack*
 */
Token_Stack *newTokenStack();

/**
 * @brief Cria um novo símbolo da categoria variável simples
 *
 * @param ident Identificador
 * @param cat Categoria
 * @param level Nível
 * @param type Tipo
 * @param shift Deslocamento
 * @return Token*
 */
Token *newVar(char *ident, char *cat, int level, char *type, int shift);
/**
 * @brief Cria um novo símbolo da categoria parâmetro formal
 *
 * @param ident Identificador
 * @param cat Categoria
 * @param level Nível
 * @param type Tipo
 * @param shift Deslocamento
 * @param pass Passagem
 * @return Token*
 */
Token *newFP(char *ident, char *cat, int level, char *type, int shift, char *pass);
/**
 * @brief Cria um novo símbolo da categoria procedimento
 *
 * @param ident Identificador
 * @param cat Categoria
 * @param level Nível
 * @param label Rótulo
 * @param n_params Número de parâmetros formais
 * @param formal_params Lista de parâmetros formais
 * @return Token*
 */
Token *newProc(char *ident, char *cat, int level, char *label, int n_params, Formal_Parameter *formal_params);

// obsoleto
Token *newToken(char *cat, char *ident, int level, int shift, char *type);

void pushToken(Token_Stack *s, Token *data);
Token_Node *popToken(Token_Stack *s);

void printTokenStack(Token_Stack *s);

void freeToken(Token *s);
void freeTokenNode(Token_Node *n);

Token_Node *searchTokenStack(Token_Stack *s, char *ident);
Token_Node *searchRecursion(Token_Node *n, char *ident);

int getNParams(Token_Stack *s);
Token_Node *getNParamsRecursion(Token_Node *t);
Formal_Parameter *getParams(Token_Stack *s);
Formal_Parameter *getParamsRecursion(Token_Node *t, int n_params);
void updateProcParams(Token_Stack *s);