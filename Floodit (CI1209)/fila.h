#include <stdio.h>
#include <stdlib.h>

typedef struct no_t {
	int dado;
	int tamanho;
	struct no_t* prox;
} no_t;

typedef struct fila_t {
	int tam;
	struct no_t* inicio;
	struct no_t* fim;
} fila_t;

fila_t *inicializaFila ();

void insereFila (fila_t *F, int x, int tam);

int desenfileira (fila_t *F);