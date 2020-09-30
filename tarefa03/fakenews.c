#include <stdio.h>
#include <stdlib.h>

#define NUM_CHAR 25
#define NUM_ESTAT 4

void le_int(int *num) {
    scanf("%d", num);
}

void le_double(double *num) {
    scanf("%lf", num);
}

void le_string(char *str) {
    scanf("%s", str);
}

char *aloca_char(int n) {
    return (char *)malloc(n * sizeof(char));
}

double *aloca_double(int n) {
    return (double *)malloc(n * sizeof(double));
}

char **aloca_vetor_char(int n) {
    return (char **)malloc(n * sizeof(char *));
}

double **aloca_vetor_double(int n) {
    return (double **)malloc(n * sizeof(double *));
}

double procura_maximo(int qtd_numeros,
                      double *vetor_de_numeros) {
    double max = 0.0;

    for(int i = 0; i < qtd_numeros; i++) {
        if(max < vetor_de_numeros[i]) {
            max = vetor_de_numeros[i];
        }
    }

    return max;
}

int main() {
    int n_termos = 0;
    int qtd_dias = 0;
    double **vetor_dados = NULL;
    char **vetor_termos = NULL;
    double **vetor_estatistica = NULL;

    le_int(&n_termos);
    le_int(&qtd_dias);

    vetor_termos = aloca_vetor_char(n_termos);
    vetor_dados = aloca_vetor_double(n_termos);
    for(int i = 0; i < n_termos; i++) {
        vetor_termos[i] = aloca_char(NUM_CHAR);
        le_string(vetor_termos[i]);
        vetor_dados[i] = aloca_double(qtd_dias);
        for(int j = 0; j < qtd_dias; j++) {
            le_double(&vetor_dados[i][j]);
        }
    }

    vetor_estatistica = aloca_vetor_double(n_termos);
    for(int i = 0; i < n_termos; i++) {
        vetor_estatistica[i] = aloca_double(qtd_dias);
        vetor_estatistica[i][0] = procura_maximo(qtd_dias, vetor_dados[i]);
    }

    printf("%d %d\n", n_termos, qtd_dias);
    for(int i = 0; i < n_termos; i++) {
        printf("%s ", vetor_termos[i]);
        for(int j = 0; j < qtd_dias; j++) {
            printf("%.2lf ", vetor_dados[i][j]);
        }
        printf("\n");
        printf("stat %.2lf\n", vetor_estatistica[i][0]);
    }

    return 0;
}
