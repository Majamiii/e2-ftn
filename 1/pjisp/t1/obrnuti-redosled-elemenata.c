/*Dat je celobrojni niz od maksimalno 30 elemenata. Obrnuti redosled elemenata u nizu (bez upotrebe pomoćnog niza) i zatim odštampati rezultat.

Za sledeće ulazne podatke [3, 7, 4, 1, 5] rešenje je [5, 1, 4, 7, 3].*/


#include <stdio.h>
#define MAX_EL 30

int main(){

    int a[MAX_EL];
    int n=0;

    do {
        printf("Unesite broj elemenata niza: ");
        scanf("%d", &n);
    } while(n<=1 || n > MAX_EL);

    for(int i=0; i<n; i++) {
        printf("Clan na indeksu %d: ", i);
        scanf("%d", &a[i]);
    }

    printf("[");

    for (int i=0; i<n; i++) {
        if(i != n-1) {
            printf("%d, ", a[n-i-1]);
        }
        else {
            printf("%d]\n", a[n-i-1]);
        }
    }


    return 0;
}




