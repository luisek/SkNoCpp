#include <iostream>
#include <boost/type_index.hpp>
#include <vector>

using namespace std;
using boost::typeindex::type_id_with_cvr;

auto validUser(vector<int>& _vect, int index)
{
    cout <<__PRETTY_FUNCTION__ <<endl;
    return _vect[index];
}

decltype(auto) validUser2(vector<int>& _vect, int index)
{
    cout <<__PRETTY_FUNCTION__ <<endl;
    return _vect[index];
}

decltype(auto) validUser3(vector<int>&& _vect, int index)
{
    cout <<__PRETTY_FUNCTION__ <<endl;
    return forward<vector<int>>(_vect)[index];
}

int main(int argc, char const *argv[])
{
    vector<int> arr{1,2,3,4,5,6};

    cout <<"validUser = " <<type_id_with_cvr<decltype(validUser(arr,2))>().pretty_name() <<'\n';
    for(const auto& a : arr)
    {
        cout <<a <<", ";
    }
    cout <<endl;
    validUser(arr,2);// = 10; <- to się nie skompiluje; lvalue required as left operand of assignment zwracamy lvalue

    cout <<"validUser2 = " <<type_id_with_cvr<decltype(validUser2(arr,2))>().pretty_name() <<'\n';
    for(const auto& a : arr)
    {
        cout <<a <<", ";
    }
    validUser2(arr,2) = 10;
    cout <<"After validUser2 call\n";
    for(const auto& a : arr)
    {
        cout <<a <<", ";
    }
    cout <<endl;
    
    cout <<"validUser3 = " <<type_id_with_cvr<decltype(validUser3({1,2,3,4,5,6},2))>().pretty_name() <<'\n';
    for(const auto& a : arr)
    {
        cout <<a <<", ";
    }
    cout <<endl;
    validUser3(move(arr),3) = 10;
    cout <<endl;
    return 0;
}
