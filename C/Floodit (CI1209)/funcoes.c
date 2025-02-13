#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include "fila.h"

void calculaFronteira(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas]){
	for (int i = 0; i < linhas; i++){
		for (int j = 0; j < colunas; j++){
			if (jogo[i][j] == 0 && jogo[i][j-1] != 0 && j > 0)
				fronteira[i][j] = 1;
			if (jogo[i][j] == 0 && jogo[i-1][j] != 0 && i > 0)
				fronteira[i][j] = 1;
			if (jogo[i][j] == 0 && jogo[i][j+1] != 0 && j < colunas - 1)
				fronteira[i][j] = 1;
			if (jogo[i][j] == 0 && jogo[i+1][j] != 0 && i < linhas - 1)
				fronteira[i][j] = 1;
			if (jogo[i][j] != 0 && fronteira[i][j] == 1)	//apaga marcações de fronteira dentro do jogo
				fronteira[i][j] = 0;
		}
	}
}

void recalcularRecursivo(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas], int i, int j, int direcao){
	//0 = esquerda, 1 = direita, 2 = cima, 3 = baixo
	//A matriz de visitados serve para o algoritmo não entrar em um loop que fica em um vai e volta entre duas recursões.
	visitado[i][j] = 1;
	if (j > 0)
		if (mapa[i][j] == mapa[i][j-1] && !visitado[i][j-1])
			recalcularRecursivo(linhas,colunas,fronteira,jogo,mapa,visitado,i,j-1,0);
	if (j < colunas)
		if (mapa[i][j] == mapa[i][j+1] && !visitado[i][j+1])
			recalcularRecursivo(linhas,colunas,fronteira,jogo,mapa,visitado,i,j+1,1);
	if (i > 0)
		if (mapa[i][j] == mapa[i-1][j] && !visitado[i-1][j])
			recalcularRecursivo(linhas,colunas,fronteira,jogo,mapa,visitado,i-1,j,2);
	if (i < linhas)
		if (mapa[i][j] == mapa[i+1][j] && !visitado[i+1][j])
			recalcularRecursivo(linhas,colunas,fronteira,jogo,mapa,visitado,i+1,j,3);
	
	if 		(direcao == 0 && j < colunas)
		jogo[i][j] = mapa[i][j+1];
	else if (direcao == 1 && j > 0)
		jogo[i][j] = mapa[i][j-1];
	else if (direcao == 2 && i < linhas)
		jogo[i][j] = mapa[i+1][j];
	else if (direcao == 3 && i > 0)
		jogo[i][j] = mapa[i-1][j];
	
	
	
}

int tamCor(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas], int i, int j, int direcao, int cor){
	//0 = esquerda, 1 = direita, 2 = cima, 3 = baixo
	//A matriz de visitados serve para o algoritmo não entrar em um loop que fica em um vai e volta entre duas recursões.
	visitado[i][j] = 1;
	int temp = 0;
	
	if (mapa[i][j] == cor && direcao == -1)
		temp++;
	
	if (j > 0)
		if (mapa[i][j-1] == cor && jogo[i][j-1] == 0 && !visitado[i][j-1])
			temp += 1 + tamCor(linhas,colunas,fronteira,jogo,mapa,visitado,i,j-1,0,cor);

	if (j < colunas)
		if (mapa[i][j+1] == cor && jogo[i][j+1] == 0 && !visitado[i][j+1])
			temp += 1 + tamCor(linhas,colunas,fronteira,jogo,mapa,visitado,i,j+1,1,cor);

	if (i > 0)
		if (mapa[i-1][j] == cor && jogo[i-1][j] == 0 && !visitado[i-1][j])
			temp += 1 + tamCor(linhas,colunas,fronteira,jogo,mapa,visitado,i-1,j,2,cor);

	if (i < linhas)
		if (mapa[i+1][j] == cor && jogo[i+1][j] == 0 && !visitado[i+1][j])
			temp += 1 + tamCor(linhas,colunas,fronteira,jogo,mapa,visitado,i+1,j,3,cor);

	
	return temp;
	
	
	
}

void desvisitar (int linhas, int colunas, int visitado[linhas][colunas]){
	for (int i = 0; i < linhas; i++)
		for (int j = 0; j < colunas; j++)
			visitado[i][j] = 0;
}

void recalculaJogo(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas]){
	//Chama a função recursiva a partir do primeiro elemento, para fazer a verificação de cada elemento do jogo. Em seguida arruma a fronteira, e reseta o visitado.
	recalcularRecursivo(linhas,colunas,fronteira,jogo,mapa,visitado,0,0,-1);
	calculaFronteira(linhas, colunas, fronteira, jogo);
	for (int i = 0; i < linhas; i++){
		for (int j = 0; j < colunas; j++){
			if (fronteira[i][j] == fronteira[i][j+1] && fronteira[i][j] == fronteira[i+1][j])
				fronteira[i][j] = 0;
			visitado[i][j] = 0;
		}
	}
}

void flood(int cor, int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas]){
	//Pinta todos os elementos do jogo da nova cor. Em seguida recalcula o jogo.
	for (int i = 0; i < linhas; i++){
		for (int j = 0; j < colunas; j++){
			if (jogo[i][j] != 0){
				jogo[i][j] = cor;
				mapa[i][j] = cor;
			}
		}
	}
	recalculaJogo(linhas, colunas, fronteira, jogo, mapa, visitado);
}

void imprimeMapa(int linhas, int colunas, int mapa[linhas][colunas]){
	for (int i = 0; i < linhas; i++){
		for (int j = 0; j < colunas; j++){
			if (mapa[i][j] < 10)
				printf("%d", 0);
			printf("%d ", mapa[i][j]);
		}
		printf("\n");
	}
}

int verificaFronteira(int linhas, int colunas, int fronteira[linhas][colunas]){
	//Se encontra alguma fronteira, retorna 0, caso contrário retorna 1.
	for (int i = 0; i < linhas; i++){
		for (int j = 0; j < colunas; j++){
			if (fronteira[i][j] == 1)
				return 0;
		}
	}
	return 1;
}

posicao_t proximo(int linhas, int colunas, int fronteira[linhas][colunas], int jogo[linhas][colunas], int mapa[linhas][colunas], int visitado[linhas][colunas]){
	//Encontra a fronteira em que seja alterado o maior número de cores.
	posicao_t posicao;
	posicao.i = -1;
	posicao.j = -1;
	int i, j;
	for (i = 0; i < linhas; i++){
		for (j = 0; j < colunas; j++){
			if (fronteira[i][j] == 1){
				
				posicao.i = i;
				posicao.j = j;
				break;			//breaks para diminuir o número de comparações.
								//
			}					//
		}						//
		if (posicao.i != -1)	//
			break;				//
	}
	
	for (i; i < linhas; i++){
		for (j; j < colunas; j++){
			if (fronteira[i][j] == 1){
				if (tamCor(linhas,colunas,fronteira,jogo,mapa,visitado,i,j,-1,mapa[i][j]) > tamCor(linhas,colunas,fronteira,jogo,mapa,visitado,posicao.i,posicao.j,-1,mapa[posicao.i][posicao.j])){
					posicao.i = i;
					posicao.j = j;
				}
			}
		}
	}
	
	return posicao;
	
}