#ifndef FILA_H
#define FILA_H

typedef struct fno * PFNo;

typedef struct fno {
    void *dado;
    PFNo proximo;
} FNo;

typedef struct fila {
    int tamanho;
    PFNo inicio;
    PFNo fim;
} Fila;
typedef Fila * PFila;

PFila cria_fila();

void destroi_fila(PFila fila);

int fila_vazia(PFila fila);

PFila enfileira(PFila fila, void *dado);

void *desenfileira(PFila fila);

void imprime_fila(PFila fila, void (*imprime)(void *));

#endif
