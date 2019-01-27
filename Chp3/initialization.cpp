#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Examp
{
public:
    /*Examp(int _a, string _name) : a{_a}, name{_name}
    {
    }*/
    ~Examp()
    {
        cout <<a <<' ' <<name <<endl;
    }
private:
    int a{10};
    string name{"empty examp"} ;
};

class Widget
{
public:

    Widget(int i, bool b) : value{i}, status{b}
    {
        cout << __PRETTY_FUNCTION__ <<endl;
    }
    Widget(int i, double d) : value{i}, dvalue{d}, status{false}
    {
        cout << __PRETTY_FUNCTION__ <<endl;
    }
    Widget(initializer_list<long double> il) : vt{il}
    {
        cout << __PRETTY_FUNCTION__ <<endl;
    }

private:
    bool status;
    int value;
    double dvalue;
    vector<long double> vt;
};

class Widget2
{
public:
    Widget2()
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
    Widget2(initializer_list<int> il) : vi{il}
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }

private:
    vector<int> vi;
};

int main()
{
    Examp ex{};
    float a{1.2f}, b{1.4f}, c{3.2f};
    int sum{a+b+c}; //wrn podczas kompilacji o cascie z float na int i o mozliwej utracie precyzji
    cout <<"sum:" <<sum <<endl;
    int sum2(a+b+c); // <=  bez informacji cast na int funkcja czy zmienna ?
    cout <<"sum2:" <<sum2 <<endl;

    Widget w1(10, true);
    Widget w2{10, true};//gdy dodamy ctor z initializer_list to wywołanie jest castowane na wywołanie ctora z initializer list
    Widget w3(10, 5.0);
    Widget w4{10, 5.0};//gdy dodamy ctor z initializer_list to wywołanie jest castowane na wywołanie ctora z initializer list

    Widget2 wi1; //default ctor
    Widget2 wi2{}; //default ctor
    Widget2 wi3();
    Widget2 wi4{{}}; //ctor z initializer list
    Widget2 wi5({}); //wywoła default ctor ale powinien z initializer listą

    return 0;
}