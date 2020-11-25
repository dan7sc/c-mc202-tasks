#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "funcoes_de_ajuda.h"

int main() {
    int num_cartoes; // numero total de cartoes
    int num_autoridades; // numero total de autoridades
    int n; // guarda retorno da funcao scanf
    Cartao *cartao = NULL; // ponteiro para tipo Cartao { numero, texto }
    Cartao *novo_cartao = NULL; // cartao gerado apos concatenação das triades
    Arvore pares; // arvore que armazena os cartões
    Arvore av_triade; // arvore que armazena os numeros de cada triade
    PNo temp1 = NULL; // no temporario para armazenar uma das triades
    PNo temp2 = NULL; // no temporario para armazenar uma das triades
    PNo temp3 = NULL; // no temporario para armazenar uma das triades
    Triade *triade = NULL; // ponteiro para tipo Triade { numero }
    int autoridade_numero; // numero de uma autoridade

    n = 1;
    // enquanto nao for fim do arquivo
    while(n > -1) {
        // lê numero de total de cartões
        n = le_int(&num_cartoes);
        if(n > 0) {
            // lê numero de total de autoridades
            le_int(&num_autoridades);

            // cria arvore que guarda os cartões
            pares = cria_arvore();
            for(int i = 0; i < num_cartoes; i++) {
                cartao = malloc(sizeof(Cartao));
                cartao->texto = malloc(5 * sizeof(char));
                le_int(&cartao->numero);
                le_string_entre_aspas(cartao->texto); // não guarda as aspas na string
                // guarda cartao criado acima
                pares = insere(pares, cartao, compara_numero_cartao);
            }

            // para cada autoridade gera um novo cartao a partir da triade
            for(int i = 0; i < num_autoridades; i++) {
                // le numero da autoridade
                le_int(&autoridade_numero);

                // cria triade
                triade = malloc(sizeof(Triade));
                triade->num_cartao1 = 0;
                triade->num_cartao2 = 0;
                triade->num_cartao3 = 0;

                // busca triade na arvore pares
                triade = busca_triade(pares, triade, autoridade_numero, soma, compara_numero_cartao);

                // se houver a triade
                if(triade != NULL && triade->num_cartao1 > 0
                   && triade->num_cartao2 > 0 && triade->num_cartao3 > 0) {
                    // cria arvore para guardar a triade
                    av_triade = cria_arvore();

                    // busca cada numero da triade na arvore pares
                    temp1 = busca(pares, &triade->num_cartao1, compara_numero_cartao);
                    temp2 = busca(pares, &triade->num_cartao2, compara_numero_cartao);
                    temp3 = busca(pares, &triade->num_cartao3, compara_numero_cartao);

                    // busca cada numero da triade na arvore pares
                    av_triade = insere(av_triade, temp1->dado, compara_numero_cartao);
                    av_triade = insere(av_triade, temp2->dado, compara_numero_cartao);
                    av_triade = insere(av_triade, temp3->dado, compara_numero_cartao);

                    // remove a triade da arvore pares
                    pares = remove_no(pares, &triade->num_cartao1, compara_numero_cartao);
                    pares = remove_no(pares, &triade->num_cartao2, compara_numero_cartao);
                    pares = remove_no(pares, &triade->num_cartao3, compara_numero_cartao);

                    // cria novo cartao com a soma dos numeros e a concatenaçao das strings da triade
                    novo_cartao = malloc(sizeof(Cartao));
                    novo_cartao->texto = NULL;
                    novo_cartao->numero = 0;
                    novo_cartao = cria_cartao(av_triade, novo_cartao, concatena_string);

                    // remove a triade da arvore av_triade
                    av_triade = remove_no(av_triade, &triade->num_cartao1, compara_numero_cartao);
                    av_triade = remove_no(av_triade, &triade->num_cartao2, compara_numero_cartao);
                    av_triade = remove_no(av_triade, &triade->num_cartao3, compara_numero_cartao);

                    // insere novo cartao na arvore pares
                    pares = insere(pares, novo_cartao, compara_numero_cartao);

                    // libera memoria dos nos temporarios
                    if(temp1 != NULL && temp2 != NULL && temp3 != NULL) {
                        free(temp1);
                        free(temp2);
                        free(temp3);
                    }
                }
                // libera memoria da triade
                free(triade);
                // libera memoria da arvore av_triade
                /* if(av_triade.raiz != NULL) { */
                /*     destroi_arvore(av_triade, destroi_texto); */
                /* } */
            }

            // imprime resultado
            percorre(pares, in_ordem, imprime_mensagem);

            // libera memoria da arvore pares
            if(pares.raiz != NULL) {
                destroi_arvore(pares, destroi_texto);
            }
        }
    }

    return 0;
}
