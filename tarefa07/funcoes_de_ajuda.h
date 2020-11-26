#ifndef FUNCOES_DE_AJUDA_H
#define FUNCOES_DE_AJUDA_H

#include "arvore.h"

int le_int(int *num);

void le_string_entre_aspas(char *str);

int compara_numero_cartao(void *numero, void *cartao);

void imprime_mensagem(void *cartao);

Cartao *concatena_string(Cartao *cartao, void *dado);

int soma(void *numero, void *cartao);

void destroi_texto(void *cartao);

void troca_dados(PNo no_a, PNo no_b);

PNo copia_dado(PNo no_a, PNo no_b);

int obtem_numero(void *dado);

void soma_triade_recursivo(Arvore av, PNo no, PNo no_b, int numero, Triade *t, int (*soma)(void *, void *), int (*compara)(void *, void *));

void busca_triade_recursivo(Arvore av, PNo no, PNo no_b, int numero, Triade *t, int (*soma)(void *, void *), int (*compara)(void *, void *));

Triade *busca_triade(Arvore av, Triade *t, int numero, int (*soma)(void *, void *), int (*compara)(void *, void *));

Cartao *cria_cartao_recursivo(PNo no, Cartao *cartao, Cartao *(*concatena)(Cartao *cartao, void *dado));

Cartao *cria_cartao(Arvore av, Cartao *cartao, Cartao *(*concatena)(Cartao *cartao, void *dado));

#endif
