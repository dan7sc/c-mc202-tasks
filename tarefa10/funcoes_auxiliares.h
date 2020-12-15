#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

#include "hash.h"

Boolean compara_caracteres(char a, char b);

int verifica_caracteres(char *valor, char *palavra);

void verifica_palavra_no_dicionario(PHash hash, char *palavra);

#endif
