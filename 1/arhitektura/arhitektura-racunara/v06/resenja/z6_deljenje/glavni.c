#include <stdio.h>

// potprogram za deljenje pomoću šiftovanja
int deli_bin(unsigned long long a, unsigned long long b,
              unsigned long long *r);

int main() {
    int g;
    unsigned long long a, b, r;

    a = 136ULL;
    b = 23455ULL;

    g = deli_bin(a, b, &r);

    printf("Rezultat:%llu\n",r);
    printf("Greska  :%d\n",g);
    if (b!=0)
        printf("Tacno   :%llu\n",a*b);
    else
        printf("Tacno   :Greska\n");

    return 0;
}


/*

    unsigned int kol,ost,a,b,maska;
    kol = 0;
    ost = 0;
    a = 53;
    b = 5;
    maska = 0x80000000; //početna maska
        while (maska) { //dok se ne obrade svi biti
            ost <<= 1;
            if (maska & a) //kopiranje bita iz a
                ost |= 1; //u ostatak
            if (ost >= b) { //ako se b sadrži u tekućem ost
                ost -= b; //oduzmi b od tekućeg ostatka
                kol |= maska;//postavi 1 u količnik
            }
            maska >>= 1;
    }


*/
