# Memória Virtual e Páginas de Memória em C

Este projeto é uma atividade da disciplina de Análise de Algoritmos da UFRR,em 2024.1, para demonstrar o uso de memória virtual e páginas de memória em um programa escrito em C. Ele faz uso da função `mmap` para mapear um arquivo grande, como a "Bíblia" (biblia.txt), na memória virtual, e aloca dinamicamente uma página de memória, escreve dados nessa página, exibe o conteúdo escrito, e libera a memória alocada ao final do processo.


Funcionamento: 
* Mapeamento de arquivo: Carrega o conteúdo do arquivo biblia.txt na memória virtual.
* Alocação de uma página de memória virtual: Aloca uma página de memória para escrita de dados arbitrários.
* Escrita na memória virtual: Escreve uma string na página de memória alocada.
* Exibição de informações de mapeamento: Exibe informações sobre a primeira e última página virtual do arquivo mapeado.
* Liberação da memória: Desmapeia a memória virtual e libera os recursos após o uso.
 
 # Requisitos

 Sistema operacional Linux (testado no Ubuntu 22.04).
 GCC (GNU Compiler Collection) instalado.
 Arquivo de texto biblia.txt no mesmo diretório do código fonte.
