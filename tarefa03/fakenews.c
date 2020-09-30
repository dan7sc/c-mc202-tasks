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

int main() {
    int n_termos = 0;
    int qtd_dias = 0;
    double **vetor_dados = NULL;
    char **vetor_termos = NULL;

    le_int(&n_termos);
    le_int(&qtd_dias);

    vetor_termos = (char **) malloc(n_termos * sizeof(char *));
    vetor_dados = (double **) malloc(n_termos * sizeof(double *));
    for(int i = 0; i < n_termos; i++) {
        vetor_termos[i] = (char *) malloc(NUM_CHAR * sizeof(char));
        le_string(vetor_termos[i]);
        vetor_dados[i] = (double *) malloc(qtd_dias * sizeof(double));
        for(int j = 0; j < qtd_dias; j++) {
            le_double(&vetor_dados[i][j]);
        }
    }

    printf("%d %d\n", n_termos, qtd_dias);
    for(int i = 0; i < n_termos; i++) {
        printf("%s ", vetor_termos[i]);
        for(int j = 0; j < qtd_dias; j++) {
            printf("%.2lf ", vetor_dados[i][j]);
        }
        printf("\n");
    }

    return 0;
}
