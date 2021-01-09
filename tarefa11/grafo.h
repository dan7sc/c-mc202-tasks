#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef enum ponto {
    pokestop = 0,
    Lugia = 1
} Ponto;

typedef struct posicao {
    float x; // posição na coordenada x
    float y; // posição na coordenada y
} Posicao;

typedef struct info {
    Posicao posicao; // tipo para posicao
    Ponto ponto; // tipo enum para o ponto de interesse que pode ser pokestop = 0 ou Lugia = 1
} Info;

typedef struct vertice {
    int id; // id de identifição do vertice
    Info info; // tipo para armazenar informação do vertice
    /* PNo adjacencia; // lista de adjacencia do vertice */
    struct vertice * proximo; // ponteiro para proximo vertice
} Vertice;
typedef Vertice * PVertice;


typedef struct grafo {
    PVertice vertice; // inicio da lista de vertices
    int n; // número de vértices do grafo
} Grafo;
typedef Grafo * PGrafo;

PVertice cria_vertice(PGrafo grafo, Vertice v);

PGrafo cria_grafo();

void destroi_vertices(PVertice vertice);

void destroi_grafo(PGrafo grafo);

PGrafo insere_vertice(PGrafo grafo, Vertice v);

/* void adiciona_arestas(PGrafo grafo, PVertice v); */

/* void insere_aresta(PVertice u, PVertice v); */

PVertice busca_vertice(PGrafo grafo, int id);

/* int tem_aresta(PVertice u, PVertice v); */

int distancia_aresta(PVertice u, PVertice v);

int busca_caminho(PGrafo grafo, PVertice origem, PVertice destino, int aresta);

/* void imprime_vertices(PGrafo grafo, void (*imprime)(void *)); */

#endif
