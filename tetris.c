
// ============================================================================
// Tetris Stack - Controle de Peças Futuras (Fila Circular)
// Autor: Jonathan de Souza Araújo
// Descrição: Simula a fila de peças futuras do jogo Tetris Stack usando fila circular.
// Permite jogar peça (dequeue), inserir nova peça (enqueue) e exibir o estado da fila.
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.


// -----------------------------------------------------------------------------
// Definição da struct Peca
// Cada peça possui tipo (char) e id (int)
// -----------------------------------------------------------------------------
typedef struct {
    char tipo; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único
} Peca;

// -----------------------------------------------------------------------------
// Definição da fila circular de peças
// -----------------------------------------------------------------------------
#define TAM_FILA 5
typedef struct {
    Peca elementos[TAM_FILA]; // Vetor de peças
    int inicio;               // Índice do início da fila
    int fim;                  // Índice do final da fila
    int qtd;                  // Quantidade atual de peças
    int proxId;               // Próximo id a ser gerado
} FilaPecas;

// -----------------------------------------------------------------------------
// Função para inicializar a fila
// -----------------------------------------------------------------------------
void inicializarFila(FilaPecas* fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->qtd = 0;
    fila->proxId = 0;
}

// -----------------------------------------------------------------------------
// Função para verificar se a fila está cheia
// -----------------------------------------------------------------------------
int filaCheia(FilaPecas* fila) {
    return fila->qtd == TAM_FILA;
}

// -----------------------------------------------------------------------------
// Função para verificar se a fila está vazia
// -----------------------------------------------------------------------------
int filaVazia(FilaPecas* fila) {
    return fila->qtd == 0;
}

// -----------------------------------------------------------------------------
// Função para gerar uma peça automaticamente
// -----------------------------------------------------------------------------
Peca gerarPeca(FilaPecas* fila) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    int idx = rand() % 4;
    Peca nova;
    nova.tipo = tipos[idx];
    nova.id = fila->proxId++;
    return nova;
}

// -----------------------------------------------------------------------------
// Função para inserir uma peça ao final da fila (enqueue)
// -----------------------------------------------------------------------------
int enqueue(FilaPecas* fila, Peca peca) {
    if (filaCheia(fila)) return 0;
    fila->elementos[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->qtd++;
    return 1;
}

// -----------------------------------------------------------------------------
// Função para remover uma peça da frente da fila (dequeue)
// -----------------------------------------------------------------------------
int dequeue(FilaPecas* fila, Peca* removida) {
    if (filaVazia(fila)) return 0;
    *removida = fila->elementos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->qtd--;
    return 1;
}

// -----------------------------------------------------------------------------
// Função para exibir o estado atual da fila
// -----------------------------------------------------------------------------
void mostrarFila(FilaPecas* fila) {
    printf("\nFila de peças\n");
    int idx = fila->inicio;
    for (int i = 0; i < fila->qtd; i++) {
        printf("[%c %d] ", fila->elementos[idx].tipo, fila->elementos[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");
}

// -----------------------------------------------------------------------------
// Função principal: menu interativo para manipular a fila de peças
// -----------------------------------------------------------------------------
int main() {
    srand((unsigned)time(NULL)); // Inicializa gerador de números aleatórios
    FilaPecas fila;
    inicializarFila(&fila);

    // Inicializa a fila com 5 peças geradas automaticamente
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(&fila));
    }

    int opcao;
    do {
        mostrarFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o \n do buffer

        if (opcao == 1) {
            Peca removida;
            if (dequeue(&fila, &removida)) {
                printf("Peça jogada: [%c %d]\n", removida.tipo, removida.id);
                // Após jogar, insere nova peça automaticamente
                if (enqueue(&fila, gerarPeca(&fila))) {
                    printf("Nova peça inserida ao final da fila.\n");
                } else {
                    printf("Fila cheia, não foi possível inserir nova peça.\n");
                }
            } else {
                printf("Fila vazia, não há peça para jogar!\n");
            }
        } else if (opcao == 2) {
            if (enqueue(&fila, gerarPeca(&fila))) {
                printf("Nova peça inserida ao final da fila.\n");
            } else {
                printf("Fila cheia, não foi possível inserir nova peça.\n");
            }
        } else if (opcao == 0) {
            printf("Saindo do sistema de controle de peças.\n");
        } else {
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    return 0;
}