/*
Zadatak 1
Modifikovati Primer 1 tako da je moguće unositi proizvoljan broj
prirodnih brojeva. Umesto unosa n na početku, postaviti ga na početnu
vrednost 5. Svaki put kad se kapacitet niza popuni, proširiti n množenjem
sa 2 i pomoću funkcije realloc napraviti, novi, veći niz te dimenzije.
Unos podataka se završava kada korisnik unese -1.

#include <stdlib.h>
#include <stdio.h>

int main() {
    int unos = 0;
    while( (unos = scanf("%d", &unos)) != -1){
        printf("\n");
    }

    return 0;
}

*/

#include <stdlib.h>
#include <stdio.h>


int * zauzmi_memoriju(int n);
void realociraj(int n, int *a);


int main() {
    int unos = 0;
    int status = 0; // Povratna vrednost scanf-a
    int n=5;

    int *a;

    while ((status = scanf("%d", &unos)) != EOF) {
        if (status == -1) { // Proveravamo da li je unet validan broj
            break;
        } else {
            
            if(n==5) {
                a=zauzmi_memoriju(n);
            }
            else{
                realociraj(n, a);
                // free(a);
            }

            n*=2;

        }
    }
    free(a);

    return 0;
}


int * zauzmi_memoriju(int n){

    int *a = (int *) malloc((n+1)*sizeof(int));

    if(a == NULL){
        printf("\nNema dovoljno memorije!\n");
        free(a);
    }

    for(int i = 0;i < n;i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
    // Nalazimo maksimum
    int max = a[0];
    for(int i = 1;i < n;i++)
        {
            if(a[i] > max)
                {
                max = a[i];
                }
        }

    return a;

}


void realociraj(int n, int *a){

    a = (int *) realloc(a, (n+1)*sizeof(int));

    if(a == NULL){
        printf("\nNema dovoljno memorije!\n");
        free(a);
    }

    for(int i = 0;i < n;i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
    // Nalazimo maksimum
    int max = a[0];
    for(int i = 1;i < n;i++)
        {
            if(a[i] > max)
                {
                max = a[i];
                }
        }


}