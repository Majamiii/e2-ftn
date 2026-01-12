#ifndef TELEFON_HPP_INCLUDED
#define TELEFON_HPP_INCLUDED

#include "dinstring.hpp"

class Telefon{
protected:
    DinString broj;
public:
    Telefon() : broj("000000000") {}
    Telefon(DinString& nekiBroj) : broj(nekiBroj) {}

    bool pozovi(const DinString& a){
        if(a != broj){
            return true;
        }else{
        return false;}
    }
};

#endif // TELEFON_HPP_INCLUDED
