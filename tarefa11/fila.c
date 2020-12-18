#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

PFila cria_fila() {
    PFila fila = malloc(sizeof(Fila));

    fila->tamanho = 0;
    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

void destroi_fila_recursivo(PFNo no) {
    if(no != NULL) {
        destroi_fila_recursivo(no->proximo);
        /* free(no->dado); */
        free(no);
    }
}

void destroi_fila(PFila fila) {
    if(fila != NULL) {
        destroi_fila_recursivo(fila->inicio);
        free(fila);
    }
}

int fila_vazia(PFila fila) {
    return fila->tamanho == 0 ? 1 : 0;
}

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

void imprime_fila(PFila fila, void (*imprime)(void *)) {
    PFNo atual;

    for(atual = fila->inicio; atual != NULL; atual = atual->proximo) {
        (*imprime)(atual->dado);
    }
    printf("\n");
}
