#include "funcoes_auxiliares.h"

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
