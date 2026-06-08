#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programa.h"
#include "queue.h"
#include "heap.h"

#define MAX_CAPACITY 100

int comparaPrioridade(void *dado1, void *dado2)
{
    Prog *d1;
    Prog *d2;

    // conversao de tipos
    d1 = (Prog *)dado1;
    d2 = (Prog *)dado2;

    // logica de comparacao
    if (prog_get_prioridade(d1) > prog_get_prioridade(d2))
    {
        return 1;
    }
    else if (prog_get_prioridade(d1) < prog_get_prioridade(d2))
    {
        return -1;
    }
    else if (prog_get_prioridade(d1) == prog_get_prioridade(d2))
    {
        if (!strcmp(prog_get_tipo(d1), "SO"))
        {
            if (prog_get_carga(d1) < prog_get_carga(d2))
            {
                return 1;
            }
            else if (prog_get_carga(d1) > prog_get_carga(d2))
            {
                return -1;
            }
            else
            {
                if (strcmp(prog_get_nome(d1), prog_get_nome(d2)) < 0)
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
        }
        else // !strcmp(prog_get_tipo(d1), "USER")
        {
            if (prog_get_ultimo_uso(d1) < prog_get_ultimo_uso(d2))
            {
                return 1;
            }
            else if (prog_get_ultimo_uso(d1) > prog_get_ultimo_uso(d2))
            {
                return -1;
            }
            else
            {
                if (strcmp(prog_get_nome(d1), prog_get_nome(d2)) < 0)
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
        }
    }
    return 0;
}

int main()
{
    // filas
    Queue *programas;
    Queue *rt;
    Heap *so;
    Heap *user;

    // variaveis de controle
    int qtd;
    int vez = 0;
    int iteracao = 0;

    // alocacao das filas
    rt = queue_constructor(MAX_CAPACITY);
    so = heap_construct(comparaPrioridade);
    user = heap_construct(comparaPrioridade);

    // leitura da quantidade de programas
    scanf("%d\n", &qtd);
    programas = queue_constructor(qtd);

    // loop do buffer
    for (int i = 0; i < qtd; i++)
    {
        Prog *p;
        p = prog_le();

        queue_add(programas, p);
    }

    // loop do gerenciador
    while (1)
    {
        Prog *p;

        //  adiciona programas na lista
        int size = queue_size(programas);
        for (int i = 0; i < size; i++)
        {
            int adicionou = 0;
            p = (Prog *)queue_remove(programas);
            if (!strcmp(prog_get_tipo(p), "RT") && prog_get_iteracao(p) == iteracao)
            {
                queue_add(rt, p);
                adicionou = 1;
            }
            else if (!strcmp(prog_get_tipo(p), "SO") && prog_get_iteracao(p) == iteracao)
            {
                heap_push(so, p);
                adicionou = 1;
            }
            else if (!strcmp(prog_get_tipo(p), "USER") && prog_get_iteracao(p) == iteracao)
            {
                heap_push(user, p);
                adicionou = 1;
            }
            if (!adicionou)
            {
                queue_add(programas, p);
            }
        }

        if (!queue_is_empty(rt))
        {
            p = (Prog *)queue_remove(rt);
            prog_decrementa_carga(p);
            prog_set_ultimo_uso(p, iteracao);
            if (prog_get_carga(p) == 0)
            {
                printf("%s %d\n", prog_get_nome(p), prog_get_ultimo_uso(p));
                prog_destroy(p);
            }
            else
            {
                queue_add(rt, p);
            }
        }
        else if (vez == 0)
        {
            // É vez de SO
            if (!heap_empty(so))
            {
                p = (Prog *)heap_pop(so);
                prog_decrementa_carga(p);
                prog_set_ultimo_uso(p, iteracao);
                if (prog_get_carga(p) == 0)
                {
                    printf("%s %d\n", prog_get_nome(p), prog_get_ultimo_uso(p));
                    prog_destroy(p);
                }
                else
                {
                    heap_push(so, p);
                }
                vez = 1;
            }
            else if (!heap_empty(user))
            {
                p = (Prog *)heap_pop(user);
                prog_decrementa_carga(p);
                prog_set_ultimo_uso(p, iteracao);
                if (prog_get_carga(p) == 0)
                {
                    printf("%s %d\n", prog_get_nome(p), prog_get_ultimo_uso(p));
                    prog_destroy(p);
                }
                else
                {
                    heap_push(user, p);
                }
                // vez continua 0
            }
        }
        else if (vez == 1)
        {
            // É vez de USER
            if (!heap_empty(user))
            {
                p = (Prog *)heap_pop(user);
                prog_decrementa_carga(p);
                prog_set_ultimo_uso(p, iteracao);
                if (prog_get_carga(p) == 0)
                {
                    printf("%s %d\n", prog_get_nome(p), prog_get_ultimo_uso(p));
                    prog_destroy(p);
                }
                else
                {
                    heap_push(user, p);
                }
                vez = 0;
            }
            else if (!heap_empty(so))
            {
                p = (Prog *)heap_pop(so);
                prog_decrementa_carga(p);
                prog_set_ultimo_uso(p, iteracao);
                if (prog_get_carga(p) == 0)
                {
                    printf("%s %d\n", prog_get_nome(p), prog_get_ultimo_uso(p));
                    prog_destroy(p);
                }
                else
                {
                    heap_push(so, p);
                }
                // vez continua 1
            }
        }

        if (queue_is_empty(rt) && heap_empty(so) && heap_empty(user))
        {
            break;
        }

        iteracao++;
    }

    queue_destroy(programas);
    queue_destroy(rt);
    heap_destroy(so);
    heap_destroy(user);

    return 0;
}