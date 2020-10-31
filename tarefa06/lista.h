#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

#define TAM_STR 50

typedef struct _Atendimento {
    int id;
} Atendimento;

typedef struct Atendimento * PAtendimento;

typedef struct Lista * PLista;

typedef struct paciente {
    char nome[TAM_STR];
    char prioridade[TAM_STR];
    PLista lista_atendimento;
} Paciente;

typedef struct Paciente * PPaciente;

typedef union TDado {
    Atendimento especialidade;
    Paciente paciente;
} TDado;

typedef struct No {
    TDado dado;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct Lista {
    int tamanho;
    No *inicio;
    No *fim;
} Lista;

typedef struct No * PNo;

typedef struct Lista * PLista;

PLista cria_lista();

void destroi_lista(PLista lista);

void imprime_lista_atendimento(PLista lista);

void imprime_lista_paciente(PLista lista);

PLista adiciona_elemento_no_inicio(PLista lista, TDado dado);

PLista adiciona_elemento_no_fim(PLista lista, TDado dado);

PLista remove_elemento_no_fim(PLista lista);

PLista remove_elemento_no_inicio(PLista lista);

#endif
