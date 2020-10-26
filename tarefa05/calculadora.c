#include <stdio.h>
#include <stdlib.h>

#define TAM_STR 25
#define MAIOR 1
#define IGUAL 0
#define MENOR -1

typedef struct No {
    int dado;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct Lista {
    int tamanho;
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

    lista->tamanho = 0;
    lista->inicio = NULL;
    lista->fim = NULL;

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

PLista adiciona_elemento_no_inicio(PLista lista, int dado) {
    PNo novo;

    novo = malloc(sizeof(No));

    novo->dado = dado;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if(lista->fim == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
        lista->tamanho++;
        return lista;
    }

    novo->proximo = lista->inicio;
    lista->inicio->anterior = novo;
    lista->inicio = novo;
    lista->tamanho++;

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
        lista->tamanho++;
        return lista;
    }

    novo->anterior = lista->fim;
    lista->fim->proximo = novo;
    lista->fim = novo;
    lista->tamanho++;

    return lista;
}

int converte_char_para_int(char c) {
    return c - '0';
}

PLista converte_string_para_lista_int(PLista numero, char *str_numero) {
    int num;

    for(int i = 0; str_numero[i] != '\0'; i++) {
        num = converte_char_para_int(str_numero[i]);
        numero = adiciona_elemento_no_fim(numero, num);
    }

    return numero;
}

PLista remove_zeros_iniciais(PLista lista) {
    PNo aux;
    PNo temp;

    aux = lista->inicio;
    while(aux->dado == 0 && lista->tamanho > 1) {
        temp = aux;
        lista->inicio = lista->inicio->proximo;
        lista->inicio->anterior = NULL;
        aux = aux->proximo;
        lista->tamanho--;
        destroi_no(temp);
    }

    return lista;
}

int eh_maior_numero(PLista lista1, PLista lista2) {
    PNo num1 = lista1->inicio;
    PNo num2 = lista2->inicio;

    if(lista1->tamanho > lista2->tamanho) {
        return MAIOR;
    } else if(lista1->tamanho < lista2->tamanho) {
        return MENOR;
    } else {
        while(num1 != NULL && num2 != NULL) {
            if(num1->dado > num2->dado) {
                return MAIOR;
            } else if(num1->dado < num2->dado) {
                return MENOR;
            }
            num1 = num1->proximo;
            num2 = num2->proximo;
        }
        return IGUAL;
    }
}

PLista copia_lista(PLista lista) {
    PNo aux;
    PLista lcopia;

    lcopia = cria_lista();
    aux = lista->fim;
    while(aux != NULL) {
        lcopia = adiciona_elemento_no_inicio(lcopia, aux->dado);
        aux = aux->anterior;
    }

    return lcopia;
}

PLista soma_elementos_restantes(PLista lista, PNo no, int num) {
    int adicional = num;

    while(no != NULL || adicional == 1) {
        if(no != NULL) {
            num = no->dado + adicional;
            no = no->anterior;
        } else {
            num = adicional;
        }
        adicional = 0;
        if(num > 9) {
            num -= 10;
            adicional = 1;
        }
        lista = adiciona_elemento_no_inicio(lista, num);
    }

    return lista;
}

PLista soma(PLista numero1, PLista numero2) {
    PNo maior;
    PNo menor;
    int soma;
    int adicional = 0;
    PLista resultado;

    resultado = cria_lista();

    if(eh_maior_numero(numero1, numero2) == MENOR) {
        menor = numero1->fim;
        maior = numero2->fim;
    } else {
        maior = numero1->fim;
        menor = numero2->fim;
    }

    while(menor != NULL) {
        soma = maior->dado + menor->dado + adicional;
        adicional = 0;
        if(soma > 9) {
            soma -= 10;
            adicional = 1;
        }
        resultado = adiciona_elemento_no_inicio(resultado, soma);
        maior = maior->anterior;
        menor = menor->anterior;
    }

    if(maior == NULL && adicional == 1) {
        resultado = adiciona_elemento_no_inicio(resultado, adicional);
    } else {
        resultado = soma_elementos_restantes(resultado, maior, adicional);
    }

    return resultado;
}

PLista subtrai(PLista numero1, PLista numero2) {
    PNo maior;
    PNo menor;
    int diferenca;
    int subtracional = 0;
    int adicional = 0;
    int eh_maior;
    PLista resultado;

    resultado = cria_lista();

    eh_maior = eh_maior_numero(numero1, numero2);
    if(eh_maior == MAIOR) {
        maior = numero1->fim;
        menor = numero2->fim;
    } else if(eh_maior == MENOR) {
        menor = numero1->fim;
        maior = numero2->fim;
    } else {
        resultado = adiciona_elemento_no_inicio(resultado, 0);
        return resultado;
    }

    while(maior != NULL && menor != NULL) {
        if(maior->dado >= menor->dado) {
            diferenca = maior->dado - subtracional - menor->dado;
            subtracional = 0;
            if(diferenca < 0) {
                diferenca = 9;
                subtracional = 1;
            }
            resultado = adiciona_elemento_no_inicio(resultado, diferenca);
            adicional = 0;
        } else {
            adicional = 10;
            diferenca = maior->dado + adicional - subtracional - menor->dado;
            resultado = adiciona_elemento_no_inicio(resultado, diferenca);
            adicional = 0;
            subtracional = 1;
        }
        maior = maior->anterior;
        menor = menor->anterior;
    }

    while(maior != NULL) {
        diferenca = maior->dado - subtracional;
        resultado = adiciona_elemento_no_inicio(resultado, diferenca);
        subtracional = 0;
        maior = maior->anterior;
    }
    resultado = remove_zeros_iniciais(resultado);

    return resultado;
}

PLista multiplica(PLista numero1, PLista numero2) {
    PNo num1;
    PNo num2;
    PLista resultado;
    PLista aux;
    PLista temp;
    int multiplicacao;
    int adicional = 0;
    int zeros_a_adicionar = 0;

    resultado = cria_lista();
    num2 = numero2->fim;

    while(num2 != NULL) {
        aux = cria_lista();
        temp = aux;
        for(int i = 0; i < zeros_a_adicionar; i++) {
            aux = adiciona_elemento_no_inicio(aux, 0);
        }
        zeros_a_adicionar++;

        num1 = numero1->fim;
        adicional = 0;

        while(num1 != NULL) {
            multiplicacao = (num1->dado * num2->dado) + adicional;
            if(multiplicacao > 9) {
                adicional = multiplicacao / 10;
                multiplicacao %=  10;
            } else {
                adicional = 0;
            }
            aux = adiciona_elemento_no_inicio(aux, multiplicacao);
            num1 = num1->anterior;
        }

        if(adicional > 0) {
            aux = adiciona_elemento_no_inicio(aux, adicional);
        }

        temp = resultado;
        resultado = soma(aux, resultado);

        destroi_lista(temp);
        destroi_lista(aux);
        num2 = num2->anterior;
    }
    resultado = remove_zeros_iniciais(resultado);

    return resultado;
}

PLista divide(PLista numero1, PLista numero2) {
    int eh_maior;
    PLista aux;
    PLista temp;
    PLista resultado;
    PLista l_unidade;

    resultado = cria_lista();
    aux = cria_lista();
    l_unidade = cria_lista();
    l_unidade = adiciona_elemento_no_inicio(l_unidade, 1);
    temp = copia_lista(numero2);

    if(numero2->inicio->dado == 1 && numero2->tamanho == 1) {
        resultado = copia_lista(numero1);
        destroi_lista(l_unidade);
        destroi_lista(temp);
        destroi_lista(aux);
        return resultado;
    }

    eh_maior = eh_maior_numero(numero1, numero2);
    if(eh_maior == IGUAL) {
        resultado = adiciona_elemento_no_inicio(resultado, 1);
    } else if(eh_maior == MENOR) {
        resultado = adiciona_elemento_no_inicio(resultado, 0);
    } else {
        while(eh_maior == MAIOR || eh_maior == IGUAL) {
            aux = soma(temp, numero2);
            destroi_lista(temp);
            temp = copia_lista(aux);
            resultado = soma(resultado, l_unidade);
            eh_maior = eh_maior_numero(numero1, aux);
            destroi_lista(aux);
        }
    }

    destroi_lista(l_unidade);
    destroi_lista(temp);
    return resultado;
}

void realiza_operacao(char op, PLista numero1, PLista numero2) {
    PLista resultado;

    switch(op) {
    case '+':
        resultado = soma(numero1, numero2);
        imprime_lista(resultado);
        destroi_lista(resultado);
        break;
    case '-':
        resultado = subtrai(numero1, numero2);
        imprime_lista(resultado);
        destroi_lista(resultado);
        break;
    case '*':
        resultado = multiplica(numero1, numero2);
        imprime_lista(resultado);
        destroi_lista(resultado);
        break;
    case '/':
        resultado = divide(numero1, numero2);
        imprime_lista(resultado);
        destroi_lista(resultado);
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

    le_int(&qtd_teste);

    for(int i = 0; i < qtd_teste; i++) {
        le_char(&operacao);
        le_string(str_numero1);
        le_string(str_numero2);

        numero1 = cria_lista();
        numero2 = cria_lista();

        numero1 = converte_string_para_lista_int(numero1, str_numero1);
        numero2 = converte_string_para_lista_int(numero2, str_numero2);

        realiza_operacao(operacao, numero1, numero2);

        destroi_lista(numero1);
        destroi_lista(numero2);
    }

    return 0;
}
