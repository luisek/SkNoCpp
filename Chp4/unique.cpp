#include "unique.hpp"
#include <iostream>

using namespace std;

struct C
{
    C()
    {
        cout <<__PRETTY_FUNCTION__ <<'\n';
    }

    C(int a)
    {
        cout <<__PRETTY_FUNCTION__ <<'\n';
    }


    ~C()
    {
        cout <<__PRETTY_FUNCTION__ <<'\n';
    }
};

int main(int argc, char* argv[])
{
    mpb::uniquePtr<C> myC(new C());
    mpb::uniquePtr<C> myC2(new C(12));

    mpb::uniquePtr<C> myC3 = mpb::make_unique<C>();
    return 0;
}
