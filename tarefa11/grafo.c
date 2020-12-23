#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fila.h"
#include "grafo.h"

PVertice cria_vertice(PGrafo grafo, Vertice v) {
    PVertice vertice = calloc(1, sizeof(Vertice));

    vertice->info.posicao.x = v.info.posicao.x;
    vertice->info.posicao.y = v.info.posicao.y;
    vertice->info.ponto = v.info.ponto;;
    vertice->adjacencia = cria_lista();
    vertice->id = grafo->n;

    return vertice;
}

PGrafo cria_grafo() {
    PGrafo grafo = calloc(1, sizeof(Grafo));

    grafo->n = 0;
    grafo->vertice = NULL;

    return grafo;
}

void destroi_vertices(PVertice vertice) {
    if(vertice != NULL) {
        destroi_vertices(vertice->proximo);
        destroi_lista(vertice->adjacencia);
        free(vertice);
    }
}

void destroi_grafo(PGrafo grafo) {
    destroi_vertices(grafo->vertice);
    free(grafo);
}

PGrafo insere_vertice(PGrafo grafo, Vertice v) {
    PVertice novo_vertice = cria_vertice(grafo, v);
    PVertice atual = NULL;

    if(grafo->n == 0) {
        grafo->vertice = novo_vertice;
        grafo->n++;
        return grafo;
    }

    atual = grafo->vertice;
    while(atual->proximo != NULL) {
        atual = atual->proximo;
    }

    atual->proximo = novo_vertice;
    adiciona_arestas(grafo, novo_vertice);
    grafo->n++;

    return grafo;
}

void adiciona_arestas(PGrafo grafo, PVertice v) {
    PVertice atual;

    atual = grafo->vertice;
    while(atual != NULL && atual->id != v->id) {
        insere_aresta(atual, v);
        atual = atual->proximo;
    }
}

void insere_aresta(PVertice u, PVertice v) {
    u->adjacencia = adiciona_na_lista(u->adjacencia, v);
    v->adjacencia = adiciona_na_lista(v->adjacencia, u);
}

PVertice busca_vertice(PGrafo grafo, int id) {
    PVertice v = NULL;
    PVertice atual = grafo->vertice;

    while(atual != NULL) {
        if(atual->id == id) {
            v = atual;
            return v;
        }
        atual = atual->proximo;
    }
    return 0;
}

int tem_aresta(PVertice u, PVertice v) {
    PNo atual;

    atual = v->adjacencia;
    while(atual != NULL) {
        if(u == (PVertice)atual->dado) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

int distancia_aresta(PVertice u, PVertice v) {
    float p1 = pow(u->info.posicao.x - v->info.posicao.x, 2);
    float p2 = pow(u->info.posicao.y - v->info.posicao.y, 2);

    return ceil(sqrt(p1 + p2));
}

void imprime(void *v) {
    PVertice vv = (PVertice)v;
    printf("%d ", vv->id);
}

/* void bfs(PGrafo grafo, PVertice s) { */
/*     PVertice w, v; */
/*     int w_id, v_id; */
/*     int *pai = malloc(grafo->n * sizeof(int)); */
/*     int *visitado = malloc(grafo->n * sizeof(int)); */
/*     PFila fila = cria_fila(); */

/*     for(v_id = 0; v_id < grafo->n; v_id++) { */
/*         pai[v_id] = -1; */
/*         visitado[v_id] = 0; */
/*     } */

/*     fila = enfileira(fila, s); */
/*     pai[s->id] = s->id; */
/*     visitado[s->id] = 1; */

/*     while(!fila_vazia(fila)) { */
/*         v = desenfileira(fila); */
/*         v_id = v->id; */
/*         w = grafo->vertice; */
/*         for(w_id = 0; w_id < grafo->n; w_id++) { */
/*             if(tem_aresta(v, w) == 1 && visitado[w_id] == 0) { */
/*                 visitado[w_id] = 1; */
/*                 pai[w_id] = v_id; */
/*                 fila = enfileira(fila, w); */
/*             } */
/*             w = w->proximo; */
/*         } */
/*     } */

/*     for(int i = 0; i < grafo->n; i++) { */
/*         printf("%d ", pai[i]); */
/*     } */
/*     printf("\n"); */

/*     destroi_fila(fila); */
/*     free(visitado); */
/*     free(pai); */
/* } */

/* void bfs(PGrafo grafo, PVertice origem) { */
/*     PVertice w, v; */
/*     int v_id; */
/*     int *pai = malloc(grafo->n * sizeof(int)); */
/*     int *visitado = malloc(grafo->n * sizeof(int)); */
/*     PFila fila = cria_fila(); */

/*     for(v_id = 0; v_id < grafo->n; v_id++) { */
/*         pai[v_id] = -1; */
/*         visitado[v_id] = 0; */
/*     } */

/*     fila = enfileira(fila, origem); */
/*     pai[origem->id] = origem->id; */
/*     visitado[origem->id] = 1; */

/*     while(!fila_vazia(fila)) { */
/*         v = desenfileira(fila); */
/*         w = (PVertice) v->adjacencia->dado; */
/*         for(PNo atual = v->adjacencia; atual != NULL; atual = atual->proximo) { */
/*             w = (PVertice) atual->dado; */
/*             printf("\n%d - %d %d", v->id, w->id, w->info.ponto); */
/*             if(tem_aresta(v, w) && !visitado[w->id]) { */
/*                 visitado[w->id] = 1; */
/*                 pai[w->id] = v->id; */
/*                 fila = enfileira(fila, w); */
/*             } */
/*         } */
/*     } */

/*     printf("\n"); */
/*     for(int i = 0; i < grafo->n; i++) { */
/*         printf("%d ", pai[i]); */
/*     } */
/*     printf("\n"); */

/*     destroi_fila(fila); */
/*     free(visitado); */
/*     free(pai); */
/* } */

/* void bfs(PGrafo grafo, PVertice origem) { */
/*     PVertice w, v; */
/*     int *pai = malloc(grafo->n * sizeof(int)); */
/*     int *visitado = malloc(grafo->n * sizeof(int)); */
/*     PFila fila = cria_fila(); */
/*     int **m = calloc(1, grafo->n * sizeof(int *)); */
/*     int n = grafo->n; */
/*     int achou = 0; */
/*     int *menor_visitado = calloc(1, grafo->n * sizeof(int)); */
/*     int *posicao_lugia = calloc(1, grafo->n * sizeof(int)); */
/*     int resultado = 0; */

/*     for(int i = 0; i < n; i++) { */
/*         m[i] = calloc(1, n * sizeof(int)); */
/*     } */

/*     for(int i = 0; i < n; i++) { */
/*         v = busca_vertice(grafo, i); */
/*         for(int j = 0; j < n; j++) { */
/*             w = busca_vertice(grafo, j); */
/*             if(tem_aresta(v, w)) { */
/*                 if(v->info.ponto == Lugia) { */
/*                     posicao_lugia[v->id] = 1; */
/*                     /\* m[i][j] = -1 * distancia_aresta(v, w); *\/ */
/*                 } /\* else { *\/ */
/*                     m[i][j] = distancia_aresta(v, w); */
/*                 /\* } *\/ */
/*             } */

/*         } */
/*     } */

/*     for(int i = 0; i < n; i++) { */
/*         for(int j = 0; j < n; j++) { */
/*             printf("%3d ", m[i][j]); */
/*         } */
/*         printf("\n"); */
/*     } */

/*     printf("\n"); */
/*     for(int j = 0; j < n; j++) { */
/*         printf("%3d ", posicao_lugia[j]); */
/*     } */
/*     printf("\n"); */

/*     for(int i = 0; i < n; i++) { */
/*         pai[i] = -1; */
/*         visitado[i] = 0; */
/*     } */

/*     v = origem; */
/*     /\* fila = enfileira(fila, v); *\/ */
/*     pai[v->id] = v->id; */
/*     visitado[v->id] = 1; */

/*     int menor = (int) INFINITY; */
/*     int id_menor; */
/*     while(achou == 0) { */
/*         if(id_menor) */
/*         for(int i = 0; i < n; i++) { */
/*             if(menor > m[v->id][i] && i != v->id && !menor_visitado[i]) { */
/*                 menor = m[v->id][i]; */
/*                 id_menor = i; */
/*             } */
/*         } */
/*         menor_visitado[id_menor] = 1; */
/*         pai[id_menor] = v->id; */
/*         visitado[id_menor] = 1; */
/*         resultado = menor; */
/*         printf(">>>> %d %d\n", menor, id_menor); */

/*         for(int i = 0; i < n; i++) { */
/*             if(menor > m[id_menor][i] && menor < resultado && i != id_menor) { */
/*                 menor = m[v->id][i]; */
/*                 id_menor = i; */
/*             } */
/*         } */
/*         if(menor_visitado[id_menor] == 1) { */
/*             achou = 1; */
/*         } */
/*     } */
/*     printf("res: %d\n", resultado); */

/*     /\* while(!fila_vazia(fila)) { *\/ */
/*     /\*     v = desenfileira(fila); *\/ */
/*     /\*     /\\* printf("%d ", v->id); *\\/ *\/ */
/*     /\*     w = (PVertice) v->adjacencia->dado; *\/ */
/*     /\*     for(PNo atual = v->adjacencia; atual != NULL; atual = atual->proximo) { *\/ */
/*     /\*         w = (PVertice) atual->dado; *\/ */
/*     /\*         /\\* printf("\n%4d   - %4d %4d %4d", v->id, w->id, w->info.ponto, distancia_aresta(w, v)); *\\/ *\/ */
/*     /\*         if(tem_aresta(v, w) && !visitado[w->id]) { *\/ */
/*     /\*             /\\* printf("\n%d - %d %d", v->id, w->id, w->info.ponto); *\\/ *\/ */
/*     /\*             visitado[w->id] = 1; *\/ */
/*     /\*             pai[w->id] = v->id; *\/ */
/*     /\*             fila = enfileira(fila, w); *\/ */
/*     /\*         } *\/ */
/*     /\*     } *\/ */
/*     /\* } *\/ */

/*     printf("\n"); */
/*     for(int i = 0; i < n; i++) { */
/*         printf("%d ", pai[i]); */
/*     } */
/*     printf("\n"); */

/*     for(int i = 0; i < n; i++) { */
/*         free(m[i]); */
/*     } */
/*     free(m); */

/*     destroi_fila(fila); */
/*     free(visitado); */
/*     free(pai); */
/*     free(posicao_lugia); */
/*     free(menor_visitado); */
/* } */


int **cria_matriz_quadrada(int n) {
    int **m = calloc(1, n * sizeof(int *));

    for(int i = 0; i < n; i++) {
        m[i] = calloc(1, n * sizeof(int));
    }

    return m;
}

void grafo_em_matriz(int **m, PGrafo grafo) {
    PVertice w, v;

    for(int i = 0; i < grafo->n; i++) {
        v = busca_vertice(grafo, i);
        for(int j = 0; j < grafo->n; j++) {
            w = busca_vertice(grafo, j);
            if(tem_aresta(v, w)) {
                m[i][j] = distancia_aresta(v, w);
            }
        }
    }
}

void imprime_matriz_quadrada(int **m, int n) {
    for(int i = -1; i < n; i++) {
        printf("[%02d] ", i);
    }
    printf("\n");

    for(int i = 0; i < n; i++) {
        printf("[%02d] ", i);
        for(int j = 0; j < n; j++) {
            printf("%4d ", m[i][j]);
        }
        printf("\n");
    }
}

/* void bfs(PGrafo grafo, PVertice origem, PVertice destino) { */
/*     PVertice predecessor, alvo; */
/*     int aresta_predecessor, aresta_alvo; */
/*     int *pai = malloc(grafo->n * sizeof(int)); */
/*     int *visitado = malloc(grafo->n * sizeof(int)); */
/*     PFila fila = cria_fila(); */
/*     int maior_aresta; */
/*     int **m = cria_matriz_quadrada(grafo->n); */

/*     grafo_em_matriz(m, grafo); */
/*     imprime_matriz_quadrada(m, grafo->n); */

/*     for(int i = 0; i < grafo->n; i++) { */
/*         pai[i] = -1; */
/*         visitado[i] = 0; */
/*     } */

/*     fila = enfileira(fila, origem); */

/*     pai[origem->id] = origem->id; */
/*     pai[destino->id] = origem->id; */

/*     visitado[origem->id] = 1; */
/*     visitado[destino->id] = 1; */

/*     /\* maior_aresta = distancia_aresta(origem, destino); *\/ */

/*     predecessor = origem; */
/*     alvo = destino; */

/*     /\* maior_aresta = 1; *\/ */
/*     while(!fila_vazia(fila)) { */
/*         predecessor = desenfileira(fila); */
/*         printf("#### pred_id: %2d   alvo_id: %2d\n", predecessor->id, alvo->id); */
/*         printf("**** LOOP ****\n"); */
/*         for(int i = 0; i < grafo->n; i++) { */
/*             aresta_predecessor = m[predecessor->id][i]; */
/*             aresta_alvo = m[i][alvo->id]; */
/*             /\* if(!visitado[i] && aresta_predecessor + aresta_alvo <= maior_aresta) { *\/ */
/*             if(!visitado[i] && aresta_predecessor < maior_aresta && aresta_alvo < maior_aresta) { */
/*             /\* if(!visitado[i] && aresta_predecessor <= maior_aresta && aresta_alvo <= maior_aresta) { *\/ */
/*             /\* if(!visitado[i] && aresta_predecessor < maior_aresta && aresta_alvo < maior_aresta && aresta_predecessor + aresta_alvo <= maior_aresta) { *\/ */
/*                 printf("#### pred_id: %2d   alvo_id: %2d\n", predecessor->id, alvo->id); */
/*                 printf("#### pred(%d->%d): %2d   alvo(%d->%d): %2d\n", predecessor->id, i, aresta_predecessor, i, alvo->id, aresta_alvo); */

/*                 maior_aresta = aresta_predecessor > aresta_alvo ? aresta_predecessor : aresta_alvo; */

/*                 visitado[i] = 1; */
/*                 pai[i] = predecessor->id; */
/*                 pai[alvo->id] = i; */

/*                 predecessor = busca_vertice(grafo, i); */
/*                 fila = enfileira(fila, predecessor); */
/*             } */
/*         } */
/*         /\* maior_aresta++; *\/ */
/*         printf("novo predecessor: %2d\n", predecessor->id); */
/*         printf("maior_aresta: %2d\n", maior_aresta); */
/*     } */

/*     for(int i = 0; i < grafo->n; i++) { */
/*         printf("[%d] %d  ", i, visitado[i]); */
/*     } */
/*     printf("\n"); */

/*     printf("\n"); */
/*     for(int i = 0; i < grafo->n; i++) { */
/*         printf("[%d] %d  ", i, pai[i]); */
/*     } */
/*     printf("\n"); */

/*     printf("\n"); */
/*     maior_aresta = destino->id; */
/*     while(maior_aresta != origem->id) { */
/*         /\* printf("%d <-- ", maior_aresta); *\/ */
/*         printf("%d <-(%d)- ", maior_aresta , m[pai[maior_aresta]][maior_aresta]); */
/*         maior_aresta = pai[maior_aresta]; */

/*     } */
/*     printf("%d\n", maior_aresta); */

/*     destroi_fila(fila); */
/*     free(visitado); */
/*     free(pai); */
/* } */

int bfs(PGrafo grafo, PVertice origem, PVertice destino) {
    PVertice predecessor, alvo;
    int /*aresta_predecessor,*/ aresta_alvo;
    int *pai = malloc(grafo->n * sizeof(int));
    int *visitado = malloc(grafo->n * sizeof(int));
    /* PFila fila = cria_fila(); */
    int maior_aresta;
    int **m = cria_matriz_quadrada(grafo->n);
    int n_vertices;
    /* int aresta; */
    /* int atual; */

    grafo_em_matriz(m, grafo);
    imprime_matriz_quadrada(m, grafo->n);

    for(int i = 0; i < grafo->n; i++) {
        pai[i] = -1;
        visitado[i] = 0;
    }

    /* fila = enfileira(fila, origem); */

    pai[origem->id] = origem->id;
    /* pai[destino->id] = origem->id; */

    visitado[origem->id] = 1;
    /* visitado[destino->id] = 1; */

    predecessor = origem;
    /* alvo = destino; */
    alvo = origem;

    maior_aresta = 0;
    /* atual = 0; */
    while(alvo->id != destino->id) {
        for(int i = 0; i < grafo->n; i++) {
            pai[i] = -1;
            visitado[i] = 0;
        }
        pai[origem->id] = origem->id;
        visitado[origem->id] = 1;
        predecessor = origem;

        /* while(!fila_vazia(fila)) { */
        /* aresta = 0; */
        maior_aresta++;
        /* predecessor = desenfileira(fila); */
        /* if(distancia_aresta(origem, destino) <= maior_aresta) { */
        /*     maior_aresta = distancia_aresta(origem, destino); */
        /*     return maior_aresta; */
        /* } */

        for(n_vertices = 1; n_vertices < grafo->n; n_vertices++) {
            /* printf("..%2d %4d %3d\n", n_vertices, alvo->id, destino->id); */
            for(int i = 0; i < grafo->n && alvo->id != destino->id; i++) {
                if(!visitado[i]) {
                    aresta_alvo = m[predecessor->id][i];
                    /* if(i == 5) printf("........ %d %4d %4d\n", i, predecessor->id, m[predecessor->id][i]); */
                    /* printf("..%2d %4d %3d\n", maior_aresta, aresta_alvo, i); */
                    if(aresta_alvo <= maior_aresta) {
                        if(i == 5) printf("........ %d %4d %4d\n", i, predecessor->id, m[predecessor->id][i]);
                        printf(".. maior:%2d   alvo:%3d   []:%2d%4d\n", maior_aresta, aresta_alvo, predecessor->id, i);
                        alvo = busca_vertice(grafo, i);
                        printf("........ %4d\n", alvo->id);
                        visitado[i] = 1;
                        pai[i] = predecessor->id;
                        predecessor = alvo;
                        break;
                    }
                }
            }
            printf("........ %4d\n", alvo->id);
            /* printf("\n"); */
            /* for(int i = 0; i < grafo->n; i++) { */
            /*     printf("[%d] %d  ", i, pai[i]); */
            /* } */
            /* printf("\n"); */
            /* printf("\n"); */
            /* for(int i = 0; i < grafo->n; i++) { */
            /*     printf("[%d] %d  ", i, visitado[i]); */
            /* } */
            /* printf("\n"); */
        }
    }
            /* if(!visitado[i] && !visitado[i+1] && aresta_alvo <= maior_aresta) { */
            /*     /\* printf("** i: %2d  --  visitado: %2d\n", i, visitado[i]); *\/ */
            /*     /\* printf("** predecessor: %2d  --  alvo: %2d\n", aresta_predecessor, aresta_alvo); *\/ */
            /*     /\* if(atual < aresta_predecessor || atual < aresta_alvo) { *\/ */
            /*     /\*     atual = aresta_predecessor > aresta_alvo ? aresta_predecessor : aresta_alvo; *\/ */
            /*     /\* } *\/ */

            /*     visitado[i] = 1; */
            /*     pai[i] = predecessor->id; */
            /*     pai[alvo->id] = i; */

            /*     /\* predecessor = busca_vertice(grafo, i); *\/ */
            /*     /\* fila = enfileira(fila, predecessor); *\/ */
            /*     /\* aresta += 1; *\/ */
            /* } */

            /* int id = destino->id; */
            /* int nv = 0; */
            /* while(id != origem->id && nv < grafo->n) { */
            /*     printf("%d <-( %d )- ", id , m[pai[id]][id]); */
            /*     id = pai[id]; */
            /*     nv++; */
            /* } */
            /* printf("%d\n", id); */

        /* printf("....\n"); */
        /* int id = destino->id; */
        /* n_vertices = 0; */
        /* while(id != origem->id && n_vertices < grafo->n) { */
        /*     printf("%d <-( %d )- ", id , m[pai[id]][id]); */
        /*     id = pai[id]; */
        /*     n_vertices++; */
        /* } */
        /* printf("%d\n", id); */


        /* printf("** atual: %d\n", atual); */
        /* printf("** aresta: %d\n", aresta); */
        /* if(aresta > 0) { */
        /*     /\* printf("............ BREAK ............\n"); *\/ */
        /*     break; */
        /* } */

        /* if(predecessor->id == origem->id) { */
        /*     fila = enfileira(fila, origem); */
        /* } */
    /* } */

    /* for(int i = 0; i < grafo->n; i++) { */
    /*     printf("[%d] %d  ", i, visitado[i]); */
    /* } */
    /* printf("\n\n"); */
    /* for(int i = 0; i < grafo->n; i++) { */
    /*     printf("[%d] %d  ", i, pai[i]); */
    /* } */
    /* printf("\n\n"); */
    /* int id = destino->id; */
    /* while(id != origem->id) { */
    /*     printf("%d <-(%d)- ", id , m[pai[id]][id]); */
    /*     id = pai[id]; */
    /* } */
    /* printf("%d\n", id); */

    /* maior_aresta = 0; */
    /* for(int i = grafo->n - 1; i > 0; i--) { */
    /*     if(pai[i] > 0) { */
    /*         if(maior_aresta < m[pai[i]][i]) { */
    /*             maior_aresta = m[pai[i]][i]; */
    /*         } */
    /*     } */
    /* } */

    /* destroi_fila(fila); */
    free(visitado);
    free(pai);
    for(int i = 0; i < grafo->n; i++) {
        free(m[i]);
    }
    free(m);

    return maior_aresta;
}


void imprime_vertices(PGrafo grafo, void (*imprime)(void *)) {
    PVertice atual = grafo->vertice;

    printf("Tamanho do grafo: %d\n", grafo->n);
    while(atual != NULL) {
        printf("%d %f %f %d\n", atual->id, atual->info.posicao.x, atual->info.posicao.y, atual->info.ponto);
        imprime_lista(atual->adjacencia, imprime);
        atual = atual->proximo;
    }
}
