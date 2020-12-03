#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

// enum para definir boolean: { FALSE = 0, TRUE = 1 }
typedef enum {
    FALSE,
    TRUE
} Boolean;

typedef struct heap {
    int *v_dados; // vetor de dados do tipo int
    int  n_elementos; // numero de elementos no vetor
    int tam_max; // numero maximo de elementos no vetor
} Heap;
typedef Heap * PHeap;

int obtem_pai(int indice);

int obtem_fesq(int indice);

int obtem_fdir(int indice);

PHeap cria_heap(int tam_max);

void destroi_heap(PHeap heap);

void troca(int *x, int *y);

void sobe_heap(PHeap heap, int indice);

void desce_heap (PHeap heap, int indice);

Boolean heap_cheio(PHeap heap);

Boolean heap_vazio(PHeap heap);

PHeap insere(PHeap h, int dado);

int remove_max(PHeap heap);

PHeap heap_sort(PHeap heap);

void imprime_sequencia(PHeap heap);

void imprime_heap(PHeap heap, int indice, int nivel);

#endif
