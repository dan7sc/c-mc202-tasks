#ifndef FUNCOES_DE_AJUDA_H
#define FUNCOES_DE_AJUDA_H

#include "arvore.h"

int le_int(int *num);

void le_string_entre_aspas(char *str);

int compara_numero_cartao(void *numero, void *cartao);

int compara_cartao(void *t_cartao, void *cartao);

int compara_autoridade_numero(void *numero, void *autoridade);

void imprime_cartao(void *cartao);

void imprime_mensagem(void *cartao);

void imprime_autoridade(void *autoridade);

void concatena_cartao(void *cartao);

Cartao *concatena_string(Cartao *cartao, void *dado);

int soma(void *a, void *b);

void destroi_cartao(void *cartao);

#endif
