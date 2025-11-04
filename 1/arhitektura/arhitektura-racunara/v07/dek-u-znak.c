#include <stdio.h>

int znak(int broj, char *odrediste);

int main()
{
    char znakovni[30];
    int uspesno = znak(12345, znakovni);

    if(uspesno){
        printf("u znakovnom obliku ovaj broj je: %s\n", znakovni);
    }

    return 0;
}