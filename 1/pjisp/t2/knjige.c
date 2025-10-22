/*
Knjige
Autor zadatka: Sanja Špica <sanjaspica@uns.ac.rs>

Iz zadate ulazne datoteke učitati statički niz struktura, pri čemu se struktura knjiga_st sastoji od sledećih polja:

naziv knjige (jedna reč, do 20 karaktera)
izdavač (jedna reč, do 20 karaktera)
broj strana knjige (pozitivan ceo broj)

Na osnovu broja strana koje osoba može da pročita za sat vremena br_strana (pozitivan realan broj) formirati 
novi statički niz struktura i upisati ga u zadatu izlaznu datoteku, pri čemu se struktura duzina_citanja_st sastoji od sledećih polja:

broj dana koji je potreban da se knjiga pročita ako osoba čita 24 sata dnevno (realan broj, zaokružen na 2 decimale, koristiti "%.2f" format specifikator)
naziv knjige (koristiti funkciju strcpy prilikom kopiranja iz strukture knjiga_st)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_KNJIGA 21
#define MAX_IZDAVAC 21
#define MAX_NIZ 30

typedef struct knjiga_st {
    char naziv_knjige[MAX_KNJIGA];
    char izdavac[MAX_IZDAVAC];
    int strane;
}KNJIGE;

typedef struct citanje_st {
    float br_dana;
    char naziv[MAX_KNJIGA];
}CITANJE;

FILE *safe_fopen(char filename[], char mode[], int error_code);
void ucitaj(KNJIGE knjiga[], FILE *in, int *n);
void kopiraj(KNJIGE knjiga[], CITANJE duzina_citanja[], int n, float br_str);
void upisi(FILE *out, CITANJE duzina_citanja[], int n);


//pr ulaza: ./knjige 11.5 knjige.txt duzina_citanja.txt
// 11.5 je br strana na sat vremena, knjige su ulazni a duzina citanja izlazni fajl

int main(int argc, char **argv) {

    if(argc != 4) {
        printf("Ukucaj ovako:   %s  ULAZNI_FAJL.TXT  IZLAZNI_FAJL.TXT\n", argv[0]);
        exit(42);
    }
    
    float br_str = atof( argv[1] );
    char *ulazni_fajl = argv[2];
    char *izlazni_fajl = argv[3];

    FILE *in = safe_fopen(ulazni_fajl, "r", 1);
    FILE *out = safe_fopen(izlazni_fajl, "w", 2);

    KNJIGE knjiga[MAX_NIZ];
    CITANJE duzina_citanja[MAX_NIZ];

    int n;

    ucitaj(knjiga, in, &n);
    kopiraj(knjiga, duzina_citanja, n, br_str);
    upisi(out, duzina_citanja, n);

    fclose(in);
    fclose(out);

    return 0;
}

FILE *safe_fopen(char filename[], char mode[], int kod) {
    FILE *fp = fopen(filename, mode);

    if(fp == NULL) {
        printf("Cannot open '%s'!", filename);
        exit(kod);
    }
    return fp;
}

void ucitaj(KNJIGE knjiga[], FILE *in, int *n) {

    /*
    Iz zadate ulazne datoteke učitati statički niz struktura, pri čemu se struktura knjiga_st sastoji od sledećih polja:

    naziv knjige (jedna reč, do 20 karaktera)
    izdavač (jedna reč, do 20 karaktera)
    broj strana knjige (pozitivan ceo broj)
    */

    *n = 0;

    while( fscanf(
        in,
        "%s %s %d",
        knjiga[*n].naziv_knjige, knjiga[*n].izdavac, &knjiga[*n].strane
        )
        != EOF) 
    {
        (*n)++;
    }

}

void kopiraj(KNJIGE knjiga[], CITANJE duzina_citanja[], int n, float br_str) {
    //naziv knjige (koristiti funkciju strcpy prilikom kopiranja iz strukture knjiga_st)

    // char knjiga[MAX_KNJIGA];

    int i=0;

    for(i=0; i<n; i++){
        strcpy( duzina_citanja[i].naziv, knjiga[i].naziv_knjige);

        duzina_citanja[i].br_dana = (knjiga[i].strane / br_str / 24);
    }

    //duzina citanja = br strana / brzina / 24

}

void upisi(FILE *out, CITANJE duzina_citanja[], int n) {
    
    for(int i=0; i<n; i++) {

        fprintf(out,
            "%.2f %s\n",
            duzina_citanja[i].br_dana, duzina_citanja[i].naziv
        );

    }

}



/*
Primer poziva:

./knjige 11.5 knjige.txt duzina_citanja.txt
sa br_strana=11.5 i zadatim ulazom u datoteci knjige.txt:

Hiljadu_brodova Delfi 231
Gorila Laguna 223
U_prolece Vulkan 281
Petlja Laguna 165
Povratak Delfi 314
Deca_zla Vulkan 141
i očekivanim izlazom u datoteci duzina_citanja.txt:

0.84 Hiljadu_brodova
0.81 Gorila
1.02 U_prolece
0.60 Petlja
1.14 Povratak
0.51 Deca_zla
*/