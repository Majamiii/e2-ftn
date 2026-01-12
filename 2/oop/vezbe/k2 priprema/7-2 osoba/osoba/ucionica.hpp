#ifndef UCIONICA_HPP_INCLUDED
#define UCIONICA_HPP_INCLUDED

#include "list.hpp"

class Ucionica{

private:
    DinString naziv;
    int kapacitet;
    List<Osoba> lista;
public:
    Ucionica(const DinString& n, int k) : naziv(n),kapacitet(k) {}
    bool dodaj(const Osoba& o){
        if(lista.size() < kapacitet){
            return lista.add(lista.size()+1, o);
        }
        return false;
    }
    void ispis(){
        if(lista.size()==0){
            cout<<endl<<"nema nikoga u ucionici"<<endl;
        }
        else{
            Osoba o;
            cout<<"u ucionici su:"<<endl;
            for(int i=1;i<lista.size()+1;i++){
                lista.read(i,o);
                o.ispis();
            }
        }
    }

};

#endif // UCIONICA_HPP_INCLUDED
