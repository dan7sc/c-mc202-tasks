#include "hash.h"

Boolean compara_caracteres(char a, char b) {
    if(a == b) {
        return TRUE;
    }
    return FALSE;
}

int verifica_remocao_caractere(char *valor, char *palavra) {
    int contador = 0;
    int igual = 0;
    int dif = 0;

    for(int i = 0, j = 0; i < (int)strlen(palavra); i++, j++) {
        igual = compara_caracteres(valor[i], palavra[j]);
        if(igual == TRUE) {
            contador += igual;
        } else {
            dif++;
            j--;
        }
    }

    if(dif > (int)strlen(valor) - 3 && contador < (int)strlen(valor) - 3) {
    /* if(dif > (int)strlen(valor) - 1) { */
        return -1;
    }
    return dif > 1 ? 0 : 1;

    /* if(contador > (int)strlen(valor) - 1) { */
    /* /\* if(contador == (int)strlen(valor)) { *\/ */
    /*     return dif > 1 ? 0 : 1; */
    /* } */

    /* return -1; */
}

int verifica_insercao_caractere(char *valor, char *palavra) {
    int contador = 0;
    int igual = 0;
    int dif = 0;

    for(int i = 0, j = 0; i < (int)strlen(valor); i++, j++) {
        igual = compara_caracteres(valor[i], palavra[j]);
        if(igual == TRUE) {
            contador += igual;
        } else {
            dif++;
            i--;
        }
    }

    /* if(dif > (int)strlen(valor) - 3 && contador < (int)strlen(valor) - 3) { */
    /* /\* if(dif > (int)strlen(valor) - 1) { *\/ */
    /*     return -1; */
    /* } */
    /* return dif > 1 ? 0 : 1; */

    if(contador > (int)strlen(valor) - 1) {
    /* if(contador == (int)strlen(valor)) { */
        return dif > 1 ? 0 : 1;
    }

    return -1;
}

int verifica_troca_caracteres(char *valor, char *palavra) {
    int contador = 0;
    int igual = 0;
    int dif = 0;

    for(int i = 0, j = 0; i < (int)strlen(valor); i++, j++) {
        igual = compara_caracteres(valor[i], palavra[j]);
        if(igual == TRUE) {
            contador += igual;
        } else {
            dif++;
        }
    }

    if(dif > (int)strlen(valor) - 1) {
        return -1;
    }
    return dif > 1 ? 0 : 1;


    /* if(contador == (int)strlen(valor)) { */
    /*     return dif > 1 ? 0 : 1; */
    /* } */

    /* return -1; */

    /* if(dif > 1) { */
    /*     return 0; */
    /* } else if(dif == 1) { */
    /*     return 1; */
    /* } else { */
    /*     return -1; */
    /* } */
}

void verifica_palavra_dicionario(PHash hash, char *palavra) {
    int cor = -1;
    char *temp = NULL;
    int tamanho_palavra = 0;
    int tamanho_valor = 0;

    temp = busca(hash, palavra);
    if(temp) {
        cor = 2;
    }

    tamanho_palavra = strlen(palavra);
    for(int i = 0; i < hash->tamanho && cor < 0; i++) {
        if(*hash->tabela[i].valor != NULL) {
            tamanho_valor = strlen(*hash->tabela[i].valor);
            /* printf("**** %d %d %d %s %s\n", cor, tamanho_palavra, tamanho_valor, palavra, *hash->tabela[i].valor); */
            if(tamanho_valor > tamanho_palavra) {
                cor = verifica_remocao_caractere(*hash->tabela[i].valor, palavra);
            } else if(tamanho_valor < tamanho_palavra) {
                cor = verifica_insercao_caractere(*hash->tabela[i].valor, palavra);
            } else {
                cor = verifica_troca_caracteres(*hash->tabela[i].valor, palavra);
            }
        }
    }

    if(cor < 1) {
        printf("vermelho\n");
    } else if(cor == 1) {
        printf("amarelo\n");
    } else {
        printf("verde\n");
    }
}

int main() {
    PHash h;
    int num_palavras_dicionario = 0;
    int num_palavras_texto = 0;
    char *palavra_texto = NULL;
    char *palavra = NULL;
    char *temp = NULL;

    scanf("%d %d", &num_palavras_dicionario, &num_palavras_texto);

    h = cria_tabela_hash(num_palavras_dicionario);
    for(int i = 0; i < num_palavras_dicionario; i++) {
        palavra = malloc(N_CHAR * sizeof(char));
        scanf("%s", palavra);
        h = insere(h, palavra);
    }

    for(int i = 0; i < num_palavras_texto; i++) {
        palavra_texto = malloc(N_CHAR * sizeof(char));
        scanf("%s", palavra_texto);
        verifica_palavra_dicionario(h, palavra_texto);
    }

    /* imprime_tabela_hash(h); */

    free(temp);
    destroi_tabela_hash(h);

    return 0;
}
