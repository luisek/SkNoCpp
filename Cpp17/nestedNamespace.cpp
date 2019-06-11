#include <iostream>
using namespace std;

namespace mpb::MyClassImplementation
{
    class MyClass
    {
    public:
        MyClass()
        {
            cout <<__PRETTY_FUNCTION__ <<endl;
        }
    };
}

int main()
{
    mpb::MyClassImplementation::MyClass myClass;
    return 0;
}