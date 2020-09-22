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

int compara_elementos_vetor_e_matriz
(
 int vsize, int vector[VETOR_SIZE],
 int mlin, int mcol, int matriz[MATRIZ_LIN][MATRIZ_COL],
 int indice_zero
 ) {
    int indice = 0;
    int numero_de_elementos_iguais = 0;

    for(int i = 0; i < vsize; i++) {
        indice = vector[i];

        // Obtem indice da coluna na matriz
        if(indice > 10) {
            if(indice % 10 == 0) {
                mcol = 9;
            } else {
                mcol = (indice % 10) - 1;
            }
        } else {
            mcol = indice - 1;
        }

        // Obtem indice da linha na matriz
        mlin = (indice - 1) / 10;

        if(matriz[mlin + indice_zero][mcol] == 1) {
            numero_de_elementos_iguais++;
        }
    }

    return numero_de_elementos_iguais;
}

int main() {
    int numero_de_apostadores;
    float premio_total;
    int numeros_sorteados[6];

    scanf("%d", &numero_de_apostadores);
    scanf("%f", &premio_total);

    int vsize = 6;
    int mcol = 10;
    int mlin = numero_de_apostadores * 6;
    int volante[MATRIZ_LIN][MATRIZ_COL];

    le_matriz(mlin, mcol, volante);
    le_vetor(vsize, numeros_sorteados);

    printf("%d %lf\n", numero_de_apostadores, premio_total);
    imprime_matriz(mlin, mcol, volante);
    imprime_vetor(vsize, numeros_sorteados);

    int inicio_do_volante = 0;
    int cont = 0;

    for(int i = 0; i < numero_de_apostadores; i++) {
        cont = compara_elementos_vetor_e_matriz
            (vsize, numeros_sorteados, mlin, mcol, volante, inicio_do_volante);
        inicio_do_volante += 6;
        printf("cont: %d\n", cont);
    }

    return 0;
}
