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

void concatena(char *string_a, void *dado) {
    Cartao c = *(Cartao *) dado;
    char *str_copia = malloc(sizeof(char *));
    int i = 0;

    while(string_a[i] != '\0') {
        i++;
    }

    printf("CONCATENA1 %s\n", string_a);

    strcpy(str_copia, c.texto);
    for(int j = 0; c.texto[j] != '\0'; j++) {
        string_a[i++] = c.texto[j];
    }
    printf("CONCATENA2 %s\n", string_a);

    string_a[i] = '\0';
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
    Arvore pares;
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
                cartao->texto = malloc(sizeof(char *));
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

                pares = remove_no(pares, &triade->num_cartao1, compara_numero_cartao);
                pares = remove_no(pares, &triade->num_cartao2, compara_numero_cartao);
                pares = remove_no(pares, &triade->num_cartao3, compara_numero_cartao);

                free(triade);
            }

            printf("%d %d\n", num_cartoes, num_autoridades);
            if(pares.raiz != NULL && pares.raiz->dado != NULL) {
                percorre(pares, pre_ordem, imprime_cartao);
            }

            if(pares.raiz != NULL) {
                destroi_arvore(pares, destroi_cartao);
            }
        }
    }

    return 0;
}
