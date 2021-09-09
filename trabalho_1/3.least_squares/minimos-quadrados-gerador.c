#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#define MAX_ABS_EPSILON 2.0
#define MAX_ABS_COEFF 100.0

double random_in_range(double max_abs) {
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return scale * ( 2*max_abs ) - max_abs;  /* [min, max] */
}

double f(int x, double a, double b) {
    return a*x + b + random_in_range(MAX_ABS_EPSILON);
}

int main(int argc, char *argv[]) {
    int meu_ranque, num_procs, i, raiz = 0;
    double *y_total,  *y_parcial;
    double a, b;
    int x, n, n_por_proc;
    FILE *out_file;
    
	if (argc < 2) {
        printf("Entre com o valor de n.\n");
        return 1;
    } else {
        n = strtol(argv[1], (char **) NULL, 10);
    }

    out_file = fopen("xydata", "w");
    if (out_file == NULL) {
        printf("error opening file\n");
        return 1;
    }
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    
    n_por_proc = n/num_procs;
    srand(time(NULL));
    // O processo raiz aloca o vetor de recepção e 
    // gera os coeficientes da função linear.
	if (meu_ranque == raiz){
        a = random_in_range(MAX_ABS_COEFF);
        b = random_in_range(MAX_ABS_COEFF);
        y_total = (double *) malloc(n*sizeof(double)); 
    }

    y_parcial = (double *) malloc((n_por_proc)*sizeof(double)); 

    MPI_Bcast(&a, 1, MPI_DOUBLE, raiz, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_DOUBLE, raiz, MPI_COMM_WORLD);

    // Cada processo calcula um pedaço de y
	for (i = 0; i < n_por_proc; i++) {
        x = i + meu_ranque*(n_por_proc);
        y_parcial[i] = f(x, a, b);
    }
    // O vetor é recebido pelo processo raiz com as partes recebidas de todos processos, incluindo o processo raiz
	MPI_Gather (y_parcial, n_por_proc, MPI_DOUBLE, y_total, n_por_proc, MPI_DOUBLE, raiz, MPI_COMM_WORLD);
	// O processo raiz calcula o resto do y 
    if (meu_ranque == raiz && n%num_procs != 0) {
        for (i = n%num_procs; i > 0; i--) {
            x = n - i;
            y_total[x] = f(x, a, b);
        }
    }
    // O processo raiz escreve no arquivo
	if (meu_ranque == raiz) {
        printf("Foram geradas %d linhas com a função %lfx + %lf\n", n, a, b);
        fprintf(out_file, "%d\n", n);

	    for (i = 0; i < n; i ++) {
            fprintf(out_file, "%lf %lf\n", (double) i, y_total[i]);
	    }
	}
	/* Termina a execução */
	MPI_Finalize();
	return(0);
}