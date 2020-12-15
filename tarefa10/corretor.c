#include "hash.h"
#include "funcoes_auxiliares.h"

int main() {
    PHash dicionario; // tabela hashing para representar o dicionario
    int num_palavras_dicionario = 0; // numero de palavras no dicionario
    int num_palavras_texto = 0; // numero de palavras do texto
    char *palavra = NULL; // guarda palavra

    scanf("%d %d", &num_palavras_dicionario, &num_palavras_texto);

    // cria hash, le palavras da entrada e insere cada uma delas no hash
    dicionario = cria_tabela_hash(num_palavras_dicionario);
    for(int i = 0; i < num_palavras_dicionario; i++) {
        palavra = calloc(N_CHAR, sizeof(char));
        scanf("%s", palavra);
        dicionario = insere(dicionario, palavra);
    }

    // le palavra do texto e verifica se esta palavra esta no dicionario
    palavra = calloc(N_CHAR, sizeof(char));
    for(int i = 0; i < num_palavras_texto; i++) {
        scanf("%s", palavra);
        verifica_palavra_no_dicionario(dicionario, palavra);
    }

    // libera memoria
    free(palavra);
    destroi_tabela_hash(dicionario);

    return 0;
}
