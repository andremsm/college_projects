//Aluno: André Miguel Sikora Marques
//GRR20182593

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

typedef struct funcoes_t{
	void *f;
}funcoes_t;

typedef struct tempo_t{
	double total;
	double derivadas;
	double jacobiana;
	double sl;
}tempo_t;

void criarF(funcoes_t funcoes[1000], char eq[1000][1000], int numEq, int argc, char *argv[], FILE *fp;);

int encontraMax(double coeficientes[100][100], int i, int n);

void trocaLinha (double coeficientes[100][100], double independentes[1000], int i, int iPivo, int n);

double max(funcoes_t funcoes[1000], double aproximacoes[1000], int numEq);

double maxResultados(double *resultados, int numEq);

void calcularJacobiana(funcoes_t funcoes[1000], funcoes_t Jacobiana[100][100], int numEq, tempo_t *tempo);

double *eliminacaoGauss(funcoes_t funcoes[1000], funcoes_t Jacobiana[100][100], int numEq, double aproximacoes[1000], double *resultados, tempo_t *tempo);

double *newton (funcoes_t funcoes[1000], funcoes_t Jacobiana[100][100], int numEq, double aproximacoes[1000], double *resultados, double epsilon, int maxIter, tempo_t *tempo, int argc, char *argv[], FILE *fp);