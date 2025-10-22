/*

Dat je niz karaktera B od maksimalno 120 karaktera u koji treba učitati sledeći citat Branislava Nušića:

"Otadzbina nije predmet ogranicen, oivicen, utelovljen. Otadzbina je misao, otadzbina je vera, a misao i vera ne umiru."
Prebrojati karaktere datog citata.

Prebrojati koliko puta se određen karakter pojavljuje u datom citatu.

*/

#include <stdio.h>
#include <string.h>

#define MAX_KARAKTERA 121


int main() {

    char s[MAX_KARAKTERA], m;

    printf("\nUnesite citat: ");
    fgets(s, MAX_KARAKTERA, stdin);

    printf("\nUnesite karakter: ");
    scanf("%c", &m);

    int br=0;
    int d=0;

    for(int i=0; i<strlen(s); i++) {
        if(s[i] != '\0') {
            d++;
        }
        else {
            i=strlen(s);
        }
    }

    for(int i=0; i<strlen(s); i++) {
        if(s[i] == m) {
            br++;
        }
    }

    printf("\nBroj pojavljivanja karaktera %c u datom citatu je %d.\n", m, br);

    int b=strlen(s);

    printf("\nBroj karaktera u datom citatu je %d.\n", b);

    return 0;
}




