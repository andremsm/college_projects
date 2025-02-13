#include "tabela_simbolos.h"

Token_Stack *newTokenStack()
{
	Token_Stack *s = (Token_Stack *)malloc(sizeof(Token_Stack));
	s->top = NULL;
	s->size = 0;
	//{NULL, 0};
	return s;
}

Token *newToken(char *cat, char *ident, int level, int shift, char *type)
{
	Token *s = (Token *)malloc(sizeof(Token));
	s->cat = (char *)malloc(sizeof(char) * (strlen(cat) + 1));
	strcpy(s->cat, cat);
	s->ident = (char *)malloc(sizeof(char) * (strlen(ident) + 1));
	strcpy(s->ident, ident);
	s->level = level;
	s->shift = shift;
	s->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));
	strcpy(s->type, type);
	return s;
}

Token *newVar(char *ident, char *cat, int level, char *type, int shift)
{
	Token *s = (Token *)malloc(sizeof(Token));

	s->ident = (char *)malloc(sizeof(char) * (strlen(ident) + 1));
	s->cat = (char *)malloc(sizeof(char) * (strlen(cat) + 1));
	s->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));

	strcpy(s->ident, ident);
	strcpy(s->cat, cat);
	s->level = level;
	strcpy(s->type, type);
	s->shift = shift;

	return s;
}

Token *newFP(char *ident, char *cat, int level, char *type, int shift, char *pass)
{
	Token *s = (Token *)malloc(sizeof(Token));

	s->ident = (char *)malloc(sizeof(char) * (strlen(ident) + 1));
	s->cat = (char *)malloc(sizeof(char) * (strlen(cat) + 1));
	s->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));
	s->pass = (char *)malloc(sizeof(char) * (strlen(pass) + 1));

	strcpy(s->ident, ident);
	strcpy(s->cat, cat);
	s->level = level;
	strcpy(s->type, type);
	s->shift = shift;
	strcpy(s->pass, pass);

	return s;
}

Token *newProc(char *ident, char *cat, int level, char *label, int n_params, Formal_Parameter *formal_params)
{
	Token *s = (Token *)malloc(sizeof(Token));

	s->ident = (char *)malloc(sizeof(char) * (strlen(ident) + 1));
	s->cat = (char *)malloc(sizeof(char) * (strlen(cat) + 1));
	s->label = (char *)malloc(sizeof(char) * (strlen(label) + 1));
	// s->formal_params = (Formal_Parameter *)malloc(sizeof(Formal_Parameter) * n_params);

	strcpy(s->ident, ident);
	strcpy(s->cat, cat);
	s->level = level;
	strcpy(s->label, label);
	s->n_params = n_params;

	return s;
}

Token *newFunc(
	char *ident,
	char *cat,
	char *label,
	int level,
	int shift,
	char *type,
	int n_params,
	Formal_Parameter *formal_params)
{
	Token *s = (Token *)malloc(sizeof(Token));

	s->ident = (char *)malloc(sizeof(char) * (strlen(ident) + 1));
	s->cat = (char *)malloc(sizeof(char) * (strlen(cat) + 1));
	s->label = (char *)malloc(sizeof(char) * (strlen(label) + 1));
	s->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));
	// s->formal_params = (Formal_Parameter *)malloc(sizeof(Formal_Parameter) * n_params);

	strcpy(s->ident, ident);
	strcpy(s->cat, cat);
	strcpy(s->label, label);
	strcpy(s->type, type);
	s->level = level;
	s->shift = shift;
	s->n_params = n_params;

	/*
	printf(
		"%s, %s, %s, %d, %d, %s, %d\n\n",
		s->ident, s->cat, s->label,
		s->level, s->shift,
		s->type,
		s->n_params);
		*/

	return s;
}

void pushToken(Token_Stack *s, Token *data)
{
	Token_Node *n = (Token_Node *)malloc(sizeof(Token_Node));
	n->data = data;
	// printf("%s\n", n->data->ident);
	//  strcpy(n->data, data);
	//   n->data = data;
	s->size++;

	if (s->top == NULL)
		n->next = NULL;
	else
		n->next = s->top;

	s->top = n;
}

Token_Node *popToken(Token_Stack *s)
{
	if (s->size == 0)
	{
		printf("Empty stack.\n");
		return NULL;
	}
	s->size--;
	// printf("Current top: %d\n", s->size);
	Token_Node *top = s->top;
	// if (s->top != NULL)
	//	printf("Current top: %s\n", s->top->data->ident);
	// if (s->top->next != NULL)
	//	printf("Next top:    %s\n", s->top->next->data->ident);
	//  Node *temp = s->top;
	//  printf("s->top = %s <=== s->top->next = %s\n", s->top->data->ident, s->top->next->data->ident);
	s->top = s->top->next;
	// printf("test_pop ");
	/*free(temp->data->cat);
	free(temp->data->ident);
	free(temp->data->shift);
	free(temp->data->type);
	free(temp->data);
	free(temp);*/
	return top;
}

void printTokenStack(Token_Stack *s)
{
	if (s->size > 0)
	{
		Token_Node *n = s->top;
		printf("Stack: [\n");
		for (int i = 0; i < s->size - 1; i++)
		{
			printf(
				"\t(%s, %s, %s, %d, %d, %d, %s),\n",
				n->data->ident, n->data->cat, n->data->label,
				n->data->level, n->data->shift,
				n->data->n_params, n->data->type);
			n = n->next;
		}
		printf(
			"\t(%s, %s, %s, %d, %d, %d, %s)\n",
			n->data->ident, n->data->cat, n->data->label,
			n->data->level, n->data->shift,
			n->data->n_params, n->data->type);
		printf("]\n");
	}
	else
		printf("Stack: []\t(Empty stack)\n");
}

void freeToken(Token *s)
{
	if (s == NULL)
	{
		printf("Error: NULL\n");
		return;
	}
	free(s->cat);
	free(s->ident);
	free(s->type);
	free(s);
}

void freeTokenNode(Token_Node *n)
{
	if (n == NULL)
	{
		printf("Error: NULL\n");
		return;
	}
	freeToken(n->data);
	free(n);
}

Token_Node *searchTokenStack(Token_Stack *s, char *ident)
{
	if (s->size > 0)
		return searchRecursion(s->top, ident);
	else
		return NULL;
}

void removeTokens(Token_Stack *s, int n)
{
	for (int i = 0; i < n; i++)
		popToken(s);
	s->size -= n;
}

Token_Node *searchRecursion(Token_Node *n, char *ident)
{
	if (n->next != NULL and strcmp(n->data->ident, ident))
		return searchRecursion(n->next, ident);
	else if (!strcmp(n->data->ident, ident))
		return n;
	else
		return NULL;
	// if (!strcmp(n->data, ident))
}

int getNParams(Token_Stack *s)
{
	if (s->size > 0)
	{
		if (!strcmp(s->top->data->type, "PF"))
			return -1;
		return getNParamsRecursion(s->top)->data->n_params;
	}
	else
		return -1;
}

Token_Node *getNParamsRecursion(Token_Node *t)
{
	if (!strcmp(t->data->cat, "PF"))
		return getNParamsRecursion(t->next);
	else
		return t;
}

Formal_Parameter *getParams(Token_Stack *s)
{
	Token_Node *t = s->top;
	return getParamsRecursion(t, getNParams(s));
}

Formal_Parameter *getParamsRecursion(Token_Node *t, int n_params)
{
	if (strcmp(t->data->cat, "PF"))
	{
		Formal_Parameter *formal_params = malloc(sizeof(Formal_Parameter) * n_params);
		return formal_params;
	}
	// printf("%s %s %s %s\n", t->data->ident, t->data->cat, t->data->type, t->data->pass);
	Formal_Parameter formal_param = {t->data->type, t->data->pass};
	// printf("%s %s %d\n", formal_param.type, formal_param.mech, n_params - (abs(t->data->shift) - 4) - 1);
	Formal_Parameter *fp_list = getParamsRecursion(t->next, n_params);
	fp_list[n_params - (abs(t->data->shift) - 4) - 1] = formal_param;

	return fp_list;
}

void updateParams(Token_Stack *s)
{
	if (s->size > 0)
	{
		Token_Node *n = s->top;
		Formal_Parameter *fp_list = getParams(s);
		while (strcmp(n->data->cat, "PROC") and strcmp(n->data->cat, "FUNC"))
			n = n->next;
		n->data->formal_params = fp_list;

		/*
		printf("\n%s{\n", n->data->cat);
		for (int i = 0; i < n->data->n_params; i++)
		{
			printf("\t[type: %s, pass: %s]", n->data->formal_params[i].type, n->data->formal_params[i].mech);
		}
		printf("\n}\n");
		*/
	}
	else
		printf("Stack: []\t(Empty stack)\n");
}

void updateProcParams(Token_Stack *s)
{
	if (s->size > 0)
	{
		Token_Node *n = s->top;
		Formal_Parameter *fp_list = getParams(s);
		while (strcmp(n->data->cat, "PROC"))
			n = n->next;
		n->data->formal_params = fp_list;

		/*
		printf("\n%s{\n", n->data->cat);
		for (int i = 0; i < n->data->n_params; i++)
		{
			printf("\t[type: %s, pass: %s]", n->data->formal_params[i].type, n->data->formal_params[i].mech);
		}
		printf("\n}\n");
		printTokenStack(s);
		*/
	}
	else
		printf("Stack: []\t(Empty stack)\n");
}