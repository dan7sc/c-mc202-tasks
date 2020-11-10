#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int le_int(int *num) {
    return scanf("%d", num);
}

void le_char(char *ch) {
    scanf(" %c", ch);
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
        return 0;
    } else {
        return 1;
    }
}

int compara_autoridade_numero(void *numero, void *autoridade) {
    int *num = (int *) numero;
    Autoridade *aut = (Autoridade *) autoridade;

    if(*num < aut->numero) {
        return 0;
    } else {
        return 1;
    }
}

void imprime_cartao(void *cartao) {
    Cartao *c = (Cartao *) cartao;

    printf("%d %s ", c->numero, c->texto);
}

void imprime_autoridade(void *autoridade) {
    Autoridade *aut = (Autoridade *) autoridade;

    printf("%d ", aut->numero);
}

int main() {
    int num_cartoes;
    int num_autoridades;
    int n;
    Cartao *cartao;
    Autoridade *autoridade;
    Arvore pares;
    Arvore autoridades;

    n = 1;
    while(n > -1) {
        while(n > 0) {
            le_int(&num_cartoes);
            le_int(&num_autoridades);

            if(n > 0) {
                pares = cria_arvore();
            }
            for(int i = 0; i < num_cartoes; i++) {
                cartao = malloc(sizeof(Cartao));
                le_int(&cartao->numero);
                le_string_entre_aspas(cartao->texto);
                if(n > 0) {
                    pares = insere(pares, cartao, compara_cartao_numero);
                }
            }

            if(n > 0) {
                autoridades = cria_arvore();
            }
            for(int i = 0; i < num_autoridades; i++) {
                autoridade = malloc(sizeof(Autoridade));
                n = le_int(&autoridade->numero);
                if(n > 0) {
                    autoridades = insere(autoridades, autoridade, compara_autoridade_numero);
                }
            }
            if(n > 0) {
                printf("%d %d\n", num_cartoes, num_autoridades);
                percorre(pares, pre_ordem, imprime_cartao);
                percorre(autoridades, pre_ordem, imprime_autoridade);
            }

            destroi_arvore(pares);
            destroi_arvore(autoridades);
        }
    }

    return 0;
}
