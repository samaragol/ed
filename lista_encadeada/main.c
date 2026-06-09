#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "forward_list.h"

int comparaInt(data_type dado1, data_type dado2)
{
    int *d1 = (int *)dado1;
    int *d2 = (int *)dado2;

    if (*d1 > *d2)
    {
        return 1;
    }

    return 0;
}

void print_data(data_type data)
{
    printf("%d\n", *((int *)data));
}

int main()
{
    int num_instructions;
    scanf(" %d", &num_instructions);

    ForwardList *list = forward_list_construct();

    for (int i = 0; i < num_instructions; i++)
    {
        int *value = (int *)malloc(sizeof(int));
        scanf(" %d", value);
        forward_list_push_front(list, value);
    }

    forward_list_sort(list, comparaInt);

    forward_list_print(list, print_data);

    forward_list_clear(list);

    forward_list_destroy(list);

    return 0;
}