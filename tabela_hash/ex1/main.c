#include <stdio.h>
#include <math.h>
#include <string.h>

#define TAM_STRING 200
#define tops unsigned long long int

tops result_hash(char *str, int base, int tam_tab)
{
    tops soma = 0;
    int tam = strlen(str);
    for (int i = 0, pot = tam - 1; i < tam; i++, pot--)
    {
        soma += str[i] * (tops)pow(base, pot);
    }
    return soma % tam_tab;
}

int main()
{
    char string[TAM_STRING];
    int base, qtd, tam_tab;

    scanf("%d %d %d\n", &base, &qtd, &tam_tab);

    for (int i = 0; i < qtd; i++)
    {
        scanf(" %s", string);
        printf("%llu\n", result_hash(string, base, tam_tab));
    }

    return 0;
}