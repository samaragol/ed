#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

#define TAM_ALLOCATED 20

struct Deque
{
    void **data;
    int inicio;
    int fim;
    int size;
    int allocated;
};

Deque *deque_construct()
{
    Deque *d;
    d = (Deque *)calloc(1, sizeof(Deque));
    d->allocated = TAM_ALLOCATED;
    d->data = (void **)calloc(d->allocated, sizeof(void *));
    return d;
}
void deque_push_back(Deque *f, int item)
{
    if (f->allocated == f->size)
    {
        Deque *aux;
        f->allocated *= 2;
        aux = (Deque *)calloc(f->allocated, sizeof(Deque));
        aux->allocated = f->allocated;
        deque_push_back(aux, deque_pop_front(f));
        f = aux;
    }
    int *dado;
    dado = (int *)malloc(1 * sizeof(int));
    *dado = item;
    f->data[f->fim] = (void *)dado;
    f->fim = (f->fim + 1) % f->allocated;
    f->size++;
}
void deque_push_front(Deque *f, int item)
{
    if (f->allocated == f->size)
    {
        Deque *aux;
        f->allocated *= 2;
        aux = (Deque *)calloc(f->allocated, sizeof(Deque));
        aux->allocated = f->allocated;
        deque_push_back(aux, deque_pop_front(f));
        f = aux;
    }
    int *dado;
    dado = (int *)malloc(1 * sizeof(int));
    *dado = item;
    f->inicio = ((f->inicio + f->allocated) - 1) % f->allocated;
    f->data[f->inicio] = (void *)dado;
    f->size++;
}
int deque_pop_back(Deque *f)
{
    int item;
    int *dado;
    f->fim = ((f->fim + f->allocated) - 1) % f->allocated;
    dado = (int *)f->data[f->fim];
    f->size--;
    item = *dado;
    free(dado);
    return item;
}
int deque_pop_front(Deque *f)
{
    int item;
    int *dado;
    dado = (int *)f->data[f->inicio];
    f->inicio = (f->inicio + 1) % f->allocated;
    f->size--;
    item = *dado;
    free(dado);
    return item;
}
int deque_get(Deque *f, int idx)
{
    int *dado;
    if (idx >= 0 && idx < f->size)
    {
        dado = (int *)f->data[(f->inicio + idx) % f->allocated];
        return *dado;
    }
    printf("Índice inválido.\n");
    return -1;
}
void deque_destroy(Deque *f)
{
    while (f->inicio != f->fim)
    {
        free(f->data[f->inicio]);
        f->inicio = (f->inicio + 1) % f->allocated;
    }
    free(f->data);
    free(f);
}