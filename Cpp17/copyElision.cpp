#include <iostream>
using namespace std;

struct Test
{
    Test()
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
    Test(const Test&)
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
    Test(Test&&)
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
    ~Test()
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
};

Test Create()
{
    cout <<__PRETTY_FUNCTION__ <<endl;
    return Test();
}

int main()
{
    cout <<"main call create\n";
    auto n = Create();
    cout <<"main end\n";
    return 0;
}

