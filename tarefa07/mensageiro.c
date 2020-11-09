#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main() {
    Arvore av = cria_arvore();
    int x;

    av = insere(av, 2);
    av = insere(av, 1);
    av = insere(av, 3);
    av = insere(av, 4);

    for(int i = 1; i < 6; i++) {
        x = busca(av, i);
        printf("%d\n", x);
    }

    percorre(av, pre_ordem);
    percorre(av, in_ordem);
    percorre(av, pos_ordem);

    return 0;
}
