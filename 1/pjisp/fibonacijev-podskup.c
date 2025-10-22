/*
Fibonačijev podskup
Autor zadatka: Rade Radišić <radisic.rade@uns.ac.rs>

Dat je niz celobrojnih vrednosti od maksimalno 30 elemenata. Uneti n vrednosti i ispitati da li 
uneti niz predstavlja podskup Fibonačijevog niza na sledeći način:

Proveriti da li je prvi član niza pripada Fibonačijevom nizu

Ako pripada, proveriti da li ostatak niza prati vrednosti u odnosu na formulu Fibonačijevog niza

Prva dva člana Fibonačijevog niza imaju vrednost 1, a svaki sledeći je zbir prethodna dva člana.

Ispisati poruku da li je niz podskup Fibonačijevog niza i same vrednosti niza ukoliko jeste.

Matematička formula Fibonačijevog niza je:

Napomene
Nije dozvoljeno koristiti globalne promenljive

Računati da je uneti niz uvek u rastućem redosledu, tako da nije potrebno dodatno sortirati uneti niz!
*/

#include <stdio.h>
#define MAX 30

int main() {

    int a[MAX];
    int n=0;

    do{
        printf("Unesite velicinu niza: ");
        scanf("%d", &n);
    }while(n<=0);

    int min;

    for(int i=0; i<n; i++) {
        printf("%d. element niza: ", i+1);
        scanf("%d", &a[i]);

        if(i==0) {
            min = a[i];
        }
        else if(a[i]<min) {
            min = a[i];
        }
    }

    int fibonacijev[n];
    int n0= 0;
    int n1 = 1;

    // i treba da bude max niza koji se unosio

    for(int i=0; i<1000; i++) {
        if(n1 >= min) {
            n1 = min;
            i=1000;
        }
        else{
            n1 += n0;
            n0 = n1-n0;
        }
    }

    int podskup = 0;

    for(int i=0; i<n; i++) {
        if (min != 1) {
            if (a[i] == n1) {
                podskup = 1;
                n1 += n0;
                n0 = n1-n0;
            }
            else {
                podskup = 0;
                i = n;
            }
        }
        else if(a[1] == 1){
            if(i==0){
                n0=0;
                n1 = 1;
            }
            if (a[i] == n1) {
                podskup = 1;
                n1 += n0;
                n0 = n1-n0;
            }
            else {
                podskup = 0;
                i = n;
            }
        }
        else if(a[1] == 2){
            if(i==0){
                n0=1;
                n1 = 1;
            }
            if (a[i] == n1) {
                podskup = 1;
                n1 += n0;
                n0 = n1-n0;
            }
            else {
                podskup = 0;
                i = n;
            }
        }
        else {
            podskup = 0;
            break;
        }
    }

    if(podskup == 1) {
        printf("\nPodskup je fibonacijev! \n");
    }
    else {
        printf("\nPodskup nije fibonacijev.\n");
    }

    return 0;
}


