#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fila.h"
#include "grafo.h"

/* A funcao recebe o grafo e os dados do vertice
   a ser criado, aloca vertice e armazena os dados
   do vertice, retornando o vertice criado
 */
PVertice cria_vertice(PGrafo grafo, Vertice v) {
    PVertice vertice = calloc(1, sizeof(Vertice));

    vertice->info.posicao.x = v.info.posicao.x;
    vertice->info.posicao.y = v.info.posicao.y;
    vertice->info.ponto = v.info.ponto;;
    vertice->adjacencia = cria_lista();
    vertice->id = grafo->n;

    return vertice;
}

/* A funcao aloca memoria para o tipo Grafo
   e inicializa o grafo, retornando o
   ponteiro para o grafo
 */
PGrafo cria_grafo() {
    PGrafo grafo = calloc(1, sizeof(Grafo));

    grafo->n = 0;
    grafo->vertice = NULL;

    return grafo;
}

/* A funcao libera a memoria de cada vertice
   do grafo e da lista de adjacencia de cada vertice
*/
void destroi_vertices(PVertice vertice) {
    if(vertice != NULL) {
        destroi_vertices(vertice->proximo);
        destroi_lista(vertice->adjacencia);
        free(vertice);
    }
}

/* A funcao recebe o grafo e
   libera a memoria alocada para o grafo
*/
void destroi_grafo(PGrafo grafo) {
    destroi_vertices(grafo->vertice);
    free(grafo);
}

/* A funcao recebe o grafo e os dados do
   vertice a ser inserido, retornando
   o grafo com o vertice inserido
*/
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
    /* adiciona_arestas(grafo, novo_vertice); */
    grafo->n++;

    return grafo;
}

/* A funcao recebe o grafo e o vertice
   em cuja lista de adjacencia serão
   inseridos os outro vertices do grafo
   formando um grafo completo
*/
void adiciona_arestas(PGrafo grafo, PVertice v) {
    PVertice atual;

    atual = grafo->vertice;
    while(atual != NULL && atual->id != v->id) {
        insere_aresta(atual, v);
        atual = atual->proximo;
    }
}

/* A funcao recebe o vertice u e o vertice v,
   criando arestas entre estes dois vertices
   e formando um grafo não orientado
*/
void insere_aresta(PVertice u, PVertice v) {
    u->adjacencia = adiciona_na_lista(u->adjacencia, v);
    v->adjacencia = adiciona_na_lista(v->adjacencia, u);
}

/* A funcao recebe o grafo e o id do vertice
   que será usado para localizar o vertice no grafo,
   retornando ponteiro para o vertice achado ou
   zero caso não haja vertice com o id dado
*/
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

/* A funcao recebe o vertice u e o vertice v
   e verifica se eles possuem aresta,
   retornando 1 se possuirem e zero caso não
*/
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

/* A funcao recebe o vertice u e o vertice v
   e calcula a distancia entre os dois vertices,
   retornando a distandia obtida
*/
int distancia_aresta(PVertice u, PVertice v) {
    float p1 = pow(u->info.posicao.x - v->info.posicao.x, 2);
    float p2 = pow(u->info.posicao.y - v->info.posicao.y, 2);

    return ceil(sqrt(p1 + p2));
}

/* A funcao recebe o grafo, o vertice de origem,
   o vertice de destino e o tamanho da maior aresta
   que o caminho entre a origem e o destino deverá conter,
   retornando 1 case tenha encontrado um caminho e
   zero caso não tenha encontrado;
   esta funcao faz uso da busca em largura (breadth-first search)
   para encontrar o caminho
*/
int busca_caminho(PGrafo grafo, PVertice origem, PVertice destino, int maior_aresta) {
    PVertice predecessor, alvo;
    int *pai = malloc(grafo->n * sizeof(int));
    int *visitado = malloc(grafo->n * sizeof(int));
    int *distancia = malloc(grafo->n * sizeof(int));
    PFila fila = cria_fila();
    int aresta = 0;

    for(int i = 0; i < grafo->n; i++) {
        pai[i] = -1;
        visitado[i] = 0;
        distancia[i] = (int) INFINITY;
    }

    predecessor = origem;
    pai[predecessor->id] = origem->id;
    visitado[predecessor->id] = 1;

    fila = enfileira(fila, predecessor);
    distancia[predecessor->id] = 0;

    while(!fila_vazia(fila)) {
        predecessor = desenfileira(fila);
        if(predecessor->id == destino->id) {
            break;
        }
        for(PVertice atual = grafo->vertice; atual != NULL; atual = atual->proximo) {
        /* for(PNo atual = predecessor->adjacencia; atual != NULL; atual = atual->proximo) { */
            /* alvo = (PVertice) atual->dado; */
            alvo = atual;
            aresta = distancia_aresta(predecessor, alvo);
            if(!visitado[alvo->id] && aresta <= maior_aresta) {
                    if(distancia[alvo->id] + aresta < distancia[predecessor->id]) {
                    visitado[alvo->id] = 1;
                    pai[alvo->id] = predecessor->id;
                    distancia[alvo->id] = distancia[predecessor->id] + aresta;
                    fila = enfileira(fila, alvo);
                }
            }
        }
    }

    destroi_fila(fila);
    free(distancia);
    free(visitado);
    free(pai);

    if(predecessor->id == destino->id) {
        return 1;
    }

    return 0;
}

/* A funcao recebe o grafo e funcao imprime
*/
void imprime_vertices(PGrafo grafo, void (*imprime)(void *)) {
    PVertice atual = grafo->vertice;

    printf("Tamanho do grafo: %d\n", grafo->n);
    while(atual != NULL) {
        printf("%d %f %f %d\n", atual->id, atual->info.posicao.x, atual->info.posicao.y, atual->info.ponto);
        imprime_lista(atual->adjacencia, imprime);
        atual = atual->proximo;
    }
}
