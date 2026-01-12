#include "dijamant.hpp"

using namespace std;

int main()
{

    /*
    Napisati kratak test program u kojem de biti istestirana konkretizacija generičke
    klase Trezor<class SADRZAJ, int KAPACITET> koja za svoj SADRZAJ ima objekte
    klase Dijamant. Obavezno istestirati sve konstruktore i metode.
    */
    Trezor<Dijamant, 10> t;

    Dijamant d1, d2(100000,40), d3(d2);

    cout<<d1<<d2<<d3;

    t.ubaciSadrzaj(d1);
    t.ubaciSadrzaj(d3);

    cout<<t.getBrojPopunjenihSefova()<<endl<<endl;

    cout<<t.izbaciSadrzaj(7)<<endl;


    return 0;
}
