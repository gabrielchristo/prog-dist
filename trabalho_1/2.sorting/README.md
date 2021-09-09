## Objetivo

Elaborar um programa para ordernação paralela de um vetor de N números aleatórios

## Abordagem

Particionamos o vetor gerado pelo processo raiz para os demais processos através da operação **MPI_Scatterv**

Cada processo realiza a ordenação parcial dos dados recebidos de forma serial através do algoritmo merge sort.

Após a ordenação parcial o processo raiz trata os dados recebidos dos outros processos através da operação **MPI_Gatherv** e processa o resultado com uma chamada final ao merge sort.

O algoritmo local sequencial escolhido foi o merge sort devido possuir melhor complexidade de execução, que é O(n log n).


## Desempenho

Para avaliar o desempenho utilizamos o método **MPI_Wtime**.

| Elementos / Versão | Paralela - 1 processo | Paralela - 2 processos | Paralela - 4 processos | Paralela - 8 processos | Paralela - 12 processos | Paralela - 16 processos |
|--------------------|-----------------------|------------------------|------------------------|------------------------|-------------------------|-------------------------|
| 10 milhôes         | 3.96 s                | 2.68 s                 | 2.11 s                 | 2.14 s                 | 2.18 s                  | 2.23 s                  |
| 20 milhôes         | 8.25 s                | 5.71 s                 | 4.47 s                 | 4.57 s                 | 4.54 s                  | 4.70 s                  |
| 40 milhôes         | 17.52 s               | 11.93 s                | 9.45 s                 | 9.67 s                 | 9.71 s                  | 9.82 s                  |
