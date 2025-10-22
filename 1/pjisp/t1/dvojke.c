/*

Dvojke
Autor zadatka: Relja Mihić <relja.mihic@uns.ac.rs>

Dat je niz celobrojnih vrednosti od maksimalno 32 elementa. Uneti n vrednosti i ispisati:

Sve elemente sa parnim indeksima

Sve elemente sa parnim vrednostima

Sve elemente čiji indeks je stepen dvojke

Sve elemente čija apsolutna vrednost je stepen dvojke

Za stepene dvojke uzeti brojeve:

Primer rada programa:

Unesite velicinu niza: 5
1. element niza je: 1
2. element niza je: 4
3. element niza je: 5
4. element niza je: -8
5. element niza je: 10
Elementi sa parnim brojem indeksa su: 1 5 10 
Elementi cija apsolutna vrednost je paran broj su: 4 -8 10 
Elementi ciji indeksi su stepen dvojke: 4 5 10 
Elementi cija apsolutna vrednost je stepen dvojke: 1 4 -8


*/

#include <stdio.h>
#include <math.h>

#define MAX 32

int main() {

    int niz[MAX];
    int n=0;

    do{
        printf("Unesite velicinu niza: ");
        scanf("%d", &n);
    }while(n<=0);

    int maks;

    for(int i=0; i<n; i++) {
        printf("%d. element niza: ", i+1);
        scanf("%d", &niz[i]);
    }

    /*
Elementi sa parnim brojem indeksa su: 1 5 10 
Elementi cija apsolutna vrednost je paran broj su: 4 -8 10 
Elementi ciji indeksi su stepen dvojke: 4 5 10 
Elementi cija apsolutna vrednost je stepen dvojke: 1 4 -8
*/
    printf("\nElementi sa parnim brojem indeksa su: ");

    for(int i=0; i<n; i++) {
        if(i%2 == 0) {
            printf("%d ", niz[i]);
        }
    }

    printf("\nElementi cija apsolutna vrednost je paran broj su: ");

    for(int i=0; i<n; i++) {
        if(abs(niz[i])%2 == 0) {
            printf("%d ", niz[i]);
        }
    }

    printf("\nElementi ciji indeksi su stepen dvojke: ");

    for(int i=0; i<n; i++) {
        for(int k=1; k<=i; k=k*2) {
            if(i == k) {
                printf("%d ", niz[i]);
            }
        }
    }

    printf("\nElementi cija apsolutna vrednost je stepen dvojke: ");

    for(int i=0; i<n; i++) {
        for(int k=1; k<=abs(niz[i]); k = k*2) {
            // printf("k: %d  ", k);
            if(abs(niz[i]) == k) {
                printf("%d ", niz[i]);
            }
        }
    }
    printf("\n");

    return 0;
}

