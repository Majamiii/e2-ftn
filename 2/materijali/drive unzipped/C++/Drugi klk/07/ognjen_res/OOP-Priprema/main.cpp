#include <iostream>
using namespace std;

class A
{
public:
int x;
A(int xx){x=xx;}
A& operator++()
{
x++;
A temp(++x);
temp.x = ++x;
return *this;
}
A operator++(int i)
{
A temp(x);
x++;
cout<<"B";
return temp;
}
};

int main()
{
A a(6);
a;
return 0;
}
