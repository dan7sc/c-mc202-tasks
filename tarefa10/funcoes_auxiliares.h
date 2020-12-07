#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

#include "hash.h"

void inicializa_string(char *str, int tamanho);

Boolean compara_caracteres(char a, char b);

void gera_substring(char *string, int inicio, char *substring, int tamanho);

Boolean eh_substring(char *string, int inicio, char *substring);

Boolean contem_substring(char *string, char *substring);

Boolean verifica_verossimilhanca(char *string_a, char *string_b);

int verifica_caracteres_faltantes(char *valor, char *palavra);

int verifica_caracteres_excedentes(char *valor, char *palavra);

int verifica_caracteres_trocados(char *valor, char *palavra);

void verifica_palavra_no_dicionario(PHash hash, char *palavra);

#endif
