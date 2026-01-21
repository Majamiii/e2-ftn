#include <iostream>
#include "trezor.hpp"
#include "dijamant.hpp"

int main()
{
    Trezor<Dijamant,2> trezor;

    Dijamant d1, d2(10,20), d3(40,50), d4(d3);
    cout<<d1<<d2;

    cout<<endl<<trezor.getBrojPopunjenihSefova()<<endl;

    cout<<trezor.izbaciSadrzaj(4)<<endl;
    trezor.ubaciSadrzaj(d1);
    cout<<endl<<trezor.getBrojPopunjenihSefova()<<endl;
    trezor.ubaciSadrzaj(d2);
    trezor.ubaciSadrzaj(d3);
    trezor.ubaciSadrzaj(d4);
    cout<<endl<<"broj: "<<trezor.getBrojPopunjenihSefova()<<endl;

    cout<<trezor.izbaciSadrzaj(4)<<endl;
    cout<<endl<<trezor.getBrojPopunjenihSefova()<<endl;

    cout<<trezor.izbaciSadrzaj(1)<<endl;
    cout<<endl<<trezor.getBrojPopunjenihSefova()<<endl;


    return 0;
}
