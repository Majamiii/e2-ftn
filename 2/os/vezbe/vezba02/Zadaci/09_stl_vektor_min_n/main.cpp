/*
Napraviti funkciju:
	
vector<int> min_n(const vector<int>& v,	int n);

Ova funkcija vraća vektor koji sadrži n najmanjih elemenata iz vektora v.
Podrazumeva se: v.size()>=n
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> min_n(const vector<int>& v,	int n);

int main()
{
    const vector<int> v = {8,7,6,5,4,3,2,1,9,2,2};
    vector<int> vv = min_n(v,5);

    
    for (auto it = vv.begin(); it != vv.end(); it++){
        cout << *it;
    }
    cout<<endl;

    return 0;
}


vector<int> min_n(const vector<int>& v,	int n){
    vector<int> vv;
    vector<int> v2 = v;
   
    vector<int>::iterator it;
    
    sort(v2.begin(), v2.end());

    for(int i=0;i<n;i++){
        vv.push_back(v2[i]);
    }

    return vv;
}