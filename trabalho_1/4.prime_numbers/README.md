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

TODO


## Análise de Escalabilidade

TODO