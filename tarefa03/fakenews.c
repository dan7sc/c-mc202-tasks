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
    printf("%s", str);
}

char *aloca_char(int n) {
    return malloc(n * sizeof(char));
}

double *aloca_double(int n) {
    return malloc(n * sizeof(double));
}

int *aloca_int(int n) {
    return malloc(n * sizeof(int));
}

char **aloca_vetor_char(int n, int m) {
    char **v = NULL;
    v = malloc(n * sizeof(char *));
    for(int i = 0; i < n; i++) {
        v[i] = malloc(m * sizeof(char));
    }
    return v;
}

double **aloca_vetor_double(int n, int m) {
    double **v = NULL;
    v = malloc(n * sizeof(double *));
    for(int i = 0; i < n; i++) {
        v[i] = malloc(m * sizeof(double));
    }
    return v;
}

int **aloca_vetor_int(int n, int m) {
    int **v = NULL;
    v = malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        v[i] = malloc(m * sizeof(int));
    }
    return v;
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

void calcula_estatistica_n_termos(int n,
                                  int m,
                                  double **v_dados,
                                  double **v_estatistica) {
    for(int i = 0; i < n; i++) {
        calcula_estatistica(m, v_dados[i], v_estatistica[i]);
    }
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

void inicializa_int(int n, int *v) {
    for(int i = 0; i < n; i++) {
        v[i] = 0;
    }
}

void imprime_estatistica(int indice,
                         double **v_estatistica) {
    for(int i = 0; i < NUM_ESTAT; i++) {
        printf("%.2lf ", v_estatistica[indice][i]);
    }
    printf("\n");
}

void imprime_termo_e_estatistica(int n,
                         char **v_termos,
                         double **v_estatistica) {
    for(int i = 0; i < n; i++) {
        imprime_string(v_termos[i]);
        printf(" ");
        imprime_estatistica(i, v_estatistica);
    }
}

void imprime_resultado(int *tam_categorias,
                       int **v_categorias,
                       char **v_termos) {
    int num = 0;

    imprime_string("\nRESULTADO:\n");
    for(int i = 0; i < NUM_CATEGORIA; i++) {
        if(i == 0) {
            imprime_string("Bot (");
        } else if(i == 1) {
            imprime_string("Surpreendente (");
        } else if(i == 2) {
            imprime_string("Normal (");
        } else if(i == 3) {
            imprime_string("Local (");
        } else if(i == 4) {
            imprime_string("Irrelevante (");
        }
        imprime_int(tam_categorias[i]);
        imprime_string("): ");
        for(int j = 0; j < tam_categorias[i]; j++) {
            num = v_categorias[i][j];
            imprime_string(v_termos[num]);
            printf(" ");
        }
        printf("\n");
    }
}

void desaloca_int(int *v) {
    free(v);
}

void desaloca_vetor_int(int n, int **v) {
    for(int i = 0; i < n; i++) {
        free(v[i]);
    }
    free(v);
}

void desaloca_vetor_char(int n, char **v) {
    for(int i = 0; i < n; i++) {
        free(v[i]);
    }
    free(v);
}

void desaloca_vetor_double(int n, double **v) {
    for(int i = 0; i < n; i++) {
        free(v[i]);
    }
    free(v);
}

int main() {
    int n_termos = 0;
    int qtd_dias = 0;
    double **vetor_dados = NULL;
    char **vetor_termos = NULL;
    double **vetor_estatistica = NULL;
    int **vetor_categorias = NULL;
    int *tam_categorias = NULL;
    int categoria = 0;
    int num = 0;

    le_int(&n_termos);
    le_int(&qtd_dias);

    vetor_termos = aloca_vetor_char(n_termos, NUM_CHAR);
    vetor_dados = aloca_vetor_double(n_termos, qtd_dias);
    vetor_estatistica = aloca_vetor_double(n_termos, qtd_dias);
    vetor_categorias = aloca_vetor_int(NUM_CATEGORIA, n_termos);
    tam_categorias = aloca_int(NUM_CATEGORIA);
    inicializa_int(NUM_CATEGORIA, tam_categorias);

    for(int i = 0; i < n_termos; i++) {
        le_string(vetor_termos[i]);
        for(int j = 0; j < qtd_dias; j++) {
            le_double(&vetor_dados[i][j]);
        }
    }

    calcula_estatistica_n_termos(n_termos,
                                 qtd_dias,
                                 vetor_dados,
                                 vetor_estatistica);

    imprime_termo_e_estatistica(n_termos, vetor_termos, vetor_estatistica);

    for(int i = 0; i < n_termos; i++) {
        categoria = avalia_categoria(vetor_estatistica[i]);
        num = tam_categorias[categoria];
        vetor_categorias[categoria][num] = i;
        tam_categorias[categoria] += 1;
    }

    imprime_resultado(tam_categorias,vetor_categorias, vetor_termos);

    desaloca_int(tam_categorias);
    desaloca_vetor_double(n_termos, vetor_dados);
    desaloca_vetor_char(n_termos, vetor_termos);
    desaloca_vetor_double(n_termos, vetor_estatistica);
    desaloca_vetor_int(NUM_CATEGORIA, vetor_categorias);

    return 0;
}
