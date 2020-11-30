#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define N 16

int main() {
    Arvore av;
    /* int v[N] = { 25, 14, 13, 11, 28, 29, 27, 26}; */
    int v[N] = { 11, 7, 15, 5, 3, 9, 8, 10, 13, 12, 14, 20, 18, 25, 25, 3 };

    av = cria_arvore();

    for(int i = 0; i < N; i++) {
        av = insere(av, v[i]);
    }

    percorre(av, pre_ordem);
    percorre(av, in_ordem);
    percorre(av, pos_ordem);

    return 0;
}
