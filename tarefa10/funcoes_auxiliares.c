#include "funcoes_auxiliares.h"

void inicializa_string(char *str, int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        str[i] = '\0';
    }
}

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

/* verifica quantos caracteres faltam para a string
   palavra se tornar igual a string valor
*/
int verifica_caracteres_faltantes(char *valor, char *palavra) {
    int eh_igual = FALSE;
    int dif = 0; // guarda quantos caracteres da string valor não estão na string palavra em ordem sequencial
    char palavra_gerada[N_CHAR]; // guarda palavra gerada ao se comparar as duas strings dadas na entrada
    int i, j;

    for(i = 0, j = 0; valor[i] != '\0' && i >= 0; i++, j++) {
        eh_igual = compara_caracteres(valor[i], palavra[j]);
        // caractere está nas duas strings
        if(eh_igual) {
            palavra_gerada[i] = palavra[j];
        // caractere não está na string palavra
        } else {
            palavra_gerada[i] = valor[i];
            dif++;
            j--; // volta um indice na string palavra
        }
    }
    palavra_gerada[i] = '\0';

    // se palavra gerada é igual a string valor mas o numero de caracteres diferentes é maior que 1
    // ou se as strings são direrentes então a cor é vermelha
    if((dif > 1 && strcmp(palavra_gerada, valor) == 0) || strcmp(palavra_gerada, valor) != 0) {
        return 2;
    }

    // se palavra gerada é igual a string valor então a cor é verde
    if(dif < 1 && strcmp(palavra_gerada, valor) == 0) {
        return 0;
    }

    // caso contrario a cor é amarela
    return 1;
}

int verifica_caracteres_excedentes(char *valor, char *palavra) {
    int eh_igual = FALSE;
    int dif = 0; // guarda quantos caracteres da string palavra não estão na string valor em ordem sequencial
    char palavra_gerada[N_CHAR]; // guarda palavra gerada ao se comparar as duas strings dadas na entrada
    int i, j;

    for(i = 0, j = 0; palavra[j] != '\0'; i++, j++) {
        eh_igual = compara_caracteres(valor[i], palavra[j]);
        // caractere está nas duas strings
        if(eh_igual) {
            palavra_gerada[i] = palavra[j];
        // caractere não está na string palavra
        } else {
            palavra_gerada[i] = valor[j];
            dif++;
            j++; // pula um indice na string palavra
        }
    }
    palavra_gerada[i] = '\0';

    // se palavra gerada é igual a string valor mas o numero de caracteres diferentes é maior que 1
    // ou se as strings são direrentes então a cor é vermelha
    if((dif > 1 && strcmp(palavra_gerada, valor) == 0) || strcmp(palavra_gerada, valor) != 0) {
        return 2;
    }

    // se palavra gerada é igual a string valor então a cor é verde
    if(dif < 1 && strcmp(palavra_gerada, valor) == 0) {
        return 0;
    }

    // caso contrario a cor é amarela
    return 1;
}

int verifica_caracteres_trocados(char *valor, char *palavra) {
    int eh_igual = FALSE;
    int dif = 0; // guarda quantos caracteres da string valor não estão na string palavra em ordem sequencial
    char palavra_gerada[N_CHAR]; // guarda palavra gerada ao se comparar as duas strings dadas na entrada
    int i, j;

    for(i = 0, j = 0; valor[i] != '\0'; i++, j++) {
        eh_igual = compara_caracteres(valor[i], palavra[j]);
        // caractere está nas duas strings
        if(eh_igual) {
            palavra_gerada[i] = palavra[i];
        // caractere não está na string palavra
        } else {
            dif++;
            palavra_gerada[i] = valor[i];
        }
    }
    palavra_gerada[i] = '\0';

    // se palavra gerada é igual a string valor mas o numero de caracteres diferentes é maior que 1
    // ou se as strings são direrentes então a cor é vermelha
    if((dif > 1 && strcmp(palavra_gerada, valor) == 0) || strcmp(palavra_gerada, valor) != 0) {
        return 2;
    }

    // se palavra gerada é igual a string valor então a cor é verde
    if(dif < 1 && strcmp(palavra_gerada, valor) == 0) {
        return 0;
    }

    // caso contrario a cor é amarela
    return 1;
}

void verifica_palavra_no_dicionario(PHash hash, char *palavra) {
    int cor = 2; // cor inicial é vermelha
    int tamanho_palavra = 0;
    int tamanho_valor = 0;

    tamanho_palavra = strlen(palavra);
    // percorre hash até o final e enquanto a cor for vermelha
    for(int i = 0; i < hash->tamanho && cor > 1; i++) {
        if(*hash->tabela[i].valor != NULL) {
            tamanho_valor = strlen(*hash->tabela[i].valor);
            // somente verifica as palavras se a diferença de tamanho
            // entre elas for menor que 2 caso contrario a cor é vermelha
            // pois já há dois caracteres diferentes
            if(abs(tamanho_palavra - tamanho_valor) < 2) {
                // se string valor é maior que string palavra verifica se há caracteres faltantes na palavra
                if(tamanho_valor > tamanho_palavra) {
                    cor = verifica_caracteres_faltantes(*hash->tabela[i].valor, palavra);
                // se string valor é menor que string palavra verifica se há caracteres excedentes na palavra
                } else if(tamanho_valor < tamanho_palavra) {
                    cor = verifica_caracteres_excedentes(*hash->tabela[i].valor, palavra);
                // se strings são de mesmo tamanho verifica se há caracteres trocados na palavra
                } else {
                    cor = verifica_caracteres_trocados(*hash->tabela[i].valor, palavra);
                }
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
