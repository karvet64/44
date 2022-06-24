#include <iostream>

using namespace std;
namespace abcd {
    int i=1;
    float f=3.1413;
}


int main()
{
    cout << "Hello world!"<<abcd::i<<" "<<abcd::f << endl;
    return 0;
}
