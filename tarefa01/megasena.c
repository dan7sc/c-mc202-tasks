#include <stdio.h>

#define MATRIZ_LIN 1000
#define MATRIZ_COL 10

void le_matriz(int lin, int col,  int matriz[MATRIZ_LIN][MATRIZ_COL]) {
    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
}

void imprime_matriz(int lin, int col, int matriz[MATRIZ_LIN][MATRIZ_COL]) {
    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int lin = 6;
    int col = 10;
    int matriz[MATRIZ_LIN][MATRIZ_COL];

    le_matriz(lin, col, matriz);
    imprime_matriz(lin, col, matriz);

    return 0;
}
