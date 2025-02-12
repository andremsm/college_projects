#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iso646.h>

typedef struct Op
{
	int op; // Operação
} Op;

typedef struct Op_Node
{
	Op *data;			  // Informações do nodo
	struct Op_Node *next; // Próximo nodo
} Op_Node;

typedef struct Op_Stack
{
	Op_Node *top;
	int size;
} Op_Stack;

/**
 * @brief Cria uma nova pilha de operações
 *
 * @return Op_Stack*
 */
Op_Stack *newOpStack();

/**
 * @brief Cria uma nova operação
 *
 * @param op_id Número da operação
 * @return Op*
 */
void pushOp(Op_Stack *s, int op);

int popOp(Op_Stack *s);

void freeOp(Op *s);
void freeOpNode(Op_Node *n);