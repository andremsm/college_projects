//Aluno: André Miguel Sikora Marques
//GRR20182593

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "funcoes.h"
#include "utils.h"

int main(int argc, char *argv[]){
	
	int numEq;
	double epsilon;
	int maxIter;
	double aproximacoes[1000];
	char equacoes[1000][1000];
	char eq[1000];
	
	funcoes_t funcoes[1000];
	funcoes_t funcoesD[1000];
	
	scanf("%d", &numEq);
	
	for (int i = 0; i < numEq; i++){
		scanf("%s", eq);
		strcpy(equacoes[i], eq);
	}
	for (int i = 0; i < numEq; i++){
		scanf("%lf", &aproximacoes[i]);
	}
	
	scanf("%lf", &epsilon);
	scanf("%d", &maxIter);
	
	FILE *fp;
	
	if (argc != 3)
			printf("%d\n", numEq);
	else if (argc == 3 && !strcmp(argv[1],"-o")){
		
		fp = fopen(argv[2],"w+");
		
		int l = 0;					//
		char c[1];					//
		while (1){					//
			c[0] = fgetc(fp);		//Encontra o último caractere do arquivo, para evitar sobrescrever algo.
			if (feof(fp))			//
				break;				//
			l++;					//
		}							//

		fprintf(fp, "%d\n", numEq);
		
	}
	
	criarF(funcoes, equacoes, numEq, argc, argv, fp);
	

	double *resultados = malloc ((sizeof(double)) * 100);
	
	tempo_t *tempo = malloc (sizeof (tempo_t *));			//As variáveis de tempo foram colocadas em um tipo específico para diminuir o tamanho das chamadas de função.
	
	funcoes_t jacobiana[100][100];
	
	tempo->jacobiana = timestamp();
	calcularJacobiana(funcoes, jacobiana, numEq, tempo);
	tempo->jacobiana = timestamp() - tempo->jacobiana;
	
	tempo->total = timestamp();
	resultados = newton (funcoes, jacobiana, numEq, aproximacoes, resultados, epsilon, maxIter, tempo, argc, argv, fp);
	tempo->total = timestamp() - tempo->total;
	if (argc != 3){
		printf("###########\n");
		printf("# Tempo Total: %lf\n", tempo->total);
		printf("# Tempo Derivadas: %lf\n", tempo->derivadas);
		printf("# Tempo Jacobiana: %lf\n", tempo->jacobiana);
		printf("# Tempo SL: %lf\n", tempo->sl);
		printf("###########\n");
	}
	else if (argc == 3 && !strcmp(argv[1],"-o")){
		
		fprintf(fp, "###########\n");
		fprintf(fp, "# Tempo Total: %lf\n", tempo->total);
		fprintf(fp, "# Tempo Derivadas: %lf\n", tempo->derivadas);
		fprintf(fp, "# Tempo Jacobiana: %lf\n", tempo->jacobiana);
		fprintf(fp, "# Tempo SL: %lf\n", tempo->sl);
		fprintf(fp, "###########\n");
		fclose(fp);
	}
	
}