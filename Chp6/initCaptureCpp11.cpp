#include <iostream>
#include <memory>
#include <functional>

using namespace std;

/**
 * przechwytywanie inicjujące nie działa w przypadku C++11
 * można je osiągnąć w poniższy sposób
 **/

class Widget
{
public:
    Widget()
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
    ~Widget()
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
    Widget(Widget&& pt)
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
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

class IsValidAndCorrect
{
public:
    using DataType = unique_ptr<Widget>;

    explicit IsValidAndCorrect(DataType&& tpw) : pw(move(tpw))
    {
    }

    bool operator()() const
    {
        return pw->isCorrect() && pw->isValidated();
    }

private:
    DataType pw;
};

namespace mpb
{
    template<typename T, typename... Ts>
    std::unique_ptr<T> make_unique(Ts&&... params)
    {
        return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
    }
}

int main(int argc, char* argv[])
{
    auto func = IsValidAndCorrect(mpb::make_unique<Widget>());
    cout <<boolalpha <<func() <<endl;

    //lub można też krócej
    cout <<"Start\n";
    auto func2 = std::bind(
        [](const unique_ptr<Widget>& ptr)
        {
            return ptr->isCorrect() && ptr->isValidated();
        },
        mpb::make_unique<Widget>()
    );

    cout <<func2() <<endl;
    cout <<"End\n";
    
    cout <<"Return\n";
    return 0;
}
