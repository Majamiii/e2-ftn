#ifndef SEMAPHORE_HPP_INCLUDED
#define SEMAPHORE_HPP_INCLUDED

#include <iostream>

using namespace std;


enum StateSemaphore {
    sOFF,
    sON,
    sBLINK,
    sOUT
};

enum StateLight {
    cNONE,
    cBLINK,
    cRED,
    cYELLOWRED,
    cYELLOW,
    cGREEN
};

class Semaphore {
private:
    StateLight StanjeSvetla;
    StateSemaphore StanjeSemafora;

public:
    Semaphore();
    bool turnON();
    bool turnOFF();
    bool turnBLINK();
    bool turnOUT();
    bool repair();
    bool changeCOLOUR();
    StateLight getLight()const;
    StateSemaphore getState()const;
};

#endif // SEMAPHORE_HPP_INCLUDED
