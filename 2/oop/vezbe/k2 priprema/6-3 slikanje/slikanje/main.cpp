#include "videokamera.hpp"
#include "telefon2.hpp"

using namespace std;

int Kamera::photoCounter=0;
int VideoKamera::videoCounter=0;

int main()
{
    Kamera cam, cam2(10, 30), cam3(10,5);
    cout<<endl<<"--- testiranje kamere ---"<<endl;

    cout<<cam2.slikaj()<<endl;
    cout<<cam3.slikaj()<<endl;
    cout<<cam2.getPhotoCount();

    cout<<endl<<"--- testiranje videa ---"<<endl;
    VideoKamera video(5, 1000);
    cout<<"pokusaj snimanja videa 1: "<<video.snimaj(3923982)<<endl;
    cout<<"pokusaj snimanja videa 2: "<<video.snimaj(67)<<endl;
    cout<<"broj napravljenih videa: "<<video.getVideoCounter()<<endl;


    cout<<endl<<"--- testiranje telefona ---"<<endl;
    DinString neekibroj = "061 234 56 78";
    Telefon t1, t2(neekibroj);
    cout<<"pozivanje samog sebe: "<<t1.pozovi("000000000")<<endl;
    cout<<"pozivanje nekog drugog: "<<t1.pozovi(neekibroj)<<endl;

    cout<<endl<<endl<<"--- testiranje druge generacije telefona ---"<<endl;
    Telefon2 tel, tel2(neekibroj,10,22);
    cout<<"Pokusaj slikanja telefonom: "<<tel2.slikajSliku()<<endl;
    cout<<"Pokusaj slikanja telefonom: "<<tel2.slikajSliku()<<endl;
    cout<<"Pokusaj slikanja telefonom: "<<tel2.slikajSliku()<<endl;
    cout<<"Pokusaj slikanja telefonom: "<<tel2.slikajSliku()<<endl;

    return 0;
}
