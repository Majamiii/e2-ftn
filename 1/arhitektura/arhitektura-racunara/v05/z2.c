// Napraviti potprogram int palindrom(char *str) koji proverava da li je string palindrom.
//  Ako jeste, vratiti 1, u suprotnom vratiti 0.

#include <stdio.h>
#include <string.h>

int palindrom(char *str);
int cpalindrom(char *str);

int main(){

    char str[100];

    printf("Unesi string: ");
    scanf("%s", str);
    //  char *str = "ana";

    int b = 0;
    b = palindrom(str);

    if (b) {
        printf("\nString je palindrom!\n");
    }
    else{
        printf("\nString nije palindrom!\n");
    }

    return 0;
}

/*

int cpalindrom(char *str){

    int p = 1;

    for(int i=0; i<strlen(str)/2+1; i++){

        if (str[i]!=str[strlen(str)-i-1]){
            p =0;
            return p;
        }
    
    }
    return p;
}*/