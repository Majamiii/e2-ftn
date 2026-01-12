#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <iostream>
#include "dinstring.hpp"
#include "list.hpp"
using namespace std;

class Test{
protected:
    DinString naziv;
    int osvojeniPoeni;
public:
    virtual int getPoeni() const=0;
    virtual bool polozio() const=0;

    Test() : naziv(""),osvojeniPoeni(0) {}
    Test(const DinString& nnaziv, int poeni) : naziv(nnaziv),osvojeniPoeni(poeni) {}

    virtual ~Test() {}

    void ispis(){
        cout<<endl<<"naziv testa: "<<naziv<<endl;
        cout<<"broj poena: "<<osvojeniPoeni<<endl;
    }

};

#endif // TEST_HPP_INCLUDED
