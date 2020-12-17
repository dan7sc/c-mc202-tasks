#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

PNo cria_lista() {
    PNo lista = NULL;

    return lista;
}

void destroi_lista(PNo lista) {
    if(lista != NULL) {
        destroi_lista(lista->proximo);
        /* free(lista->dado); */
        free(lista);
    }
}

PNo adiciona_na_lista(PNo lista, void *dado) {
    PNo novo;

    novo = malloc(sizeof(No));
    novo->dado = dado;
    novo->proximo = lista;
    lista = novo;

    return lista;
}

PNo remove_da_lista(PNo lista) {
    PNo novo;

    if(lista == NULL) {
        return NULL;
    }
    novo = lista;
    lista = lista->proximo;

    free(novo->dado);
    free(novo);

    return lista;
}

void imprime_lista(PNo lista, void (*imprime)(void *)) {
    PNo atual;

    for(atual = lista; atual != NULL; atual = atual->proximo) {
        (*imprime)(atual->dado);
    }
}
