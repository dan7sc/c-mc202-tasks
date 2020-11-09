#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main() {
    Arvore av = cria_arvore();

    av = insere(av, 2);
    av = insere(av, 1);
    av = insere(av, 3);
    av = insere(av, 4);

    printf("%d\n", av.raiz->dado);
    printf("%d\n", av.raiz->esq->dado);
    printf("%d\n", av.raiz->dir->dado);
    printf("%d\n", av.raiz->dir->dir->dado);

    return 0;
}
