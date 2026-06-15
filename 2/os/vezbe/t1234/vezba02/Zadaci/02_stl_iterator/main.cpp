/*
Napraviti program koji prihvata proizvoljan broj linija sa standardnog ulaza i zatim ih ispisuje u redosledu kojim su uneti.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> v;
    string s;
    cout<<"Unesite stringove (ctrl-d za kraj):"<<endl;

    while(getline(cin,s)){
        v.push_back(s);
    }

    cout<<"ispis stringova..."<<endl;

    int i=0;
    for(auto it = v.begin(); it != v.end(); it++, i++){
        cout<<v[i]<<endl;
    }

    return 0;
}
