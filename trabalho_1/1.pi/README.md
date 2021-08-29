## Objetivos

- Paralelizar o programa **calcpi_seq.c**
- Paralelizar o programa **montecarlo_pi.c**

## Abordagem para calcpi_seq.c

A abordagem aqui é dividir a carga de trabalho do loop principal, onde estão sendo realizados os cálculos de aproximação da integral com o método do trapézio.

Para tal, dividimos o número de iterações N entre todos os processos. No caso dessa divisão não ser inteira deixamos as iterações excedentes com o processo de maior ranque.

## Avaliação de desempenho para calcpi_seq.c

Utilizamos a rotina definida no arquivo **timer.h** para medição de tempo da versão sequencial. Já o desempenho da versão paralela foi medido com a rotina **MPI_Wtime**.

Como os resultados de cada execução podem variar, utilizamos como referência a média dos valores obtidos com 3 rodadas, considerando todos os processos. Com isso obtemos a seguinte tabela:

| Precisão / Versão | Sequencial | Paralela - 1 processo | Paralela - 2 processos | Paralela - 4 processos | Paralela - 8 processos | Paralela - 12 processos | Paralela - 16 processos |
|-------------------|------------|-----------------------|------------------------|------------------------|------------------------|-------------------------|-------------------------|
| 10^9              | 3,382 s    | 3,238 s               | 1,638 s                | 0,839 s                | 0,846 s                | 0,824 s                 | 0,847 s                 |
| 10^10             | 33,986 s   | 33,347 s              | 16,732 s               | 8,627 s                | 8,589 s                | 8,776 s                 | 8,491 s                 |
| 10^11             | 336,967 s  | 333,379 s             | 170,059 s              | 89,580 s               | 86,993 s               | 86,485 s                | 87,040 s                |

TODO: grafico speedup e eficiencia

## Abordagem para montecarlo_pi.c

TODO: avaliar com 1,2,4,8,12 e 16 processos

TODO: montar grafico com tempo total, speedup e eficiencia


## Avaliação de desempenho para montecarlo_pi.c

TODO: avaliar com 1,2,4,8,12 e 16 processos

TODO: montar grafico com tempo total, speedup e eficiencia