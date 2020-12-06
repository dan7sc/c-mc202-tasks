#include "hash.h"

int busca_potencia2_maior_N(int n) {
    int potencia = 2;

    while (potencia < n){
        potencia = potencia << 1;
    }

    return potencia;
}

Boolean eh_primo(int num) {
    if(num <= 1 || ((num % 2) == 0 && num > 2)) {
        return FALSE;
    }

    for (int i = 3; i < num / 2; i += 2) {
        if ((num % i) == 0) {
            return FALSE;
        }
    }

    return TRUE;
}

int busca_primo(int tamanho) {
    int menor = busca_potencia2_maior_N(tamanho);
    int maior = busca_potencia2_maior_N(menor + 1);
    int media = (maior - menor) / 2 + menor;

    media = media;
    maior = media + 1;
    while(menor < maior && maior > menor) {
        if(eh_primo(menor)) {
            return menor;
        }
        if(eh_primo(maior)) {
            return maior;
        }
        menor++;
        maior--;
    }

    return tamanho;
}

PHash cria_tabela_hash(int tamanho) {
    PHash hash = malloc(sizeof(Hash));

    tamanho = busca_primo(tamanho);
    hash->tamanho = tamanho;
    hash->tabela = malloc(tamanho * sizeof(Tabela));
    for(int i = 0; i < hash->tamanho; i++) {
        hash->tabela[i].valor = malloc(sizeof(char *));
        *hash->tabela[i].valor = NULL;
    }

    return hash;
}

void destroi_tabela_hash(PHash hash) {
    for(int i = 0; i < hash->tamanho; i++) {
        free(*hash->tabela[i].valor);
        free(hash->tabela[i].valor);
    }
    free(hash->tabela);
    free(hash);
}

int f_hash(PHash hash, char *chave) {
    long int n = 0;
    int tamanho = (int) strlen(chave);

    for(int i = 0; i < tamanho; i++) {
        n = (256 * n + chave[i]) % hash->tamanho;
    }

    return n;
}

PHash insere(PHash hash, char *valor) {
    int chave = 0;

    chave = f_hash(hash, valor);
    while(chave >= 0 && chave < hash->tamanho) {
        if(*hash->tabela[chave].valor == NULL) {
            *hash->tabela[chave].valor = valor;
             return hash;
        }
        chave = (chave + 1) % hash->tamanho;
    }

    return hash;
}

char *remove_valor(PHash hash, char *valor) {
    int chave = 0;
    char *valor_a_trocar = NULL;
    char *removido = NULL;

    chave = f_hash(hash, valor);

    if(!busca(hash, valor)) {
        return NULL;
    }

    while(strcmp(*hash->tabela[chave].valor, valor) != 0) {
        chave = (chave + 1) % hash->tamanho;
    }

    removido = malloc(N_CHAR * sizeof(char));
    strcpy(removido, *hash->tabela[chave].valor);
    free(*hash->tabela[chave].valor);
    *hash->tabela[chave].valor = NULL;

    chave = (chave + 1) % hash->tamanho;
    while (*hash->tabela[chave].valor != NULL) {
        valor_a_trocar = malloc(N_CHAR * sizeof(char));
        strcpy(valor_a_trocar, *hash->tabela[chave].valor);
        free(*hash->tabela[chave].valor);
        *hash->tabela[chave].valor = NULL;
        insere(hash, valor_a_trocar);
        chave = (chave + 1) % hash->tamanho;
    }

    return removido;
}

char *busca(PHash hash, char *valor) {
    int chave = 0;

    chave = f_hash(hash, valor);
    while(chave > -1 && chave < hash->tamanho && *hash->tabela[chave].valor != NULL) {
        if(strcmp(*hash->tabela[chave].valor, valor) == 0) {
            return *hash->tabela[chave].valor;
        }
        chave = (chave + 1) % hash->tamanho;
    }

    return NULL;
}

void imprime_tabela_hash(PHash hash) {
    printf("Hash com %d posicoes\n", hash->tamanho);

    for (int i = 0; i < hash->tamanho; i++) {
        if(*hash->tabela[i].valor != NULL) {
            printf("chave: %d, valor: %s\n", i, *hash->tabela[i].valor);
        }
    }
}
