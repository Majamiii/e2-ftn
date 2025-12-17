#ifndef MONITOR_HPP_INCLUDED
#define MONITOR_HPP_INCLUDED

#include "screen.hpp"

enum MonitorStates {sON, sOFF, sOUT, sTEST, sSTANDBY};

class Monitor
{
private:
    MonitorStates state;
    Screen screen;
public:
    Monitor() : screen() {
        state = sOFF;
    }

    bool turnOn(){
        if((state==sSTANDBY)||(state==sOFF)){
            state = sON;
            cout<<"Ekran je upaljen."<<endl;
            screen.setState(ssON);
            return 1;
        }
        else{
            cout<<"Monitor ne moze da se upali iz ovog stanja."<<endl;
            return 0;
        }
    }
    bool turnOff(){
        if((state==sTEST)||(state==sON)||(state==sSTANDBY)){
            cout<<"Monitor se gasi"<<endl;
            state = sOFF;
            screen.setState(ssOFF);
            return 1;
        }
        else{
            cout<<"Monitor ne moze da se ugasi iz ovog stanja."<<endl;
            return 0;
        }
    }
    bool turnOut(){
        if(state != sOUT){
            state = sOUT;
            cout << "Monitor prelazi u stanje sOUT"<<endl;
            screen.setState(ssOFF);
            return 1;
        }
        else{
            cout<<"Monitor je vec bio u stanju sOUT"<<endl;
            return 0;
        }
    }
    bool turnTest(){
        if(state == sON){
            cout<<"Monitor prelazi u stanje sTEST"<<endl;
            state = sTEST;
            // ne moramo da palimo screen jer jer sigurno vec upaljen jer je bio u sON
            return 1;
        }
        else{
            cout<<"Nemoguce je preci u stanje sTEST"<<endl;
            return 0;
        }
    }
    bool turnStandBy(){
        if(state == sON){
            cout<<"Monitor prelazi u stanje StandBy"<<endl;
            state = sSTANDBY;
            screen.setState(ssOFF);
            return 1;
        }
        else{
            cout<<"Nemoguce je preci u stanje standby"<<endl;
            return 0;
        }
    }
    bool repair(){
        if(state==sOUT){
            state=sOFF;
            cout<<"Monitor je popravljen."<<endl;
            return 1;
        }
        else{
            cout<<"Monitor nije bio pokvaren"<<endl;
            return 0;
        }
    }

    bool incB(){
        return screen.incB();
    }
    bool decB(){
        return screen.decB();
    }

    MonitorStates getMonitorState() const {
        return state;
    }

    ScreenStates getScreenState() const {
        return screen.getState();
    }

    int getBrightness() const {
        return screen.getBrightness();
    }

    friend void printInfo(const Monitor&);

};

#endif // MONITOR_HPP_INCLUDED
