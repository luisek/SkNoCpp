#include <iostream>
#include <tuple>
#include <map>

using namespace std;


struct Point
{
    double x;
    double y;
};

Point getStartPoint()
{
    return {0.0, 0.0};
}

int main()
{
    double myArray[3] = {1.0, 2.0, 3.0};
    auto [a, b, c] = myArray;
    cout <<"array print: ";
    cout << a << b << c <<endl;

    auto& [d, e, f] = myArray;
    d = 5.0;
    f = 8.0;
    cout <<d <<e <<f <<endl;

    auto [x, y] = getStartPoint();
    cout <<"Start point: (" <<x <<", " <<y <<")" <<endl;

    map<int, bool> myMap{{1, true}, {2, false}, {3, true}, {4, false}};

    for(const auto & [key, value] : myMap)
    {
        cout <<"(" <<key <<", " <<boolalpha <<value <<")" <<endl;
    }

    map<int, double> myMap2{{1,2.0}, {2, 3.0}};

    for(auto& [key, value] : myMap2)
    {
        cout <<"myMpa2[" <<key <<"] = " <<value <<endl;
        value = 0.0;
    }

    for(const auto& [key, value] : myMap2)
    {
        cout <<"myMap2[" <<key <<"] = " <<value <<endl;
    }

    return 0;
}