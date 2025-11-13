#include <iostream>

using namespace std;

int main()
{
    int n=0,x=0;
    cout << "Koliko brojeva zelis da saberes?" << endl;
    cin>>n;

    if (n <= 0){
            cout << "Mora se uneti pozitivan broj."<<endl;
            return 1;
    }

    int suma=0;
    for (int i=0; i<n; i++){
        cout << "Unesi " << i+1 <<". broj: ";
        cin>>x;
        suma += x;
    }
    cout<<endl<<"Rezultat je: " << suma<<endl;
    return 0;
}
