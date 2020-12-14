#include "hash.h"
#include "funcoes_auxiliares.h"

int main() {
    PHash h; // tabela hashing para representar o dicionario
    int num_palavras_dicionario = 0; // numero de palavras no dicionario
    int num_palavras_texto = 0; // numero de palavras do texto
    char *palavra_texto = NULL; // palavra do texto
    char *palavra = NULL; // palavra

    scanf("%d %d", &num_palavras_dicionario, &num_palavras_texto);

    // cria hash, le palavras da entrada e insere cada uma delas no hash
    h = cria_tabela_hash(num_palavras_dicionario);
    for(int i = 0; i < num_palavras_dicionario; i++) {
        palavra = calloc(N_CHAR, sizeof(char));
        scanf("%s", palavra);
        h = insere(h, palavra);
    }

    // le palavra do texto e verifica se esta palavra esta no dicionario
    palavra_texto = calloc(N_CHAR, sizeof(char));
    for(int i = 0; i < num_palavras_texto; i++) {
        scanf("%s", palavra_texto);
        verifica_palavra_no_dicionario(h, palavra_texto);
    }

    // libera memoria
    free(palavra_texto);
    destroi_tabela_hash(h);

    return 0;
}
