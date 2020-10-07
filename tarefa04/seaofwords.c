#include <stdio.h>
#include <stdlib.h>

#define N_CHAR 20
#define TRUE 1
#define FALSE 0

void le_int(int *num) {
    scanf("%d", num);
}

void le_string(char *str) {
    scanf("%s", str);
}

void le_matriz_char(int lin, int col,  char **matriz) {
    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            scanf(" %c", &matriz[i][j]);
        }
    }
}

void le_matriz_string(int n,  char **matriz) {
    for(int i = 0; i < n; i++) {
        scanf("%s", matriz[i]);
    }
}

void inicializa_matriz_char(int lin, int col,  char **matriz) {
    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            matriz[i][j] = 0;
        }
    }
}

char **aloca_matriz(int n, int m) {
    char **v = NULL;
    v = malloc(n * sizeof(char *));
    for(int i = 0; i < n; i++) {
        v[i] = malloc(m * sizeof(char));
    }
    return v;
}

void imprime_int(int n) {
    printf("%d", n);
}

void imprime_char(char c) {
    printf("%c", c);
}

void imprime_string(char *str) {
    printf("%s", str);
}

void imprime_matriz_char(int lin, int col,  char **matriz) {
    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

void imprime_matriz_string(int n,  char **matriz) {
    for(int i = 0; i < n; i++) {
        for (int j = 0; matriz[i][j] != '\0'; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

int esta_nos_limites(int lin, int col, int lin_index, int col_index) {
    if(lin_index >= 0 && col_index >= 0 && lin_index < lin && col_index < col) {
        return TRUE;
    }
    return FALSE;
}

int busca_palavra_recursivo(int lin,
                            int col,
                            char **matriz,
                            int i,
                            int j,
                            char *palavra,
                            int index,
                            char **visitados) {
    int para_baixo = 0;
    int para_direita = 0;
    int para_cima = 0;
    int para_esquerda = 0;

    if(esta_nos_limites(lin, col, i, j) == 1 &&
       palavra[index] != '\0' &&
       visitados[i][j] != '*') {
        if(matriz[i][j] != palavra[index]) {
            return 0;
        }

        if(matriz[i][j] == palavra[index]) {
            visitados[i][j] = '*';
            index++;

            i++;
            para_baixo = busca_palavra_recursivo(lin,
                                                 col,
                                                 matriz,
                                                 i,
                                                 j,
                                                 palavra,
                                                 index,
                                                 visitados);
            i--;

            j++;
            para_direita = busca_palavra_recursivo(lin,
                                                   col,
                                                   matriz,
                                                   i,
                                                   j,
                                                   palavra,
                                                   index,
                                                   visitados);
            j--;

            i--;
            para_cima = busca_palavra_recursivo(lin,
                                                col,
                                                matriz,
                                                i,
                                                j,
                                                palavra,
                                                index,
                                                visitados);
            i++;

            j--;
            para_esquerda = busca_palavra_recursivo(lin,
                                                    col,
                                                    matriz,
                                                    i,
                                                    j,
                                                    palavra,
                                                    index,
                                                    visitados);
            j++;
        }
        visitados[i][j] = '0';
    }

    if(para_baixo) return TRUE;
    if(para_direita) return TRUE;
    if(para_cima) return TRUE;
    if(para_esquerda) return TRUE;

    if(palavra[index] == '\0') {
        return TRUE;
    }

    index--;
    return FALSE;
}

void busca_palavra(int lin,
                   int col,
                   char **matriz,
                   char *palavra,
                   char **visitados) {
    int index = 0;
    int eh_encontrada = 0;

    for(int i = 0; i < lin && !eh_encontrada; i++) {
        for(int j = 0; j < col && !eh_encontrada; j++) {
            if(matriz[i][j] == palavra[index]) {
                eh_encontrada = busca_palavra_recursivo(lin,
                                                        col,
                                                        matriz,
                                                        i,
                                                        j,
                                                        palavra,
                                                        index,
                                                        visitados);
            }
        }
    }
    if(eh_encontrada == 0) printf("nao\n");
    else if(eh_encontrada == 1) printf("sim\n");
}

int main() {
    int lin = 0;
    int col = 0;
    int n_palavras = 0;
    char **texto = NULL;
    char **palavras = NULL;
    char **visitados = NULL;

    le_int(&lin);
    le_int(&col);
    le_int(&n_palavras);

    texto = aloca_matriz(lin, col);
    palavras = aloca_matriz(n_palavras, N_CHAR);
    visitados = aloca_matriz(lin, col);

    le_matriz_char(lin, col, texto);
    le_matriz_string(n_palavras, palavras);

    /* imprime_int(lin); */
    /* printf(" "); */
    /* imprime_int(col); */
    /* printf(" "); */
    /* imprime_int(n_palavras); */
    /* printf("\n"); */
    /* imprime_matriz_char(lin, col, texto); */
    /* imprime_matriz_string(n_palavras, palavras); */

    for(int i = 0; i < n_palavras; i++) {
        inicializa_matriz_char(lin, col, visitados);
        busca_palavra(lin, col, texto, palavras[i], visitados);
    }

    return 0;
}
