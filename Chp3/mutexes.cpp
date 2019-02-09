#include <iostream>
#include <thread>
#include <atomic>
#include <string>

using namespace std;

class Widget
{
public:
    
    int compute() const
    {
        if(cacheValid)
        {
            cout <<cachedValue.load() <<'\n';
            return cachedValue;
        }
        else
        {
            auto newValue = computeValue();
            cachedValue = newValue;
            cacheValid = true;
            cout <<cachedValue.load() <<'\n';
            return cachedValue;
        }
        
    }

private:

    int computeValue() const
    {
        return 1000;
    }
    /*
    użycie dwóch zmiennych typu atomic nie jest bezpieczne
    program po wyliczeniu computeValue() i przypisaniiu jej do zmiennej cachedValue
    może przerwać wywołanie wątku i zacząć wyołanie drugiego, co spowoduje, że drugi wątek
    jeszcze raz wywoła computeValue.
    Zmiana kolejności też nie bardzo pomoże ponieważ jeśli przypiszemy true do chacedValid
    to zmienna cachedValues może mieć jeszcze nie przeliczone wartości i zwrócić śmieci.

    W tym przypadku najlepiej jest po prostu utwożyć:
    jako zmienne klasy
    mutable mutex m;
    mutable bool cachedValid{false};
    mutable int cachedValue;

    w metodzie compute()
    na początku wywołujemy lock_guard<mutex> guard(m);
    */

    mutable atomic<bool> cacheValid{false};
    mutable atomic<int> cachedValue{0};
};

int main(int argc, char* argv[])
{
    Widget w;
    std::thread t1(&Widget::compute, &w);
    std::thread t2(&Widget::compute, &w);
    std::thread t3(&Widget::compute, &w);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
