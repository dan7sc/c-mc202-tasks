#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_de_ajuda.h"

// le numero inteiro
int le_int(int *num) {
    return scanf("%d", num);
}

// le string entre aspas e nao armazena as aspas
void le_string_entre_aspas(char *str) {
    char ch;
    int i;
    int contador = 0;

    getchar();
    for(i = 0; contador < 2 && i <= TAM_TEXTO; i++) {
        scanf("%c", &ch);
        // armazena a letra
        if(ch != '"') {
            str[i] = ch;
        } else {
            // retorna uma posicao quando encontra aspas
            // e incrementa contador de aspas
            i--;
            contador++;
        }
    }
    str[i] = '\0';
}

// compara numero com o numero do cartao e retorna
// -1 se numero é menor que o numero do cartao
// 0 se numero é igual ao numero do cartao
// 1 se numero é maior que o numero do cartao
int compara_numero_cartao(void *numero, void *cartao) {
    int num = *(int *) numero;
    Cartao c = *(Cartao *) cartao;

    if(num < c.numero) {
        return -1;
    } else if(num > c.numero) {
        return 1;
    } else {
        return 0;
    }
}

// imprime string armazenada no cartao
void imprime_mensagem(void *cartao) {
    Cartao c = *(Cartao *) cartao;

    printf("%s", c.texto);
}

// concatena texto do cartao com a string que está
// sendo gerada pela concatenação dos textos de todos os cartões
Cartao *concatena_string(Cartao *cartao, void *dado) {
    Cartao c = *(Cartao *) dado;
    char *temp = NULL;
    int tam_cartao = 0;
    int tam_dado = 0;

    tam_dado = 1 + strlen(c.texto);

    if(cartao->texto == NULL) {
        cartao->texto = malloc(tam_dado * sizeof(char));
        cartao->numero += c.numero;
        strcpy(cartao->texto, c.texto);
    } else {
        // aloca memoria suficiente para concatenar as duas strings
        // de tamanhos tam_cartao e tam_dado
        tam_cartao = 1 + strlen(cartao->texto);
        temp = malloc((tam_cartao + tam_dado) * sizeof(char));
        strcpy(temp, cartao->texto);
        strcat(temp, c.texto);
        free(cartao->texto);
        // cartao armazena a nova string e o novo numero
        cartao->texto = temp;
        cartao->numero += c.numero;
    }

    return cartao;
}

// soma numero com o numero do cartao
int soma(void *numero, void *cartao) {
    int num = *(int *) numero;
    Cartao c = *(Cartao *) cartao;

    return num + c.numero;
}

// libera memória da string do cartao
void destroi_texto(void *cartao) {
    Cartao *c = (Cartao *) cartao;

    free(c->texto);
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
    int tamanho = sizeof(Cartao);

    no_a->dado = malloc(tamanho);
    memcpy(no_a->dado, no_b->dado, tamanho);

    return no_a;
}

// obtem numero do cartao
int obtem_numero(void *dado) {
    Cartao c = *(Cartao *)dado;

    return c.numero;
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

// concatena texto de cada no da arvore do menor para o maior numero do no
Cartao *cria_cartao_recursivo(PNo no, Cartao *cartao,
                              Cartao *(*concatena)(Cartao *cartao, void *dado)) {
    if(no != NULL) {
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
