#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
    int n;
    char opc[10];

    Stack *s = stack_construct();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf(" %s", opc);

        if (!strcmp(opc, "PUSH"))
        {
            char *string = (char *)malloc(100 * sizeof(char));
            scanf(" %s", string);
            stack_push(s, string);
        }
        else if (!strcmp(opc, "POP"))
        {
            char *dado = (char *)stack_pop(s);
            printf("%s\n", dado);
            free(dado);
        }
    }

    int tam = stack_size(s);
    for (int i = 0; i < tam; i++)
    {
        free((char *)stack_pop(s));
    }
    stack_destroy(s);

    return 0;
}