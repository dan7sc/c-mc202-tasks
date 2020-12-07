#include "hash.h"
#include "funcoes_auxiliares.h"

int main() {
    PHash h;
    int num_palavras_dicionario = 0;
    int num_palavras_texto = 0;
    char *palavra_texto = NULL;
    char *palavra = NULL;

    scanf("%d %d", &num_palavras_dicionario, &num_palavras_texto);

    h = cria_tabela_hash(num_palavras_dicionario);
    for(int i = 0; i < num_palavras_dicionario; i++) {
        palavra = calloc(N_CHAR, sizeof(char));
        scanf("%s", palavra);
        h = insere(h, palavra);
    }

    palavra_texto = calloc(N_CHAR, sizeof(char));
    for(int i = 0; i < num_palavras_texto; i++) {
        scanf("%s", palavra_texto);
        verifica_palavra_no_dicionario(h, palavra_texto);
    }

    free(palavra_texto);
    destroi_tabela_hash(h);

    return 0;
}
