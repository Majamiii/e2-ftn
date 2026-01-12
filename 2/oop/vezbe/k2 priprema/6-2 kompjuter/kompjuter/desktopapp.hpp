#ifndef DESKTOPAPP_HPP_INCLUDED
#define DESKTOPAPP_HPP_INCLUDED

#include "aplikacija.hpp"
#include "kompjuter.hpp"

class DesktopApp : public Aplikacija{
private:
    Kompjuter minSysReq, optimumSysReq;
    static int desktopCount;
public:
    DesktopApp() : Aplikacija("Java", 0) {desktopCount++;}
    DesktopApp(const Kompjuter& m, const Kompjuter& o, const
char* jezik, double vel) : minSysReq(m), optimumSysReq(o), Aplikacija(jezik,vel) {desktopCount++;}
    DesktopApp(const DesktopApp& d) : Aplikacija((Aplikacija)d), minSysReq(d.minSysReq),
optimumSysReq(d.optimumSysReq) {desktopCount++;}

    ~DesktopApp() {desktopCount--;}

    friend ostream& operator<<(ostream& o, const DesktopApp& d){
        o<<(Aplikacija)d;
        o<<"Minimalni sistem: ";
        o<<d.minSysReq<<endl;
        o<<"Optimalni sistem: ";
        o<<d.optimumSysReq<<endl;
        o<<"------------------------"<<endl;
        return o;
    }

    int getCount() {return desktopCount;}

};

/*
Iz klase Application izvesti klasu DesktopApp. Klasa sadrži dodatna polja:
minSysReq (Computer), optimumSysReq (Computer), desktopCount (static, int).
U klasi implementirati:
- Konstruktor bez parametara - polje language postaviti na vrednost
„Java“ direktno u konstruktoru
- Konstruktor sa parametrima (const Computer&, const Computer&, const
char*, double) - prvi parametar za setovanje polja minSysReq, drugi za
setovanje polja optimumSysReq, treći za setovanje polja language, četvrti
za setovanje polja sizeMB
- Konstruktor kopije
- Destruktor
- Redefinisan operator << za ispis vrednosti svih polja koja nisu statička,
uključujući i nasleđena
- Redefinisanu metodu int getCount() const koja vraća broj desktop
aplikacija
*/

#endif // DESKTOPAPP_HPP_INCLUDED
