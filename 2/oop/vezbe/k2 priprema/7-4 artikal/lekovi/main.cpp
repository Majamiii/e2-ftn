#include "EvidencijaLekova.hpp"

using namespace std;

int main()
{
    Lek l1;
    Lek l2(1234, "brufen", 3, 500), l3(l2);

    cout<<l1<<l2<<l3;

    EvidencijaLekova e;
    e.dodajLek(l1);
    cout<<e;

    e.dodajLek(l2);
    cout<<e;

    e.sortirajLekove();
    cout<<e;

    e.ukloniLek(1);
    cout<<e;

    e.dodajLek(8572456, "magicni napitak", 1000, 10000000000);
    cout<<e;

    return 0;
}
