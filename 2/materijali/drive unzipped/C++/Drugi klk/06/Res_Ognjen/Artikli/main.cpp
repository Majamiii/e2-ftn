#include <iostream>
#include "artikal.hpp"

using namespace std;

int main(){
    Artikal a1("Banana", 80);
    cout << a1 << endl;
    DinString ds2("orbit lepi od borovnice");
    Artikal a2(ds2, 66.6);
    cout << a2 << endl;

    {
        Artikal a3(a2);
        cout << a3 << endl;
    }

    cout << a2 << endl;

}
