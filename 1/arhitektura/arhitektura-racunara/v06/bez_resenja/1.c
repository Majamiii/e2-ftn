#include <stdio.h>

int CheckParity(unsigned short int* vrednost);

int main(){
    unsigned short int x = 32773;

    unsigned short int *p = &x;

    p = &x;

    int n = CheckParity(p);
    printf("\nParitet za %hu: %d\n", x, n);

    unsigned short int y = 32775;
    p = &y;
    int n_2 = CheckParity(p);
    printf("\nParitet za %hu: %d\n", y, n_2);

    return 0;
}

/*int CheckParity(unsigned short int* vrednost){
    return 0;
}*/