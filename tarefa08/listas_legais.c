#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main() {
    int qtde_inicial_lista = 0; // quantidade de números inicialmente na lista
    int num_operacoes = 0; // número de operações
    int numero = 0; // guarda número
    int operacao = 0; // guarda operação
    Arvore lista; // arvore AVL
    PNo temp = NULL; // nó temporário para guardar resultado da função busca

    lista = cria_arvore(); // AVL

    le_int(&qtde_inicial_lista);
    le_int(&num_operacoes);

    // insere os números iniciais da lista
    for(int i = 0; i < qtde_inicial_lista; i++) {
        le_int(&numero);
        lista = insere(lista, numero);
    }

    // realiza as operações
    for(int i = 0; i < num_operacoes; i++) {
        le_int(&operacao);
        switch(operacao) {
        case 1:
            // adiciona numero inteiro na lista atual
            le_int(&numero);
            lista = insere(lista, numero);
            break;
        case 2:
            // busca numero e mostra quantas vezes este numero aparece na lista
            le_int(&numero);
            temp = busca(lista, numero);
            printf("%d\n", temp->frequencia);
            free(temp);
            break;
        case 3:
            // mostra a menor quantidade de números que devem ser retirados
            // da lista atual para que ela se torne legal
            numero = obtem_numeros_removidos_lista_legal(lista);
            printf("%d\n", numero);
            break;
        default:
            break;
        }
    }

    destroi_arvore(lista);

    return 0;
}
