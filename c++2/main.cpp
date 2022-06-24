#include <iostream>

using namespace std;
class ch{
    int i;

public:
    int kv(int i1);
};
int ch::kv(int i1)
{
    return i=i1*i1;
}
int main()
{
    ch zz;
    cout <<zz.kv(5)<< endl;
    return 0;
}
