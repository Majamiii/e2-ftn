/*
Dat je niz realnih brojeva od maksimalno 20 elemenata. Učitati n pozitivnih elemenata, gde svaka vrednost u nizu predstavlja otpornost jednog otpornika izraženu u omima. Otpornosti mogu biti isključivo pozitivne, realne vrednosti. Uneti putem standardnog ulaza vrednost struje I, koja predstavlja realnu vrednost. Otpornici su serijski povezani i predstavljaju električno kolo kroz koje protiče struja I. Za serijski vezane otpornosti iz niza izračunati i ispisati:

Ukupnu vrednost napona nad električnim kolom.

Procentualni udeo napona nad najvećim potrošačem u odnosu na ukupan napon u kolu.

Formirati novi niz u odnosu na ulazni, gde su pojedinačni elementi snage otpornika.

Ispise vrednosti zaokružiti na dve decimale.

Za ulazni niz otpornosti [1, 20, 15, 10, 6, 2.5] i vrednost struje od 0.5 ampera, očekivani ispis na standardnom izlazu je:

Unesite broj clanova niza: 6
R[0] = 1
R[1] = 20
R[2] = 15
R[3] = 10
R[4] = 6
R[5] = 2.5
Unesite jacinu struje u amperima: 0.5

Ukupan napon: 27.25V
Procentualni udeo napona: 36.70%
[0.25W, 5.00W, 3.75W, 2.50W, 1.50W, 0.62W]

Korisne matematičke formule

Ukupna otpornost serijski vezanih otpornika: Ruk = R1 + R2 + ... + Rn

Omov zakon:     U=R I

Džulov zakon:   P=R I2
*/

/*
Nauceno odavde:
-  V[i] = pow(a[i], 3);
-   %5lf znaci da ce biti 5 razmaka odvojeno od prethodno napisanog
-   %5.1lf issto kao gore samo integrisano zaokruzivanje na 1 decimalu
*/



#include <stdio.h>
#define MAX_EL 20

int main() {

    int n=0;
    float r_max = 0;

    do{
        printf("\nUnesite broj clanova niza: ");
        scanf("%d", &n);
    }while(n<=0 || n>=MAX_EL);

    float r[n];

    printf("\nUnesite otpore [m]:\n");

    for(int i=0; i<n; i++) {

        printf("R[%d] = ", i);
        scanf("%f", &r[i]);

        if(i==0) r_max = r[i];

        else if(r[i]>r_max) {
            r_max = r[i];
        }
    }

    float struja;
    do{
        printf("\nUnesite jacinu struje u amperima: ");
        scanf("%f", &struja);
    }while(struja<=0 );

    float uk_napon = 0;

    for(int i=0; i<n; i++) {
        uk_napon += struja*r[i];
    }
    printf("\n\nUkupan napon: %.2f V\n", uk_napon);
    printf("Procentualni udeo napona: %.2f%%\n[", r_max*struja*100/uk_napon);

    for(int i=0; i<n; i++) {
        if(i != n-1) {
            printf("%.2fW, ", struja*struja*r[i]);
        }
        else {
            printf("%.2fW]\n\n", struja*struja*r[i]);
        }
            
    }

    /*
    
Ukupan napon: 27.25V
Procentualni udeo napona: 36.70%
[0.25W, 5.00W, 3.75W, 2.50W, 1.50W, 0.62W]

Korisne matematičke formule

Ukupna otpornost serijski vezanih otpornika: Ruk = R1 + R2 + ... + Rn

Omov zakon:     U=R I

Džulov zakon:   P=R I2
*/


    return 0;
}