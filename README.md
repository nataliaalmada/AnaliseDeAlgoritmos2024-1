# Memória Virtual e Páginas de Memória em C

Este projeto é uma atividade da disciplina de Análise de Algoritmos da UFRR,em 2024.1, para demonstrar o uso de memória virtual e páginas de memória em um programa escrito em C, testado no Ubuntu 22.04 e Fedora Linux 40 Workstation Edition. Ele faz uso da função `mmap` para mapear um arquivo grande, como a "Bíblia" (biblia.txt), na memória virtual, e aloca dinamicamente uma página de memória, escreve dados nessa página, exibe o conteúdo escrito, e libera a memória alocada ao final do processo.


Funcionamento: 
* Mapeamento de arquivo: Carrega o conteúdo do arquivo biblia.txt na memória virtual.
* Alocação de uma página de memória virtual: Aloca uma página de memória para escrita de dados arbitrários.
* Escrita na memória virtual: Escreve uma string na página de memória alocada.
* Exibição de informações de mapeamento: Exibe informações sobre a primeira e última página virtual do arquivo mapeado.
* Liberação da memória: Desmapeia a memória virtual e libera os recursos após o uso.
 
 # Requisitos

 Sistema operacional Linux.
 Arquivo de texto biblia.txt no mesmo diretório do código fonte.
 Compilação do código com GCC (GNU Compiler Collection) que deve ter sido instaladoado.
 Executar o programa.

 # Complexidade
Segundo a literatura de Cormen, devemos
* Identificar as operações principais: Analisar as operações que dominam o tempo de execução, como laços (loops), operações de entrada/saída, e chamadas de funções complexas.
* Calcular a complexidade de cada operação:
* Combinar as complexidades: regra de maior ordem para determinar a complexidade final.

### Analisando o código para determinar a complexidade:

 *1. Definição do Tamanho da Página de Memória*
```c
size_t tamanho_pagina = sysconf(_SC_PAGESIZE);
```
*Complexidade*: \(O(1)\) — uma única chamada de sistema.

*2. Abertura e Tamanho do Arquivo*
```c
int arquivo = open("biblia.txt", O_RDONLY);
off_t tamanho_arquivo = lseek(arquivo, 0, SEEK_END);
lseek(arquivo, 0, SEEK_SET);
```
*Complexidade*: \(O(1)\) para abrir o arquivo, \(O(1)\) para cada chamada `lseek`. 
Pra fins de análise de complexidade, o `lseek` é tratado como \(O(1)\).

*3. Mapeamento de Arquivo na Memória*
```c
char *mapa = mmap(NULL, tamanho_arquivo, PROT_READ, MAP_PRIVATE, arquivo, 0);
```
*Complexidade*: \(O(tamanho\_arquivo)\) — essa operação mapeia o arquivo inteiro na memória, então é proporcional ao tamanho do arquivo.

*4. Alocação de Memória e Escrita*
```c
void *pagina = mmap(NULL, tamanho_pagina, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
strncpy((char *)pagina, texto, tamanho_pagina - 1);
```
*Complexidade*: \(O(1)\) para `mmap` (mapeando apenas uma página) e \(O(tamanho\_pagina)\) para `strncpy`.

*5. Cálculo de Número de Página e Offset*
```c
uintptr_t numero_pagina_inicial = endereco_inicial >> 12;
uintptr_t offset_pagina_inicial = endereco_inicial & 0xFFF;
uintptr_t numero_pagina_final = endereco_final >> 12;
uintptr_t offset_pagina_final = endereco_final & 0xFFF;
```
*Complexidade*: \(O(1)\) — operações simples de bitwise.

*6. Desmapeamento e Fechamento*
```c
if (munmap(pagina, tamanho_pagina) == -1) { ... }
if (munmap(mapa, tamanho_arquivo) == -1) { ... }
close(arquivo);
```
*Complexidade*: \(O(tamanho\_arquivo)\) para desmapear o arquivo, \(O(1)\) para desmapear a página e fechar o arquivo.

### _Complexidade Total_

A operação de maior custo é o mapeamento do arquivo, que é proporcional ao tamanho do arquivo (`tamanho_arquivo`). Portanto, a complexidade assintótica dominante é:

\[
O(tamanho\_arquivo)
\]

Segundo o Cormen, essa complexidade seria considerada como **O(n)** onde \(n\) representa o tamanho do arquivo mapeado.
## Referências
* How to Map Files into Memory in C (mmap, memory mapped file io)
 
https://youtu.be/m7E9piHcfr4?si=JKa0S9x3Mwf7gIYC
* Reading and writing files using memory-mapped I/O


https://learningdaily.dev/reading-and-writing-files-using-memory-mapped-i-o-220fa802aa1c

* Linux Memory Management — All you need to know

*https://hemantra.medium.com/linux-memory-management-all-you-need-to-know-d1dbdda8b386

* Algoritmos - Teoria e Prática - 3ª Ed. 2012 - Thomas H. Cormen [et al.] 
