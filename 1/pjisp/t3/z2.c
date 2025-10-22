/*

Zadatak 2
Napisati jednostruko spregnutu listu, koja sadrži stringove maksimalne
dužine 30 karaktera. Popuniti listu sa određenim stringovima (može biti
zadato unapred, bez potrebe za unosom), zatim putem tastature uneti
karakter. Izračunati srednju vrednost udela zadatog karaktera na nivou
cele liste. Ispisati rezultat zaokružen na dve decimale.
Primer:
Zadato slovo a i reči u listi:
Pera -> 0.25
Mika -> 0.25
Laza -> 0.5
Srednja vrednost udela: 0.33 (zaokruženo na dve decimale)


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cvor_st {
    char *el;
    struct cvor_st *tekuci;
}CVOR;

void inicijalizacija(CVOR **pglava);

CVOR * napravi_cvor(char ime[]);
void dodaj_na_kraj(CVOR **glava, CVOR *novi);
void obrisi_listu(CVOR **pglava);
void naci_udeo(CVOR *glava, char k);

int main(){

    char k;

    printf("Uneti karakter ciji se udeo trazi:");
    scanf("%c", &k);

    CVOR *glava;
    inicijalizacija(&glava);

    // CVOR *novi = napravi_cvor("Pera");

    dodaj_na_kraj(&glava, napravi_cvor("Pera"));
    dodaj_na_kraj(&glava, napravi_cvor("Mika"));
    dodaj_na_kraj(&glava, napravi_cvor("Laza"));

    naci_udeo(glava, k);

    obrisi_listu(&glava);

    return 0;
}



void inicijalizacija(CVOR **pglava){

    *pglava = NULL;

}


CVOR * napravi_cvor(char ime[]){

    CVOR *novi = malloc(sizeof(char)*strlen(ime));
    
    if(novi == NULL){
        printf("NEMA DOVOLJNO MESTA\n");
    }

    novi->el = ime;
    novi->tekuci = NULL;

    return novi;

}


void dodaj_na_kraj(CVOR **pglava, CVOR *novi){

    if(*pglava == NULL){
        *pglava = novi;
    }

    else {
        CVOR *tekuci = *pglava;
        while(tekuci->tekuci != NULL){
            tekuci = tekuci->tekuci;
        }
        tekuci->tekuci = novi;
    }

}


void obrisi_listu(CVOR **pglava){

    CVOR *temp = *pglava;

    while(temp != NULL){
        CVOR *sledeci = temp->tekuci;
        
        temp = temp->tekuci;

        sledeci = NULL;
        free(sledeci);
    }

}


void naci_udeo(CVOR *glava, char k){
    CVOR *trenutno = glava;

    int cntr_ima = 0;
    int cntr_uk = 0;

    while(trenutno != NULL){
        CVOR *sledeci = trenutno->tekuci;
        int n = strlen(trenutno->el);
        for(int i=0; i<n; i++){

            if(trenutno->el[i] == k){
                cntr_ima ++;
            }

            cntr_uk++;
        }
        trenutno = sledeci;
    }

    if(cntr_uk > 0){
        printf("\nudeo koji ima slovo %c je %.2f%% i ono se pojavljuje %d puta.\n", k, (float)cntr_ima/cntr_uk*100, cntr_ima);
    }
    else{
        printf("\nuopste nema unesenih reci.\n");
    }

}