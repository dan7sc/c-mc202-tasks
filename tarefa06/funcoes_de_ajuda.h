#ifndef FUNCOES_DE_AJUDA_H
#define FUNCOES_DE_AJUDA_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int le_int(int *num);

void le_string(char *str);

void le_string_entre_aspas(char *str);

int compara_elementos(const void *elemento_a, const void *elemento_b);

Horario converte_segundos_em_horas_minutos(int segundos);

void imprime_lista_saida_pacientes(PLista lista);

char *converte_enum_para_string(EPrioridade prior);

EPrioridade converte_string_para_enum(char *str);

#endif
