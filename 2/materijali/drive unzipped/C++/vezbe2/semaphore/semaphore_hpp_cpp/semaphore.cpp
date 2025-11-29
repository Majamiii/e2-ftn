#include "semaphore.hpp"

Semaphore::Semaphore()
{
    state = sOFF;
    colour = cNONE;
}

bool Semaphore::turnOn()
{
    if(state==sOFF)
    {
        state=sON;
        colour = cRED;
        return true;
    }
    return false;
}

bool Semaphore::turnOff()
{
    if(state==sON || state ==sBLINK)
    {
        state=sOFF;
        colour = cNONE;
        return true;
    }
    return false;
}

bool Semaphore::turnBlink()
{
    if(state==sOFF)
    {
        state=sBLINK;
        colour = cBLINK;
        return true;
    }
    return false;
}

bool Semaphore::turnOut()
{
    if(state!=sOUT)
    {
        state=sOUT;
        colour = cNONE;
        return true;
    }
    return false;
}

bool Semaphore::repair()
{
    if(state==sOUT)
    {
        state=sOFF;
        colour = cNONE;
        return true;
    }
    return false;
}

bool Semaphore::changeColour()
{
    if(state==sON)
    {
        switch(colour)
        {
        case cRED:
            colour = cYELLOWRED;
            break;
        case cYELLOWRED:
            colour = cGREEN;
            break;
        case cGREEN:
            colour = cYELLOW;
            break;
        case cYELLOW:
            colour = cRED;
            break;
        }
        return true;
    }
    return false;
}

States Semaphore:: getState()const
{
    return state;
}

Colours Semaphore:: getColour()const
{
    return colour;
}
