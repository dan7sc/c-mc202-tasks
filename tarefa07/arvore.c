#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

void troca_dados(PNo no_a, PNo no_b) {
    PNo aux = malloc(sizeof(No));

    aux->dado = no_a->dado;
    no_a->dado = no_b->dado;
    no_b->dado = aux->dado;

    free(aux);
}

PNo copia_dado(PNo no, PNo no_a_copiar) {
    int tamanho = sizeof(Cartao);

    no->dado = malloc(tamanho);
    memcpy(no->dado, no_a_copiar->dado, tamanho);

    return no;
}

void *copia_cartao(void *cartao_a, void *cartao_b) {
    int tamanho = sizeof(Cartao);

    cartao_a = malloc(tamanho);
    ((Cartao *)cartao_a)->texto = malloc(sizeof(char *));

    ((Cartao *)cartao_a)->numero = ((Cartao *)cartao_b)->numero;
    strcpy(((Cartao *)cartao_a)->texto, ((Cartao *)cartao_b)->texto);

    /* memcpy(cartao_a, cartao_b, tamanho); */

    return cartao_a;
}

int obtem_autoridade(void *dado) {
    Cartao c = *(Cartao *)dado;

    return c.numero;
}

PNo cria_no(void *dado) {
    PNo raiz = malloc(sizeof(No));

    raiz->dado = dado;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->pai = NULL;

    return raiz;
}

Arvore cria_arvore() {
    Arvore av;

    av.raiz = NULL;

    return av;
}

void destroi_no(PNo no) {
    if(no != NULL) {
        free(no->dado);
        free(no);
    }
}

void destroi_arvore_recursivo(PNo no, void (*destroi)(void *)) {
    if(no != NULL) {
        destroi_arvore_recursivo(no->esq, destroi);
        destroi_arvore_recursivo(no->dir, destroi);
        destroi(no->dado);
        destroi_no(no);
    }
}

void destroi_arvore(Arvore av, void (*destroi)(void *)) {
    destroi_arvore_recursivo(av.raiz, destroi);
}

PNo insere_no(PNo no, void *dado, int (*compara)(void *, void *)) {
    PNo novo_no;

    if(no == NULL) {
        novo_no = cria_no(dado);
        no = novo_no;
        return no;
    }

    if((*compara)(dado, no->dado) < 0) {
        novo_no = insere_no(no->esq, dado, compara);
        no->esq = novo_no;
        /* novo_no->pai = no; */
    } else {
        novo_no = insere_no(no->dir, dado, compara);
        no->dir = novo_no;
        /* novo_no->pai = no; */
    }

    return no;
}

Arvore insere(Arvore av, void *dado, int (*compara)(void *, void *)) {
    av.raiz = insere_no(av.raiz, dado, compara);

    return av;
}

PNo remove_sucessor(PNo no) {
    PNo max = no->esq;
    PNo pai = no;

    if(no->esq == NULL) {
        return NULL;
    }

    // procura maximo na subarvore esquerda
    while(max->dir != NULL) {
        pai = max;
        max = max->dir;
    }

    if(pai->dir == max) {
        pai->dir = max->esq;
    } else {
        pai->esq = max->esq;
    }

    troca_dados(no, max);

    return max;
}

PNo obtem_minimo(PNo no) {
    if(no == NULL || no->esq == NULL) {
        return no;
    }
    return obtem_minimo(no->esq);
}

PNo obtem_maximo(PNo no) {
    if(no == NULL || no->dir == NULL) {
        return no;
    }
    return obtem_maximo(no->dir);
}

PNo obtem_sucessor_esq(PNo no) {
    PNo sucessor = no->esq;

    if(sucessor == NULL) {
        return NULL;
    }

    return obtem_maximo(sucessor);
}

PNo obtem_sucessor_dir(PNo no) {
    PNo sucessor = no->dir;

    if(sucessor == NULL) {
        return NULL;
    }

    return obtem_minimo(sucessor);
}

PNo remove_no_recursivo(PNo no, void *dado, int (*compara)(void *, void *)) {
    PNo temp;

    if(no == NULL) {
        return NULL;
    }

    if((*compara)(dado, no->dado) == -1) {
        no->esq = remove_no_recursivo(no->esq, dado, compara);
    } else if((*compara)(dado, no->dado) == 1) {
        no->dir = remove_no_recursivo(no->dir, dado, compara);
    } else {
        if(no->esq == NULL && no->dir == NULL) {
            temp = no;
            destroi_no(temp);
            no = NULL;
            return no;
        } else if(no->esq == NULL && no->dir != NULL) {
            temp = no;
            no = no->dir;
            destroi_no(temp);
            return no;
        } else if(no->dir == NULL && no->esq != NULL) {
            temp = no;
            no = no->esq;
            destroi_no(temp);
            return no;
        } else {
            temp = remove_sucessor(no);
            destroi_no(temp);
            return no;
        }
    }

    return no;
}

Arvore remove_no(Arvore av, void *dado, int (*compara)(void *, void *)) {
    av.raiz = remove_no_recursivo(av.raiz, dado, compara);

    return av;
}

PNo busca_no(PNo no, void *dado, int (*compara)(void *, void *)) {
    PNo temp;

    if(no == NULL) {
        return no;
    }

    if((*compara)(dado, no->dado) == -1) {
        return busca_no(no->esq, dado, compara);
    } else if((*compara)(dado, no->dado) == 1) {
        return busca_no(no->dir, dado, compara);
    } else {
        temp = cria_no(NULL);
        temp = copia_dado(temp, no);
        return temp;
    }
}

PNo busca(Arvore av, void *dado, int (*compara)(void *, void *)) {
    PNo no;

    no = busca_no(av.raiz, dado, compara);

    return no;
}

void percorre_pre_ordem(PNo no, void (*imprime)(void *)) {
    if(no != NULL) {
        (*imprime)(no->dado);
        percorre_pre_ordem(no->esq, imprime);
        percorre_pre_ordem(no->dir, imprime);
    }
}

void percorre_in_ordem(PNo no, void (*imprime)(void *)) {
    if(no != NULL) {
        percorre_in_ordem(no->esq, imprime);
        (*imprime)(no->dado);
        percorre_in_ordem(no->dir, imprime);
    }
}

void percorre_pos_ordem(PNo no, void (*imprime)(void *)) {
    if(no != NULL) {
        percorre_pos_ordem(no->esq, imprime);
        percorre_pos_ordem(no->dir, imprime);
        (*imprime)(no->dado);
    }
}

void percorre(Arvore av, EPercurso percurso, void (*imprime)(void *)) {
    switch(percurso) {
    case 0:
        percorre_pre_ordem(av.raiz, imprime);
        break;
    case 1:
        percorre_in_ordem(av.raiz, imprime);
        break;
    case 2:
        percorre_pos_ordem(av.raiz, imprime);
        break;
    default:
        break;
    }
    printf("\n");
}

void busca_triade_recursivo(PNo no, int numero, Triade *t, Contagem *contagem, int (*soma)(void *, void *), int (*compara)(void *, void *)) {
    if(no != NULL) {
        busca_triade_recursivo(no->esq, numero, t, contagem, soma, compara);
        busca_triade_recursivo(no->dir, numero, t, contagem, soma, compara);
        if(contagem->contador < 3 && (*soma)(contagem, no->dado) <= numero) {
            if(contagem->contador == 0) {
                t->num_cartao1 = obtem_autoridade(no->dado);
            } else if(contagem->contador == 1) {
                t->num_cartao2 = obtem_autoridade(no->dado);
            } else {
                t->num_cartao3 = obtem_autoridade(no->dado);
            }
            contagem->soma = (*soma)(contagem, no->dado);
            contagem->contador++;
        }
    }
}

Triade *busca_triade(Arvore av, Triade *t, int numero, int (*soma)(void *, void *), int (*compara)(void *, void *)) {
    Contagem *contagem;

    contagem = malloc(sizeof(Contagem));
    contagem->soma = 0;
    contagem->contador = 0;

    busca_triade_recursivo(av.raiz, numero, t, contagem, soma, compara);

    free(contagem);

    return t;
}

Cartao *cria_cartao_recursivo(PNo no, Cartao *cartao, Cartao *(*concatena)(Cartao *cartao, void *dado)) {
    if(no != NULL) {
        cria_cartao_recursivo(no->esq, cartao, concatena);
        cartao = (*concatena)(cartao, no->dado);
        cria_cartao_recursivo(no->dir, cartao, concatena);
    }

    return cartao;
}

Cartao *cria_cartao(Arvore av, Cartao *cartao, Cartao *(*concatena)(Cartao *cartao, void *dado)) {

    cartao = cria_cartao_recursivo(av.raiz, cartao, concatena);

    return cartao;
}
