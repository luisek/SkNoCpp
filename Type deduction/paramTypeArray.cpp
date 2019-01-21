#include <iostream>
using namespace std;

template <typename T>
void fun(T& param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
}

int main(int argc, char const *argv[])
{
    const char name[] = "Jan AP Kaczmarek";
    const char* ptrToName = name;

    fun(ptrToName);
    return 0;
}
