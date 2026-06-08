#ifndef _HEAP_H_
#define _HEAP_H_

typedef void *data_type;
// Função de comparação. Deve retornar valor > 0 se primeiro elemento tem maior prioridade e valor < 0 se o segundo em mais prioridade.
typedef int (*cmp_fn)(void *a, void *b);

typedef struct Heap Heap;

// Cria um heap vazio
Heap *heap_construct(cmp_fn cmp);

// Libera memória do heap
void heap_destroy(Heap *h);

// Insere um elemento no heap
void heap_push(Heap *h, data_type value);

// Remove e retorna o elemento de maior prioridade
data_type heap_pop(Heap *h);

// Retorna o número de elementos
int heap_size(Heap *h);

// Verifica se está vazio
int heap_empty(Heap *h);

data_type heap_get(Heap *h, int i);

#endif