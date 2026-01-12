#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include <iostream>
#include "dinstring.hpp"
#include "list.hpp"

class Component{
protected:
    double x,y;
public:
    double getX() {return x;}
    double getY() {return y;}

    virtual void printComponent(){
        cout<<"x: "<<x<<endl;
        cout<<"y: "<<y<<endl;
    }
    virtual DinString getTypeName() =0;

};

#endif // COMPONENT_HPP_INCLUDED
