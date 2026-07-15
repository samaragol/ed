#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"
#include "node.h"

/**
 * @brief Construct a new Linked List:: Linked List object
 *  Allocates memory for a new linked list and returns a pointer to it.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the linked list using forward_list_destroy().
 *
 */
ForwardList *forward_list_construct()
{
    ForwardList *l;

    l = (ForwardList *)malloc(1 * sizeof(ForwardList));
    l->head = NULL;
    l->size = 0;
    return l;
}

/**
 * @brief Returns the size of the linked list.
 *  Returns the number of nodes in the linked list.
 * @param l
 * Pointer to the linked list.
 * @return int
 * Number of nodes in the linked list.
 *
 */
int forward_list_size(ForwardList *l)
{
    return l->size;
}

/**
 * @brief Pushes a new node to the front of the linked list.
 *  Allocates memory for a new node and inserts it at the front of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new node.
 *
 */
void forward_list_push_front(ForwardList *l, data_type data)
{
    Node *novo = node_construct(data, l->head);
    l->head = novo;
    l->size++;
}

/**
 * @brief Pushes a new node to the back of the linked list.
 *  Allocates memory for a new node and inserts it at the front of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new node.
 *
 */
void forward_list_push_back(ForwardList *l, data_type data)
{
    Node *novo = node_construct(data, NULL);
    if (l->head == NULL)
    {
        l->head = novo;
    }
    else
    {
        Node *atual = l->head;
        while (atual->next != NULL)
        {
            atual = atual->next;
        }
        atual->next = novo;
    }
    l->size++;
}

/**
 * @brief Print the elements of the linked list.
 *  Print the elements of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 *
 */
void forward_list_print(ForwardList *l, void (*print_fn)(data_type))
{
    Node *n = l->head;

    while (n != NULL)
    {
        print_fn(n->value);
        n = n->next;
    }
}

/**
 * @brief Returns the data stored in the node at the given index.
 * @param l
 * Pointer to the linked list.
 * @param i
 * Index of the node.
 * @return data_type
 * Data stored in the node at the given index.
 *
 */
data_type forward_list_get(ForwardList *l, int i)
{
    int indice = 0;
    Node *node = l->head;

    while (node != NULL && indice < i)
    {
        node = node->next;
        indice++;
    }

    return node->value;
}

/**
 * @brief Remove the first node of the linked list and returns its data.
 * @param l
 * Pointer to the linked list.
 * @return data_type
 * Pointer to the data stored in the first node of the linked list that was removed.
 *
 */
data_type forward_list_pop_front(ForwardList *l)
{
    Node *removido = l->head;
    data_type valor = removido->value;

    l->head = removido->next;
    free(removido);
    l->size--;

    return valor;
}

/**
 * @brief Remove the node in the given index.
 * @param l
 * Pointer to the linked list.
 * @return data_type
 * Pointer to the data stored in the removed node.
 *
 */
data_type forward_list_pop_index(ForwardList *l, int index)
{
    if (index < 0 || index >= forward_list_size(l))
    {
        printf("INVALID INDEX\n");
        return 0;
    }
    if (index == 0)
    {
        return forward_list_pop_front(l);
    }

    Node *anterior = l->head;
    for (int i = 0; i < index - 1; i++)
    {
        anterior = anterior->next;
    }

    Node *removido = anterior->next;
    data_type valor = removido->value;
    anterior->next = removido->next;
    free(removido);
    l->size--;

    return valor;
}

/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the linked list.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 */
ForwardList *forward_list_reverse(ForwardList *l)
{
    ForwardList *invertida = forward_list_construct();

    for (Node *node = l->head; node != NULL; node = node->next)
    {
        forward_list_push_front(invertida, node->value);
    }

    return invertida;
}

/**
 * @brief Removes all nodes from the linked list.
 * Removes all nodes from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the data stored in the nodes.
 */
void forward_list_clear(ForwardList *l)
{
    node_destroy(l->head);
    l->head = NULL;
    l->size = 0;
}

/**
 * @brief Removes all nodes with the given value from the linked list.
 * Removes all nodes with the given value from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @param val
 * Value to be removed from the linked list.
 */
void forward_list_remove(ForwardList *l, data_type val)
{
    while (l->head != NULL && l->head->value == val)
    {
        Node *removido = l->head;
        l->head = removido->next;
        free(removido);
        l->size--;
    }

    Node *anterior = l->head;
    while (anterior != NULL && anterior->next != NULL)
    {
        Node *atual = anterior->next;
        if (atual->value == val)
        {
            anterior->next = atual->next;
            free(atual);
            l->size--;
        }
        else
        {
            anterior = atual;
        }
    }
}

/**
 * @brief Removes all duplicate values from the linked list.
 * Removes all duplicate values from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The linked list must be sorted.
 */
void forward_list_unique(ForwardList *l)
{
    Node *atual = l->head;
    while (atual != NULL && atual->next != NULL)
    {
        if (atual->value == atual->next->value)
        {
            Node *removido = atual->next;
            atual->next = removido->next;
            free(removido);
            l->size--;
        }
        else
        {
            atual = atual->next;
        }
    }
}

/**
 * @brief Adds all nodes from the given list to the end of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param m
 * Pointer to the linked list to be added to the end of the linked list.
 */
void forward_list_cat(ForwardList *l, ForwardList *m)
{
    if (l == NULL || m == NULL || m->head == NULL)
    {
        return;
    }

    if (l->head == NULL)
    {
        l->head = m->head;
    }
    else
    {
        l->size += m->size;
        Node *n = m->head;
        while (n != NULL)
        {
            forward_list_push_front(l, n->value);
            n = n->next;
        }
    }

    m->head = NULL;
    m->size = 0;
}

/**
 * @brief Sorts the linked list.
 * Sorts the linked list.
 * @param l
 * Pointer to the linked list.
 */
void forward_list_sort(ForwardList *l, compara_fn compara)
{
    int trocou;
    do
    {
        trocou = 0;
        Node *atual = l->head;
        while (atual->next != NULL)
        {
            Node *proximo = atual->next;
            if (compara(atual->value, proximo->value))
            {
                data_type temp = atual->value;
                atual->value = proximo->value;
                proximo->value = temp;
                trocou = 1;
            }
            atual = proximo;
        }
    } while (trocou);
}

/**
 * @brief Destroys the linked list.
 *  Frees the memory allocated for the linked list and all its nodes.
 * @param l
 * Pointer to the linked list.
 *
 */
void forward_list_destroy(ForwardList *l)
{
    forward_list_clear(l);
    free(l);
}