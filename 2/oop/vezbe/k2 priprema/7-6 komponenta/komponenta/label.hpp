#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include "component.hpp"

class Label:public Component{
protected:
    DinString text;
    static DinString typeName;
public:
    Label() {
        this->x=0;
        this->y=0;
        this->text="";
    }
    Label(double x, double y, const DinString& d){
        this->x=x;
        this->y=y;
        this->text=d;
    }
    DinString getTypeName(){return typeName;}

    void printComponent(){
        cout<<endl<<getTypeName();
        Component::printComponent();
        cout<<"text: "<<text<<endl;
    }

    DinString getText(){
        return text;
    }
    void setText(DinString t){
        this->text=t;
    }

};

#endif // LABEL_HPP_INCLUDED
