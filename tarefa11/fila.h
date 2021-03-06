#ifndef FILA_H
#define FILA_H

typedef struct fno * PFNo;

typedef struct fno {
    void *dado; // ponteiro para o dado do nó
    PFNo proximo; // ponteiro para o proximo nó da fila
} FNo;

typedef struct fila {
    int tamanho; // tamanho da fila
    PFNo inicio; // ponteiro para o inicio da fila
    PFNo fim; // ponteiro para o fim da fila
} Fila;
typedef Fila * PFila;

PFila cria_fila();

void destroi_fila(PFila fila);

int fila_vazia(PFila fila);

PFila enfileira(PFila fila, void *dado);

void *desenfileira(PFila fila);

void imprime_fila(PFila fila, void (*imprime)(void *));

#endif
