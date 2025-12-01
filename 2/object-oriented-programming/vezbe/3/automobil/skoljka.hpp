#ifndef SKOLJKA_HPP_INCLUDED
#define SKOLJKA_HPP_INCLUDED

enum bojaSkoljke {PLAVA, CRVENA, ZELENA};

class Skoljka{

private:
    bojaSkoljke boja;

public:
    Skoljka(){
        boja = PLAVA;
    }
    Skoljka(bojaSkoljke b){
        // dodati proveru
        boja = b;
    }
    bojaSkoljke getBoja() const{
        return boja;
    }
    void setBoja(bojaSkoljke b){
        // dodati proveru
        boja = b;
    }
};

#endif // SKOLJKA_HPP_INCLUDED
