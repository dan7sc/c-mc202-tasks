#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "funcoes_de_ajuda.h"

int main() {
    int num_cartoes;
    int num_autoridades;
    int n;
    Cartao *cartao = NULL;
    Cartao *novo_cartao = NULL;
    Arvore pares;
    Arvore av_triade;
    PNo temp1 = NULL;
    PNo temp2 = NULL;
    PNo temp3 = NULL;
    Triade *triade = NULL;
    int autoridade_numero;

    n = 1;
    while(n > -1) {
        n = le_int(&num_cartoes);
        if(n > 0) {
            le_int(&num_autoridades);

            pares = cria_arvore();
            for(int i = 0; i < num_cartoes; i++) {
                cartao = malloc(sizeof(Cartao));
                cartao->texto = malloc(5 * sizeof(char));
                le_int(&cartao->numero);
                le_string_entre_aspas(cartao->texto);
                pares = insere(pares, cartao, compara_numero_cartao);
            }

            for(int i = 0; i < num_autoridades; i++) {
                le_int(&autoridade_numero);

                triade = malloc(sizeof(Triade));
                triade->num_cartao1 = 0;
                triade->num_cartao2 = 0;
                triade->num_cartao3 = 0;

                triade = busca_triade(pares, triade, autoridade_numero, soma, compara_numero_cartao);

                av_triade = cria_arvore();
                if(triade != NULL && triade->num_cartao1 > 0 && triade->num_cartao2 > 0 && triade->num_cartao3 > 0) {
                    temp1 = busca(pares, &triade->num_cartao1, compara_numero_cartao);
                    temp2 = busca(pares, &triade->num_cartao2, compara_numero_cartao);
                    temp3 = busca(pares, &triade->num_cartao3, compara_numero_cartao);

                    av_triade = insere(av_triade, temp1->dado, compara_numero_cartao);
                    av_triade = insere(av_triade, temp2->dado, compara_numero_cartao);
                    av_triade = insere(av_triade, temp3->dado, compara_numero_cartao);

                    pares = remove_no(pares, &triade->num_cartao1, compara_numero_cartao);
                    pares = remove_no(pares, &triade->num_cartao2, compara_numero_cartao);
                    pares = remove_no(pares, &triade->num_cartao3, compara_numero_cartao);

                    novo_cartao = malloc(sizeof(Cartao));
                    novo_cartao->texto = NULL;
                    novo_cartao->numero = 0;
                    novo_cartao = cria_cartao(av_triade, novo_cartao, concatena_string);

                    av_triade = remove_no(av_triade, &triade->num_cartao1, compara_numero_cartao);
                    av_triade = remove_no(av_triade, &triade->num_cartao2, compara_numero_cartao);
                    av_triade = remove_no(av_triade, &triade->num_cartao3, compara_numero_cartao);

                    pares = insere(pares, novo_cartao, compara_numero_cartao);

                    if(temp1 != NULL && temp2 != NULL && temp3 != NULL) {
                        free(temp1);
                        free(temp2);
                        free(temp3);
                    }
                }

                free(triade);
                destroi_arvore(av_triade, destroi_cartao);

                if(av_triade.raiz != NULL) {
                    destroi_arvore(av_triade, destroi_cartao);
                }
            }

            percorre(pares, in_ordem, imprime_mensagem);

            if(pares.raiz != NULL) {
                destroi_arvore(pares, destroi_cartao);
            }

            if(av_triade.raiz != NULL) {
                destroi_arvore(av_triade, destroi_cartao);
            }
        }
    }

    return 0;
}
