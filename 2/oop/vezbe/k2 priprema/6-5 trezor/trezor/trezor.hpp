#ifndef TREZOR_HPP_INCLUDED
#define TREZOR_HPP_INCLUDED

#include <iostream>

template<class SADRZAJ, int kapacitet>
class Trezor{

private:
    SADRZAJ sef[kapacitet];
    bool popunjenost[kapacitet];
public:
    Trezor() {
        for(int i=0;i<kapacitet;i++){
            popunjenost[i]=false;
        }
    }

    int getBrojPopunjenihSefova(){
        int n=0;
        for(int i=0;i<kapacitet;i++){
            if(popunjenost[i]==true){
                n++;
            }
        }
        return n;
    }

    int ubaciSadrzaj(const SADRZAJ& predmet){
        for(int i=0;i<kapacitet;i++){
            if(popunjenost[i]==false){
                popunjenost[i]=true;
                sef[i]=predmet;
                return i;
            }
        }
        return -1;
    }

    bool izbaciSadrzaj(int i){
        if(popunjenost[i]==true){
            popunjenost[i]=false;
            return true;
        }
        return false;
    }

};

#endif // TREZOR_HPP_INCLUDED
