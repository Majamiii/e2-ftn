#include "student.hpp"
#include "ucionica.hpp"

using namespace std;

int main()
{

    Osoba o("Maja", "Milovic"), nepoznata;
    o.ispisi();nepoznata.ispisi();

    // ----------------
    Student s("n","n",1);
    s.ispisi();

    cout<<"----ucionica ----"<<endl<<endl;
    Ucionica u("skola", 10);
    u.dodaj(o);
    u.dodaj(s);
    u.dodaj(nepoznata);
    u.ispis();

    return 0;
}
