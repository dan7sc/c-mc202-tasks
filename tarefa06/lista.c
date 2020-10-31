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
    PNo temp;

    while(lista->inicio != NULL) {
        temp = lista->inicio->proximo;
        free(lista->inicio);
        lista->inicio = temp;
    }

    free(lista);
}

void imprime_lista_atendimento(PLista lista) {
    PNo atual;

    atual = lista->inicio;
    while(atual != NULL) {
        printf("%d ", atual->dado.especialidade.id);
        atual = atual->proximo;
    }
}

void imprime_lista_paciente(PLista lista) {
    PNo atual;

    atual = lista->inicio;
    while(atual != NULL) {
        printf("%s ", atual->dado.paciente.nome);
        printf("%s ", atual->dado.paciente.prioridade);
        imprime_lista_atendimento(atual->dado.paciente.lista_atendimento);
        printf("\n");
        atual = atual->proximo;
    }
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

PLista remove_elemento_no_fim(PLista lista) {
    PNo novo_fim;
    PNo temp;

    if(lista->fim == NULL) {
        return lista;
    }

    temp = lista->fim;
    novo_fim = lista->fim->anterior;
    novo_fim->proximo = NULL;
    lista->fim->anterior = NULL;
    lista->fim = novo_fim;
    lista->tamanho--;

    free(temp);

    return lista;
}

PLista remove_elemento_no_inicio(PLista lista) {
    PNo novo_inicio;
    PNo temp;

    if(lista->inicio == NULL) {
        return lista;
    }

    temp = lista->inicio;
    novo_inicio = lista->inicio->proximo;
    novo_inicio->anterior = NULL;
    lista->inicio->proximo = NULL;
    lista->inicio = novo_inicio;
    lista->tamanho--;

    free(temp);

    return lista;
}
