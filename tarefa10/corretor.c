#include "hash.h"

int main() {
    PHash h;
    int tamanho = 0;
    char *palavra = NULL;
    char *temp = NULL;
    int contador = 0;

    scanf("%d", &tamanho);
    h = cria_tabela_hash(tamanho);

    while(contador < tamanho) {
        palavra = malloc(N_CHAR * sizeof(char));
        scanf("%s", palavra);
        h = insere(h, palavra);
        contador++;
    }

    imprime_tabela_hash(h);

    temp = busca(h, "nebris");
    printf(">> encontrado >> %s\n", temp);
    temp = busca(h, "bo");
    printf(">> encontrado >> %s\n", temp);

    temp = remove_valor(h, "ectopago");
    printf(">> removido >> %s\n", temp);
    free(temp);
    temp = remove_valor(h, "ola");
    printf(">> removido >> %s\n", temp);

    imprime_tabela_hash(h);

    free(temp);
    destroi_tabela_hash(h);

    return 0;
}
