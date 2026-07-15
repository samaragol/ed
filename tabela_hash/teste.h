#ifndef _HASH_H_
#include "forward_list.h"

typedef struct HashTable HashTable;
typedef int (*HashFunction)(HashTable *h, void *dado); // nao eh definida aqui essa budega
typedef int (*CmpFunction)(void *dado1, void *dado2);

struct HashTable
{
    ForwardList **buckets;
    int table_size;
    int n_elemtente
    HashFunction hash_fn;
    CmpFunction cmp_fn;
};
typedef struct HashTableItem
{
    void *key;
    void *valor;
} HashTableItem;
typedef struct HashItarator
{
    Node *current;
    int idx_bucket;
    HashTable *h;
} HashItarator;

HashTable *hash_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn);
void hash_destroy(HashTable *h)

#endif