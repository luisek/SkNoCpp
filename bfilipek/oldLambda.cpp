#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;



int main()
{
    //--std=c++98 błąd kompilacji nie można utworzyc instancji szablonu 
    struct PrintFunctor
    {
        void operator()(int x)
        {
            cout << x <<endl;
        }
    };

    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    for_each(v.begin(), v.end(), PrintFunctor());
    for_each(v.begin(), v.end(), [](int x){cout <<x <<'\n';});

    return 0;
}