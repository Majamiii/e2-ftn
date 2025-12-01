#include <iostream>

#include "valjak.hpp"

using namespace std;

int main()
{
    Krug k1, k2(3);
    cout<<k2.getR()<<endl;
    cout<<k2.getO()<<endl;
    cout<<k2.getP()<<endl;
    cout<<"*********"<<endl;
    Pravougaonik p1, p2(4,5);
    cout<<p2.getA()<<endl;
    cout<<p1.getA()<<endl;
    cout<<"*********"<<endl;
    Valjak v1, v2(2,4);
    cout<<v1.getR()<<" i "<<v1.getH()<<endl;
    cout << v1.getP() << " "<<v1.getV()<<endl;
    cout<<v2.getR()<<" i "<<v2.getH()<<endl;
    cout << v2.getP() << " "<<v2.getV()<<endl;
    return 0;
}
