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
    int elemento = 0;
    int numero_de_elementos_iguais = 0;

    for(int i = 0; i < VETOR_SIZE; i++) {
        elemento = vector[i];

        // Obtem indice da linha na matriz
        mlin = (elemento - 1) / 10;

        // Obtem indice da coluna na matriz
        if(elemento > 10) {
            if(elemento % 10 == 0) {
                mcol = 9;
            } else {
                mcol = (elemento % 10) - 1;
            }
        } else {
            mcol = elemento - 1;
        }

        if(matriz[mlin + indice_zero][mcol] == 1) {
            numero_de_elementos_iguais++;
        }
    }

    return numero_de_elementos_iguais;
}

void conta_premiados
(
 int numeros_sorteados_do_apostador,
 int quantidade_de_premiados[]
 ) {
    if(numeros_sorteados_do_apostador == 6) {
        ++quantidade_de_premiados[0];
    } else if(numeros_sorteados_do_apostador == 5) {
        ++quantidade_de_premiados[1];
    } else if(numeros_sorteados_do_apostador == 4) {
        ++quantidade_de_premiados[2];
    }
}

void distribui_premios
(
 float premio,
 int numeros_sorteados_do_apostador,
 int quantidade_de_premiados[]
 ) {
    double premios_possiveis[] = { 0.62*premio, 0.19*premio, 0.19*premio, 0.00 };

    if(numeros_sorteados_do_apostador == 6) {
        printf("%.2lf\n", premios_possiveis[0] / quantidade_de_premiados[0]);
    } else if(numeros_sorteados_do_apostador == 5) {
        printf("%.2lf\n", premios_possiveis[1] / quantidade_de_premiados[1]);
    } else if(numeros_sorteados_do_apostador == 4) {
        printf("%.2lf\n", premios_possiveis[2] / quantidade_de_premiados[2]);
    } else {
        printf("%.2lf\n", premios_possiveis[3]);
    }
}

int main() {
    int numero_de_apostadores;
    double premio_total;
    int numeros_sorteados[VETOR_SIZE];
    int volante[MATRIZ_LIN][MATRIZ_COL];
    int numeros_sorteados_do_apostador[NUM_APOSTADORES];
    int quantidade_de_premiados[] = { 0, 0, 0 };
    int inicio_submatriz = 0;
    int mlin;

    scanf("%d", &numero_de_apostadores);
    scanf("%lf", &premio_total);

    mlin = numero_de_apostadores * 6;

    le_matriz(mlin, MATRIZ_COL, volante);
    le_vetor(VETOR_SIZE, numeros_sorteados);

    for(int i = 0; i < numero_de_apostadores; i++) {
        numeros_sorteados_do_apostador[i] =
            compara_elementos_vetor_e_submatriz(
                                                numeros_sorteados,
                                                volante,
                                                inicio_submatriz);
        inicio_submatriz += 6;
    }

    for(int i = 0; i < numero_de_apostadores; i++) {
        conta_premiados(
                        numeros_sorteados_do_apostador[i],
                        quantidade_de_premiados);
    }

    for(int i = 0; i < numero_de_apostadores; i++) {
        distribui_premios(
                          premio_total,
                          numeros_sorteados_do_apostador[i],
                          quantidade_de_premiados);
    }

    return 0;
}
