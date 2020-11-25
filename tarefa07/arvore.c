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

// copia dados do no_b para o no_a
PNo copia_dado(PNo no_a, PNo no_b) {
    int tamanho = sizeof(Cartao);

    no_a->dado = malloc(tamanho);
    memcpy(no_a->dado, no_b->dado, tamanho);

    return no_a;
}

// copia dados do cartao_b para o cartao_a
void *copia_cartao(void *cartao_a, void *cartao_b) {
    int tamanho = sizeof(Cartao);

    cartao_a = malloc(tamanho);
    ((Cartao *)cartao_a)->texto = malloc(sizeof(char *));

    ((Cartao *)cartao_a)->numero = ((Cartao *)cartao_b)->numero;
    strcpy(((Cartao *)cartao_a)->texto, ((Cartao *)cartao_b)->texto);

    return cartao_a;
}

// obtem numero do cartao
int obtem_numero(void *dado) {
    Cartao c = *(Cartao *)dado;

    return c.numero;
}

PNo cria_no(void *dado) {
    PNo raiz = malloc(sizeof(No));

    raiz->dado = dado;
    raiz->esq = NULL;
    raiz->dir = NULL;

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
        // se numero a ser inserido é menor que o numero do no atual
        // então insere a esquerda
        novo_no = insere_no(no->esq, dado, compara);
        no->esq = novo_no;
    } else {
        // se numero a ser inserido é maior que o numero do no atual
        // então insere a direita
        novo_no = insere_no(no->dir, dado, compara);
        no->dir = novo_no;
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

PNo remove_no_recursivo(PNo no, void *dado, int (*compara)(void *, void *)) {
    PNo temp;

    if(no == NULL) {
        return NULL;
    }

    if((*compara)(dado, no->dado) == -1) {
        // procura no a ser removido no lado esquerdo
        no->esq = remove_no_recursivo(no->esq, dado, compara);
    } else if((*compara)(dado, no->dado) == 1) {
        // procura no a ser removido no lado direito
        no->dir = remove_no_recursivo(no->dir, dado, compara);
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
        // procura dado no lado esquerdo se é menor que dado do no atual
        return busca_no(no->esq, dado, compara);
    } else if((*compara)(dado, no->dado) == 1) {
        // procura dado no lado direito se é maior que dado do no atual
        return busca_no(no->dir, dado, compara);
    } else {
        // faz uma copia do no encontrado e retorna a copia
        temp = cria_no(NULL);
        temp = copia_dado(temp, no);
        return temp;
    }
}

PNo busca(Arvore av, void *dado, int (*compara)(void *, void *)) {
    PNo no = NULL;

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

// percorre arvore segundo o tipo de percurso dado:
// 0 -> pre-ordem, 1 -> in-ordem, 2 -> pos-ordem
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

void soma_triade_recursivo(Arvore av, PNo no, PNo no_b,
                           int numero, Triade *t,
                           int (*soma)(void *, void *),
                           int (*compara)(void *, void *)) {
    int n = 0; // soma do numero de dois cartoes
    int sn = 0; // diferenca entre o numero que se quer buscar e a soma do numero de dois cartoes
    PNo r = NULL; // no que guarda o retorno da funcao busca

    if(no_b != NULL && compara(no->dado, no_b->dado) != 0) {
        // soma um no no com no no_b do lado esquerdo
        soma_triade_recursivo(av, no, no_b->esq, numero, t, soma, compara);
        n = (*soma)(no->dado, no_b->dado);
        sn = numero - n;
        r = busca(av, &sn, compara);
        // se soma do numero dos tres nos (no, no_b e r) é igual a numero da autoridade (numero) então armazena a triade em t
        if(r != NULL && compara(no->dado, r->dado) != 0 && compara(no_b->dado, r->dado) != 0  && sn + n == numero) {
            t->num_cartao1 = obtem_numero(no->dado);
            t->num_cartao2 = obtem_numero(no_b->dado);
            t->num_cartao3 = obtem_numero(r->dado);
        }
        destroi_no(r);
        // soma um no no com no no_b do lado direito
        soma_triade_recursivo(av, no, no_b->dir, numero, t, soma, compara);
    }
}

void busca_triade_recursivo(Arvore av, PNo no, PNo no_b,
                            int numero, Triade *t,
                            int (*soma)(void *, void *),
                            int (*compara)(void *, void *)) {
    if(no != NULL) {
        // para um no no_b fixo percorre a arvore do lado esquerdo
        busca_triade_recursivo(av, no->esq, no_b, numero, t, soma, compara);
        soma_triade_recursivo(av, no, no_b, numero, t, soma, compara);
        // para um no no_b fixo percorre a arvore do lado direito
        busca_triade_recursivo(av, no->dir, no_b, numero, t, soma, compara);
    }
}

Triade *busca_triade(Arvore av, Triade *t, int numero,
                     int (*soma)(void *, void *),
                     int (*compara)(void *, void *)) {
    busca_triade_recursivo(av, av.raiz, av.raiz, numero, t, soma, compara);

    return t;
}

Cartao *cria_cartao_recursivo(PNo no, Cartao *cartao,
                              Cartao *(*concatena)(Cartao *cartao, void *dado)) {
    if(no != NULL) {
        // concatena texto de cada no da arvore do menor para o maior numero do no
        cria_cartao_recursivo(no->esq, cartao, concatena);
        cartao = (*concatena)(cartao, no->dado);
        cria_cartao_recursivo(no->dir, cartao, concatena);
    }

    return cartao;
}

Cartao *cria_cartao(Arvore av, Cartao *cartao,
                    Cartao *(*concatena)(Cartao *cartao, void *dado)) {

    cartao = cria_cartao_recursivo(av.raiz, cartao, concatena);

    return cartao;
}
