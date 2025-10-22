/*

Napisati program koji omogućuje izdavanje računa. Radnik unosi ime i prezime kupca (string od 
maksimalno 30 karaktera), kao i broj kupljenih artikala. Nakon toga, za svaki artikal potrebno 
je upisati šifru artikla (string od maksimalno 8 karaktera), kao i njegovu cenu. Ukoliko šifra 
artikla počinje sa karakterom 'P', to označava da je proizvod trenutno na popustu i da njegovu 
cenu treba umanjiti za 10%. Nakon unetih artikala ispisati ukupnu cenu koju kupac treba da plati
 sa obračunatim PDV-om, koji predstavlja dodatnih 20% na ukupnu cenu. Uraditi validaciju unosa 
 za broj artikala, kao i za cenu. Program treba da vrati na ponovni unos korisnika ukoliko je 
 uneo vrednost manju ili jednaku od nule u oba slučaja.

Primer rada programa:

Unesite ime i prezime kupca: Pera Peric
Unesite broj kupljenih artikala: 3
Sifra artikla 1: TR1054
Cena artikla 1: 249.99
Sifra artikla 2: QU4308
Cena artikla 2: 57.99
Sifra artikla 3: PG2058
Cena artikla 3: 163.99
Ostvaren popust na artikal, cena PG2058: 147.59

Ukupno: 455.57
Ukupno (sa PDV-om): 546.69

*/

#include <stdio.h>
#include <string.h>
#define MAX_IME 31
#define MAX_SIFRA 9

int main() {

    char ime[MAX_IME];

    printf("Unesite ime i prezime kupca: ");
    fgets(ime, MAX_IME, stdin);
    ime[strlen(ime) - 1] = '\0';

    int n=0;

    do {
        printf("Unesite br artikala: ");
        scanf("%d", &n);
    }while(n<1);

    char sifra[MAX_SIFRA];
    float cena;

    float suma =0 ;

    for(int i=0; i<n; i++) {
        printf("\nUnesite sifru artikla: \n");
        scanf("%s", sifra);

        printf("Cena artikla: ");
        scanf("%f", &cena);

        if(sifra[0] == 'p' || sifra[0] == 'P') {
            cena *= 0.9;
            printf("Ostvaren popust na artikal %s, nova cena iznosi: %.2f\n", sifra, cena);
        }
        suma += cena;
    }

    printf("\nUkupna cena: %.2f\n", suma);
    printf("Ukupna cena sa porezom: %.2f\n", suma*1.2);


    return 0;
}

