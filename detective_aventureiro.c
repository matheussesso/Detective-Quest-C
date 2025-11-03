// DETECTIVE QUEST - COLETA DE PISTAS (Nivel Aventureiro)
// Explora mansão com árvore binária e coleta pistas em BST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct PistaNode {
    char descricao[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

int pistas_coletadas = 0;

// Cria uma nova sala com pista associada
Sala* criarSala(char* nome_sala, char* pista_sala) {
    Sala* nova_sala = (Sala*)malloc(sizeof(Sala));
    strcpy(nova_sala->nome, nome_sala);
    strcpy(nova_sala->pista, pista_sala);
    nova_sala->esquerda = NULL;
    nova_sala->direita = NULL;
    return nova_sala;
}

// Cria um nó para a BST de pistas
PistaNode* criarPistaNode(char* descricao) {
    PistaNode* novo_node = (PistaNode*)malloc(sizeof(PistaNode));
    strcpy(novo_node->descricao, descricao);
    novo_node->esquerda = NULL;
    novo_node->direita = NULL;
    return novo_node;
}

// Insere uma pista na BST (em ordem alfabética)
PistaNode* inserirPista(PistaNode* raiz, char* descricao) {
    if (raiz == NULL) {
        return criarPistaNode(descricao);
    }
    
    int comparacao = strcmp(descricao, raiz->descricao);
    
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, descricao);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, descricao);
    }
    
    return raiz;
}

// Exibe a interface de exploração
void exibir_interface(Sala* sala_atual) {
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║         DETECTIVE QUEST - EXPLORAÇÃO       ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("\nSala atual: %s\n", sala_atual->nome);
    
    if (strlen(sala_atual->pista) > 0) {
        printf("Pista encontrada: %s\n", sala_atual->pista);
        pistas_coletadas++;
    } else {
        printf("Sem pistas nesta sala.\n");
    }
    
    printf("\n");
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

// Explora a mansão e coleta pistas
void explorarSalasComPistas(Sala* raiz, PistaNode** arvore_pistas) {
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
        
        // Coleta pista se existir
        if (strlen(sala_atual->pista) > 0) {
            *arvore_pistas = inserirPista(*arvore_pistas, sala_atual->pista);
        }
        
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
            printf("║      EXPLORAÇÃO CONCLUÍDA!                ║\n");
            printf("║   Retornando com as pistas coletadas...   ║\n");
            printf("╚════════════════════════════════════════════╝\n");
            break;
        } else {
            printf("\nOpcao invalida! Use E, D ou S.\n");
        }
    }
}

// Exibe pistas em ordem alfabética (in-order)
void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    exibirPistas(raiz->esquerda);
    printf("  -> %s\n", raiz->descricao);
    exibirPistas(raiz->direita);
}

// Libera memória da árvore de salas
void liberarArvore(Sala* sala) {
    if (sala == NULL) {
        return;
    }
    
    liberarArvore(sala->esquerda);
    liberarArvore(sala->direita);
    free(sala);
}

// Libera memória da árvore de pistas
void liberarPistas(PistaNode* pista) {
    if (pista == NULL) {
        return;
    }
    
    liberarPistas(pista->esquerda);
    liberarPistas(pista->direita);
    free(pista);
}

// Programa principal - monta o mapa e inicia exploração
int main() {
    // Cria o mapa da mansão com pistas
    Sala* hall = criarSala("Hall de Entrada", "");
    
    // Segundo nível
    hall->esquerda = criarSala("Sala de Estar", "Recibo de transferencia bancaria");
    hall->direita = criarSala("Cozinha", "Frasco de veneno vazio");
    
    // Terceiro nível - esquerda
    hall->esquerda->esquerda = criarSala("Biblioteca", "Livro com pagina marcada");
    hall->esquerda->direita = criarSala("Escritório", "Carta manuscrita suspeita");
    
    // Terceiro nível - direita
    hall->direita->esquerda = criarSala("Despensa", "");
    hall->direita->direita = criarSala("Sala de Jantar", "Copo com marcas de laboratorio");
    
    // Quarto nível
    hall->esquerda->esquerda->esquerda = criarSala("Arquivo Secreto", "Documento confidencial");
    hall->esquerda->esquerda->direita = criarSala("Sala de Leitura", "");
    
    hall->esquerda->direita->esquerda = criarSala("Cofre Oculto", "Chave dourada antiga");
    hall->esquerda->direita->direita = criarSala("Sala de Reunioes", "Agenda com encontros marcados");
    
    hall->direita->esquerda->esquerda = criarSala("Adega", "Garrafa com etiqueta falsa");
    hall->direita->esquerda->direita = criarSala("Dispensa Fria", "Alimento vencido");
    
    hall->direita->direita->esquerda = criarSala("Salao de Baile", "");
    hall->direita->direita->direita = criarSala("Jardim de Inverno", "Luva descartada");
    
    // Inicializa árvore de pistas
    PistaNode* arvore_pistas = NULL;
    
    // Inicia exploração
    explorarSalasComPistas(hall, &arvore_pistas);
    
    // Exibe pistas coletadas em ordem alfabética
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║      PISTAS COLETADAS (Alfabético)        ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("Total de pistas: %d\n\n", pistas_coletadas);
    
    if (arvore_pistas != NULL) {
        exibirPistas(arvore_pistas);
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }
    
    printf("\n");
    
    // Libera memória
    liberarArvore(hall);
    liberarPistas(arvore_pistas);
    
    return 0;
}
