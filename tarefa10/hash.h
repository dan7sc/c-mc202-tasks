#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N_CHAR 25 // numero maximo de caracteres das palavras

// enum para definir boolean: { FALSE = 0, TRUE = 1 }
typedef enum {
    FALSE,
    TRUE
} Boolean;

typedef struct tabela {
    char **valor; // valor guardado no hash
} Tabela;

typedef struct hash {
    Tabela *tabela; // tabela de hashing
    int tamanho; // tamanho da tabela de hashing
} Hash;
typedef struct hash * PHash;

int busca_potencia2_maior_N(int n);

Boolean eh_primo(int num);

int busca_primo(int tamanho);

PHash cria_tabela_hash(int tamanho);

void destroi_tabela_hash(PHash hash);

int f_hash(PHash hash, char *chave);

PHash insere(PHash hash, char *valor);

char *remove_valor(PHash hash, char *valor);

char *busca(PHash hash, char *valor);

void imprime_tabela_hash(PHash hash);

#endif
