#include <iostream>
#include "Monitor.hpp"
#include "Screen.hpp"

using namespace std;

void MeniIspis (Monitor mon1) {
    int izbor, q;
    using namespace std;
    cout << "Meni:" << endl;
    cout << "1. Turn on: "<< endl;
    cout << "2. Turn off: "<< endl;
    cout << "3. Turn out: "<< endl;
    cout << "4. Turn standBy: "<< endl;
    cout << "5. Turn testing: "<< endl;
    cout << "5. Turn repair: "<< endl;
    cout << "6. Turn pojacaj osvetljenost: "<< endl;
    cout << "7. Turn smanji osvetljenost: "<< endl;
    cout << "8. ispisi izvestaj" << endl;
    cout << "UNESI: ----->" << endl;

    cin >> izbor;

    switch (izbor) {
        case 1:
            mon1.turnON();
            q = mon1.turnON();
            if (q){
                cout << "Uspesno izvrseno" <<endl;
            }
            else cout <<" Neuspesna operacija" << endl;
            break;
        case 2:
            mon1.turnOFF();
            q = mon1.turnOFF();
            if (q){
                cout << "Uspesno izvrseno" <<endl;
            }
            else cout <<" Neuspesna operacija" << endl;
            break;
        case 3:
            mon1.turnOUT();
            q = mon1.turnOUT();
            if (q){
                cout << "Uspesno izvrseno" << endl;
            } else cout <<" Neuspesna operacija" << endl;
            break;
        case 4:
            mon1.turnStandBy();
            q = mon1.turnStandBy();
            if (q) {
                cout << "Uspesno izvrseno" <<endl;
            }
            else cout <<" Neuspesna operacija" << endl;
            break;
        case 5:
            mon1.turnTEST();
            q = mon1.turnTEST();
            if (q) {
                cout << "Uspesno izvrseno" <<endl;
            }
            else cout <<" Neuspesna operacija" << endl;
            break;
        case 6:
            mon1.incB();
            q = mon1.incB();
            if (q) {
                cout << "Uspesno izvrseno" <<endl;
            }
            else cout <<" Neuspesna operacija" << endl;
            break;
        case 7:
            mon1.decB();
            q = mon1.decB();
            if (q) {
                cout << "Uspesno izvrseno" <<endl;
            }
            else cout <<" Neuspesna operacija" << endl;
            break;
        case 8:
            mon1.repair();
            if (q) {
                cout << "Uspesno izvrseno" <<endl;
            }
            else cout <<" Neuspesna operacija" << endl;
            break;
        default:
            cout << "nepostojeci/ pogresan unos: " << endl;
            break;
    }

    mon1.printInfo(mon1);
    MonitorStates A = mon1.getMonitorState();
    ScreenStates B = mon1.getScreenStates();

    int c = mon1.getBrightness();

    cout << "****Stanje monitora je: " << endl;

    switch (A) {
    case sON:
        cout << "ukljucen" << endl;
        break;
    case sOFF:
        cout << "iskljucen" << endl;
        break;
    case sOUT:
        cout << "pokvaren" << endl;
        break;
    case sSTANDBY:
        cout << "standby" << endl;
        break;
    case sTEST:
        cout << "TEST" << endl;
        break;
    }

    cout << "****Stanje ekrana je: " << endl;

    switch (B) {
    case ssON:
        cout << "ukljucen" << endl;
        break;
    case ssOFF:
        cout << "iskljucen" << endl;
        break;
     }
    cout << "----Osvetljenost ekrana je: " << c << endl;

    cout<<"--------------------------"<<endl;

    MeniIspis(mon1);

}
int main()
{
    Monitor mon1;
    MeniIspis(mon1);

    return 0;
}
