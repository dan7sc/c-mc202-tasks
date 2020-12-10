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
    int taxa_cancelamento = 7;
    float pagamento_por_km = 1.4;

    return (taxa_cancelamento * n_cancelamentos + pagamento_por_km * km_rodados);
}

// calcula despesas do motorista
double calcula_despesas(int km_rodados) {
    int custo_aluguel_por_dia = 57;
    float custo_gasolina_por_litro = 4.104;
    int consumo_km_por_litro = 10;

    return (custo_aluguel_por_dia + (custo_gasolina_por_litro * km_rodados) / consumo_km_por_litro);
}

// calcula o rendimento liquido do motorista
double calcula_rendimento_liquido(double rbruto, double despesas) {
    float taxa_uber = 0.25;

    return ((1 - taxa_uber) * rbruto - despesas);
}
