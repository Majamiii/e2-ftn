#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

#include "component.hpp"


class CheckBox:public Component{
private:
    bool pressed;
    static DinString typeName;
public:
    CheckBox(double xx=0, double yy=0, bool p=false) {
        this->x=xx;
        this->y=yy;
        this->pressed=p;
    }

    DinString getTypeName(){
        return typeName;
    }

    void printComponent(){
        cout<<getTypeName()<<endl;
        Component::printComponent();
        cout<<"pritisnuto: "<< ( pressed==true ? "da" : "ne" )<<endl;
    }

    bool getPressed(){return pressed;}
    void setPressed(bool setp){pressed=setp;}

};

#endif // CHECKBOX_HPP_INCLUDED
