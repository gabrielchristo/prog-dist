#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define THREADS 16
#define N 1000000000 // 1 bilhao

int main(int argc, char** argv)
{
	unsigned long total = 0;
	double start, end;

	omp_set_num_threads(THREADS);

	// vetor com N entradas
	int *vector = malloc(N * sizeof(int));

	// atribuindo 1 a todas as entradas do vetor
	// de inicio consideramos todos os numeros como primos
	for(unsigned long i = 0; i < N; i++)
		vector[i] = 1;

	// inicio da medicao
	start = omp_get_wtime();

	for (unsigned long i = 2; i <= (unsigned long) sqrt(N); i++) // vericacao somente ate raiz de N ja basta
	{
        if (vector[i] == 1)
		{
            #pragma omp parallel for schedule(static)
            for(unsigned long j = 2 * i; j < N; j += i) // loop sobre multiplos de i
			{
                #pragma omp atomic write
                vector[j] = 0;	// marcando como nao primo
            }
        }
    }

	// efetuando contagem apos o crivo
	#pragma omp parallel for reduction(+:total)
    for (unsigned long i = 0; i < N; i++)
	{
        if (vector[i])
            total++;
    }

	// fim da medicao
	end = omp_get_wtime();

	// impressao do tempo gasto e total de primos
	// subtraimos 2 do total, pois zero e um nao sao considerados primos
	printf("Total de primos: %lu | Tempo total do algoritmo: %.3f segundos\n", total - 2, end - start);

	return 0;
}