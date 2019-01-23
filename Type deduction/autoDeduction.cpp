#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;


int main(int argc, char const *argv[])
{
    int x = 12;
    int& rx = x;
    const int& cx = x;

    auto a1 = x;
    cout <<"a1 = " <<type_id_with_cvr<decltype(a1)>().pretty_name() <<'\n';
    auto a2 = rx;
    cout <<"a2 = " <<type_id_with_cvr<decltype(a2)>().pretty_name() <<'\n';
    auto a3 = cx;
    cout <<"a3 = " <<type_id_with_cvr<decltype(a3)>().pretty_name() <<'\n';

    auto& b1 = x;
    cout <<"b1 = " <<type_id_with_cvr<decltype(b1)>().pretty_name() <<'\n';
    auto& b2 = rx;
    cout <<"b2 = " <<type_id_with_cvr<decltype(b2)>().pretty_name() <<'\n';
    auto& b3 = cx; //tutaj jest dość istotne mimo, że przyisujemy do auto& b3 to jeśli inicjalizator jest const to
    //przechodzi on do b3 i b3 jest typu const int&
    cout <<"b3 = " <<type_id_with_cvr<decltype(b3)>().pretty_name() <<'\n';

    const auto& c1 = x;
    cout <<"c1 = " <<type_id_with_cvr<decltype(c1)>().pretty_name() <<'\n';
    const auto& c2 = rx;
    cout <<"c2 = " <<type_id_with_cvr<decltype(c2)>().pretty_name() <<'\n';
    const auto& c3 = cx;
    cout <<"c3 = " <<type_id_with_cvr<decltype(c3)>().pretty_name() <<'\n';

    return 0;
}
