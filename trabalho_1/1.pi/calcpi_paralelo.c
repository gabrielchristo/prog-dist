/*
	Versao paralela do codigo calcpi_seq
*/

#include <stdio.h>
#include "mpi.h"
#define N 1e9

int main(int argc, char **argv)
{
	// declaracao de variaveis
	double pi = 0.0f, soma_parcial = 0.0f, start, end;
	int rank, size, root_rank = 0;

	// mpi init
	MPI_Init(&argc, &argv);

	// rank e numero de processos
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	// inicio medicao de tempo
	start = MPI_Wtime();

	// divisao do loop principal
	long blockSize = N / size;
	long blockEnd = rank == (size - 1) ? N : blockSize * (1 + rank);
    for (long i = rank * blockSize; i < blockEnd; i++)
	{
        double t = (double) ((i+0.5)/N);
        soma_parcial += 4.0/(1.0+t*t);
    }

	// reducao das somas parciais para processo raiz
	MPI_Reduce(&soma_parcial, &pi, 1, MPI_DOUBLE, MPI_SUM, root_rank, MPI_COMM_WORLD);

	// fim medicao de tempo
	end = MPI_Wtime();
	printf("processo %d consumiu %.3f segundos\n", rank, end - start);
	MPI_Barrier(MPI_COMM_WORLD);

	// print da aproximacao
	if(rank == root_rank)
    	printf("pi = %f\n", pi/N);

	// fim do programa
	MPI_Finalize();
    return 0;
}
