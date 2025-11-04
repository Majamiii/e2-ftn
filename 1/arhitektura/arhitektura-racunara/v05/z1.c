//   1. Napraviti potprogram int uvecaj(int x) koji na argument dodaje 1 i vraća dobijeni broj.


#include <stdio.h>

unsigned int RUNPP_REG_ERR = 0;

int uvecaj(int x);

int main()
{
    int n, g;
    printf("Unesite N: ");
    scanf("%d",&n);

    g = uvecaj(n);

    printf("\nBroj %d uvecan za 1 je %d\n\n", n, g);

    return 0;
}