#include <stdio.h>
#include <stdlib.h>

#define N_CHAR 20
#define TRUE 1
#define FALSE 0

typedef struct _livro {
    char **texto;
    int lin;
    int col;
} Livro;

typedef struct _palavras {
    char *palavra;
    int indice_letra;
} Palavras;

void le_int(int *num) {
    scanf("%d", num);
}

void le_string(char *str) {
    scanf("%s", str);
}

void le_matriz_char(int lin, int col,  char **matriz) {
    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            scanf(" %c", &matriz[i][j]);
        }
    }
}

void le_palavras(int n, Palavras *palavras) {
    for(int i = 0; i < n; i++) {
        scanf("%s", palavras[i].palavra);
    }
}

void inicializa_matriz_char(int lin, int col,  char **matriz) {
    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            matriz[i][j] = 0;
        }
    }
}

char **aloca_matriz(int n, int m) {
    char **v = NULL;
    v = malloc(n * sizeof(char *));
    for(int i = 0; i < n; i++) {
        v[i] = malloc(m * sizeof(char));
    }
    return v;
}

Palavras *aloca_palavras(int n, int m) {
    Palavras *plv;
    plv = malloc(n * sizeof(Palavras));
    for(int i = 0; i < n; i++) {
        plv[i].indice_letra = 0;
        plv[i].palavra = malloc(m * sizeof(char));
    }
    return plv;
}

void desaloca_matriz(int n, char **matriz) {
    for(int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void desaloca_palavras(int n, Palavras *plv) {
    for(int i = 0; i < n; i++) {
        free(plv[i].palavra);
    }
    free(plv);
}

void imprime_string(char *str) {
    printf("%s", str);
}

int esta_nos_limites(int lin, int col, int lin_index, int col_index) {
    if(lin_index >= 0 && col_index >= 0 && lin_index < lin && col_index < col) {
        return TRUE;
    }
    return FALSE;
}

int busca_palavra_recursivo(Livro lv,
                            int i, int j,
                            Palavras plv,
                            char **visitados) {
    if(esta_nos_limites(lv.lin, lv.col, i, j) == 1 &&
       plv.palavra[plv.indice_letra] != '\0' &&
       visitados[i][j] != '*') {
        if(lv.texto[i][j] != plv.palavra[plv.indice_letra]) {
            return 0;
        }

        if(lv.texto[i][j] == plv.palavra[plv.indice_letra]) {
            visitados[i][j] = '*';
            plv.indice_letra++;

            if(busca_palavra_recursivo(lv, i + 1, j, plv, visitados)) {
                return TRUE;
            }
            if(busca_palavra_recursivo(lv, i, j + 1, plv, visitados)) {
                return TRUE;
            }
            if(busca_palavra_recursivo(lv, i - 1, j, plv, visitados)) {
                return TRUE;
            }
            if(busca_palavra_recursivo(lv, i, j - 1, plv, visitados)) {
                return TRUE;
            }
        }
        visitados[i][j] = '0';
    }

    if(plv.palavra[plv.indice_letra] == '\0') {
        return TRUE;
    }

    plv.indice_letra--;
    return FALSE;
}

void busca_palavra(Livro lv,
                   Palavras plv) {
    int eh_encontrada = 0;
    char **visitados = NULL;

    visitados = aloca_matriz(lv.lin, lv.col);
    inicializa_matriz_char(lv.lin, lv.col, visitados);

    for(int i = 0; i < lv.lin && !eh_encontrada; i++) {
        for(int j = 0; j < lv.col && !eh_encontrada; j++) {
            if(lv.texto[i][j] == plv.palavra[plv.indice_letra]) {
                eh_encontrada = busca_palavra_recursivo(lv, i, j, plv, visitados);
            }
        }
    }

    if(eh_encontrada) {
        printf("sim\n");
    } else {
        printf("nao\n");
    }

    desaloca_matriz(lv.lin, visitados);
}

int main() {
    int qtd_palavras;
    Livro livro;
    Palavras *palavras;

    le_int(&livro.lin);
    le_int(&livro.col);
    le_int(&qtd_palavras);

    livro.texto = aloca_matriz(livro.lin, livro.col);
    palavras = aloca_palavras(qtd_palavras, N_CHAR);

    le_matriz_char(livro.lin, livro.col, livro.texto);
    le_palavras(qtd_palavras, palavras);

    for(int i = 0; i < qtd_palavras; i++) {
        busca_palavra(livro, palavras[i]);
    }

    desaloca_matriz(livro.lin, livro.texto);
    desaloca_palavras(qtd_palavras, palavras);

    return 0;
}
