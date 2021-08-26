## Objetivo

- Elaborar programa para gerar N pares de coordenadas (X, Y)
- Modificar o programa **minimos-quadrados-original.c**
	- Enviar valor de N e das coordenadas para todos os processos utilizando uma rotina de comunicação coletiva
	- Escrever versão usando **MPI_Isend()** para enviar coordenadas para cada processo
	- Utilizar comunicação coletiva (redução) para recepção das somas parciais

## Abordagem

TODO

## Desempenho

TODO: rodar com 1,2,4,8,12 e 16 processos com N=10^6,10^7 e 10^8

TODO: grafico com tempo total, speedup e eficiencia