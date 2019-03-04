#include <iostream>
#include <vector>
using namespace std;

/*
template <typename T>
void fwd(T&& param)
{
    f(forward<T>(param));
}
*/

class Widget
{
public:
    const static size_t MinVals = 28;
};
const size_t Widget::MinVals;

void f(const vector<int>& vs)
{
    cout <<__PRETTY_FUNCTION__ <<endl;
}

void f(size_t val)
{
    cout <<__PRETTY_FUNCTION__ <<endl;
}

template <typename... Ts>
void fwd(Ts&&... params)
{
    cout <<__PRETTY_FUNCTION__ <<endl;
    f(forward<Ts>(params)...);
}

int main()
{
    f({1,2,3});
    //fwd({1,2,3}); objaśnienie na stronie 247/248
    auto il = {1,2,3};
    fwd(il);
    vector<int> widgetVect;
    widgetVect.reserve(Widget::MinVals);
    f(Widget::MinVals);
    fwd(Widget::MinVals); //skompiluje się jedynie gdy mamy definicję statica
    //const size_t Widget::MinVals;
    //odwołanie potrzebuje adresu zmiennej Widget::MinVals czyli potrzebuje aby przydzielić jej pamięć i ją zdefiniować
    //"odwołanie jest pod spodem wskaźnikiem..."

    return 0;
}