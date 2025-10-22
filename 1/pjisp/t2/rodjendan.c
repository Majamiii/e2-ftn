/*
Iz zadate ulazne datoteke učitatati statički niz struktura, pri čemu se struktura rodjendan_st sastoji od sledećih polja:

Ime (jedna reč, do 15 karaktera),

Dan rođenja (prirodan broj),

Mesec rođenja (prirodan broj),

Broj željenih parcadi torte(prirodan broj).

Napisati funkciju koja nalazi slavljenika (rođen na današnji dan), a zatim slavljeniku čestitati rođendan na standardni izlaz.

Napisati funkciju suma, koja vraća ukupan broj željenih parcadi torte.

Napisati funkciju koja sa standardnog ulaza uzima broj torti (t – prirodan broj) i proverava da li je broj torti dovoljan 
da bi svaki gost dobio željeni broj parčadi torte (jedna torta = 10 parčadi). Na standardni izlaz ispisati da li ima dovoljno 
torti na rođendanu
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_IME 15

typedef struct rodjendan_st{
    char ime[MAX_IME];
    unsigned dan;
    unsigned mesec;
    unsigned broj_parcadi;
}RODJUS;

FILE *safe_fopen(char filename[], char mode[], int kod);
void unos(FILE *in, int *n, RODJUS *rodjendani);
void provera(RODJUS *rodjendani, int n);

int main(int argc, int **argv) {

    if(argc != 1) {
        printf("Pogresno pokretanje programa.\n");
        exit(EXIT_FAILURE);
    }

    int n=0;

    FILE *in = safe_fopen("rodjendan.txt", "r", 2);

    RODJUS rodjendani[100];

    unos(in, &n, rodjendani);
    provera(rodjendani, n);

    fclose(in);

    return 0;
}


FILE *safe_fopen(char filename[], char mode[], int kod){

    FILE *fp = fopen(filename, mode);

    if(fp == NULL) {
        printf("Nedostupan fajl.\n");
        exit(kod);
    }

    return fp;

}


void unos(FILE *in, int *n, RODJUS *rodjendani){
    
    while(
        (fscanf(in, "%s %u %u %u",
        rodjendani[*n].ime, &rodjendani[*n].dan, &rodjendani[*n].mesec, &rodjendani[*n].broj_parcadi
        ))!= EOF
    ){
        (*n)++;
    }

    for(int i=0; i<(*n); i++){
        if(rodjendani[i].dan == 3 && rodjendani[i].mesec == 12){
            printf("Srecan rodjendan %s!\n", rodjendani[i].ime);
        }
    }

}

void provera(RODJUS *rodjendani, int n){

    int br;
    
    printf("\nZa t=");
    scanf("%d", &br);

    int uk_parc=0;

    for(int k=0; k<n; k++){
        uk_parc += rodjendani[k].broj_parcadi;
    }

    if(uk_parc/(br*10) >= 1){
        printf("\nIma dovoljno torte!\n");
    }
    else{
        printf("\nNema dovoljno torte.\n");
    }

}


/*
Primer poziva programa:

./a.out
Primer ispisa slavljenika (ako je rođen 5. 12.)

Srecan rodjendan Nikola!



Primer ispisa slavljenika (ako je rođen 6. 12.)

Srećan rodjendan Ana!



Primer ispisa da li ima dovoljno torti

Za t=2
Nema dovoljno torte!

Za t=4
Ima dovoljno torte!
*/