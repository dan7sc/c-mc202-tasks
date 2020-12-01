#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main() {
    int qtde_inicial_lista = 0;
    int num_operacoes = 0;
    int numero = 0;
    int operacao = 0;
    Arvore lista;
    PNo temp = NULL;

    lista = cria_arvore();

    le_int(&qtde_inicial_lista);
    le_int(&num_operacoes);

    for(int i = 0; i < qtde_inicial_lista; i++) {
        le_int(&numero);
        lista = insere(lista, numero);
    }

    for(int i = 0; i < num_operacoes; i++) {
        le_int(&operacao);
        switch(operacao) {
        case 1:
            le_int(&numero);
            lista = insere(lista, numero);
            break;
        case 2:
            le_int(&numero);
            temp = busca(lista, numero);
            printf("%d\n", temp->frequencia);
            free(temp);
            break;
        case 3:
            numero = obtem_lista_legal(lista);
            printf("%d\n", numero);
            break;
        default:
            break;
        }
    }

    destroi_arvore(lista);

    return 0;
}
