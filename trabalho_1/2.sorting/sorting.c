#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N 40000000

int* generateRandomArray(int size)
{
	// cria array com numeros aleatorios
	int* array = (int*) malloc(size * sizeof(int));
	for(int i = 0; i < size; i++)
		array[i] = rand() % size;
	return array;
}

void printArray(int* array, int size)
{
	// imprime conteudo de um array
	for(int i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n");
}

void merge(int* source, int* destination, int low, int middle, int high)
{
	// aplicar ordenacao no novo array
	int h, i, j, k;
	h = low;
	i = low;
	j = middle + 1;
	
	while((h <= middle) && (j <= high)) {
		if(source[h] <= source[j]) {
			destination[i] = source[h];
			h++;
		}
		else {
			destination[i] = source[j];
			j++;
		}
		i++;
	}
	if(middle < h) {
		for(k = j; k <= high; k++) {
			destination[i] = source[k];
			i++;
		}	
	}
	else {
		for(k = h; k <= middle; k++) {
			destination[i] = source[k];
			i++;
		}	
	}
	for(k = low; k <= high; k++) {
		source[k] = destination[k];	
	}
}

void mergeSort(int* source, int* destination, int low, int high)
{
	// merge sort recursivo
	if(low < high)
	{
		int middle = (low + high)/2;
		mergeSort(source, destination, low, middle);
		mergeSort(source, destination, (middle + 1), high);
		merge(source, destination, low, middle, high);
	}
}


int main(int argc, char** argv)
{
	// declaracao de variaveis
	int rank, size, root_rank = 0, *buffer, *local_buffer, *ordered, *parcial_ordered, *gather_result;
	double start, end;
	int *counts, *displacements;

	// mpi init
	MPI_Init(&argc, &argv);

	// rank e numero de processos
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	// auxiliares para scatterv e gatherv
	counts = (int*) malloc(size * sizeof(int));
	displacements = (int*) malloc(size * sizeof(int));

	// criacao do array
	if(rank == root_rank){
		buffer = generateRandomArray(N);
		//printArray(buffer, N);
	}

	// inicio medicao tempo
	start = MPI_Wtime();

	// divisao do array entre os processos via scatter
	int splittedSize = N / size;
	int blockEnd = (rank == size - 1) ? N : splittedSize * (1 + rank);
	for(int i = 0; i < size; i++){
		counts[i] = (i == size - 1) ? splittedSize + N % size : splittedSize;
		displacements[i] = splittedSize * i;
	}
	printf("Process %d with local buffer index from %d to %d (size = %d)\n", rank, displacements[rank], blockEnd, counts[rank]);

	local_buffer = (int*) malloc(counts[rank] * sizeof(int));
	MPI_Scatterv(buffer, counts, displacements, MPI_INT, local_buffer, counts[rank], MPI_INT, root_rank, MPI_COMM_WORLD);

	// merge sort parcial de todos os processos
	parcial_ordered = (int*) malloc(counts[rank] * sizeof(int));
	mergeSort(local_buffer, parcial_ordered, 0, counts[rank] - 1);

	// coleta do resultado para buffer
	if(rank == root_rank){
		ordered = (int*) malloc(N * sizeof(int));
		gather_result = (int*) malloc(N * sizeof(int));
	}
	MPI_Gatherv(local_buffer, counts[rank], MPI_INT, gather_result, counts, displacements, MPI_INT, root_rank, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	// merge sort em cima do resultado do gatherv
	if(rank == root_rank){
		mergeSort(gather_result, ordered, 0, N - 1);
		//printArray(ordered, N);
		free(ordered);
		free(gather_result);
		free(buffer);
	}

	// fim medicao de tempo
	end = MPI_Wtime();
	printf("Process %d took %.3f seconds\n", rank, end - start);

	// liberando memoria
	free(counts);
	free(displacements);
	free(local_buffer);
	free(parcial_ordered);

	// fim do programa
	MPI_Finalize();
	return 0;
}
