#include <stdlib.h>
#include "hash.h"
#include "forward_list.h"

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

struct ListIterator
{
    HashTable* hash;
    int bucket;
    Node* atual;
};


// constroi a hash
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    HashTable* h = (HashTable*)calloc(1, sizeof(HashTable));

    h->cmp_fn = cmp_fn;
    h->hash_fn = hash_fn;
    h->table_size = table_size;
    h->buckets = (ForwardList**)calloc(h->table_size, sizeof(ForwardList*));

    return h;
}

// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val){
    int bucket = h->hash_fn(h, key) % h->table_size;

    if(h->buckets[bucket] == NULL){
        h->buckets[bucket] = forward_list_construct();
        HashTableItem* novo = (HashTableItem*)calloc(1, sizeof(HashTableItem));
        novo->key = key;
        novo->val = val;
        forward_list_push_front(h->buckets[bucket], novo);
        h->n_elements++;
        return NULL;
    } else {
        ListIterator* it = list_iterator_construct(h->buckets[bucket]);
        void* rtn = NULL;

        while(!list_iterator_is_over(it)){
            HashTableItem* item = *(HashTableItem**)list_iterator_next(it);
            if(h->cmp_fn(item->key, key) == 0){
                list_iterator_destroy(it);
                rtn = item->val;
                item->val = val;
                return rtn;
            }
        }

        list_iterator_destroy(it);

        HashTableItem* novo = (HashTableItem*)calloc(1, sizeof(HashTableItem));
        novo->key = key;
        novo->val = val;
        forward_list_push_front(h->buckets[bucket], novo);
        h->n_elements++;
        return NULL;
    }

}

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key){
    int bucket = h->hash_fn(h, key) % h->table_size;

    if(h->buckets[bucket] == NULL)
        return NULL;

    ListIterator* it = list_iterator_construct(h->buckets[bucket]);

    while(!list_iterator_is_over(it)){
        HashTableItem* item = *(HashTableItem**)list_iterator_next(it);
        if(h->cmp_fn(item->key, key) == 0){
            list_iterator_destroy(it);
            return item->val;
        }
    }

    list_iterator_destroy(it);

    return NULL;
}

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void *hash_table_pop(HashTable *h, void *key){

    int bucket = h->hash_fn(h, key) % h->table_size;


    if(h->buckets[bucket] == NULL)
        return NULL;


    Node *ant = NULL;
    Node *atual = h->buckets[bucket]->head;


    while(atual != NULL){

        HashTableItem *item = (HashTableItem*)atual->value;

        if(h->cmp_fn(item->key, key) == 0){

            void *val = item->val;

            if(ant == NULL)
                h->buckets[bucket]->head = atual->next;
            else
                ant->next = atual->next;


            node_destroy(atual);
            free(item->key);
            free(item);

            h->buckets[bucket]->size--;
            h->n_elements--;

            return val;
        }


        ant = atual;
        atual = atual->next;
    }


    return NULL;
}
// numero de buckets
int hash_table_size(HashTable *h){
    return h->table_size;
}

// numero de elementos inseridos
int hash_table_num_elems(HashTable *h){
    return h->n_elements;
}

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h){

    for(int i = 0; i < h->table_size; i++){

        if(h->buckets[i] != NULL){

            Node *atual = h->buckets[i]->head;

            while(atual != NULL){

                HashTableItem *item = (HashTableItem*)atual->value;

                free(item->key);
                free(item->val);
                free(item);

                atual = atual->next;
            }

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

// cria um novo iterador para a tabela hash
HashTableIterator *hash_table_iterator(HashTable *h){
    HashTableIterator* it = (HashTableIterator*)calloc(1, sizeof(HashTableIterator));

    it->hash = h;
    it->bucket = 0;
    it->atual = NULL;

    for(int i = 0; i < h->table_size; i++, it->bucket++){
        if(h->buckets[i] != NULL){
            it->atual = h->buckets[i]->head;
            return it;
        }
    }

    return it;
}

// retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrario
int hash_table_iterator_is_over(HashTableIterator *it){
    return it->atual == NULL;
}

// retorna o proximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it){

    if(it->atual == NULL)
        return NULL;


    HashTableItem *item = (HashTableItem*)it->atual->value;


    // ainda tem elemento na lista atual
    if(it->atual->next != NULL){
        it->atual = it->atual->next;
    }
    else{

        it->bucket++;

        it->atual = NULL;

        while(it->bucket < it->hash->table_size){

            if(it->hash->buckets[it->bucket] != NULL){

                it->atual = it->hash->buckets[it->bucket]->head;
                break;

            }

            it->bucket++;
        }
    }

    return item;
}

// desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it){
    free(it);
}

Vector *hash_to_vector(HashTable *h){

    Vector *v = vector_construct();

    HashTableIterator *it = hash_table_iterator(h);

    while(!hash_table_iterator_is_over(it)){

        HashTableItem *item = hash_table_iterator_next(it);

        vector_push_back(v, item);

    }

    hash_table_iterator_destroy(it);

    return v;
}