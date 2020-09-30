#include <stdio.h>
#include <stdlib.h>

#define N 25

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
    int num_termos = 0;
    int qtd_dias = 0;
    char *nome = NULL;
    double *num = NULL;

    le_int(&num_termos);
    le_int(&qtd_dias);
    nome = (char *) malloc(N * sizeof(char));
    le_string(nome);
    num = (double *) malloc(qtd_dias * sizeof(double));
    for(int i = 0; i < qtd_dias; i++) {
        le_double(&num[i]);
    }

    printf("%d %d\n", num_termos, qtd_dias);
    printf("%s", nome);
    printf("\n");
    for(int i = 0; i < qtd_dias; i++) {
        printf("%.15lf\n", num[i]);
    }

    return 0;
}
