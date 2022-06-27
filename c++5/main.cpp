#include <iostream>

using namespace std;

struct Tabs{

    Tabs(){cout<<" con\n";}
    ~Tabs(){cout<<"des\n";}

};
int main()
{
    Tabs t;
  Tabs**a;
  a=new Tabs*[5];
  if(a)
  {
       a[0]=&t;
        delete[] a;

  }

    return 0;
}
