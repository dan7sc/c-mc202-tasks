#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include <math.h>

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
    int para_de_ler_entrada;
    char ponto[8];
    Posicao origem;
    int maior_aresta = (int)INFINITY;
    int aresta, encontrou;

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

    for(destino = g->vertice; destino != NULL; destino = destino->proximo) {
        if(destino->info.ponto == Lugia) {
            /* printf("%d\n", destino->id); */
            encontrou = 0;
            aresta = 1;
            while(!encontrou) {
                /* printf("****\n"); */
                aresta++;
                encontrou = bfs(g, raiz, destino, aresta);
            }
            /* bfs(g, raiz); */
            /* printf("%d\n", aresta); */
            if(aresta < maior_aresta) {
                maior_aresta = aresta;
            }
        }
    }

    /* maior_aresta = bfs(g, raiz, destino); */
    /* printf("====>>>>  maior aresta: %d\n", maior_aresta); */
    printf("%d\n", maior_aresta);

    /* imprime_vertices(g, imprime_adjacencia); */
    /* calcula_distancias_vertice_adjacencia(g->vertice); */

    destroi_grafo(g);

    return 0;
}
