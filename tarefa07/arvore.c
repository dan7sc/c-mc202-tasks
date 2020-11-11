#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

PNo cria_no(void *dado, PNo esq, PNo dir, PNo pai) {
    PNo raiz = malloc(sizeof(No));

    raiz->dado = dado;
    raiz->esq = esq;
    raiz->dir = dir;
    raiz->pai = pai;

    return raiz;
}

Arvore cria_arvore() {
    Arvore av;

    av.raiz = NULL;

    return av;
}

void destroi_no(PNo no) {
    if(no != NULL) {
        destroi_no(no->esq);
        destroi_no(no->dir);
        free(no->dado);
        free(no);
    }
}

void destroi_arvore(Arvore av) {
    destroi_no(av.raiz);
}

PNo insere_no(PNo no, void *dado, int (*compara)(void *, void *)) {
    PNo novo_no;

    if(no == NULL) {
        novo_no = cria_no(dado, NULL, NULL, NULL);
        no = novo_no;
        return no;
    }

    if((*compara)(dado, no->dado) == -1) {
        novo_no = insere_no(no->esq, dado, compara);
        no->esq = novo_no;
        novo_no->pai = no;
    } else if((*compara)(dado, no->dado) == 1) {
        novo_no = insere_no(no->dir, dado, compara);
        no->dir = novo_no;
        novo_no->pai = no;
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
        pai->dir = max->dir;
    } else {
        pai->esq = max->dir;
    }

    no->dado = max->dado;
    return max;
}

PNo remove_no_recursivo(PNo no, void *dado, int (*compara)(void *, void *)) {
    if(no == NULL) {
        return NULL;
    }

    if((*compara)(dado, no->dado) == -1) {
        no->esq = remove_no_recursivo(no->esq, dado, compara);
        return no;
    } else if((*compara)(dado, no->dado) == 1) {
        no->dir = remove_no_recursivo(no->dir, dado, compara);
        return no;
    } else {
        if(no->esq == NULL && no->dir != NULL) {
            no = no->dir;
            return no;
        } else if(no->dir == NULL && no->esq != NULL) {
            no = no->esq;
            return no;
        } else {
            return remove_sucessor(no);
        }
    }
}

PNo remove_no(Arvore av, void *dado, int (*compara)(void *, void *)) {
    PNo no;

    no = remove_no_recursivo(av.raiz, dado, compara);

    return no;
}

PNo busca_no(PNo no, void *dado, int (*compara)(void *, void *)) {
    if(no == NULL) {
        return no;
    }

    if((*compara)(dado, no->dado) == -1) {
        return busca_no(no->esq, dado, compara);
    } else if((*compara)(dado, no->dado) == 1) {
        return busca_no(no->dir, dado, compara);
    } else {
        return no;
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

Contagem conta_triade_no(PNo no, int autoridade, Contagem *contagem, int (*soma)(void *, void *)) {
    if(no != NULL) {
        conta_triade_no(no->esq, autoridade, contagem, soma);
        conta_triade_no(no->dir, autoridade, contagem, soma);
        if(contagem->contador < 3 && (
               (*soma)(contagem, no->dado) == autoridade || (*soma)(contagem, no->dado) < autoridade)
            ) {
            contagem->soma = (*soma)(contagem, no->dado);
            contagem->contador++;
        }
    }

    return *contagem;
}

void conta_triade(Arvore av, int autoridade, int (*soma)(void *, void *)) {
    Contagem *contagem;

    contagem = malloc(sizeof(Contagem));
    contagem->soma = 0;
    contagem->contador = 0;

    *contagem = conta_triade_no(av.raiz, autoridade, contagem, soma);

    free(contagem);
}
