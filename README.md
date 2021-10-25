# Programação Paralela e Distribuída

Repositório da disciplina de Programação paralela e distribuída da UFRJ ministrada em 2021.1

## MPI

### Instalação

`sudo apt install openmpi-bin libopenmpi-dev`

### Compilar

`mpicc <input> -o <output> -lm`

Nota: a flag -lm é para linkar com a biblioteca math, utilizada em diversos programas

### Executar

`mpirun <executable> -n <processes>`

Nota: para executar mais processos do que o número disponível de núcleos no processador, é necessário executar com a flag --oversubscribe

---

## OpenMP

### Instalação

`sudo apt install libomp-dev`

Nota: atualmente em 08/2021 irá instalar a versão libomp-10-dev

### Compilar

`gcc -fopenmp <input> -o <output>`

---

## OpenACC

### Instalação

Necessário GCC de versão 6 ou maior ou PGCC

### Compilar

`gcc -fopenacc -fopt-info <input> -o <output>`

`pgcc -acc -ta=<machine> -Minfo=all <input> -o <output>`

Variável de ambiente **ACC_DEVICE_TYPE** pode assumir os seguintes valores:

- **host** modo serial
- **nvidia** arquitetura Nvidia PTX (parallel thread execution)
- **gcn** arquitetura AMD GCN (graphics core next)

Para verificar o valor atual:

`echo $ACC_DEVICE_TYPE`

Para mudar o valor:

`export ACC_DEVICE_TYPE=<type>`

---

## SSH

### Teresópolis

- grupo01@teresopolis.dcc.ufrj.br:22022

- Configurar o arquivo **submission.sh** e usar comando `qsub submission.sh` para iniciar o job

- Utilizar pasta `/work/grupo01` para colocar os códigos e rodar os jobs

### Tesla

- grupo01@tesla.dcc.ufrj.br:25252

### Colar texto no vim

`:set paste`

`Ctrl + Shift + V`