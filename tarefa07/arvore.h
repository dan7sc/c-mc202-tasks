#ifndef ARVORE_H
#define ARVORE_H

#define TAM_TEXTO 5

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
    char *texto;
} Cartao;

typedef struct autoridade {
    int numero;
} Autoridade;

typedef struct no {
    void *dado;
    struct no *esq;
    struct no *dir;
    struct no *pai;
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

PNo insere_no(PNo no, void *dado, int (*compara)(void *, void *));

Arvore insere(Arvore av, void *dado, int (*compara)(void *, void *));

PNo remove_sucessor(PNo no);

PNo obtem_sucessor_esq(PNo no);

PNo obtem_sucessor_dir(PNo no);

PNo obtem_minimo(PNo no);

PNo obtem_maximo(PNo no);

PNo remove_no_recursivo(PNo no, void *dado, int (*compara)(void *, void *));

Arvore remove_no(Arvore av, void *dado, int (*compara)(void *, void *));

PNo busca_no(PNo no, void *dado, int (*compara)(void *, void *));

PNo busca(Arvore av, void *dado, int (*compara)(void *, void *));

void percorre_pre_ordem(PNo no, void (*imprime)(void *));

void percorre_in_ordem(PNo no, void (*imprime)(void *));

void percorre_pos_ordem(PNo no, void (*imprime)(void *));

void percorre(Arvore av, EPercurso percurso, void (*imprime)(void *));

Contagem conta_triade_no(PNo no, int numero, Contagem *contagem, int (*soma)(void *, void *));

void conta_triade(Arvore av, int numero, int (*soma)(void *, void *));

#endif
