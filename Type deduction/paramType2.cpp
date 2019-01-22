#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

//template<typename T>
//void fun(ParamType param)
template <typename T>
void fun(T&& param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
    cout <<"T = " <<type_id_with_cvr<T>().pretty_name() <<'\n';
    cout <<"param = " <<type_id_with_cvr<decltype(param)>().pretty_name() <<'\n';
}

void example1()
{
    /*
    ParamType jest odwołaniem uniwersalnym.

        1. Jeżeli expr to l-wartość, zarówno T, jaki ParamType są dedukowane jako odwołania do l-wartości.
            Jest to jedyna sytuacja dotycząca dedukcji typów szablonu, gdzie T jest dedukowane jako odwołanie.
            Chociaż ParamType jest deklarowany przy użyciu składni dla odwołania do r-wartości, jego deukowanym typem
            jest odwołanie do l-wartości.

        2. Jeśli expr to odwołanie do r-wartości to stosowanie są "normalne reguły":
            2.1. Jeśli typ wyrażenia exp to odwołanie uniwersalne to zignoruj jego referencyjność
            2.2. Następnie dopasuj do wzorca typ wyrażenia expr wzdlędem ParamType, aby wyznaczyć T.
    */

   int x = 27;
   const int cx = x;    //cx to const int
   const int& rx = x;   //rx to odwołanie do x jako const int

   fun(x);              //x to l-wartość, T to int&, typ param to int&
   cout <<endl;
   fun(cx);             //cx to l-wartość, T to const int&, param to const int&
   cout <<endl;
   fun(rx);             //rx to l-wartość, T to const int&, param to const int&;
   cout <<endl;
   fun(27);             //27 to r-wartość, T to int, param to int&&
}

//f(expr)
int main(int argc, char* argv[])
{

    example1();
    
    return 0;
}