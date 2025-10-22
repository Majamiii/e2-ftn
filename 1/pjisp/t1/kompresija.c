/*

Kompresija stringa
Autor zadatka: Rade Radišić <radisic.rade@uns.ac.rs>

Napisati program koji vrši kompresiju unetog stringa od najviše 99 karaktera. Kompresija se vrši na sledeći način:

U unetom stringu se prate ponavljanja određenog karaktera jedan za drugim iste veličine

Umesto ponovljenih karaktera, ispisati broj ponavljanja karaktera i sam karakter

U slučaju da nema ponavljanja, ne piše se broj ispred karaktera

Na osnovu navedenih pravila kompresije, formirati novi, rezultujući string, koji je neophodno ispisati. 
Osim kompresovanog stringa, ispisati i procenat kompresije algoritma koji se računa po sledećoj formuli:

ž
ž
 
Napomene
S obzirom na to da je ukupni broj karaktera dvocifren broj, broj ponavljanja takođe može biti najviše dvocifren

Za ispisivanje procenat karaktera u naredbi printf, navesti %% u format stringu

Primer rada programa:

Unesite string: Primeeeeer nekommmprrrressovanoggg striiiiinga
String nakon kompresije: Prim5er neko3mp4re2sovano3g str5inga
Procenat kompresije: 21.74%
Primer rada programa u slučaju unetog istog slova:

Unesite string: aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
String nakon kompresije: 42a
Procenat kompresije: 92.86%

Primer rada programa u slučaju stringa sa karakterima koji se ne ponavljaju:

Unesite string: Primer stringa bez kompresije
String nakon kompresije: Primer stringa bez kompresije
Procenat kompresije: 0.00%

*/

#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {

    char nekompresovani[MAX];
    char kompresovani[MAX];

    printf("Unesite string: ");
    __fpurge(stdin);
    gets(nekompresovani);

    int br=strlen(nekompresovani);

    if (nekompresovani[br - 1] == '\n') { // Ukloni novi red na kraju, ako postoji
        nekompresovani[br - 1] = '\0';
        br--;
    }

    char ch;
    int k=0;

    int count=0;

    for(int i=0; i<br; i++) {
        if(nekompresovani[i] == nekompresovani[i+1]){
            if(nekompresovani[i+1] != ch) { 
                ch = nekompresovani[i];
                for(int j=i; j<br-i; j++) {
                    if(nekompresovani[j] == nekompresovani[j+1]) {
                        count++;
                    }
                    else {
                        j=br;
                        count++;
                    }
                }
                if(count<10) {
                    kompresovani[k] = count + '0';
                    k += 1;
                }
                else {
                    kompresovani[k] = count/10 + '0';
                    kompresovani[k+1] = count % 10 + '0';
                    k += 2;
                }
                kompresovani[k] = ch;
                k += 1;
                // i = i+count-2;
                count=0;
            }
        }
        else {
            kompresovani[k] = nekompresovani[i];
            k += 1;
        }
    }

    printf("\nKompresovani string: ");
    // char s;

    // for(int i=0; i<k; i++) {
    //     s = kompresovani[i];
    //     printf("%c", s);
    // }

    printf("%s", kompresovani);

    printf("\n");


    return 0;
}






