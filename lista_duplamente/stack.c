#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "stack.h"

Stack *stack_construct()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->l = list_construct();
    return s;
}
void stack_push(Stack *s, data_type dado)
{
    list_push_front(s->l, dado);
}
data_type stack_pop(Stack *s)
{
    return list_pop_front(s->l);
}
int stack_size(Stack *s)
{
    return list_size(s->l);
}
void stack_destroy(Stack *s)
{
    list_destroy(s->l);
    free(s);
}