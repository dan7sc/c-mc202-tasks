#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main() {
    Arvore av = cria_arvore();

    av.raiz = cria_no(1, NULL, NULL);
    av.raiz->esq = cria_no(0, NULL, NULL);
    av.raiz->dir = cria_no(2, NULL, NULL);

    printf("%d\n", av.raiz->dado);
    printf("%d\n", av.raiz->esq->dado);
    printf("%d\n", av.raiz->dir->dado);

    return 0;
}
