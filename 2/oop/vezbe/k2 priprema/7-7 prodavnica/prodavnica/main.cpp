#include "voce.hpp"
#include "odeca.hpp"
#include "prodavnica.hpp"

int Odeca::brojVelike=0;

int main()
{
    DinString jabukaa="jabuka", srb="Srbija", xsmajica="majica", pantalone="pantalone",velikam="l majica",xlm="xl majica";
    Voce jabuka(jabukaa,100,srb,5);
    jabuka.ispisi();

    cout<<endl<<"---------------------"<<endl<<endl;
    Odeca m1(500,xsmajica,XS,MAJICA);
    m1.ispisi();
    Odeca m2(100, velikam, L, MAJICA);
    Odeca p1(800, pantalone, M, PANTALONE);

    DinString maxi="Maxi";
    Prodavnica p(maxi);

    p.dodajProizvod(jabuka);
    p.dodajProizvod(m1);
    p.dodajProizvod(m2);

    p.ispisi();

    return 0;
}
