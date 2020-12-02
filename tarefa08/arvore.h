#ifndef ARVORE_H
#define ARVORE_H

typedef struct no {
    int dado;
    struct no *esq;
    struct no *dir;
    int altura;
    int frequencia;
} No;
typedef struct no * PNo;

typedef struct arvore {
    PNo raiz;
} Arvore;
typedef struct arvore * PArvore;

PNo cria_no(int dado);

Arvore cria_arvore();

void destroi_arvore_recursivo(PNo no);

void destroi_arvore(Arvore av);

PNo rotacao_simples_esquerda(PNo no);

PNo rotacao_simples_direita(PNo no);

PNo rotacao_dupla_esquerda(PNo no);

PNo rotacao_dupla_direita(PNo no);

PNo insere_no(PNo no, int dado);

Arvore insere(Arvore av, int dado);

PNo busca_no(PNo no, int dado);

PNo busca(Arvore av, int dado);

int obtem_maximo(int a, int b);

int obtem_altura(PNo no);

int obtem_balanceamento(PNo no);

int atualiza_altura(PNo no);

int le_int(int *num);

PNo copia_dado(PNo no_a, PNo no_b);

int obtem_numeros_removidos_lista_legal_recursivo(PNo no, int *contador);

int obtem_numeros_removidos_lista_legal(Arvore av);

#endif
