#include <iostream>

using namespace std;

#include "figura.hpp"
#include "kvadrat.hpp"
#include "krug.hpp"
#include "oblik.hpp"

void predstavljanje(const Figura& f){
    cout<<f.getO()<<endl;
    cout<<f.getP()<<endl;
}

int main()
{
    // Figura f;
    // apstraktne klase se ne mogu istancirati

    Figura *f;
    // moze pokazivac ali ne moze sam objekat

    pravougaonik p1;
    pravougaonik p(2,3);
    predstavljanje(p);

    Kvadrat k(5);
    predstavljanje(k);

    Krug krug(3);
    predstavljanje(krug);

    Oblik oblik(3);
    cout<<oblik.getO()<<endl;
    cout<<oblik.getP()<<endl;

    return 0;
}
