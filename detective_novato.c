// DETECTIVE QUEST - MAPA DA MANSAO (Nivel Novato)
// Simula exploração de uma mansão usando árvore binária

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Cria uma nova sala com alocação dinâmica
Sala* criarSala(char* nome_sala) {
    Sala* nova_sala = (Sala*)malloc(sizeof(Sala));
    strcpy(nova_sala->nome, nome_sala);
    nova_sala->esquerda = NULL;
    nova_sala->direita = NULL;
    return nova_sala;
}

// Exibe a interface de exploração
void exibir_interface(Sala* sala_atual) {
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║         DETECTIVE QUEST - EXPLORAÇÃO       ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("\nSala atual: %s\n\n", sala_atual->nome);
    
    if (sala_atual->esquerda != NULL) {
        printf("(E) Ir para esquerda\n");
    }
    if (sala_atual->direita != NULL) {
        printf("(D) Ir para direita\n");
    }
    if (sala_atual->esquerda == NULL && sala_atual->direita == NULL) {
        printf("Sem saidas! Esta é uma sala-folha.\n");
    }
    printf("(S) Sair da mansão\n");
}

// Explora a mansão de forma interativa
void explorarSalas(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    Sala* sala_atual = raiz;
    char escolha;
    
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║    BEM-VINDO À MANSÃO - DETECTIVE QUEST    ║\n");
    printf("║    Encontre pistas explorando cada sala    ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    
    while (1) {
        exibir_interface(sala_atual);
        printf("\nEscolha: ");
        scanf(" %c", &escolha);
        
        if (escolha == 'E' || escolha == 'e') {
            if (sala_atual->esquerda != NULL) {
                sala_atual = sala_atual->esquerda;
                printf("\n→ Você entrou em: %s\n", sala_atual->nome);
            } else {
                printf("\nNao ha saida para a esquerda!\n");
            }
        } else if (escolha == 'D' || escolha == 'd') {
            if (sala_atual->direita != NULL) {
                sala_atual = sala_atual->direita;
                printf("\n→ Você entrou em: %s\n", sala_atual->nome);
            } else {
                printf("\nNao ha saida para a direita!\n");
            }
        } else if (escolha == 'S' || escolha == 's') {
            printf("\n");
            printf("╔════════════════════════════════════════════╗\n");
            printf("║   Obrigado por jogar Detective Quest!      ║\n");
            printf("║           Até a próxima missão!           ║\n");
            printf("╚════════════════════════════════════════════╝\n");
            printf("\n");
            break;
        } else {
            printf("\nOpcao invalida! Use E, D ou S.\n");
        }
    }
}

// Libera a memória alocada pela árvore
void liberarArvore(Sala* sala) {
    if (sala == NULL) {
        return;
    }
    
    liberarArvore(sala->esquerda);
    liberarArvore(sala->direita);
    free(sala);
}

// Programa principal - monta o mapa e inicia exploração
int main() {
    // Cria o mapa da mansão como árvore binária
    Sala* hall = criarSala("Hall de Entrada");
    
    // Segundo nível
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");
    
    // Terceiro nível - esquerda
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Escritório");
    
    // Terceiro nível - direita
    hall->direita->esquerda = criarSala("Despensa");
    hall->direita->direita = criarSala("Salas de Jantar");
    
    // Quarto nível - mais profundidade
    hall->esquerda->esquerda->esquerda = criarSala("Arquivo Secreto");
    hall->esquerda->esquerda->direita = criarSala("Sala de Leitura");
    
    hall->esquerda->direita->esquerda = criarSala("Cofre Oculto");
    hall->esquerda->direita->direita = criarSala("Sala de Reuniões");
    
    hall->direita->esquerda->esquerda = criarSala("Adega");
    hall->direita->esquerda->direita = criarSala("Dispensa Fria");
    
    hall->direita->direita->esquerda = criarSala("Salao de Baile");
    hall->direita->direita->direita = criarSala("Jardim de Inverno");
    
    // Inicia a exploração
    explorarSalas(hall);
    
    // Libera memória
    liberarArvore(hall);
    
    return 0;
}
