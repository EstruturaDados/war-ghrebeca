#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================
// WAR ESTRUTURADO - NÍVEL MESTRE
// Com sistema de missões estratégicas, ataques e verificação
// ============================================================

// Estrutura para armazenar dados de cada território
struct Territorio {
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército dominante
    int tropas;    // Quantidade de tropas
};

// ============================================================
// Função que sorteia uma missão e copia para o jogador
// ============================================================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;       // Sorteia índice
    strcpy(destino, missoes[sorteio]);         // Copia missão sorteada
}

// ============================================================
// Função que mostra o mapa atual
// ============================================================
void exibirMapa(struct Territorio* mapa, int qtd) {
    printf("\n=== MAPA DO MUNDO ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s (%s) - Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ============================================================
// Função que simula ataque entre dois territórios
// ============================================================
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1; // número aleatório de 1 a 6
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- ATAQUE ---\n");
    printf("%s (%s) ataca %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado do atacante: %d | Dado do defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        int tropasTransferidas = atacante->tropas / 2; 
        defensor->tropas = tropasTransferidas;         
        atacante->tropas -= tropasTransferidas;        
        strcpy(defensor->cor, atacante->cor);          
        printf("O atacante venceu! %s agora pertence a %s com %d tropas.\n",
               defensor->nome, defensor->cor, defensor->tropas);
    } else {
        // Defensor vence ou empata
        atacante->tropas -= 1;
        printf("O defensor resistiu! %s perde 1 tropa e agora tem %d tropas.\n",
               atacante->nome, atacante->tropas);
    }
}

// ============================================================
// Função que verifica se o jogador cumpriu sua missão
// ============================================================
int verificarMissao(char* missao, struct Territorio* mapa, int qtd, char* corJogador) {
    int conquistados = 0;
    int totalTropas = 0;

    if (strcmp(missao, "Conquistar todos os territórios") == 0) {
        for (int i = 0; i < qtd; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0)
                conquistados++;
        if (conquistados == qtd) return 1;
    }

    if (strcmp(missao, "Manter ao menos 5 tropas em um território") == 0) {
        for (int i = 0; i < qtd; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 5)
                return 1;
    }

    if (strcmp(missao, "Conquistar 3 territórios") == 0) {
        for (int i = 0; i < qtd; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0)
                conquistados++;
        if (conquistados >= 3) return 1;
    }

    if (strcmp(missao, "Dominar metade dos territórios do mapa") == 0) {
        for (int i = 0; i < qtd; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0)
                conquistados++;
        if (conquistados >= qtd / 2) return 1;
    }

    if (strcmp(missao, "Ter ao menos 10 tropas no total") == 0) {
        for (int i = 0; i < qtd; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0)
                totalTropas += mapa[i].tropas;
        if (totalTropas >= 10) return 1;
    }

    return 0; // missão ainda não cumprida
}

// ============================================================
// Função para liberar memória
// ============================================================
void liberarMemoria(struct Territorio* mapa, char* missaoJogador) {
    free(mapa);          
    free(missaoJogador); 
}

// ============================================================
// Função principal
// ============================================================
int main() {
    srand(time(NULL)); // Inicializa aleatoriedade

    // Vetor de missões
    char* missoes[] = {
        "Conquistar todos os territórios",
        "Manter ao menos 5 tropas em um território",
        "Conquistar 3 territórios",
        "Dominar metade dos territórios do mapa",
        "Ter ao menos 10 tropas no total"
    };
    int totalMissoes = 5;

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    struct Territorio* mundo = (struct Territorio*) calloc(qtd, sizeof(struct Territorio));

    // Cadastro dos territórios
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome do território: ");
        scanf(" %[^\n]", mundo[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mundo[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &mundo[i].tropas);
    }

    // Exibe mapa inicial
    exibirMapa(mundo, qtd);

    // Atribui missão ao jogador
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    char corJogador[10];
    strcpy(corJogador, mundo[0].cor);

    // Exibe missão do jogador
    printf("\n--- SUA MISSÃO (%s) ---\n", corJogador);
    printf("%s\n", missaoJogador);

    // ============================================================
    // Loop principal com menu de ações
    // ============================================================
    int opcao;
    do {
        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1. Atacar\n2. Verificar missão\n0. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int atacante, defensor;
            printf("Escolha o território atacante (1 a %d): ", qtd);
            scanf("%d", &atacante);
            printf("Escolha o território defensor (1 a %d): ", qtd);
            scanf("%d", &defensor);

            if (atacante < 1 || atacante > qtd || defensor < 1 || defensor > qtd) {
                printf("Território inválido!\n");
            } else if (strcmp(mundo[atacante - 1].cor, mundo[defensor - 1].cor) == 0) {
                printf("Não pode atacar um território da mesma cor!\n");
            } else if (mundo[atacante - 1].tropas == 0) {
                printf("Território atacante não tem tropas!\n");
            } else {
                atacar(&mundo[atacante - 1], &mundo[defensor - 1]);
            }

            exibirMapa(mundo, qtd);

            // Verifica missão automaticamente
            if (verificarMissao(missaoJogador, mundo, qtd, corJogador)) {
                printf("\nPARABÉNS! Você cumpriu sua missão: %s\n", missaoJogador);
                break;
            }

        } else if (opcao == 2) {
            if (verificarMissao(missaoJogador, mundo, qtd, corJogador)) {
                printf("\nVocê já cumpriu sua missão!\n");
            } else {
                printf("\nMissão ainda não cumprida.\n");
            }
        } else if (opcao == 0) {
            printf("\nSaindo do jogo...\n");
            break;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (1);

    // Libera memória
    liberarMemoria(mundo, missaoJogador);
    printf("\nJogo encerrado.\n");
    return 0;
}
