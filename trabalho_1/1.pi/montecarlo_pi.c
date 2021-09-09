/**
 *
 * Autor: Adrian Statescu mergesortv@gmail.com http://adrianstatescu.com
 *
 * Descrição:  Programa em C Program para computar o valor de PI usando o método de Monte Carlo.
 *
 * Licença MIT 
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"
#define SEED time(NULL)

int main() {

 srand( SEED );
 long i, n=1e11, count;
 double x,y,z,pi,start,end;

 printf("n = %ld \n", n);

 count = 0;

 GET_TIME(start);

 for(i = 0; i < n; ++i) {

     x = (double)rand() / RAND_MAX;

     y = (double)rand() / RAND_MAX;

     z = x * x + y * y;

     if( z <= 1 ) count++;
 }

 pi = (double) count / n * 4;

 GET_TIME(end);
 
 printf("Aproximação de PI é = %g\n", pi);
 printf("took %f seconds\n", end - start);

 return(0);
}
