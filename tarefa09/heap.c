#include "heap.h"
#include <math.h>

int obtem_pai(int indice) {
    return (indice - 1) / 2;
}

int obtem_fesq(int indice) {
    return 2*indice + 1;
}

int obtem_fdir(int indice) {
    return 2*indice + 2;
}

PHeap cria_heap(int tam_max) {
    PHeap heap = malloc(sizeof(Heap));

    heap->tam_max = tam_max;
    heap->n_elementos = 0;
    heap->v_dados = malloc(tam_max * sizeof(int));

    return heap;
}

void destroi_heap(PHeap heap) {
    free(heap->v_dados);
    free(heap);
}

void troca(int *x, int *y) {
    int aux;

    aux = *x;
    *x = *y;
    *y = aux;
}

void sobe_heap(PHeap heap, int indice) {
    int pai;

    pai = obtem_pai(indice);
    if( (pai >= 0) && (heap->v_dados[pai] < heap->v_dados[indice]) ) {
        troca(&heap->v_dados[indice], &heap->v_dados[pai]);
        pai = obtem_pai(indice);
        sobe_heap(heap, pai);
    }
}

void desce_heap (PHeap heap, int indice) {
    int maior, esq, dir;

    esq = obtem_fesq(indice);
    dir = obtem_fdir(indice);

    if ((esq < heap->n_elementos) && (heap->v_dados[esq] > heap->v_dados[indice])) {
        maior = esq;
    } else {
        maior = indice;
    }

    if ((dir < heap->n_elementos) && (heap->v_dados[dir] > heap->v_dados[maior])) {
        maior = dir;
    }

    if (maior != indice) {
        troca(&heap->v_dados[indice], &heap->v_dados[maior]);
        desce_heap(heap, maior);
    }
}

Boolean heap_cheio(PHeap heap) {
    if (heap->n_elementos >= heap->tam_max) {
        return TRUE;
    } else {
        return FALSE;
    }
}

Boolean heap_vazio(PHeap heap) {
    if (heap->n_elementos <= 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

PHeap insere(PHeap heap, int dado) {
    if (!heap_cheio(heap)) {
        heap->n_elementos++;
        heap->v_dados[heap->n_elementos - 1] = dado;
        sobe_heap(heap, heap->n_elementos - 1);
    }

    return heap;
}

int remove_max(PHeap heap) {
    int dado;

    if (!heap_vazio(heap)) {
        dado = heap->v_dados[0];
        heap->v_dados[0]  = heap->v_dados[heap->n_elementos - 1];
        heap->n_elementos--;
        desce_heap(heap, 0);
    }

    return dado;
}

PHeap heap_sort(PHeap heap) {
    int n;

    n = heap->n_elementos;
    for (int i = heap->n_elementos - 1; i > 0; i--) {
        troca(&heap->v_dados[i], &heap->v_dados[0]);
        heap->n_elementos--;
        desce_heap(heap, 0);
    }
    heap->n_elementos = n;

    return heap;
}

void imprime_sequencia(PHeap heap) {
    for (int i = 0; i < heap->n_elementos; i++) {
        printf("%d ", heap->v_dados[i]);
    }
    printf("\n");

}

void imprime_heap(PHeap heap, int indice, int nivel) {
    if (indice < heap->n_elementos){
        imprime_heap(heap, obtem_fdir(indice), nivel + 1);
        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("%03d", heap->v_dados[indice]);
        for (int i = 0; i <= log2(heap->n_elementos) - nivel; i++) {
            printf("---");
        }
        printf("\n");
        imprime_heap(heap, obtem_fesq(indice), nivel + 1);
    }
}
