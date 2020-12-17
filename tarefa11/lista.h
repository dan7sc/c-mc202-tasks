#ifndef LISTA_H
#define LISTA_H

typedef struct No * PNo;

typedef struct No {
    void **dado;
    struct No *proximo;
} No;

PNo cria_lista();

void destroi_lista(PNo lista);

PNo adiciona_na_lista(PNo lista, void *dado);

PNo remove_da_lista(PNo lista);

void imprime_lista(PNo lista, void (*imprime)(void *));

#endif
