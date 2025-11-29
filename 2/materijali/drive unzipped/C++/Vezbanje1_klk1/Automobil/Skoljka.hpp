#ifndef SKOLJKA_HPP_INCLUDED
#define SKOLJKA_HPP_INCLUDED

enum BojaSkoljke {
    PLAVA,
    CRVENA,
    ZELENA
};

class Skoljka {
private:
    BojaSkoljke Boja;
public:
    Skoljka () {
        Boja = PLAVA;
    }
    Skoljka (BojaSkoljke boja) {
        Boja = boja;
    }
    Skoljka (const Skoljka& skljk) {
        Boja = skljk.Boja;
    }
    void setBoja(BojaSkoljke boja) {
        Boja = boja;
    }
    BojaSkoljke getBoja() const {
        return Boja;
    }
    friend void ispisiSkoljku (const Skoljka&);
};

#endif // SKOLJKA_HPP_INCLUDED
