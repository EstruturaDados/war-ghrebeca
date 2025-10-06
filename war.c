#include <stdio.h>   // Biblioteca para entrada e saída de dados
#include <stdlib.h>  // Biblioteca para alocação dinâmica e rand
#include <string.h>  // Biblioteca para manipulação de strings
#include <time.h>    // Biblioteca para função time (aleatoriedade)

// ============================================================
// WAR ESTRUTURADO - NÍVEL AVENTUREIRO
// Cadastro dinâmico de territórios e simulação de ataque
// ============================================================

// Estrutura para armazenar dados de cada território
struct Territorio {
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército dominante
    int tropas;    // Quantidade de tropas
};

// Função que simula ataque entre dois territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Gera números aleatórios entre 1 e 6 simulando dados
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    // Mostra quem está atacando e quem está defendendo
    printf("\nAtaque de %s (%s) contra %s (%s)\n", 
            atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if(dadoAtacante > dadoDefensor) { 
        // Atacante vence
        int tropasTransferidas = atacante->tropas / 2; // calcula metade das tropas do atacante
        defensor->tropas = tropasTransferidas;        // defensor recebe essas tropas
        atacante->tropas -= tropasTransferidas;       // atacante perde essas tropas
        strcpy(defensor->cor, atacante->cor);         // defensor muda de dono (mesma cor do atacante)
        printf("O atacante venceu! %s agora pertence a %s com %d tropas.\n",
                defensor->nome, defensor->cor, defensor->tropas);
    } else { 
        // Defensor vence ou empata
        atacante->tropas -= 1; // atacante perde 1 tropa
        printf("O defensor resistiu! %s perde 1 tropa e agora tem %d tropas.\n",
                atacante->nome, atacante->tropas);
    }
}

// Função para liberar memória alocada dinamicamente
void liberarMemoria(struct Territorio* mapa) {
    free(mapa); // libera o espaço usado pelo vetor de territórios
}

int main() {
    srand(time(NULL)); // Inicializa a aleatoriedade para que os números do rand mudem a cada execução

    int qtd; // variável para armazenar a quantidade de territórios
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Aloca dinamicamente um vetor de territórios do tamanho escolhido pelo usuário
    struct Territorio* mundo = (struct Territorio*) calloc(qtd, sizeof(struct Territorio));

    // Cadastro dos territórios
    for(int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro Território %d ---\n", i + 1);

        printf("Nome do território: ");
        scanf(" %[^\n]", mundo[i].nome); // lê string com espaços

        printf("Cor do exército: ");
        scanf(" %[^\n]", mundo[i].cor); // lê string com espaços

        printf("Número de Tropas: ");
        scanf("%d", &mundo[i].tropas); // lê número de tropas
    }

    // Exibe mapa atual
    printf("\n=== MAPA DO MUNDO ===\n");
    for(int i = 0; i < qtd; i++) {
        printf("%d. %s (%s) - Tropas: %d\n", 
                i + 1, mundo[i].nome, mundo[i].cor, mundo[i].tropas);
    }

    // Fase de ataque
    int atacante, defensor;
    do {
        printf("\nEscolha o território atacante (1 a %d, ou 0 para sair): ", qtd);
        scanf("%d", &atacante);
        if(atacante == 0) break; // se o jogador digitar 0, sai do loop

        printf("Escolha o território defensor (1 a %d): ", qtd);
        scanf("%d", &defensor);

        // Verifica se o jogador não atacou o próprio território
        if(strcmp(mundo[atacante-1].cor, mundo[defensor-1].cor) == 0) {
            printf("Não pode atacar um território da mesma cor!\n");
            continue; // volta ao início do loop
        }

        // Chama a função que realiza o ataque
        atacar(&mundo[atacante-1], &mundo[defensor-1]);

    } while(atacante != 0); // repete enquanto atacante não for 0

    // Libera memória antes de encerrar
    liberarMemoria(mundo);

    return 0; // fim do programa
}
