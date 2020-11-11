#ifndef ARVORE_H
#define ARVORE_H

#define TAM_STR 7

typedef enum percurso {
    pre_ordem = 0,
    in_ordem = 1,
    pos_ordem = 2
} EPercurso;

typedef struct contagem {
    int soma;
    int contador;
} Contagem;

typedef struct cartao {
    int numero;
    char texto[TAM_STR];
} Cartao;

typedef struct autoridade {
    int numero;
} Autoridade;

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

PNo cria_no(void *dado, PNo esq, PNo dir);

Arvore cria_arvore();

void destroi_no(PNo no);

void destroi_arvore(Arvore av);

PNo insere_no(PNo no, void *dado, int (*compara)(void *, void *));

Arvore insere(Arvore av, void *dado, int (*compara)(void *, void *));

PNo busca_no(PNo no, void *dado, int (*compara)(void *, void *));

PNo busca(Arvore av, void *dado, int (*compara)(void *, void *));

void percorre_pre_ordem(PNo no, void (*imprime)(void *));

void percorre_in_ordem(PNo no, void (*imprime)(void *));

void percorre_pos_ordem(PNo no, void (*imprime)(void *));

void percorre(Arvore av, EPercurso percurso, void (*imprime)(void *));

Contagem conta_triade_no(PNo no, int numero, Contagem *contagem, int (*soma)(void *, void *));

void conta_triade(Arvore av, int numero, int (*soma)(void *, void *));

#endif
