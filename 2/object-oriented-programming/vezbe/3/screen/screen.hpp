#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#include <iostream>
using namespace std;

#define KORAK 2
#define D_GRANICA 0
#define G_GRANICA 20

enum ScreenStates {ssON, ssOFF};

class Screen{
private:
    ScreenStates state;
    int brightness;
public:
    Screen(){
        state=ssOFF;
        brightness=0;
    }

    bool incB(){
        if(state == ssON){
            if(brightness+KORAK>G_GRANICA){
                cout<<"Nemoguce jos povecati osvetljenje."<<endl;
                return 0;
            }
            else{
                cout<<"Osvetljenje je povecano za 1 korak."<<endl;
                brightness += KORAK;
                return 1;
            }
        }
        else{
            cout<<"Ekran nije ukljucen, nemoguce je povecati osvetljenje."<<endl;
            return 0;
        }
    }

    bool decB(){
        if(state == ssON){
            if(brightness-KORAK<D_GRANICA){
                cout<<"Nemoguce jos smanjiti osvetljenje."<<endl;
                return 0;
            }
            else{
                cout<<"Osvetljenje je smanjeno za 1 korak."<<endl;
                brightness -= KORAK;
                return 1;
            }
        }
        else{
            cout<<"Ekran nije ukljucen, nemoguce je smanjiti osvetljenje."<<endl;
            return 0;
        }
    }

    void setState(ScreenStates s){
        state = s;
    }

    ScreenStates getState() const {
        return state;
    }
    int getBrightness() const{
        return brightness;
    }
};

#endif // SCREEN_HPP_INCLUDED
