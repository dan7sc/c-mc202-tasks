#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N_CHAR 15 // numero maximo de caracteres no nome do cliente
#define N_ACAO 500 // numero maximo de ações realizadas pelo motorista

// enum para definir boolean: { FALSE = 0, TRUE = 1 }
typedef enum {
    FALSE,
    TRUE
} Boolean;

typedef struct posicao {
    int x; // coordenada cartesiana x
    int y; // coordenada cartesiana y
} Posicao;

typedef struct cliente {
    char nome[N_CHAR]; // nome do cliente
    double avaliacao; // avalicação do cliente
    Posicao origem; // posicao de origem do cliente
    Posicao destino; // posicao do destino do cliente
} Cliente;

typedef struct heap {
    Cliente *v_dados; // vetor de dados do tipo int
    int  n_elementos; // numero de elementos no vetor
    int tam_max; // numero maximo de elementos no vetor
} Heap;
typedef Heap * PHeap;

int obtem_pai(int indice);

int obtem_fesq(int indice);

int obtem_fdir(int indice);

PHeap cria_heap(int tam_max);

void destroi_heap(PHeap heap);

void troca(Cliente *x, Cliente *y);

void sobe_heap(PHeap heap, int indice);

void desce_heap (PHeap heap, int indice);

Boolean heap_cheio(PHeap heap);

Boolean heap_vazio(PHeap heap);

PHeap insere(PHeap h, Cliente dado);

Cliente *remove_max(PHeap heap);

void maximiza_prioridade(PHeap heap, char *str);

PHeap heap_sort(PHeap heap);

void imprime_sequencia(PHeap heap);

void imprime_heap(PHeap heap, int indice, int nivel);

#endif
