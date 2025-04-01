#include <iostream>
#include <variant>
#include <string>

using namespace std;

struct PrintVisitor
{
    void operator()(int i )
    {
        cout << "int i: " <<i <<endl;
    }
    void operator()(float f)
    {
        cout <<"float f: " <<f <<endl;
    }
    void operator()(const string& str)
    {
        cout <<"string str: " <<str <<endl;
    }
};

int main()
{
    variant<int, float, string> intFloatString;
    static_assert(variant_size_v<decltype(intFloatString)> == 3);

    visit(PrintVisitor{}, intFloatString);

    cout <<"index = " <<intFloatString.index() <<endl;
    intFloatString = 100.0f;
    cout <<"index = " <<intFloatString.index() <<endl;
    intFloatString = "Hello super world!";
    cout <<"index = " <<intFloatString.index() <<endl;

    if(const auto intPtr = get_if<int>(&intFloatString))
        cout  <<" init: " <<*intPtr <<endl;
    else if( const auto floatPtr = get_if<float>(&intFloatString))
        cout <<" float: " <<*floatPtr <<endl;

    if(holds_alternative<int>(intFloatString))
        cout <<"the value holds an int!\n";
    else if(holds_alternative<float>(intFloatString))
        cout <<"the value holds an int!\n";
    else if(holds_alternative<string>(intFloatString))
        cout <<"the value holds a string!\n";
    try{
        auto f = get<float>(intFloatString);
        cout <<"float: " <<f <<'\n';
    }
    catch(bad_variant_access)
    {
        cout <<"our variant does not hold float at this moment...\n";
    }
    

    return 0;
}
