#include <iostream>
using namespace std;

template <typename ... Args>
auto sum(Args ...args)
{
    return (args + ...);
}

int main()
{
    cout <<sum(1,2,3,4,5) <<endl;
    return 0;
}