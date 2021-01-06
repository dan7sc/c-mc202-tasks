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
    Arvore av;
    PPilha pav;
    /* int **m = NULL; */
    PANo atual = NULL;
    int tam = 0;
    /* int aresta = -1; */

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
    /*  percorre "matriz superior" do grafo
        onde linhas são os vertice do grafo (lista de vertices)
        e as colunas são elementos da lista de adjacencia
     */
    /* m = malloc(g->n * sizeof(int *)); */
    /* for(int i = 0; i < g->n; i++) { */
    /*     m[i] = calloc(g->n, sizeof(int)); */
    /* }
 */
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
        /* insere distancias entre os vertices u e w no heap */
        for(int j = i+1; j < g->n; j++) {
            w = busca_vertice(g, j);
            av = insere_na_arvore(av, distancia_aresta(u, w));
        }

        /* for(int j = i+1; j < g->n; j++) { */
        /*     w = busca_vertice(g, j); */
        /*     m[i][j] = distancia_aresta(u, w); */
        /* } */
    }
    /* printf("**** %d %d\n", av.raiz->altura, (int)pow(2, av.raiz->altura) - 1); */
    /* percorre_pre_ordem(av.raiz); */
    /* printf("\n"); */
    /* percorre_in_ordem(av.raiz); */
    /* printf("\n"); */
    /* percorre_pos_ordem(av.raiz); */
    /* printf("\n**...**\n"); */
    /* percorre_in_ordem_it(av); */
    /* printf("\n"); */

    tam = (int) pow(2, av.raiz->altura) - 1;
    arestas = calloc(tam, sizeof(int));
    /* printf("****\n"); */
    pav = cria_pilha();
    atual = av.raiz;
    indice = 0;
    while(atual != NULL || !pilha_vazia(pav)) {
        if(atual != NULL) {
            empilha(pav, atual);
            atual = atual->esq;
        } else {
            atual = desempilha(pav);
            arestas[indice] = atual->dado;
            indice++;
            atual = atual->dir;
        }
    };
    /* printf("\n\n"); */

    /* for(int i = 0; i < tam; i++) { */
    /* for(int i = 0; i < tam && arestas[i] != 0; i++) { */
    /*     printf("%d ", arestas[i]); */
    /* } */

    /* for(int i = 0; i < g->n; i++) { */
    /*     for(int j = 0; j < i+1; j++) { */
    /*         printf("%2d ", 0); */
    /*     } */
    /*     for(int j = i+1; j < g->n; j++) { */
    /*         printf("%2d ", m[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    /* printf("\n"); */

    /* tam_heap = heap->n_elementos; */
    /* arestas = malloc(tam_heap * sizeof(int)); // vetor que guarda arestas em ordem crescente */
    /* /\* cria vetor ordenado com as distancias armazenadas no heap *\/ */
    /* for(int i = 0; i < tam_heap; i++) { */
    /*     aresta = remove_min(heap); */
    /*     arestas[i] = *aresta; */
    /*     free(aresta); */
    /* } */

    /* arestas = calloc(500, sizeof(int)); */
    /* indice = 0; */
    /* para cada lugia no vetor lugias realiza o laço interno de busca */
    for(int i = 0; lugias[i] != 0; i++) {
        /* para cada distancia no vetor arestas faz uma busca por largura no grafo
           para encontrar um caminho em que a maior aresta seja maior_aresta
        */
        /* pav = cria_pilha(); */
        for(indice = 0; indice < tam; indice++) {
            encontrou = busca_caminho(g, raiz, lugias[i], arestas[indice]);
            if(encontrou) {
                break;
            }
        }

        /* atual = av.raiz; */
        /* do { */
        /*     if(atual != NULL) { */
        /*         empilha(pav, atual); */
        /*         atual = atual->esq; */
        /*     } else { */
        /*         atual = desempilha(pav); */
        /*         printf("%d ", atual->dado); */
        /*         aresta = atual->dado; */
        /*         encontrou = busca_caminho(g, raiz, lugias[i], aresta); */
        /*         if(encontrou) { */
        /*             arestas[indice++] = atual->dado; */
        /*             /\* aresta = atual->dado; *\/ */
        /*             break; */
        /*         } */
        /*         atual = atual->dir; */
        /*     } */
        /* } while(!pilha_vazia(pav)); */

        /*  guarda a maior menor aresta entre todos os caminhos percorridos */
        /* printf("%d\n", aresta, maior_aresta); */
        if(arestas[indice] < maior_aresta) {
            maior_aresta = arestas[indice];
            /* maior_aresta = aresta; */
        }
        /* destroi_pilha(pav); */
    }

    /* for(int i = 0; i < 500; i++) { */
    /*     printf("%d ", arestas[i]); */
    /* } */

    /* printf("\n"); */
    /*  imprime a maior menor aresta */
    printf("%d\n", maior_aresta);

    /* desaloca memoria */
    free(lugias);
    free(arestas);
    destroi_grafo(g);
    destroi_arvore(av);
    destroi_pilha(pav);

    return 0;
}
