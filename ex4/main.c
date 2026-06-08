#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "deque.h"

int main()
{
    Deque *f;
    char opc[20];
    int qtd;
    int item;
    int idx;

    f = deque_construct();

    scanf("%d", &qtd);

    for (int i = 0; i < qtd; i++)
    {
        scanf(" %s", opc);

        if (!strcmp(opc, "PUSH_BACK"))
        {
            scanf(" %d", &item);
            deque_push_back(f, item);
        }
        else if (!strcmp(opc, "PUSH_FRONT"))
        {
            scanf(" %d", &item);
            deque_push_front(f, item);
        }
        else if (!strcmp(opc, "POP_BACK"))
        {
            item = deque_pop_back(f);
            printf(" %d\n", item);
        }
        else if (!strcmp(opc, "POP_FRONT"))
        {
            item = deque_pop_front(f);
            printf(" %d\n", item);
        }
        else if (!strcmp(opc, "GET"))
        {
            scanf(" %d", &idx);
            item = deque_get(f, idx);
            printf(" %d\n", item);
        }
    }

    deque_destroy(f);
    return 0;
}