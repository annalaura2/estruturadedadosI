#include <stdio.h>
#include <stdlib.h> // Contém malloc(alocação de memória) e free(liberação de memória)

#define NUM_FLOATS 20
#define STR_LENGTH 10

void *e_malloc(size_t);

int main(void)
{
    int i;

    // Alocações ESTÁTICAS: depois da finalização do programa essas variáveis são desalocadas da memória
    // e a memória passa a poder utilizar aquele determinado espaço para alocar outras variáveis
    int n = 10;
    float f = 5.0f;
    char c[STR_LENGTH] = "123456789";
    int v[25];

    printf("\n");

    printf("n: int => %ld byte(s)\n", sizeof(n));
    //o sizeof é para mostrar os bytes que a variável ocupa na memória, o sizeof retorna 
    //um sizet
    printf("f: float => %ld byte(s)\n", sizeof(f));
    // o percento %ld se refere ao sizet, como o sizeof retorna o sizet 
    // e o sizet é definido como unsigned long que um tipo que retorna tamanhos 
    // por isso o %ld/ l - unsigned long e d porque retorna um inteiro
    printf("c: char => %ld byte(s)\n", sizeof(c));
    printf("v: int[25] => %ld byte(s)\n\n", sizeof(v));

    // Alocações DINÂMICAS:
    int *pi = (int *)e_malloc(1 * sizeof(int));
    float *pf = (float *)e_malloc(NUM_FLOATS * sizeof(float));
    char *s = (char *)e_malloc(STR_LENGTH * sizeof(char));

    *pi = 25;

    for (i = 0; i < NUM_FLOATS; i++)
        pf[i] = i * 2.0f;

    for (i = 0; i < STR_LENGTH; i++)
        s[i] = c[i];

    s[STR_LENGTH] = '\0';

    printf("pi: int * => %ld byte(s)\n", sizeof(pi));
    printf("pf: float * => %ld byte(s)\n", sizeof(pf));
    printf("s: char * => %ld byte(s)\n\n", sizeof(s));

    printf("pi = %d\n\n", *pi);

    for (i = 0; i < NUM_FLOATS; i++)
        printf("pf[%d] = %f\n", i, *(pf + i));

    printf("\n");

    printf("s = %s\n", s);

    // Desalocando a memória previamente alocada
    free(pi);
    pi = NULL;

    free(pf);
    pf = NULL;

    free(s);
    s = NULL;
}

void *e_malloc(size_t bytes)
{
    void *p = malloc(bytes);

    if (p == NULL)
        exit(EXIT_FAILURE);

    return p;
}
