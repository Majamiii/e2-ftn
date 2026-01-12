#ifndef ANDROIDAPP_HPP_INCLUDED
#define ANDROIDAPP_HPP_INCLUDED

#include "aplikacija.hpp"

class AndroidApp : public Aplikacija {
private:
    static int androidCount;
public:
    AndroidApp() : Aplikacija() {androidCount++;}
    AndroidApp(double velicina) : Aplikacija("java",velicina){androidCount++;};
    AndroidApp(const AndroidApp& a) : Aplikacija((Aplikacija)a) {author = a.author;}
    ~AndroidApp(){androidCount--;}

    friend ostream& operator<<(ostream& os, const AndroidApp& app){
        os<<endl<<"--- android aplikacija ---"<<endl;
        os<<"jezik i autor: "<<app.language<<" ,  "<<app.author<<endl;
        os<<"velicina: "<<app.sizeMB<<endl;
        return os;
    }

    int getCount(){
        return androidCount;
    }

};

#endif // ANDROIDAPP_HPP_INCLUDED
