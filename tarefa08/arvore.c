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

    return raiz;
}

Arvore cria_arvore() {
    Arvore av;

    av.raiz = NULL;

    return av;
}

void destroi_no(PNo no) {
    if(no != NULL) {
        free(no);
    }
}

void destroi_arvore_recursivo(PNo no) {
    if(no != NULL) {
        destroi_arvore_recursivo(no->esq);
        destroi_arvore_recursivo(no->dir);
        destroi_no(no);
    }
}

void destroi_arvore(Arvore av) {
    destroi_arvore_recursivo(av.raiz);
}

PNo rotacao_simples_esquerda(PNo no) {
    /* printf("**  E  **\n"); */
    PNo temp = no->dir;

    no->dir = temp->esq;
    temp->esq = no;

    return temp;
}

PNo rotacao_simples_direita(PNo no) {
    /* printf("**  D  **\n"); */
    PNo temp = no->esq;

    no->esq = temp->dir;
    temp->dir = no;

    return temp;
}

PNo rotacao_dupla_esquerda(PNo no) {
    /* printf("**  EE  **\n"); */
    no->dir = rotacao_simples_direita(no->dir);
    return rotacao_simples_esquerda(no);
}

PNo rotacao_dupla_direita(PNo no) {
    /* printf("**  DD  **\n"); */
    no->esq = rotacao_simples_esquerda(no->esq);
    return rotacao_simples_direita(no);
}

PNo insere_no(PNo no, int dado) {
    PNo novo_no;
    int balanceamento = 0;

    if(no == NULL) {
        novo_no = cria_no(dado);
        no = novo_no;
        return no;
    }

    if(no->dado == dado) {
        no->quantidade++;
        return no;
    }

    if(dado < no->dado) {
        // se numero a ser inserido é menor que o numero do no atual
        // então insere a esquerda
        no->esq = insere_no(no->esq, dado);
    } else {
        // se numero a ser inserido é maior que o numero do no atual
        // então insere a direita
        no->dir = insere_no(no->dir, dado);
    }

    balanceamento = obtem_balanceamento(no);

    if(balanceamento > 1) {
        if(dado < no->esq->dado) {
            no = rotacao_simples_direita(no);
        } else {
            no = rotacao_dupla_direita(no);
        }
    } else if(balanceamento < -1) {
        if(dado > no->dir->dado) {
            no = rotacao_simples_esquerda(no);
        } else {
            no = rotacao_dupla_esquerda(no);
        }
    }

    return no;
}

Arvore insere(Arvore av, int dado) {
    av.raiz = insere_no(av.raiz, dado);

    return av;
}

PNo remove_sucessor(PNo no) {
    PNo max = no->esq;
    PNo pai = no;

    if(no->esq == NULL) {
        return NULL;
    }

    // procura maximo na subarvore direita
    while(max->dir != NULL) {
        pai = max;
        max = max->dir;
    }

    if(pai->dir == max) {
        // max é filho direito do pai entao
        // filho esquerdo de max passa a ser filho direito do pai
        pai->dir = max->esq;
    } else {
        // max é filho esquerdo do pai entao
        // filho esquerdo de max passa a ser filho esquerdo do pai
        pai->esq = max->esq;
    }

    troca_dados(no, max);

    // retorna o sucessor
    return max;
}

PNo remove_no_recursivo(PNo no, int dado) {
    PNo temp;

    if(no == NULL) {
        return NULL;
    }

    if(dado < no->dado) {
        // procura no a ser removido no lado esquerdo
        no->esq = remove_no_recursivo(no->esq, dado);
    } else if(dado > no->dado) {
        // procura no a ser removido no lado direito
        no->dir = remove_no_recursivo(no->dir, dado);
    } else {
        if(no->esq == NULL && no->dir == NULL) {
            // no nao tem filhos entao remove
            temp = no;
            destroi_no(temp);
            no = NULL;
            return no;
        } else if(no->esq == NULL && no->dir != NULL) {
            // no tem filho direito entao retorna o no direito
            temp = no;
            no = no->dir;
            destroi_no(temp);
            return no;
        } else if(no->dir == NULL && no->esq != NULL) {
            // no tem filho esquerdo entao retorna o no esquerdo
            temp = no;
            no = no->esq;
            destroi_no(temp);
            return no;
        } else {
            // no tem filho esquerdo e direito entao remove o sucessor
            temp = remove_sucessor(no);
            destroi_no(temp);
            return no;
        }
    }

    return no;
}

Arvore remove_no(Arvore av, int dado) {
    av.raiz = remove_no_recursivo(av.raiz, dado);

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

void percorre_pre_ordem(PNo no) {
    if(no != NULL) {
        printf("%d-%d-%d, ", no->dado, obtem_altura(no), no->quantidade);
        percorre_pre_ordem(no->esq);
        percorre_pre_ordem(no->dir);
    }
}

void percorre_in_ordem(PNo no) {
    if(no != NULL) {
        percorre_in_ordem(no->esq);
        printf("%d-%d-%d, ", no->dado, obtem_altura(no), no->quantidade);
        percorre_in_ordem(no->dir);
    }
}

void percorre_pos_ordem(PNo no) {
    if(no != NULL) {
        percorre_pos_ordem(no->esq);
        percorre_pos_ordem(no->dir);
        printf("%d-%d-%d, ", no->dado, obtem_altura(no), no->quantidade);
    }
}

// percorre arvore segundo o tipo de percurso dado:
// 0 -> pre-ordem, 1 -> in-ordem, 2 -> pos-ordem
void percorre(Arvore av, EPercurso percurso) {
    switch(percurso) {
    case 0:
        percorre_pre_ordem(av.raiz);
        break;
    case 1:
        percorre_in_ordem(av.raiz);
        break;
    case 2:
        percorre_pos_ordem(av.raiz);
        break;
    default:
        break;
    }
    printf("\n");
}

int obtem_maximo(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

int obtem_altura(PNo no) {
    if (no != NULL)
        return 1 + obtem_maximo(obtem_altura(no->esq), obtem_altura(no->dir));
    else
        return 0;
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

void troca_dados(PNo no_a, PNo no_b) {
    PNo aux = malloc(sizeof(No));

    aux->dado = no_a->dado;
    no_a->dado = no_b->dado;
    no_b->dado = aux->dado;

    free(aux);
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
