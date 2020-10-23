#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *prox;
} No;

typedef struct No * PNo;

PNo cria_lista() {
    return NULL;
}

void destroi_lista(PNo lista) {
    if(lista != NULL) {
        destroi_lista(lista->prox);
        free(lista);
    }
}

void imprime_lista(PNo lista) {
    PNo atual;

    atual = lista;
    while(atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

PNo adiciona_elemento(PNo lista, int dado) {
    PNo novo;

    novo = malloc(sizeof(No));
    novo->dado = dado;
    novo->prox = lista;

    return novo;
}

PNo adiciona_elemento_no_fim(PNo lista, int dado) {
    PNo novo;
    PNo temp = lista;

    novo = malloc(sizeof(No));

    novo->dado = dado;
    novo->prox = NULL;

    if(lista == NULL) {
        return novo;
    }

    while(temp->prox != NULL) {
        temp = temp->prox;
    }
    temp->prox = novo;

    return lista;
}

int main() {
    PNo lista;

    lista = cria_lista();

    for(int i = 1; i < 10; i++) {
        lista = adiciona_elemento_no_fim(lista, i);
    }

    imprime_lista(lista);
    destroi_lista(lista);

    return 0;
}
