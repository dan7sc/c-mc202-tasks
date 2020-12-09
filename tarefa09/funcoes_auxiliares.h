#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

#include "heap.h"

void copia_cliente(Cliente *ca, Cliente *cb);

int calcula_distancia(Posicao origem, Posicao destino);

double calcula_rendimento_bruto(int n_cancelamentos, int km_rodados);

double calcula_despesas(int km_rodados);

double calcula_rendimento_liquido(double rbruto, double despesas);

#endif
