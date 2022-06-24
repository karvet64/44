#include <iostream>

using namespace std;
class Test{
    int num;
public:
    Test(int _num,char c)
    {
        num=_num;
        cout<<num<<" "<<c<<" constructor\n";
    }
    ~Test()
    {
        cout<<num<<" "<<"destructor\n";
    }
    void Print()
    {
        cout<<num<<" "<<"print\n";
    }
};

int main()
{

    Test p(1,'q');
    {
        Test a(22,'u');
        a.Print();
    }
    p.Print();
    cout<<"finish\n";
    return 0;
}
