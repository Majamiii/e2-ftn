#ifndef TELEFON2_HPP_INCLUDED
#define TELEFON2_HPP_INCLUDED

#include "telefon.hpp"
#include "kamera.hpp"

class Telefon2:public Telefon{
protected:
    Kamera cam;
public:
    Telefon2() : Telefon(), cam() {}
    Telefon2(DinString& br, int pikseli, int prostor) : Telefon(br),cam(pikseli,prostor) {}

    bool slikajSliku(){
        return cam.slikaj();
    }
};

#endif // TELEFON2_HPP_INCLUDED
