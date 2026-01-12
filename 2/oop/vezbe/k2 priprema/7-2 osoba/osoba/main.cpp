#include "student.hpp"
#include "ucionica.hpp"

using namespace std;

int main()
{

    Osoba o("Maja", "Milovic"), nepoznata;
    o.ispis();nepoznata.ispis();

    // ----------------
    Student s("n","n",1);
    s.ispis();


    Ucionica u("skola", 10);
    u.dodaj(o);
    u.dodaj(s);
    u.dodaj(nepoznata);
    u.ispis();

    return 0;
}
