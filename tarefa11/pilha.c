#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

PPilha cria_pilha() {
    PPilha pilha = malloc(sizeof(Pilha));

    pilha->tamanho = 0;
    pilha->topo = NULL;

    return pilha;
}

void destroi_pilha_recursivo(PPNo no) {
    if(no != NULL) {
        destroi_pilha_recursivo(no->proximo);
        /* free(no->dado); */
        free(no);
    }
}

void destroi_pilha(PPilha pilha) {
    if(pilha != NULL) {
        destroi_pilha_recursivo(pilha->topo);
        free(pilha);
    }
}

int pilha_vazia(PPilha pilha) {
    return pilha->tamanho == 0 ? 1 : 0;
}

PPilha empilha(PPilha pilha, void *dado) {
    PPNo novo;

    novo = malloc(sizeof(PINo));
    novo->dado = dado;
    novo->proximo = NULL;

    if(pilha->topo == NULL) {
        pilha->topo = novo;
        pilha->tamanho = 1;
        return pilha;
    }

    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;

    return pilha;
}

void *desempilha(PPilha pilha) {
    PPNo topo;
    void *dado;

    if(pilha->topo == NULL) {
        return NULL;
    }

    topo = pilha->topo;
    pilha->topo = pilha->topo->proximo;

    dado = topo->dado;
    pilha->tamanho--;

    topo->proximo = NULL;
    free(topo);

    return dado;
}

void imprime_pilha(PPilha pilha, void (*imprime)(void *)) {
    PPNo atual;

    for(atual = pilha->topo; atual != NULL; atual = atual->proximo) {
        (*imprime)(atual->dado);
    }
    printf("\n");
}
