// FEITO POR:
// André Miguel Sikora Marques
// GRR20182593

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

#include "chrono.c"

#include "helper_cuda.h" // mudado aqui por WZ

// para compilar:
// nvcc -arch sm_61 --std=c++14 -o trab3 reduceMax.cu

#define MAX_SIZE ((256 * 1024 * 1024) + 4)
// #define MAX_SIZE 268435460

__device__ static float atomicMax(float *address, float val)
{
	int *address_as_i = (int *)address;
	int old = *address_as_i, assumed;
	do
	{
		assumed = old;
		old = ::atomicCAS(address_as_i, assumed,
						  __float_as_int(::fmaxf(val, __int_as_float(assumed))));
	} while (assumed != old);
	return __int_as_float(old);
}

__device__ float global_max;

__global__ void
reduceMax_coalesced(float *max, float *Input, unsigned nElements)
{
	int thread_index = threadIdx.x + blockIdx.x * blockDim.x;

	if (thread_index == 0)
		global_max = FLT_MIN;

	int increment = blockDim.x * gridDim.x;

	float max_local = FLT_MIN;
	for (int i = thread_index; i < nElements; i += increment)
		if (Input[i] > max_local)
			max_local = Input[i];

	__shared__ unsigned int shared_max[(48 * 1024) / 4];
	if (thread_index < (48 * 1024) / 4)
		shared_max[thread_index] = max_local;
	__syncthreads();

	for (unsigned int stride = blockDim.x; stride > 0; stride /= 2)
	{
		__syncthreads();
		if (thread_index < stride)
			if (shared_max[thread_index] < shared_max[thread_index + stride])
				shared_max[thread_index] = shared_max[thread_index + stride];
	}

	__syncthreads();

	atomicMax(&global_max, shared_max[0]);

	/*
	max_local = shared_max[0];
	for (int i = 1; i < blockDim.x; i++)
		if (shared_max[i] > max_local)
			max_local = shared_max[i];
	*/

	__syncthreads();

	if (thread_index == 0)
		*max = global_max;

}

__global__ void
reduceMax_blockCoalesced(float *max, float *Input, unsigned nElements)
{
	int thread_index = threadIdx.x + blockIdx.x * blockDim.x;

	if (thread_index == 0)
		global_max = FLT_MIN;

	// int increment = blockDim.x * gridDim.x;
	int increment = blockDim.x;

	unsigned int nElements_block = nElements / gridDim.x;

	unsigned int begin = min(nElements_block * blockIdx.x, nElements);
	unsigned int end = min(begin + nElements_block, nElements);

	float max_local = FLT_MIN;
	for (int i = begin; i < end; i += increment)
		if (Input[i] > max_local)
			max_local = Input[i];

	__shared__ unsigned int shared_max[(48 * 1024) / 4];
	if (thread_index < (48 * 1024) / 4)
		shared_max[thread_index] = max_local;
	__syncthreads();

	for (unsigned int stride = blockDim.x; stride > 0; stride /= 2)
	{
		__syncthreads();
		if (thread_index < stride)
			if (shared_max[thread_index] < shared_max[thread_index + stride])
				shared_max[thread_index] = shared_max[thread_index + stride];
	}

	/*
	for (unsigned int stride = 1; stride <= blockDim.x; stride *= 2)
	{
		__syncthreads();
		if (thread_index % stride == 0)
			if (shared_max[thread_index] < shared_max[thread_index + stride])
				shared_max[thread_index] = shared_max[thread_index + stride];
	}
	*/

	__syncthreads();

	atomicMax(&global_max, shared_max[0]);

	/*
	max_local = shared_max[0];
	for (int i = 1; i < blockDim.x; i++)
		if (shared_max[i] > max_local)
			max_local = shared_max[i];
	*/

	__syncthreads();

	if (thread_index == 0)
		max[0] = global_max;
}

//////////////
int main(int argc, char *argv[])
{

	if (argc < 3)
	{
		fprintf(stderr, "usage:\n\t./trab2 <nTotalElements> <nR>\n");
		exit(-1);
	}

	int nTotalElements = atoi(argv[1]);
	int nR = atoi(argv[2]);

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

	static float *cudaInput;
	static float *cudaMax;

	cudaError_t err;

	err = cudaMalloc((void **)&cudaInput, MAX_SIZE * sizeof(float));
	if (err != cudaSuccess)
	{
		printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	err = cudaMalloc((void **)&cudaMax, sizeof(float));
	if (err != cudaSuccess)
	{
		printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	float max[1] = {FLT_MIN};
	cudaMemcpy(cudaInput, Input, inputSize * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(cudaMax, max, sizeof(float), cudaMemcpyHostToDevice);

	printf("\n\n");

	chronometer_t chrono_va; // cria um chonometro para medir vectorAdd

	long long time = 0;
	for(int i = 0; i < nR; i++){
		chrono_reset(&chrono_va);
		chrono_start(&chrono_va);
		reduceMax_coalesced<<<56, 1024>>>(cudaMax, cudaInput, nTotalElements);
		cudaDeviceSynchronize();
		chrono_stop(&chrono_va);
		time += chrono_gettotal(&chrono_va);
	}
	double avg_ms_coalesced = (double)time/(nR * 1000);
	printf("avg_time_coalesced: %f microseconds\n", avg_ms_coalesced);

	double OPS = ((double)nTotalElements * 1000 * 1000) / (avg_ms_coalesced * (1000 * 1000 * 1000));
	printf("throughput_coalesced: %lf GOP/s\n\n", OPS);

	max[0] = FLT_MIN;
	cudaMemcpy(cudaMax, max, sizeof(float), cudaMemcpyHostToDevice);
	time = 0;
	for(int i = 0; i < nR; i++){
		chrono_reset(&chrono_va);
		chrono_start(&chrono_va);
		reduceMax_blockCoalesced<<<56, 1024>>>(cudaMax, cudaInput, nTotalElements);
		cudaDeviceSynchronize();
		chrono_stop(&chrono_va);
		time += chrono_gettotal(&chrono_va);
	}
	double avg_ms_blockCoalesced = (double)time/(nR * 1000);
	printf("avg_time_blockCoalesced: %f microseconds\n", avg_ms_blockCoalesced);

	OPS = ((double)nTotalElements * 1000 * 1000) / (avg_ms_blockCoalesced * (1000 * 1000 * 1000));
	printf("throughput_blockCoalesced: %lf GOP/s\n", OPS);

	printf("\n\n");

	double speedup = avg_ms_coalesced / avg_ms_blockCoalesced;
	printf("speedup: %f\n", speedup);

	printf("\n\n");

	err = cudaGetLastError();

	if (err != cudaSuccess)
	{
		fprintf(stderr, "Failed to launch reduceMax kernel (error code %s)!\n", cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	//double total_time_in_milliseconds = (double)chrono_gettotal(&chrono_va) /
	//									((double)1000 * 1000);
	//printf("total_time_in_milliseconds: %lf ms\n", total_time_in_milliseconds);

	return 0;
}
