#include <iostream>

using namespace std;

//template<typename T>
//void fun(ParamType param)
template <typename T>
void fun(T param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
    cout <<typeid(param).name() <<'\n';
}

void example1()
{
    /*
    ParamType nie jest ani wskaźnikiem, ani odwołaniem. //przekazywanie przez wartość

        1. Jeśli expr jest odwołaniem, ignorujemy część referencyjną
        2. Jeśli po zignorowaniu referencyjności w wyrażeniu expr, wyrażenie expr ma włsaność const lub volatile,
        również ignorujemy ten fakt        
    */

   int x = 27;
   const int cx = x;    //cx to const int
   const int& rx = x;   //rx to odwołanie do x jako const int

   fun(x);              //T, param to int
   fun(cx);             //T, param to int
   fun(rx);             //T, param int
}

int main(int argc, char* argv[])
{
    example1();
    const char* const ptr = "Fun with pointers";
    fun(ptr);
    return 0;
}