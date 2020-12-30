#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* A funcao aloca memoria para tipo Fila,
   inicializa a fila, retornando a fila
*/
PFila cria_fila() {
    PFila fila = malloc(sizeof(Fila));

    fila->tamanho = 0;
    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

/* A funcao recebe nó da fila
   e desaloca recursivamente os nós
*/
void destroi_fila_recursivo(PFNo no) {
    if(no != NULL) {
        destroi_fila_recursivo(no->proximo);
        free(no);
    }
}

/* A funcao recebe a fila e
   desaloca memoria para cada nó,
   desalocando a memoria da fila por ultimo
*/
void destroi_fila(PFila fila) {
    if(fila != NULL) {
        destroi_fila_recursivo(fila->inicio);
        free(fila);
    }
}

/* A funcao recebe a fila,
   retornando 1 se a fila está vazia
   ou zero caso contrario
*/
int fila_vazia(PFila fila) {
    return fila->tamanho == 0 ? 1 : 0;
}

/* A funcao recebe a fila e o dado a ser
   armazenado na fila, retornando
   a fila com o dado inserido nela
*/
PFila enfileira(PFila fila, void *dado) {
    PFNo novo;

    novo = malloc(sizeof(FNo));
    novo->dado = dado;
    novo->proximo = NULL;

    if(fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
        fila->tamanho = 1;
        return fila;
    }

    fila->fim->proximo = novo;
    fila->fim = novo;
    fila->tamanho++;

    return fila;
}

/* A funcao recebe a fila e
   remove o primeiro elemento da fila,
   retornando ponteiro para o dado removido
*/
void *desenfileira(PFila fila) {
    PFNo inicio;
    void *dado;

    if(fila->inicio == NULL) {
        return NULL;
    }

    inicio = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    if(fila->inicio == NULL) {
        fila->fim = NULL;
    }
    dado = inicio->dado;
    fila->tamanho--;

    inicio->proximo = NULL;
    free(inicio);

    return dado;
}

/* A funcao recebe a fila e ponteiro para funcao imprime,
   imprime os dados do inicio ao fim da fila
*/
void imprime_fila(PFila fila, void (*imprime)(void *)) {
    PFNo atual;

    for(atual = fila->inicio; atual != NULL; atual = atual->proximo) {
        (*imprime)(atual->dado);
    }
    printf("\n");
}
