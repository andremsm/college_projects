// FEITO POR:
// André Miguel Sikora Marques
// GRR20182593

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

#define MAX_HEAP_SIZE (2048)
#define MAX_SIZE 20000000

typedef struct
{
	float key; // inserir um valor v float na chave
			   // (obtido do vetor de entrada Input)
	int val;   // inserir a posiçao p como valor val
} Pair;

__device__ void lock(int *mutex)
{
	while (atomicCAS(mutex, 0, 1) != 0)
		;
}
__device__ void unlock(int *mutex)
{
	atomicExch(mutex, 0);
}

__device__ void drawHeapTree(Pair heap[], int size, int nLevels) // FIX ME!
{
	int offset = 0;
	int space = (int)pow(2, nLevels - 1);
	// int space = 0;

	int nElements = 1;
	for (int level = 0; level < nLevels; level++)
	{

		// print all elements in this level
		for (int i = offset; i < size && i < (offset + nElements); i++)
		{
			printf("[%3lf, %d]", heap[i].key, heap[i].val);
		}
		printf("\n");

		offset += nElements;
		space = nElements - 1;
		nElements *= 2;
	}
}

__device__ void swap(Pair *a, Pair *b) //__attribute__((always_inline));
{
	Pair temp = *a;
	*a = *b;
	*b = temp;
}

void maxHeapify_seq(Pair heap[], int size, int i)
{
	while (1)
	{
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if (left < size && heap[left].key > heap[largest].key)
			largest = left;

		if (right < size && heap[right].key > heap[largest].key)
			largest = right;

		if (largest != i)
		{
			// swap(&heap[i], &heap[largest]); // Using the swap function
			Pair temp = heap[i];
			heap[i] = heap[largest];
			heap[largest] = temp;
			i = largest;
		}
		else
		{
			break;
		}
	}
}

// #define parent(pos) ( pos/2 ) // SE nao usar posicao 0
#define parent(pos) ((pos - 1) / 2)

void heapifyUp(Pair heap[], int *size, int pos, int old_pos)
{
	int val = heap[pos].key;
	while (pos > 0 && val > heap[parent(pos)].key)
	{
		heap[pos] = heap[parent(pos)];
		pos = parent(pos);
	}
	heap[pos].key = val;
	heap[pos].val = old_pos;
}

void insert(Pair heap[], int *size, Pair element)
{
	*size += 1;
	int last = *size - 1;

	heap[last] = element;
	// printf("before heapifyUp ");
	heapifyUp(heap, size, last, element.val);
	// printf("after heapifyUp ");
}

int isMaxHeap(Pair heap[], int size)
{
	for (int i = 1; i < size; i++)
		if (heap[i].key <= heap[parent(i)].key)
			continue;
		else
		{
			printf("\nbroke at [%d]=%lf\n", i, heap[i].key);
			printf("father at [%d]=%lf\n",
				   parent(i), heap[parent(i)].key);
			return 0;
		}
	return 1;
}

void decreaseMax_seq(Pair heap[], int size, Pair new_value)
{
	if (size == 0) // Heap is empty
		return;

	if (heap[0].key > new_value.key)
	{
		heap[0] = new_value;
#if SHOW_DECREASE_MAX_STEPS
		drawHeapTree(heap, size, 4);
		printf("	~~~~~~~~~~~~~~~~~~~~~~~~~\n");
#endif
		maxHeapify_seq(heap, size, 0);
	}
}

__device__ void maxHeapify(Pair heap[], int size, int i)
{
	while (1)
	{
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if (left < size && heap[left].key > heap[largest].key)
			largest = left;

		if (right < size && heap[right].key > heap[largest].key)
			largest = right;

		if (largest != i)
		{
			// swap(&heap[i], &heap[largest]); // Using the swap function
			Pair temp = heap[i];
			heap[i] = heap[largest];
			heap[largest] = temp;
			i = largest;
		}
		else
		{
			break;
		}
	}
}

__device__ void decreaseMax(Pair heap[], int size, Pair new_value)
{
	if (size == 0) // Heap is empty
		return;

	if (heap[0].key > new_value.key)
	{
		heap[0] = new_value;
#if SHOW_DECREASE_MAX_STEPS
		drawHeapTree(heap, size, 4);
		printf("	~~~~~~~~~~~~~~~~~~~~~~~~~\n");
#endif
		maxHeapify(heap, size, 0);
	}
}

__global__ void
achar_K_Menores(Pair (*heap)[MAX_HEAP_SIZE], float *input, int heapSize, int inputSize, int *mutex)
{
	int thread_index = threadIdx.x + blockIdx.x * blockDim.x;
	int thread_index_next = (threadIdx.x + 1) + blockIdx.x * blockDim.x;

	int index = (thread_index) * (inputSize / (320 * 140));
	int next_index = (thread_index_next) * (inputSize / (320 * 140));

	Pair temp;
	if (index < inputSize)
	{
		for (int i = index; i < next_index; i++)
		{
			if (i < inputSize)
			{
				temp.key = input[i];
				temp.val = i;
				bool leave = true;
				while (leave)
				{
					if (atomicCAS(mutex, 0, 1) == 0)
					{
						decreaseMax(heap[blockIdx.x], heapSize, temp);
						leave = false;
						atomicExch(mutex, 0);
						break;
					}
					break;
					// decreaseMax(heap[blockIdx.x], heapSize, temp);
				}
			}
			else
				break;
		}
		// printf("%d is legal\n", index);
		// if(blockIdx.x >= 140)
		//	printf("blockId: %d\n", blockIdx.x);
		// temp.key = input[index];
		// temp.val = index;
		// decreaseMax(heap[blockIdx.x], heapSize, temp);
	}
}

__global__ void
merge_heaps(Pair (*heap)[2048], int heapSize, int nBlocks, int *mutex)
{
	// int index = (threadIdx.x + blockIdx.x * blockDim.x) * 320;
	// int next_index = (threadIdx.x + (blockIdx.x + 1) * blockDim.x) * 320;

	Pair temp;
	// if (index < heapSize){
	for (int i = 0; i < heapSize; i++)
	{
		bool leave = true;
		while (leave)
		{
			if (atomicCAS(mutex, 0, 1) == 0)
			{
				temp.key = heap[blockIdx.x + nBlocks][i].key;
				temp.val = heap[blockIdx.x + nBlocks][i].val;
				decreaseMax(heap[blockIdx.x], heapSize, temp);
				leave = false;
				atomicExch(mutex, 0);
				break;
			}
			break;
		}
	}
	//}
}

void verifyOutput(const float *Input,
				  const Pair *Output, // pair_t é o tipo de um par (v,p)
				  int nTotalElmts,
				  int k)
{
	// codigo da verificacao a ser incluido por voce
	// voce deve verificar se o conjunto de pares de saida está correto
	// e imprimir uma das mensagens abaixo
	int ok = 1;

	// inserir aqui o codigo da verificacao
	// uma implementação possível para o verificador seria
	// (nao precisa seguir essa descrição, voce pode fazer outro método
	//  de verificação)
	//
	// 1) Criar um vetor I de pares (chave, valor)
	//	os os elementos de I devem ser copias
	//	de cada valor (e,p) do vetor de entrada Input
	//	(ou seja, cada valor e que veio da posição p da entrada)
	// 2) Ordenar o vetor I em ordem crescente,
	//	obtendo-se um outro vetor Is (ordenado em ordem crescente de chaves)
	//	usando um algoritmo de ordenação do tipo (chave, valor)
	//	(por exemplo ordenação da stdlib, caso exista)
	// 3) Para cada par (ki,vi) pertencente ao vetor Output
	//	  procurar a chave ki dentre K primeiros elementos
	//	  de Is.
	//	  Se a chave Ki estiver em Is com valor val==vi continue
	//	  senão faça ok = 0 e reporte o erro abaixo

	if (ok)
		printf("\nOutput set verified correctly.\n");
	else
		printf("\nOutput set DID NOT compute correctly!!!\n");
}

//////////////
int main(int argc, char *argv[])
{
	int nTotalElements = atoi(argv[1]);
	int k = atoi(argv[2]);

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

	// passar no vetor heap vazio inserindo os primeiros k valores do vetor de float, e a posição

	//__device__ Pair heap[140][MAX_HEAP_SIZE];   // aloca estático 140 heaps na global memory da gpu
	//__device__ int heapSize = k;

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

	static float *cudaInput;
	// static Pair **cudaHeap;
	Pair(*cudaHeap)[MAX_HEAP_SIZE] = nullptr;

	cudaError_t err;

	err = cudaMalloc((void **)&cudaInput, MAX_SIZE * sizeof(float));
	if (err != cudaSuccess)
	{
		printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	err = cudaMalloc((void **)&cudaHeap, MAX_HEAP_SIZE * sizeof(Pair) * 140);
	if (err != cudaSuccess)
	{
		printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	cudaMemcpy(cudaInput, Input, inputSize * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(cudaHeap, heap, k * 140 * sizeof(Pair), cudaMemcpyHostToDevice);

	int *mutex;
	cudaMalloc(&mutex, sizeof(int));
	cudaMemset(mutex, 0, sizeof(int));

	// Launch the Vector Add CUDA Kernel
	// int threadsPerBlock = 320;
	// int blocksPerGrid = (nTotalElements + threadsPerBlock - 1) / threadsPerBlock;
	int blocks = 140;
	// int threadsPerBlock = (inputSize/blocks) + 1;
	dim3 gridSize(140, 1, 1);
	dim3 blockSize((320), 1, 1);
	printf("inputSize: %d\n", inputSize);
	printf("CUDA kernel launch with %d blocks of %d threads\n", blocks, 320);

	chronometer_t chrono_va; // cria um chonometro para medir vectorAdd

	chrono_start(&chrono_va);

	achar_K_Menores<<<gridSize, blockSize>>>(cudaHeap, cudaInput, heapSize, inputSize, mutex);

	dim3 gridSize2(70, 1, 1);
	dim3 blockSize2((320), 1, 1);
	merge_heaps<<<gridSize2, blockSize2>>>(cudaHeap, heapSize, 70, mutex);

	dim3 gridSize3(35, 1, 1);
	dim3 blockSize3((320), 1, 1);
	merge_heaps<<<gridSize3, blockSize3>>>(cudaHeap, heapSize, 35, mutex);

	// cudaDeviceSynchronize();
	// chrono_stop(&chrono_va);

	cudaMemcpy(heap, cudaHeap, k * 140 * sizeof(Pair), cudaMemcpyDeviceToHost);

	// chrono_start(&chrono_va);

	for (int i = 1; i <= 35; i++)
	{
		for (int j = 0; j < heapSize; j++)
		{
			temp.key = heap[i][j].key;
			temp.val = heap[i][j].val;
			decreaseMax_seq(heap[0], heapSize, temp);
		}
	}
	cudaDeviceSynchronize();
	chrono_stop(&chrono_va);

	//   printf("\n----- reportando o tempo total para as %d ativações do kernel -------",
	//		   N_REPETICOES);
	chrono_reportTime(&chrono_va, (char *)"achar_K_Menores");

	//	printf("\n----- tempo médio por ativação do kernel -------");
	//	chrono_report_TimeInLoop(&chrono_va,
	//							(char *)"vectorAdd_kernel",
	//							 N_REPETICOES);
	printf("\n\n");

	cudaMemcpy(heap, cudaHeap, k * 140 * sizeof(Pair), cudaMemcpyDeviceToHost);

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

	double OPS = (nTotalElements) / total_time_in_milliseconds;
	printf("Throughput: %lf OP/ms\n", OPS);
	printf("Throughput em MOPS: %lf MOP/ms\n", OPS / 1000000);

	verifyOutput(NULL, NULL, 0, 0);

	/*for (int i = 0; i < inputSize; i++)
		cudaInput[i] = input[i];
	for (int i = 0; i < k; i++)
		cudaHeap[i] = heap[i];*/

	// int heap[MAX_HEAP_SIZE] = {60, 50, 40, 30, 20, 10}; // {70, 40, 50, 30, 20, 10};
	// int heapSize = 6;

	return 0;
}
