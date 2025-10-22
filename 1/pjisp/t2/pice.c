/*

Dat je niz od maksimalno 20 pica. Učitati n pica ako su opisane sledećim podacima:

naziv (jedna reč, do 30 karaktera)
cena (u dinarima, realna vrednost)
precnik (u cm, celobrojna vrednost)
vegetarijanska (jedna reč, do 2 karaktera, "da" ili "ne")
pun_naziv (više reči, određeno opisom u zadatku)

Ispisati prosečnu cenu pice. Ispisati sve nazive pica veće od površine zadate argumentom komandne linije.

 
Pi proceniti na 2 decimale. Formirati string od naziva, veličine pice i reči vegetarijanska ako je pica vegetarijanska. Veličine pice mogu biti:

mala - ako je prečnik manji od 25
srednja - ako je prečnik između 25 i 40
velika - ako je prečnik veći od 40

Formirano ime upisati u polje pun_naziv i ispisati ga. Ispisati koliko ima vegetarijanskih pica.

U slučaju uspešnog izvršavanja programa, izaći sa status kodom 0 (EXIT_SUCCESS).
Ukoliko program ne može da se izvrši do kraja usled sledećih nedostataka, izaći iz programa sa sledećim status kodovima:

U slučaju nedovoljnog ili suvišnog broj argumenata komandne linije, izaći iz programa sa status kodom 1 (EXIT_FAILURE)
Ako nije pronađena pice površine veće od unete argumentom komandne linije, izaći sa status kodom 2

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 31
#define VEGETERIJANSKA 3
#define PUN_NAZIV 31+14+7+2+1
#define M_PI 3.14
#define MAX_PICA 20

typedef struct pica_st{
    char naziv[MAX_NAZIV];
    float cena;
    int precnik;
    char vegeterijanska[VEGETERIJANSKA];
    char pun_naziv[PUN_NAZIV];
}PICA;

FILE *safe_fopen(char filename[], char mode[], int exit_code);
void unos(PICA pice[], int *n, FILE *in);
void prosecna_cena(int n, PICA pice[]);
void ispis_vecih(int n, PICA pice[], float povrsina, FILE *out);
void pun_naziv(int n, PICA pice[]);

int main(int argc, char **argv) {
    
    // U slučaju nedovoljnog ili suvišnog broj argumenata komandne linije, izaći iz programa sa status kodom 1 (EXIT_FAILURE)
    if( argc != 4) {
        printf("Nije dobar broj argumenata komandne linije. EXIT FAILURE.\n");
        exit(1);
    }

    float povrsina = atof(argv[1]);
    // int n = atof(argv[2]);
    char *fajl = argv[2];
    char *fajl_izlaz = argv[3];

    FILE *in = safe_fopen(fajl, "r", 1);
    FILE *out = safe_fopen(fajl_izlaz, "w", 2);

    PICA pice[MAX_PICA];

    int n;
    
    unos(pice, &n, in);
    prosecna_cena(n, pice);
    ispis_vecih(n, pice, povrsina, out);
    pun_naziv(n,pice);

    fclose(in);

    return 0;
}


FILE *safe_fopen(char filename[], char mode[], int exit_code){

    FILE *fp = fopen(filename,mode);

    if(fp == NULL) {
        printf("Pointer value NULL\n");
        exit(exit_code);
    }
    return fp;

}


void unos(PICA pice[], int *pn, FILE *in) {

    // int *k= fscanf("%d", pn);

    do{
        fscanf(in, "%d", pn);
    }while(*pn <= 0 || *pn>MAX_PICA);

    int temp = *pn ;

    for(int i=0; i<temp; i++) {
        fscanf(in,"%s %f %d %s", pice[i].naziv, &(pice[i].cena), &pice[i].precnik, pice[i].vegeterijanska);
    }

}


void prosecna_cena(int broj, PICA pice[]) {
    float sum = 0;

    for(int i=0; i<broj; i++) {
        sum += pice[i].cena;
    }

    printf("Procesna cena pice je %.2f dinara.\n", sum/broj);

}


void ispis_vecih(int n, PICA pice[], float povrsina, FILE *out) {
    int i=0;
    float p_temp;

    int pronadjena = 0;

    fprintf(out,"Pice koje su vece od unete povrsine: ");

    for(i=0; i<n; i++) {

        p_temp = pice[i].precnik * pice[i].precnik * M_PI / 4;

        if (p_temp > povrsina) {
            fprintf(out,"%s ", pice[i].naziv);
            pronadjena = 1;
        }

    }

    if (pronadjena == 0) {
        fprintf(out, "Nije pronadjena pica povrsine vece od unete argumentom komandne linije!");
        exit(2);
    }

    //Ako nije pronađena pice površine veće od unete argumentom komandne linije, izaći sa status kodom 2

    printf("\n\n");

}


void pun_naziv(int n, PICA pice[]){

    /*
    Formirati string od naziva, veličine pice i reči vegetarijanska ako je pica vegetarijanska. Veličine pice mogu biti:

    mala - ako je prečnik manji od 25
    srednja - ako je prečnik između 25 i 40
    velika - ako je prečnik veći od 40

    Formirano ime upisati u polje pun_naziv i ispisati ga.
    */

    char velicina[8];

    int brojac = 0;

    for(int i=0; i<n; i++) {
        
        strcpy( pice[i].pun_naziv, pice[i].naziv );

        if( pice[i].precnik < 25 ) {
            strcat( pice[i].pun_naziv, " mala ");
        }
        else if( pice[i].precnik < 40 ){
            strcat( pice[i].pun_naziv, " srednja " );
        }
        else if(pice[i].precnik >=40) {
            strcat( pice[i].pun_naziv, " velika " );
        }

        if( strcmp(pice[i].vegeterijanska, "da")==0 ) {
            strcat( pice[i].pun_naziv, "vegeterijanska " );
            brojac++;
        }

        printf("%s\n", pice[i].pun_naziv);

    }

    printf("\nIma %d vegeterijanskih pica u ponudi.\n", brojac);

    exit(0);

}


/*
Primer poziva programa:

./a.out 500.00 < pice.txt
Primer ulazne datoteke pice.txt:

6
Kapricoza 739.99 32 ne
Madjarica 800.00 32 ne
Margarita 350.00 24 da
Mediteran 1529.99 50 ne
Tuna 1350.00 52 ne
Vegetarijana 379.99 24 da
Ispis programa na standardnom izlazu:

Prosecna pica kosta: 858.33 dinara.
Pice koje su vece od unete povrsine: Kapricoza Madjarica Mediteran Tuna 

Kapricoza srednja
Madjarica srednja
Margarita mala vegetarijanska
Mediteran velika
Tuna velika
Vegetarijana mala vegetarijanska

Ima 2 vegetarijanskih pica u ponudi.
*/