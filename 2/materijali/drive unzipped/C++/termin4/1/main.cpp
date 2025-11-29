#include <iostream>
using namespace std;

#include "JSTrougao.hpp"

int main(){
    Trougao t1(1,4,4);  //ima tri parametra
    JKTrougao jk1(2,3); //ima dva parametra, treci je jednak drugom - definisan konstruktorom nadklase
    JSTrougao js1(5);   //ima jedan parametar ^^^^^^^^^^^^^^^^^^^^^^^

    cout<<t1.getP()<<endl;
    cout<<jk1.getP()<<endl;
    cout<<js1.getP()<<endl;

    return 0;
}
