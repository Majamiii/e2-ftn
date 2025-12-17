#ifndef KOCKICA_HPP_INCLUDED
#define KOCKICA_HPP_INCLUDED

#include <iostream>
#include <ctime>


class Kockica{
private:
    int vrednost;
public:
    int getVrednost() const;
    void baci();
    Kockica();
    Kockica(int i);
    Kockica(const Kockica& k);
};


#endif // KOCKICA_HPP_INCLUDED
