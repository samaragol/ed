#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "atendimento.h"
#include "frame.h"

int main()
{
    Queue *q;
    int qtd;
    char opc[20];
    char tipo[20];
    int tam;

    scanf(" %s", tipo);
    scanf(" %d", &qtd);

    if (!strcmp(tipo, "SENHAS"))
    {
        tam = 10;
    }
    else
    {
        tam = 20;
    }
    q = queue_constructor(tam);

    for (int i = 0; i < qtd; i++)
    {
        scanf(" %s", opc);

        if (!strcmp(opc, "ADICIONAR"))
        {

            if (!strcmp(tipo, "SENHAS"))
            {
                Atendimento *a;
                char nome[50];
                char cpf[12];
                scanf(" %s %s", nome, cpf);
                if (queue_is_full(q))
                {
                    printf("FILA CHEIA\n");
                }
                else
                {
                    a = atendimento_constructor(nome, cpf);
                    queue_add(q, a);
                }
            }
            else // streaming
            {
                Frame *f;
                char video_id[50];
                int frame_id;
                float timestamp;
                scanf(" %s %d %f", video_id, &frame_id, &timestamp);
                if (queue_is_full(q))
                {
                    printf("FILA CHEIA\n");
                }
                else
                {
                    f = frame_constructor(video_id, frame_id, timestamp);
                    queue_add(q, f);
                }
            }
        }
        else if (!strcmp(opc, "CHAMAR"))
        {
            Atendimento *a;
            if (queue_is_empty(q))
            {
                printf("FILA VAZIA\n");
            }
            else
            {
                a = (Atendimento *)queue_remove(q);
                printf("%s\n", atendimento_get_nome(a));
                atendimento_destroy(a);
            }
        }
        else if (!strcmp(opc, "PLAY"))
        {
            if (queue_is_empty(q))
            {
                printf("FILA VAZIA\n");
            }
            else if (queue_size(q) < 5)
            {
                printf("AGUARDE\n");
            }
            else
            {
                for (int i = 0; i < 5; i++)
                {
                    Frame *f;
                    f = (Frame *)(queue_remove(q));
                    printf("ID: %d, Timestamp: %.2f\n", frame_get_frame_id(f), frame_get_timestamp(f));
                    frame_destroy(f);
                }
            }
        }
    }

    while (!queue_is_empty(q))
    {
        if (!strcmp(tipo, "SENHAS"))
        {
            atendimento_destroy((Atendimento *)(queue_remove(q)));
        }
        else
        {
            frame_destroy((Frame *)(queue_remove(q)));
        }
    }

    queue_destroy(q);

    return 0;
}