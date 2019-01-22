#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

template <typename T>
void fun1(T param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
    cout <<"T = " <<type_id_with_cvr<T>().pretty_name() <<'\n';
    cout <<"param = " <<type_id_with_cvr<decltype(param)>().pretty_name() <<'\n';
}

template <typename T>
void fun2(T& param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
    cout <<"T = " <<type_id_with_cvr<T>().pretty_name() <<'\n';
    cout <<"param = " <<type_id_with_cvr<decltype(param)>().pretty_name() <<'\n';
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
