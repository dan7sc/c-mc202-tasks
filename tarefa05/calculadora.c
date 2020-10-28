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

PLista limpa_lista(PLista lista) {
    PNo temp;

    while(lista->inicio != NULL) {
        temp = lista->inicio->proximo;
        destroi_no(lista->inicio);
        lista->inicio = temp;
    }

    return lista;
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

void imprime_lista_reversa(PLista lista) {
    PNo atual;

    atual = lista->fim;
    while(atual != NULL) {
        printf("%d", atual->dado);
        atual = atual->anterior;
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

PLista copia_sub_lista(PLista lista, int inicio, int tam) {
    PLista l;
    PNo p;
    int tamanho = 0;

    l = copia_lista(lista);

    if(inicio == 0 && tam > 0) {
        p = l->inicio;
        for(int i = 1; i < tam && p != NULL; i++) {
            tamanho++;
            if(p->proximo == NULL){
                return NULL;
            }
            /* tamanho++; */
            p = p->proximo;
        }
        l->tamanho = tamanho + 1;
        l->fim = p;
        l->fim->proximo = NULL;
    } else if(tam == 0 && inicio > 0) {
        p = l->inicio;
        for(int i = 1; i < inicio; i++) {
            tamanho++;
            if(p->proximo == NULL) {
                return NULL;
            }
            /* tamanho++; */
            p = p->proximo;
        }
        l->tamanho -= tamanho;
        l->inicio = p;
        l->inicio->anterior = NULL;
    }

    return l;
}

PLista concatena_listas(PLista lista1, PLista lista2) {
    PLista l1;
    PLista l2;
    PLista lista;

    l1 = copia_lista(lista1);
    l2 = copia_lista(lista2);

    l1->fim->proximo = l2->inicio;
    l2->inicio->anterior = l1->fim;
    l1->fim = l2->fim;
    l2->inicio = l1->inicio;

    lista = copia_lista(l1);
    lista->tamanho = lista1->tamanho + lista2->tamanho;
    destroi_lista(l1);

    return lista;
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

PLista divide_versao_1(PLista numero1, PLista numero2) {
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

void die(char *str, int n) {
    printf("********   ");
    printf(" %s ", str);
    printf(" %d ", n);
    printf("   ********\n");
}

PLista divide(PLista numero1, PLista numero2) {
    int eh_maior;
    int tam_dif;
    PLista aux = NULL;
    PLista aux_temp = NULL;
    PLista lmulti = NULL;
    PLista lsoma = NULL;
    PLista l_unidade = NULL;
    PLista resultado = NULL;
    PLista vazia = NULL;

    if(numero2->inicio->dado == 1 && numero2->tamanho == 1) {
        resultado = copia_lista(numero1);
        return resultado;
    }

    resultado = cria_lista();
    l_unidade = cria_lista();
    l_unidade = adiciona_elemento_no_inicio(l_unidade, 1);

    eh_maior = eh_maior_numero(numero1, numero2);
    if(eh_maior == IGUAL) {
        resultado = adiciona_elemento_no_inicio(resultado, 1);
    } else if(eh_maior == MENOR) {
        resultado = adiciona_elemento_no_inicio(resultado, 0);
    } else {
        tam_dif = numero1->tamanho - numero2->tamanho;
        while(tam_dif >= 0) {
            aux = cria_lista();
            aux = adiciona_elemento_no_inicio(aux, 1);
            for(int i = 0; i < tam_dif; i++) {
                aux = adiciona_elemento_no_fim(aux, 0);
            }

            lmulti = multiplica(aux, numero2);
            eh_maior = eh_maior_numero(lmulti, numero1);
            destroi_lista(lmulti);
            if(eh_maior == MENOR || eh_maior == IGUAL) {
                aux_temp = copia_lista(aux);
                for(int i = 0; i < 10; i++) {
                    aux_temp->inicio->dado = i;
                    vazia = soma(resultado, aux_temp);
                    lsoma = multiplica(vazia, numero2);
                    destroi_lista(vazia);
                    eh_maior = eh_maior_numero(lsoma, numero1);
                    destroi_lista(lsoma);
                    if(eh_maior == MENOR || eh_maior == IGUAL) {
                        aux->inicio->dado = i;
                    }
                }
                destroi_lista(aux_temp);
                vazia = resultado;
                resultado = soma(resultado, aux);
                destroi_lista(vazia);
            }
            tam_dif -= 1;

            destroi_lista(aux);
        }
    }

    destroi_lista(l_unidade);

    return resultado;
}

PLista divide_versao_2(PLista numero1, PLista numero2) {
    int eh_maior;
    PLista aux;
    PLista temp;
    PLista resultado;
    PLista l_unidade;

    PLista divisor;
    PLista dividendo;
    PLista dividendo_a;
    PLista dividendo_b;

    int tam;
    int continua = 0;

    resultado = cria_lista();
    aux = cria_lista();
    l_unidade = cria_lista();
    l_unidade = adiciona_elemento_no_inicio(l_unidade, 1);
    temp = copia_lista(numero2);

    divisor = copia_lista(numero2);
    dividendo = copia_lista(numero1);
    dividendo_a = copia_lista(numero1);
    dividendo_b = copia_lista(numero1);

    eh_maior = eh_maior_numero(numero1, numero2);
    if(eh_maior == IGUAL) {
        resultado = adiciona_elemento_no_inicio(resultado, 1);
    } else if(eh_maior == MENOR) {
        resultado = adiciona_elemento_no_inicio(resultado, 0);
    } else {
        tam = numero2->tamanho + 1;
        continua = 1;
        while(continua == 1) {
            dividendo_a = copia_lista(dividendo);
            dividendo_a = copia_sub_lista(dividendo_a, 0, tam);

            dividendo_b = copia_lista(dividendo);
            dividendo_b = copia_sub_lista(dividendo_b, tam + 1, 0);

            eh_maior = MENOR;
            temp = cria_lista();
            while(eh_maior == MENOR || eh_maior == IGUAL) {
                temp = soma(temp, l_unidade);
                aux = multiplica(temp, divisor);
                eh_maior = eh_maior_numero(aux, dividendo_a);
            }
            temp = subtrai(temp, l_unidade);
            aux = subtrai(aux, divisor);
            resultado = adiciona_elemento_no_fim(resultado, temp->inicio->dado);

            continua = 0;
            dividendo = subtrai(dividendo_a, aux);
            if(dividendo_b != NULL) {
                dividendo = concatena_listas(dividendo, dividendo_b);
            }
            if(dividendo->tamanho > tam - 1) {
                continua = 1;
            } else {
                continua = 0;
            }
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
