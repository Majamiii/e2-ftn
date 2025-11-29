#include "semaphore.hpp"

Semaphore::Semaphore(){
    StanjeSemafora = sOFF;
    StanjeSvetla = cNONE;
}

bool Semaphore::turnON(){
    if (StanjeSemafora == sOFF) {
        StanjeSemafora = sON;

        return true;
    }
    return false;
}

bool Semaphore::turnOFF(){
    if (StanjeSemafora == sON || StanjeSemafora== sBLINK) {
        StanjeSemafora = sOFF;
        StanjeSvetla = cNONE;
        return true;

    }
    return false;
}

bool Semaphore::turnBLINK(){
    if (StanjeSemafora == sOFF) {
        StanjeSemafora = sBLINK;
        StanjeSvetla = cBLINK;
        return true;
    }
return false;
}

bool Semaphore::turnOUT(){
    if (StanjeSemafora == sON || StanjeSemafora == sOFF || StanjeSemafora == sBLINK){
        StanjeSemafora = sOUT;
        StanjeSvetla = cNONE;
        return true;
    }
return false;
}

bool Semaphore::repair(){
    if (StanjeSemafora == sOUT){
        StanjeSemafora = sOFF;
        StanjeSvetla = cNONE;
        return true;
    }
    return false;
}

bool Semaphore::changeCOLOUR(){
    if (StanjeSemafora == sON) {
        switch (StanjeSvetla) {
        case cNONE:
            StanjeSvetla = cRED;
            break;
        case cRED:
            StanjeSvetla = cYELLOWRED;
            break;
        case cYELLOWRED:
            StanjeSvetla = cGREEN;
            break;
        case cGREEN:
            StanjeSvetla = cYELLOW;
            break;
        case cYELLOW:
            StanjeSvetla = cRED;
            break;
        }
        return true;
    }
    return false;
}

StateLight Semaphore::getLight()const{
    return StanjeSvetla;
}

StateSemaphore Semaphore::getState()const{
    return StanjeSemafora;
}









