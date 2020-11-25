#ifndef FUNCOES_DE_AJUDA_H
#define FUNCOES_DE_AJUDA_H

#include "arvore.h"

int le_int(int *num);

void le_string_entre_aspas(char *str);

int compara_numero_cartao(void *numero, void *cartao);

void imprime_mensagem(void *cartao);

Cartao *concatena_string(Cartao *cartao, void *dado);

int soma(void *a, void *b);

void destroi_cartao(void *cartao);

#endif
