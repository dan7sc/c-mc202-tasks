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
    int altura;
    int quantidade;
} No;
typedef struct no * PNo;

typedef struct arvore {
    PNo raiz;
} Arvore;
typedef struct arvore * PArvore;

PNo cria_no(int dado);

Arvore cria_arvore();

void destroi_no(PNo no);

void destroi_arvore_recursivo(PNo no);

void destroi_arvore(Arvore av);

PNo rotaciona_para_esquerda(PNo no);

PNo rotaciona_para_direita(PNo no);

PNo insere_no(PNo no, int dado);

Arvore insere(Arvore av, int dado);

PNo remove_sucessor(PNo no);

PNo remove_no_recursivo(PNo no, int dado);

Arvore remove_no(Arvore av, int dado);

PNo busca_no(PNo no, int dado);

PNo busca(Arvore av, int dado);

void percorre_pre_ordem(PNo no);

void percorre_in_ordem(PNo no);

void percorre_pos_ordem(PNo no);

void percorre(Arvore av, EPercurso percurso);

int obtem_maximo(int a, int b);

int obtem_altura(PNo no);

int obtem_balanceamento(PNo no);

int le_int(int *num);

void imprime_numero(int numero);

void troca_dados(PNo no_a, PNo no_b);

PNo copia_dado(PNo no_a, PNo no_b);

#endif
