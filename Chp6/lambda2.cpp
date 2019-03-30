#include <iostream>
#include <memory>

using namespace std;

class Widget
{
public:
    constexpr bool isValidated()
    {
        return true;
    }
    constexpr bool isCorrect()
    {
        return false;
    }
private:

};

int main(int argc, char* argv[])
{
    auto pw = make_unique<Widget>();
    int ch = 12;
    int cc = 22;
    int ccc = 122;

    /*
    przechwytywanie incjujące [pw=move(pw)]
    zasięg zmiennej po lewej stronie operator = jest inny niż zasię zmiennej po prawej
    pw (po lewej) jest zasięgiem kalsy domknięcia
    zasięg po prawej = move(pw) jest taki sam jak zasięg w którym jest definiowane wyrażenie lambda
    można też użyć [pw = make_unique<Widget>()] zamiast [pw=move(pw)]
    */
    auto func = [pw = move(pw), c = ch, d = cc, x = ccc]
    {
        return pw->isCorrect() && pw->isValidated();
    };

    cout <<boolalpha <<func() <<endl;

    cout <<sizeof(func) <<endl;
    cout <<sizeof(int) <<endl;
    return 0;
}