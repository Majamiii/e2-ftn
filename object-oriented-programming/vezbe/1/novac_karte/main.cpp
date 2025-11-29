/*
3-1 ZADATAK
C++
Napisati funkciju za izračunavanje svote novca potrebne za kupovinu karata za
bioskop.
Funkcija ima dva parametra za broj karata i cenu jedne karte. Ukoliko se cena
karte ne navede koristi se podrazumevana cena koja iznosi 50 dinara.
Testirati implementiranu funkciju.
*/

#include <iostream>

using namespace std;

int novac(int broj, int cena=50);

int main()
{
    cout << "Broj karata: ";
    int n=0;
    cin >> n;

    cout << "Cena karte: ";
    int cena;
    cin >> cena;

    int uk = novac(n, cena);
    cout <<uk<<endl;

    cout << novac(6);

    return 0;
}

int novac(int broj, int cena){
    return cena*broj;
}
