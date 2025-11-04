#include <stdio.h>

int jedinice(long long n);

int main(){

    printf("Upisi broj kom hoces da prebrojis jedinice: ");

    long long n;

    scanf("%lld", &n);

    int x = jedinice(n);

    printf("\nBroj ima %d jedinica\n", x);

    return 0;
}