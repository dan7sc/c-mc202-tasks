#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

PNo cria_no(int dado) {
    PNo raiz = malloc(sizeof(No));

    raiz->dado = dado;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->quantidade = 1;
    raiz->altura = 1;

    return raiz;
}

Arvore cria_arvore() {
    Arvore av;

    av.raiz = NULL;

    return av;
}

void destroi_arvore_recursivo(PNo no) {
    if(no != NULL) {
        destroi_arvore_recursivo(no->esq);
        destroi_arvore_recursivo(no->dir);
        free(no);
    }
}

void destroi_arvore(Arvore av) {
    destroi_arvore_recursivo(av.raiz);
}

PNo rotacao_simples_esquerda(PNo no) {
    PNo temp = no->dir;

    no->dir = temp->esq;
    temp->esq = no;

    no->altura = 1 + obtem_maximo(obtem_altura(no->esq), obtem_altura(no->dir));
    temp->altura = 1 + obtem_maximo(obtem_altura(temp->esq), obtem_altura(temp->dir));

    return temp;
}

PNo rotacao_simples_direita(PNo no) {
    PNo temp = no->esq;

    no->esq = temp->dir;
    temp->dir = no;

    no->altura = 1 + obtem_maximo(obtem_altura(no->esq), obtem_altura(no->dir));
    temp->altura = 1 + obtem_maximo(obtem_altura(temp->esq), obtem_altura(temp->dir));

    return temp;
}

PNo rotacao_dupla_esquerda(PNo no) {
    no->dir = rotacao_simples_direita(no->dir);
    no = rotacao_simples_esquerda(no);

    return no;
}

PNo rotacao_dupla_direita(PNo no) {
    no->esq = rotacao_simples_esquerda(no->esq);
    no = rotacao_simples_direita(no);

    return no;
}

PNo insere_no(PNo no, int dado) {
    PNo novo_no;

    if(no == NULL) {
        novo_no = cria_no(dado);
        no = novo_no;
        return no;
    }

    if(dado < no->dado) {
        // se numero a ser inserido é menor que o numero do no atual
        // então insere a esquerda
        no->esq = insere_no(no->esq, dado);
    } else if(dado > no->dado) {
        // se numero a ser inserido é maior que o numero do no atual
        // então insere a direita
        no->dir = insere_no(no->dir, dado);
    } else {
        no->quantidade++;
        return no;
    }

    no->altura = 1 + obtem_maximo(obtem_altura(no->esq), obtem_altura(no->dir));

    if (obtem_balanceamento(no) < -1) {
        if (obtem_balanceamento(no->dir) > 0) {
            no = rotacao_dupla_esquerda(no);
        } else {
            no = rotacao_simples_esquerda(no);
        }
    } else if (obtem_balanceamento(no) > 1) {
        if (obtem_balanceamento(no->esq) < 0) {
            no = rotacao_dupla_direita(no);
        } else {
            no = rotacao_simples_direita(no);
        }
    }

    return no;
}

Arvore insere(Arvore av, int dado) {
    av.raiz = insere_no(av.raiz, dado);

    return av;
}

PNo busca_no(PNo no, int dado) {
    PNo temp;

    if(no == NULL) {
        return no;
    }

    if(dado < no->dado) {
        // procura dado no lado esquerdo se é menor que dado do no atual
        return busca_no(no->esq, dado);
    } else if(dado > no->dado) {
        // procura dado no lado direito se é maior que dado do no atual
        return busca_no(no->dir, dado);
    } else {
        // faz uma copia do no encontrado e retorna a copia
        temp = cria_no(0);
        temp = copia_dado(temp, no);
        return temp;
    }
}

PNo busca(Arvore av, int dado) {
    PNo no = NULL;

    no = busca_no(av.raiz, dado);

    return no;
}

int obtem_maximo(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

int obtem_altura(PNo no) {
    if(no == NULL) {
        return 0;
    }
    return no->altura;
}

int obtem_balanceamento(PNo no) {
    if(no == NULL) {
        return 0;
    }

    return (obtem_altura(no->esq) - obtem_altura(no->dir));
}

// le numero inteiro
int le_int(int *num) {
    return scanf("%d", num);
}

// copia dados do no_b para o no_a
PNo copia_dado(PNo no_a, PNo no_b) {

    no_a->dado = no_b->dado;
    no_a->quantidade = no_b->quantidade;

    return no_a;
}

int obtem_lista_legal_recursivo(PNo no, int *contador) {
    int qtde = 0;

    if(no != NULL) {
        obtem_lista_legal_recursivo(no->esq, contador);
        if(no->dado != no->quantidade) {
            if(no->quantidade < no->dado) {
                *contador += no->quantidade;
            } else {
                qtde = no->quantidade;
                while(no->dado != qtde) {
                    *contador += 1;
                    qtde--;
                }
            }
        }
        obtem_lista_legal_recursivo(no->dir, contador);
    }

    return *contador;
}

int obtem_lista_legal(Arvore av) {
    int removidos = 0;
    int *contador = malloc(sizeof(int));
    *contador = 0;

    *contador = obtem_lista_legal_recursivo(av.raiz, contador);
    removidos = *contador;
    free(contador);

    return removidos;
}
