#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

#define TAM_NOME 50
#define NUM_ESPECIALISTAS 9
#define NUM_PROFISSIONAIS 38

typedef enum Prioridade {
    normal = 0,
    preferencial = 1
} EPrioridade;

typedef struct Lista * PLista;

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
typedef struct Paciente * PPaciente;

typedef struct atendimento {
    int qtde_profissionais_por_id[9];
    int qtde_ocupados_por_id[9];
    PLista pacientes_em_atendimento;
} Atendimento;
typedef struct atendimento * PAtendimento;

typedef union TDado {
    int id;
    Paciente paciente;
    Atendimento atendimento;
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

char *converte_enum_para_string(EPrioridade prior);

EPrioridade converte_string_para_enum(char *str);

PLista cria_lista();

void destroi_lista(PLista lista);

void imprime_lista_atendimento(PLista lista);

void imprime_lista_paciente(PLista lista);

Horario converte_segundos_em_horas_minutos(int segundos);

void imprime_lista_saida_pacientes(PLista lista);

PLista adiciona_elemento_no_inicio(PLista lista, TDado dado);

PLista adiciona_elemento_no_fim(PLista lista, TDado dado);

TDado *remove_elemento_no_inicio(PLista lista);

/* PLista remove_elemento_no_fim(PLista lista); */

/* PLista remove_elemento_no_inicio(PLista lista); */

#endif
