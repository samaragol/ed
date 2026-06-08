#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programa.h"

#define MAX_NOME 65
#define MAX_TIPO 5

struct Prog
{
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
    int carga;
    int iteraçao;
    int ultimo_uso;
    int destruido;
};

Prog *prog_le()
{
    Prog *p;
    p = (Prog *)calloc(1, sizeof(Prog));

    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
    int carga;
    int iteracao;

    scanf(" %s %s %d %d %d", nome, tipo, &prioridade, &carga, &iteracao);

    strncpy(p->nome, nome, 65);
    strncpy(p->tipo, tipo, 5);
    p->prioridade = prioridade;
    p->carga = carga;
    p->iteraçao = iteracao;
    p->ultimo_uso = -1;

    return p;
}
void prog_decrementa_carga(Prog *p)
{
    p->carga--;
}
void prog_set_ultimo_uso(Prog *p, int i)
{
    p->ultimo_uso = i;
}
char *prog_get_nome(Prog *p)
{
    return p->nome;
}
char *prog_get_tipo(Prog *p)
{
    return p->tipo;
}
int prog_get_carga(Prog *p)
{
    return p->carga;
}
int prog_get_iteracao(Prog *p)
{
    return p->iteraçao;
}
int prog_get_ultimo_uso(Prog *p)
{
    return p->ultimo_uso;
}
int prog_get_prioridade(Prog *p)
{
    return p->prioridade;
}
int prog_get_destruido(Prog *p)
{
    if (p->destruido)
    {
        return 1;
    }
    return 0;
}
void prog_destroy(Prog *p)
{
    p->destruido = 1;
    free(p);
}
