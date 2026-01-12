#ifndef ZICARA_HPP_INCLUDED
#define ZICARA_HPP_INCLUDED

#include "putnikdete.hpp"

enum StanjeZicare{OTVORENA,ZATVORENA};

template <VrstaKarte SEZONA, int BROJ_SEDISTA, int INTERVAL>
class Zicara{
private:
    List<Putnik*> putnici;
    StanjeZicare stanje;
    int ukupnoVoznji,ukupnoMinuta;
public:
    Zicara() : stanje(ZATVORENA) {};

    void otvori(){
        stanje=OTVORENA;
        ukupnoMinuta=0;
        ukupnoVoznji=0;
    }
    void zatvori(){
        stanje=ZATVORENA;
        putnici.clear();
    }
    bool dodajPutnika(Putnik* p){
        if(p->getVrsta() != SEZONA){
            return false;
        }else{
            Putnik* temp;
            for(int i=1;i<=putnici.size();i++){
                putnici.read(i,temp);
                if(p->getMb() == temp->getMb()){
                    return false;
                }
            }
            return putnici.add(putnici.size()+1, p);
        }
    }

    int brojPutnika() const{
        return putnici.size();
    }

    bool preveziTuru(){
        if ((stanje==ZATVORENA) or (brojPutnika()==0)){
            return false;
        }
        else if(stanje==OTVORENA){
            int n = ( BROJ_SEDISTA>brojPutnika() ? brojPutnika() : BROJ_SEDISTA );
            for(int i=1;i<=n;i++){
                putnici.remove(i);
            }
            ukupnoVoznji+=n;
            ukupnoMinuta+=INTERVAL;
        }
        return true;
    }

    friend ostream& operator<<(ostream& os, const Zicara<SEZONA,BROJ_SEDISTA,INTERVAL>& z){
        os<<endl<<"-------- ZICARA --------"<<endl;
        os<<"Sezona: ";
        switch (SEZONA){
        case(LETO):cout<<"letnja"<<endl;break;
        case(SKI):cout<<"ski"<<endl;break;
        case(SKI_OPENING):cout<<"ski opening"<<endl;break;
        }
        os<<"Broj sedista i trajanje: "<<BROJ_SEDISTA<<", "<<INTERVAL<<endl;
        if(z.stanje==OTVORENA){
            os<<"Stanje: otvorena"<<endl;
        }else{os<<"Stanje: zatvorena"<<endl;}
        os<<"Ukupan broj voznji i radno vreme: "<<z.ukupnoVoznji<<", "<<z.ukupnoMinuta/60<<endl;
        os<<"Broj putnika u redu: "<<z.brojPutnika()<<endl;
        if(z.brojPutnika()>0){
            Putnik* temp;
            for(int i=1;i<=z.brojPutnika();i++){
                z.putnici.read(i,temp);
                os<<*temp;
            }
        }
        return os;
    }
};

/*

-   preklopiti   operator   ispisa   <<   -   tako   da  ispisuje  sezonu,  broj  sedišta  na  žičari,  trajanje
 jedne   vožnje,   stanje,   ukupan   broj   vožnji,   ukupno   radno   vreme   žicare   u   satima,   broj
 putnika  u  redu  i  u  slučaju  da  je  broj  putnika  u  redu  veći  od  nule,  ispisati  listu  svih  putnika
 koji čekaju u redu.

*/

#endif // ZICARA_HPP_INCLUDED
