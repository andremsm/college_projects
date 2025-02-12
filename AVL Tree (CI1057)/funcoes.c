#include "header.h"
#include <stdio.h>
#include <stdlib.h>

struct No *criaNo (int chave){
	//Função que cria o nó.

	struct No *N = (struct No *) malloc (sizeof (struct No));
	N->dir = NULL;
	N->esq = NULL;
	N->pai = NULL;
	N->altura = 0;		//Sempre inicializa em 0, a altura correta é calculada durante a função emOrdem
	N->chave = chave;
	return N;
	
}

int altura (struct No *N){
	//Essa função calcula a altura da subárvore.

	int he, hd;
	
	if (N == NULL) return 0;
	
	he = altura(N->esq);
	hd = altura(N->dir);
	
	if (he>hd) return he+1;
	
	else return hd+1;
	
}

int balanceamento (struct No *N){
	//Essa função calcula o fator de balanceamento da subárvore.

	int he, hd;
	he = altura(N->esq);	//Altura da subárvore da esquerda
	hd = altura(N->dir);	//Altura da subárvore da direita
	return he-hd;			//Altura da subárvore esquerda - Altura da subárvore direita
	
}

void emOrdem (struct No *N, int altura){
	//Essa função faz o percurso em ordem da árvore,
	//calcula a altura em que está a folha, e imprime
	//a chave e a altura na qual a função está.
	
	if (N != NULL){
		emOrdem(N->esq, altura+1);
		printf("%d,", N->chave);
		N->altura = altura;
		printf("%d\n", N->altura);
		emOrdem(N->dir, altura+1);
	}
	
}

struct No *rotacaoDir (struct No *N){
	//Essa função faz a rotação do nó para a direita.
	
	struct No *aux = N->esq;
	N->esq = aux->dir;
	aux->pai = N->pai;
	N->pai = aux;
	
	if (aux->dir != NULL)	//Esse if evita segmentation fault.
		aux->dir->pai = N;
		
	aux->dir = N;
	return aux;
	
}

struct No *rotacaoEsq (struct No *N){
	//Essa função faz a rotação do nó para a esquerda.
	
	struct No *aux = N->dir;
	N->dir = aux->esq;
	aux->pai = N->pai;
	N->pai = aux;
	
	if (aux->esq != NULL)	//Esse if evita segmentation fault.
		aux->esq->pai = N;
		
	aux->esq = N;
	return aux;
	
}

struct No *insereNo (struct No *N, int chave){
	//Essa é uma função principal que é chamada do main para
	//inserir o nó. Primeiro a função busca recursivamente
	//pelo local de inserção do nó. Quando N for nulo,
	//a função cria um novo nó neste local.
	//Após isso, a função calcula o fator de balanceamento no
	//escopo da função, e faz a rotação adequada para ajustar
	//o balancemanto da árvore.
	
	if (N == NULL) return criaNo(chave);	//Árvore vazia ou nó correto
	
	if (chave < N->chave){
		N->esq = insereNo(N->esq, chave);
		N->esq->pai = N;	//Evita erros
	}
	
	else if (chave > N->chave){
		N->dir = insereNo(N->dir, chave);
		N->dir->pai = N;	//Evita erros
	}
	
	else return N;	//Esse else serve para evitar chaves duplicadas, ao contrário de apenas retornar N

	int b = balanceamento(N);
	
	if (b > 1 && chave < N->esq->chave)		//Caso esquerda-esquerda
		return rotacaoDir(N);

	if (b < -1 && chave > N->dir->chave)	//Caso direita-direita
		return rotacaoEsq(N);

	if (b > 1 && chave > N->esq->chave){	//Caso esquerda-direita
		N->esq = rotacaoEsq(N->esq);
		return rotacaoDir(N);
	}
	
	if (b < -1 && chave < N->dir->chave){	//Caso direita-esquerda
		N->dir = rotacaoDir(N->dir);
		return rotacaoEsq(N);
	}
	
	return N;								//Caso não seja necessário rotacionar
	
}

struct No *encontrarRaiz (struct No *N){
	//Essa função serve para encontrar a raíz
	//e evitar alterações em locais indevidos.
	
	if (N == NULL) return NULL;	//Árvore vazia
	
	while (N->pai != NULL)		//Encontra a raíz iterativamente
		N = N->pai;
		
	return N;
	
}

void ajustaPai (struct No *N, struct No *novo){
	//Essa função ajusta o pai do nó após a remoção.

	if (N->pai != NULL){		//Esse if serve para evitar segmentation fault
		
		if (N->pai->esq == N)
			N->pai->esq = novo;
		
		else
			N->pai->dir = novo;
		
	}
	
	if (novo != NULL)
		novo->pai = N->pai;

}

struct No *max (struct No *N){
	//Essa função encontra a maior folha na subárvore.
	
	if (N->dir == NULL)
		return N;
	
	else
		return max(N->dir);
	
}

struct No *antecessor (struct No *N){
	//Essa função encontra o antecessor do nó.
	
	if (N->esq != NULL)
		return max(N->esq);
	
	else{
		struct No *s = N->pai;	//s é o antecessor
		
		while (s != NULL && N == s->esq){
			N = s;
			s = s->pai;
		}
		
		return s;
	}
	
	return NULL;
	
}

struct No *removeNo (struct No *N){
	//Essa função verifica em qual caso
	//cai a remoção, e remove o nó.

	if (N->esq == NULL && N->dir == NULL){	//Caso nó não tem filhos
		struct No *temp = N->pai;	//Evita erros com ponteiros
		ajustaPai(N, NULL);
		return encontrarRaiz(temp);
	}
	
	else if (N->esq == NULL){	//Caso nó não tem filho esquerdo
		ajustaPai(N, N->dir);
		
		if (N->pai == NULL)		//Evita segmentation fault
			return encontrarRaiz(N->dir);
			
		return encontrarRaiz(N);
	}
	
	else if (N->dir == NULL){	//Caso nó não tem filho direito
		ajustaPai(N, N->esq);
		
		if (N->pai == NULL)		//Evita segmentation fault
			return encontrarRaiz(N->esq);
			
		return encontrarRaiz(N);
	}
	
	else{	//Caso nó tem ambos filhos
		struct No *a = antecessor(N);	//Essa variável armazena o antecessor do nó
		ajustaPai(a, a->esq);
		a->esq = N->esq;				//Ajusta ponteiros para evitar
		a->dir = N->dir;				//erros no próximo ajuste do pai
		ajustaPai(N, a);
		
		if (a->dir != NULL)				//Evita segmentation fault
			a->dir->pai = a;
			
		if (a->esq != NULL)				//Evita segmentation fault
			a->esq->pai = a;
			
		return encontrarRaiz(a);
	}
	
	return encontrarRaiz(N);
	
}

struct No *balancearEmOrdem (struct No *N){
	//Essa função percorre os nós em ordem, fazendo
	//o balanceamento da subárvore quando necessário
	
	if (N != NULL){
		balancearEmOrdem(N->esq);
		
		int b = balanceamento(N);	//Essa variável armazena o fator de balanceamento da subárvore
		
		if (b > 1 && balanceamento(N->esq) >= 0){	//Caso esquerda-esquerda
			struct No *temp =  rotacaoDir(N);
			
			if (temp->pai != NULL && temp->chave > temp->pai->chave)		//Ajusta o filho direito do pai, evitando erros
				temp->pai->dir = temp;
			
			else if (temp->pai != NULL && temp->chave < temp->pai->chave)	//Ajusta o filho esquerdo do pai, evitando erros
				temp->pai->esq = temp;
			
			return temp;
		}

		if (b < -1 && balanceamento(N->dir) <= 0){	//Caso direita-direita
			struct No *temp = rotacaoEsq(N);
			
			if (temp->pai != NULL && temp->chave > temp->pai->chave)		//Ajusta o filho direito do pai, evitando erros
				temp->pai->dir = temp;
			
			else if (temp->pai != NULL && temp->chave < temp->pai->chave)	//Ajusta o filho esquerdo do pai, evitando erros
				temp->pai->esq = temp;
			
			return temp;
		}

		if (b > 1 && balanceamento(N->esq) < 0){	//Caso esquerda-direita
			N->esq = rotacaoEsq(N->esq);
			struct No *temp = rotacaoDir(N);

			if (temp->pai != NULL && temp->chave > temp->pai->chave)		//Ajusta o filho direito do pai, evitando erros
				temp->pai->dir = temp;
			
			else if (temp->pai != NULL && temp->chave < temp->pai->chave)	//Ajusta o filho esquerda do pai, evitando erros
				temp->pai->esq = temp;

			return temp;
		}
		
		if (b < -1 && balanceamento(N->dir) > 0){	//Caso direita-esquerda
			N->dir = rotacaoDir(N->dir);
			struct No *temp = rotacaoEsq(N);
			
			if (temp->pai != NULL && temp->chave > temp->pai->chave)		//Ajusta o filho direito do pai, evitando erros
				temp->pai->dir = temp;
			
			else if (temp->pai != NULL && temp->chave < temp->pai->chave)	//Ajusta o filho esquerdo do pai, evitando erros
				temp->pai->esq = temp;
			
			return temp;
		}
		
		balancearEmOrdem(N->dir);
	}
	
	return N;
	
}

struct No *buscaParaRemover (struct No *N, int i){
	//Essa é uma função principal que é chamada do main para
	//remover o nó. Primeiro um nó temporário é criado para
	//armazenar a raiz da árvore, para que não ocorram erros
	//com retorno de NULL. Após isso é feita uma busca iterativa
	//para encontrar-se o nó a ser removido. Caso o nó não exista
	//a função retorna o nó temporário, que é a raiz. Após isso
	//outro nó temporário é criado, novamente para evitarem-se
	//erros com retorno de NULL através da chamada da função
	//encontrarRaiz. Após isso é feita a exclusão do nó através
	//da função removeNo, que retorna a raíz da árvore para o nó
	//temporário. Em seguida é feito o balanceamento da árvore,
	//começando pela menor folha, devido ao percurso da função ser
	//em ordem. Caso a árvore não esteja vazia, a função
	//buscaParaRemover retorna, através da função encontrarRaiz,
	//o nó raíz da árvore. Caso contrário retorna NULL.
	
	struct No *temp2 = N;	//Evita erros no retorno
	
	while (N != NULL && i != N->chave){		//Busca iterativamente pelo nó a ser removido
		if (i < N->chave)
			N = N->esq;
		
		else
			N = N->dir;
	}
	
	if (N == NULL) return encontrarRaiz(temp2);	//Evita erros no retorno, caso o nó não exista ou a árvore esteja vazia
	
	struct No *temp;	//Evita erros no retorno
	
	if (N != NULL){		//Se o nó a ser removido existe, essa parte é executada
		temp = removeNo(N);		//Remove o nó
		temp = balancearEmOrdem(temp);		//Verifica o balanceamento da árvore, e o corrige
	}
	
	if (temp != NULL)	//Evita erros no retorno
		return encontrarRaiz(temp);
	
	return NULL;
	
}


