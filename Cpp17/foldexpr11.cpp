#include <iostream>
using namespace std;


auto SumCpp11()
{
    return 0;
}

template<typename T1, typename ...T>
auto SumCpp11(T1 s, T... ts)
{
    return s + SumCpp11(ts...);
}

int main()
{
    cout <<SumCpp11(1,2,3,4,5) <<endl;
}