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
} No;
typedef struct no * PNo;

typedef struct arvore {
    PNo raiz; // raiz da arvore
} Arvore;

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

int obtem_numeros_a_retirar_da_lista_recursivo(PNo no, int *contador);

int obtem_numeros_a_retirar_da_lista(Arvore av);

#endif
