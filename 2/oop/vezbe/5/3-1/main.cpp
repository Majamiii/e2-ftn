#include <iostream>

#include "pravilanoblik.hpp"

using namespace std;

int main()
{
    cout<<endl<<"****  pravougaonik  ******"<<endl<<endl;
    Pravougaonik p1(1,2);
    cout << p1.getP()<<endl;
    cout<<p1.getO()<<endl;

    cout<<endl<<"****  elipsa  ******"<<endl<<endl;
    Elipsa e(3,2);
    cout<<e.getP()<<endl;
    cout<<e.getO()<<endl;

    cout<<endl<<"*****   oblik  ******"<<endl<<endl;
    Oblik o(5,4);
    cout<<"Oblik"<<endl;
    cout<<o.getP()<<endl<<o.getO()<<endl;

    cout<<endl<<"***** pravilan oblik ******"<<endl<<endl;

    PravilanOblik po(5);
    cout<<po.getP()<<endl;
    cout<<po.getO()<<endl;

    cout<<endl<<"******************"<<endl;
    return 0;
}
