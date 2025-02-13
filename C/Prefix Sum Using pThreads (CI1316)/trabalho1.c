#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "chrono.c"

#define MAX_THREADS 64

#define MAX_TOTAL_ELEMENTS (250 * 1000 * 1000) // if each float takes 4 bytes
											   // will have a maximum 500 million elements
											   // which fits in 2 GB of RAM

pthread_t Thread[MAX_THREADS];
int my_thread_id[MAX_THREADS];
int partialSum[MAX_THREADS];

int nThreads;		// numero efetivo de threads
					// obtido da linha de comando
int nTotalElements; // numero total de elementos
					// obtido da linha de comando

int InputVector[MAX_TOTAL_ELEMENTS];	// will NOT use malloc
int OutputVector[MAX_TOTAL_ELEMENTS];	// for simplicity

pthread_barrier_t myBarrier;

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void *prefix_sum(void *ptr)
{
	int myIndex = *((int *)ptr);
	int nElements = nTotalElements / nThreads;

	// assume que temos pelo menos 1 elemento por thhread
	int first = myIndex * nElements;
	int last = min((myIndex + 1) * nElements, nTotalElements);

	if (myIndex != 0)
	{
		first++;
		if (myIndex == nThreads - 1)
			last = nTotalElements - 1;
		pthread_barrier_wait(&myBarrier);
	}

	// work with my chunck
	float myPartialSum = 0;
	for (int i = first + 1; i <= last; i++)
		InputVector[i] += InputVector[i - 1];

	partialSum[myIndex + 1] = InputVector[last];

	pthread_barrier_wait(&myBarrier);

	if (myIndex == 0)
	{
		partialSum[0] = 0;
		for (int i = 1; i < nThreads; i++)
			partialSum[i] += partialSum[i - 1];
	}

	pthread_barrier_wait(&myBarrier);

	int j = myIndex;
	for (int i = first; i <= last; i++)
		InputVector[i] += partialSum[j];

	// store my result
	partialSum[myIndex] = myPartialSum;

	pthread_barrier_wait(&myBarrier);

	return NULL;
}

int main(int argc, char *argv[])
{
	int i;
	chronometer_t parallelReductionTime;

	if (argc != 3)
	{
		printf("usage: %s <nTotalElements> <nThreads>\n",
			   argv[0]);
		return 0;
	}
	else
	{
		nThreads = atoi(argv[2]);
		if (nThreads == 0)
		{
			printf("usage: %s <nTotalElements> <nThreads>\n",
				   argv[0]);
			printf("<nThreads> can't be 0\n");
			return 0;
		}
		if (nThreads > MAX_THREADS)
		{
			printf("usage: %s <nTotalElements> <nThreads>\n",
				   argv[0]);
			printf("<nThreads> must be less than %d\n", MAX_THREADS);
			return 0;
		}
		nTotalElements = atoi(argv[1]);
		if (nTotalElements > MAX_TOTAL_ELEMENTS)
		{
			printf("usage: %s <nTotalElements> <nThreads>\n",
				   argv[0]);
			printf("<nTotalElements> must be up to %d\n", MAX_TOTAL_ELEMENTS);
			return 0;
		}
	}

	/*printf("reading inputs...\n");
	for (int i = 0; i < nTotalElements; i++)
	{
		scanf("%d", &InputVector[i]);
	}*/
	
	// initialize InputVector
	for (int i = 0; i < nTotalElements; i++){
		InputVector[i] = i + 1;
		OutputVector[i] = i + 1;
	}

	printf("\n\nwill use %d threads to calculate prefix-sum of %d total elements\n", nThreads, nTotalElements);

	chrono_reset(&parallelReductionTime);

	pthread_barrier_init(&myBarrier, NULL, nThreads);

	// thread 0 será main

	my_thread_id[0] = 0;
	for (i = 1; i < nThreads; i++)
	{
		my_thread_id[i] = i;
		pthread_create(&Thread[i], NULL,
					   prefix_sum, &my_thread_id[i]);
	}

	// Medindo tempo SEM criacao das threads
	pthread_barrier_wait(&myBarrier); // que acontece se isso for omitido ?
	chrono_start(&parallelReductionTime);

	prefix_sum(&my_thread_id[i]); // main faz papel da thread 0
								  // chegando aqui todas as threads sincronizaram, até a 0 (main)

	// Measuring time after threads finished...
	chrono_stop(&parallelReductionTime);

	// main imprime o resultado global
	/*for (i = 0; i < nTotalElements; i++)
		printf("%d ", InputVector[i]);
	printf("\n");
	*/

	for (i = 1; i < nThreads; i++)
		pthread_join(Thread[i], NULL); // isso é necessário ?

	pthread_barrier_destroy(&myBarrier);

	chrono_reportTime(&parallelReductionTime, "parallelReductionTime");

	// calcular e imprimir a VAZAO (numero de operacoes/s)
	double total_time_in_seconds = (double)chrono_gettotal(&parallelReductionTime) /
								   ((double)1000 * 1000 * 1000);
	printf("total_time_in_seconds: %lf s\n", total_time_in_seconds);

	double OPS = (nTotalElements) / total_time_in_seconds;
	printf("Throughput: %lf OP/s\n", OPS);

	//Tive que inverter o InputVector e o OutputVector aqui porque eu calculei tudo no InputVector.
	//Por isso também que os dois são inicializados no começo do main.
	int last = 0;
    for( int i=0; i<nTotalElements ; i++ ) {
           if( InputVector[i] != (OutputVector[i] + last) ) {
               fprintf( stderr, "Out[%d]= %d (wrong result!)\n", i, InputVector[i] );
               break;
           }
           last = InputVector[i];    
    }  

	return 0;
}