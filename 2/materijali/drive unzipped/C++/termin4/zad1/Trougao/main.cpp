#include "trougao.hpp"
#include "JKtrougao.hpp"


int main()
{
    Trougao t1,  t2(5, 6, 7), t3(t1);
    JKtrougao jkt1, jkt2(4, 10), jkt3(jkt1);
    JKtrougao() : Trougao(3, 3, 5) {}

    t1.getA();
    t1.getB();
    t1.getC();
    cout << t1.getO() << endl;
    cout << t1.getP() << endl;
    cout << jkt1.getO() << endl;
    cout << jkt1.getP() << endl;


    return 0;
}
