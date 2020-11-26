#ifndef ARVORE_H
#define ARVORE_H

#define TAM_TEXTO 5

typedef enum percurso {
    pre_ordem = 0,
    in_ordem = 1,
    pos_ordem = 2
} EPercurso;

typedef struct cartao {
    int numero;
    char *texto;
} Cartao;

typedef struct triade {
    int num_cartao1;
    int num_cartao2;
    int num_cartao3;
} Triade;

typedef struct no {
    void *dado;
    struct no *esq;
    struct no *dir;
} No;
typedef struct no * PNo;

typedef struct arvore {
    PNo raiz;
} Arvore;
typedef struct arvore * PArvore;

PNo cria_no(void *dado);

Arvore cria_arvore();

void destroi_no(PNo no);

void destroi_arvore_recursivo(PNo no, void (*destroi)(void *));

void destroi_arvore(Arvore av, void (*destroi)(void *));

void destroi_triade(Triade *t);

PNo insere_no(PNo no, void *dado, int (*compara)(void *, void *));

Arvore insere(Arvore av, void *dado, int (*compara)(void *, void *));

PNo remove_sucessor(PNo no);

PNo remove_no_recursivo(PNo no, void *dado, int (*compara)(void *, void *));

Arvore remove_no(Arvore av, void *dado, int (*compara)(void *, void *));

PNo busca_no(PNo no, void *dado, int (*compara)(void *, void *));

PNo busca(Arvore av, void *dado, int (*compara)(void *, void *));

void percorre_pre_ordem(PNo no, void (*imprime)(void *));

void percorre_in_ordem(PNo no, void (*imprime)(void *));

void percorre_pos_ordem(PNo no, void (*imprime)(void *));

void percorre(Arvore av, EPercurso percurso, void (*imprime)(void *));

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
