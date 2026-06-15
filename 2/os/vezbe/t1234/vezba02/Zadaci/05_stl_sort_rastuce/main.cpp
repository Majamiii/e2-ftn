/*
Uneti 5 celih brojeva sa standardnog ulaza.
Korišćenjem STL algoritma sortirati brojeve u rastućem redosledu.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> niz;
    int x;

    while(cin>>x){
        niz.push_back(x);
    }

    sort(niz.begin(), niz.end());

    for(auto it = niz.begin(); it != niz.end(); it++){
        cout << *it;
    }

    return 0;
}
