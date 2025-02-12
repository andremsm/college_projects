#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

fila_t *inicializaFila (){
	fila_t *F = (fila_t *) malloc (sizeof(fila_t));
	F->tam = 0;
	F->inicio = NULL;
	F->fim = NULL;
	return F;
}

void insereFila (fila_t *F, int x, int tam){
	no_t *N;
	N = (no_t *) malloc (sizeof(no_t));
	
	if (F->inicio == NULL){
		N->prox = NULL;
		F->inicio = N;
		F->fim = N;
		F->inicio->dado = x;
		F->inicio->tamanho = tam;
		F->tam++;
		return;
	}
	
	N->prox = NULL;
	F->fim->prox = N;
	F->fim = N;
	F->fim->dado = x;
	F->fim->tamanho = tam;
	F->tam++;
	return;
	
}

int desenfileira (fila_t *F){
	if (F->inicio == NULL) return -1;
	
	no_t *temp = F->inicio;
	int x = temp->dado;
	F->inicio = F->inicio->prox;
	F->tam--;
	free (temp);
	return x;
}