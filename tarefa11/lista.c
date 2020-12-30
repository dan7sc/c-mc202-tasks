#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* A funcao aloca memoria para tipo PNo,
   inicializa a lista, retornando a lista
*/
PNo cria_lista() {
    PNo lista = NULL;

    return lista;
}

/* A funcao recebe a lista e
   desaloca memoria para cada nó,
   desalocando a memoria da lista por ultimo
*/
void destroi_lista(PNo lista) {
    if(lista != NULL) {
        destroi_lista(lista->proximo);
        free(lista);
    }
}

/* A funcao recebe a lista e o dado a ser
   armazenado na lista, retornando
   a lista com o dado inserido no inicio dela
*/
PNo adiciona_na_lista(PNo lista, void *dado) {
    PNo novo;

    novo = malloc(sizeof(No));
    novo->dado = dado;
    novo->proximo = lista;
    lista = novo;

    return lista;
}

/* A funcao recebe a lista e
   remove o primeiro elemento da lista,
   retornando ponteiro para a nova lista
   e desaloca a memoria do dado removido
*/
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

/* A funcao recebe a lista e ponteiro para funcao imprime,
   imprime os dados do inicio ao fim da lista
*/
void imprime_lista(PNo lista, void (*imprime)(void *)) {
    PNo atual;

    for(atual = lista; atual != NULL; atual = atual->proximo) {
        (*imprime)(atual->dado);
    }
}
