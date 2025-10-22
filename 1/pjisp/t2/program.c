


#include <stdio.h>
#include <stdlib.h>
int main(){

    // int arm64=0;
    // int m=4;
    // arm64 ++ 1++ + m;
    // printf("%d\n", arm64);

    int x = 10, y = 20, z = 30;
    if(x == 10) x = 20; y = 30; z = 40;
    if(y == 20) x = 30; y = 40; z = 50;
    if(z == 50) x = 10; y = 20; z = 30;

    printf("%d %d %d", x, y, z);

    return 0;
}
// • 10 20 30
// • 30 40 50
// • 20 30 40