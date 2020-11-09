#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

#define TAM_NOME 50 // limite da string do nome do paciente
#define NUM_ESPECIALISTAS 9 // numero de especialistas
#define NUM_PROFISSIONAIS 38 // numero de profissionais

typedef struct Lista * PLista;

typedef enum Prioridade {
    normal = 0,
    preferencial = 1
} EPrioridade;

typedef struct horario {
    int horas;
    int minutos;
} Horario;

typedef struct paciente {
    char nome[TAM_NOME];
    EPrioridade prioridade;
    int ordem_de_chegada;
    int horario_de_saida;
    PLista lista_atendimento;
} Paciente;

typedef union TDado {
    int id;
    Paciente paciente;
} TDado;

typedef struct No {
    TDado dado;
    struct No *anterior;
    struct No *proximo;
} No;
typedef struct No * PNo;

typedef struct Lista {
    int tamanho;
    No *inicio;
    No *fim;
} Lista;

PLista cria_lista();

void destroi_lista(PLista lista);

PLista adiciona_elemento_no_inicio(PLista lista, TDado dado);

PLista adiciona_elemento_no_fim(PLista lista, TDado dado);

TDado *remove_elemento_no_inicio(PLista lista);

#endif
