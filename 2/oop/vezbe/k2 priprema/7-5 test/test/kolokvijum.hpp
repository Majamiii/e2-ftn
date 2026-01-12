#ifndef KOLOKVIJUM_HPP_INCLUDED
#define KOLOKVIJUM_HPP_INCLUDED

#include "test.hpp"

class Kolokvijum:public Test{
public:
    Kolokvijum() : Test("", 0){}
    Kolokvijum(char *naziv) : Test(naziv, rand()%25+1) {}

    int getPoeni() const{
        return osvojeniPoeni;
    }
    bool polozio() const{
        if(getPoeni()>12){
            return true;
        }else{
        return false;}
    }
};

#endif // KOLOKVIJUM_HPP_INCLUDED
