#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_de_ajuda.h"

// le numero inteiro
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
        // armazena a letra
        if(ch != '"') {
            str[i] = ch;
        } else {
            // retorna uma posicao quando encontra aspas
            // e incrementa contador de aspas
            i--;
            contador++;
        }
    }
    str[i] = '\0';
}

// compara numero com o numero do cartao e retorna
// -1 se numero é menor que o numero do cartao
// 0 se numero é igual ao numero do cartao
// 1 se numero é maior que o numero do cartao
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

// imprime string armazenada no cartao
void imprime_mensagem(void *cartao) {
    Cartao c = *(Cartao *) cartao;

    printf("%s", c.texto);
}

// concatena texto do cartao com a string que está
// sendo gerada pela concatenação dos textos de todos os cartões
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
        // aloca memoria suficiente para concatenar as duas strings
        // de tamanhos tam_cartao e tam_dado
        tam_cartao = 1 + strlen(cartao->texto);
        temp = malloc((tam_cartao + tam_dado) * sizeof(char));
        strcpy(temp, cartao->texto);
        strcat(temp, c.texto);
        free(cartao->texto);
        // cartao armazena a nova string e o novo numero
        cartao->texto = temp;
        cartao->numero += c.numero;
    }

    return cartao;
}

// soma numero com o numero do cartao
int soma(void *numero, void *cartao) {
    int num = *(int *) numero;
    Cartao c = *(Cartao *) cartao;

    return num + c.numero;
}

// libera memória da string do cartao
void destroi_texto(void *cartao) {
    Cartao *c = (Cartao *) cartao;

    free(c->texto);
}
