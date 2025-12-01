#include "monitor.hpp"

void printInfo(const Monitor& m){
    cout<<endl<<"----------------"<<endl;
    cout<<"EKRAN"<<endl;
    cout<<"Osvetljenje: "<<m.screen.getBrightness()<<endl;
    cout<<"Stanje: ";
    ScreenStates stanje = m.screen.getState();

    switch(stanje){
        case ssOFF : cout<<"OFF"<<endl;break;
        case ssON: cout<<"ON"<<endl;break;
    }
    cout<<"----------------"<<endl;

    cout<<"MONITOR"<<endl;
    cout<<"Stanje: ";
    MonitorStates mstanje = m.getMonitorState();
    switch(mstanje){
        case sON : cout<<"ON"<<endl;break;
        case sOFF : cout<<"OFF"<<endl;break;
        case sSTANDBY : cout<<"StandBy"<<endl;break;
        case sOUT : cout<<"Out"<<endl;break;
        case sTEST : cout<<"Test"<<endl;break;
    }
    cout<<"----------------"<<endl<<endl;
};

int main()
{
    Screen s;
    cout<<"screen brightness: "<<s.getBrightness()<<endl;
    s.incB();
    s.setState(ssON);
    cout << s.getState()<<endl;
    s.incB();
    cout<<"screen brightness: "<<s.getBrightness()<<endl;
    s.decB();
    cout<<"screen brightness: "<<s.getBrightness()<<endl;
    s.decB();

    Monitor m;

    m.turnOff();
    printInfo(m);
    m.turnOn();
    m.turnStandBy();
    m.turnTest();

    // TODO: dodati da je npr x=m.turnOn i onda cases da li je error ili nije

    printInfo(m);
    return 0;
}
