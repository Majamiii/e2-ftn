/*
Svuda dođi
Autor zadatka: Aleksandar Vasiljević <alexva02@uns.ac.rs>

Napisati program koji na osnovu ulaznog stringa A formirati izlazni string B 
sačinjen od prve i poslednje reči ulaznog stringa A. Prilikom unosa ulaznog 
stringa A voditi računa o maksimalnoj dozvoljenoj dužini koja iznosi 22 karaktera. 
Izlazni string B treba da se sastoji isključivo od velikih slova (konverziju 
raditi samo nad slovima):

Unesite zeljeni string (max duzine 22): Svuda podji, kuci dodji
Očekivani izlaz na ekranu je:

SVUDA DODJI
Očekivani izlaz na ekranu ukoliko se za vrednost string A unetog preko standardnog ulaza „Svuda“ je sledeći:

SVUDA SVUDA

*/


#include <stdio.h>
#include <string.h>

#define MAX_STRING 23

int main() {

    char str[MAX_STRING];

    printf("Unesite string: ");
    __fpurge(stdin);
    gets(str);

    int br = strlen(str);
    char one[br];

    int j=0;

    for(int i=0; i<br+1; i++) {
        if (str[i] == ' ' || str[i] == '\0'){
            one[j] = ' ';
            j++;
            i = br;
        }
        else {
            one[j] = str[i];
            j++;
        }
        char ch = one[j-1];

        printf("%c  , j:%d\n", ch, j);
    }

    int count=0;
    
    for(int i=br-1; i>=0; i--) {
        if(!(str[i] == ' ')){
            count++;
        }
        else {
            break;
        }
    }

    // printf("\ncount: %d\n", count);

    char two[count+1];

    
    for(int i=0; i<count; i++) {
        if (str[i] == ' ' || str[i] == '\0'){
            i = count;
        }
        else {
            two[count-i-1] = str[br-i-1];
            // j++;
        }
        char ch = two[count-i-1];

        printf("%c\n", ch);
    }

    printf("\n");
    j=0;
    char ch;

    for(int i=0; i<strlen(one)+strlen(two); i++) {
        if(i<strlen(one)) {
            ch=one[i];
        }
        else {
            ch=two[j];
            j++;
        }

        if(ch >= 'a' || ch<='z') {
            ch -= 32;
        }
        else {
            continue;
        }
        
        printf("%c", ch);
    }

    printf("\n");
    return 0;
}


