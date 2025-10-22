/*

Iz zadate ulazne datoteke timovi.txt učitati statički niz struktura, pri čemu se 
struktura tim_st sastoji od sledećih polja:

država tima (jedna reč, do 20 karaktera)
vrsta spremane hrane (jedna reč, do 20 karaktera)
ocena od publike (realan broj)
ocena od žirija (realan broj)

Pronaći sve timove koji su prošli u sledeći krug i ispisati ih na terminal. Tim prolazi u sledeći krug takmičenja 
ukoliko je ukupna ocena (od publike i žirija) veća od granice potrebne za prolazak. Granica potrebna za prolazak 
u sledeći krug takmičenja se prosleđuje kao poslednji argument komandne linije. Pronaći prosečnu ocenu timova 
koji su prosli u sledeći krug.

Na standardni izlaz (terminal) ispisati i prosečnu ocenu timova koji su prošli u sledeći krug.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAZIV 21

typedef struct tim_st {
    char drzava[MAX_NAZIV];
    char hrana[MAX_NAZIV];
    float ocena_publika;
    float ocena_ziri;
}TIMOVI;

FILE* safe_fopen(char fajl_unos[], char mode[], int kod);
void unos(int *n, FILE *in, TIMOVI timovi[]);
void prolazak(int n, TIMOVI timovi[], float granica, FILE *out);

int main(int argc, char **argv) {

    int n=0;

    if(argc != 4) {
        printf("Pogresno pokretanje programa. Format:   %s input.txt 13.5\n", argv[0]);
        exit(12);
    }

    float granica = atof(argv[3]);
    
    char *fajl_unos = argv[1];
    char *fajl_ispis = argv[2];

    FILE *in = safe_fopen(fajl_unos, "r", 1);
    FILE *out = safe_fopen(fajl_ispis, "w", 2);

    TIMOVI timovi[30];

    unos(&n, in, timovi);
    prolazak(n, timovi, granica, out);

    fclose(in);
    fclose(out);

    return 0;
}



FILE* safe_fopen(char fajl_unos[], char mode[], int kod) {

    FILE *fp = fopen(fajl_unos, mode);

    if(fp == NULL) {
        printf("\nGRESKA U OTVARANJU FAJLA. ON NE POSTOJI.\n");
        exit(kod);
    }

    return fp;
}


void unos(int *n, FILE *in, TIMOVI timovi[]){

    while(
        fscanf(
            in, "%s %s %f %f",
            timovi[*n].drzava, timovi[*n].hrana, &timovi[*n].ocena_publika, &timovi[*n].ocena_ziri
        )!= EOF
    ){ (*n)++; }

    // printf("%s\n", timovi[3].hrana);

}

void prolazak(int n, TIMOVI timovi[], float granica, FILE *out) {

    int i;
    float suma = 0;
    int brojac = 0;

    for(i=0; i<n; i++) {
        if (timovi[i].ocena_publika + timovi[i].ocena_ziri >= granica) {
            fprintf(out,"%s %s %.2f %.2f\n", timovi[i].drzava, timovi[i].hrana, timovi[i].ocena_publika, timovi[i].ocena_ziri);
            suma += timovi[i].ocena_publika + timovi[i].ocena_ziri;
            brojac++;
        }
    }
    fprintf(out, "\nProsecna ocena timova koji su prosli u drugi krug je %.2f.", (float)suma/brojac);


}

/*

Primer poziva:

./program timovi.txt 13.5
sa zadatim ulazom u datoteci timovi.txt:

USA meksicka 7.5 6.5
CANADA tajlandska 6.2 4.3
SPANIJA kineska 9.1 8.6
SLOVENIJA indijska 5.3 6.8
NORVESKA italijanska 8.7 9.5
CESKA libanska 4.7 3.9

i očekivanim izlazom na terminalu:

USA meksicka 7.5 6.5
SPANIJA kineska 9.1 8.6
NORVESKA italijanska 8.7 9.5
Prosecna ocena timova koji su prosli u sledeci krug takmicenja je: 16.63
*/