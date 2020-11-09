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

PLista cria_lista() {
    PLista lista = malloc(sizeof(Lista));

    lista->tamanho = 0;
    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

void destroi_lista(PLista lista) {
    PNo temp;

    while(lista->inicio != NULL) {
        temp = lista->inicio->proximo;
        free(lista->inicio);
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

PLista converte_string_para_lista_int(PLista numero, char *str) {
    int num;

    for(int i = 0; str[i] != '\0'; i++) {
        num = str[i] - '0';
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
        free(temp);
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

PLista soma_elementos_restantes(PLista numero, PNo inicio, int num) {
    int unidade_a_adicionar = num;

    if(inicio == NULL && num == 1) {
        /* lista maior terminaou mas ainda há uma unidade decimal a adicionar */
        numero = adiciona_elemento_no_inicio(numero, num);
        return numero;
    }

    /* lista não terminou e/ou ainda há elementos a adicionar */
    while(inicio != NULL || unidade_a_adicionar == 1) {
        if(inicio != NULL) {
            num = inicio->dado + unidade_a_adicionar;
            inicio = inicio->anterior;
        } else {
            num = unidade_a_adicionar;
        }
        unidade_a_adicionar = 0;
        /* se soma tem duas casas decimais então subtrai unidade a mais */
        /* e guarda unidade decimal excedente para somar no nó anterior  */
        if(num > 9) {
            num -= 10;
            unidade_a_adicionar = 1;
        }
        /* adiciona apenas número com uma casa decimal */
        numero = adiciona_elemento_no_inicio(numero, num);
    }

    return numero;
}

PLista subtrai_elementos_restantes(PLista numero, PNo inicio, int num) {
    int unidade_a_subtrair = num;

    if(inicio == NULL && num == 1) {
        /* lista maior terminaou mas ainda há uma unidade decimal a adicionar */
        numero = adiciona_elemento_no_inicio(numero, num);
        return numero;
    }

    /* lista não terminou e/ou ainda há elementos a subtrair */
    while(inicio != NULL || unidade_a_subtrair == 1) {
        if(inicio != NULL) {
            num = inicio->dado - unidade_a_subtrair;
            inicio = inicio->anterior;
        } else {
            num = unidade_a_subtrair;
        }
        unidade_a_subtrair = 0;
        /* se diferença for negativa é porque está somando com zero */
        /* e subtraindo uma unidade logo diferença passa a ser nove */
        /* e guarda unidade decimal para subtrair no nó anterior  */
        if(num < 0) {
            num = 9;
            unidade_a_subtrair = 1;
        }
        /* num tem apenas número com uma casa decimal */
        numero = adiciona_elemento_no_inicio(numero, num);
    }

    return numero;
}

PLista obtem_potencia_de_dez(int inteiro, int tamanho) {
    PLista lista;

    lista = cria_lista();
    lista = adiciona_elemento_no_inicio(lista, inteiro);

    if(tamanho == 0) {
        return lista;
    }

    for(int i = 0; i < tamanho; i++) {
        lista = adiciona_elemento_no_fim(lista, 0);
    }

    return lista;
}

PLista soma(PLista numero1, PLista numero2) {
    PNo maior;
    PNo menor;
    int soma;
    int unidade_a_adicionar = 0;
    PLista resultado;

    resultado = cria_lista();

    /* nó maior aponta para o fim do maior numero */
    /* e nó menor para o fim do  menor numero */
    if(eh_maior_numero(numero1, numero2) == MENOR) {
        menor = numero1->fim;
        maior = numero2->fim;
    } else {
        maior = numero1->fim;
        menor = numero2->fim;
    }

    /* Soma elementos começando pelo fim */
    while(menor != NULL) {
        soma = maior->dado + menor->dado + unidade_a_adicionar;
        unidade_a_adicionar = 0;
        /* se soma tem duas casas decimais então subtrai unidade a mais */
        /* e guarda unidade decimal excedente para somar no nó anterior  */
        if(soma > 9) {
            soma -= 10;
            unidade_a_adicionar = 1;
        }
        /* adiciona apenas número com uma casa decimal */
        resultado = adiciona_elemento_no_inicio(resultado, soma);
        maior = maior->anterior;
        menor = menor->anterior;
    }

    resultado = soma_elementos_restantes(resultado, maior, unidade_a_adicionar);

    return resultado;
}

PLista subtrai(PLista numero1, PLista numero2) {
    PNo maior;
    PNo menor;
    int diferenca;
    int unidade_a_subtrair = 0;
    int unidade_a_adicionar = 0;
    int eh_maior;
    PLista resultado;

    resultado = cria_lista();

    /* nó maior aponta para o fim do maior numero */
    /* e nó menor para o fim do  menor numero */
    /* se numeros forem iguais retorna lista com zero */
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

    /* subtrai elementos começando pelo fim */
    while(maior != NULL && menor != NULL) {
        if(maior->dado >= menor->dado) {
            diferenca = maior->dado - unidade_a_subtrair - menor->dado;
            unidade_a_subtrair = 0;
            /* se diferença for negativa é porque está somando nós */
            /* com dois zeros e subtraindo uma unidade */
            /* logo diferença passa a ser nove */
            /* e guarda unidade decimal para subtrair no nó anterior  */
            if(diferenca < 0) {
                diferenca = 9;
                unidade_a_subtrair = 1;
            }
            resultado = adiciona_elemento_no_inicio(resultado, diferenca);
            unidade_a_adicionar = 0;
        } else {
            /* número do nó maior é menor que o do nó menor */
            /* logo acrescenta uma dezena vinda do nó anterior */
            /* resultado terá sempre uma casa decimal */
            unidade_a_adicionar = 10;
            diferenca = maior->dado + unidade_a_adicionar - unidade_a_subtrair - menor->dado;
            /* adiciona apenas número com uma casa decimal */
            resultado = adiciona_elemento_no_inicio(resultado, diferenca);
            unidade_a_adicionar = 0;
            unidade_a_subtrair = 1;
        }
        maior = maior->anterior;
        menor = menor->anterior;
    }

    resultado = subtrai_elementos_restantes(resultado, maior, unidade_a_subtrair);
    resultado = remove_zeros_iniciais(resultado);

    return resultado;
}

PLista multiplica(PLista numero1, PLista numero2) {
    PNo num1;
    PNo num2;
    PLista resultado;
    PLista produto_a_somar; // armazena o resultado da multiplicação para cada iteração
    PLista temp; // ponteiro temporário
    int produto;
    int unidade_a_adicionar = 0;
    int posicao_multiplicador = 1;

    resultado = cria_lista();
    /* começa multiplicação pelo fim da lista */
    num2 = numero2->fim;

    while(num2 != NULL) {
        num1 = numero1->fim;
        produto_a_somar = cria_lista();

        /* produto a partir do segundo número do multiplicador */
        /* acrescenta zeros no resultado */
        for(int i = 1; i < posicao_multiplicador; i++) {
            produto_a_somar = adiciona_elemento_no_inicio(produto_a_somar, 0);
        }
        posicao_multiplicador++;

        unidade_a_adicionar = 0;
        /* aqui acontece a multiplicação de um número do multiplicador */
        /* pelos números do multiplicando */
        /* resultado do produto é armazenado na lista produto_a_somar */
        while(num1 != NULL) {
            produto = (num1->dado * num2->dado) + unidade_a_adicionar;
            /* produto dos números tem duas unidades decimais */
            /* logo remove uma unidade decimal para adicionar no nó anterior */
            if(produto > 9) {
                unidade_a_adicionar = produto / 10;
                produto %=  10;
            } else {
                unidade_a_adicionar = 0;
            }
            /* adiciona apenas número com uma casa decimal */
            produto_a_somar = adiciona_elemento_no_inicio(produto_a_somar, produto);
            num1 = num1->anterior;
        }

        /* ainda há uma casa decimal a adicionar */
        if(unidade_a_adicionar > 0) {
            produto_a_somar = adiciona_elemento_no_inicio(produto_a_somar, unidade_a_adicionar);
        }

        /* guarda referencia a memoria alocada da lista resultado */
        temp = resultado;
        /* soma o resultado dos produtos */
        resultado = soma(produto_a_somar, resultado);
        num2 = num2->anterior;

        destroi_lista(temp);
        destroi_lista(produto_a_somar);
    }

    resultado = remove_zeros_iniciais(resultado);

    return resultado;
}

PLista divide(PLista numero1, PLista numero2) {
    int eh_maior;
    int tam; // diferença de tamanho entre numero1 e numero2
    PLista quociente;
    PLista l_produto;
    PLista l_soma;
    PLista resultado;
    PLista l_a_somar;
    PLista temp;  // ponteiro temporário

    /* se o divisor é um retorna o dividendo */
    if(numero2->inicio->dado == 1 && numero2->tamanho == 1) {
        resultado = copia_lista(numero1);
        return resultado;
    }

    resultado = cria_lista();

    eh_maior = eh_maior_numero(numero1, numero2);
    if(eh_maior == IGUAL) {
        /* se os números são iguais retorn lita com um */
        resultado = adiciona_elemento_no_inicio(resultado, 1);
    } else if(eh_maior == MENOR) {
        /* se o dividendo é menor que o divisor retorn lita com zero */
        resultado = adiciona_elemento_no_inicio(resultado, 0);
    } else {
        tam = numero1->tamanho - numero2->tamanho;
        while(tam >= 0) {
            l_a_somar = cria_lista();
            for(int i = 1; i < 10; i++) {
                /* obtem potència de dez que multiplicada pelo divisor */
                /* dá como resultado o menor número mais próximo do dividendo */
                quociente = obtem_potencia_de_dez(i, tam);
                l_soma = soma(resultado, quociente);
                l_produto = multiplica(l_soma, numero2);
                /* verifica se o produto é menor que o divisor  */
                eh_maior = eh_maior_numero(l_produto, numero1);
                destroi_lista(l_produto);
                /* se for menor então encontramos o maior número que  */
                /* multiplicado pelo divisor chega próximo ao dividendo */
                if(eh_maior == MENOR || eh_maior == IGUAL) {
                    temp = l_a_somar;
                    l_a_somar = copia_lista(quociente);
                    destroi_lista(temp);
                }
                destroi_lista(quociente);
                destroi_lista(l_soma);
            }
            /* guarda referencia a memoria alocada da lista resultado */
            temp = resultado;
            /* resultado é a soma dos quocientes obtidos iterativamente */
            resultado = soma(resultado, l_a_somar);
            tam -= 1;

            destroi_lista(temp);
            destroi_lista(l_a_somar);
        }
    }

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
