#ifndef APLIKACIJA_HPP_INCLUDED
#define APLIKACIJA_HPP_INCLUDED

#include "kompjuter.hpp"  //zbog dinstring
/*
Napisati klasu Application. Klasa sadrži polja: language (DinString), sizeMB
(double), author (DinString), appCount (static, int). U klasi implementirati:
- Konstruktor bez parametara
- Konstruktor sa parametrima (const char*, double) - prvi parametar za
setovanje polja language, drugi za setovanje polja sizeMB, a polje author
postaviti na naziv kompanije direktno u konstruktoru
- Konstruktor kopije
- Destruktor
- Operator << za ispis vrednosti svih polja koja nisu statička
- Metodu int getCount() const koja vraća broj aplikacij
*/

class Aplikacija{
protected:
    DinString language;
    double sizeMB;
    DinString author;
    static int appCount;
public:
    Aplikacija() : language("c++"),sizeMB(10),author("") {appCount++;}
    Aplikacija(const char* lang, double s) : language(lang), sizeMB(s), author("GaMiami") {appCount++;}
    Aplikacija(const Aplikacija& app) : language(app.language), sizeMB(app.sizeMB),author(app.author) {appCount++;}
    ~Aplikacija(){appCount--;};

    friend ostream& operator<<(ostream& os, const Aplikacija& app){
        os<<endl<<"--- aplikacija ---"<<endl;
        os<<"jezik i autor: "<<app.language<<" ,  "<<app.author<<endl;
        os<<"velicina: "<<app.sizeMB<<endl;
        return os;
    }
    int getCount() const{
        return appCount;
    }

};

#endif // APLIKACIJA_HPP_INCLUDED
