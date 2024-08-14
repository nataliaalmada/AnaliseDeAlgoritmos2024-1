#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Definir o tamanho da página de memória
    size_t tamanho_pagina = sysconf(_SC_PAGESIZE);
    printf("Tamanho da página: %zu bytes\n", tamanho_pagina);

    // Abrir o arquivo biblia.txt para leitura
    int arquivo = open("biblia.txt", O_RDONLY);
    if (arquivo == -1) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Obter o tamanho do arquivo
    off_t tamanho_arquivo = lseek(arquivo, 0, SEEK_END);
    lseek(arquivo, 0, SEEK_SET);
    printf("Tamanho do arquivo: %ld bytes\n", tamanho_arquivo);

    // Mapear o arquivo para a memória virtual
    char *mapa = mmap(NULL, tamanho_arquivo, PROT_READ, MAP_PRIVATE, arquivo, 0);
    if (mapa == MAP_FAILED) {
        perror("Erro ao mapear o arquivo para a memória");
        close(arquivo);
        exit(EXIT_FAILURE);
    }

    // Alocar uma página de memória virtual para escrever dados
    void *pagina = mmap(NULL, tamanho_pagina, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (pagina == MAP_FAILED) {
        perror("Erro ao mapear a página de memória");
        munmap(mapa, tamanho_arquivo);
        close(arquivo);
        exit(EXIT_FAILURE);
    }

    // Escrever dados na página de memória
    const char *texto = "Escrevendo dados na página de memória virtual!";
    strncpy((char *)pagina, texto, tamanho_pagina - 1);
    ((char *)pagina)[tamanho_pagina - 1] = '\0';

    // Exibir o texto que foi escrito na memória virtual
    printf("Texto na memória virtual: %s\n", (char *)pagina);

    // Exibir informações sobre a primeira e última página do arquivo mapeado
    uintptr_t endereco_inicial = (uintptr_t)mapa;
    uintptr_t numero_pagina_inicial = endereco_inicial >> 12;
    uintptr_t offset_pagina_inicial = endereco_inicial & 0xFFF;

    uintptr_t endereco_final = (uintptr_t)(mapa + tamanho_arquivo - 1);
    uintptr_t numero_pagina_final = endereco_final >> 12;
    uintptr_t offset_pagina_final = endereco_final & 0xFFF;

    printf("\nInformações sobre o mapeamento:\n");
    printf("Endereço inicial (HEX): 0x%lx, Página: %ld, Offset: %ld\n", endereco_inicial, numero_pagina_inicial, offset_pagina_inicial);
    printf("Endereço final (HEX): 0x%lx, Página: %ld, Offset: %ld\n", endereco_final, numero_pagina_final, offset_pagina_final);

    // Desmapear a página de memória e o arquivo
    if (munmap(pagina, tamanho_pagina) == -1) {
        perror("Erro ao desmapear a página de memória");
    }
    if (munmap(mapa, tamanho_arquivo) == -1) {
        perror("Erro ao desmapear o arquivo da memória");
    }

    // Fechar o arquivo
    close(arquivo);

    return 0;
}
