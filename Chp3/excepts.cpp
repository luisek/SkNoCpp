#include <iostream>
#include <vector>
using namespace std;
/*
int f_throw(int x) throw()
{
    cout <<"Receive x = " <<x <<endl;
    throw runtime_error("fuck fuck");
    return x;
}*/

void fill_vc(vector<int>& _v)
{
    for(int i =0; i < _v.size() -1; ++i)
    {
        _v.push_back( i / 2);
    }
}

int f_noexcept(int x) noexcept
{
    vector<int> _vc;
    _vc.reserve(10*100*1000);
    fill_vc(_vc); 
    return x;
}

int f_without(int x)
{
    vector<int> _vc;
    _vc.reserve(10*100*1000);
    fill_vc(_vc);
    return x;
}


int main(int argc, char* argv[])
{
    auto i = 10 * 100 * 1000;
    for(auto ai = 0; ai < i; ++ai)
    {
        f_without(ai);
        //f_noexcept(ai);
    }
    return 0;
}