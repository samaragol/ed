#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// typedef struct
// {
//     data_type *data;
//     int size;
//     int allocated;
// } Vector;

// Cria um vetor vazio
Vector *vector_construct()
{
    Vector *v;

    v = (Vector *)calloc(1, sizeof(Vector));
    v->allocated = 10;
    v->data = (data_type *)calloc(v->allocated, sizeof(data_type));
    return v;
}

// Adiciona um elemento no final do vetor
void vector_push_back(Vector *v, data_type val)
{
    if (v->size == v->allocated)
    {
        v->allocated *= 2;
        v->data = (data_type *)realloc(v->data, sizeof(data_type) * v->allocated);
    }

    v->data[v->size] = val;
    v->size++;
}

// Retorna o i-Ã©simo elemento do vetor
data_type vector_get(Vector *v, int i)
{
    return v->data[i];
}

// Atribui o valor val ao i-Ã©simo elemento do vetor
void vector_set(Vector *v, int i, data_type val);

// Retorna o tamanho do vetor
int vector_size(Vector *v)
{
    return v->size;
}

// Retorna o indice do primeiro elemento com valor val. Retorna -1 se nao encontrado.
int vector_find(Vector *v, data_type val);

// Retorna o maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_max(Vector *v);

// Retorna o menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_min(Vector *v);

// Retorna o Ã­ndice do maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmax(Vector *v)
{
    int ind_max = 0;

    for (int i = 0; i < v->size; i++)
    {
        if (v->data[ind_max] < v->data[i])
        {
            ind_max = i;
        }
    }

    return ind_max;
}

// Retorna o Ã­ndice do menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmin(Vector *v);

// Remove o i-Ã©simo elemento do vetor.
data_type vector_remove(Vector *v, int i);

// Remove o primeiro elemento
data_type vector_pop_front(Vector *v);

// Remove o ultimo elemento
data_type vector_pop_back(Vector *v)
{
    data_type dado;

    dado = v->data[v->size - 1];
    v->size--;
    return dado;
}

// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val);

// Troca os elementos das posiÃ§Ãµes i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j)
{
    data_type aux;

    aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v, int (*compara)(const void *, const void *))
{
    int min, i, j;

    for (i = 0; i < v->size; i++)
    {
        min = i;
        for (j = i + 1; j < v->size; j++)
        {
            if (compara(v->data[min], v->data[j]) >= 0)
            {
                min = j;
            }
        }

        if (i != min)
        {
            vector_swap(v, i, min);
        }
    }
}

// Inverte o vetor in-place (sem criar um novo vetor)
void vector_reverse(Vector *v);

// Cria uma cÃ³pia do vector e dos valores de seus atributos.
Vector *vector_copy(Vector *v);

// Remove todos os elementos de v
void vector_clear(Vector *v);

// Libera a memoria alocada para o vetor
void vector_destroy(Vector *v)
{
    free(v->data);
    free(v);
}
