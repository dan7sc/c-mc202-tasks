#include <stdio.h>
#include "heap.h"

#define N_ACAO 250

int main() {
    PHeap fila;
    char acao;
    Cliente cliente;

    fila = cria_heap(N_ACAO);

    do {
        scanf("%c", &acao);
        switch(acao) {
        case 'A':
            scanf("%s", cliente.nome);
            scanf("%lf", &cliente.avaliacao);
            scanf("%d %d", &cliente.origem.x, &cliente.origem.y);
            scanf("%d %d", &cliente.destino.x, &cliente.destino.y);
            fila = insere(fila, cliente);
            printf("Cliente %s foi adicionado(a)\n", cliente.nome);
            break;
        case 'F':
            cliente = remove_max(fila);
            printf("A corrida de %s foi finalizada\n", cliente.nome);
            break;
        case 'C':
            printf("%s cancelou a corrida\n", cliente.nome);
            break;
        case 'T':
            printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
            break;
        }
    } while(acao != 'T');

    imprime_sequencia(fila);
    imprime_heap(fila, 0, 1);

    destroi_heap(fila);

    return 0;
}
