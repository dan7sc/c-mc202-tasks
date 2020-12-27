#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef enum ponto {
    pokestop = 0,
    Lugia = 1
} Ponto;

typedef struct posicao {
    float x;
    float y;
} Posicao;

typedef struct info {
    Posicao posicao;
    Ponto ponto;
} Info;

typedef struct vertice {
    int id;
    Info info;
    PNo adjacencia;
    struct vertice * proximo;
} Vertice;
typedef Vertice * PVertice;


typedef struct grafo {
    PVertice vertice;
    int n;
} Grafo;
typedef Grafo * PGrafo;

PVertice cria_vertice(PGrafo grafo, Vertice v);

PGrafo cria_grafo();

void destroi_grafo(PGrafo grafo);

PGrafo insere_vertice(PGrafo grafo, Vertice v);

void adiciona_arestas(PGrafo grafo, PVertice v);

void insere_aresta(PVertice u, PVertice v);

PVertice busca_vertice(PGrafo grafo, int id);

int tem_aresta(PVertice u, PVertice v);

int distancia_aresta(PVertice u, PVertice v);

int bfs(PGrafo grafo, PVertice origem, PVertice destino, int aresta);
/* void bfs(PGrafo grafo, PVertice origem); */

void imprime_vertices(PGrafo grafo, void (*imprime)(void *));

void imprime_arestas(PGrafo grafo);

#endif
