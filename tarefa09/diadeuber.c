#include <stdio.h>
#include <string.h>
#include "heap.h"

#define N_ACAO 250

void copia_cliente(Cliente *ca, Cliente *cb) {
    strcpy(ca->nome, cb->nome);
    ca->avaliacao = cb->avaliacao;
    ca->origem = cb->origem;
    ca->destino = cb->destino;
}

int main() {
    PHeap fila;
    char acao;
    Cliente cliente;
    Cliente *cliente_em_atendimento = NULL;

    fila = cria_heap(N_ACAO);

    do {
        scanf("%c", &acao);
        switch(acao) {
        case 'A':
            scanf("%s", cliente.nome);
            scanf("%lf", &cliente.avaliacao);
            scanf("%d %d", &cliente.origem.x, &cliente.origem.y);
            scanf("%d %d", &cliente.destino.x, &cliente.destino.y);
            if(cliente_em_atendimento == NULL) {
                cliente_em_atendimento = malloc(sizeof(Cliente));
                copia_cliente(cliente_em_atendimento, &cliente);
            } else {
                fila = insere(fila, cliente);
            }
            printf("Cliente %s foi adicionado(a)\n", cliente.nome);
            break;
        case 'F':
            printf("A corrida de %s foi finalizada\n", cliente_em_atendimento->nome);
            cliente_em_atendimento = remove_max(fila);
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
