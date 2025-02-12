#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iso646.h>

typedef struct Label
{
	int label_id; // Número do label
	char *label;  // Label em formato de string (ex: R00, R01, R02...)
	char *ident;  // Qual identificador criou o label
	int n_lex;	  // Nível léxico

} Label;

typedef struct Label_Node
{
	Label *data;			 // Informações do nodo
	struct Label_Node *next; // Próximo nodo
} Label_Node;

typedef struct Label_Stack
{
	Label_Node *top;
	int size;
} Label_Stack;

/**
 * @brief Cria uma nova pilha de rótulos
 *
 * @return Label_Stack*
 */
Label_Stack *newLabelStack();

/**
 * @brief Cria um novo rótulo
 *
 * @param label_id Número do label
 * @return Label*
 */
Label *newLabel(int label_id, char *ident);

void pushLabel(Label_Stack *s, Label *data);

Label_Node *popLabel(Label_Stack *s);

void freeLabel(Label *s);
void freeLabelNode(Label_Node *n);