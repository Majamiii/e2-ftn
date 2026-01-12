#include "phd.hpp"

using namespace std;

void predstavljanje1(Osoba osoba)
{
    cout << "Predstavljanje 1: ";
    osoba.predstaviSe();
}

void predstavljanje2(const Osoba &osoba)
{
    cout << "Predstavljanje 2: ";
    osoba.predstaviSe();
}

int main()
{
    // --- osoba ---
    Osoba o1;
    o1.predstaviSe();

    DinString ime("Maja");
    DinString prezime("Milovic");
    Osoba o(ime, prezime);
    o.predstaviSe();

    // --- student ---
    Student s(o, 69);       // ne trollujem zapravo mi je to br indeksa HAHAH - u slucaju da ovo iko ikad procita
    s.predstaviSe();

    // phd
    Phd p(s,7.77);
    p.predstaviSe();

    predstavljanje1(o);
    predstavljanje2(o);

    predstavljanje1(s);
    predstavljanje2(s);

    predstavljanje1(p);
    predstavljanje2(p);

    return 0;
}
