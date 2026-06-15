/* 
Napraviti funkciju:
	
vector<int> min(const vector<int>& a, const vector<int>& b);

Ova funkcija vraća vektor koji sadrži minimume korespodentnih elemenata vektora a i b.
Npr: r[0]=min(a[0],b[0]), r[1]=...
Podrazumeva se: a.size()==b.size()
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> min(const vector<int>& a, const vector<int>& b);

int main()
{
    const vector<int> a = {8,7,6,5,4,3,2,1};
    const vector<int> b = {1,2,3,4,5,6,7,8};

    const vector<int> v = min(a,b);

    for (auto it = v.begin(); it != v.end(); it++){
        cout << *it;
    }
    cout<<endl;

    return 0;
}


vector<int> min(const vector<int>& a, const vector<int>& b){
    vector<int> v;
    
    vector<int>::const_iterator ita;
    vector<int>::const_iterator itb;
    
    for(ita = a.begin(), itb = b.begin(); ita != a.end() && itb != b.end(); ita++, itb++){
        v.push_back(min(*ita, *itb));
    }
    return v;
}