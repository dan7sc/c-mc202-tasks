#include <stdio.h>
#include <stdlib.h>

#define N_CHAR 20

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

int main() {
    int lin = 0;
    int col = 0;
    int n_palavras = 0;
    char **matriz = NULL;
    char **palavras = NULL;

    le_int(&lin);
    le_int(&col);
    le_int(&n_palavras);

    matriz = aloca_matriz(lin, col);
    le_matriz_char(lin, col, matriz);

    palavras = aloca_matriz(n_palavras, N_CHAR);
    le_matriz_string(n_palavras, palavras);

    imprime_int(lin);
    printf(" ");
    imprime_int(col);
    printf(" ");
    imprime_int(n_palavras);
    printf("\n");
    imprime_matriz_char(lin, col, matriz);
    imprime_matriz_string(n_palavras, palavras);

    return 0;
}
