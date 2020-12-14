#include "hash.h"

/* busca potencia de 2 maior
   que o numero dado na entrada
   e retorna essa potencia
   Ex: se n=30, então potencia=2^5=32
 */
int busca_potencia2_maior_N(int n) {
    int potencia = 2;

    while (potencia < n) {
        // potencia é elevada de uma unidade a
        // cada iteração: 2^2, 2^3 2^4 etc
        // usando operadores bit-a-bit
        potencia = potencia << 1;
    }

    return potencia;
}

/* verifica se o numero
   dado na entrada é primo
   retorna TRUE se for primo e
   FALSE caso contrario
*/
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

/* busca numero primo entre a primeira
   potencia de 2 maior do que o tamanho
   dado na entrada e a segunda potencia
   de 2 maior do que o tamanho dado
   e retorna o numero primo achado
   ex: tamanho=30, menor=2^5=32, maior=2^6=64, primo=39
*/
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

/* cria tabela hash de tamanho maior
   do que o tamanho inserido na entrada,
   o tamanho é dado pela funcao busca_primo,
   e aloca memoria para armazenar as strings
   retornando a estrutura hash
*/
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

/* libera a memoria alocada para armazenar
   as strings, para armazenar a tabela e
   a estrutura hash
*/
void destroi_tabela_hash(PHash hash) {
    for(int i = 0; i < hash->tamanho; i++) {
        free(*hash->tabela[i].valor);
        free(hash->tabela[i].valor);
    }
    free(hash->tabela);
    free(hash);
}

/* funcao de hashing que associa um elemento
   de um conjunto (strings) a um número
   inteiro de tamanho fixo
   usando o método da divisão
   e retorna o numero inteiro gerado
*/
int f_hash(PHash hash, char *chave) {
    long int n = 0;
    int tamanho = (int) strlen(chave);

    for(int i = 0; i < tamanho; i++) {
        n = (256 * n + chave[i]) % hash->tamanho;
    }

    return n;
}

/* insere o valor dado na entrada na tabela hash,
   o tratamento de colisao é feito por endereçamento aberto
   e o reespalhamento é linear
   retorna o hash com o valor inserido
*/
PHash insere(PHash hash, char *valor) {
    int chave = 0;

    // indice da tabela hash onde será armazenado o valor dado na entrada
    chave = f_hash(hash, valor);
    while(chave >= 0 && chave < hash->tamanho) {
        if(*hash->tabela[chave].valor == NULL) {
            *hash->tabela[chave].valor = valor;
             return hash;
        }
        // reespalhamento linear caso a posição esteja ocupada
        chave = (chave + 1) % hash->tamanho;
    }

    return hash;
}

/* remove da tabela hash o valor dado na entrada,
   o tratamento de colisao é feito por endereçamento aberto
   e o reespalhamento é linear
   retorna o valor removido caso ele exista ou NULL
*/
char *remove_valor(PHash hash, char *valor) {
    int chave = 0;
    char *valor_a_trocar = NULL;
    char *removido = NULL;

    // busca chave do valor na tabela sem a colisão
    chave = f_hash(hash, valor);

    // valor não está na tabela
    if(!busca(hash, valor)) {
        return NULL;
    }

    // procura valor na tabela caso tem havido colisão na sua inserção
    while(strcmp(*hash->tabela[chave].valor, valor) != 0) {
        chave = (chave + 1) % hash->tamanho;
    }

    // remove valor
    removido = malloc(N_CHAR * sizeof(char));
    strcpy(removido, *hash->tabela[chave].valor);
    free(*hash->tabela[chave].valor);
    *hash->tabela[chave].valor = NULL;

    // reinsere os valores que sofreram colisão
    // e sofreram reespalhamento
    // devido ao valor agora removido
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

/* busca pelo valor dado na entrada
   simula a inserção calculando a
   função de hashing e percorre a tabela
   em sequencia procurando pela chave
   retorna o valor encontrado ou NULL se não hourver valor
*/
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

/* imprime tabela hash mostrando chave e valor
   e o numero total de posicoes na tabela
 */
void imprime_tabela_hash(PHash hash) {
    printf("Hash com %d posicoes\n", hash->tamanho);

    for (int i = 0; i < hash->tamanho; i++) {
        if(*hash->tabela[i].valor != NULL) {
            printf("chave: %d, valor: %s\n", i, *hash->tabela[i].valor);
        }
    }
}
