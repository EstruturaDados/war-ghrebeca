#include <stdio.h>

// ============================================================
// WAR ESTRUTURADO - NÍVEL NOVATO
// Cadastro inicial dos 5 territórios do jogo WAR
// ============================================================

// Estrutura para armazenar dados de cada território
struct Territorio {
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército dominante
    int tropas;    // Quantidade de tropas
};

int main() {
    // Vetor estático de 5 territórios
    struct Territorio mundo[5];
    int i; // Índice para loops

    // Cabeçalho inicial do programa
    printf("==========================================\n");
    printf("    WAR ESTRUTURADO - CADASTRO INICIAL    \n");
    printf("==========================================\n\n");

    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n");

    // Loop para cadastro dos territórios
    for (i = 0; i < 5; i++) {
        printf("\n--- Cadastro Território %d ---\n", i + 1);

        // Solicita nome do território
        printf("Nome do território: ");
        scanf(" %[^\n]", mundo[i].nome);  // Lê string com espaços

        // Solicita cor do exército
        printf("Cor do exército: ");
        scanf(" %[^\n]", mundo[i].cor);   // Lê string com espaços

        // Solicita número de tropas
        printf("Número de Tropas: ");
        scanf("%d", &mundo[i].tropas);    // Lê inteiro
    }

    printf("\nCadastro inicial concluído com sucesso!\n");

    // Cabeçalho do mapa
    printf("\n====================================\n");
    printf("    MAPA DO MUNDO - ESTADO ATUAL    \n");
    printf("====================================\n");

    // Loop para exibir todos os territórios cadastrados
    for (i = 0; i < 5; i++) {
        printf("\nTERRITÓRIO %d:\n", i + 1);
        printf("  - Nome: %s\n", mundo[i].nome);
        printf("  - Dominado por: Exército %s\n", mundo[i].cor);
        printf("  - Tropas: %d\n", mundo[i].tropas);
    }

    // Fim do programa
    return 0;
}