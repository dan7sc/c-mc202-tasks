#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "pilha.h"

PANo cria_no(int dado) {
    PANo raiz = malloc(sizeof(ANo));

    raiz->dado = dado;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->frequencia = 1;
    raiz->altura = 1;

    return raiz;
}

Arvore cria_arvore() {
    Arvore av;

    av.raiz = NULL;

    return av;
}

void destroi_arvore_recursivo(PANo no) {
    if(no != NULL) {
        destroi_arvore_recursivo(no->esq);
        destroi_arvore_recursivo(no->dir);
        free(no);
    }
}

void destroi_arvore(Arvore av) {
    destroi_arvore_recursivo(av.raiz);
}

/* na rotação simples a esquerda cada nó move uma posição
// a esquerda da posicao em que estava anteriormente
// exemplo:
//         no                 b
//       /    \             /   \
//      a      b   ==>>    no     y
//           /   \       /    \
//          x     y     a      x
*/
PANo rotacao_simples_esquerda(PANo no) {
    PANo temp = no->dir; // b na representação acima

    // rotação esquerda
    no->dir = temp->esq;
    temp->esq = no;

    // atualiza a altura dos nós que foram rotacionados
    // nó é atualizado primeiro pois o cálculo da altura de temp depende dele
    no->altura = atualiza_altura(no);
    temp->altura = atualiza_altura(temp);

    return temp;
}

/* na rotação simples a direita cada nó move uma posição
// a direita da posicao em que estava anteriormente
// exemplo:
//         no               a
//       /    \           /   \
//      a      b   ==>>  x     no
//    /   \                  /    \
//   x     y                y      b
*/
PANo rotacao_simples_direita(PANo no) {
    PANo temp = no->esq;  // a na representação acima

    // rotação para direita
    no->esq = temp->dir;
    temp->dir = no;

    // atualiza a altura dos nós que foram rotacionados
    // nó é atualizado primeiro pois o cálculo da altura de temp depende dele
    no->altura = atualiza_altura(no);
    temp->altura = atualiza_altura(temp);

    return temp;
}

/* na rotação dupla a esquerda é realizada uma rotação simples
// a direita e depois uma rotação simples a esquerda
// exemplo:
//         no                 no                       c
//       /    \             /    \                   /    \
//      a      b    ==>>   a      c       ==>>      no      b
//           /   \              /   \              /  \    /  \
//          c     z            x     b            a    x  y    z
//        /   \                    /   \
//       x     y                  y     z
*/
PANo rotacao_dupla_esquerda(PANo no) {
    no->dir = rotacao_simples_direita(no->dir);
    no = rotacao_simples_esquerda(no);

    return no;
}

/* na rotação dupla a direita é realizada uma rotação simples
// a esquerda e depois uma rotação simples a direita
// exemplo:
//         no                     no                   c
//       /    \                 /    \               /    \
//      a      b   ==>>        c      b    ==>>     a      no
//    /   \                  /   \                /  \    /   \
//   x     c                a     z              x    y   z    b
//       /   \            /   \
//      y     z          x     y
*/
PANo rotacao_dupla_direita(PANo no) {
    no->esq = rotacao_simples_esquerda(no->esq);
    no = rotacao_simples_direita(no);

    return no;
}

// cria novo nó caso dado não exista na árvore
// ou incrementa a frequencia do nó que possui o dado
// a inserir caso o este já esteja na árvore
// retornando a raiz
PANo insere_no(PANo no, int dado) {
    PANo novo_no;

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
        // incrementa a frequencia pois o dado ja está na árvore
        no->frequencia++;
        return no;
    }

    // verifica o balanceamento da arvore e
    // realiza rotações caso necessario
    if (obtem_balanceamento(no) > POSITIVO) { // desbalanceamento à direita
        if (obtem_balanceamento(no->dir) < ZERO) { // altura do lado esquerdo do filho direito é maior
            no = rotacao_dupla_esquerda(no);
        } else {
            no = rotacao_simples_esquerda(no);
        }
    } else if (obtem_balanceamento(no) < NEGATIVO) { // desbalanceamento à esquerda
        if (obtem_balanceamento(no->esq) > ZERO) { // altura do lado direito do filho esquerdo é maior
            no = rotacao_dupla_direita(no);
        } else {
            no = rotacao_simples_direita(no);
        }
    }

    // atualiza a altura do nó no
    no->altura = atualiza_altura(no);

    return no;
}

Arvore insere_na_arvore(Arvore av, int dado) {
    av.raiz = insere_no(av.raiz, dado);

    return av;
}

// busca por nó com valor dado
PANo busca_no(PANo no, int dado) {
    PANo temp;

    // não há nó com valor dado
    if(no == NULL) {
        temp = cria_no(0);
        temp->frequencia = 0;
        temp->altura = 0;
        return temp;
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

PANo busca(Arvore av, int dado) {
    PANo no = NULL;

    no = busca_no(av.raiz, dado);

    return no;
}

// obtem máximo entre dois números
// retornando o maior
int obtem_maximo(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

// obtem e retorna altura do nó
int obtem_altura(PANo no) {
    if(no == NULL) {
        return 0;
    }
    return no->altura;
}

// obtem e retorna balanceamento do nó
int obtem_balanceamento(PANo no) {
    if(no == NULL) {
        return 0;
    }

    return (obtem_altura(no->dir) - obtem_altura(no->esq));
}

// obtem nova altura do nó e retorna a nova altura
int atualiza_altura(PANo no) {
    return (1 + obtem_maximo(obtem_altura(no->esq), obtem_altura(no->dir)));
}

// copia dados do no_b para o no_a
PANo copia_dado(PANo no_a, PANo no_b) {

    no_a->dado = no_b->dado;
    no_a->frequencia = no_b->frequencia;
    no_a->altura = no_b->altura;

    return no_a;
}

void percorre_pre_ordem(PANo no) {
    if(no != NULL) {
        printf("%d ", no->dado);
        percorre_in_ordem(no->esq);
        percorre_in_ordem(no->dir);
    }
}

void percorre_pos_ordem(PANo no) {
    if(no != NULL) {
        percorre_in_ordem(no->esq);
        percorre_in_ordem(no->dir);
        printf("%d ", no->dado);
    }
}

void percorre_in_ordem(PANo no) {
    if(no != NULL) {
        percorre_in_ordem(no->esq);
        printf("%d ", no->dado);
        percorre_in_ordem(no->dir);
    }
}

void percorre_in_ordem_it(Arvore av) {
    PPilha pav = cria_pilha();
    PANo atual = av.raiz;

    while(!pilha_vazia(pav) || atual != NULL) {
        if(atual != NULL) {
            empilha(pav, atual);
            atual = atual->esq;
        } else {
            atual = desempilha(pav);
            printf("%d ", atual->dado);
            atual = atual->dir;
        }
    }
}
