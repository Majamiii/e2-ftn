#ifndef SEMAPHORE_HPP_INCLUDED
#define SEMAPHORE_HPP_INCLUDED

enum States {sOFF, sON, sOUT, sBLINK};
enum Colours {cNONE, cBLINK, cRED, cYELLOWRED, cGREEN, cYELLOW};

class Semaphore
{
    private:
        States state;
        Colours colour;

    public:
        Semaphore();
        bool turnOn();
        bool turnOff();
        bool turnBlink();
        bool turnOut();
        bool repair();
        bool changeColour();
        States getState()const;
        Colours getColour()const;

};

#endif // SEMAPHORE_HPP_INCLUDED
