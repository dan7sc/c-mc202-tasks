#include <stdio.h>
#include <string.h>
#include <math.h>
#include "heap.h"

#define N_ACAO 250

void copia_cliente(Cliente *ca, Cliente *cb) {
    strcpy(ca->nome, cb->nome);
    ca->avaliacao = cb->avaliacao;
    ca->origem = cb->origem;
    ca->destino = cb->destino;
}

int calcula_distancia(Posicao origem, Posicao destino) {
    return (abs(origem.x - destino.x) + abs(origem.y - destino.y));
}

double calcula_rendimento_bruto(int n_cancelamentos, int km_rodados) {
    return (7*n_cancelamentos + 1.4*km_rodados);
}

double calcula_despesas(int km_rodados) {
    return (57 + (4.104*km_rodados)/10);
}

double calcula_rendimento_liquido(double rbruto, double despesas) {
    return (0.75*rbruto - despesas);
}

int main() {
    PHeap fila;
    char acao;
    Cliente cliente;
    Cliente *cliente_em_atendimento = NULL;
    Cliente *cliente_cancelado = NULL;
    int km_rodados = 0;
    int km_rodados_pagos = 0;
    int n_cancelamentos = 0;
    Posicao atual;

    atual.x = 0;
    atual.y = 0;

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
            km_rodados += calcula_distancia(atual, cliente_em_atendimento->origem);
            atual = cliente_em_atendimento->origem;
            km_rodados += calcula_distancia(atual, cliente_em_atendimento->destino);
            km_rodados_pagos += calcula_distancia(atual, cliente_em_atendimento->destino);
            atual = cliente_em_atendimento->destino;
            printf("A corrida de %s foi finalizada\n", cliente_em_atendimento->nome);
            free(cliente_em_atendimento);
            cliente_em_atendimento = remove_max(fila);
            break;
        case 'C':
            scanf("%s", cliente.nome);
            maximiza_prioridade(fila, cliente.nome);
            cliente_cancelado = remove_max(fila);
            n_cancelamentos++;
            printf("%s cancelou a corrida\n", cliente_cancelado->nome);
            free(cliente_cancelado);
            break;
        case 'T':
            printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
            printf("Km total: %d\n", km_rodados);
            printf("Rendimento bruto: %.2lf\n", calcula_rendimento_bruto(n_cancelamentos, km_rodados_pagos));
            printf("Despesas: %.2lf\n", calcula_despesas(km_rodados));
            printf("Rendimento liquido: %.2lf\n", calcula_rendimento_liquido(
                       calcula_rendimento_bruto(n_cancelamentos, km_rodados_pagos),
                       calcula_despesas(km_rodados)));
            break;
        }
    } while(acao != 'T');

    destroi_heap(fila);

    return 0;
}
