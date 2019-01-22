#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

template <typename T>
void fun(T& param)
{
    cout <<__PRETTY_FUNCTION__ <<'\n';
    cout <<"T = " <<type_id_with_cvr<T>().pretty_name() <<'\n';
    cout <<"param = " <<type_id_with_cvr<decltype(param)>().pretty_name() <<'\n';
}

int main(int argc, char const *argv[])
{
    const char name[] = "Jan AP Kaczmarek";
    const char* ptrToName = name;

    fun(ptrToName);
    return 0;
}
