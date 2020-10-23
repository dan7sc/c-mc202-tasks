#include <stdio.h>
#include <stdlib.h>

#define TAM_STR 25

typedef struct No {
    int dado;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct Lista {
    No *inicio;
    No *fim;
} Lista;

typedef struct No * PNo;

typedef struct Lista * PLista;

void le_int(int *num) {
    scanf("%d", num);
}

void le_char(char *ch) {
    scanf(" %c", ch);
}

void le_string(char *str) {
    scanf("%s", str);
}

PNo cria_no() {
    return NULL;
}

PLista cria_lista() {
    PLista lista = malloc(sizeof(Lista));

    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

Lista inicia() {
    Lista lista;

    lista.inicio = NULL;
    lista.fim = NULL;

    return lista;
}

void destroi_no(PNo no) {
    free(no);
}

void destroi_lista(PLista lista) {
    PNo temp;

    while(lista->inicio != NULL) {
        temp = lista->inicio->proximo;
        destroi_no(lista->inicio);
        lista->inicio = temp;
    }

    free(lista);
}

void imprime_lista(PLista lista) {
    PNo atual;

    atual = lista->inicio;
    while(atual != NULL) {
        printf("%d", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

void imprime_resultado(Lista lista) {
    PNo atual;

    atual = lista.inicio;
    while(atual != NULL) {
        printf("%d", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}


PLista adiciona_elemento_no_inicio(PLista lista, int dado) {
    PNo novo;

    novo = malloc(sizeof(No));

    novo->dado = dado;
    novo->anterior = NULL;
    novo->proximo = lista->inicio;
    lista->inicio = novo;

    return lista;
}

PLista adiciona_elemento_no_fim(PLista lista, int dado) {
    PNo novo;

    novo = malloc(sizeof(No));

    novo->dado = dado;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if(lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
        return lista;
    }

    novo->anterior = lista->fim;
    lista->fim->proximo = novo;
    lista->fim = novo;

    return lista;
}

int converte_char_para_int(char c) {
    return c - '0';
}

PLista converte_string_para_lista_int(PLista numero, char *str_numero) {
    int num;

    for(int i = 0; str_numero[i] != '\0'; i++) {
        num = converte_char_para_int(str_numero[i]);
        numero = adiciona_elemento_no_inicio(numero, num);
    }

    return numero;
}

Lista soma() {
    Lista resultado;
    resultado = inicia();

    printf("operacao de soma\n");

    return resultado;
}

Lista subtrai() {
    Lista resultado;
    resultado = inicia();

    printf("operacao de subtracao\n");

    return resultado;
}

Lista multiplica() {
    Lista resultado;
    resultado = inicia();

    printf("operacao de multiplicao\n");

    return resultado;
}

Lista divide() {
    Lista resultado;
    resultado = inicia();

    printf("operacao de divisao\n");

    return resultado;
}

void realiza_operacao(char op) {
    Lista resultado;

    switch(op) {
    case '+':
        resultado = soma();
        imprime_resultado(resultado);
        break;
    case '-':
        resultado = subtrai();
        imprime_resultado(resultado);
        break;
    case '*':
        resultado = multiplica();
        imprime_resultado(resultado);
        break;
    case '/':
        resultado = divide();
        imprime_resultado(resultado);
        break;
    default:
        printf("operacao desconhecida\n");
        break;
    }
}

int main() {
    int qtd_teste;
    char operacao;
    char str_numero1[TAM_STR];
    char str_numero2[TAM_STR];
    PLista numero1;
    PLista numero2;

    numero1 = cria_lista();
    numero2 = cria_lista();

    le_int(&qtd_teste);
    le_char(&operacao);
    le_string(str_numero1);
    le_string(str_numero2);

    numero1 = converte_string_para_lista_int(numero1, str_numero1);
    numero2 = converte_string_para_lista_int(numero2, str_numero2);

    printf("%d ", qtd_teste);
    printf("%c\n", operacao);

    /* printf("%s\n", str_numero1); */
    /* printf("%s\n", str_numero2); */

    imprime_lista(numero1);
    imprime_lista(numero2);

    realiza_operacao(operacao);

    destroi_lista(numero1);
    destroi_lista(numero2);

    return 0;
}
