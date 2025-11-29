#include <iostream>
using namespace std;

enum TypeOfSortiranje{ //ENUMERACIJA TIPOVA SORTA:
    RASTUCE = 0,
    OPADAJUCE
};

void UnosElementa (int *niz, int duzina){
    cout << "unesite elemente niza:" << "\t" << endl;

    for (int i = 0; i < duzina; i++){
            cout << "\t niz[" << i << "] = " << endl;
            cin >> niz[i];
    }

    cout << endl;

}

void stampaj(int *niz, int duzina){

    for(int i = 0; i < duzina; i++){
         cout << "\tniz[" << i << "] = " << niz[i] << endl;
    }
    cout << endl;
}

void SortiranjeNiza(int *niz, int duzina, TypeOfSortiranje tip){

    int temp;

    switch (tip) {
        case RASTUCE:
            for (int i = 0; i < duzina-1; i++){
                int MinIndx = i;
                for (int j = i+1; j  < duzina; j++) {
                    if (niz[i] > niz[MinIndx]) {
                        MinIndx = j;
                    }
                }
            //AKO SE DESIO NAJMANJI PRI PROLASKU:

                if (MinIndx != i) { //swappin algorithm
                    temp = *(niz+i);
                    *(niz + i) = *(niz + MinIndx);
                    *(niz + MinIndx) = temp;
                }
            }
            break;
        case OPADAJUCE:
            for (int i = 0; i < duzina-1; i++){
                int MaxIndx = i;
                for (int j = i+1; j  < duzina; j++) {
                    if (niz[i] < niz[MaxIndx]) {
                        MaxIndx = j;
                    }
                }
                if (MaxIndx != i) { //swappin algorithm
                    temp = *(niz+i);
                    *(niz + i) = *(niz + MaxIndx);
                    *(niz + MaxIndx) = temp;
                }
            }
        break;
    }
}
int main(){

    int duzina;

    cout << "unesite duzinu niza ->" << endl;
    cin >> duzina;

    if (duzina==0) { //provera validnosti:
        cout << "Uneli ste nedozvoljenu vrednost!!!" << endl;
        return 0;
    }

    //dinamicka alokacija
    int *niz = new int[duzina];

    if (niz == NULL){ //provera dostupnosti memorije
        cout << "nema dovoljno memorije";
        return 0;
    }

    //////FUNKCIJE:
    UnosElementa(niz, duzina);
    cout << "Niz pre sort:"<< "\t";
    stampaj(niz, duzina);

    cout << "Niz posle rastuceg sort:"<< "\t" << endl;
    SortiranjeNiza(niz, duzina, RASTUCE);
    stampaj(niz, duzina);

    cout << "Niz posle opadajuceg sort:"<< "\t"<<endl;
    SortiranjeNiza(niz, duzina, OPADAJUCE);
    stampaj(niz, duzina);

    //oslobadjanje memorije:

    delete[] niz;

    return 0;
}
