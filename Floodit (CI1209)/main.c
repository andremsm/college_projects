#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include "fila.h"

int main (){
	
	int linhas = 0, colunas = 0, cores = 0;
	int scan_f;	//Somente para evitar warnings no compilador.
	scan_f = scanf("%d %d %d", &linhas, &colunas, &cores);
	int mapa[linhas][colunas];
	int jogo[linhas][colunas];
	int fronteira[linhas][colunas];
	int visitado[linhas][colunas];
	
	for (int i = 0; i < linhas; i++){
		for (int j = 0; j < colunas; j++){
			scan_f = scanf("%d", &mapa[i][j]);
			jogo[i][j] = 0;
			fronteira[i][j] = 0;
			visitado[i][j] = 0;
		}
	}
	jogo[0][0] = mapa[0][0];
	fila_t * passos = inicializaFila();
	calculaFronteira(linhas, colunas, fronteira, jogo);
	int move;
	
	posicao_t proximoH;	//Próximo baseado na heurística.
	int k = 0;
	int contador;
	
	while (!verificaFronteira(linhas,colunas,fronteira)){
		proximoH = proximo(linhas,colunas,fronteira,jogo,mapa,visitado);
		desvisitar(linhas,colunas,visitado);
		move = mapa[proximoH.i][proximoH.j];
		insereFila(passos, move, 0);
		k++;
		flood(move,linhas,colunas,fronteira,jogo,mapa,visitado);
		contador++;
	}
	
	printf("%d\n", contador);
	for (int l = 0; l < k; l++)
		printf("%d ", desenfileira(passos));
	printf("\n");
	
	return 0;
}