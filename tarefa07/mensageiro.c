#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

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

int compara_cartao(void *t_cartao, void *cartao) {
    /* int numero = (int)(((Cartao *) t_cartao)->numero); */
    Cartao t = *(Cartao *) t_cartao;
    Cartao c = *(Cartao *) cartao;

    if(t.numero < c.numero) {
        return -1;
    } else if(t.numero > c.numero) {
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

Cartao *concatena_string(Cartao *cartao, void *dado) {
    Cartao c = *(Cartao *) dado;
    char *copia = NULL;
    char *temp = NULL;
    int tam_cartao = 0;
    int tam_dado = 0;

    tam_dado = 1 + strlen(c.texto);

    if(cartao->texto == NULL) {
        copia = malloc(tam_dado * sizeof(char));
        cartao->numero = 0;
        strcpy(copia, c.texto);
        cartao->texto = copia;
        copia = NULL;
    } else {
        tam_cartao = 1 + strlen(cartao->texto);
        copia = malloc(tam_cartao * sizeof(char));
        temp = malloc((tam_cartao + tam_dado) * sizeof(char));

        strcpy(copia, cartao->texto);
        strcpy(temp, copia);
        strcat(temp, c.texto);

        free(cartao->texto);
        cartao->texto = temp;
        cartao->numero += c.numero;
    }

    free(copia);

    return cartao;
}

int soma(void *a, void *b) {
    int num = *(int *) a;
    Cartao c = *(Cartao *) b;

    return num + c.numero;
}

void destroi_cartao(void *cartao) {
    Cartao *c = (Cartao *) cartao;

    free(c->texto);
}

int main() {
    int num_cartoes;
    int num_autoridades;
    int n;
    Cartao *cartao = NULL;
    Cartao *novo_cartao = NULL;
    Arvore pares;
    Arvore av_triade;
    PNo temp1 = NULL;
    PNo temp2 = NULL;
    PNo temp3 = NULL;
    Triade *triade = NULL;
    int autoridade_numero;

    n = 1;
    while(n > -1) {
        n = le_int(&num_cartoes);
        if(n > -1) {
            le_int(&num_autoridades);

            pares = cria_arvore();
            for(int i = 0; i < num_cartoes; i++) {
                cartao = malloc(sizeof(Cartao));
                cartao->texto = malloc(6 * sizeof(char));
                le_int(&cartao->numero);
                le_string_entre_aspas(cartao->texto);
                pares = insere(pares, cartao, compara_numero_cartao);
            }

            for(int i = 0; i < num_autoridades; i++) {
                le_int(&autoridade_numero);

                triade = malloc(sizeof(Triade));
                triade->num_cartao1 = 0;
                triade->num_cartao2 = 0;
                triade->num_cartao3 = 0;

                triade = busca_triade(pares, triade, autoridade_numero, soma, compara_numero_cartao);

                av_triade = cria_arvore();
                if(triade->num_cartao1 > 0 && triade->num_cartao2 > 0 && triade->num_cartao3 > 0) {
                    temp1 = busca(pares, &triade->num_cartao1, compara_numero_cartao);
                    temp2 = busca(pares, &triade->num_cartao2, compara_numero_cartao);
                    temp3 = busca(pares, &triade->num_cartao3, compara_numero_cartao);

                    av_triade = insere(av_triade, temp1->dado, compara_numero_cartao);
                    av_triade = insere(av_triade, temp2->dado, compara_numero_cartao);
                    av_triade = insere(av_triade, temp3->dado, compara_numero_cartao);

                    pares = remove_no(pares, &triade->num_cartao1, compara_numero_cartao);
                    pares = remove_no(pares, &triade->num_cartao2, compara_numero_cartao);
                    pares = remove_no(pares, &triade->num_cartao3, compara_numero_cartao);

                    novo_cartao = malloc(sizeof(Cartao));
                    novo_cartao->texto = NULL;
                    novo_cartao->numero = 0;
                    novo_cartao = cria_cartao(av_triade, novo_cartao, concatena_string);

                    av_triade = remove_no(av_triade, &triade->num_cartao1, compara_numero_cartao);
                    av_triade = remove_no(av_triade, &triade->num_cartao2, compara_numero_cartao);
                    av_triade = remove_no(av_triade, &triade->num_cartao3, compara_numero_cartao);

                    pares = insere(pares, novo_cartao, compara_numero_cartao);

                    if(temp1 != NULL && temp2 != NULL && temp3 != NULL) {
                        free(temp1);
                        free(temp2);
                        free(temp3);
                    }
                }

                free(triade);
                destroi_arvore(av_triade, destroi_cartao);

                if(av_triade.raiz != NULL) {
                    destroi_arvore(av_triade, destroi_cartao);
                }
            }

            printf("%d %d\n", num_cartoes, num_autoridades);
            if(pares.raiz != NULL && pares.raiz->dado != NULL) {
                percorre(pares, pre_ordem, imprime_cartao);
            }

            if(pares.raiz != NULL) {
                destroi_arvore(pares, destroi_cartao);
            }

            if(av_triade.raiz != NULL) {
                destroi_arvore(av_triade, destroi_cartao);
            }
        }
    }

    return 0;
}
