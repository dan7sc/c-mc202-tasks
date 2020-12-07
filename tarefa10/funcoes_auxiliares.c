#include "funcoes_auxiliares.h"

void inicializa_string(char *str, int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        str[i] = '\0';
    }
}

Boolean compara_caracteres(char a, char b) {
    if(a == b) {
        return TRUE;
    }
    return FALSE;
}

void gera_substring(char *string, int inicio, char *substring, int tamanho) {
    int tam = inicio + tamanho;

    inicializa_string(substring, N_CHAR);
    for(int i = inicio, j = 0; i < tam && string[i] != '\0'; i++, j++) {
        substring[j] = string[i];
    }
}

Boolean eh_substring(char *string, int inicio, char *substring) {
    int eh_igual = 0;
    int contador = 0;
    int tam_substring = strlen(substring);

    for(int i = inicio, j = 0; string[i] != '\0' && substring[j] != '\0'; i++, j++) {
        eh_igual = compara_caracteres(string[i], substring[j]);
        if(eh_igual) {
            contador++;
        }
    }
    if(contador == tam_substring) {
        return TRUE;
    }

    return FALSE;
}

Boolean contem_substring(char *string, char *substring) {
    int eh_igual = 0;
    int contador = 0;
    int tam_str = 0;
    int tam_sub = 0;
    int k = 0;

    tam_str = strlen(string);
    tam_sub = strlen(substring);

    for(k = 0; k < (tam_str - tam_sub); k++) {
        for(int i = k, j = 0; string[i] != '\0' && substring[j] != '\0'; i++, j++) {
            eh_igual = compara_caracteres(string[i], substring[j]);
            if(eh_igual) {
                contador++;
            } else {
                contador = 0;
            }
            if(contador == tam_sub) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

Boolean verifica_verossimilhanca(char *string_a, char *string_b) {
    int contador = 0;
    int total = 0;
    char substring[N_CHAR];
    int tam_sub = 1;
    int tam_str_a = strlen(string_a);

    for(tam_sub = 1; tam_str_a - tam_sub - 1 > 0; tam_sub++) {
        for(int k = 0; string_a[k] != '\0' && k < (tam_str_a - tam_sub + 1); k++) {
            inicializa_string(substring, tam_sub);
            gera_substring(string_b, k, substring, tam_sub);
            if(contem_substring(string_a, substring)) {
                contador++;
            }
            total++;
        }
    }

    if((200 * contador / total) > 70) {
        return TRUE;
    }

    return FALSE;
}

int verifica_caracteres_faltantes(char *valor, char *palavra) {
    int contador = 0;
    int eh_igual = 0;
    int dif = 0;
    char palavra_gerada[N_CHAR];
    int i, j;

    for(i = 0, j = 0; valor[i] != '\0' && i >= 0; i++, j++) {
        eh_igual = compara_caracteres(valor[i], palavra[j]);
        if(eh_igual) {
            contador++;
            palavra_gerada[i] = palavra[j];
        } else {
            palavra_gerada[i] = valor[i];
            dif++;
            j--;
        }
    }
    palavra_gerada[i] = '\0';

    if(strcmp(palavra_gerada, valor) != 0) {
        return -1;
    }

    return dif > 1 ? 0 : 1;
}

int verifica_caracteres_excedentes(char *valor, char *palavra) {
    int contador = 0;
    int eh_igual = 0;
    int dif = 0;
    char palavra_gerada[N_CHAR];
    int i, j;

    for(i = 0, j = 0; valor[i] != '\0'; i++, j++) {
        eh_igual = compara_caracteres(valor[i], palavra[j]);
        if(eh_igual) {
            contador++;
            palavra_gerada[i] = palavra[j];
        } else {
            palavra_gerada[i] = valor[j];
            dif++;
            j++;
        }
    }
    palavra_gerada[i] = '\0';

    if(strcmp(palavra_gerada, valor) != 0) {
        return -1;
    }

    return dif > 1 ? 0 : 1;
}

int verifica_caracteres_trocados(char *valor, char *palavra) {
    int contador = 0;
    int eh_igual = 0;
    int dif = 0;
    char palavra_gerada[N_CHAR];
    int i, j;

    for(i = 0, j = 0; valor[i] != '\0'; i++, j++) {
        eh_igual = compara_caracteres(valor[i], palavra[j]);
        if(eh_igual) {
            contador++;
            palavra_gerada[i] = palavra[i];
        } else {
            dif++;
            palavra_gerada[i] = valor[i];
        }
    }
    palavra_gerada[i] = '\0';

    if(strcmp(palavra_gerada, valor) != 0) {
        return -1;
    }

    return dif > 1 ? 0 : 1;
}

void verifica_palavra_no_dicionario(PHash hash, char *palavra) {
    int cor = -1;
    char *temp = NULL;
    int tamanho_palavra = 0;
    int tamanho_valor = 0;
    Boolean eh_verossimel = FALSE;

    temp = busca(hash, palavra);
    if(temp) {
        cor = 2;
    }
    temp = NULL;

    tamanho_palavra = strlen(palavra);
    for(int i = 0; i < hash->tamanho && cor < 0; i++) {
        if(*hash->tabela[i].valor != NULL) {
            tamanho_valor = strlen(*hash->tabela[i].valor);
            eh_verossimel = verifica_verossimilhanca(*hash->tabela[i].valor, palavra);
            if(eh_verossimel && abs(tamanho_palavra - tamanho_valor) < 2 ) {
                if(tamanho_valor > tamanho_palavra) {
                    cor = verifica_caracteres_faltantes(*hash->tabela[i].valor, palavra);
                } else if(tamanho_valor < tamanho_palavra) {
                    cor = verifica_caracteres_excedentes(*hash->tabela[i].valor, palavra);
                } else {
                    cor = verifica_caracteres_trocados(*hash->tabela[i].valor, palavra);
                }
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
