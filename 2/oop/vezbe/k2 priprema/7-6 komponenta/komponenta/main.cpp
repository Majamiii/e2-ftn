#include "label.hpp"
#include "checkbox.hpp"
#include "panel.hpp"

using namespace std;

DinString CheckBox::typeName = "DinString";
DinString Label::typeName = "Label";
DinString Panel::typeName = "Panel";

int main()
{

    CheckBox cb1,cb2(3,2,true);
    cb2.printComponent();

    const DinString natpis="cao cao";
    Label lbl1, lbl2(7,6,natpis);
    lbl1.printComponent();

    // ---------------
    Panel p1;
    p1.printComponent();
    cout << endl << endl;

    p1.setCapacity(3);
    p1.printComponent();
    cout << endl << endl;

    p1.addComponent(cb1);
    p1.addComponent(cb2);
    p1.addComponent(lbl1);

    p1.printComponent();
    cout << endl << endl;

    if (!p1.addComponent(lbl2))
        cout << "Greska prilikom dodavanja" << endl << endl;

    p1.removeComponent(1);
    p1.printComponent();
    cout << endl << endl;

    Panel p2(p1);
    p2.printComponent();
    cout << endl << endl;

    return 0;
}
