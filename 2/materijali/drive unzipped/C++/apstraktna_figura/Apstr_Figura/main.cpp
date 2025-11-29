#include <iostream>
#include "pravougaonik.hpp"
#include "kvadrat.hpp"
#include "elipsa.hpp"
#include "krug.hpp"
#include "oblik.hpp"
#include <math.h>

void predstavljanje(const Figura& f){
    cout<<f.getO()<<endl;
    cout<<f.getP()<<endl;
}


int main(){

    Pravougaonik p1(2,3), p2(), p3(p1);
    Kvadrat kv(5);
    Elipsa el(3,4);
    predstavljanje(p1);
    predstavljanje(kv);
    predstavljanje(el);
    return 0;
}
