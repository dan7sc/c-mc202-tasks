#ifndef ARVORE_H
#define ARVORE_H

typedef enum percurso {
    pre_ordem = 0,
    in_ordem = 1,
    pos_ordem = 2
} EPercurso;

typedef struct no {
    int dado;
    struct no *esq;
    struct no *dir;
} No;
typedef struct no * PNo;

typedef struct arvore {
    PNo raiz;
} Arvore;
typedef struct arvore * PArvore;

PNo cria_no(int dado, PNo esq, PNo dir);

Arvore cria_arvore();

PNo insere_no(PNo no, int dado);

Arvore insere(Arvore av, int dado);

PNo busca_no(PNo no, int dado);

int busca(Arvore av, int dado);

void percorre_pre_ordem(PNo no);

void percorre_in_ordem(PNo no);

void percorre_pos_ordem(PNo no);

void percorre(Arvore av, EPercurso percurso);

#endif
