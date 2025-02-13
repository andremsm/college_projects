//Aluno: Andr� Miguel Sikora Marques
//GRR20182593

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "funcoes.h"
#include "utils.h"

void criarF(funcoes_t funcoes[1000], char eq[1000][1000], int numEq, int argc, char *argv[], FILE *fp){
	//Essa fun��o transforma as strings lidas em fun��es. Originalmente eu tentei colocar as fun��es em uma matriz de void,
	//o que funcionou nessa fun��o pelo menos. Por�m mais adiante no c�digo isso parou de funcionar. Ent�o mudei para um
	//vetor do tipo funcoes_t, o qual dentro cont�m um vetor void para armazenar a fun��o.
	
	for (int i = 0; i < numEq; i++){
		int l = strlen(eq[i]);

		if (l > 0 && eq[i][l-1] == '\n')
			eq[i][l-1] = '\0';
		funcoes[i].f = evaluator_create(eq[i]);
		
		
		
		if (argc != 3)														//Trecho para imprimir as fun��es em tela.
			printf("%s = 0\n", evaluator_get_string(funcoes[i].f));			//
		else if (argc == 3 && !strcmp(argv[1],"-o")){						//Trecho para salvar as fun��es em um arquivo.
			fprintf(fp, "%s = 0\n", evaluator_get_string(funcoes[i].f));	//
		}
		
	}
}

int encontraMax(double coeficientes[100][100], int i, int n){
	//Essa fun��o encontra o maior coeficiente para fazer o pivoteamento parcial.
	
	int max = i;
	
	for (int j = i; j < n; j++){
		if (coeficientes[j][i] > coeficientes[i][i])
			max = j;
	}
	
	return max;
}

void trocaLinha (double coeficientes[100][100], double independentes[1000], int i, int iPivo, int n){
	//Essa fun��o troca a linha na matriz de coeficientes, e no vetor de termos independentes, usado no
	//pivoteamento parcial.
	
	double tempc, tempi;
	
	for (int j = i; j < n; j++){
		tempc = coeficientes[i][j];
		tempi = independentes[i];
		coeficientes[i][j] = coeficientes[iPivo][j];
		coeficientes[iPivo][j] = tempc;
		independentes[i] = independentes[iPivo];
		independentes[iPivo] = tempi;
	}
	
}

double max(funcoes_t funcoes[1000], double aproximacoes[1000], int numEq){
	//Encontra o maior valor entre fun��es usando o vetor de aproxima��es.
	
	int i = 0;
	char **names;
	int count;
	evaluator_get_variables (funcoes[i].f, &names, &count);
	double maior = fabs(evaluator_evaluate (funcoes[i].f, count, names, aproximacoes));
	i++;
	double temp;
	while (i < numEq){
		evaluator_get_variables (funcoes[i].f, &names, &count);
		temp = fabs(evaluator_evaluate (funcoes[i].f, numEq, names, aproximacoes));
		if (maior < temp)
			maior = temp;
		i++;
	}

	return maior;
}

double maxResultados(double *resultados, int numEq){
	//Encontra o maior valor no vetor de resultados.
	
	int i = 0;
	double max = fabs(resultados[i]);
	for (i = 0; i < numEq; i++)
		if (fabs(resultados[i]) > max)
			max = fabs(resultados[i]);
	return max;
	
}

void calcularJacobiana(funcoes_t funcoes[1000], funcoes_t Jacobiana[100][100], int numEq, tempo_t *tempo){
	//Calcula as derivadas e as coloca na matriz jacobiana.
	
	char **names;
	int count;
	
	
	
	for (int i = 0; i < numEq; i++){
		evaluator_get_variables (funcoes[i].f, &names, &count);
		
		for (int j = 0; j < numEq; j++){
			double tempod = timestamp();										//Calcula o tempo gasto na deriva��o.
			Jacobiana[i][j].f = evaluator_derivative(funcoes[i].f, names[j]);
			tempod = timestamp() - tempod;										//Calcula o tempo gasto na deriva��o.
			tempo->derivadas += tempod;											//
		}

	}
	
}

double *eliminacaoGauss(funcoes_t funcoes[1000], funcoes_t Jacobiana[100][100], int numEq, double aproximacoes[1000], double *resultados, tempo_t *tempo){
	//Primeiro calcula os valores que ficar�o no vetor de termos independentes, depois os coeficientes, e depois faz a elimina��o de Gauss. Por �ltimo calcula
	//o valor que assumir� cada vari�vel na solu��o do sistema.
	
	char **names;
	int count;
	double coeficientes[100][100];
	double independentes[1000];
	
	for (int i = 0; i < numEq; i++){
		evaluator_get_variables (funcoes[i].f, &names, &count);
		independentes[i] = (evaluator_evaluate (funcoes[i].f, numEq, names, aproximacoes))*(-1);
	}
	
	for (int i = 0; i < numEq; i++){
		
		for (int j = 0; j < numEq; j++){
			evaluator_get_variables (Jacobiana[i][j].f, &names, &count);
			coeficientes[i][j] = evaluator_evaluate(Jacobiana[i][j].f, count, names, aproximacoes);
		}

	}
	
	for (int i = 0; i < numEq; i++){
		
		int iPivo = encontraMax(coeficientes, i, numEq);
		if (i != iPivo)
			trocaLinha(coeficientes, independentes, i, iPivo, numEq);
		
		for (int k = i+1; k < numEq; k++){
			
			double m = coeficientes[k][i]/coeficientes[i][i];
			coeficientes[k][i] = 0.0;
			for (int j = i+1; j < numEq; j++)
				coeficientes[k][j] -= coeficientes[i][j] * m;
			independentes[k] -= independentes[i] * m;
			
		}
	}
	
	for (int i = numEq - 1; i >= 0; i--){
		
		for (int j = numEq - 1; j >= 0; j--){
			
			if (coeficientes[i][j-1] == 0.0 || (j - 1) < 0){
				resultados[i] = independentes[i]/coeficientes[i][j];
				break;
			}
			else
				independentes[i] = independentes[i] - coeficientes[i][j]*resultados[j];
			
		}
	}

	return resultados;
}

double *newton (funcoes_t funcoes[1000], funcoes_t Jacobiana[100][100], int numEq, double aproximacoes[1000], double *resultados, double epsilon, int maxIter, tempo_t *tempo, int argc, char *argv[], FILE *fp){
	//Implementa o m�todo de Newton como mostrado no slide n�mero 38 da aula de Resolu��o de Sistemas N�o-Lineares. Primeiro calcula
	//se os valores de aproxima��es na itera��o satisfazem o crit�rio de parada, depois faz a elimina��o de Gauss, depois verifica se
	//os resultados satisfazem o crit�rio de parada.
	
	for (int i = 0; i <= maxIter; i++){
		
		if (argc != 3){												//
			printf("#\n");											//
			for (int j = 0; j < numEq; j++){						//
				printf("x%d = %lf\n", j+1, aproximacoes[j]);		//Trecho para impress�o em tela.
			}														//
																	//
		}															//
		else if (argc == 3 && !strcmp(argv[1],"-o")){				//
			fprintf(fp, "#\n");										//
			for (int j = 0; j < numEq; j++){						//
				fprintf(fp, "x%d = %lf\n", j+1, aproximacoes[j]);	//Trecho para salvar em arquivo.
			}														//
																	//
		}															//
		
		if (max(funcoes, aproximacoes, numEq) < epsilon){
			return aproximacoes;
		}
		double tempos = timestamp();																//Calcula o tempo gasto resolvendo sistemas lineares.
		resultados = eliminacaoGauss(funcoes, Jacobiana, numEq, aproximacoes, resultados, tempo);
		tempos = timestamp() - tempos;																//Calcula o tempo gasto resolvendo sistemas lineares.
		tempo->sl += tempos;																		//
		for (int i = 0; i < numEq; i++)
			aproximacoes[i] += resultados[i];
		
		if (maxResultados(resultados, numEq) < epsilon)
			return aproximacoes;
	}
	
}


















