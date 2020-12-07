#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

#include "hash.h"

void inicializa_string(char *str, int tamanho);

Boolean compara_caracteres(char a, char b);

void gera_substring(char *string, int inicio, char *substring, int tamanho);

Boolean eh_substring(char *string, int inicio, char *substring);

Boolean contem_string_substring(char *string, char *substring);

int conta_substrings_B_em_A(char *string_a, char *string_b);

Boolean verifica_verossimilhanca(char *string_a, char *string_b);

int verifica_remocao_caractere(char *valor, char *palavra);

int verifica_insercao_caractere(char *valor, char *palavra);

int verifica_troca_caracteres(char *valor, char *palavra);

void verifica_palavra_dicionario(PHash hash, char *palavra);

#endif
