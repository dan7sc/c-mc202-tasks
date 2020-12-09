#include <stdio.h>
#include <string.h>
#include <math.h>
#include "heap.h"

// faz copia do cliente cb e armazena no cliente ca
void copia_cliente(Cliente *ca, Cliente *cb) {
    strcpy(ca->nome, cb->nome);
    ca->avaliacao = cb->avaliacao;
    ca->origem = cb->origem;
    ca->destino = cb->destino;
}

// calcula distancia entro a origem e o destino
// usando a distancia de Manhattan medida em kilometros
int calcula_distancia(Posicao origem, Posicao destino) {
    return (abs(origem.x - destino.x) + abs(origem.y - destino.y));
}

// calcula o rendimento bruto do motorista
double calcula_rendimento_bruto(int n_cancelamentos, int km_rodados) {
    return (7*n_cancelamentos + 1.4*km_rodados);
}

// calcula despesas do motorista
double calcula_despesas(int km_rodados) {
    return (57 + (4.104*km_rodados)/10);
}

// calcula o rendimento liquido do motorista
double calcula_rendimento_liquido(double rbruto, double despesas) {
    return (0.75*rbruto - despesas);
}

int main() {
    PHeap fila; // heap: fila de prioridade
    char acao; // acao a ser tomada pelo motorista
    Cliente cliente;
    Cliente *cliente_em_atendimento = NULL; // cliente sendo levado pelo motorista
    Cliente *cliente_cancelado = NULL; // cliente que cancelou a corrida
    int km_rodados = 0; // kilometros rodados pelo motorista
    int km_rodados_pagos = 0; // kilometros rodados pelo motorista junto com o cliente
    int n_cancelamentos = 0; // numero do cancelamentos feitos pelos clientes
    Posicao atual; // posicao atual do motorista em coordenadas cartesianas

    // posicao de origem do motorista
    atual.x = 0;
    atual.y = 0;

    // cria heap/fila de prioridade
    fila = cria_heap(N_ACAO/2); // maximo do heap é metade do numero de acões: para cada insercao há uma remocao

    // enquando acao for diferente de 'T'
    do {
        scanf("%c", &acao); // le acao
        switch(acao) {
        // o motorista aceitou a solicitação de um(a) cliente, deixando-o(a) em espera
        case 'A':
            // le dados do cliente
            scanf("%s", cliente.nome);
            scanf("%lf", &cliente.avaliacao);
            scanf("%d %d", &cliente.origem.x, &cliente.origem.y);
            scanf("%d %d", &cliente.destino.x, &cliente.destino.y);
            // se o motorista não esta atendendo um cliente,
            // cliente passsa a ser o cliente em atendimento
            // caso contrario insere o cliente na fila
            if(cliente_em_atendimento == NULL) {
                cliente_em_atendimento = malloc(sizeof(Cliente));
                copia_cliente(cliente_em_atendimento, &cliente);
            } else {
                fila = insere(fila, cliente);
            }
            printf("Cliente %s foi adicionado(a)\n", cliente.nome);
            break;
        // o motorista finalizou a corrida atual
        case 'F':
            // soma kilometros percorridos da posicao atual do motorista até a posicao do cliente
            km_rodados += calcula_distancia(atual, cliente_em_atendimento->origem);
            // atualiza posicao atual do motorista
            atual = cliente_em_atendimento->origem;
            // soma kilometros percorridos até a posicao de destino do cliente
            km_rodados += calcula_distancia(atual, cliente_em_atendimento->destino);
            // soma kilometros em que o motorista está levando o cliente ate o destino deste
            km_rodados_pagos += calcula_distancia(atual, cliente_em_atendimento->destino);
            // atualiza posicao atual do motorista
            atual = cliente_em_atendimento->destino;
            printf("A corrida de %s foi finalizada\n", cliente_em_atendimento->nome);
            free(cliente_em_atendimento);
            // apos cliente chegar ao destino, novo cliente a ser atendido
            // pelo motorista passa a ser o maximo do heap
            cliente_em_atendimento = remove_max(fila);
            break;
        // o(a) cliente indicado(a) cancelou sua solicitação
        case 'C':
            scanf("%s", cliente.nome);
            // cliente que cancelou corrida passa ser o maximo do heap
            maximiza_prioridade(fila, cliente.nome);
            // entaõ é removido do heap
            cliente_cancelado = remove_max(fila);
            // soma numero de cancelamentos
            n_cancelamentos++;
            printf("%s cancelou a corrida\n", cliente_cancelado->nome);
            free(cliente_cancelado);
            break;
        // o motorista indicou o término da sua jornada e deseja ver o rendimento obtido
        case 'T':
            // imprime relatorio
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

    // libera memoria
    destroi_heap(fila);

    return 0;
}
