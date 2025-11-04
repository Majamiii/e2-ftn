#include <stdio.h>

int CheckParity(unsigned short int* vrednost);
int CheckParityArray(unsigned short int* niz, int n);

int main(){

    unsigned short int p[] = {32773, 32774, 32775};       // nije dobro, nije dobro, dobro je -> pogresno su postavljeni elementi na 0 i 1 idx
    // ili ako je uk br elemenata onda pp treba da vrati 2

    int n = 3;

    int broj = CheckParityArray(p, n);
    printf("\nBroj pogresno postavljenih elemenata je: %d\n", broj);

    return 0;
}