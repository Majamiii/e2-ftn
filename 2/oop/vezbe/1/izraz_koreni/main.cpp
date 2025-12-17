/*

3 ZADATAK
C++
Napisati funkciju koja za zadati pozitivan ceo broj 𝑛 izračunava vrednost izraza
𝑟𝑒𝑧 = √1 + √2 + ⋯ + √𝑛 zaokružen na dve decimale.
Testirati implementiranu funkciju.

*/

#include <iostream>
#include <math.h>   // isto kao include cmath
#include <iomanip>

using namespace std;

int main()
{
    cout << "Unesi pozitivan broj n: " << endl;
    int n;
    cin>>n;

    if (n <= 1) {
        cout << "Broj mora da bude pozitivan.";
        return 1;
    }

    float suma = 0;

    for (int i=1; i<=n; i++){
        suma += sqrt(i);
    }

    cout << "Trazena suma je "<< fixed << setprecision(2) <<suma<<endl;

    suma *= 100;
    round(suma);
    suma /= 100;

    cout << "Trazena suma je "<< suma<<endl;

    return 0;
}
