#ifndef PANEL_HPP_INCLUDED
#define PANEL_HPP_INCLUDED

#include "component.hpp"
#include "list.hpp"

class Panel:public Component{
private:
    static DinString typeName;
    int capacity;
    List<Component*> components;
public:
    Panel() {
        this->x=0;
        this->y=0;
        this->capacity=10;
    }
    Panel(const Panel& p){
        this->x = p.x;
        this->y=p.y;
        this->capacity=p.capacity;
    }

    DinString getTypeName(){
        return typeName;
    }

    void printComponent(){
        cout<<endl<<getTypeName()<<endl;
        Component::printComponent();
        cout<<"Sadrzaj liste sa komponentama: ";
        Component* c;
        for(int i=1;i<=components.size();i++){
            components.read(i, c);
            c->printComponent();
        }
    }
    int getCapacity(){return capacity;}
    void setCapacity(int c){
        this->capacity = c;
    }
    bool addComponent(Component& comp){
        Component* k = &comp;
        if(components.size() < capacity){
            components.add(components.size()+1, k);
            return true;
        }else{
        return false;}
    }
    bool removeComponent(int idx){
        return components.remove(idx);
    }
};

#endif // PANEL_HPP_INCLUDED
