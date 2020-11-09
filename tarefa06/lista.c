#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

PLista cria_lista() {
    PLista lista = malloc(sizeof(Lista));

    lista->tamanho = 0;
    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

void destroi_lista(PLista lista) {
    PNo no = NULL;
    PNo temp = NULL;

    no = lista->inicio;
    while (no != NULL) {
        temp = no;
        no = no->proximo;
        free(temp);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;

    free(lista);
}

PLista adiciona_elemento_no_inicio(PLista lista, TDado dado) {
    PNo novo;

    novo = malloc(sizeof(No));
    novo->dado = dado;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if(lista->fim == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
        lista->tamanho++;
        return lista;
    }

    novo->proximo = lista->inicio;
    lista->inicio->anterior = novo;
    lista->inicio = novo;
    lista->tamanho++;

    return lista;
}

PLista adiciona_elemento_no_fim(PLista lista, TDado dado) {
    PNo novo;

    novo = malloc(sizeof(No));
    novo->dado = dado;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if(lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
        lista->tamanho++;
        return lista;
    }

    novo->anterior = lista->fim;
    lista->fim->proximo = novo;
    lista->fim = novo;
    lista->tamanho++;

    return lista;
}

TDado *remove_elemento_no_inicio(PLista lista) {
    PNo novo_inicio;
    PNo temp;
    TDado *elemento;

    if(lista->inicio == NULL) {
        elemento = &lista->inicio->dado;
        return elemento;
    }

    temp = lista->inicio;
    novo_inicio = lista->inicio->proximo;

    if(novo_inicio == NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
        elemento = &temp->dado;

        return elemento;
    }

    lista->inicio = novo_inicio;
    novo_inicio->anterior = NULL;
    temp->proximo = NULL;
    lista->tamanho--;

    elemento = &temp->dado;

    return elemento;
}
