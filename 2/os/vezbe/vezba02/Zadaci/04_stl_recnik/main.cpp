/*
Napraviti jednostavan program za prevođenje reči sa engleskog na srpski jezik.
Nakon unosa reči sa standardnog ulaza, ispisuje se prevod (ukoliko unesena reč postoji u rečniku). 

Uneti 3 engleske reči i njihove prevode na srpski.
*/

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    map<string, string> recnik;

    recnik["hi"] = "cao";
    recnik["thanks"] = "hvala";
    recnik["goodbye"] = "dovidjenja";

    string s;

    for(int i=0;i<3;i++){
        getline(cin, s);
        cout << recnik[s] << endl;
    }

    return 0;
}
