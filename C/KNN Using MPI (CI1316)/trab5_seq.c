// TRABALHO5: CI316 1o semestre 2022
// Aluno:André Miguel Sikora Marques
// GRR:20182593
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <mpi.h>

#include "chrono.c"

chronometer_t Chrono_MPI;
MPI_Status status;

void geraConjuntoDeDados(float **C, int nc, int D)
{
	for (int i = 0; i < nc; i++)
		for (int j = 0; j < D; j++)
			C[i][j] = (float)rand();
}

/*float calculaDistancia(float **Q, float **P, int D, int i, int k)
{
	float dist = 0.0;
	for (int j = 0; j < D; j++)
	{
		dist += (Q[i][j] - P[k][j]) * (Q[i][j] - P[k][j]);
	}
	return dist;
}*/

float calculaDistancia(float *Q, float *P, int D)
{
	float dist = 0.0;
	for (int j = 0; j < D; j++)
	{
		dist += (Q[j] - P[j]) * (Q[j] - P[j]);
	}
	return dist;
}

int **knn(float **Q, int nq, float **P, int np, int D, int k)
{
	int **R = (int **)malloc(sizeof(int *) * nq);
	float **Dr = (float **)malloc(sizeof(float *) * nq);
	float *Dmax = (float *)malloc(sizeof(float) * nq);
	for (int i = 0; i < nq; i++)
	{
		R[i] = (int *)malloc(sizeof(int) * k);
		Dr[i] = (float *)malloc(sizeof(float) * k);
		for (int j = 0; j < k; j++)
		{
			Dr[i][j] = FLT_MAX;
		}
		Dmax[i] = FLT_MAX;
	}
	//
	float dist = 0.0;
	for (int i = 0; i < nq; i++)
	{
		for (int j = 0; j < np; j++)
		{
			dist = calculaDistancia(Q[i], P[j], D);
			if (dist < Dmax[i])
			{
				int flag = 0;
				for (int elem = 0; elem < k; elem++)
				{
					if (Dmax[i] == Dr[i][elem])
					{
						// verifica se Dmax realmente é o único de valor FLT_MAX
						for (int l = elem + 1; l < k; l++)
						{
							if (Dr[i][l] == Dmax[i])
							{
								flag = 1;
								break;
							}
						}
					}
					if (!flag)
						Dmax[i] = dist;
					Dr[i][elem] = dist;
					R[i][elem] = j;
				}
			}
			// dist += (Q[i][j] - P[i][j]) * (Q[i][j] - P[i][j]);
			//  R[i][j] = (Q[i][j] - P[i][j]) * (Q[i][j] - P[i][j]);
		}
	}
	//
	return R;
}

int main(int argc, char *argv[])
{

	int my_rank;
	int nThreads;
	// linha de comando: int(nq, np, D, k)
	// k = 128
	int nq, np, D, k;
	srand(777);

	if (argc < 5)
	{
		fprintf(stderr, "\nusage: %s <nq> <np> <D> <k>\n", argv[0]);
		return 0;
	}

	nq = atoi(argv[1]);
	np = atoi(argv[2]);
	D = atoi(argv[3]);
	k = atoi(argv[4]);

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nThreads);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	chrono_reset(&Chrono_MPI);

	float **Q = (float **)malloc(sizeof(float *) * nq);
	float **P = (float **)malloc(sizeof(float *) * np);
	int **R;

	for (int i = 0; i < nq; i++)
		Q[i] = (float *)malloc(sizeof(float) * D);
	for (int i = 0; i < np; i++)
		P[i] = (float *)malloc(sizeof(float) * D);

	geraConjuntoDeDados(Q, nq, D);
	geraConjuntoDeDados(P, np, D);

	R = knn(Q, nq, P, np, D, k);

	for (int i = 0; i < nq; i++)
	{
		free(Q[i]);
		free(R[i]);
	}
	for (int i = 0; i < np; i++)
		free(P[i]);
	free(Q);
	free(R);
	free(P);
	MPI_Finalize();
}