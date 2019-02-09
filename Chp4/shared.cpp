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
    mpb::sharedPtr<C>* sp =  new mpb::sharedPtr<C>();
    cout <<"after sp\n";
    mpb::sharedPtr<C> sp1(*sp);
    delete sp;
    cout <<"after sp1\n";

    std::shared_ptr<C> spStd = make_shared<C>();

    return 0;
}