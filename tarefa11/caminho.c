#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"
#include "heap.h"

void imprime_adjacencia(void *dado) {
    Vertice v = *(Vertice *) dado;

    printf("==> %d %f %f %d\n", v.id, v.info.posicao.x, v.info.posicao.y, v.info.ponto);
}

Ponto converte_string_para_enum(char *str) {
    char *strings[] = { "pokestop", "Lugia" };

    if(strcmp(str, strings[1]) == 0) {
        return Lugia;
    }
    return pokestop;
}

float calcula_distancia(Posicao p1, Posicao p2) {
    float distancia = 0.0;

    distancia = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

    return distancia;
}

void calcula_distancias_vertice_adjacencia(PVertice v) {
    PNo atual;
    PVertice u;
    float d;

    for(atual = v->adjacencia; atual != NULL; atual = atual->proximo) {
        u = (PVertice)atual->dado;
        d = calcula_distancia(v->info.posicao, u->info.posicao);
        printf("%.2f ", d);
    }
    printf("\n");
}

int main() {
    PGrafo g = cria_grafo();
    Vertice v;
    PVertice raiz, destino;
    PVertice u, w;
    int para_de_ler_entrada;
    char ponto[8];
    Posicao origem;
    int maior_aresta = (int)INFINITY;
    int *aresta, encontrou, indice;
    int *arestas = NULL;
    PHeap heap = NULL;
    int tam_heap = 0;

    scanf("%f %f", &origem.x, &origem.y);
    para_de_ler_entrada = scanf("%f %f %s", &v.info.posicao.x, &v.info.posicao.y, ponto);
    while(para_de_ler_entrada > -1) {
        v.info.ponto = converte_string_para_enum(ponto);
        insere_vertice(g, v);
        para_de_ler_entrada = scanf("%f %f %s", &v.info.posicao.x, &v.info.posicao.y, ponto);
    }

    raiz = g->vertice;
    while(raiz->info.posicao.x != origem.x && raiz->info.posicao.y != origem.y) {
        raiz = raiz->proximo;
    }

    heap = cria_heap(g->n);
    for(int i = 0; i < g->n; i++) {
        for(int j = i+1; j < g->n; j++) {
            u = busca_vertice(g, i);
            w = busca_vertice(g, j);
            heap = insere(heap, distancia_aresta(u, w));
        }
    }

    /* imprime_sequencia(heap); */

    tam_heap = heap->n_elementos;
    arestas = malloc(tam_heap * sizeof(int));
    for(int i = 0; i < tam_heap; i++) {
        aresta = remove_min(heap);
        arestas[i] = *aresta;
        free(aresta);
    }

    /* printf("tam heap: %d\n", tam_heap); */
    /* for(int i = 0; i < tam_heap; i++) { */
    /*     printf("%d ", arestas[i]); */
    /* } */
    /* printf("\n"); */

    for(destino = g->vertice; destino != NULL; destino = destino->proximo) {
        if(destino->info.ponto == Lugia) {
            /* printf("%d\n", destino->id); */
            for(indice = 0; indice < tam_heap; indice++) {
                encontrou = bfs(g, raiz, destino, arestas[indice]);
                /* printf("%d\n", encontrou); */
                if(encontrou) break;
            }
            /* bfs(g, raiz); */
            /* printf("%d\n", aresta); */
            if(arestas[indice] < maior_aresta) {
                maior_aresta = arestas[indice];
            }
        }
    }

    /* maior_aresta = bfs(g, raiz, destino); */
    /* printf("====>>>>  maior aresta: %d\n", maior_aresta); */
    printf("%d\n", maior_aresta);

    /* imprime_vertices(g, imprime_adjacencia); */
    /* calcula_distancias_vertice_adjacencia(g->vertice); */

    free(arestas);
    destroi_grafo(g);
    destroi_heap(heap);

    return 0;
}
