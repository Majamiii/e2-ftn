/*
Dat je niz od maksimalno 30 vina. Učitati n vina ako su vina opisana sledećim podacima:

naziv (jedna reč, do 30 karaktera)
osnovna_cena (u dinarima, celobrojna vrednost
kolicina (u litrima, realna vrednost)
godiste (celobrojna vrednost)
tip (jedna reč, do 10 karaktera)

Izmeniti naziv tako da se umesto _ koristi prazan prostor, prvo slovo uveća, ostala umanje. Ispisati nazive svih vina 
tipa unetog pomoću argumenta komandne linije. Proceniti cenu vina formulom:

cena = (osnovna + (2024-godiste)) * 100 * kolicina / tip
 
Gde je tip koeficijent određen vrednošću polja tip i ima vrednosti:

crveno - 0.66
roze - 1
belo - 1.33

Ispisati cene vina.

U slučaju uspešnog izvršavanja programa, izaći sa status kodom 0 (EXIT_SUCCESS). Ukoliko program ne može da se izvrši do 
kraja usled sledećih nedostataka, izaći iz programa sa sledećim status kodovima:

U slučaju nedovoljnog ili suvišnog broj argumenata komandne linije, izaći iz programa sa status kodom 1 (EXIT_FAILURE)

Ako nije pronađeno vino tipa unetog argumentom komandne linije, izaći sa status kodom 2

Ako tip nekog od vina nije belo, crveno ili roze, izaći sa status kodom 3

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VINA 20
#define MAX_NAZIV 31
#define MAX_TIP 11

typedef struct vino_st {
    char naziv[MAX_NAZIV];
    int osnovna_cena;
    float kolicina;
    int godiste;
    char tip[MAX_TIP];
}VINO;

void unos_vina(VINO *, int *);
void izmena_naziva(VINO *, int);
void ispis_tipa(VINO *, int, char *);
void cena(VINO *, int);


int main(int argc, char **argv) {

    VINO vina[MAX_VINA];
    int n;

    if (argc != 2) {
        printf("\nPrimer poziva: %s belo\n", argv[0]);
        exit(1);
    }

    unos_vina(vina, &n);
    izmena_naziva(vina, n);
    ispis_tipa(vina, n, argv[1]);
    cena(vina, n);

    return 0;
}

void unos_vina(VINO *v, int *pn) {

    do {
        scanf("%d", pn);
    }while (*pn <= 0 || *pn >= MAX_VINA);

    for (int i=0; i<*pn; i++) {
        scanf("%s %d %f %d %s", v[i].naziv, &v[i].osnovna_cena, &v[i].kolicina, &v[i].godiste, v[i].tip);
    }

}


void izmena_naziva(VINO *v, int n) {
    /*
    Izmeniti naziv tako da se umesto _ koristi prazan prostor, prvo slovo uveća, ostala umanje.
    */

    int d = 0; //duzina reci

    for(int i=0; i<n; i++) {
        d = strlen(v[i].naziv);

        int prvo_slovo = 1;

        for(int j=0; j<d; j++) {

            if(prvo_slovo==1) {
                if(v[i].naziv[j] >= 'a' && v[i].naziv[j] <= 'z') {
                    v[i].naziv[j] -= 32;
                }
                prvo_slovo = 0;
            }
            else if(v[i].naziv[j] >= 'A' && v[i].naziv[j] <= 'Z' && prvo_slovo == 0) {
                v[i].naziv[j] += 32;
                prvo_slovo = 0;
            }
            
            if(v[i].naziv[j] == '_') {
                v[i].naziv[j] = ' ';
                prvo_slovo = 1;
            }

        }

    }
}

void ispis_tipa(VINO *v, int n, char *tip) {
    // printf("%s\n", tip);

    printf("\nVina datog tipa: \n");

    int nadjeno = 0;

    for(int i=0; i<n; i++){
        
        if(strcmp( tip, v[i].tip ) == 0) {
            nadjeno = 1;
            printf("%s\n", v[i].naziv);
        }

    }
    if(nadjeno == 0) {
        printf("Nije pronadjeno vino tipa %s.\n", tip);
        exit(2);
    }
}

void cena(VINO *v, int n) {
    /*
    Proceniti cenu vina formulom:

    cena = (osnovna + (2024-godiste)) * 100 * kolicina / tip
    
    Gde je tip koeficijent određen vrednošću polja tip i ima vrednosti:

    crveno - 0.66
    roze - 1
    belo - 1.33

    Ispisati cene vina.
    */
    float tip = 1;

    printf("\n");


    for(int i=0; i<n; i++) {
        int cena = ( v[i].osnovna_cena + (2024 - v[i].godiste) ) * 100 * v[i].kolicina;


        if( strcmp(v[i].tip, "crveno") == 0 ) {
            tip = 0.66;
            printf("%s %.2f\n", v[i].naziv, (float)cena/tip);
        }
        else if (strcmp(v[i].tip, "belo") == 0) {
            tip = 1.33;
            printf("%s %.2f\n", v[i].naziv, (float)cena/tip);
        }
        else if (strcmp(v[i].tip, "roze") == 0) {
            tip = 1;
            printf("%s %.2f\n", v[i].naziv, (float)cena/tip);
        }
        else {
            printf("Ne postoji vino datog tipa.\n");
            exit(3);
        }

    }

}

/*

Primer poziva programa:

./a.out belo < vina.txt
Primer ulazne datoteke vina.txt:

7
VRANAC 1000 1 2020 crveno
FRESCOBALDI_CICINIS 1500 1 2020 belo
PINOT_NOIR 1200 1.5 2017 crveno
ALEXANDRIA 300 0.75 2021 roze
ZDREBCEVA_KRV 300 1 2024 crveno
REGINA 500 0.7 2022 roze
STARI_GRAD 200 1 2021 belo



Ispis programa na standardnom izlazu:

Vina datog tipa:
Frescobaldi Cicinis
Stari Grad

Vranac 2121.21
Frescobaldi Cicinis 1428.57
Pinot Noir 4318.18
Alexandria 450.00
Zdrebceva Krv 454.55
Regina 490.00
Stari Grad 375.94

*/