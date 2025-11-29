#include <iostream>
using namespace std;
class A
{
public:
int x, y;
public:
A(){x=1; y=2;}

~A(){cout<<y<<x;}

friend ostream& operator<<(ostream &out, const A& a)
{
    out<<a.y<<a.x;
    return out;
}
};

void fun2(A c){c.x=2; c.y=2;}
void fun1(A& a){a.x=1; a.y=1;}

int main()
{
A a;
fun1(a);
cout<<a;
fun2(a);
return 0;
}
