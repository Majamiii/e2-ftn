#ifndef MENJAC_HPP_INCLUDED
#define MENJAC_HPP_INCLUDED

using namespace std;

enum TipMenjaca { AUTOMATIK, MANUELNI };

class Menjac{

private:
    int brojBrzina;
    TipMenjaca tip;
public:
    Menjac(){
        tip = MANUELNI;
        brojBrzina = 3;
    }
    Menjac(int v, TipMenjaca tipp){
        brojBrzina = v;
        tip = tipp;
    };
    Menjac(const Menjac& m){
        brojBrzina = m.brojBrzina;
        tip = m.tip;
    };

    bool setBrojBrzina(int i){
        if((i==5)||(i==6)){
            brojBrzina = i;
            cout << "Broj brzina je promenjen."<<endl;
            return true;
        }
        else{
            cout << "Broj brzina ne moze da se promeni."<<endl;
            return false;
        }
    };
    void setTip(TipMenjaca tipp){
        if((tipp == AUTOMATIK ) || (tipp == MANUELNI)){
            tip = tipp;
            cout << "Promenjen tip menjaca"<<endl;
        }
        else {
            cout << "Nepostojeci tip menjaca"<<endl;
        }
    };
    int getBrojBrzina() const{
        return brojBrzina;
    };
    TipMenjaca getTip() const{
        return tip;
    };

    friend void ispisiMenjac(const Menjac&);
};

#endif // MENJAC_HPP_INCLUDED
