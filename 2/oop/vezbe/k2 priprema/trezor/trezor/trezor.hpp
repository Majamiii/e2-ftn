#ifndef TREZOR_HPP_INCLUDED
#define TREZOR_HPP_INCLUDED

#include <iostream>

template<class SADRZAJ, int KAPACITET>
class Trezor{
private:
    SADRZAJ sefovi[KAPACITET];
    bool popunjenost[KAPACITET];
public:
    Trezor() {
        for(int i=0;i<KAPACITET;i++){
            popunjenost[i]=false;
        }
    }
    int getBrojPopunjenihSefova(){
        int counter=0;
        for(int i=0;i<KAPACITET;i++){
            if(popunjenost[i]){counter++;};
        }
        return counter;
    }
    int ubaciSadrzaj(const SADRZAJ& predmet){
        for(int i=0;i<KAPACITET;i++){
            if(!popunjenost[i]){popunjenost[i]=true;return i;};
        }
        return -1;
    }
    bool izbaciSadrzaj(int i){
        if(popunjenost[i]){
            popunjenost[i]=false;
            return true;
        }else{
            return false;
        }
    }
};
#endif // TREZOR_HPP_INCLUDED
