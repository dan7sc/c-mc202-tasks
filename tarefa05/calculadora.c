#include <stdio.h>
#include <stdlib.h>

#define TAM_STR 25

typedef struct No {
    int dado;
    struct No *prox;
} No;

typedef struct No * PNo;

void le_int(int *num) {
    scanf("%d", num);
}

void le_char(char *ch) {
    scanf(" %c", ch);
}

void le_string(char *str) {
    scanf("%s", str);
}

PNo cria_lista() {
    return NULL;
}

void destroi_lista(PNo lista) {
    if(lista != NULL) {
        destroi_lista(lista->prox);
        free(lista);
    }
}

void imprime_lista(PNo lista) {
    PNo atual;

    atual = lista;
    while(atual != NULL) {
        printf("%d", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

PNo adiciona_elemento(PNo lista, int dado) {
    PNo novo;

    novo = malloc(sizeof(No));
    novo->dado = dado;
    novo->prox = lista;

    return novo;
}

PNo adiciona_elemento_no_fim(PNo lista, int dado) {
    PNo novo;
    PNo temp = lista;

    novo = malloc(sizeof(No));

    novo->dado = dado;
    novo->prox = NULL;

    if(lista == NULL) {
        return novo;
    }

    while(temp->prox != NULL) {
        temp = temp->prox;
    }
    temp->prox = novo;

    return lista;
}

int converte_char_para_int(char c) {
    return c - '0';
}

PNo converte_string_para_lista_int(char *str_numero) {
    int num;
    PNo numero;

    numero = cria_lista();

    for(int i = 0; str_numero[i] != '\0'; i++) {
        num = converte_char_para_int(str_numero[i]);
        numero = adiciona_elemento_no_fim(numero, num);
    }

    return numero;
}

int main() {
    int qtd_teste;
    char operacao;
    char str_numero1[TAM_STR];
    char str_numero2[TAM_STR];
    PNo numero1;
    PNo numero2;

    numero1 = cria_lista();
    numero2 = cria_lista();

    le_int(&qtd_teste);
    le_char(&operacao);
    le_string(str_numero1);
    le_string(str_numero2);

    numero1 = converte_string_para_lista_int(str_numero1);
    numero2 = converte_string_para_lista_int(str_numero2);

    printf("%d ", qtd_teste);
    printf("%c\n", operacao);

    /* printf("%s\n", str_numero1); */
    /* printf("%s\n", str_numero2); */

    imprime_lista(numero1);
    imprime_lista(numero2);

    destroi_lista(numero1);
    destroi_lista(numero2);

    return 0;
}
