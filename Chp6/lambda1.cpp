#include <iostream>
#include <functional>
#include <vector>

using namespace std;

using FilterContainer = vector<function<bool(int)>>;
FilterContainer filters;

int computeValue1()
{
    return 2;
}

int computeValue2()
{
    return 1;
}

int computeDivisor(int calc1, int calc2)
{
    return calc1 + calc2;
}

void addDivisorFilter()
{
    auto calc1 = computeValue1();
    auto calc2 = computeValue2();

    auto divisor = computeDivisor(calc1, calc2);

    filters.emplace_back(
        [&](int value){return value % divisor == 0;}
    );
}

int main()
{
    addDivisorFilter();
    for(auto f : filters)
    {
        cout << f(9) <<'\n';
    }
    
    return 0;
}