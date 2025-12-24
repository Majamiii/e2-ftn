#ifndef TREZOR_HPP_INCLUDED
#define TREZOR_HPP_INCLUDED

template <class SADRZAJ, int KAPACITET>
class Trezor{
private:
    SADRZAJ sefovi[KAPACITET];
    bool popunjenost[KAPACITET];
public:
    Trezor(){
        for(int i=0;i<KAPACITET;i++){
            popunjenost[i]=false;
        }
    }

    int getBrojPopunjenihSefova(){
        int brojac=0;
        for(int i=0; i<KAPACITET; i++){
            if(popunjenost[i]){
                brojac++;
            }
        }
        return brojac;
    }

    int ubaciSadrzaj(const SADRZAJ& predmet){
        for(int i=0; i<KAPACITET; i++){
            if(popunjenost[i]==false){
                popunjenost[i]=true;
                sefovi[i] = predmet;
                return i;
            }
        }
        return -1;
    }

    bool izbaciSadrzaj(int sef){
        if(popunjenost[sef]=true){
            popunjenost[sef]=false;
            return true;
        }
        return false;
    }

};

#endif // TREZOR_HPP_INCLUDED
