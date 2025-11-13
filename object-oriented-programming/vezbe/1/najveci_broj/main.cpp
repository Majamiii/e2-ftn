#include <iostream>

using namespace std;

int main()
{
    cout << "Upisuj brojeve od kojih cemo traziti najveci."<<endl;
    cout << "Upis se zavrsava unosom nule."<<endl;

    int x=1;
    int najveci = -100000000;

    while (x != 0){
        cin>>x;
        if (x>najveci){
            najveci = x;
        }
    }

    cout << "Najveci broj je "<< najveci<<endl;

    return 0;
}
