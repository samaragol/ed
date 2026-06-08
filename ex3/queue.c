#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct Queue
{
    void **data;
    int inicio;
    int fim;
    int size;
    int allocated;
};

// Create an queue
Queue *queue_constructor(int max_capacity)
{
    Queue *q;

    q = (Queue *)calloc(1, sizeof(Queue));
    q->allocated = max_capacity;
    q->data = (void **)calloc(q->allocated, sizeof(void *));
    return q;
}

// Add an element
void queue_add(Queue *queue, void *data)
{
    queue->data[queue->fim] = data;
    queue->size++;
    queue->fim = (queue->fim + 1) % queue->allocated;
}

// Remove the oldest element in the queue
void *queue_remove(Queue *queue)
{
    void *dado;

    dado = queue->data[queue->inicio];
    queue->inicio = (queue->inicio + 1) % queue->allocated;
    queue->size--;
    return dado;
}

// Return the number of elements in the queue
int queue_size(Queue *queue)
{
    return queue->size;
}

// Return 1 if the queue is full and 0, otherwise
int queue_is_full(Queue *queue)
{
    if (queue->size == queue->allocated)
    {
        return 1;
    }
    return 0;
}

// Return 1 if the queue is empty and 0, otherwise
int queue_is_empty(Queue *queue)
{
    if (queue->size == 0)
    {
        return 1;
    }
    return 0;
}

// Free the data structure.
// IMPORTANT: the user of the lib is responsible for removing and freeing elements
// remaining in the queue. In the queue is not empty when the functions is called,
// the function will not release them.
void queue_destroy(Queue *queue)
{
    free(queue->data);
    free(queue);
}