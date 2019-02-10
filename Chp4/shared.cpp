#include "shared.hpp"
#include <iostream>
#include <memory>

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
    mpb::sharedPtr<C> emptyShared;

    mpb::sharedPtr<C> valueC(new C(12));

    emptyShared = valueC;
    mpb::sharedPtr<C> newC(valueC);

    mpb::sharedPtr<C> witValue(C(12));

    auto newSharedValue(move(witValue));

    auto new2SharedValue = move(newSharedValue);

    return 0;
}