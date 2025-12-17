#ifndef PRAVOUGAONIK_H_INCLUDED
#define PRAVOUGAONIK_H_INCLUDED

class Pravougaonik{

private:
    int a;
    int b;
public:
    Pravougaonik(int aa=1, int bb=1){
        a=aa;
        b=bb;
    }
    double getA() const{
        return a;
    }
    double getB() const {
        return b;
    }
    double getO() const{
        return 2*a+2*b;
    }
    double getP() const{
        return a*b;
    }

};

#endif // PRAVOUGAONIK_H_INCLUDED
