#ifndef KOCKA_HPP_INCLUDED
#define KOCKA_HPP_INCLUDED
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "kocka.hpp"

using namespace std;

class Kocka{
private:
    int vrednost;

public:
    Kocka();
    Kocka(int);
    Kocka(const Kocka&);

    void baci();
    int getVrednost() const;
};

#endif // KOCKA_HPP_INCLUDED
