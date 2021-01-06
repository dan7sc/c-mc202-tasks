#ifndef PILHA_H
#define PILHA_H

typedef struct ppno * PPNo;

typedef struct ppno {
    void *dado;
    PPNo proximo;
} PINo;

typedef struct pilha {
    int tamanho;
    PPNo topo;
} Pilha;
typedef Pilha * PPilha;

PPilha cria_pilha();

void destroi_pilha(PPilha pilha);

int pilha_vazia(PPilha pilha);

PPilha empilha(PPilha pilha, void *dado);

void *desempilha(PPilha pilha);

void imprime_pilha(PPilha pilha, void (*imprime)(void *));

#endif
