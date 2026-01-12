using namespace std;

#include "jednakostranicni.hpp"

int main()
{

    Trougao t1;
    t1.ispisi();

    Trougao t2(3,2,1);
    t2.ispisi();

    Jednakokraki t;
    t.ispisi();

    Jednakokraki m(5,6);
    m.ispisi();

    Jednakostranicni x(4);
    x.ispisi();

    return 0;
}
