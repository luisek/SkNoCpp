#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    Widget2 wi1; //default ctor
    Widget2 wi2{}; //default ctor
    Widget2 wi3();
    Widget2 wi4{{}}; //ctor z initializer list
    Widget2 wi5({}); //wywoła default ctor ale powinien z initializer listą

    return 0;
}