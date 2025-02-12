#include "pilha_tipos.h"

Type_Stack *newTypeStack()
{
    Type_Stack *s = (Type_Stack *)malloc(sizeof(Type_Stack));
    s->top = NULL;
    s->size = 0;
    //{NULL, 0};
    return s;
}

Type *newType(int type_id, char *ident, int orig_type_id, char *orig_type)
{
    Type *l = (Type *)malloc(sizeof(Type));

    l->type_id = type_id;
    l->orig_type_id = orig_type_id;

    l->orig_type = (char *)malloc(sizeof(char) * (strlen(orig_type) + 1));
    strcpy(l->orig_type, orig_type);

    l->ident = (char *)malloc(sizeof(char) * (strlen(ident) + 1));
    strcpy(l->ident, ident);

    // l->n_lex = n_lex;
    return l;
}

void pushType(Type_Stack *s, Type *data)
{
    Type_Node *n = (Type_Node *)malloc(sizeof(Type_Node));
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

Type_Node *popType(Type_Stack *s)
{
    if (s->size == 0)
    {
        printf("Empty stack.\n");
        return NULL;
    }
    s->size--;
    Type_Node *top = s->top;
    s->top = s->top->next;
    return top;
}

Type_Node *getType(Type_Stack *s, char *ident)
{
    if (s->size > 0)
        return getTypeRecursion(s->top, ident);
    else
        return NULL;
}

Type_Node *getTypeRecursion(Type_Node *n, char *ident)
{
    if (n->next != NULL and strcmp(n->data->ident, ident))
        return getTypeRecursion(n->next, ident);
    else if (!strcmp(n->data->ident, ident))
        return n;
    else
        return NULL;
    // if (!strcmp(n->data, ident))
}

Type_Node *getTypeByID(Type_Stack *s, int ident)
{
    if (s->size > 0)
        return getTypeByIDRecursion(s->top, ident);
    else
        return NULL;
}

Type_Node *getTypeByIDRecursion(Type_Node *n, int ident)
{
    if (n->next != NULL and n->data->type_id != ident)
        return getTypeByIDRecursion(n->next, ident);
    else if (n->data->type_id == ident)
        return n;
    else
        return NULL;
    // if (!strcmp(n->data, ident))
}

void freeType(Type *s) {}
void freeTypeNode(Type_Node *n) {}

/*
void testTypes()
{
    printf("testing types...\n");
    Type_Stack *stack = newTypeStack();
    for (int i = 0; i < 100; i++)
    {
        Type *temp = newType(i, "p");
        pushType(stack, temp);
    }

    Type_Node *printer = popType(stack);
    while (printer != NULL)
    {
        printf("%s ", printer->data->type);
        printer = popType(stack);
    }
    printf("\n");
}
*/
void printTypeStack(Type_Stack *s)
{
    if (s->size > 0)
    {
        Type_Node *n = s->top;
        printf("Stack: [\n");
        for (int i = 0; i < s->size - 1; i++)
        {
            printf("\t(%d, %s, %d, %s),\n", n->data->type_id, n->data->ident, n->data->orig_type_id, n->data->orig_type);
            n = n->next;
        }
        printf("\t(%d, %s, %d, %s)\n", n->data->type_id, n->data->ident, n->data->orig_type_id, n->data->orig_type);
        printf("]\n");
    }
    else
        printf("Stack: []\t(Empty stack)\n");
}
