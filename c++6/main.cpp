#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;
class TPoint{
    int x,y;
public:
    void Init(int _x,int _y){x=_x;y=_y;}
    void Show(){cout<<x<<","<<y<<endl;}
};

int main()
{
 int len=10;
 TPoint *mas=new TPoint[len];
 if(mas)
 {
          for(int i=0;i<len;i++)
     {
         mas[i].Init(rand(),rand());
         mas[i].Show();
     }
     delete[]mas;
 }

    return 0;
}
