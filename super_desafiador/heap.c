#include "heap.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

struct Heap
{
    Vector *data;
    cmp_fn cmp;
};

// Cria um heap vazio
Heap *heap_construct(cmp_fn cmp)
{
    Heap *h = (Heap *)calloc(1, sizeof(Heap));
    h->data = vector_construct();
    h->cmp = cmp;
    return h;
}

// Libera memória do heap
void heap_destroy(Heap *h)
{
    vector_destroy(h->data);
    free(h);
}

// Insere um elemento no heap
void heap_push(Heap *h, data_type value)
{
    vector_push_back(h->data, value);

    if (heap_size(h) > 1)
    {
        int ind_filho = heap_size(h) - 1;
        int ind_pai = (ind_filho - 1) / 2;

        while (ind_filho > 0 && h->cmp(vector_get(h->data, ind_filho), vector_get(h->data, ind_pai)) > 0)
        {
            vector_swap(h->data, ind_filho, ind_pai);
            ind_filho = ind_pai;
            ind_pai = (ind_filho - 1) / 2;
        }
    }
}

// Remove e retorna o elemento de maior prioridade
data_type heap_pop(Heap *h)
{
    if (heap_empty(h))
        return NULL;

    int n = heap_size(h);
    if (n == 1)
        return vector_pop_back(h->data);

    vector_swap(h->data, 0, n - 1);
    data_type dado = vector_pop_back(h->data);

    int ind_pai = 0;
    while (1)
    {
        int ind_filho_e = 2 * ind_pai + 1;
        int ind_filho_d = 2 * ind_pai + 2;
        int maior = ind_pai;
        int sz = heap_size(h);

        if (ind_filho_e < sz && h->cmp(vector_get(h->data, ind_filho_e), vector_get(h->data, maior)) > 0)
            maior = ind_filho_e;

        if (ind_filho_d < sz && h->cmp(vector_get(h->data, ind_filho_d), vector_get(h->data, maior)) > 0)
            maior = ind_filho_d;

        if (maior == ind_pai)
            break;

        vector_swap(h->data, ind_pai, maior);
        ind_pai = maior;
    }

    return dado;
}

// Retorna o número de elementos
int heap_size(Heap *h)
{
    return vector_size(h->data);
}

// Verifica se está vazio
int heap_empty(Heap *h)
{
    return heap_size(h) == 0;
}

data_type heap_get(Heap *h, int i)
{
    return vector_get(h->data, i);
}
