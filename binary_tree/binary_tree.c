#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

// typedef struct
// {
//     void *key;
//     void *value;
// } KeyValPair;

KeyValPair *key_val_pair_construct(void *key, void *val)
{
    KeyValPair *k = (KeyValPair *)calloc(1, sizeof(KeyValPair));
    k->key = key;
    k->value = val;
    return k;
}
void key_val_pair_destroy(KeyValPair *kvp)
{
    free(kvp);
}

typedef struct Node
{
    KeyValPair *k;
    struct Node *left;
    struct Node *right;
} Node;

Node *node_construct(KeyValPair *k, Node *left, Node *right)
{
    Node *n = (Node *)calloc(1, sizeof(Node));
    n->k = k;
    n->left = left;
    n->right = right;
    return n;
}

struct BinaryTree
{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn)
{
    BinaryTree *b = (BinaryTree *)calloc(1, sizeof(BinaryTree));
    b->cmp_fn = cmp_fn;
    b->key_destroy_fn = key_destroy_fn;
    b->val_destroy_fn = val_destroy_fn;
    return b;
}
void binary_tree_add(BinaryTree *bt, void *key, void *value)
{
    KeyValPair *k = key_val_pair_construct(key, value);
    Node *prev = bt->root;
    Node *prox = bt->root;

    while (1)
    {
        if (prox == NULL)
        {
            Node *novo = node_construct(k, NULL, NULL);
            prox = novo;
            return;
        }
        if (bt->cmp_fn(prox->k->value, k->value))
        {
        }
        // to tentando entender ainda
    }
}
void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key);
KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);
Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key);
void *binary_tree_get(BinaryTree *bt, void *key);
void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);
