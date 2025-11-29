/*
4 ZADATAK
C++
Napisati funkciju koja na osnovu primljene godine određuje da li je godina
prestupna ili ne.
Godina je prestupna ukoliko je deljiva sa 4, osim onih koje su deljive sa 100 a
nisu deljive sa 400 u isto vreme.
2004 - da
1800 - ne
1900 - ne
2000 - da
1600 – da
Testirati implementiranu funkciju.
*/

#include <iostream>

using namespace std;

bool prestupna(int god);

int main()
{
    int godine[6] = {2004, 1800, 1900, 2000, 1600, 2025};

    for (int i=0; i<6; i++){
        if ( prestupna( godine[i] ) == true){
            cout << "Godina je prestupna."<<endl;
        }else{
            cout << "Godina nije prestupna." << endl;
        }
    }

    return 0;
}

bool prestupna(int god){
    bool prestupna = false;
    if (god % 4 == 0 ){
        if (god % 100 == 0){
            if (god % 400 == 0){
                prestupna = true;
                return prestupna;
            }
            prestupna = false;
            return prestupna;
        }
        prestupna = true;
        return prestupna;
    }
    return false;
};
