## Objetivos

- Comparar diferentes versões do programa paralelo para cálculo de números primos
- Analisar escalabilidade com Lei de Gustafson e número de processadores adequado

## Abordagem

Executar versões paralelas com 1,2,4,8,12 e 16 processos

Utilizar valores de N=10^9,10^10 e 10^11

 - Aqui temos um processo (mestre) que fica responsável por enviar as tarefas 
 os demais processos (trabalhadores). Assim que uma tarefa é terminada e o resultado
 enviado para o mestre, uma outra tarefa será alocada para o trabalhador e assim sucessivamente
 até que não haja mais tarefas para serem executadas.
 - Como forma de evitar uma sobrecarga na comunicação, esse método requer que cada tarefa
 tenha um tamanho mínimo, para manter o processador ocupado por um tempo razoavelmente
 grande.
 - Podemos observar que existe uma sobrecarga maior por conta de uma quantidade maior de
 mensagens enviadas, mas o comportamento do programa é melhor como um todo, apresen-
 tando um gráfico com curvas mais bem comportadas.
 - As rotinas de envio e recepção utilizadas foram a do modo padrão, ou seja, para mensagens
 de pequeno tamanho o envio e recepção são bufferizados, permitindo que o programa funcione
 corretamente.

## Desempenho

## Avaliação de desempenho para mpi_primos.c

Executamos com 1,2,4,8,12 e 16 processos com N=10^9,10^10 e 10^11

Utilizamos a rotina definida no arquivo **timer.h** para medição de tempo da versão sequencial. Já o desempenho da versão paralela foi medido com a rotina **MPI_Wtime**.

Como os resultados de cada execução podem variar, utilizamos como referência a média dos valores obtidos com 3 rodadas, considerando todos os processos. Com isso obtemos a seguinte tabela:

| Precisão / Versão | Sequencial | Paralela - 1 processo | Paralela - 2 processos | Paralela - 4 processos | Paralela - 8 processos | Paralela - 12 processos | Paralela - 16 processos |
|-------------------|------------|-----------------------|------------------------|------------------------|------------------------|-------------------------|-------------------------|
| 10^9              | 28.654 s    | 28.524 s               | 25.646 s                | 23.906 s                | 22.534 s                | 21.264 s                 | 16.294 s                 |
| 10^10             | 49,267 s   | 48,129 s              | 33,127 s               | 36,342 s                | 31,545 s                | 31,634 s                 | 28,347 s                 |
| 10^11             | 316,346 s  | 301,427 s             | 140,349 s              | 89,233 s               | 86,471 s               | 80,234 s                | 85,040 s                |


## Avaliação de desempenho para mpi_primosbag.c

Executamos com 1,2,4,8,12 e 16 processos com N=10^9,10^10 e 10^11

Utilizamos a rotina definida no arquivo **timer.h** para medição de tempo da versão sequencial. Já o desempenho da versão paralela foi medido com a rotina **MPI_Wtime**.

Como os resultados de cada execução podem variar, utilizamos como referência a média dos valores obtidos com 3 rodadas, considerando todos os processos. Com isso obtemos a seguinte tabela:

| Precisão / Versão | Sequencial | Paralela - 1 processo | Paralela - 2 processos | Paralela - 4 processos | Paralela - 8 processos | Paralela - 12 processos | Paralela - 16 processos |
|-------------------|------------|-----------------------|------------------------|------------------------|------------------------|-------------------------|-------------------------|
| 10^9              | 27.323 s    | 26.670 s               | 24.248 s                | 23.380 s                | 12.967 s                | 11.450 s                 | 16.294 s                 |
| 10^10             | 54,986 s   | 51,234 s              | 43,325 s               | 45,543 s                | 41,253 s                | 41,678 s                 | 38,347 s                 |
| 10^11             | 406,967 s  | 401,379 s             | 222,349 s              | 155,524 s               | 132,923 s               | 81,345 s                | 89,130 s                |


## Análise de Escalabilidade

TODO