#include "desktopapp.hpp"
#include "androidapp.hpp"

#include "androidapp.hpp"
#include "desktopapp.hpp"

using namespace std;

int Aplikacija::appCount=0;
int AndroidApp::androidCount=0;
int DesktopApp::desktopCount=0;

int main()
{
    Kompjuter k1, k2(2,128,"amd","ubuntu"), k3(k2);
    cout<<k3;

    cout<<endl<<"Kreiranje aplikacija a1 i a2..."<<endl;

    Aplikacija a1, a2("asembler", 50);
    cout<<a1;
    {
        Aplikacija a3(a2);
        cout<<a3;
        cout<<a3.getCount()<<endl;
    }
    cout<<a2.getCount()<<endl;

    cout<<endl<<"-------------------------"<<endl<<"kreiranje android aplikacija..."<<endl;
    AndroidApp an2(650);
    cout<<an2;
    cout<<an2.getCount();
    AndroidApp an1;
    cout<<endl<<an2.getCount();


    cout<<endl<<"------------------------"<<endl<<"kreiranje desktop aplikacije..."<<endl;
    DesktopApp d1(k1,k2,"pajton",1500);
    cout<<d1;

    return 0;
}
