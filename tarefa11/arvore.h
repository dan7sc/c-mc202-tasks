#ifndef ARVORE_H
#define ARVORE_H

enum balanceamento {
    NEGATIVO = -1, // altura do lado esquerdo da arvore é maior que lado direito por uma unidade
    ZERO = 0,  // arvore tem lado esquerdo e direito de mesma altura
    POSITIVO = 1 // altura do lado esquerdo da arvore é maior que lado direito por uma unidade
};

typedef struct no {
    int dado; // guarda dado inserido na arvore
    struct no *esq; // ponteiro para filho esquerdo
    struct no *dir; // ponteiro para filho direito
    int altura; // altura do nó da arvore (altura da arvore com um nó é 1 e sem nó é zero )
    int frequencia; // número de vezes que o dado foi inserido na arvore
} ANo;
typedef struct no * PANo;

typedef struct arvore {
    PANo raiz; // raiz da arvore
} Arvore;

PANo cria_no(int dado);

Arvore cria_arvore();

void destroi_arvore_recursivo(PANo no);

void destroi_arvore(Arvore av);

PANo rotacao_simples_esquerda(PANo no);

PANo rotacao_simples_direita(PANo no);

PANo rotacao_dupla_esquerda(PANo no);

PANo rotacao_dupla_direita(PANo no);

PANo insere_no(PANo no, int dado);

Arvore insere_na_arvore(Arvore av, int dado);

PANo busca_no(PANo no, int dado);

PANo busca(Arvore av, int dado);

int obtem_maximo(int a, int b);

int obtem_altura(PANo no);

int obtem_balanceamento(PANo no);

int atualiza_altura(PANo no);

PANo copia_dado(PANo no_a, PANo no_b);

void percorre_pre_ordem(PANo no);

void percorre_pos_ordem(PANo no);

void percorre_in_ordem(PANo no);

void percorre_in_ordem_it(Arvore av);

#endif
