#include <stdio.h>

unsigned int RUNPP_REG_ERR = 0;

int fibonaci(int n, unsigned int* rez);

int main()
{
    int n, g;
    unsigned int f;
    printf("Unesite N: ");
    scanf("%d",&n);
    // n = 7;
    // 1 1 2 3 5 8   13 21
    // treba da se vrati 8 ako je n=6
    g = fibonaci(n, &f);
    if (g)
        printf("Greska!\n");
    else
        printf("Fibonaci(%d)=%u\n", n, f);

    if (RUNPP_REG_ERR) return RUNPP_REG_ERR+128;
    else return g;
}

// 1 1 2 5 4 10 8 16 40

