# Programação Paralela e Distribuída

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

Atualmente em 08/2021 irá instalar a versão libomp-10-dev