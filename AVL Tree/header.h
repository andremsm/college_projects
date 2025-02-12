#ifndef __header__
#define __header__
#include <stdio.h>
#include <stdlib.h>

struct No {
	struct No *dir;
	struct No *esq;
	struct No *pai;
	int altura;
	int chave;
};

struct No *criaNo (int chave);

int altura (struct No *N);

int balanceamento (struct No *N);

void emOrdem (struct No *N, int altura);

struct No *rotacaoDir (struct No *N);

struct No *rotacaoEsq (struct No *N);

struct No *insereNo (struct No *N, int chave);

struct No *encontrarRaiz (struct No *N);

void ajustaPai (struct No *N, struct No *novo);

struct No *max (struct No *N);

struct No *antecessor (struct No *N);

struct No *removeNo (struct No *N);

struct No *balancearEmOrdem (struct No *N);

struct No *buscaParaRemover (struct No *N, int i);

#endif


