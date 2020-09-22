#include <stdio.h>

#define NUM_APOSTADORES 1000
#define VETOR_SIZE 6
#define MATRIZ_LIN 6000
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

void conta_premiados
(
 int numeros_sorteados,
 int quantidade_de_premiados[]
) {
    if(numeros_sorteados == 6) {
        ++quantidade_de_premiados[0];
    } else if(numeros_sorteados == 5) {
        ++quantidade_de_premiados[1];
    } else if(numeros_sorteados == 4) {
        ++quantidade_de_premiados[2];
    }
}

void distribui_premios
(
 int numero_de_apostadores,
 double premios_possiveis[],
 int numeros_sorteados_por_apostador[],
 int quantidade_de_premiados[]
 ) {
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
 int numero_de_apostadores, float premio,
 int vsize, int numeros_sorteados[VETOR_SIZE],
 int mlin, int mcol, int volante[MATRIZ_LIN][MATRIZ_COL]
 ) {
    int inicio_zero = 0;
    int numeros_sorteados_por_apostador[NUM_APOSTADORES];
    int quantidade_de_premiados[] = { 0, 0, 0 };
    double premios_possiveis[] = { 0.62*premio, 0.19*premio, 0.19*premio, 0.00 };

    for(int i = 0; i < numero_de_apostadores; i++) {
        numeros_sorteados_por_apostador[i] = compara_elementos_vetor_e_matriz
            (vsize, numeros_sorteados, mlin, mcol, volante, inicio_zero);

        inicio_zero += 6;

        conta_premiados
            (numeros_sorteados_por_apostador[i],
             quantidade_de_premiados);
    }

    distribui_premios
        (numero_de_apostadores,
         premios_possiveis,
         numeros_sorteados_por_apostador,
         quantidade_de_premiados);
}

int main() {
    int numero_de_apostadores;
    double premio_total;
    int numeros_sorteados[6];

    scanf("%d", &numero_de_apostadores);
    scanf("%lf", &premio_total);

    int vsize = 6;
    int mcol = 10;
    int mlin = numero_de_apostadores * 6;
    int volante[MATRIZ_LIN][MATRIZ_COL];

    le_matriz(mlin, mcol, volante);
    le_vetor(vsize, numeros_sorteados);

    /* printf("%d %lf\n", numero_de_apostadores, premio_total); */
    /* imprime_matriz(mlin, mcol, volante); */
    /* imprime_vetor(vsize, numeros_sorteados); */

    mostra_premios_recebidos
        (numero_de_apostadores, premio_total, vsize, numeros_sorteados, mlin, mcol, volante);

    return 0;
}
