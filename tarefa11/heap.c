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
    heap->v_dados = malloc(tam_max * sizeof(int));

    return heap;
}

// destroi o heap e o vetor de dados
void destroi_heap(PHeap heap) {
    free(heap->v_dados);
    free(heap);
}

// troca os valores de x e y
void troca(int *x, int *y) {
    int aux;

    aux = *x;
    *x = *y;
    *y = aux;
}

// sobe no heap a partir do indice dado
// e troca com o pai se necessario (se o valor do heap
// no indice for menor que o valor do heap no pai)
void sobe_heap(PHeap heap, int indice) {
    int pai;

    pai = obtem_pai(indice);

    if( (pai >= 0) && (heap->v_dados[pai] > heap->v_dados[indice]) ) {
        troca(&heap->v_dados[indice], &heap->v_dados[pai]);
        pai = obtem_pai(indice);
        sobe_heap(heap, pai);
    }
}

// desce no heap a partir do indice dado
void desce_heap (PHeap heap, int indice) {
    int menor, esq, dir;

    // obtem filho esquerdo e filho direito do heap no indice dado
    esq = obtem_fesq(indice);
    dir = obtem_fdir(indice);

    // se filho esquerdo for menor que o pai
    // menor passa a ser o filho esquerdo, caso contrario, passa a ser o indice
    if ((esq < heap->n_elementos) && (heap->v_dados[esq] < heap->v_dados[indice])) {
        menor = esq;
    } else {
        menor = indice;
    }

    // se filho direito for menor que o maior obtido anteriormente
    // menor passa a ser o filho direito
    if ((dir < heap->n_elementos) && (heap->v_dados[dir] < heap->v_dados[menor])) {
        menor = dir;
    }
    // se o menor não está no heap do indice dado
    // entao é realizada a troca e feita nova descida no heap
    if (menor != indice) {
        troca(&heap->v_dados[indice], &heap->v_dados[menor]);
        desce_heap(heap, menor);
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
PHeap insere(PHeap heap, int dado) {
    // verifica se elemento já não foi inserido no heap
    // se já foi inserido retorna o heap
    for (int i = 0; i < heap->n_elementos; i++) {
        if(heap->v_dados[i] == dado) {
            return heap;
        }
    }

    if (!heap_cheio(heap)) {
        heap->n_elementos++;
        heap->v_dados[heap->n_elementos - 1] = dado;
        sobe_heap(heap, heap->n_elementos - 1);
    }

    return heap;
}

// remove o minimo do heap
// e retorna o minimo removido
int *remove_min(PHeap heap) {
    int *dado = NULL;

    if (heap_vazio(heap)) {
        return NULL;
    }

    // guarda informação do minimo removido na variavel dado
    dado = malloc(sizeof(int));
    *dado = heap->v_dados[0];
    heap->v_dados[0]  = heap->v_dados[heap->n_elementos - 1];
    heap->n_elementos--;
    // desce no heap arrumando os dados
    // trocando o pai com o menor dos dois filhos, se necessario
    desce_heap(heap, 0);

    return dado;
}

// imprime sequencia do heap em ordem
// sequencial dos indices do vetor
void imprime_sequencia(PHeap heap) {
    for (int i = 0; i < heap->n_elementos; i++) {
        printf("%d ", heap->v_dados[i]);
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
        printf("%d", heap->v_dados[indice]);
        for (int i = 0; i <= log2(heap->n_elementos) - nivel; i++) {
            printf("---");
        }
        printf("\n");
        imprime_heap(heap, obtem_fesq(indice), nivel + 1);
    }
}
