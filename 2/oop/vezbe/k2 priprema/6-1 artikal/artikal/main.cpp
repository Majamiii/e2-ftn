#include "artikal.hpp"

using namespace std;

int Artikal::instanci = 0;

int main()
{
    Artikal a("solja", 1000);
    Artikal b("tanjir", 900);

    cout<<a;
    cout<<b;

    {
        Artikal c("Ukras", 300);
        cout<<c;
    }

    cout<<b;
    // cout<<c;

    return 0;
}
