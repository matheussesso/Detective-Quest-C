// DETECTIVE QUEST - JULGAMENTO FINAL (Nivel Mestre)
// Explora mansão, coleta pistas e acusa suspeito com verificação

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 20

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

// Hash table: pista -> suspeito
typedef struct {
    char pista[100];
    char suspeito[50];
    int ativo;
} EntradaHash;

EntradaHash tabela_hash[TAMANHO_HASH];
int pistas_coletadas = 0;

// Funcao hash simples
int funcao_hash(char* chave) {
    int hash = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        hash += chave[i];
    }
    return hash % TAMANHO_HASH;
}

// Inicializa a tabela hash
void inicializar_hash() {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabela_hash[i].ativo = 0;
    }
}

// Insere pista-suspeito na hash
void inserirNaHash(char* pista, char* suspeito) {
    int indice = funcao_hash(pista);
    
    // Trata colisões com sondagem linear
    while (tabela_hash[indice].ativo == 1) {
        indice = (indice + 1) % TAMANHO_HASH;
    }
    
    strcpy(tabela_hash[indice].pista, pista);
    strcpy(tabela_hash[indice].suspeito, suspeito);
    tabela_hash[indice].ativo = 1;
}

// Busca suspeito pela pista
char* encontrarSuspeito(char* pista) {
    int indice = funcao_hash(pista);
    int inicio = indice;
    
    while (tabela_hash[indice].ativo == 1) {
        if (strcmp(tabela_hash[indice].pista, pista) == 0) {
            return tabela_hash[indice].suspeito;
        }
        indice = (indice + 1) % TAMANHO_HASH;
        if (indice == inicio) break;
    }
    
    return NULL;
}

// Cria uma nova sala
Sala* criarSala(char* nome_sala, char* pista_sala) {
    Sala* nova_sala = (Sala*)malloc(sizeof(Sala));
    strcpy(nova_sala->nome, nome_sala);
    strcpy(nova_sala->pista, pista_sala);
    nova_sala->esquerda = NULL;
    nova_sala->direita = NULL;
    return nova_sala;
}

// Cria nó da BST de pistas
PistaNode* criarPistaNode(char* descricao) {
    PistaNode* novo_node = (PistaNode*)malloc(sizeof(PistaNode));
    strcpy(novo_node->descricao, descricao);
    novo_node->esquerda = NULL;
    novo_node->direita = NULL;
    return novo_node;
}

// Insere pista na BST
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

// Exibe interface de exploração
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
        printf("Sem saidas! Sala-folha.\n");
    }
    printf("(S) Sair da mansão\n");
}

// Explora mansão coletando pistas
void explorarSalas(Sala* raiz, PistaNode** arvore_pistas) {
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
        
        if (strlen(sala_atual->pista) > 0) {
            *arvore_pistas = inserirPista(*arvore_pistas, sala_atual->pista);
        }
        
        printf("\nEscolha: ");
        scanf(" %c", &escolha);
        getchar();  // Limpa newline do buffer
        
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

// Exibe pistas em ordem alfabética
void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    exibirPistas(raiz->esquerda);
    printf("  -> %s", raiz->descricao);
    
    char* suspeito = encontrarSuspeito(raiz->descricao);
    if (suspeito != NULL) {
        printf(" [%s]\n", suspeito);
    } else {
        printf("\n");
    }
    
    exibirPistas(raiz->direita);
}

// Conta pistas de um suspeito
int contarPistasPorSuspeito(PistaNode* raiz, char* suspeito) {
    if (raiz == NULL) {
        return 0;
    }
    
    int esquerda = contarPistasPorSuspeito(raiz->esquerda, suspeito);
    int direita = contarPistasPorSuspeito(raiz->direita, suspeito);
    
    char* susp_pista = encontrarSuspeito(raiz->descricao);
    int atual = (susp_pista != NULL && strcmp(susp_pista, suspeito) == 0) ? 1 : 0;
    
    return esquerda + atual + direita;
}

// Verifica o suspeito final e mostra resultado
void verificarSuspeitoFinal(PistaNode* arvore_pistas) {
    if (arvore_pistas == NULL) {
        printf("\nSem pistas coletadas. Nao ha culpado.\n");
        return;
    }
    
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║      FASE FINAL - JULGAMENTO              ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("\nQue acusa: ");
    
    char acusado[50];
    fgets(acusado, sizeof(acusado), stdin);
    // Remove newline
    size_t len = strlen(acusado);
    if (len > 0 && acusado[len-1] == '\n') {
        acusado[len-1] = '\0';
    }
    
    int pistas_suspeito = contarPistasPorSuspeito(arvore_pistas, acusado);
    
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║      RESULTADO DA ACUSAÇÃO                ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    
    printf("\nSuspeito: %s\n", acusado);
    printf("Pistas contra: %d\n\n", pistas_suspeito);
    
    if (pistas_suspeito >= 2) {
        printf("╔════════════════════════════════════════════╗\n");
        printf("║  CULPADO IDENTIFICADO COM SUCESSO!        ║\n");
        printf("║  %s é o responsável pelo crime!          ║\n", acusado);
        printf("╚════════════════════════════════════════════╝\n");
    } else {
        printf("╔════════════════════════════════════════════╗\n");
        printf("║  EVIDÊNCIAS INSUFICIENTES!               ║\n");
        printf("║  Minimo 2 pistas necessarias.            ║\n");
        printf("║  Investigação deve continuar...          ║\n");
        printf("╚════════════════════════════════════════════╝\n");
    }
    
    printf("\n");
}

// Libera árvore de salas
void liberarArvore(Sala* sala) {
    if (sala == NULL) {
        return;
    }
    
    liberarArvore(sala->esquerda);
    liberarArvore(sala->direita);
    free(sala);
}

// Libera árvore de pistas
void liberarPistas(PistaNode* pista) {
    if (pista == NULL) {
        return;
    }
    
    liberarPistas(pista->esquerda);
    liberarPistas(pista->direita);
    free(pista);
}

// Programa principal
int main() {
    inicializar_hash();
    
    // Define pistas-suspeitos
    inserirNaHash("Recibo de transferencia bancaria", "Primo Rico");
    inserirNaHash("Frasco de veneno vazio", "Chef Moreno");
    inserirNaHash("Livro com pagina marcada", "Bibliotecario Silva");
    inserirNaHash("Carta manuscrita suspeita", "Secretaria Paula");
    inserirNaHash("Copo com marcas de laboratorio", "Doutor Alvaro");
    inserirNaHash("Documento confidencial", "Primo Rico");
    inserirNaHash("Chave dourada antiga", "Primo Rico");
    inserirNaHash("Agenda com encontros marcados", "Secretaria Paula");
    inserirNaHash("Garrafa com etiqueta falsa", "Chef Moreno");
    inserirNaHash("Alimento vencido", "Chef Moreno");
    inserirNaHash("Luva descartada", "Doutor Alvaro");
    
    // Cria mapa da mansão
    Sala* hall = criarSala("Hall de Entrada", "");
    
    hall->esquerda = criarSala("Sala de Estar", "Recibo de transferencia bancaria");
    hall->direita = criarSala("Cozinha", "Frasco de veneno vazio");
    
    hall->esquerda->esquerda = criarSala("Biblioteca", "Livro com pagina marcada");
    hall->esquerda->direita = criarSala("Escritório", "Carta manuscrita suspeita");
    
    hall->direita->esquerda = criarSala("Despensa", "");
    hall->direita->direita = criarSala("Sala de Jantar", "Copo com marcas de laboratorio");
    
    hall->esquerda->esquerda->esquerda = criarSala("Arquivo Secreto", "Documento confidencial");
    hall->esquerda->esquerda->direita = criarSala("Sala de Leitura", "");
    
    hall->esquerda->direita->esquerda = criarSala("Cofre Oculto", "Chave dourada antiga");
    hall->esquerda->direita->direita = criarSala("Sala de Reunioes", "Agenda com encontros marcados");
    
    hall->direita->esquerda->esquerda = criarSala("Adega", "Garrafa com etiqueta falsa");
    hall->direita->esquerda->direita = criarSala("Dispensa Fria", "Alimento vencido");
    
    hall->direita->direita->esquerda = criarSala("Salao de Baile", "");
    hall->direita->direita->direita = criarSala("Jardim de Inverno", "Luva descartada");
    
    // Inicia exploração
    PistaNode* arvore_pistas = NULL;
    explorarSalas(hall, &arvore_pistas);
    
    // Exibe pistas com suspeitos
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║      PISTAS COLETADAS (Com Suspeitos)     ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("Total de pistas: %d\n\n", pistas_coletadas);
    
    if (arvore_pistas != NULL) {
        exibirPistas(arvore_pistas);
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }
    
    // Fase de julgamento
    verificarSuspeitoFinal(arvore_pistas);
    
    // Libera memória
    liberarArvore(hall);
    liberarPistas(arvore_pistas);
    
    return 0;
}
