/*
U jednostruko spregnutoj listi nalaze se ocene koje je student dobio
tokom godine. Izračunati prosek i rezultat ispisati na standardnom izlazu
(ekranu).
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct cvor_st{
    int vrednost;
    struct cvor_st *sledeci;
}CVOR;

void inicijalizacija(CVOR **glava);
CVOR * napravi_cvor(int vrednost);
void dodaj_na_kraj(CVOR **glava, CVOR *novi);
float prosek_studenta(CVOR *pglava);
void obrisi_listu(CVOR **pglava);

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


void inicijalizacija(CVOR **glava){
    *glava = NULL;
}


CVOR * napravi_cvor(int vrednost){
    
    CVOR *novi = (CVOR *) malloc(sizeof(int));

    if(novi == NULL){
        printf("\nnema dovoljno mesta za novi cvor.\n");
    }

    novi->vrednost = vrednost;
    novi->sledeci = NULL;
    
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

float prosek_studenta(CVOR *pglava){


    if(pglava == NULL){
        printf("ne postoje elementi u listi.\n");
        return 0;
    }

    float suma = 0;
    float brojac = 0;

    CVOR *temp = pglava;

    while(temp ->sledeci != NULL){
        suma += temp->vrednost;
        brojac++;
        temp = temp->sledeci;
    }

    return suma/brojac;
}



void obrisi_listu(CVOR **pglava){

    CVOR *tekuci = *pglava;

    while(tekuci != NULL){
        CVOR *temp = tekuci->sledeci;
        tekuci = tekuci->sledeci;
        temp = NULL;
        free(temp);
    }

}


