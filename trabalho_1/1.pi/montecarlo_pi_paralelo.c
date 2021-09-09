/*
	Versao paralela do codigo montecarlo_pi
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define SEED time(NULL)
#define N 1e9

int main(int argc, char** argv)
{
	// definicao de variaveis
	srand( SEED );
	int rank, size, root_rank = 0;
	long count = 0, parcial_count = 0;
	double x,y,z,pi,start,end;

	// mpi init
	MPI_Init(&argc, &argv);

	// rank e numero de processos
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == root_rank)
 		printf("N = %ld\n", (long) N);

	// inicio medicao de tempo
	start = MPI_Wtime();

	// divisao do loop principal
	long blockSize = N / size;
	long blockEnd = rank == (size - 1) ? N : blockSize * (1 + rank);
 	for(long i = rank * blockSize; i < blockEnd; i++) {

     	x = (double)rand() / RAND_MAX;
     	y = (double)rand() / RAND_MAX;
     	z = x * x + y * y;

     	if( z <= 1 ) parcial_count++;
 	}

	// reducao das somas parciais para processo raiz
	MPI_Reduce(&parcial_count, &count, 1, MPI_LONG, MPI_SUM, root_rank, MPI_COMM_WORLD);

	// fim medicao de tempo
	end = MPI_Wtime();
	printf("processo %d consumiu %.3f segundos\n", rank, end - start);
	MPI_Barrier(MPI_COMM_WORLD);

	// print da aproximacao
	pi = (double) count / N * 4;
	if(rank == root_rank)
    	printf("Aproximacao de PI é = %g\n", pi);
	
	// fim do programa
	MPI_Finalize();
	return 0;
}
