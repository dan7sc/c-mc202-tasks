#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_CHAR 25
#define NUM_ESTAT 4
#define NUM_CATEGORIA 5

#define MAXIMO 0
#define MINIMO 1
#define MEDIA 2
#define DPADRAO 3

#define BOT 0
#define SURPREENDENTE 1
#define NORMAL 2
#define LOCAL 3
#define IRRELEVANTE 4

void le_int(int *num) {
    scanf("%d", num);
}

void le_double(double *num) {
    scanf("%lf", num);
}

void le_string(char *str) {
    scanf("%s", str);
}

void imprime_int(int n) {
    printf("%d", n);
}

void imprime_string(char *str) {
    printf("%s ", str);
}

char *aloca_char(int n) {
    return (char *)malloc(n * sizeof(char));
}

double *aloca_double(int n) {
    return (double *)malloc(n * sizeof(double));
}

int *aloca_int(int n) {
    return (int *)malloc(n * sizeof(int));
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

double procura_minimo(int qtd_numeros,
                      double *vetor_de_numeros) {
    double min = 101;

    for(int i = 0; i < qtd_numeros; i++) {
        if(min > vetor_de_numeros[i]) {
            min = vetor_de_numeros[i];
        }
    }

    return min;
}

double calcula_media(int qtd_numeros,
                     double *vetor_de_numeros) {
    double media = 0.0;

    for(int i = 0; i < qtd_numeros; i++) {
        media += vetor_de_numeros[i];
    }

    return media / qtd_numeros;
}

double calcula_desvio_padrao(int qtd_numeros,
                             double *vetor_de_numeros,
                             double media) {
    double soma = 0.0;
    double x = 0.0;
    double dp = 0.0;

    for(int i = 0; i < qtd_numeros; i++) {
        x = vetor_de_numeros[i] - media;
        soma += x * x;
    }
    dp = sqrt(soma / qtd_numeros);

    return dp;
}

void calcula_estatistica(int n,
                         double *v_dados,
                         double *v_estatistica) {
    v_estatistica[MAXIMO] = procura_maximo(n, v_dados);
    v_estatistica[MINIMO] = procura_minimo(n, v_dados);
    v_estatistica[MEDIA] = calcula_media(n, v_dados);
    v_estatistica[DPADRAO] = calcula_desvio_padrao(n,
                                                   v_dados,
                                                   v_estatistica[MEDIA]);
}

void imprime_estatistica(int indice,
                         double **v_estatistica) {
    for(int i = 0; i < NUM_ESTAT; i++) {
        printf("%.2lf ", v_estatistica[indice][i]);
    }
    printf("\n");
}

int avalia_categoria(double *v_estatistica) {
    if(v_estatistica[MEDIA] >= 60 &&
       v_estatistica[DPADRAO] > 15) {
        return BOT;
    } else if(v_estatistica[MEDIA] >= 60 &&
              v_estatistica[DPADRAO] <= 15) {
        return SURPREENDENTE;
    } else if(v_estatistica[MEDIA] < 60 &&
             v_estatistica[MAXIMO] >= 80 &&
             v_estatistica[MINIMO] > 20) {
        return NORMAL;
    } else if(v_estatistica[MEDIA] < 60 &&
              v_estatistica[MAXIMO] >= 80 &&
              v_estatistica[MINIMO] <= 20) {
        return LOCAL;
    } else if(v_estatistica[MEDIA] < 60 &&
              v_estatistica[MAXIMO] < 80) {
        return IRRELEVANTE;
    }
    return -1;
}

int main() {
    int n_termos = 0;
    int qtd_dias = 0;
    double **vetor_dados = NULL;
    char **vetor_termos = NULL;
    double **vetor_estatistica = NULL;
    /* char **vetor_categoria = NULL; */
    /* int *tam_categoria = NULL; */
    int categoria = -1;

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
        calcula_estatistica(qtd_dias, vetor_dados[i], vetor_estatistica[i]);
    }

    for(int i = 0; i < n_termos; i++) {
        imprime_string(vetor_termos[i]);
        imprime_estatistica(i, vetor_estatistica);
    }

    imprime_string("\nRESULTADO:\n");
    /* vetor_categoria = aloca_vetor_char(NUM_CATEGORIA); */
    /* tam_categoria = aloca_int(NUM_CATEGORIA);g */
    for(int i = 0; i < n_termos; i++) {
        categoria = avalia_categoria(vetor_estatistica[i]);
        /* vetor_categoria[i] = aloca_char(NUM_CHAR); */
        imprime_int(categoria);
        imprime_string(" ");
    }
    imprime_string("\n");

    return 0;
}
