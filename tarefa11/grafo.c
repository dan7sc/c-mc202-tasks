#include "lista.h"
#include "grafo.h"

PVertice cria_vertice(PGrafo grafo, Vertice v) {
    PVertice vertice = calloc(1, sizeof(Vertice));

    vertice->info.posicao.x = v.info.posicao.x;
    vertice->info.posicao.y = v.info.posicao.y;
    vertice->info.ponto = v.info.ponto;;
    vertice->adjacencia = cria_lista();
    vertice->id = 1 + grafo->n;

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

void imprime_vertices(PGrafo grafo, void (*imprime)(void *)) {
    PVertice atual = grafo->vertice;

    while(atual != NULL) {
        printf("%d %f %f %d\n", atual->id, atual->info.posicao.x, atual->info.posicao.y, atual->info.ponto);
        imprime_lista(atual->adjacencia, imprime);
        atual = atual->proximo;
    }
}
