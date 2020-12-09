#include "heap.h"

// retorna o indice do pai
int obtem_pai(int indice) {
    return (indice - 1) / 2;
}

// retorna o indice do filho esquerdo
int obtem_fesq(int indice) {
    return 2*indice + 1;
}

// retorna o indice do filho direito
int obtem_fdir(int indice) {
    return 2*indice + 2;
}

// cria heap de tamanho tam_max
// e retorna o heap
PHeap cria_heap(int tam_max) {
    PHeap heap = malloc(sizeof(Heap));

    heap->tam_max = tam_max;
    heap->n_elementos = 0;
    heap->v_dados = malloc(tam_max * sizeof(Cliente));

    return heap;
}

// destroi o heap e o vetor de dados
void destroi_heap(PHeap heap) {
    free(heap->v_dados);
    free(heap);
}

// troca os valores de x e y
void troca(Cliente *x, Cliente *y) {
    Cliente aux;

    aux = *x;
    *x = *y;
    *y = aux;
}

// sobe no heap a partir do indice dado
// e troca com o pai se necessario (se o valor do heap
// no indice for maior que o valor do heap no pai)
void sobe_heap(PHeap heap, int indice) {
    int pai;

    pai = obtem_pai(indice);
    if( (pai >= 0) && (heap->v_dados[pai].avaliacao < heap->v_dados[indice].avaliacao) ) {
        troca(&heap->v_dados[indice], &heap->v_dados[pai]);
        pai = obtem_pai(indice);
        sobe_heap(heap, pai);
    }
}

// desce no heap a partir do indice dado
void desce_heap (PHeap heap, int indice) {
    int maior, esq, dir;

    // obtem filho esquerdo e filho direito do heap no indice dado
    esq = obtem_fesq(indice);
    dir = obtem_fdir(indice);

    // se filho esquerdo for maior que o pai
    // maior passa a ser o filho esquerdo, caso contrario, passa a ser o indice
    if ((esq < heap->n_elementos) && (heap->v_dados[esq].avaliacao > heap->v_dados[indice].avaliacao)) {
        maior = esq;
    } else {
        maior = indice;
    }

    // se filho direito for maior que o maior obtido anteriormente
    // maior passa a ser o filho direito
    if ((dir < heap->n_elementos) && (heap->v_dados[dir].avaliacao > heap->v_dados[maior].avaliacao)) {
        maior = dir;
    }

    // se o maior não está no heap do indice dado
    // entao é realizada a troca e feita nova descida no heap
    if (maior != indice) {
        troca(&heap->v_dados[indice], &heap->v_dados[maior]);
        desce_heap(heap, maior);
    }
}

// verifica se o heap está cheio
// retornando TRUE se estiver cheio
// e FALSE caso contrario
Boolean heap_cheio(PHeap heap) {
    if (heap->n_elementos >= heap->tam_max) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// verifica se o heap está vazio
// retornando TRUE se estiver vazio
// e FALSE caso contrario
Boolean heap_vazio(PHeap heap) {
    if (heap->n_elementos <= 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// insere dado no heap se ele não estiver cheio
// e retorna o heap com o novo dado inserido
PHeap insere(PHeap heap, Cliente dado) {
    if (!heap_cheio(heap)) {
        heap->n_elementos++;
        heap->v_dados[heap->n_elementos - 1] = dado;
        sobe_heap(heap, heap->n_elementos - 1);
    }

    return heap;
}

// remove o maximo do heap
// e retorna o maximo removido
Cliente *remove_max(PHeap heap) {
    Cliente *dado = NULL;

    if (heap_vazio(heap)) {
        return NULL;
    }

    // guarda informação do maximo removido na variavel dado
    dado = malloc(sizeof(Cliente));
    *dado = heap->v_dados[0];
    heap->v_dados[0]  = heap->v_dados[heap->n_elementos - 1];
    heap->n_elementos--;
    // desce no heap arrumando os dados
    // trocando o pai com o maior dos dois filhos, se necessario
    desce_heap(heap, 0);

    return dado;
}

// muda a prioridade de um elemento do heap com
// a string str como dado que passa a ter
// prioridade maxima, ou seja, se torna a raiz do heap
void maximiza_prioridade(PHeap heap, char *str) {
    for (int i = 0; i < heap->n_elementos; i++) {
        if(strcmp(str, heap->v_dados[i].nome) == 0) {
            heap->v_dados[i].avaliacao = 6;
            sobe_heap(heap, i);
        }
    }
}

// a cada iteração troca o maximo do heap,
// colocando ele na ultima posição do vetor
// e retorna o heap ordenado em ordem crescente,
// heap de maximo passa a ser heap de minimo
PHeap heap_sort(PHeap heap) {
    int n;

    n = heap->n_elementos;
    for (int i = heap->n_elementos - 1; i > 0; i--) {
        troca(&heap->v_dados[i], &heap->v_dados[0]);
        heap->n_elementos--;
        desce_heap(heap, 0);
    }
    heap->n_elementos = n;

    return heap;
}

// imprime sequencia do heap em ordem
// sequencial dos indices do vetor
void imprime_sequencia(PHeap heap) {
    for (int i = 0; i < heap->n_elementos; i++) {
        printf("%.16lf ", heap->v_dados[i].avaliacao);
    }
    printf("\n");

}

// imprime o heap
void imprime_heap(PHeap heap, int indice, int nivel) {
    if (indice < heap->n_elementos){
        imprime_heap(heap, obtem_fdir(indice), nivel + 1);
        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("%03.16lf", heap->v_dados[indice].avaliacao);
        for (int i = 0; i <= log2(heap->n_elementos) - nivel; i++) {
            printf("---");
        }
        printf("\n");
        imprime_heap(heap, obtem_fesq(indice), nivel + 1);
    }
}
