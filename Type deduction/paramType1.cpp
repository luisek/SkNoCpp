#include <iostream>

using namespace std;

template <typename T>
void paramType()
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
}

template <typename T>
void fun(T& param)
{   
    cout <<__PRETTY_FUNCTION__ <<'\n';
    paramType<decltype(param)>();
}

void example1()
{
    /*
    ParamType to odwołanie uniwersalne lub wskaźnik, ale nie odwołanie uniwersalne.

        1. Jeśli typ wyrażenia exp to odwołanie uniwersalne to zignoruj jego referencyjność
        2. Następnie dopasuj do wzorca typ wyrażenia expr wzdlędem ParamType, aby wyznaczyć T.
    */

   int x = 27;
   const int cx = x;    //cx to const int
   const int& rx = x;   //rx to odwołanie do x jako const int

   fun(x);              //T to int, typ param to int&
   fun(cx);             //T to const int, param to const int&
   fun(rx);             //T to const int, param to const int&; referencyjność rx jest ignorowana
}

//template<typename T>
//void fun(ParamType param)
template <typename T>
void funC(const T& param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
     paramType<decltype(param)>();
}

void example1C()
{
    /*
    ParamType to odwołanie uniwersalne lub wskaźnik, ale nie odwołanie uniwersalne.

        1. Jeśli typ wyrażenia exp to odwołanie uniwersalne to zignoruj jego referencyjność
        2. Następnie dopasuj do wzorca typ wyrażenia expr wzdlędem ParamType, aby wyznaczyć T.
    */
   
   int x = 27;
   const int cx = x;    //cx to const int
   const int& rx = x;   //rx to odwołanie do x jako const int

   funC(x);              //T to int, typ param to const int&
   funC(cx);             //T to int, param to const int&
   funC(rx);             //T to int, param to const int&; referencyjność rx jest ignorowana
}

//template<typename T>
//void fun(ParamType param)
template <typename T>
void funP(T* param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
    paramType<decltype(param)>();
}
void example1P()
{
    /*
    ParamType to odwołanie uniwersalne lub wskaźnik, ale nie odwołanie uniwersalne.

        1. Jeśli typ wyrażenia exp to odwołanie uniwersalne to zignoruj jego referencyjność
        2. Następnie dopasuj do wzorca typ wyrażenia expr wzdlędem ParamType, aby wyznaczyć T.
    */
   
   int x = 27;
   const int* cx = &x;    //cx to const int
   
   funP(&x);             //T to int, typ param to int*
   funP(cx);             //T to const int, param to const int*
}

//template<typename T>
//void fun(ParamType param)
template <typename T>
void funCP(const T* param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
    paramType<decltype(param)>();
}
void example1CP()
{
    /*
    ParamType to odwołanie uniwersalne lub wskaźnik, ale nie odwołanie uniwersalne.

        1. Jeśli typ wyrażenia exp to odwołanie uniwersalne to zignoruj jego referencyjność
        2. Następnie dopasuj do wzorca typ wyrażenia expr wzdlędem ParamType, aby wyznaczyć T.
    */
   
   int x = 27;
   const int* cx = &x;    //cx to const int
   
   funCP(&x);             //T to int, typ param to const int*
   funCP(cx);             //T to int, param to const int*
}

//f(expr)
int main(int argc, char* argv[])
{
    example1();
    example1C();
    example1P();
    example1CP();
    
    return 0;
}