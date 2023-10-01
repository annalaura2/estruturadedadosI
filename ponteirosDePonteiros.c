#include <stdio.h>
#include <stdlib.h>

int swapPonteiros(int **p1, int **p2);

int main(void)
{
    int i = 10;
    int x = 25;

    int *p1 = &i;
    int *p2 = &x;

    printf("Valor = %d, Endereço: %p\n", *p1, p1);
    printf("Valor = %d, Endereço: %p\n", *p2, p2);

    printf("\n====== Trocando os valores =====\n");
    swapPonteiros(&p1, &p2);

    printf("Valor = %d, Endereço = %p\n", *p1, p1);
    printf("Valor = %d, Endereço = %p\n\n", *p2, p2);
}

int swapPonteiros(int **p1, int **p2)
{

    int *temp = *p1;

    *p1 = *p2;
    *p2 = temp;
}
