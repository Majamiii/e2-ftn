/*
Snake i Kebab notacija
Autor zadatka: Rade Radišić <radisic.rade@uns.ac.rs>

Napisati program koji konvertuje uneti string veličine od najviše 30 karaktera u jednu od notacija: 
snake_case ili kebab-case. Snake notacija sadrži donju crtu (_) umesto razmaka, dok Kebab notacija 
umesto razmaka ima crticu (-). Korisnik bira u koju od navedenih notacija će biti konvertovan string. 

Normalizovati string tako da sadrži isključivo mala slova. U slučaju da string sadrži neki od znakova 
koji nisu slovo ili broj, izaći iz programa uz poruku greške. Ukoliko je konverzija uspešno sprovedena, 
ispisati rezultujući string, kao i ukupan broj konvertovanih karaktera u stringu.

Napomene

Obratiti pažnju na validaciju karaktera koji će biti korišćen za pretvaranje u određenu notaciju (može biti samo _ ili -)

Testirati program i za slučaj kad korisnik unese više karaktera od veličine ulaznog stringa

Primer rada programa:




Uneti string: Primer konverzije stringa
Izaberite notaciju (moguce vrednosti - i _): -

String nakon konverzije: primer-konverzije-stringa
Broj zamenjenih karaktera: 3



Primer rada programa u slučaju nevalidnog unosa sa tastature:

Uneti string: Primer nevalidnog stringa!?
Izaberite notaciju (moguce vrednosti - i _): _

Greska prilikom konverzije stringa u zadatu notaciju!

*/

#include <stdio.h>
#include <string.h>

#define MAX 31

int main() {

    char str[MAX];

    printf("Uneti string: ");
    __fpurge(stdin);
    gets(str);

    int notacija = 0;
    char znak;
    int brojac = 0;

    do{
        printf("Izaberite notaciju: (- ili _): ");
        scanf("%c", &znak);
    }while(!(znak=='-' || znak =='_'));

    int br = strlen(str);
    char ch;

    for(int i=0; i<br; i++) {
        ch = str[i];
        
        if(ch >= 'A' && ch <= 'Z') {
            ch += 32;
        }
        else if(ch == ' '){
            ch = znak;
            brojac++;
        }
        else if(ch >= 'a' && ch <= 'z') {
            continue;
        }
        else if(ch >= '0' && ch <= '9') {
            continue;
        }
        else{
            printf("\nNeispravan unos!\n");
        }
        str[i] = ch;
    }

    printf("\nBroj zamenjenih karaktera: %d\n", brojac);

    printf("String nakon konverzije: ");
    puts(str);


    return 0;
}

