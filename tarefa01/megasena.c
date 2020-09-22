#include <stdio.h>

#define NUM_APOSTADORES 1000
#define VETOR_SIZE 6
#define MATRIZ_LIN 6000
#define MATRIZ_COL 10

void le_vetor(int size, int vetor[]) {
    for(int i = 0; i < size; i++) {
        scanf("%d", &vetor[i]);
    }
}

void le_matriz(int lin, int col,  int matriz[][MATRIZ_COL]) {
    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
}

int compara_elementos_vetor_e_submatriz
(
 int vector[],
 int matriz[][MATRIZ_COL],
 int indice_zero
 ) {
    int mlin = indice_zero;
    int mcol = 0;
    int indice = 0;
    int numero_de_elementos_iguais = 0;

    for(int i = 0; i < VETOR_SIZE; i++) {
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

void conta_premiados
(
 int numero_de_apostadores,
 int numeros_sorteados[],
 int numeros_sorteados_por_apostador[],
 int volante[][MATRIZ_COL],
 int quantidade_de_premiados[]
) {
    int inicio_matriz = 0;

    for(int i = 0; i < numero_de_apostadores; i++) {
        numeros_sorteados_por_apostador[i] =
            compara_elementos_vetor_e_submatriz(
                                             numeros_sorteados,
                                             volante,
                                             inicio_matriz);

        inicio_matriz += 6;

        if(numeros_sorteados_por_apostador[i] == 6) {
            ++quantidade_de_premiados[0];
        } else if(numeros_sorteados_por_apostador[i] == 5) {
            ++quantidade_de_premiados[1];
        } else if(numeros_sorteados_por_apostador[i] == 4) {
            ++quantidade_de_premiados[2];
        }
    }
}

void distribui_premios
(
 int numero_de_apostadores,
 float premio,
 int numeros_sorteados_por_apostador[],
 int quantidade_de_premiados[]
 ) {
    double premios_possiveis[] = { 0.62*premio, 0.19*premio, 0.19*premio, 0.00 };

    for(int i = 0; i < numero_de_apostadores; i++) {
        if(numeros_sorteados_por_apostador[i] == 6) {
            printf("%.2lf\n", premios_possiveis[0] / quantidade_de_premiados[0]);
        } else if(numeros_sorteados_por_apostador[i] == 5) {
            printf("%.2lf\n", premios_possiveis[1] / quantidade_de_premiados[1]);
        } else if(numeros_sorteados_por_apostador[i] == 4) {
            printf("%.2lf\n", premios_possiveis[2] / quantidade_de_premiados[2]);
        } else {
            printf("%.2lf\n", premios_possiveis[3]);
        }
    }
}

void mostra_premios_recebidos
(
 int numero_de_apostadores,
 float premio,
 int numeros_sorteados[],
 int volante[][MATRIZ_COL]
 ) {
    int numeros_sorteados_por_apostador[NUM_APOSTADORES];
    int quantidade_de_premiados[] = { 0, 0, 0 };

    conta_premiados(
                    numero_de_apostadores,
                    numeros_sorteados,
                    numeros_sorteados_por_apostador,
                    volante,
                    quantidade_de_premiados);

    distribui_premios(
                      numero_de_apostadores,
                      premio,
                      numeros_sorteados_por_apostador,
                      quantidade_de_premiados);
}

int main() {
    int numero_de_apostadores;
    double premio_total;
    int numeros_sorteados[VETOR_SIZE];

    scanf("%d", &numero_de_apostadores);
    scanf("%lf", &premio_total);

    int mlin = numero_de_apostadores * 6;
    int volante[MATRIZ_LIN][MATRIZ_COL];

    le_matriz(mlin, MATRIZ_COL, volante);
    le_vetor(VETOR_SIZE, numeros_sorteados);

    mostra_premios_recebidos(
                             numero_de_apostadores,
                             premio_total,
                             numeros_sorteados,
                             volante);

    return 0;
}
