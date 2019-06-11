#include <iostream>
#include <memory>
#include <functional>

using namespace std;


bool compare(const unique_ptr<int>& a, const unique_ptr<int>& b, const unique_ptr<int>& c)
{
    return (*a < *b + *c);
}

struct empty
{}e;

template <typename T>
void print_type_name() {
cout << __PRETTY_FUNCTION__ << endl;
}

int main(int argc, char const *argv[])
{
    unique_ptr<int> a = make_unique<int>(23);
    unique_ptr<int> b = make_unique<int>(223);
    unique_ptr<int> c = make_unique<int>(2223);

    function<bool(const unique_ptr<int>&, const unique_ptr<int>&, const unique_ptr<int>&)> func_obj = compare;
    cout <<compare(a,b,c) <<endl;

    /*auto auto_obj = [](const unique_ptr<int>& a, const unique_ptr<int>&b)
                    {
                        return *a < *b;
                    };
    cout <<auto_obj(a,b) <<'\n';

    //SkNoCpp strona 44

    cout <<"sizeof auto_obj: " <<sizeof(auto_obj) <<'\n';
    cout <<"sizeof empt: " <<sizeof(e) <<endl;
    print_type_name<decltype(auto_obj)>();*/
    if( func_obj)
    {
        cout << "przypisany" << endl;
    }
    cout <<"sizeof func_obj: " <<sizeof(func_obj) <<'\n';
    return 0;
}
