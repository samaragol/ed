#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
#include "programa.h"

using namespace std;

struct Comparator
{
    bool operator()(Prog *d1, Prog *d2) const
    {
        // Maior prioridade primeiro
        if (prog_get_prioridade(d1) != prog_get_prioridade(d2))
            return prog_get_prioridade(d1) < prog_get_prioridade(d2);

        // Critérios de desempate
        if (!strcmp(prog_get_tipo(d1), "SO"))
        {
            if (prog_get_carga(d1) != prog_get_carga(d2))
                return prog_get_carga(d1) > prog_get_carga(d2);

            return strcmp(prog_get_nome(d1), prog_get_nome(d2)) > 0;
        }
        else
        {
            if (prog_get_ultimo_uso(d1) != prog_get_ultimo_uso(d2))
                return prog_get_ultimo_uso(d1) > prog_get_ultimo_uso(d2);

            return strcmp(prog_get_nome(d1), prog_get_nome(d2)) > 0;
        }
    }
};

int main()
{
    queue<Prog *> programas;
    queue<Prog *> rt;

    priority_queue<Prog *, vector<Prog *>, Comparator> so;
    priority_queue<Prog *, vector<Prog *>, Comparator> user;

    int qtd;
    int vez = 0;
    int iteracao = 0;

    scanf("%d", &qtd);

    // Leitura dos programas
    for (int i = 0; i < qtd; i++)
    {
        Prog *p = prog_le();
        programas.push(p);
    }

    while (1)
    {
        Prog *p;

        // Adiciona os programas que chegam nesta iteração
        int size = programas.size();

        for (int i = 0; i < size; i++)
        {
            p = programas.front();
            programas.pop();

            bool adicionou = false;

            if (!strcmp(prog_get_tipo(p), "RT") &&
                prog_get_iteracao(p) == iteracao)
            {
                rt.push(p);
                adicionou = true;
            }
            else if (!strcmp(prog_get_tipo(p), "SO") &&
                     prog_get_iteracao(p) == iteracao)
            {
                so.push(p);
                adicionou = true;
            }
            else if (!strcmp(prog_get_tipo(p), "USER") &&
                     prog_get_iteracao(p) == iteracao)
            {
                user.push(p);
                adicionou = true;
            }

            if (!adicionou)
                programas.push(p);
        }

        // RT sempre possui prioridade
        if (!rt.empty())
        {
            p = rt.front();
            rt.pop();

            prog_decrementa_carga(p);
            prog_set_ultimo_uso(p, iteracao);

            if (prog_get_carga(p) == 0)
            {
                printf("%s %d\n",
                       prog_get_nome(p),
                       prog_get_ultimo_uso(p));
                prog_destroy(p);
            }
            else
            {
                rt.push(p);
            }
        }
        else if (vez == 0)
        {
            // Executa SO
            if (!so.empty())
            {
                p = so.top();
                so.pop();

                prog_decrementa_carga(p);
                prog_set_ultimo_uso(p, iteracao);

                if (prog_get_carga(p) == 0)
                {
                    printf("%s %d\n",
                           prog_get_nome(p),
                           prog_get_ultimo_uso(p));
                    prog_destroy(p);
                }
                else
                {
                    so.push(p);
                }

                vez = 1;
            }
            else if (!user.empty())
            {
                p = user.top();
                user.pop();

                prog_decrementa_carga(p);
                prog_set_ultimo_uso(p, iteracao);

                if (prog_get_carga(p) == 0)
                {
                    printf("%s %d\n",
                           prog_get_nome(p),
                           prog_get_ultimo_uso(p));
                    prog_destroy(p);
                }
                else
                {
                    user.push(p);
                }
            }
        }
        else
        {
            // Executa USER
            if (!user.empty())
            {
                p = user.top();
                user.pop();

                prog_decrementa_carga(p);
                prog_set_ultimo_uso(p, iteracao);

                if (prog_get_carga(p) == 0)
                {
                    printf("%s %d\n",
                           prog_get_nome(p),
                           prog_get_ultimo_uso(p));
                    prog_destroy(p);
                }
                else
                {
                    user.push(p);
                }

                vez = 0;
            }
            else if (!so.empty())
            {
                p = so.top();
                so.pop();

                prog_decrementa_carga(p);
                prog_set_ultimo_uso(p, iteracao);

                if (prog_get_carga(p) == 0)
                {
                    printf("%s %d\n",
                           prog_get_nome(p),
                           prog_get_ultimo_uso(p));
                    prog_destroy(p);
                }
                else
                {
                    so.push(p);
                }
            }
        }

        // Fim da simulação
        if (programas.empty() &&
            rt.empty() &&
            so.empty() &&
            user.empty())
        {
            break;
        }

        iteracao++;
    }

    return 0;
}