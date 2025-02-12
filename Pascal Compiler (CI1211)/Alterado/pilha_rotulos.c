#include "pilha_rotulos.h"

Label_Stack *newLabelStack()
{
	Label_Stack *s = (Label_Stack *)malloc(sizeof(Label_Stack));
	s->top = NULL;
	s->size = 0;
	//{NULL, 0};
	return s;
}

Label *newLabel(int label_id, char *ident)
{
	Label *l = (Label *)malloc(sizeof(Label));
	l->label_id = label_id;
	l->label = (char *)malloc(sizeof(char) * (strlen("R00") + 1));
	sprintf(l->label, "R%02d", label_id);
	l->ident = (char *)malloc(sizeof(char) * (strlen(ident) + 1));
	strcpy(l->ident, ident);
	// l->n_lex = n_lex;
	return l;
}

void pushLabel(Label_Stack *s, Label *data)
{
	Label_Node *n = (Label_Node *)malloc(sizeof(Label_Node));
	n->data = data;
	// strcpy(n->data, data);
	//  n->data = data;
	s->size++;

	if (s->top == NULL)
		n->next = NULL;
	else
		n->next = s->top;

	s->top = n;
}

Label_Node *popLabel(Label_Stack *s)
{
	if (s->size == 0)
	{
		printf("Empty stack.\n");
		return NULL;
	}
	s->size--;
	Label_Node *top = s->top;
	s->top = s->top->next;
	return top;
}

void freeLabel(Label *s) {}
void freeLabelNode(Label_Node *n) {}

void testLabels()
{
	printf("testing labels...\n");
	Label_Stack *stack = newLabelStack();
	for (int i = 0; i < 100; i++)
	{
		Label *temp = newLabel(i, "p");
		pushLabel(stack, temp);
	}

	Label_Node *printer = popLabel(stack);
	while (printer != NULL)
	{
		printf("%s ", printer->data->label);
		printer = popLabel(stack);
	}
	printf("\n");
}

void printLabelStack(Label_Stack *s)
{
	if (s->size > 0)
	{
		Label_Node *n = s->top;
		printf("Stack: [\n");
		for (int i = 0; i < s->size - 1; i++)
		{
			printf("\t(%s, %d, %s, %d),\n", n->data->label, n->data->label_id, n->data->ident, n->data->n_lex);
			n = n->next;
		}
		printf("\t(%s, %d, %s, %d)\n", n->data->label, n->data->label_id, n->data->ident, n->data->n_lex);
		printf("]\n");
	}
	else
		printf("Stack: []\t(Empty stack)\n");
}