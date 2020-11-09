#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

PNo cria_no(int dado, PNo esq, PNo dir) {
    PNo raiz = malloc(sizeof(No));

    raiz->dado = dado;
    raiz->esq = esq;
    raiz->dir = dir;

    return raiz;
}

Arvore cria_arvore() {
    Arvore av;

    av.raiz = NULL;

    return av;
}

PNo insere_no(PNo no, int dado) {
    PNo novo_no;

    if(no == NULL) {
        novo_no = cria_no(dado, NULL, NULL);
        no = novo_no;
        return no;
    }

    if(dado <= no->dado) {
        no->esq = insere_no(no->esq, dado);
    } else {
        no->dir = insere_no(no->dir, dado);
    }

    return no;
}

Arvore insere(Arvore av, int dado) {
    av.raiz = insere_no(av.raiz, dado);

    return av;
}

PNo busca_no(PNo no, int dado) {
    if(no == NULL  || dado == no->dado) {
        return no;
    }

    if(dado < no->dado) {
        return busca_no(no->esq, dado);
    } else {
        return busca_no(no->dir, dado);
    }
}

int busca(Arvore av, int dado) {
    PNo no;

    if(av.raiz == NULL || dado == av.raiz->dado) {
        return av.raiz->dado;
    } else {
        no = busca_no(av.raiz, dado);
        if(no == NULL) {
            return -1;
        }
        return no->dado;
    }
}
