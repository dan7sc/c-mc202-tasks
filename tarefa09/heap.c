#include "heap.h"
#include <string.h>
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
    heap->v_dados = malloc(tam_max * sizeof(Cliente));

    return heap;
}

void destroi_heap(PHeap heap) {
    free(heap->v_dados);
    free(heap);
}

void troca(Cliente *x, Cliente *y) {
    Cliente aux;

    aux = *x;
    *x = *y;
    *y = aux;
}

void sobe_heap(PHeap heap, int indice) {
    int pai;

    pai = obtem_pai(indice);
    if( (pai >= 0) && (heap->v_dados[pai].avaliacao < heap->v_dados[indice].avaliacao) ) {
        troca(&heap->v_dados[indice], &heap->v_dados[pai]);
        pai = obtem_pai(indice);
        sobe_heap(heap, pai);
    }
}

void desce_heap (PHeap heap, int indice) {
    int maior, esq, dir;

    esq = obtem_fesq(indice);
    dir = obtem_fdir(indice);

    if ((esq < heap->n_elementos) && (heap->v_dados[esq].avaliacao > heap->v_dados[indice].avaliacao)) {
        maior = esq;
    } else {
        maior = indice;
    }

    if ((dir < heap->n_elementos) && (heap->v_dados[dir].avaliacao > heap->v_dados[maior].avaliacao)) {
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

PHeap insere(PHeap heap, Cliente dado) {
    if (!heap_cheio(heap)) {
        heap->n_elementos++;
        heap->v_dados[heap->n_elementos - 1] = dado;
        sobe_heap(heap, heap->n_elementos - 1);
    }

    return heap;
}

Cliente *remove_max(PHeap heap) {
    Cliente *dado = NULL;

    if (heap_vazio(heap)) {
        return NULL;
    }

    dado = malloc(sizeof(Cliente));
    *dado = heap->v_dados[0];
    heap->v_dados[0]  = heap->v_dados[heap->n_elementos - 1];
    heap->n_elementos--;
    desce_heap(heap, 0);

    return dado;
}

void maximiza_prioridade(PHeap heap, char *str) {
    for (int i = 0; i < heap->n_elementos; i++) {
        if(strcmp(str, heap->v_dados[i].nome) == 0) {
            heap->v_dados[i].avaliacao = 6;
            sobe_heap(heap, i);
        }
    }
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
        printf("%.16lf ", heap->v_dados[i].avaliacao);
    }
    printf("\n");

}

void imprime_heap(PHeap heap, int indice, int nivel) {
    if (indice < heap->n_elementos){
        imprime_heap(heap, obtem_fdir(indice), nivel + 1);
        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("%03.16lf", heap->v_dados[indice].avaliacao);
        for (int i = 0; i <= log2(heap->n_elementos) - nivel; i++) {
            printf("---");
        }
        printf("\n");
        imprime_heap(heap, obtem_fesq(indice), nivel + 1);
    }
}
