// FEITO POR:
// André Miguel Sikora Marques
// GRR20182593

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "chrono.c"

// (c) by W.Zola set/23
//
// EXAMPLE Sequential MAX-Heap,
//                              decreaseMax operation
//                              and others

// para compilar:
// gcc -O3 max-heap.c -o max-heap -lm

// #define SHOW_DECREASE_MAX_STEPS 1

#define MAX_HEAP_SIZE (1024 * 1024)
#define MAX_SIZE 20000000

typedef struct
{
        float key; // inserir um valor v float na chave
                   // (obtido do vetor de entrada Input)
        int val;   // inserir a posiçao p como valor val
} Pair;

void drawHeapTree(Pair heap[], int size, int nLevels) // FIX ME!
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

void swap(Pair *a, Pair *b) //__attribute__((always_inline));
{
        Pair temp = *a;
        *a = *b;
        *b = temp;
}

void maxHeapify(Pair heap[], int size, int i)
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
                        swap(&heap[i], &heap[largest]); // Using the swap function
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

void heapifyUp(Pair heap[], int *size, int pos)
{
        int val = heap[pos].key;
        while (pos > 0 && val > heap[parent(pos)].key)
        {
                heap[pos] = heap[parent(pos)];
                pos = parent(pos);
        }
        heap[pos].key = val;
}

void insert(Pair heap[], int *size, Pair element)
{
        *size += 1;
        int last = *size - 1;

        heap[last] = element;
        heapifyUp(heap, size, last);
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

void decreaseMax(Pair heap[], int size, Pair new_value)
{
        if (size == 0) // Heap is empty
                return;

        if (heap[0].key > new_value.key)
        {
                heap[0] = new_value;
#if SHOW_DECREASE_MAX_STEPS
                drawHeapTree(heap, size, 4);
                printf("        ~~~~~~~~~~~~~~~~~~~~~~~~~\n");
#endif
                maxHeapify(heap, size, 0);
        }
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

        // passar no vetor heap vazio inserindo os prmieiros k valores do vetor de float, e a posição

        chronometer_t chrono_va; // cria um chonometro para medir vectorAdd

        chrono_start(&chrono_va);

        static Pair heap[MAX_HEAP_SIZE];
        int heapSize = 0;

        Pair temp;
        for (int i = 0; i < k; i++)
        {
                temp.key = Input[i];
                temp.val = i;
                insert(heap, &heapSize, temp);
        }

        for (int i = k; i < nTotalElements; i++)
        {
                temp.key = Input[i];
                temp.val = i;
                decreaseMax(heap, heapSize, temp);
        }

        chrono_stop(&chrono_va);

        //   printf("\n----- reportando o tempo total para as %d ativações do kernel -------",
        //           N_REPETICOES);
        chrono_reportTime(&chrono_va, (char *)"achar_K_Menores");

        double total_time_in_milliseconds = (double)chrono_gettotal(&chrono_va) /
                                            ((double)1000 * 1000);
        printf("total_time_in_milliseconds: %lf ms\n", total_time_in_milliseconds);

        double OPS = (nTotalElements) / total_time_in_milliseconds;
        printf("Throughput: %lf OP/ms\n", OPS);
        printf("Throughput em MOPS: %lf MOP/ms\n", OPS / 1000000);

        for (int i = 0; i < k; i++)
        {
                // printf("[%f, %d] ", heap[i].key, heap[i].val);
        }

        // dividir (por exemplo) em 2 blocos de threads que recebem 1000 sobra o resto pra fica fazendo decrease
        // entre cada bloco (cada bloco faz um decrease pra um valor)
        // no final esses 2 blocos de threads metade dos kMenores fica em um e metade no outro (não?)

        // algumas leem algumas inserem

        // int heap[MAX_HEAP_SIZE] = {60, 50, 40, 30, 20, 10}; // {70, 40, 50, 30, 20, 10};
        // int heapSize = 6;

        /*
                printf(">>>Max-Heap before decrease operation:\n");
                for (int i = 0; i < heapSize; ++i)
                {
                        printf("[%3lf, %d]", heap[i].key, heap[i].val);
                }
                printf("\n");

                printf("------Max-Heap Tree------\n");
                drawHeapTree(heap, heapSize, 3);

                //decreaseMax(heap, heapSize, 5); // Decreasing the maximum value to 5

                printf("\nMax-Heap after decrease operation:\n");
                for (int i = 0; i < heapSize; ++i)
                {
                        printf("%lf ", heap[i].key);
                }
                printf("\n");

                printf("------Max-Heap Tree------\n");
                drawHeapTree(heap, heapSize, 3);

                printf("=========================\n");
                Pair data[12];
                data[0].key = 40;
                data[0].val = 0;
                data[1].key = 10;
                data[1].val = 1;
                data[2].key = 30;
                data[2].val = 2;
                data[3].key = 70;
                data[3].val = 3;
                data[4].key = 50;
                data[4].val = 4;
                data[5].key = 20;
                data[5].val = 5;
                data[6].key = 4;
                data[6].val = 6;
                data[7].key = 5;
                data[7].val = 7;
                data[8].key = 44;
                data[8].val = 8;
                data[9].key = 40;
                data[9].val = 9;
                data[10].key = 55;
                data[10].val = 10;
                data[11].key = 50;
                data[11].val = 11;

                // int data[] = {40, 10, 30, 70, 50, 20, 4, 5, 44, 40, 55, 50};
                int n = sizeof(data) / sizeof(data[0]);

                // empty heap
                heapSize = 0;
                printf("EMPTY heap!\n");

                printf("will insert: ");
                for (int i = 0; i < n; i++)
                {
                        printf("%f ", data[i].key);
                }
                printf("\n");

                for (int i = 0; i < n; i++)
                {
                        printf("inserting %f\n", data[i].key);
                        insert(heap, &heapSize, data[i]);
                        printf("------Max-Heap Tree------ ");
                        if (isMaxHeap(heap, heapSize))
                                printf("is a heap!\n");
                        else
                                printf("is NOT a heap!\n");
        #ifndef SHOW_DECREASE_MAX_STEPS
                        drawHeapTree(heap, heapSize, 4);
        #endif
                }
        #ifdef SHOW_DECREASE_MAX_STEPS
                drawHeapTree(heap, heapSize, 4);
        #endif

                printf("=========================\n");
                printf("=====decreaseMAX tests===\n");
                Pair data2[12];
                data2[0].key = 4;
                data2[0].val = 0;
                data2[1].key = 10;
                data2[1].val = 1;
                data2[2].key = 30;
                data2[2].val = 2;
                data2[3].key = 70;
                data2[3].val = 3;
                data2[4].key = 55;
                data2[4].val = 4;
                data2[5].key = 20;
                data2[5].val = 5;
                data2[6].key = 4;
                data2[6].val = 6;
                data2[7].key = 5;
                data2[7].val = 7;
                data2[8].key = 25;
                data2[8].val = 8;

                // int data2[] = {4, 10, 30, 70, 55, 20, 4, 5, 25};
                n = sizeof(data2) / sizeof(data2[0]);

                printf("will decreaseMAX to the following values: ");
                for (int i = 0; i < 9; i++) // i < n
                {
                        printf("%f ", data2[i].key);
                }
                printf("\n");

                for (int i = 0; i < 9; i++)
                {
                        printf("decreaseMAX to %f\n", data2[i].key);
                        int new_value = data2[i].key;
                        decreaseMax(heap, heapSize, new_value);

                        printf("------Max-Heap Tree (after decrease)------ ");
                        if (isMaxHeap(heap, heapSize))
                                printf("is a max heap!\n");
                        else
                                printf("is NOT a max heap!\n");

                        // #ifndef SHOW_DECREASE_MAX_STEPS
                        drawHeapTree(heap, heapSize, 4);
                        // #endif
                }
        */
        return 0;
}