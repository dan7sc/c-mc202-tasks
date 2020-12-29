#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"
#include "heap.h"

/* A funcao recebe cadeia de caracteres,
   retornando enum que identifica essa string
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
    char ponto[8]; // string para guardar o ponto de interesse
    Posicao origem; // posicao da origem de Red
    int maior_aresta = (int)INFINITY; // guarda maior aresta de um caminho
    int *aresta; // ponteiro para guardar endereço devolvido pelo heap na remoção
    int encontrou; // guarda 1 se encontrou caminho ou zero caso contrario
    int indice; // guarda indice de um vetor qualquer
    int *arestas = NULL; // vetor dinamico ordenado em ordem crescente para guardar as distancias entre os vertices de um grafo
    PHeap heap = NULL; // heap para guardar as distancias entre os vertices de um grafo
    int tam_heap = 0; // tamanho do heap

    /* le a posicao de origem do Red  */
    scanf("%f %f", &origem.x, &origem.y);
    para_de_ler_entrada = scanf("%f %f %s", &v.info.posicao.x, &v.info.posicao.y, ponto);
    /* enquando não for EOL no arquivo le a posição do ponto de interesse e o tipo de ponto (pokestop ou Lugia) */
    while(para_de_ler_entrada > -1) {
        v.info.ponto = converte_string_para_enum(ponto);
        insere_vertice(g, v);
        para_de_ler_entrada = scanf("%f %f %s", &v.info.posicao.x, &v.info.posicao.y, ponto);
    }

    indice = 0;
    lugias = calloc(g->n, sizeof(PVertice));
    heap = cria_heap(g->n);
    /*  percorre "matriz superior" do grafo
        onde linhas são os vertice do grafo e
        as colunas são elementos da lista de adjacencia
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
            heap = insere(heap, distancia_aresta(u, w));
        }
    }

    /* for(int i = 0; lugias[i] != 0 ; i++) { */
    /*     w = lugias[i]; */
    /*     printf("%d ", w->id); */
    /* } */
    /* printf("\n"); */

    /* imprime_sequencia(heap); */

    tam_heap = heap->n_elementos;
    arestas = malloc(tam_heap * sizeof(int));
    /* cria vetor ordenado com as distancias armazenadas no heap */
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

    /* para cada lugia no vetor lugias realiza o laço interno de busca */
    for(int i = 0; lugias[i] != 0; i++) {
        /* para cada distancia no vetor arestas faz uma busca por largura no grafo
           para encontrar um caminho em que a maior aresta seja maior_aresta
        */
        for(indice = 0; indice < tam_heap; indice++) {
            encontrou = bfs(g, raiz, lugias[i], arestas[indice]);
            if(encontrou) break;
        }
        /*  guarda a maior menor aresta entre todos os caminhos percorridos */
        if(arestas[indice] < maior_aresta) {
            maior_aresta = arestas[indice];
        }
    }

    /*  imprime a maior menor aresta */
    printf("%d\n", maior_aresta);

    /* desaloca memoria */
    free(lugias);
    free(arestas);
    destroi_grafo(g);
    destroi_heap(heap);

    return 0;
}
