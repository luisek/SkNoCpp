#include "unique.hpp"
#include <iostream>

using namespace std;

class A
{
public:
    A()
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
    A(A&&)
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
    A&  operator=(A&& other)
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
        return *this;
    }

    ~A()
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
};

int main()
{
    auto unptr = mpb::makeUnique<int>(12);

    cout <<*unptr <<endl;
    if(unptr)
    {
        cout <<"IS NOT NULL\n";
    }
    auto a = mpb::UniquePtr(new A{});
    auto b = mpb::makeUnique<A>();
    a.reset(b.release());

}