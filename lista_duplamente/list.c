#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "list.h"

/**
 * @brief Construct a novo double linked list object
 *  Allocates memory for a novo double linked list and returns a pointer to it.
 * @return List*
 * Pointer to the novoly allocated double linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the double linked list using list_destroy().
 *
 */
List *list_construct()
{
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

/**
 * @brief Returns the size of the double linked list.
 *  Returns the number of nodes in the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @return int
 * Number of nodes in the double linked list.
 *
 */
int list_size(List *l)
{
    return l->size;
}

/**
 * @brief Pushes a novo node to the front of the double linked list.
 *  Allocates memory for a novo node and inserts it at the front of the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @param data
 * Pointer to the data to be stored in the novo node.
 *
 */
void list_push_front(List *l, data_type data)
{
    Node *novo;

    novo = node_construct(data, NULL, l->head);

    if (l->head == NULL)
    {
        l->head = novo;
        l->last = novo;
    }
    else
    {
        l->head->prev = novo;
        l->head = novo;
    }
    l->size++;
}

/**
 * @brief Pushes a novo node to the back of the double linked list.
 *
 * @param l
 * Pointer to the double linked list.
 * @param data
 * data to be stored in the novo node.
 */
void list_push_back(List *l, data_type data)
{
    Node *novo;

    novo = node_construct(data, l->last, NULL);
    if (l->head == NULL)
    {
        l->head = novo;
        l->last = novo;
    }
    else
    {
        l->last->next = novo;
        l->last = novo;
    }
    l->size++;
}

/**
 * @brief Print the elements of the double linked list.
 *  Print the elements of the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 *
 */
void list_print(List *l, void (*print_fn)(data_type))
{
    Node *atual;
    printf("[");
    for (atual = l->head; atual != NULL; atual = atual->next)
    {
        print_fn(atual->value);
        if (atual->next != NULL)
        {
            printf(", ");
        }
    }
    printf("]");
}

/**
 * @brief Print the elements of the double linked list in reverse order.
 * Print the elements of the double linked list in reverse order.
 * @param l
 * Pointer to the double linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 */
void list_print_reverse(List *l, void (*print_fn)(data_type))
{
    Node *atual;
    printf("[");
    for (atual = l->last; atual->prev != NULL; atual = atual->prev)
    {
        print_fn(atual->value);
        if (atual->prev != NULL)
        {
            printf(", ");
        }
    }
    printf("]");
}

/**
 * @brief Returns the data stored in the node at the given index.
 * @param l
 * Pointer to the double linked list.
 * @param i
 * Index of the node.
 * @return data_type
 * Data stored in the node at the given index.
 *
 */
data_type list_get(List *l, int i)
{
    Node *no;
    int index;

    if (i < 0 || i >= l->size)
    {
        printf("INVALID INDEX\n");
        return 0;
    }
    for (index = 0, no = l->head; index != i; index++)
    {
        no = no->next;
    }
    return no->value;
}

/**
 * @brief Remove the first node of the double linked list and returns its data.
 * @param l
 * Pointer to the double linked list.
 * @return data_type
 * Pointer to the data stored in the first node of the double linked list that was removed.
 *
 */
data_type list_pop_front(List *l)
{
    if (l->head == NULL)
    {
        return 0;
    }
    else
    {
        Node *removido;
        data_type dado;

        removido = l->head;
        dado = removido->value;
        l->head = removido->next;

        if (l->head != NULL)
        {
            l->head->prev = NULL;
        }
        else
        {
            l->last = NULL;
        }

        node_destroy(removido);
        l->size--;

        return dado;
    }
}

/**
 * @brief Remove the last node of the double linked list and returns its data.
 * @param l
 * Pointer to the double linked list.
 * @return data_type
 * Data stored in the last node of the double linked list that was removed.
 */
data_type list_pop_back(List *l)
{
    if (l->last == NULL)
    {
        return 0;
    }
    else
    {
        Node *removido;
        data_type dado;

        removido = l->last;
        dado = removido->value;

        if (removido->prev != NULL)
        {
            removido->prev->next = NULL;
        }
        else
        {
            l->head = NULL;
        }

        l->last = removido->prev;
        
        node_destroy(removido);
        l->size--;

        return dado;
    }
}

/**
 * @brief Create a novo list given by the reverse of the given list.
 * @param l
 * Pointer to the double linked list.
 * @return List*
 * Pointer to the novoly allocated double linked list.
 */
List *list_reverse(List *l);

/**
 * @brief Removes all nodes from the double linked list.
 * Removes all nodes from the double linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the double linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the data stored in the nodes.
 */
void list_clear(List *l)
{
    if (l->head == NULL)
    {
        return;
    }
    else
    {
        int tam = 10;

        for (int i = 0; i < tam; i++)
        {
            list_pop_front(l);
        }
    }
}

/**
 * @brief Removes all nodes with the given value from the double linked list.
 * Removes all nodes with the given value from the double linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the double linked list.
 * @param val
 * Value to be removed from the double linked list.
 */
void list_remove(List *l, data_type val);

/**
 * @brief Removes all duplicate values from the double linked list.
 * Removes all duplicate values from the double linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the double linked list.
 * @note
 * The double linked list must be sorted.
 */
void list_unique(List *l);

/**
 * @brief Adds all nodes from the given list to the end of the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @param m
 * Pointer to the double linked list to be added to the end of the double linked list.
 */
void list_cat(List *l, List *m);

/**
 * @brief Sorts the double linked list.
 * Sorts the double linked list.
 * @param l
 * Pointer to the double linked list.
 */
void list_sort(List *l);

/**
 * @brief Destroys the double linked list.
 *  Frees the memory allocated for the double linked list and all its nodes.
 * @param l
 * Pointer to the double linked list.
 *
 */
void list_destroy(List *l)
{
    list_clear(l);
    free(l);
}