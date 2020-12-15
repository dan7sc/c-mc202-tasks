#include "funcoes_auxiliares.h"

/* compara caracteres dados na entrada
   retorna TRUE se forem iguais
   e FALSE caso contrario
 */
Boolean compara_caracteres(char a, char b) {
    if(a == b) {
        return TRUE;
    }
    return FALSE;
}

/* verifica se strings são as mesmas gerando uma nova string
   com a comparação e contando o numero de erros de digitação;
   retorna 0 se palavra não possui erros de digitação,
   1 se possui um erro e 2 se possui dois ou mais erros
*/
int verifica_caracteres(char *valor, char *palavra) {
    int num_erros = 0; // numero de erros de digitação
    char palavra_gerada[N_CHAR]; // guarda palavra gerada ao se comparar as duas strings dadas na entrada
    int i, j;
    int tamanho_valor = strlen(valor);
    int tamanho_palavra = strlen(palavra);
    int tipo_corretor = 0;

    // tipo_corretor é zero quando tamanho das strings são iguais,
    // é negativo quando palavra é menor (fixa indice) e
    // é positivo quando palavra é maior (pula indicie)
    tipo_corretor = tamanho_palavra - tamanho_valor;
    for(i = 0, j = 0; i < N_CHAR && j < N_CHAR && valor[i] != '\0'; i++, j++) {
        // caractere está nas duas strings
        if(compara_caracteres(valor[i], palavra[j])) {
            palavra_gerada[i] = palavra[j];
        // caracteres são diferentes
        } else {
            palavra_gerada[i] = valor[i];
            num_erros++;
            // string palavra é menor que valor logo possui caractere faltando
            if(tipo_corretor < 0) {
                j--; // permanece no mesmo indice
            // string palavra é menor que valor logo possui caractere em excesso
            } else if(tipo_corretor > 0) {
                j++; // pula um indice
            }
        }
    }
    palavra_gerada[i] = '\0';

    // se string palavra ainda possui caracteres que não foram comparados,
    // ou seja, são caracteres em excesso, então incrementa o numero de erros
    while(j < N_CHAR && palavra[j] != '\0') {
        num_erros++;
        j++;
    }

    // se palavra gerada é igual a string valor mas o numero de caracteres diferentes é maior que 1
    // ou se as strings são direrentes então a cor é vermelha
    if((num_erros > 1 && strcmp(palavra_gerada, valor) == 0) || strcmp(palavra_gerada, valor) != 0) {
        return 2;
    }

    // se palavra gerada é igual a string valor e o numero de erros de
    // digitação é menor que 1 então a cor é verde
    if(num_erros < 1 && strcmp(palavra_gerada, valor) == 0) {
        return 0;
    }

    // caso contrario a cor é amarela
    return 1;
}

void verifica_palavra_no_dicionario(PHash hash, char *palavra) {
    int cor = 2; // cor inicial é vermelha
    int tamanho_palavra = 0;
    int tamanho_valor = 0;

    // percorre hash até o final e enquanto a cor for vermelha
    for(int i = 0; i < hash->tamanho && cor == 2; i++) {
        if(*hash->tabela[i].valor != NULL) {
            tamanho_palavra = strlen(palavra);
            tamanho_valor = strlen(*hash->tabela[i].valor);
            // somente verifica as palavras se a diferença de tamanho
            // entre elas for menor que 2 caso contrario a cor é vermelha
            // pois já há dois caracteres diferentes
            if(abs(tamanho_palavra - tamanho_valor) < 2) {
                cor = verifica_caracteres(*hash->tabela[i].valor, palavra);
            }
        }
    }

    // imprime resultado
    if(cor == 1) {
        printf("amarelo\n");
    } else if(cor == 0) {
        printf("verde\n");
    } else {
        printf("vermelho\n");
    }
}
