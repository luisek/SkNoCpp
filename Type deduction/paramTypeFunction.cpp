#include <iostream>
using namespace std;

template <typename T>
void fun1(T param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
}

template <typename T>
void fun2(T& param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
}

void someFun(int a, double d)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
}

int main(int argc, char const *argv[])
{
    fun1(someFun);
    fun2(someFun);
    
    return 0;
}
