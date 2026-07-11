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

struct BinaryTree
{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

// FUNÇÔES AUXILIARES
////////////////////////////////////////////////////////////////////
static Node *add_recursive(Node *root,
                           Node *novo,
                           BinaryTree *bt)
{
    if (root == NULL)
        return novo;

    int cmp = bt->cmp_fn(novo->k->key, root->k->key);

    if (cmp < 0)
        root->left = add_recursive(root->left, novo, bt);

    else if (cmp > 0)
        root->right = add_recursive(root->right, novo, bt);

    else
    {
        bt->key_destroy_fn(novo->k->key);
        bt->val_destroy_fn(novo->k->value);
        key_val_pair_destroy(novo->k);
        free(novo);
    }

    return root;
}

static void destroy_nodes(Node *node, BinaryTree *bt)
{
    if (node == NULL)
        return;

    destroy_nodes(node->left, bt);
    destroy_nodes(node->right, bt);

    bt->key_destroy_fn(node->k->key);
    bt->val_destroy_fn(node->k->value);

    key_val_pair_destroy(node->k);
    free(node);
}
////////////////////////////////////////////////////////////////////

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
    Node *novo = calloc(1, sizeof(Node));
    novo->k = key_val_pair_construct(key, value);

    if (bt->root == NULL)
    {
        bt->root = novo;
        return;
    }

    Node *curr = bt->root;

    while (1)
    {
        int cmp = bt->cmp_fn(key, curr->k->key);

        if (cmp == 0)
        {
            bt->key_destroy_fn(key);
            bt->val_destroy_fn(value);
            key_val_pair_destroy(novo->k);
            free(novo);
            return;
        }

        if (cmp < 0)
        {
            if (curr->left == NULL)
            {
                curr->left = novo;
                return;
            }

            curr = curr->left;
        }
        else
        {
            if (curr->right == NULL)
            {
                curr->right = novo;
                return;
            }

            curr = curr->right;
        }
    }
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value)
{
    Node *novo = calloc(1, sizeof(Node));
    novo->k = key_val_pair_construct(key, value);

    bt->root = add_recursive(bt->root, novo, bt);
}
int binary_tree_empty(BinaryTree *bt)
{
    return bt->root == NULL;
}
void binary_tree_remove(BinaryTree *bt, void *key);
KeyValPair *binary_tree_min(BinaryTree *bt)
{
    if (bt->root == NULL)
        return NULL;

    Node *curr = bt->root;

    while (curr->left != NULL)
        curr = curr->left;

    return curr->k;
}
KeyValPair *binary_tree_max(BinaryTree *bt)
{
    if (bt->root == NULL)
        return NULL;

    Node *curr = bt->root;

    while (curr->right != NULL)
        curr = curr->right;

    return curr->k;
}
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);
Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key);
void *binary_tree_get(BinaryTree *bt, void *key)
{
    Node *curr = bt->root;

    while (curr != NULL)
    {
        int cmp = bt->cmp_fn(key, curr->k->key);

        if (cmp == 0)
            return curr->k->value;

        if (cmp < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }

    return NULL;
}
void binary_tree_destroy(BinaryTree *bt)
{
    destroy_nodes(bt->root, bt);
    free(bt);
}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);
