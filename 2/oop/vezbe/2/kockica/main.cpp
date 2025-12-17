#include "kockica.hpp"

#define KRAJ_BROJ 3

using namespace std;

int menu(){
    cout << "1 za bacanje, 2 za vracanje vrednosti, 3 za kraj"<<endl<<endl;
    int n;
    cin >> n;
    return n;
}

int main()
{
    srand(time(0));
    Kockica k1();
    Kockica k2(3);
    Kockica k3(k2);
    k3.baci();
    cout << k3.getVrednost()<<endl<<endl;
    int n=0;

    do{
        n = menu();
        switch(n){
            case 1:
                k3.baci();
                cout << "Kocka je bacena"<<endl<<endl;
                break;
            case 2:
                cout << "Vrednost kocke je "<<k3.getVrednost()<<endl<<endl;
                break;
            case 3:
                cout<<"ggwp"<<endl<<endl;
                break;
        }

    }while(n != KRAJ_BROJ);


    return 0;
}
