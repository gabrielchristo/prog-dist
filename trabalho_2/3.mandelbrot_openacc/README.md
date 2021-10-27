## Objetivo

Desenvolver paralelização em OpenACC do programa Mandelbrot, a partir da versão sequencial.

## Abordagem

Através da diretiva do OpenACC `parallel for` e com a movimentação de dados, conseguimos paralelizar o loop principal, responsável pelo cálculo iterativo do Mandelbrot.

## Desempenho

Em comparação com a versão OpenMP não obtivemos ganho significativo, mantendo parecida a base do tempo de execução.