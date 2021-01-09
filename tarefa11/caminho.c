#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"
#include "pilha.h"
#include "arvore.h"

#define N_CHAR 8

/* A funcao recebe cadeia de caracteres,
   retornando tipo enum que identifica essa string:
   pokestop = 0, Lugia = 1
*/
Ponto converte_string_para_enum(char *str) {
    char *strings[] = { "pokestop", "Lugia" };

    if(strcmp(str, strings[1]) == 0) {
        return Lugia;
    }
    return pokestop;
}

int main() {
    PGrafo g = cria_grafo();
    Vertice v; // tipo vertice para guardar dados da entrada
    PVertice raiz; // guarda posicao de origem do Red no grafo (raiz do grafo)
    PVertice u, w; // vertices genericos
    PVertice *lugias; // vetor dinamico de vertices onde estão localizados os Lugias
    int para_de_ler_entrada; // inteiro para parar laço de leitura da entrada
    char ponto[N_CHAR]; // string para guardar o ponto de interesse
    Posicao origem; // posicao da origem de Red
    int maior_aresta = (int)INFINITY; // guarda maior aresta de um caminho
    int encontrou; // guarda 1 se encontrou caminho ou zero caso contrario
    int indice; // guarda indice de um vetor qualquer
    int *arestas = NULL; // vetor dinamico ordenado em ordem crescente para guardar as distancias entre os vertices de um grafo
    Arvore av; // arvore AVL com o peso das arestas (distancia entre vertices)
    PPilha p; // pilha para atravessar a arvore
    PANo atual = NULL; // no auxiliar para arvore

    /* le a posicao de origem do Red  */
    scanf("%f %f", &origem.x, &origem.y);
    para_de_ler_entrada = scanf("%f %f %s", &v.info.posicao.x, &v.info.posicao.y, ponto);
    /* enquando não for EOL no arquivo le a posição do ponto de interesse e o tipo de ponto (pokestop ou Lugia) */
    while(para_de_ler_entrada > -1) {
        v.info.ponto = converte_string_para_enum(ponto);
        insere_vertice(g, v);
        para_de_ler_entrada = scanf("%f %f %s", &v.info.posicao.x, &v.info.posicao.y, ponto);
    }

    indice = 0; // posicao inicial no vetor lugias
    lugias = calloc(g->n, sizeof(PVertice));
    av = cria_arvore();
    /*  percorre lista de vertices do grafo */
    for(int i = 0; i < g->n; i++) {
        u = busca_vertice(g, i); // busca vertice no grafo com id i
        /* se posicao do vertice u é igual a posicao do Red na origem então a raiz é u */
        if(origem.x == u->info.posicao.x && origem.y == u->info.posicao.y) {
            raiz = u;
        }
        /* se ponto de interesse é igual a Lugia (1) então guarda u no vetor dinamico lugias */
        if(u->info.ponto == Lugia) {
            lugias[indice++] = u;
        }
        /* para cada vertice percorre a lista de novo
           para calcular distancias entre vertices
           insere distancias entre os vertices u e w na arvore
        */
        for(int j = i+1; j < g->n; j++) {
            w = busca_vertice(g, j);
            av = insere_na_arvore(av, distancia_aresta(u, w));
        }
    }
    /*  para cada lugia faz uma busca pelo caminho
        com a maior menor aresta
     */
    for(int i = 0; lugias[i] != 0; i++) {
        p = cria_pilha();
        atual = av.raiz;
        /* faz percurso in-ordem na arvore (ordem crescente de distancias);
           para cada distancia na arvore faz uma busca por largura no grafo
           para encontrar um caminho em que a maior aresta seja maior_aresta
        */
        while(atual != NULL || !pilha_vazia(p)) {
            if(atual != NULL) {
                empilha(p, atual);
                atual = atual->esq;
            } else {
                atual = desempilha(p);
                encontrou = busca_caminho(g, raiz, lugias[i], atual->dado);
                if(encontrou) {
                    destroi_pilha(p);
                    break;
                }
                atual = atual->dir;
            }
        };
        /*  verifica se é a aresta com maior peso
            dentre os caminhos percorridos,
            se for guarda na variavel maior_aresta
         */
        if(atual->dado < maior_aresta) {
            maior_aresta = atual->dado;
        }
    }
    printf("%d\n", maior_aresta);

    /* desaloca memoria */
    free(lugias);
    free(arestas);
    destroi_grafo(g);
    destroi_arvore(av);

    return 0;
}
