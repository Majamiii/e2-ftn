#include <iostream>
#include "putnik_dete.hpp"
#include "zicara.hpp"
using namespace std;

int main()
{
    Karta k1(), k2(5, SKI_OPENING);
    Putnik p1(5, SKI, "0702003773633", "Jovan Jovanovic");
    PutnikDete p2(p1, "0304001778677");
    cout<<p1;
    VrstaKarte a=p1.getVrstaKarte();
    cout<< "pass:"<< a<<endl;
    DinString jmbg=p2.getMb();
    cout<<jmbg<<"\t\t\t"<<endl;
    cout<<"---------**********---------"<<endl;
    cout<<p2;

    Zicara zic1();
    return 0;
}
