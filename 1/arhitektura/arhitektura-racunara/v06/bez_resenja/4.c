#include <stdio.h>

int prebaci(long long broj, int pozicija, int vrednost);

int main(){

    long long n = 10;     // 1010

    // npr hocemo treci bit na 1 -> 1110 -> 14
    long long x;
    x = prebaci(n,3,1);

    printf("Prebacen broj je %lld\n", x);

    return 0;
}