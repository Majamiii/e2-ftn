#include <stdio.h>

unsigned int RUNPP_REG_ERR = 0;

int prebrojNajviseUzastopnih(unsigned long long* vrednost);

void printbin64(unsigned long long x) {
    unsigned long long m=0x8000000000000000ULL;
    int s=0;
    while(m) {
        printf("%s%s",m&x ? "1" : "0",++s%8 ? "" : " ");
        m >>= 1;
    }
    printf("\n");
}

int main() {
    unsigned long long v;
    int r;

    printf("Vrednost (hex): ");
    v = 18430708796247572227;
    scanf("%llx",&v);
    //  v = 15;
    printf("Binarno: ");
    //  11111111 11000111 00001000 00000000 00000111 00000000 11111111 00000011  - treba da bude 16
    // 18430708796247572227
    printbin64(v);
    r = prebrojNajviseUzastopnih(&v);
    printf("Najveci broj uzastopnih nula je %d\n", r);

    #ifdef LEVEL42
    printf("\nRUNPP_REG_ERR:%d\n",RUNPP_REG_ERR);
    #endif
    return 0;
}
