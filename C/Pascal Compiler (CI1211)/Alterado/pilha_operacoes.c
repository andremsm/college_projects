#include "pilha_operacoes.h"

Op_Stack *newOpStack()
{
	Op_Stack *s = (Op_Stack *)malloc(sizeof(Op_Stack));
	s->top = NULL;
	s->size = 0;
	//{NULL, 0};
	return s;
}

Op *newOp(int op_id, char *ident)
{
	Op *o = (Op *)malloc(sizeof(Op));
	o->op = op_id;
	return o;
}

void pushOp(Op_Stack *s, int op)
{
	Op *o = (Op *)malloc(sizeof(Op));
	o->op = op;

	Op_Node *n = (Op_Node *)malloc(sizeof(Op_Node));
	n->data = o;
	// strcpy(n->data, data);
	//  n->data = data;
	s->size++;

	if (s->top == NULL)
		n->next = NULL;
	else
		n->next = s->top;

	s->top = n;
}

int popOp(Op_Stack *s)
{
	if (s->size == 0)
	{
		printf("Empty stack.\n");
		return -1;
	}
	s->size--;
	Op_Node *top = s->top;
	s->top = s->top->next;
	return top->data->op;
}

void freeOp(Op *s) {}
void freeOpNode(Op_Node *n) {}
/*
void testOps()
{
	printf("testing ops...\n");
	Op_Stack *stack = newOpStack();
	for (int i = 0; i < 100; i++)
	{
		Op *temp = newOp(i, "p");
		pushOp(stack, temp);
	}

	Op_Node *printer = popOp(stack);
	while (printer != NULL)
	{
		printf("%s ", printer->data->op);
		printer = popOp(stack);
	}
	printf("\n");
}

void printOpStack(Op_Stack *s)
{
	if (s->size > 0)
	{
		Op_Node *n = s->top;
		printf("Stack: [\n");
		for (int i = 0; i < s->size - 1; i++)
		{
			printf("\t(%s, %d, %s, %d),\n", n->data->op, n->data->op_id, n->data->ident, n->data->n_lex);
			n = n->next;
		}
		printf("\t(%s, %d, %s, %d)\n", n->data->op, n->data->op_id, n->data->ident, n->data->n_lex);
		printf("]\n");
	}
	else
		printf("Stack: []\t(Empty stack)\n");
}
*/