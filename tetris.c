
// ============================================================================
// Tetris Stack - Gerenciamento de Peças com Fila Circular e Pilha Linear
// Autor: [Seu Nome]
// Descrição: Simula o gerenciamento de peças futuras e reservadas no jogo Tetris Stack.
// Utiliza fila circular para peças futuras e pilha linear para peças reservadas.
// ============================================================================

#include <stdio.h>      // Entrada e saída padrão
#include <stdlib.h>     // Funções utilitárias e aleatórias
#include <time.h>       // Para geração de números aleatórios

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.



// -----------------------------------------------------------------------------
// Definição da struct Peca
// Cada peça possui tipo (char) e id (int)
// -----------------------------------------------------------------------------
typedef struct {
    char tipo; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único
} Peca;

// -----------------------------------------------------------------------------
// Definição da fila circular de peças futuras
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
// Definição da pilha linear de peças reservadas
// -----------------------------------------------------------------------------
#define TAM_PILHA 3
typedef struct {
    Peca elementos[TAM_PILHA]; // Vetor de peças
    int topo;                  // Índice do topo da pilha
} PilhaPecas;

// -----------------------------------------------------------------------------
// Função para inicializar a fila
// -----------------------------------------------------------------------------
void inicializarFila(FilaPecas* fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->qtd = 0;
    fila->proxId = 0;
}

// Função para inicializar a pilha
// -----------------------------------------------------------------------------
void inicializarPilha(PilhaPecas* pilha) {
    pilha->topo = -1;
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

// Função para verificar se a pilha está cheia
// -----------------------------------------------------------------------------
int pilhaCheia(PilhaPecas* pilha) {
    return pilha->topo == TAM_PILHA - 1;
}

// Função para verificar se a pilha está vazia
// -----------------------------------------------------------------------------
int pilhaVazia(PilhaPecas* pilha) {
    return pilha->topo == -1;
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

// Função para inserir uma peça no topo da pilha (push)
// -----------------------------------------------------------------------------
int push(PilhaPecas* pilha, Peca peca) {
    if (pilhaCheia(pilha)) return 0;
    pilha->topo++;
    pilha->elementos[pilha->topo] = peca;
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

// Função para remover uma peça do topo da pilha (pop)
// -----------------------------------------------------------------------------
int pop(PilhaPecas* pilha, Peca* removida) {
    if (pilhaVazia(pilha)) return 0;
    *removida = pilha->elementos[pilha->topo];
    pilha->topo--;
    return 1;
}

// -----------------------------------------------------------------------------
// Função para exibir o estado atual da fila
// -----------------------------------------------------------------------------
void mostrarFila(FilaPecas* fila) {
    printf("Fila de peças\t");
    int idx = fila->inicio;
    for (int i = 0; i < fila->qtd; i++) {
        printf("[%c %d] ", fila->elementos[idx].tipo, fila->elementos[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");
}

// Função para exibir o estado atual da pilha
// -----------------------------------------------------------------------------
void mostrarPilha(PilhaPecas* pilha) {
    printf("Pilha de reserva \t(Topo -> Base): ");
    if (pilhaVazia(pilha)) {
        printf("(vazia)");
    } else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->elementos[i].tipo, pilha->elementos[i].id);
        }
    }
    printf("\n");
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Função para trocar a peça da frente da fila com o topo da pilha
// -----------------------------------------------------------------------------
int trocarFrenteFilaComTopoPilha(FilaPecas* fila, PilhaPecas* pilha) {
    if (filaVazia(fila) || pilhaVazia(pilha)) return 0;
    // Troca os dados das peças
    Peca temp = fila->elementos[fila->inicio];
    fila->elementos[fila->inicio] = pilha->elementos[pilha->topo];
    pilha->elementos[pilha->topo] = temp;
    return 1;
}

// -----------------------------------------------------------------------------
// Função para troca múltipla entre as 3 primeiras peças da fila e as 3 da pilha
// -----------------------------------------------------------------------------
int trocaMultipla(FilaPecas* fila, PilhaPecas* pilha) {
    if (fila->qtd < 3 || pilha->topo < 2) return 0; // Precisa de pelo menos 3 peças em cada
    for (int i = 0; i < 3; i++) {
        int idxFila = (fila->inicio + i) % TAM_FILA;
        Peca temp = fila->elementos[idxFila];
        fila->elementos[idxFila] = pilha->elementos[pilha->topo - i];
        pilha->elementos[pilha->topo - i] = temp;
    }
    return 1;
}

// -----------------------------------------------------------------------------
// Função principal: menu interativo para manipular fila e pilha de peças
// -----------------------------------------------------------------------------
int main() {
    srand((unsigned)time(NULL)); // Inicializa gerador de números aleatórios
    FilaPecas fila;
    PilhaPecas pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inicializa a fila com 5 peças geradas automaticamente
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(&fila));
    }

    int opcao;
    do {
        printf("\n==============================================\n");
        printf("Estado atual das estruturas:\n");
        mostrarFila(&fila);
        mostrarPilha(&pilha);
        printf("==============================================\n");
        printf("\nOpções disponíveis:\n");
        printf("Código\tAção\n");
        printf("1\tJogar peça da frente da fila\n");
        printf("2\tEnviar peça da fila para a pilha de reserva\n");
        printf("3\tUsar peça da pilha de reserva\n");
        printf("4\tTrocar peça da frente da fila com o topo da pilha\n");
        printf("5\tTrocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0\tSair\n");
        printf("==============================================\n");
        printf("Opção escolhida: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o \n do buffer

        if (opcao == 1) {
            // Jogar peça: remove da frente da fila
            Peca removida;
            if (dequeue(&fila, &removida)) {
                printf("Ação: Peça jogada: [%c %d]\n", removida.tipo, removida.id);
                // Após jogar, insere nova peça automaticamente
                enqueue(&fila, gerarPeca(&fila));
            } else {
                printf("Fila vazia, não há peça para jogar!\n");
            }
        } else if (opcao == 2) {
            // Reservar peça: move da frente da fila para o topo da pilha
            if (pilhaCheia(&pilha)) {
                printf("Pilha de reserva cheia! Não é possível reservar mais peças.\n");
            } else if (filaVazia(&fila)) {
                printf("Fila vazia, não há peça para reservar!\n");
            } else {
                Peca reservada;
                dequeue(&fila, &reservada);
                push(&pilha, reservada);
                printf("Ação: Peça [%c %d] reservada no topo da pilha.\n", reservada.tipo, reservada.id);
                enqueue(&fila, gerarPeca(&fila));
            }
        } else if (opcao == 3) {
            // Usar peça reservada: remove do topo da pilha
            Peca usada;
            if (pop(&pilha, &usada)) {
                printf("Ação: Peça reservada usada: [%c %d]\n", usada.tipo, usada.id);
            } else {
                printf("Pilha de reserva vazia! Não há peça para usar.\n");
            }
        } else if (opcao == 4) {
            // Trocar peça da frente da fila com o topo da pilha
            if (trocarFrenteFilaComTopoPilha(&fila, &pilha)) {
                printf("Ação: Troca realizada entre a peça da frente da fila e o topo da pilha.\n");
            } else {
                printf("Não foi possível realizar a troca (verifique se há peças suficientes).\n");
            }
        } else if (opcao == 5) {
            // Troca múltipla entre as 3 primeiras da fila e as 3 da pilha
            if (trocaMultipla(&fila, &pilha)) {
                printf("Ação: Troca realizada entre os 3 primeiros da fila e as 3 peças da pilha.\n");
            } else {
                printf("Não foi possível realizar a troca múltipla (verifique se há peças suficientes).\n");
            }
        } else if (opcao == 0) {
            printf("Saindo do sistema de controle de peças.\n");
        } else {
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    return 0;
}