#ifndef _STACK_H_

#include "list.h"

typedef struct Stack
{
    List *l;
} Stack;

Stack *stack_construct();
void stack_push(Stack *s, data_type dado);
data_type stack_pop(Stack *s);
int stack_size(Stack *s);
void stack_destroy(Stack *s);

#endif