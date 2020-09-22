#include <stdio.h>

#define VETOR_SIZE 6
#define MATRIZ_LIN 1000
#define MATRIZ_COL 10

void le_vetor(int size, int vetor[VETOR_SIZE]) {
    for(int i = 0; i < size; i++) {
        scanf("%d", &vetor[i]);
    }
}

void imprime_vetor(int size, int vetor[VETOR_SIZE]) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

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
    int mlin = 6;
    int mcol = 10;
    int vsize = 6;
    int matriz[MATRIZ_LIN][MATRIZ_COL];
    int vetor[VETOR_SIZE];

    le_matriz(mlin, mcol, matriz);
    le_vetor(vsize, vetor);

    imprime_matriz(mlin, mcol, matriz);
    imprime_vetor(vsize, vetor);

    return 0;
}
