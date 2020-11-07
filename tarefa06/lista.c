#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

char *converte_enum_para_string(EPrioridade prior) {
    char *strings[] = { "normal", "preferencial" };

    return strings[prior];
}

EPrioridade converte_string_para_enum(char *str) {
    EPrioridade prioridade = 0;
    char *strings[] = { "normal", "preferencial" };

    if(str[0] == strings[1][0]) {
        prioridade = 1;
    }

    return prioridade;
}

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

void imprime_lista_atendimento(PLista lista) {
    PNo atual;

    atual = lista->inicio;
    while(atual != NULL) {
        printf("%d ", atual->dado.id);

        atual = atual->proximo;
    }
}

void imprime_lista_paciente(PLista lista) {
    PNo atual;
    EPrioridade prioridade;
    char *str;

    atual = lista->inicio;
    while(atual != NULL) {
        prioridade = atual->dado.paciente.prioridade;
        str = converte_enum_para_string(prioridade);

        printf("%d: ", atual->dado.paciente.ordem_de_chegada);
        printf("%s ", atual->dado.paciente.nome);
        printf("%s ", str);
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

/* PLista remove_elemento_no_fim(PLista lista) { */
/*     PNo novo_fim; */
/*     PNo temp; */

/*     if(lista->fim == NULL) { */
/*         return lista; */
/*     } */

/*     temp = lista->fim; */
/*     novo_fim = lista->fim->anterior; */

/*     if(novo_fim == NULL) { */
/*         lista->inicio = NULL; */
/*         lista->fim = NULL; */

/*         free(temp); */

/*         return lista; */
/*     } */

/*     lista->fim = novo_fim; */
/*     novo_fim->proximo = NULL; */
/*     temp->anterior = NULL; */
/*     lista->tamanho--; */

/*     free(temp); */

/*     return lista; */
/* } */

/* PLista remove_elemento_no_inicio(PLista lista) { */
/*     PNo novo_inicio; */
/*     PNo temp; */

/*     if(lista->inicio == NULL) { */
/*         return lista; */
/*     } */

/*     temp = lista->inicio; */
/*     novo_inicio = lista->inicio->proximo; */

/*     if(novo_inicio == NULL) { */
/*         lista->inicio = NULL; */
/*         lista->fim = NULL; */

/*         free(temp); */

/*         return lista; */
/*     } */

/*     lista->inicio = novo_inicio; */
/*     novo_inicio->anterior = NULL; */
/*     temp->proximo = NULL; */
/*     lista->tamanho--; */

/*     free(temp); */

/*     return lista; */
/* } */
