#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iso646.h>

typedef struct Type
{
	int type_id; // Número do type
    int orig_type_id;
	char *orig_type; 
	char *ident;  // Qual identificador criou o type
	int n_lex;	  // Nível léxico

} Type;

typedef struct Type_Node
{
	Type *data;			 // Informações do nodo
	struct Type_Node *next; // Próximo nodo
} Type_Node;

typedef struct Type_Stack
{
	Type_Node *top;
	int size;
} Type_Stack;

/**
 * @brief Cria uma nova pilha de rótulos
 *
 * @return Type_Stack*
 */
Type_Stack *newTypeStack();

/**
 * @brief Cria um novo rótulo
 *
 * @param type_id Número do type
 * @return Type*
 */
Type *newType(int type_id, char *ident, int orig_type_id, char *orig_type);

void pushType(Type_Stack *s, Type *data);

Type_Node *popType(Type_Stack *s);

Type_Node *getType(Type_Stack *s, char *ident);
Type_Node *getTypeRecursion(Type_Node *n, char *ident);

Type_Node *getTypeByID(Type_Stack *s, int ident);
Type_Node *getTypeByIDRecursion(Type_Node *n, int ident);

void freeType(Type *s);
void freeTypeNode(Type_Node *n);