#include <iostream>

using namespace std;



int main(int argc, char* argv[])
{
    auto SimpleLambda = [](int n) {return n;};
    static_assert(SimpleLambda(3) == 3, "staticAssert bum!");

    /*
    To się nie skompiluje. Wywołujemy w constexpr lambda dynaminczą alokacje pamięci
    lambda aby była constexpr musi zawierać jedynie wywołania funkcji które są constexpr

    auto FaultyLeakyLambda = [](int n) constexpr
    {
        int* p = new int(10);
        return n+(*p);
    };
    */
    return 0;
}