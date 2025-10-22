/*
Prosek učenika
Autor zadatka: Rade Radišić <radisic.rade@uns.ac.rs>

Razredni starešina unosi ocene učenika na kraju godine u đačku knjižicu. 
Napisati program koji pomaže pri računanju proseka i deskriptivne ocene učenika.

Podaci sa tastature se unose u string maksimalne veličine 30 karaktera. 
Ocene se unose kao jedan string, gde su zarezom i proizvoljnim brojem razmaka 
razdvojene pojedinačne ocene, koje mogu imati vrednost između 1 i 5. Ocene se iz 
stringa prebacuju u niz celobrojnih vrednosti maksimalne veličine 10 elemenata. 
Ukoliko se u stringu pojavi karakter koji nije cifra od 1 do 5, zarez ili razmak, 
kao i ukoliko je broj ocena veći od zadate veličine celobrojnog niza, ispisati poruku
o grešci i zaustaviti dalju obradu stringa. Radi jednostavnosti, računati da je 
string uvek formata jedan karakter (na primer, ocena), pa proizvoljni broj zareza 
i razmaka, pa drugi karakter, pa opet proizvoljni broj zareza i razmaka itd.

U slučaju uspešne obrade unetog stringa, od dobijenog niza celobrojnih brojeva 
izračunati srednju vrednost, na osnovu koje se formira deskriptivna ocena 
(odrediti minimalnu dimenziju stringa u koji mogu da stanu sve navedene vrednosti):

Od 4.50, uključujući i 4.50, do 5.00, učenik je odlican

Od 3.50, uključujući i 3.50, do 4.50, učenik je vrlo dobar

Od 2.50, uključujući i 2.50, do 3.50, učenik je dobar

Od 1.50, uključujući i 1.50, do 2.50, učenik je dovoljan

Za sve pozitivne vrednosti manje od 1.50, učenik je nedovoljan

Program treba da ispisuje celobrojni niz ocena, prosek učenika i deskriptivnu ocenu.

Primer rada programa:

Upisati ocene ucenika: 5,3,4,3,5,2,5
Ocene ucenika: 5, 3, 4, 3, 5, 2, 5
Prosek ucenika: 3.86 vrlo dobar
Primer rada programa u slučaju nevalidnog unosa sa tastature:

Upisati ocene ucenika: 5,3,a,a,6,1
Karakter 'a' u unosu nije validan!
Primer rada programa u slučaju unosa više od dozvoljenog broja ocena:

Upisati ocene ucenika: 5,3,5,2,4,4,4,3,2,1,3,5,5
Moguce je uneti maksimalno 10 ocena!
Primer rada programa u slučaju unosa samo zareza i razmaka:

Upisati ocene ucenika: ,,, ,,   , 
Ocene ucenika: 
Prosek ucenika: 0.00 nedovoljan
*/


#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#define MAX_KARAKTERA 30

int main() {

    char str[MAX_KARAKTERA];

    printf("Upisati ocene ucenika: ");
    fgets(str, MAX_KARAKTERA, stdin);

    int len = strlen(str);
    if(str[len-1] < '\n') {
        str[len-1] = '\0';
        len--;
    }

    int ocene[15];
    int j=0, sum=0;
    int x;
    int counter = 0;
    char ch;
    char xch;

    for(int i=0; i<len-1; i++) {
        if(str[i]==' ' || str[i]==',') {
            continue;
        }
        else {
            x = str[i] - '0';
            // printf("x: %d\n", x);

            if(x>0 && x<=5) {
                ocene[j] = x;
                counter++;
                sum += x;
                if(counter>10) {
                    printf("\nNemoguce upisati preko 10 ocena!\n");
                    break;
                }
            }
            else {
                ch = ocene[j];
                printf("\nKarakter %c nije validan!\n", ch);
            }

        }
    }

    printf("\nProsek ocena je: %.2f\n", (float)sum/counter);

    return 0;
}


