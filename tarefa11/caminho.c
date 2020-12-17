#include "lista.h"
#include "grafo.h"

void imprime_adjacencia(void *dado) {
    Vertice v = *(Vertice *) dado;

    printf("==> %d %f %f %d\n", v.id, v.info.posicao.x, v.info.posicao.y, v.info.ponto);
}

Ponto converte_string_para_enum(char *str) {
    Ponto ponto = 0;
    char *strings[] = { "Red", "pokestop", "Lugia" };

    for(int i = 0; i < 3; i++) {
        if(strcmp(str, strings[i])) {
            ponto = i;
        }
    }

    return ponto;
}

int main() {
    PGrafo g = cria_grafo();
    Vertice v;
    int para_de_ler_entrada = 1;
    char ponto[8];

    scanf("%f %f", &v.info.posicao.x, &v.info.posicao.y);
    v.info.ponto = Red;
    insere_vertice(g, v);

    while(para_de_ler_entrada > -1) {
        para_de_ler_entrada = scanf("%f %f %s", &v.info.posicao.x, &v.info.posicao.y, ponto);
        v.info.ponto = converte_string_para_enum(ponto);
        insere_vertice(g, v);
    }

    imprime_vertices(g, imprime_adjacencia);

    destroi_grafo(g);

    return 0;
}
