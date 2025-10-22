/*Unosom sa tastature je zadat niz X od maksimalno 50 celobrojnih elemenata. 
Učitati n elemenata u niz X i formirati nizove A i B, pri čemu su elementi niza A parni elementi niza X, 
a elementi niza B su elementi niza X sa neparnim indeksom (1,3,5,...).

Izračunati SRVA srednju vrednost niza A. Na izlazu štampati elemente nizova A, B i SRVA srednju vrednost niza A.*/

/*
NAUCENO:
- floating point precision setting
*/


#include <stdio.h>
#define MAX_EL 50

int main(){

    int x[MAX_EL];
    int num=0;

    do{
        printf("Unesi broj clanova niza: ");
        scanf("%d", &num);
    }while(num<1 || num>=MAX_EL);

    int m=0;
    int n=0;
    int suma = 0;

    int a[MAX_EL];
    int b[MAX_EL];

    for(int i=0; i<num; i++) {
        printf("a[%d] = ", i);
        scanf("%d", &x[i]);
    }
    
    for(int i=0; i<num; i++) {

        if(x[i]%2 == 0){
            a[m] = x[i];
            m++;
            suma += x[i];
        }
        if(i%2 == 1){
            b[n] = x[i];
            n++;
        }

    }

    float srva = 0;
    
    if(m!=0){
        srva = (float)(suma / m);
        printf("\nSrednja vrednost A: %.2f\n", srva);
    }
    else {
        printf("\nNiz A nema elemente, pa je nemoguce izracunati njihovu srednju vrednost.\n");
    }


    printf("Niz A = [");

    for(int i=0; i<m; i++) {
        if(i!=m-1){
            printf("%d, ", a[i]);
        }
        else{
            printf("%d]\n", a[i]);
        }
    }
    printf("Niz B = [");

    for(int i=0; i<n; i++) {
        if(i!=n-1){
            printf("%d, ", b[i]);
        }
        else{
            printf("%d]\n", b[i]);
        }
    }

    return 0;
}


