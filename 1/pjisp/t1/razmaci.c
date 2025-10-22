#include <stdio.h>
#include <string.h>

#define MAX 101

int main(){

    char string[MAX];

    printf("Unesite string za proveru: ");
    fgets(string, MAX, stdin);

    int d = strlen(string) -1;

    int levo=0;
    int desno = 0;

    for(int i=0; i<d; i++) {
        if(string[i] == ' '){
            levo++;
        }
        else {
            i=d;
        }
    }

    for(int i=0; i<d; i++) {
        if(string[d-i-1] == ' ') {
            desno++;
        }
        else{
            i=d;
        }
    }

    printf("\nbr razmaka sleva: %d\n", levo);
    printf("br razmaka s desne strane: %d\n", desno);


    printf("\nIzmenjeni string: ");

    for(int i=levo; i<d-desno; i++){
        printf("%c", string[i]);
    }

    printf("h\n\n");


    return 0;
}