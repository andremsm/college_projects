#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(){

	struct No *raiz = NULL;						//Variável que armazena a árvore
	char comando;								//Variável que armazena 'i' ou 'r' (inserção e remoção)
	int chave;									//Variável que armazena a chave que será inserida ou removida
	int returnScanf = scanf (" %c", &comando);	//Variável que armazena o retorno da função scanf (1, se for uma entrada válida)

	while (returnScanf == 1){
		
		if (comando == 'i'){					//Inserção
			scanf (" %i", &chave);
			raiz = insereNo(raiz, chave);
		}
		
		else if (comando == 'r'){				//Remoção
			scanf (" %i", &chave);
			raiz = buscaParaRemover(raiz, chave);
		}
		
		returnScanf = scanf (" %c", &comando);	//Lê a próxima operação
		
	}
	
	if (raiz != NULL){							//Caso a árvore esteja vazia, isso gera um segmentation fault na função emOrdem
		encontrarRaiz(raiz);					//Encontra a raíz, para se ter a certeza que a árvore inteira será impressa
		emOrdem(raiz, raiz->altura);			//Imprime a árvore em ordem
	}
	
	return 0;
}


