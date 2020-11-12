#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int le_int(int *num) {
    return scanf("%d", num);
}

// le string entre aspas e nao armazena as aspas
void le_string_entre_aspas(char *str) {
    char ch;
    int i;
    int contador = 0;

    for(i = 0; contador < 2 && i < TAM_STR - 1; i++) {
        scanf("%c", &ch);
        if(ch != '"') {
            str[i] = ch;
        } else {
            i--;
            contador++;
        }
    }
    str[i] = '\0';
}

/* void le_string_entre_aspas(char *str) { */
/*     char ch; */
/*     int i; */
/*     int contador = 0; */

/*     for(i = 0; contador < 2 && i < TAM_STR; i++) { */
/*         scanf("%c", &ch); */
/*         if(ch == '"') { */
/*             contador++; */
/*         } */
/*         str[i] = ch; */
/*     } */
/*     str[i] = '\0'; */
/* } */

int compara_cartao_numero(void *numero, void *cartao) {
    int *num = (int *) numero;
    Cartao *c = (Cartao *) cartao;

    if(*num < c->numero) {
        return -1;
    } else if(*num > c->numero) {
        return 1;
    } else {
        return 0;
    }
}

int compara_autoridade_numero(void *numero, void *autoridade) {
    int *num = (int *) numero;
    Autoridade *aut = (Autoridade *) autoridade;

    if(*num < aut->numero) {
        return -1;
    } else if(*num > aut->numero) {
        return 1;
    } else {
        return 0;
    }
}

void imprime_cartao(void *cartao) {
    Cartao c = *(Cartao *) cartao;

    printf("%d %s ", c.numero, c.texto);
}

void imprime_autoridade(void *autoridade) {
    Autoridade aut = *(Autoridade *) autoridade;

    printf("%d ", aut.numero);
}

void concatena_cartao(void *cartao) {
    Cartao c = *(Cartao *) cartao;

    for(int i = 1; c.texto[i] != '\0'; i++) {
        printf("%c", c.texto[i]);
    }
}

int soma(void *a, void *b) {
    int num = *(int *) a;
    Cartao c = *(Cartao *) b;

    return num + c.numero;
}

int main() {
    int num_cartoes;
    int num_autoridades;
    int n;
    Cartao *cartao;
    Autoridade *autoridade;
    Arvore pares;
    Arvore autoridades;
    int num_cartao_a_remover;
    PNo cartao_encontrado;

    n = 1;
    while(n > -1) {
        n = le_int(&num_cartoes);
        if(n > -1) {
            le_int(&num_autoridades);

            pares = cria_arvore();
            for(int i = 0; i < num_cartoes; i++) {
                cartao = malloc(sizeof(Cartao));
                le_int(&cartao->numero);
                le_string_entre_aspas(cartao->texto);
                pares = insere(pares, cartao, compara_cartao_numero);
            }

            autoridades = cria_arvore();
            for(int i = 0; i < num_autoridades; i++) {
                autoridade = malloc(sizeof(Autoridade));
                le_int(&autoridade->numero);
                autoridades = insere(autoridades, autoridade, compara_autoridade_numero);
                conta_triade(pares, autoridade->numero, soma);
            }

            num_cartao_a_remover = 65;
            cartao_encontrado = NULL;

            cartao_encontrado = busca(pares, &num_cartao_a_remover, compara_cartao_numero);
            pares = remove_no(pares, &num_cartao_a_remover, compara_cartao_numero);

            printf("%d %d\n", num_cartoes, num_autoridades);

            if(pares.raiz != NULL && pares.raiz->dado != NULL) {
                percorre(pares, pre_ordem, imprime_cartao);
            }
            percorre(autoridades, in_ordem, imprime_autoridade);

            percorre(pares, pre_ordem, concatena_cartao);

            if(pares.raiz != NULL) {
                destroi_arvore(pares);
            }
            destroi_arvore(autoridades);
            destroi_no(cartao_encontrado);
        }
    }

    return 0;
}
