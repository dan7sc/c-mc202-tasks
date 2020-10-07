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

typedef struct _palavra {
    char *palavra;
    int indice;
} Palavra;

typedef struct _palavras {
    Palavra *lista;
    int qtd;
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

void le_palavras(Palavras palavras) {
    for(int i = 0; i < palavras.qtd; i++) {
        scanf("%s", palavras.lista[i].palavra);
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

Palavra *aloca_palavras(int n, int m) {
    Palavras v;
    v.lista = malloc(n * sizeof(Palavra));
    for(int i = 0; i < n; i++) {
        v.lista[i].palavra = malloc(m * sizeof(char));
    }
    return v.lista;
}

void imprime_int(int n) {
    printf("%d", n);
}

void imprime_char(char c) {
    printf("%c", c);
}

void imprime_string(char *str) {
    printf("%s", str);
}

void imprime_matriz_char(int lin, int col,  char **matriz) {
    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

void imprime_matriz_string(int n,  char **matriz) {
    for(int i = 0; i < n; i++) {
        for (int j = 0; matriz[i][j] != '\0'; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

void imprime_palavras(int n,  Palavra *lista) {
    for(int i = 0; i < n; i++) {
        for (int j = 0; lista[i].palavra[j] != '\0'; j++) {
            printf("%c", lista[i].palavra[j]);
        }
        printf("\n");
    }
}

int esta_nos_limites(int lin, int col, int lin_index, int col_index) {
    if(lin_index >= 0 && col_index >= 0 && lin_index < lin && col_index < col) {
        return TRUE;
    }
    return FALSE;
}

int busca_palavra_recursivo(Livro lv,
                            int i, int j,
                            Palavra lst,
                            char **visitados) {
    if(esta_nos_limites(lv.lin, lv.col, i, j) == 1 &&
       lst.palavra[lst.indice] != '\0' &&
       visitados[i][j] != '*') {
        if(lv.texto[i][j] != lst.palavra[lst.indice]) {
            return 0;
        }

        if(lv.texto[i][j] == lst.palavra[lst.indice]) {
            visitados[i][j] = '*';
            lst.indice++;

            if(busca_palavra_recursivo(lv, i + 1, j, lst, visitados)) {
                return TRUE;
            }
            if(busca_palavra_recursivo(lv, i, j + 1, lst, visitados)) {
                return TRUE;
            }
            if(busca_palavra_recursivo(lv, i - 1, j, lst, visitados)) {
                return TRUE;
            }
            if(busca_palavra_recursivo(lv, i, j - 1, lst, visitados)) {
                return TRUE;
            }
        }
        visitados[i][j] = '0';
    }

    if(lst.palavra[lst.indice] == '\0') {
        return TRUE;
    }

    lst.indice--;
    return FALSE;
}

void busca_palavra(Livro lv,
                   Palavra lst) {
    int eh_encontrada = 0;
    char **visitados = NULL;

    visitados = aloca_matriz(lv.lin, lv.col);
    inicializa_matriz_char(lv.lin, lv.col, visitados);

    for(int i = 0; i < lv.lin && !eh_encontrada; i++) {
        for(int j = 0; j < lv.col && !eh_encontrada; j++) {
            if(lv.texto[i][j] == lst.palavra[lst.indice]) {
                eh_encontrada = busca_palavra_recursivo(lv, i, j, lst, visitados);
            }
        }
    }
    if(eh_encontrada) {
        printf("sim\n");
    } else {
        printf("nao\n");
    }
}

int main() {
    Livro livro;
    Palavras palavras;

    le_int(&livro.lin);
    le_int(&livro.col);
    le_int(&palavras.qtd);

    livro.texto = aloca_matriz(livro.lin, livro.col);
    palavras.lista = aloca_palavras(palavras.qtd, N_CHAR);

    le_matriz_char(livro.lin, livro.col, livro.texto);
    le_palavras(palavras);

    /* imprime_int(livro.lin); */
    /* printf(" "); */
    /* imprime_int(livro.col); */
    /* printf(" "); */
    /* imprime_int(palavras.qtd); */
    /* printf("\n"); */
    /* imprime_matriz_char(livro.lin, livro.col, livro.texto); */
    /* imprime_palavras(palavras.qtd, palavras.lista); */

    for(int i = 0; i < palavras.qtd; i++) {
        busca_palavra(livro, palavras.lista[i]);
    }

    return 0;
}
