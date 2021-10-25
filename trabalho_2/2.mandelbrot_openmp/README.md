## Objetivo
Paralelizar o programa mandelbrot, que calcula um fractal de mandelbrot,
utilizando rotinas do OpenMP. Ao paralelizar o código do mandelbrot, você aumentará sua 
compreensão dos modelos de programação, ganhará experiência no desenvolvimento de uma 
aplicação MPI. Para isso observe os seguintes passos: (2,5  pontos).

- Você necessitará de um arquivo começar o trabalho: a versão sequencial do mandelbrot, 
que pode ser obtida no AVA.
- Compile, verifique o seu funcionamento e familiarize-se com o modo com que o 
programa sequencial funciona. 
- Experimente modificar o código para imprimir o mandelbrot colorido, aumente o 
tamanho da imagem para obter um tempo significativo de computação.
- Paralelize o programa. Para conseguir isto, imagine que cada thread irá calcular faixas 
(horizontais ou verticais) da imagem.
- Note que apenas uma tarefa deverá escrever o resultado final da imagem para exibição 
posterior para o usuário. 
- Compare o desempenho rodando em 1, 8 e 16  threads.
- Apresente um relatório com código fonte, resultados e comentários sobre todo esse 
processo.


## Abordagem
Utilizamos o código para imprimir o mandelbrot colorido e também fizemos uso do aumento do tamanho da imagem, onde percebeu-se um aumento do tempo de processamento.
Basicamente cada thread calcula faixas 


## Desempenho
Executando o programa localmente em uma única CPU de 4 núcleos, obtemos a seguinte tabela:


| Elementos / Versão | Paralela - 1 processo | Paralela - 8 processos | Paralela - 16 processos | 
|--------------------|-----------------------|------------------------|------------------------|
| 1000x1000         | 9.96 s                | 6.68 s                 | 3.11 s                 |
| 2000x2000         | 30.25 s                | 25.71 s                 | 20.17 s                 |
| 4000x4000         | 153.52 s               | 112.93 s                | 59.45 s                 |
