/*
Napisati konkurentni program koji stvara 2 niti od funkcije f. 
Funkcija f treba da prolazi kroz petlju dužine 10000 elemenata i ispisuje parne ili neparne brojeve (među tih 10000 elemenata).

Ispis parnih ili neparnih brojeva se vrši pozivom funkcija ispisi_parne i ispisi_neparne. 
U funkciji ispisi_parne prvo se pre ispisa zaključava muteks m1, a potom muteks m2. 
U funkciji ispisi_neparne prvo se pre ispisa zaključava muteks m2, a potom muteks m1.

Sva zaključavanja se vrše kroz objekte klase unique_lock.

Pratiti izvršavanje programa.
*/

#include <iostream>
#include <mutex>
#include <vector>
#include <numeric>
#include <thread>
#include <algorithm>

using namespace std;

mutex m1,m2;

void ispisi_parne(int n){

    unique_lock<mutex> ul1(m1);
    unique_lock<mutex> ul2(m2);

    ul1.lock();
    ul2.lock();

    cout<<n;
    cout<<flush;
}

void ispisi_neparne(int n){

    unique_lock<mutex> ul2(m2);
    unique_lock<mutex> ul1(m1);

    ul2.lock();
    ul1.lock();

    cout<<n;
    cout<<flush;
}

void f(){
    for(int i=0;i<10000;i++){
        if(i%2==0){
            ispisi_parne(i);
        }else{
            ispisi_neparne(i);
        }
    }
}


int main(){
    thread nit1(f);
    thread nit2(f);

    nit1.join();
    nit2.join();

    return 0;
}
