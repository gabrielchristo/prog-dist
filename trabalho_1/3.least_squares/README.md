## Objetivo

- Elaborar programa para gerar N pares de coordenadas (X, Y)
- Modificar o programa **minimos-quadrados-original.c**
	- Enviar valor de N e das coordenadas para todos os processos utilizando uma rotina de comunicação coletiva
	- Escrever versão usando **MPI_Isend()** para enviar coordenadas para cada processo
	- Utilizar comunicação coletiva (redução) para recepção das somas parciais

## Abordagem

 - Este programa calcula um modelo linear para um conjunto de dados fornecidos.
 - Os dados são lidos de um arquivo; a primeira linha é o número de pontos de dados (n), seguido pelas coordenadas de x e y.
 - Os pontos de dados são divididos entre os processos de forma que cada processo tenha naverage = n / numprocs pontos; os pontos de dados restantes são adicionados ao último processo.
 - Cada processo calcula as somas parciais (mySUMx, mySUMy, mySUMxy, mySUMxx) independentemente, usando seu subconjunto de dados. Na etapa final, as somas globais (SUMx, SUMy, SUMxy, SUMxx) são calculadas para encontrar a linha de mínimos quadrados.
 - Para o propósito deste exercício, a comunicação é feita estritamente usando as operações ponto a ponto MPI, MPI_SEND e MPI_RECV. 

## Desempenho

TODO: rodar com 1,2,4,8,12 e 16 processos com N=10^6,10^7 e 10^8

TODO: grafico com tempo total, speedup e eficiencia

| Precisão / Versão | Sequencial | Paralela - 1 processo | Paralela - 2 processos | Paralela - 4 processos | Paralela - 8 processos | Paralela - 12 processos | Paralela - 16 processos |
|-------------------|------------|-----------------------|------------------------|------------------------|------------------------|-------------------------|-------------------------|
| 10^6              | qqqqq s    | 7.670 s               | 8.646 s                | 9.380 s                | 11.967 s                | 14.450 s                 | 16.294 s                 |
| 10^7             | qqqqq s   | qqqqqq s              | qqqqqq s               | qqqqqq s                | qqqqqq s                | qqqqqq s                 | qqqqqq s                 |
| 10^8             | qqqqqq s  | qqqqqq s             | qqqqqq s              | qqqqqq s               | qqqqqq s               | qqqqqq s                | qqqqqq s   