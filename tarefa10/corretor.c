#include "hash.h"

void inicializa_string(char *str) {
    for(int i = 0; i < N_CHAR; i++) {
        str[i] = '\0';
    }
}

Boolean compara_caracteres(char a, char b) {
    if(a == b) {
        return TRUE;
    }
    return FALSE;
}

char *gera_substring(char *string, int inicio, int tamanho) {
    char *substring = malloc(tamanho * sizeof(char));
    int j = 0;

    for(int i = inicio; i < (inicio + tamanho) && string[i] != '\0'; i++) {
        substring[j++] = string[i];
    }

    return substring;
}

Boolean eh_substring(char *string, int inicio, char *sub_string) {
    int igual = 0;
    int contador = 0;

    for(int i = inicio, j = 0; string[i] != '\0' && sub_string[j] != '\0'; i++, j++) {
        igual = compara_caracteres(string[i], sub_string[j]);
        if(igual == TRUE) {
            contador++;
        }
    }
    if(contador == (int)strlen(sub_string)) {
        return TRUE;
    }

    return FALSE;
}

Boolean contem_string_substring(char *string, char *substring) {
    int igual = 0;
    int contador = 0;
    int tam_str = (int)strlen(string);
    int tam_sub = (int)strlen(substring);

    for(int k = 0; k < (tam_str - tam_sub); k++) {
        for(int i = k, j = 0; string[i] != '\0' && substring[j] != '\0'; i++, j++) {
            igual = compara_caracteres(string[i], substring[j]);
            if(igual == TRUE) {
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

int conta_substrings_B_em_A(char *string_a, char *string_b) {
    int contador;
    int tam_sub_b = (int)strlen(string_b) / 3;
    int tam_str_a = (int)strlen(string_a);

    for(int k = 0; string_b[k] != '\0'; k += 3) {
        contador = 0;
        for(int i = 0; string_a[i] != '\0' && i < tam_str_a - tam_sub_b; i++) {
            if(eh_substring(string_a, i, string_b) == TRUE) {
                contador++;
                break;
            }
        }
    }

    return contador;
}

Boolean verifica_verossimilhanca(char *string_a, char *string_b) {
    int contador = 0;
    int total = 0;
    char *substring[N_CHAR];
    int tam_sub = 1;
    int tam_str_a = (int)strlen(string_a);
    /* int tam_str_b = (int)strlen(string_b); */
    int eh_palavra_igual = 0;

    for(tam_sub = 1; tam_str_a - tam_sub - 1 > 0; tam_sub++) {
        for(int k = 0; string_a[k] != '\0' && k < (tam_str_a - tam_sub + 1); k++) {
            *substring = gera_substring(string_b, k, tam_sub);
            if(contem_string_substring(string_a, *substring) == TRUE) {
                contador++;
            }
            total++;
        }
    }

    /* for(tam_sub = 1; tam_str_a - tam_sub - 1 > 0; tam_sub++) { */
    /*     for(int k = 0; string_a[k] != '\0' && k < (tam_str_b - tam_sub + 1); k++) { */
    /*         *substring = gera_substring(string_a, k, tam_sub); */
    /*         if(contem_string_substring(string_b, *substring) == TRUE) { */
    /*             contador++; */
    /*         } */
    /*         total++; */
    /*     } */
    /* } */

    eh_palavra_igual = (200 * contador) / total;
    /* printf("    >>>>>>>>  ........   %s   %d   %s\n", string_b, eh_palavra_igual, string_a); */

    if(eh_palavra_igual > 70) {
        return TRUE;
    }

    return FALSE;
}

int verifica_remocao_caractere(char *valor, char *palavra) {
    int contador = 0;
    int igual = 0;
    int dif = 0;
    char palavra_gerada[N_CHAR];
    int i, j, comp;

    for(i = 0, j = 0; valor[i] != '\0' && i >= 0; i++, j++) {
        igual = compara_caracteres(valor[i], palavra[j]);
        if(igual == TRUE) {
            contador++;
            palavra_gerada[i] = palavra[j];
        } else {
            palavra_gerada[i] = valor[i];
            dif++;
            j--;
        }
    }
    palavra_gerada[i] = '\0';

    /* printf("    >>>>>>>>     %s %d\n", palavra_gerada, dif); */
    comp = strcmp(palavra_gerada, valor);
    if(comp == 0 && dif > (int)strlen(valor) - 1) {
        return -1;
    }
    if(comp != 0) {
        return -1;
    }

    return dif > 1 ? 0 : 1;
}

int verifica_insercao_caractere(char *valor, char *palavra) {
    int contador = 0;
    int igual = 0;
    int dif = 0;
    char palavra_gerada[N_CHAR];
    int i, j, comp;

    for(i = 0, j = 0; valor[i] != '\0'; i++, j++) {
        igual = compara_caracteres(valor[i], palavra[j]);
        if(igual == TRUE) {
            contador++;
            palavra_gerada[i] = palavra[j];
        } else {
            palavra_gerada[i] = valor[j];
            dif++;
            j++;
        }
    }
    palavra_gerada[i] = '\0';

    /* printf("    >>>>>>>>     %s %d\n", palavra_gerada, dif); */
    comp = strcmp(palavra_gerada, valor);
    if(comp == 0 && dif > (int)strlen(valor) - 1) {
        return -1;
    }
    if(comp != 0) {
        return -1;
    }

    return dif > 1 ? 0 : 1;
}

int verifica_troca_caracteres(char *valor, char *palavra) {
    int contador = 0;
    int igual = 0;
    int dif = 0;
    char palavra_gerada[N_CHAR];
    int i, j, comp;

    for(i = 0, j = 0; valor[i] != '\0'; i++, j++) {
        igual = compara_caracteres(valor[i], palavra[j]);
        if(igual == TRUE) {
            contador++;
            palavra_gerada[i] = palavra[i];
        } else {
            dif++;
            palavra_gerada[i] = valor[i];
        }
    }
    palavra_gerada[i] = '\0';

    /* printf("    >>>>>>>>     %s %d\n", palavra_gerada, dif); */

    comp = strcmp(palavra_gerada, valor);
    if(comp == 0 && dif > (int)strlen(valor) - 1) {
        return -1;
    }
    if(comp != 0) {
        return -1;
    }

    return dif > 1 ? 0 : 1;
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
            /* if(abs(tamanho_palavra - tamanho_valor) < 2 ) { */
            if(verifica_verossimilhanca(*hash->tabela[i].valor, palavra) == TRUE && abs(tamanho_palavra - tamanho_valor) < 2 ) {
                /* printf("**** %d %d %d %s %s\n", cor, tamanho_palavra, tamanho_valor, palavra, *hash->tabela[i].valor); */
                if(tamanho_valor > tamanho_palavra) {
                    /* printf("MAIOR\n"); */
                    cor = verifica_remocao_caractere(*hash->tabela[i].valor, palavra);
                } else if(tamanho_valor < tamanho_palavra) {
                    /* printf("MENOR\n"); */
                    cor = verifica_insercao_caractere(*hash->tabela[i].valor, palavra);
                } else {
                    /* printf("IGUAL\n"); */
                    cor = verifica_troca_caracteres(*hash->tabela[i].valor, palavra);
                }
                /* break; */
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
