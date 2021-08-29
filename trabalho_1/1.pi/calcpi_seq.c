#include <stdio.h>
#include "timer.h"
#define N 1e9

int main(int argc, char *argv[]) { /* calcpi_seq.c  */
double pi = 0.0f, start, end; 
long i;
	GET_TIME(start);
    for (i = 0; i < N; i++) {
         double t = (double) ((i+0.5)/N);
         pi += 4.0/(1.0+t*t);
    }
	GET_TIME(end);
    printf("pi = %f\n",pi/N);
	printf("took %f seconds\n", end - start);
    return(0);
}
