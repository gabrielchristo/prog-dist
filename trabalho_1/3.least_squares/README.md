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
## Avaliação de desempenho para minimos-quadrados-coletivo.c
Executamos com 1,2,4,8,12 e 16 processos com N=10^6,10^7 e 10^8

Utilizamos a rotina definida no arquivo **timer.h** para medição de tempo da versão sequencial. Já o desempenho da versão paralela foi medido com a rotina **MPI_Wtime**.

Como os resultados de cada execução podem variar, utilizamos como referência a média dos valores obtidos com 3 rodadas, considerando todos os processos. Com isso obtemos a seguinte tabela:

| Precisão / Versão | Sequencial | Paralela - 1 processo | Paralela - 2 processos | Paralela - 4 processos | Paralela - 8 processos | Paralela - 12 processos | Paralela - 16 processos |
|-------------------|------------|-----------------------|------------------------|------------------------|------------------------|-------------------------|-------------------------|
| 10^6              | 7.521 s    | 7.670 s               | 5.646 s                | 3.380 s                | 2.967 s                | 1.450 s                 | 16.294 s                 |
| 10^7             | 43,986 s   | 43,234 s              | 23,325 s               | 15,543 s                | 11,253 s                | 11,678 s                 | 8,347 s                 |
| 10^8             | 236,967 s  | 233,379 s             | 140,349 s              | 89,524 s               | 86,923 s               | 86,345 s                | 87,040 s                |



## Avaliação de desempenho para minimos-quadrados-isend.c
Executamos com 1,2,4,8,12 e 16 processos com N=10^6,10^7 e 10^8

Utilizamos a rotina definida no arquivo **timer.h** para medição de tempo da versão sequencial. Já o desempenho da versão paralela foi medido com a rotina **MPI_Wtime**.

Como os resultados de cada execução podem variar, utilizamos como referência a média dos valores obtidos com 3 rodadas, considerando todos os processos. Com isso obtemos a seguinte tabela:
| Precisão / Versão | Sequencial | Paralela - 1 processo | Paralela - 2 processos | Paralela - 4 processos | Paralela - 8 processos | Paralela - 12 processos | Paralela - 16 processos |
|-------------------|------------|-----------------------|------------------------|------------------------|------------------------|-------------------------|-------------------------|
| 10^6              | 6.232 s    | 7.234 s               | 4.632 s                | 3.355 s                | 2.214 s                | 1.325 s                 | 15.254 s                 |
| 10^7             | 42,345 s   | 42,435 s              | 23,236 s               | 15,543 s                | 11,367 s                | 11,346 s                 | 8,456 s                 |
| 10^8             | 236,578 s  | 233,242 s             | 120,356 s              | 79,588 s               | 76,857 s               | 76,123 s                | 67,564 s                |
