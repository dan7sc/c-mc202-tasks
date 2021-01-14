#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula {
    int num;
    char *formula;
} Celula;

void le_formula(FILE *arquivo, char *r) {
    printf("s %s\n", r);
    while(strcmp(r, ",")) {
        fscanf(arquivo, " %ms ", &r);
        printf(".%s ", r);
    }
    printf("\n");
}

int main() {
    char *nome_arquivo = NULL;
    FILE *arquivo = NULL;
    char *r = NULL;
    /* Celula c; */
    int ncol, nlin;
    int i = 0;

    scanf("%ms ", &nome_arquivo);
    scanf("%d %d", &ncol, &nlin);
    printf("%s %d %d\n", nome_arquivo, ncol, nlin);

    arquivo = fopen(nome_arquivo, "r");

    while(fscanf(arquivo, " %m[^\n,],", &r) != EOF){
        printf("%s ", r);
        if(i == ncol - 1)
            printf("\n");
        i++;
        if(i == ncol)
            i = 0;
    }

    fclose(arquivo);

    return 0;
}
