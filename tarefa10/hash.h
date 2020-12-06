#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N_CHAR 25

// enum para definir boolean: { FALSE = 0, TRUE = 1 }
typedef enum {
    FALSE,
    TRUE
} Boolean;

typedef struct tabela {
    char **valor;
} Tabela;

typedef struct hash {
    Tabela *tabela;
    int tamanho;
} Hash;
typedef struct hash * PHash;

PHash cria_tabela_hash(int tamanho);

void destroi_tabela_hash(PHash hash);

int f_hash(PHash hash, char *chave);

PHash insere(PHash hash, char *valor);

char *remove_valor(PHash hash, char *valor);

char *busca(PHash hash, char *valor);

void imprime_tabela_hash(PHash hash);

#endif
