#ifndef MACHINE_HPP_INCLUDED
#define MACHINE_HPP_INCLUDED


#include <iostream>

using namespace std;

enum MachineState {sA, sB, sC, sD};

class Machine{

private:
    int vrednost;
    MachineState currentState;
public:
    Machine();
    bool MetodaX();
    bool MetodaY();
    bool MetodaZ();
    bool MetodaW();
    bool plus();
    bool minus();
    MachineState getCurrentState() const;
    int getValue() const;

};


#endif // MACHINE_HPP_INCLUDED
