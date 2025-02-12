#include <stdio.h>
#include <stdlib.h>

typedef struct posicao{
	int i;
	int j;
}posicao_t;

void calculaFronteira(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas]);

void recalcularRecursivo(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas], int i, int j, int direcao);

int tamCor(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas], int i, int j, int direcao, int cor);

void desvisitar (int linhas, int colunas, int visitado[linhas][colunas]);

void recalculaJogo(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas]);

void flood(int cor, int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas]);

void imprimeMapa(int linhas, int colunas, int mapa[linhas][colunas]);

int verificaFronteira(int linhas, int colunas, int fronteira[linhas][colunas]);

posicao_t proximo(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas]);