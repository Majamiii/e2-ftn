#include <stdio.h>

// fibonaci rekurzijom u c-u
int fibonaci(int n);

int main(){

    int n=30;
    
    // fib = 832040
    
    int rez = fibonaci(30);
    printf("rezultat: %d\n", rez);

    return 0;
}

int fibonaci(int n){

    int rez;

    if(n<3){
        return 1;
    }

    else{
        rez = fibonaci(n-1) + fibonaci(n-2);
    }

    return rez;
}