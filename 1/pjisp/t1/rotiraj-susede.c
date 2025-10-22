/*

Rotiraj susede
Autor zadatka: Aleksandar Vasiljević <alexva02@uns.ac.rs>

Napisati program koji od korisnika očekuje da unese ulazni string i karakter. 
Kreirati novi string koji se dobija tako što se iz unetog stringa izbacuje 
svaka pojava karaktera i vrši se njegovo prebrojavanje. Radi jednostavnosti, 
pretpostaviti da uneti string sadrži isključivo mala ili velika slova. Nakon 
izbacenog karaktera potrebno je izvršiti šifrovanje. Šifrovanje se vrši rotacijom 
susednih karaktera (ukoliko je broj karaktera nakon izbacivanja neparan, poslednji 
karakter ostaviti nepromenjen):

Unesite zeljeni string (max duzine 21): propozicija
Uneti znak koji zelite da izbacite: o
Očekivani izlaz na ekranu je:

Karakter o je iz polaznog stringa izbacen 2 puta.
String nakon modifikacija: rpzpcijia

*/

#include <stdio.h>
#include <string.h>
#define MAX 22

int main() {

    char str1[MAX];
    char znak;

    printf("\nUnesite zeljeni string max duzine 21: ");
    __fpurge(stdin);
    gets(str1);

    printf("\nUneti znak koji zelite da izbacite: ");
    scanf("%c", &znak);

    printf("\nOcekivani izlaz na ekranu je: \n\n");

    int br = 0;
    int n = strlen(str1);

    int t = 0;

    char temp;

    for(int i=0; i<n; i++) {
        if(str1[i] == znak) {
            br++;
            temp=str1[n];
            t=1;

            for(int k=i; k<n-1; k++) {
                str1[n] = str1[i];
                str1[k] = str1[k+1];
            }
            str1[n-1]=temp;
            n--;
            i--;

        }
    }

    if(t==1) {
    
        for(int j=0; j<n; j+=2) {
            temp = str1[j];
            str1[j] = str1[j+1];
            str1[j+1] = temp;
        }
    }

    printf("Karakter %c je iz polaznog stringa izbacen %d puta.\n", znak, br);

    printf("Novi string: ");

    char ch;

    for(int i=0; i<n; i++) {
        ch = str1[i];
        printf("%c", ch);
    }
    if(n%2 != 0) {
        ch = str1[n];
        printf("%c", ch);
    }
    printf("\n");

    return 0;
}



