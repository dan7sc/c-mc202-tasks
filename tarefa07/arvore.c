#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

PNo cria_no(void *dado, PNo esq, PNo dir) {
    PNo raiz = malloc(sizeof(No));

    raiz->dado = dado;
    raiz->esq = esq;
    raiz->dir = dir;

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
        novo_no = cria_no(dado, NULL, NULL);
        no = novo_no;
        return no;
    }

    if((*compara)(dado, no->dado) == 0) {
        no->esq = insere_no(no->esq, dado, compara);
    } else {
        no->dir = insere_no(no->dir, dado, compara);
    }

    return no;
}

Arvore insere(Arvore av, void *dado, int (*compara)(void *, void *)) {
    av.raiz = insere_no(av.raiz, dado, compara);

    return av;
}

PNo busca_no(PNo no, void *dado, int (*compara)(void *, void *)) {
    if(no == NULL || (*compara)(dado, no->dado) == 0) {
        return no;
    }

    if((*compara)(dado, no->dado) == 0) {
        return busca_no(no->esq, dado, compara);
    } else {
        return busca_no(no->dir, dado, compara);
    }
}

PNo busca(Arvore av, void *dado, int (*compara)(void *, void *)) {
    PNo no;

    if(av.raiz == NULL || (*compara)(dado, av.raiz->dado) == 0) {
        return av.raiz->dado;
    } else {
        no = busca_no(av.raiz, dado, compara);
        if(no == NULL) {
            return NULL;
        }
        return no->dado;
    }
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
