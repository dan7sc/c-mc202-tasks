#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_de_ajuda.h"

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

void imprime_mensagem(void *cartao) {
    Cartao c = *(Cartao *) cartao;

    printf("%s", c.texto);
}

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
        tam_cartao = 1 + strlen(cartao->texto);
        temp = malloc((tam_cartao + tam_dado) * sizeof(char));
        strcpy(temp, cartao->texto);
        strcat(temp, c.texto);
        free(cartao->texto);
        cartao->texto = temp;
        cartao->numero += c.numero;
    }

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
