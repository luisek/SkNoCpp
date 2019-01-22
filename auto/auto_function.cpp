#include <iostream>
#include <memory>
#include <functional>

using namespace std;


bool compare(const unique_ptr<int>& a, const unique_ptr<int>& b)
{
    return *a < *b;
}

int main(int argc, char const *argv[])
{
    unique_ptr<int> a = make_unique<int>(23);
    unique_ptr<int> b = make_unique<int>(223);

    function<bool(const unique_ptr<int>&, const unique_ptr<int>&)> func_obj = compare;
    cout <<compare(a,b) <<endl;

    auto auto_obj = [](const unique_ptr<int>& a, const unique_ptr<int>&b)
                    {
                        return *a < *b;
                    };
    cout <<auto_obj(a,b) <<'\n';

    //SkNoCpp strona 44
    cout <<"sizeof func_obj: " <<sizeof(func_obj) <<'\n';
    cout <<"sizeof auto_obj: " <<sizeof(auto_obj) <<'\n';    
    return 0;
}
