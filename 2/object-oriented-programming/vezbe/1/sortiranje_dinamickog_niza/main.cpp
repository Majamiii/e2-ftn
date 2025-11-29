/*

2 ZADATAK
C++
Napisati program za sortiranje dinamički alociranog niza čija se dužina i
elementi unose preko konzole.

IMPLEMENTIRATI

 funkciju za unos elemenata sa dva argumenta
    1. pokazivač na niz
    2. dužina niza
 funkciju za sortiranje sa tri argumenta
    1. pokazivač na niz
    2. dužina niza
    3. vrsta sortiranja (RASTUCE, OPADAJUCE) - nebrojivi tip podataka
 funkciju za štampanje elemenata sa dva argumenta
    1. pokazivač na niz
    2. dužina niza

*/


#include <iostream>

using namespace std;

enum VrstaSortiranja {RASTUCE, OPADAJUCE};

void unos(int *niz, int duzina);
void sortiraj(int *niz, int duzina, VrstaSortiranja vrsta);
void stampaj(int *niz, int duzina);

int main()
{
    int duzina = 0;
    cout << "Unesite duzinu niza: ";
    cin >> duzina;

    if(duzina <= 0){
        cout << "Greska: Duzina niza mora biti pozitivna vrednost.";
        return 0;
    }

     // dinamicka alokacija memorije niza promenjivih tipa 'int' duzine 'duzina'
    int *niz = new int[duzina];

    if(niz == NULL){
        cout << "Racunar nema dovoljno memorije!" << endl;
        return 0;
    }

    unos(niz,duzina);
    cout << "Nesortiran niz: ";
    stampaj(niz, duzina);
    sortiraj(niz, duzina, RASTUCE);
    cout << endl << "Sortiran niz, rastuce: ";
    stampaj(niz, duzina);
    cout<<endl;
    sortiraj(niz, duzina, OPADAJUCE);
    cout << "Sortiran niz, opadajuce: ";
    cout<<endl;
    stampaj(niz, duzina);

    // oslobadjamo memoriju
    delete[] niz;

    return 0;
}




void unos(int *niz, int duzina){
    cout << "Unesite elemente niza."<<endl;

    for (int i=0; i<duzina; i++){
        cin >> niz[i];
    }
    cout <<endl;
}

void stampaj(int *niz, int duzina){
    cout << "Elementi niza su: [";

    for (int i=0; i<duzina; i++){
        if (i == duzina-1){
            cout << niz[i]<<"]";
        }
        else {
            cout << niz[i] << ", ";
        }
    }
}


void sortiraj(int *niz, int duzina, VrstaSortiranja vrsta){
    int temp=0;
    switch (vrsta){
        case RASTUCE:
            for (int i=0; i<duzina-1; i++){
                int minIndex = i;
                for (int j=i+1; j<duzina; j++){
                    if (niz[j]<niz[minIndex]){
                        minIndex = j;
                    }
                }
                if (i != minIndex){
                    temp = niz[i];
                    niz[i] = niz[minIndex];
                    niz[minIndex] = temp;
                }
            }
            break;

        case OPADAJUCE:
            for (int i=0; i<duzina-1; i++){
                int minIndex = i;
                for (int j=i+1; j<duzina; j++){
                    if (niz[j]>niz[minIndex]){
                        minIndex = j;
                    }
                }
                if (i != minIndex){
                    temp = niz[i];
                    niz[i] = niz[minIndex];
                    niz[minIndex] = temp;
                }
            }
            break;

        }

}
