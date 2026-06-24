#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "forward_list.h"

struct HashTable
{
    int table_size;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    ForwardList **buckets;
    int n_elements;
};

struct HashTableIterator
{
    Node no_atual;
    int indice;
    HashTable *h;
};

// constroi a hash
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *h;

    h = (HashTable *)calloc(1, sizeof(HashTable));

    h->table_size = table_size;
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;
    h->buckets = (ForwardList **)calloc(table_size, sizeof(ForwardList *));
    return h;
}

// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val)
{
    int i = h->hash_fn(h, key);

    if (!(i >= 0 && i < h->table_size))
    {
        printf("Índice fora da tabela.\n");
        return NULL;
    }

    if (h->buckets[i] == NULL)
        h->buckets[i] = forward_list_construct();

    Node *node = h->buckets[i]->head;
    while (node != NULL)
    {
        HashTableItem *item = (HashTableItem *)node->value;
        if (h->cmp_fn(item->key, key) == 0)
        {
            void *old_val = item->val;
            item->val = val;
            return old_val;
        }
        node = node->next;
    }

    HashTableItem *hti = (HashTableItem *)calloc(1, sizeof(HashTableItem));
    hti->key = key;
    hti->val = val;
    forward_list_push_front(h->buckets[i], hti);
    h->n_elements++;
    return NULL;
}

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key)
{
    int i = h->hash_fn(h, key);

    if (!(i >= 0 && i < h->table_size))
    {
        printf("Índice fora da tabela.\n");
        return NULL;
    }

    if (h->buckets[i] == NULL)
        return NULL;

    Node *node = h->buckets[i]->head;
    while (node != NULL)
    {
        HashTableItem *item = (HashTableItem *)node->value;
        if (h->cmp_fn(item->key, key) == 0)
            return item->val;
        node = node->next;
    }

    return NULL;
}

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void *hash_table_pop(HashTable *h, void *key)
{
    int i = h->hash_fn(h, key);

    if (!(i >= 0 && i < h->table_size))
    {
        printf("Índice fora da tabela.\n");
        return NULL;
    }

    if (h->buckets[i] == NULL)
        return NULL;

    Node *prev = NULL;
    Node *node = h->buckets[i]->head;
    while (node != NULL)
    {
        HashTableItem *item = (HashTableItem *)node->value;
        if (h->cmp_fn(item->key, key) == 0)
        {
            void *val = item->val;
            if (prev == NULL)
                h->buckets[i]->head = node->next;
            else
                prev->next = node->next;

            free(item->key);
            free(item);
            free(node);
            h->buckets[i]->size--;
            h->n_elements--;
            return val;
        }
        prev = node;
        node = node->next;
    }

    return NULL;
}

// numero de buckets
int hash_table_size(HashTable *h)
{
    return h->table_size;
}

// numero de elementos inseridos
int hash_table_num_elems(HashTable *h)
{
    return h->n_elements;
}

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;

            while (n != NULL)
            {
                HashTableItem *pair = (HashTableItem *)n->value;
                free((char *)((*pair).key));
                free((char *)(*pair).val);
                free(pair);
                n = n->next;
            }

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

// cria um novo iterador para a tabela hash
HashTableIterator *hash_table_iterator(HashTable *h)
{
    HashTableIterator *hi;

    hi = (HashTableIterator *)calloc(1, sizeof(HashTableIterator));
    hi->h = h;
    return hi;
}

// retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrario
int hash_table_iterator_is_over(HashTableIterator *it);

// retorna o proximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it);

// desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it);