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
#include "verificaKNN.c"

chronometer_t Chrono_MPI;
MPI_Status status;

void geraConjuntoDeDados(float *C, int nc, int D, int k)
{
	for (int i = 0; i < nc; i++)
		for (int j = 0; j < D; j++)
			C[i * k + j] = (float)(rand() % 100);
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

int *knn(float *Q, int nq, float *P, int np, int D, int k)
{

	int my_rank, n_threads;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_threads);
	int my_chunk_begin = (nq / n_threads) * my_rank;
	int my_chunk_end = (nq / n_threads) * (my_rank + 1);
	int chunk_size = my_chunk_end - my_chunk_begin;
	// MPI_Status status;

	int *R = (int *)malloc(sizeof(int) * nq * k);
	int *chunk_R = (int *)malloc(sizeof(int) * chunk_size * k);
	float *Dr = (float *)malloc(sizeof(float) * nq * k);
	float *Dmax = (float *)malloc(sizeof(float) * nq);
	MPI_Barrier(MPI_COMM_WORLD);
	chrono_start(&Chrono_MPI);
	for (int i = 0; i < nq; i++)
	{
		// R[i] = (int *)malloc(sizeof(int) * k);
		// Dr[i] = (float *)malloc(sizeof(float) * k);
		for (int j = 0; j < k; j++)
		{
			Dr[i * k + j] = FLT_MAX;
		}
		Dmax[i] = FLT_MAX;
	}

	float dist = 0.0;
	int chunk_i = 0;
	for (int i = my_chunk_begin; i < my_chunk_end; i++)
	{
		for (int j = 0; j < np; j++)
		{
			dist = calculaDistancia(Q + i * k, P + j * k, D);
			/*
			if (my_rank == 0)
				printf("%f			%d			%f			%d\n", dist, j, Dmax[i], R[i]);
				*/
			if (dist < Dmax[i])
			{
				for (int elem = 0; elem < k; elem++)
				{
					int flag = 0;
					if (Dmax[i] == Dr[i * k + elem])
					{
						// verifica se Dmax realmente é o único de valor FLT_MAX
						for (int l = elem + 1; l < k; l++)
						{
							if (Dr[i * k + l] == Dmax[i])
							{
								flag = 1;
								break;
							}
						}
					}
					if (!flag)
						Dmax[i] = dist;
					Dr[i * k + elem] = dist;
					R[i * k + elem] = j;
					chunk_R[chunk_i * k + elem] = j;
				}
			}
			// dist += (Q[i][j] - P[i][j]) * (Q[i][j] - P[i][j]);
			//  R[i][j] = (Q[i][j] - P[i][j]) * (Q[i][j] - P[i][j]);
		}
		chunk_i++;
	}
	// int *R_linear = (int *)malloc(sizeof(int) * nq * k);
	//  printf("chunk_i: %d\n", chunk_i);
	/*
	if (my_rank != 0)
		MPI_Send(chunk_R, chunk_size * k, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
	else
	{
		for (int i = 1; i < n_threads; i++)
		{
			MPI_Recv(chunk_R, chunk_size * k, MPI_FLOAT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			int i_chunk_begin = (nq / n_threads) * i;
			int i_chunk_end = (nq / n_threads) * (i + 1);
			int m = 0;
			for (int j = i_chunk_begin; j < i_chunk_end; j++)
			{
				for (int l = 0; l < k; l++)
				{
					printf("%d ", chunk_R[m]);
					R[j][l] = chunk_R[m];
					m++;
				}
				printf("\n");
			}
		}
	}
	*/
	MPI_Gather(chunk_R, chunk_size * k, MPI_INT, R, chunk_size * k, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	chrono_stop(&Chrono_MPI);
	/*
	if (my_rank == 0)
		for (int i = 0; i < nq; i++)
		{
			for (int j = 0; j < k; j++)
				printf("%d ", R[i * k + j]);
			printf("\n");
			// printf("%i ", R[i][j]);
		}
	*/
	/*for (int i = 0; i < nq; i++)
		free(Dr[i]);
	free(Dr);
	free(Dmax);
	free(chunk_R);*/
	free(chunk_R);
	free(Dr);
	free(Dmax);

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

	float *Q = (float *)malloc(sizeof(float) * nq * D);
	float *P = (float *)malloc(sizeof(float) * np * D);
	int *R;

	/*
	for (int i = 0; i < nq; i++)
		Q[i] = (float *)malloc(sizeof(float) * D);
	for (int i = 0; i < np; i++)
		P[i] = (float *)malloc(sizeof(float) * D);
	*/

	if (my_rank == 0)
	{
		geraConjuntoDeDados(Q, nq, D, k);
		geraConjuntoDeDados(P, np, D, k);
	}
	MPI_Bcast(Q, nq * D, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Bcast(P, np * D, MPI_FLOAT, 0, MPI_COMM_WORLD);
	/*
	if (my_rank == 3)
	{
		printf("=================== nq: %d D: %d\n", nq, D);
		for (int i = 0; i < nq; i++)
		{
			for (int j = 0; j < D; j++)
			{
				printf("%f ", Q[i * k + j]);
			}
			printf("\n\n\n");
		}
	}
	*/
	R = knn(Q, nq, P, np, D, k);
	if (my_rank == 0)
	{
		chrono_reportTime(&Chrono_MPI, "knn");
		// calcular e imprimir a VAZAO (numero de operacoes/s)
		double total_time_in_seconds = (double)chrono_gettotal(&Chrono_MPI) /
									   ((double)1000 * 1000 * 1000);
		printf("total_time_in_seconds: %lf s\n", total_time_in_seconds);

		// double MBPS = ((tMsg * nMsg) / total_time_in_seconds) / 1000000;
		// printf("Throughput: %lf MB/s\n", MBPS * (nThreads - 1));

		// double latencia = ((double)chrono_gettotal(&Chrono_MPI) / (nMsg * 1000));
		// printf("Latência: %lf us\n", latencia);
		verificaKNN(Q, nq, P, np, D, k, R);
	}

	free(Q);
	free(R);
	free(P);
	MPI_Finalize();
}