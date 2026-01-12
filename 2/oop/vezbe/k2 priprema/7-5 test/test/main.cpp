#include "kolokvijum.hpp"
#include "student.hpp"

int main()
{
    Kolokvijum test1, test2("pjisp");
    test2.ispis();
    cout<<test2.polozio()<<endl;

    Kolokvijum test3("analiza"),test4("algebra"),test5("engleski");

    Test *pr = &test2;
    Test *pr3 = &test3;
    Test *pr4 = &test4;
    Test *pr5 = &test5;

    List<Test*> listica;
    listica.add(1,pr);
    listica.add(1,pr3);
    listica.add(1,pr4);
    listica.add(1,pr5);

    const DinString prviSemestar="prviSemestar";
    Predmet p1, p2(prviSemestar, listica), p3(p2);

    cout<<"Polozen prvi semestar? "<<p2.polozio()<<endl;
    cout<<"Ukupni poeni: "<<p2.getUkupniPoeni()<<endl<<endl<<endl;

    p2.ispis();

    return 0;
}
