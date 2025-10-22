/*
Unosom sa tastature je zadat niz A, neoznačenih celih brojeva od maksimalno 30 elemenata. 
Transformisati niz (bez pomoćnog) tako da se svaki element niza pojavi samo jednom.

Na izlazu štampati broj elemenata zadatog niza, elemente zadatog niza, broj elemenata transformisanog niza i elemente niza.
*/

/*
NAUCENO: 
-
*/

#include <stdio.h>
#define MAX_EL 30

int main(){

    int a[MAX_EL];
    int n=0;

    do{
        printf("Unesite br el niza: ");
        scanf("%d", &n);
    }while(n<1 || n>=MAX_EL);

    for(int i=0; i<n; i++) {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    printf("br el niza: %d\n\n A = [", n);

    for(int i=0; i<n; i++) {
        printf("%d, ", a[i]);
    }
    printf("]\n");

    int temp=0;

    for(int i=0; i<n; i++){
        
        for(int j=i+1; j<n; j++){
            if (a[i] == a[j]) {
                temp = a[n-1];
                a[n-1] = a[j];
                a[j] = temp;

                if(temp != a[n-1]){
                    continue;
                }
                else {
                    j--;
                }

                n = n-1;
            }
        }
    }

    printf("\nBr clanova transformisanog niza: %d\nA2 = [", n);
    
    for(int i=0; i<n; i++) {
        printf("%d, ", a[i]);
    }
    printf("]\n");


    return 0;
}






