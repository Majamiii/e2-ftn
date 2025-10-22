/*

Dat je niz karaktera B od maksimalno 130 karaktera u koji treba učitati sledeci citat (Fridrih Niče):

"Ko Se Bori Sa Cudovistima, Mora Paziti Da Sam Ne Postane Cudoviste. A Kad Dugo Gledas U Ponor, Ponor Pocne Da Gleda U Tebe."
Prebrojati karaktere datog citata.

Napisati program koji modifikuje dati citat tako što velika slova pretvara u mala i obrnuto.



Broj karaktera datog citata je 123.

kO sE bORI sA cUDOVISTIMA, mORA pAZITI dA sAM nE pOSTANE cUDOVISTE. a kAD dUGO gLEDAS u pONOR, pONOR pOCNE dA gLEDA u tEBE.

*/

/*
NAUCENO: 
    __fpurge(stdin);
    gets(str);

    max karaktera = n+1
*/

#include <stdio.h>
#include <string.h>
#define MAX_KARAKTERA 131

int main() {
/*
    char str[MAX_KARAKTERA];

    printf("Napisite string: ");
    __fpurge(stdin);
    gets(str);

    int br=strlen(str);
    printf("\nBroj karaktera niza je %d.\n", br);

    for(int i=0; i<br; i++) {
        if(str[i]>="A" && str[i]<="Z") {
            str[i] += 32;
        }
        else if(str[i]>="a" && str[i]<="z") {
            str[i] -= 32;
        }
        printf("s", str[i]);
    }
*/
    
    char B[MAX_KARAKTERA];

    printf("Unesite string: ");
    __fpurge(stdin);
    gets(B);

    int br=strlen(B);   
    printf("Broj karaktera datog citata je %d\n", br);

    int i=0;
    while(B[i] != '\0') {
        if (B[i] >= 'A' && B[i] <= 'Z'){ 
            B[i] += 32;
        }
        else if (B[i] >= 'a' && B[i] <= 'z'){
            B[i] -= 32;
        }
        i++;
    }
    puts(B);

    return 0;
}









