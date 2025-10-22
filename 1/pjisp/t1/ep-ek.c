/*

Dat je niz realnih brojeva od maksimalno 30 elemenata. Učitati n pozitivnih elemenata, koji predstavljaju 
trenutnu visinu u metrima tela u odnosu na tlo. Uneti putem standardnog ulaza masu tela m u kilogramima, 
koja predstavlja realnu vrednost veću od nule. Za unete visine izračunati i ispisati:

Vrednost ukupne energije u sistemu.

Vrednost najmanje razlike između potencijalne i kinetičke energije za određenu visinu h.

Formirati novi niz u kom će se nalaziti brzine tela koje odgovaraju unetim visinama.

Ispise realnih vrednosti zaokružiti na dve decimale.

Za uneti niz visina [1, 3.4, 5, 2, 0] i masu tela 10kg, očekivani ispis na standardnom izlazu je:

Unesite broj visina: 5
Unesite visine [m]:
h[0] = 1
h[1] = 3.4
h[2] = 5
h[3] = 2
h[4] = 0
Unesite masu tela [kg]: 10

Ukupna energija: 490.50J
Najmanja razlika u energijama: 98.10J
[8.86m/s, 5.60m/s, 0.00m/s, 7.67m/s, 9.90m/s]

Ep = mgh,g=9.81m/s2
Ek = mv^2 /2

*/

/*
NAUCENO:
- Euk se moze izracunati preko max visine
*/


#include <stdio.h>
#include <math.h>
#define MAX_EL 30

int main() {

    int n=0;
    float g=9.81;

    do{
        printf("\nUnesite broj visina: ");
        scanf("%d", &n);
    }while(n<=0 || n>=MAX_EL);

    float h[n];

    printf("\nUnesite visine [m]:\n");
    float max_h=0;

    for(int i=0; i<n; i++) {

        printf("h[%d] = ", i);
        scanf("%f", &h[i]);

        if(h[i]>max_h) {
            max_h = h[i];
        }
    }

    float m=0;
    
    do{
        printf("\nUnesite masu tela [kg]: ");
        scanf("%f", &m);
        
    }while(m<=0);

    float euk = 0;
    euk = m*g*max_h;

    printf("\nUkupna energija u sistemu: %.2f J.\n", euk);

    float min_razlika = 10000000;
    float razlika;
    float brzina[n];

    float ep=0;
    float ek = 0;

    printf("\n[");

    for(int i=0; i<n; i++) {

        ep = m*g*h[i];
        ek = euk - ep;

        razlika = abs( ek-ep );

        if(i==0){
            min_razlika = razlika;
        }
        else if (razlika < min_razlika) {
            min_razlika = razlika;
        }

        //ek = mv2/2    =>   v2=2*ek/m

        brzina[i] = sqrt(2*ek / m);

        if(i != n-1) {
            printf("%.2fm/s, ", brzina[i]);
        }
        else {
            printf("%.2fm/s]\n", brzina[i]);
        }

    }
    printf("\nNajmanja razlika u energijama: %.2f J\n\n", min_razlika);

    return 0;
}

