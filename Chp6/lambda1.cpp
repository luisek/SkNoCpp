#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

using FilterContainer = vector<function<bool(int)>>;
FilterContainer filters;

class Widget
{
public:
    Widget() : divisor{3}
    {}
    void addFilter()
    {
        auto copyDivisor = divisor;
        filters.emplace_back(
            [copyDivisor](int value) {return value % copyDivisor == 0;}
        );
    }
private:
    int divisor;
};

void doSomeWork()
{
    /*
    void addFilter()
    {
        auto copyThis = this;
        filters.emplace_back(
            [copyThis](int value) {return value % copyThis->divisor == 0;}
        );
    }
    ponieważ lambda przechwytuje przez kopię wskaźnik this powoduje to w następstwie zawiśnięcie wskaźnika
    w poniższym kodzie tworzymy wskaźnik klasy Widget który wywołuje addFilter po wykoniau fukncji uruchomienie
    którejś z funkcji znajdujących się w filters spowoduje booom!
    Rozwiązanie stworzyć kopię divisor;
    auto divisorCopy = divisor
    C++14:
    [divisor=divisor]
    */
    auto pw = make_unique<Widget>();

    pw->addFilter();
}


int computeValue1()
{
    return 2;
}

int computeValue2()
{
    return 1;
}

int computeDivisor(int calc1, int calc2)
{
    return calc1 + calc2;
}

void addDivisorFilter()
{
    auto calc1 = computeValue1();
    auto calc2 = computeValue2();

    auto divisor = computeDivisor(calc1, calc2);

    filters.emplace_back(
        [&divisor](int value){return value % divisor == 0;}
    );
    /*
    Gdy tylko wychodzimy z funkcji addDivisor zmienna divosor przestaje istnieć a wywołując funkcję
    z kontenera prowadzimy do niezdefiniowanego zachowania.
    C++11 lepiej jawnie określać listę zmiennych lokalnych i parametrów, od których zależy wyrażenie lambda
    rozwiązanie przekazanie przez wartość [=] ale też może spowodować zawiśnięcie w przypadku kopiowania wskaźników
    -gdy przez wartoś przekazujemy wskaźnik który jest kopiowany...
    */
}

template <typename C>
void workWithContainer(const C& container)
{
    auto calc1 = computeValue1();
    auto calc2 = computeValue2();

    auto divisor = computeDivisor(calc1, calc2);

    using ContElemT = typename C::value_type;

    using std::begin;
    using std::end;

    //w C++14 mozemy pozbyć się ContElemT i zastąpić to auto
    //usuwamy też using ContElemT
    if(std::all_of(
        begin(container), end(container),
        [&](const ContElemT& value)
        {return value % divisor == 0;}
    ))
    {
        cout <<"its OK! \n";
    }
    else
    {
        cout <<"its NOK! \n";
    }
}

int main()
{
/*    addDivisorFilter();
    for(auto f : filters)
    {
        cout << f(9) <<'\n';
    }
*/
    doSomeWork();
    for(auto fun : filters)
    {
        cout <<fun(3) <<endl;
    }

    vector<int> values{3, 6, 9, 12, 15, 2};
    workWithContainer(values);

    return 0;
}
