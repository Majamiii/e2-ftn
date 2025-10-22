/*
U jednostruko spregnutoj listi nalaze se ocene koje je student dobio
tokom godine. Izračunati prosek i rezultat ispisati na standardnom izlazu
(ekranu).
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct struct_st {
    int el;
    struct struct_st *sledeci;
}CVOR;

void inicijalizacija(CVOR **glava);
CVOR * napravi_cvor(int vrednost);
void dodaj_na_kraj(CVOR **pglava, CVOR *novi);
void obrisi_listu(CVOR **pglava);
float prosek_studenta(CVOR *pglava);

int main(){


    char broj_indeksa[] = "ee300-2020";
    char ime_studenta[] = "Jovan Jovanovic";

    CVOR *glava;

    inicijalizacija(&glava);

    dodaj_na_kraj(&glava, napravi_cvor(8));
    dodaj_na_kraj(&glava, napravi_cvor(7));
    dodaj_na_kraj(&glava, napravi_cvor(9));
    dodaj_na_kraj(&glava, napravi_cvor(10));
    dodaj_na_kraj(&glava, napravi_cvor(6));
    dodaj_na_kraj(&glava, napravi_cvor(8));
    dodaj_na_kraj(&glava, napravi_cvor(9));
    dodaj_na_kraj(&glava, napravi_cvor(8));

    printf("Student %s, sa brojem indeksa %s, ima prosek %.2lf\n",
    ime_studenta, broj_indeksa, prosek_studenta(glava));
    obrisi_listu(&glava);

    return 0;

}



void inicijalizacija(CVOR **pglava){

    *pglava = NULL;

}


CVOR * napravi_cvor(int vrednost){
    CVOR *novi = (CVOR *) malloc(sizeof(CVOR));

    if(novi == NULL){
        printf("nema mesta\n");
    }

    novi -> el = vrednost;
    novi -> sledeci = NULL;

    return novi;

}



void dodaj_na_kraj(CVOR **pglava, CVOR *novi){

    if(*pglava == NULL){
        *pglava = novi;
    }

    else{
        CVOR *tekuci = *pglava;
        while(tekuci->sledeci != NULL){
            tekuci = tekuci->sledeci;
        }
        tekuci->sledeci = novi;
    }

}


void obrisi_listu(CVOR **pglava){

    CVOR *temp;

    while(*pglava != NULL){
        temp = *pglava;
        *pglava = (*pglava)->sledeci;
        temp->sledeci == NULL;
        free(temp);
    }

}


float prosek_studenta(CVOR *pglava){

    if (pglava == NULL) {
        printf("Lista je prazna!\n");
        return 0;
    }

    CVOR *temp = pglava;
    int suma = 0;
    int brojac=0;

    while(temp->sledeci != NULL){
        suma += temp->el;
        brojac++;

        temp = temp->sledeci;
    }
    return( (float)suma / brojac  );

}