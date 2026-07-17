#ifndef _PROGRAMA_H_

typedef struct Prog Prog;

Prog *prog_le();
void prog_decrementa_carga(Prog *p);
void prog_set_ultimo_uso(Prog *p, int i);
char *prog_get_nome(Prog *p);
char *prog_get_tipo(Prog *p);
int prog_get_carga(Prog *p);
int prog_get_iteracao(Prog *p);
int prog_get_ultimo_uso(Prog *p);
int prog_get_prioridade(Prog *p);
int prog_get_destruido(Prog *p);
void prog_destroy(Prog *p);

#endif