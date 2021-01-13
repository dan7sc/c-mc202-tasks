#include <stdio.h>

int main() {
    char *nome_arquivo = NULL;
    FILE *arquivo = NULL;
    int r;
    int ncol, nlin;
    int i = 0;

    scanf("%ms ", &nome_arquivo);
    scanf("%d %d", &ncol, &nlin);
    printf("%s %d %d\n", nome_arquivo, ncol, nlin);

    arquivo = fopen(nome_arquivo, "r");

    while(fscanf(arquivo, " %d ,", &r) != EOF){
        printf("%5d ", r);
        if(i == ncol - 1)
            printf("\n");
        i++;
        if(i == ncol)
            i = 0;
    }

    fclose(arquivo);

    return 0;
}
