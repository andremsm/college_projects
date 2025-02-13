// FEITO POR:
// André Miguel Sikora Marques
// GRR20182593

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

#include "chrono.c"

#include "helper_cuda.h" // mudado aqui por WZ
/**
 * CUDA Kernel Device code
 *
 * Computes the vector addition of A and B into C. The 3 vectors have the same
 * number of elements numElements.
 */

// (c) by W.Zola set/23
//
// EXAMPLE Sequential MAX-Heap,
//				decreaseMax operation
//				and others

// para compilar:
// gcc -O3 max-heap.c -o max-heap -lm

// #define SHOW_DECREASE_MAX_STEPS 1

#define MAX_SIZE ((256 * 1024 * 1024) + 4)
// #define MAX_SIZE 268435460

__global__ void
globalHisto_GM(unsigned int *H, int h, float *Input, int nElements, float nMin, float nMax)
{
	// h <- linha de comando
	// <nBlocks (56), nThreads (1024)>

	int thread_index = threadIdx.x + blockIdx.x * blockDim.x;

	int increment = blockDim.x * gridDim.x;

	float A = nMax - nMin;
	float AF = A / h;
	int faixa;
	for (int i = thread_index; i < nElements; i += increment)
	{
		faixa = (Input[i] - nMin) / AF;
		atomicAdd(&(H[faixa]), 1);
	}
}

__global__ void
blockHisto_SM(unsigned int (*HH)[(48 * 1024) / 4], int h, float *Input, int nElements, float nMin, float nMax)
{
	// h <- linha de comando
	// <nBlocks (56), nThreads (1024)>
	//

	__shared__ unsigned int HS[(48 * 1024) / 4];

	for (int i = threadIdx.x; i < h; i += blockDim.x)
		HS[i] = 0;

	__syncthreads();

	int thread_index = threadIdx.x + blockIdx.x * blockDim.x;

	int increment = blockDim.x * gridDim.x;

	float A = nMax - nMin;
	float AF = A / h;
	int faixa;
	for (int i = thread_index; i < nElements; i += increment)
	{
		faixa = (Input[i] - nMin) / AF;
		atomicAdd(&(HS[faixa]), 1);
	}

	__syncthreads();

	for (int i = threadIdx.x; i < h; i += blockDim.x)
		HH[blockIdx.x][i] += HS[i];
}

__global__ void
globalHisto_SM(unsigned int *H, int h, float *Input, int nElements, float nMin, float nMax)
{
	__shared__ unsigned int HS[(48 * 1024) / 4];

	for (int i = threadIdx.x; i < h; i += blockDim.x)
		HS[i] = 0;

	__syncthreads();

	int thread_index = threadIdx.x + blockIdx.x * blockDim.x;

	int increment = blockDim.x * gridDim.x;

	float A = nMax - nMin;
	float AF = A / h;
	int faixa;
	for (int i = thread_index; i < nElements; i += increment)
	{
		faixa = (Input[i] - nMin) / AF;
		atomicAdd(&(HS[faixa]), 1);
	}

	__syncthreads();

	for (int i = threadIdx.x; i < h; i += blockDim.x)
		atomicAdd(&(H[i]), HS[i]);
}

//////////////
int main(int argc, char *argv[])
{
	// testar com os mesmos valores do trabalho passado

	if (argc < 4)
	{
		fprintf(stderr, "usage:\n\t./trab2 <nTotalElements> <h> <-gh OR -bh OR -ghgm>\n");
		fprintf(stderr, "\t-gh = globalHisto_SM\n");
		fprintf(stderr, "\t-bh = blockHisto_SM\n");
		fprintf(stderr, "\t-ghgm = globalHisto_GM\n");
		exit(-1);
	}

	//printf("%s\n%s\n%s\n%s\n", argv[0], argv[1], argv[2], argv[3]);

	int nTotalElements = atoi(argv[1]);
	int h = atoi(argv[2]);
	//char *mode = argv[3];
	//printf("nTotalElements: %d\nh: %d\n", nTotalElements, h);

	// initialize Input vector
	static float Input[MAX_SIZE]; // max_size

	int inputSize = 0;

	for (int i = 0; i < nTotalElements; i++)
	{
		int a = rand(); // Returns a pseudo-random integer
						// between 0 and RAND_MAX.
		int b = rand(); // same as above

		// float v = abs((int)(a * 100.0 + b) % 100);

		// inserir o valor v na posição i
		// Input[i] = v;
		Input[i] = a;
	}
	inputSize = nTotalElements;

	float nMax = FLT_MIN;
	float nMin = FLT_MAX;

	for (int i = 0; i < nTotalElements; i++)
	{
		if (Input[i] > nMax)
			nMax = Input[i];
		if (Input[i] < nMin)
			nMin = Input[i];
	}
	printf("nMin: %f\nnMax: %f\n", nMin, nMax);
	printf("Largura da faixa: %d", (int)(nMax - nMin)/h);

	unsigned int *histogram = (unsigned int *)malloc(sizeof(unsigned int) * h);

	// passar no vetor heap vazio inserindo os primeiros k valores do vetor de float, e a posição

	//__device__ Pair heap[140][MAX_HEAP_SIZE];   // aloca estático 140 heaps na global memory da gpu
	//__device__ int heapSize = k;

	/*
		Pair heap[140][MAX_HEAP_SIZE];
		int heapSize = 0;

		Pair temp;
		for (int j = 0; j < 140; j++)
		{
			for (int i = 0; i < k; i++)
			{
				//  printf("(%d, %d) ", i, temp.val);
				temp.key = Input[k * j + i];
				temp.val = k * j + i;
				// if (j == 2){
				// printf("\n%f\n", temp.key);
				// printf("\n%d\n", temp.val);
				// exit(0);
				//}
				insert(heap[j], &heapSize, temp);
			}
			heapSize = 0;
			// printf("\n%d\n", j);
		}
		heapSize = k;

		// dividir (por exemplo) em 2 blocos de threads que recebem 1000 sobra o resto pra fica fazendo decrease
		// entre cada bloco (cada bloco faz um decrease pra um valor)
		// no final esses 2 blocos de threads metade dos kMenores fica em um e metade no outro (não?)

		// algumas leem algumas inserem

		// int heap[MAX_HEAP_SIZE] = {60, 50, 40, 30, 20, 10}; // {70, 40, 50, 30, 20, 10};
		// int heapSize = 6;
	*/
	static float *cudaInput;
	static unsigned int *cudaHistogram_GH;
	static unsigned int(*cudaHistogram_BH)[(48 * 1024) / 4] = nullptr;
	// static Pair **cudaHeap;

	cudaError_t err;

	err = cudaMalloc((void **)&cudaInput, MAX_SIZE * sizeof(float));
	if (err != cudaSuccess)
	{
		printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	err = cudaMalloc((void **)&cudaHistogram_BH, sizeof(unsigned int) * (((48 * 1024) / 4) * 56));
	if (err != cudaSuccess)
	{
		printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	err = cudaMalloc((void **)&cudaHistogram_GH, sizeof(unsigned int) * h);
	if (err != cudaSuccess)
	{
		printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	cudaMemcpy(cudaInput, Input, inputSize * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(cudaHistogram_BH, histogram, sizeof(unsigned int) * (((48 * 1024) / 4) * 56), cudaMemcpyHostToDevice);
	cudaMemcpy(cudaHistogram_GH, histogram, sizeof(unsigned int) * h, cudaMemcpyHostToDevice);

	/*
		int *mutex;
		cudaMalloc(&mutex, sizeof(int));
		cudaMemset(mutex, 0, sizeof(int));
	*/
	// Launch the Vector Add CUDA Kernel
	// int threadsPerBlock = 320;
	// int blocksPerGrid = (nTotalElements + threadsPerBlock - 1) / threadsPerBlock;
	//int blocks = 140;
	// int threadsPerBlock = (inputSize/blocks) + 1;
	//dim3 gridSize(56, 1, 1);
	//dim3 blockSize((1024), 1, 1);
	//printf("inputSize: %d\n", inputSize);
	//printf("CUDA kernel launch with %d blocks of %d threads\n", blocks, 320);

	chronometer_t chrono_va; // cria um chonometro para medir vectorAdd

	if (!strcmp(argv[3], "-gh"))
	{
		chrono_reset(&chrono_va);
		chrono_start(&chrono_va);
		globalHisto_SM<<<56, 1024>>>(cudaHistogram_GH, h, cudaInput, nTotalElements, nMin, nMax);
		cudaDeviceSynchronize();
		chrono_stop(&chrono_va);
		cudaMemcpy(histogram, cudaHistogram_GH, sizeof(unsigned int) * h, cudaMemcpyDeviceToHost);
		chrono_reportTime(&chrono_va, (char *)"globalHisto_SM");
	}

	if (!strcmp(argv[3], "-bh"))
	{
		chrono_reset(&chrono_va);
		chrono_start(&chrono_va);

		// achar_K_Menores<<<gridSize, blockSize>>>(cudaHeap, cudaInput, heapSize, inputSize, mutex);

		// dim3 gridSize2(70, 1, 1);
		// dim3 blockSize2((320), 1, 1);
		// merge_heaps<<<gridSize2, blockSize2>>>(cudaHeap, heapSize, 70, mutex);

		// dim3 gridSize3(35, 1, 1);
		// dim3 blockSize3((320), 1, 1);
		// merge_heaps<<<gridSize3, blockSize3>>>(cudaHeap, heapSize, 35, mutex);

		// globalHisto_GM<<<56, 1024>>>(cudaHistogram, h, cudaInput, nTotalElements, nMin, nMax);
		blockHisto_SM<<<56, 1024>>>(cudaHistogram_BH, h, cudaInput, nTotalElements, nMin, nMax);

		// cudaDeviceSynchronize();
		// chrono_stop(&chrono_va);

		// chrono_start(&chrono_va);

		// for (int i = 1; i <= 35; i++)
		//{
		//	for (int j = 0; j < heapSize; j++)
		//	{
		//		temp.key = heap[i][j].key;
		//		temp.val = heap[i][j].val;
		//		decreaseMax_seq(heap[0], heapSize, temp);
		//	}
		// }
		cudaDeviceSynchronize();
		chrono_stop(&chrono_va);
		cudaMemcpy(histogram, cudaHistogram_BH, sizeof(unsigned int) * h, cudaMemcpyDeviceToHost);
		chrono_reportTime(&chrono_va, (char *)"blockHisto_SM");
	}

	if (!strcmp(argv[3], "-ghgm"))
	{
		chrono_reset(&chrono_va);
		chrono_start(&chrono_va);
		globalHisto_GM<<<56, 1024>>>(cudaHistogram_GH, h, cudaInput, nTotalElements, nMin, nMax);
		cudaDeviceSynchronize();
		chrono_stop(&chrono_va);
		cudaMemcpy(histogram, cudaHistogram_GH, sizeof(unsigned int) * h, cudaMemcpyDeviceToHost);
		chrono_reportTime(&chrono_va, (char *)"globalHisto_GM");
	}

	//   printf("\n----- reportando o tempo total para as %d ativações do kernel -------",
	//		   N_REPETICOES);
	//chrono_reportTime(&chrono_va, (char *)"achar_K_Menores");

	//	printf("\n----- tempo médio por ativação do kernel -------");
	//	chrono_report_TimeInLoop(&chrono_va,
	//							(char *)"vectorAdd_kernel",
	//							 N_REPETICOES);
	printf("\n\n");

	// cudaMemcpy(heap, cudaHeap, k * 140 * sizeof(Pair), cudaMemcpyDeviceToHost);

	// int temp2 = -999999;
	//	for (int i = 0; i < heapSize; i++){
	//		printf("{%f, %d}, ", heap[0][i].key, heap[0][i].val);
	//	}

	err = cudaGetLastError();

	if (err != cudaSuccess)
	{
		fprintf(stderr, "Failed to launch vectorAdd kernel (error code %s)!\n", cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	double total_time_in_milliseconds = (double)chrono_gettotal(&chrono_va) /
										((double)1000 * 1000);
	printf("total_time_in_milliseconds: %lf ms\n", total_time_in_milliseconds);

	double OPS = ((double)nTotalElements * 1000) / total_time_in_milliseconds;
	printf("Throughput: %lf OP/s\n", OPS);
	printf("Throughput_ em GOP/ms: %lf GOP/ms\n", OPS / (1000 * 1000 * 1000));
	//printf("Vazão de dados em GB/s: %lf\n", (nTotalElements * 4) / (total_time_in_milliseconds / 1000));

//	for (int i = 0; i < h; i++)
//		printf("%ui ", histogram[i]);

	// verifyOutput(NULL, NULL, 0, 0);

	/*for (int i = 0; i < inputSize; i++)
		cudaInput[i] = input[i];
	for (int i = 0; i < k; i++)
		cudaHeap[i] = heap[i];*/

	// int heap[MAX_HEAP_SIZE] = {60, 50, 40, 30, 20, 10}; // {70, 40, 50, 30, 20, 10};
	// int heapSize = 6;

	return 0;
}
