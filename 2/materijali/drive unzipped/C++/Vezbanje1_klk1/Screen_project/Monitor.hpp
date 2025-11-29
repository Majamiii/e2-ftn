#ifndef MONITOR_HPP_INCLUDED
#define MONITOR_HPP_INCLUDED
#include "Screen.hpp"
#include <iostream>

using namespace std;

enum MonitorStates{
    sON,
    sOFF,
    sOUT,
    sTEST,
    sSTANDBY
};

class Monitor {
private:
    MonitorStates state;
    Screen screen;
public:
    Monitor () : screen() {
        state = sOFF;
        screen.setState(ssOFF);
    }
    bool turnON() {
        if (state != sOUT){
            state = sON;
            screen.setState(ssON);
            return true;
        }
        return false;
    }
    bool turnOFF() {
        if (state != sOUT){
            state = sOFF;
            screen.setState(ssOFF);
            return true;
        }
        return false;
    }
    bool turnOUT() {
        if (state != sOUT){
            state = sOUT;
            screen.setState(ssOFF);
            return true;
        }
        return false;
    }
    bool turnTEST() {
        if (state == sON){
            state = sTEST;
            screen.setState(ssOFF);
            return true;
        }
        return false;
    }
    bool repair() {
        if (state != sOUT){
            state = sOUT;
            screen.setState(ssOFF);
            return true;
        }
        return false;
    }
    bool turnStandBy() {
        if (state == sON) {
            state = sSTANDBY;
            screen.setState(ssOFF);
            return true;
        }
        return false;
    }

    bool incB() {
        return screen.incB();
    }

    bool decB() {
        return screen.decB();
    }

    MonitorStates getMonitorState() const {
        return state;
    }

    ScreenStates getScreenStates() const {
        return screen.getState();
    }

    int getBrightness() const {
        return screen.getBrightness();
    }

    void printInfo(const Monitor&) {}
};

#endif // MONITOR_HPP_INCLUDED
