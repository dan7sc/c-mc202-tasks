#include <stdio.h>
#include "heap.h"

#define N_ACAO 250

int main() {
    PHeap fila;

    fila = cria_heap(N_ACAO);

    for (int i = 1; i < 11; i++){
        fila = insere(fila, i);
    }

    imprime_sequencia(fila);

    remove_max(fila);
    fila = heap_sort(fila);

    imprime_heap(fila, 0, 1);

    destroi_heap(fila);

    return 0;
}
