#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

PNo cria_no(int dado) {
    PNo raiz = malloc(sizeof(No));

    raiz->dado = dado;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->frequencia = 1;
    raiz->altura = 0;

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

/* na rotação simples a esquerda cada nó move uma posição
// a esquerda da posicao em que estava anteriormente
// exemplo:
//         no                 b
//       /    \             /   \
//      a      b   ==>>    no     y
//           /   \       /    \
//          x     y     a      x
*/
PNo rotacao_simples_esquerda(PNo no) {
    PNo temp = no->dir; // b na representação acima

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
PNo rotacao_simples_direita(PNo no) {
    PNo temp = no->esq;  // a na representação acima

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
PNo rotacao_dupla_esquerda(PNo no) {
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
PNo rotacao_dupla_direita(PNo no) {
    no->esq = rotacao_simples_esquerda(no->esq);
    no = rotacao_simples_direita(no);

    return no;
}

// cria novo nó caso dado não exista na árvore
// ou incrementa a frequencia do nó que possui o dado
// a inserir caso o este já esteja na árvore
// retornando a raiz
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
        // incrementa a frequencia pois o dado ja está na árvore
        no->frequencia++;
        return no;
    }

    // verifica o balanceamento da arvore e
    // realiza rotações caso necessario
    if (obtem_balanceamento(no) > 1) {
        if (obtem_balanceamento(no->dir) < 0) {
            no = rotacao_dupla_esquerda(no);
        } else {
            no = rotacao_simples_esquerda(no);
        }
    } else if (obtem_balanceamento(no) < -1) {
        if (obtem_balanceamento(no->esq) > 0) {
            no = rotacao_dupla_direita(no);
        } else {
            no = rotacao_simples_direita(no);
        }
    }

    // atualiza a altura do nó no
    no->altura = atualiza_altura(no);

    return no;
}

Arvore insere(Arvore av, int dado) {
    av.raiz = insere_no(av.raiz, dado);

    return av;
}

// busca por nó com valor dado
PNo busca_no(PNo no, int dado) {
    PNo temp;

    // não há nó com valor dado
    if(no == NULL) {
        temp = cria_no(0);
        temp->frequencia = 0;
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

PNo busca(Arvore av, int dado) {
    PNo no = NULL;

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
int obtem_altura(PNo no) {
    if(no == NULL) {
        return 0;
    }
    return no->altura;
}

// obtem e retorna balanceamento do nó
int obtem_balanceamento(PNo no) {
    if(no == NULL) {
        return 0;
    }

    return (obtem_altura(no->dir) - obtem_altura(no->esq));
}

// obtem nova altura do nó e retorna a nova altura
int atualiza_altura(PNo no) {
    return (1 + obtem_maximo(obtem_altura(no->esq), obtem_altura(no->dir)));
}

// le numero inteiro
int le_int(int *num) {
    return scanf("%d", num);
}

// copia dados do no_b para o no_a
PNo copia_dado(PNo no_a, PNo no_b) {

    no_a->dado = no_b->dado;
    no_a->frequencia = no_b->frequencia;
    no_a->altura = no_b->altura;

    return no_a;
}

// obtem a quantidade de numeros que precisam ser removidos
// para tornar a lista legal  e retorna a quantidade de números removidos
int obtem_numeros_removidos_lista_legal_recursivo(PNo no, int *num_removidos) {
    if(no != NULL) {
        obtem_numeros_removidos_lista_legal_recursivo(no->esq, num_removidos);
        // verifica se a frequencia do numero é menor
        // que o proprio numero na lista/arvore ...
        if(no->frequencia < no->dado) {
            // ... caso seja o numero tem que ser removido da lista legal
            // o numero de vezes que ele aparece na lista/arvore
            *num_removidos += no->frequencia;
        // se a frequencia do número é maior que o número ...
        } else if(no->frequencia > no->dado) {
            // ... o numero em excesso tem que ser removido da lista legal
            // numero em excesso: frequecia do numero - numero
            *num_removidos += no->frequencia - no->dado;
        }
        obtem_numeros_removidos_lista_legal_recursivo(no->dir, num_removidos);
    }

    return *num_removidos;
}

int obtem_numeros_removidos_lista_legal(Arvore av) {
    int num_removidos = 0;  // conta o numero de elementos removidos para lista se tornar legal

    // chama percurso in-ordem para obter os numeros a serem removidos
    num_removidos = obtem_numeros_removidos_lista_legal_recursivo(av.raiz, &num_removidos);

    return num_removidos;
}
