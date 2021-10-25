## Objetivo
Implementação de uma versão paralela em OpenMP da simulação 2-D de transferência de calor em uma 
placa de metal NxN, utilizando o método Gauss-Seidel SOR (successive over-relaxation). Este 
método funciona realizando M iterações, nas quais é calculada a temperatura de cada ponto de uma
placa de metal como a média de cada um dos seus vizinhos. A versão sequencial pode ser obtida 
no AVA. 

Dados para o problema:
- Número de iterações: 4098
- Tamanho da placa de metal: 1022
- A temperatura inicial da placa é 20 graus celsius
- A temperatura da fonte de calor localizada no ponto 800x800 (meio da placa) da placa é 100 graus celsius
- As bordas estão sempre com a temperatura igual a 20 graus celsius

## Abordagem



## Desempenho
Demorou 21.8556 segundos para executar o algoritmo em uma placa de metal de 1022x1022. Erro maximo na iteracao 45 era 0.009623
