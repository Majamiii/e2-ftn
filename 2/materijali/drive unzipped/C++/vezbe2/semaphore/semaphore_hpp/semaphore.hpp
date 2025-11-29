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
    Semaphore()
    {
        state = sOFF;
        colour = cNONE;
    }

    bool turnOn()
    {
        if(state==sOFF)
        {
            state=sON;
            colour = cRED;
            return true;
        }
        return false;
    }

    bool turnOff()
    {
        if(state==sON || state ==sBLINK)
        {
            state=sOFF;
            colour = cNONE;
            return true;
        }
        return false;
    }

    bool turnBlink()
    {
        if(state==sOFF)
        {
            state=sBLINK;
            colour = cBLINK;
            return true;
        }
        return false;
    }

    bool turnOut()
    {
        if(state!=sOUT)
        {
            state=sOUT;
            colour = cNONE;
            return true;
        }
        return false;
    }

    bool repair()
    {
        if(state==sOUT)
        {
            state=sOFF;
            colour = cNONE;
            return true;
        }
        return false;
    }

    bool changeColour()
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

    States getState()const
    {
        return state;
    }

    Colours getColour()const
    {
        return colour;
    }

};

#endif // SEMAPHORE_HPP_INCLUDED
