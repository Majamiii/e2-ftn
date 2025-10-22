/*

String u stringu
Autor zadatka: Aleksandar Vasiljević <alexva02@uns.ac.rs>

Napisati program koji omogućava umetanje podstringa u polazni string na zadatu poziciju.

Na početku programa, od korisnika se zahteva da unese dva stringa, polazni (maksimalne 
dužine 70 karaktera) i umetnuti (maksimalne dužine 20 karaktera). Nakon toga korisnik 
unosi poziciju na koju želi da umetne podstring (voditi računa o tome da pozicija mora 
biti prirodan broj ne veći od dužine polaznog stringa). Ako korisnik unese poziciju koja 
premašuje dužinu polaznog stringa, ispisati poruku o grešci i završiti program. Rezultujući 
string (pomoć: može a ne mora biti u novom stringu) ispisati u obrnutom redosledu.

Primer rada programa:

Unesite polazni string: Ovo je primer stringa.
Unesite podstring koji zelite da umetnete u polazni string: prvog
Na koju poziciju zelite da umetnete uneti podstring (prirodan broj ne veci od 70)? 13

String nakon modifikacije: .agnirts govrp remirp ej ovO
Primer rada programa kada nije moguće umetnuti string:

Unesite polazni string: Ovo je primer stringa.
Unesite podstring koji zelite da umetnete u polazni string: prvog
Na koju poziciju zelite da umetnete uneti podstring (prirodan broj ne veci od 70)? 60

Nije moguce umetnuti string na 60. poziciju u polaznom stringu!

*/

#include <stdio.h>
#include <string.h>

#define MAX_POLAZNI 71
#define MAX_UMETNUTI 21

int main() {

    char polazni[MAX_POLAZNI];
    char umetnuti[MAX_UMETNUTI];

    printf("\nUnesite polazni string: ");
    __fpurge(stdin);
    gets(polazni);
    
    printf("Unesite umetnuti string: ");
    __fpurge(stdin);
    gets(umetnuti);

    int pozicija=0;

    do{
        printf("Na koju poziciju zelite da umetnete uneti podstring (prirodan broj ne veci od 70)? ");
        scanf("%d", &pozicija);
    } while(pozicija<=0 || pozicija>MAX_POLAZNI);

    if(pozicija>=strlen(polazni)) {
        printf("Nije moguce umetnuti string na %d. poziciju u pocetnom stringu!\n", pozicija);
    }

    // printf("\npozicija: %d\n", pozicija);

    char ch;
    int j=0;
    int k=0;

    for(int i=0; i<(strlen(polazni)+strlen(umetnuti)+1); i++) {

        if(i<pozicija) {
            ch = polazni[i];
            printf("%c", ch);
        }
        
        else if(i>=pozicija && i<pozicija+strlen(umetnuti)) {
            ch = umetnuti[j];
            printf("%c", ch);
            j++;
            if(i == pozicija+strlen(umetnuti) -1) {
                k=i-j;
            }
        }

        else {
            ch = polazni[k];
            printf("%c", ch);
            k++;
        }
        
    }

    printf("\n");

    return 0;
}




