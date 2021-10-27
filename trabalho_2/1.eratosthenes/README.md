## Objetivo

Desenvolver um programa OpenMP capaz de verificar o total de números primos entre 2 e N, através do crivo de Eratóstenes.

## Abordagem

O loop principal responsável pela verificação dos múltiplos de cada primo foi paralelizado com a diretiva `parallel for`. O balanceamento foi estático devido a atribuição do valor zero a determinada entrada do vetor ser uma tarefa de custo constante. Nessa mesma atribuição utilizamos a diretiva `atomic write` para garantir atomicidade na escrita do valor atualizado no vetor.

Após o crivo, dividimos a tarefa de contagem da quantidade de primos no vetor com a diretiva `parallel for` em conjunto com a redução do valor total, de diretiva `reduction(+:total)`.

## Desempenho

Para avaliar o desempenho foi testado o programa com 1, 8 e 16 threads.

O valor de N utilizado foi 1 bilhão, que foi o máximo permitido pela alocação de memória da máquina, necessário para alocar o vetor.

| Threads | Tempo   | Speedup | Eficiência |
|---------|---------|---------|------------|
| 1       | 25,56 s | 1,00    | 1,00       |
| 8       | 12,44 s | 2,05    | 0,25       |
| 16      | 12,57 s | 2,03    | 0,12       |

Para 16 threads o ganho foi essencialmente o mesmo de 8 threads.