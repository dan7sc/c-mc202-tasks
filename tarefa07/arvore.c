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
