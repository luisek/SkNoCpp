#include <iostream>
#include <optional>

using namespace std;

class MyClass 
{
public:
    MyClass(std::string name) 
    {
        cout << __PRETTY_FUNCTION__ <<" " <<name <<endl;
    }
    MyClass(const MyClass& tmp)
    {
        cout << __PRETTY_FUNCTION__ <<endl;
    }
    MyClass& operator=(MyClass)
    {
        cout << __PRETTY_FUNCTION__ <<endl;
        return *this;
    }
    MyClass(MyClass&&)
    {
        cout << __PRETTY_FUNCTION__ <<endl;
    }
    MyClass& operator=(MyClass&&)
    {
        cout << __PRETTY_FUNCTION__ <<endl;
        return *this;
    }
    ~MyClass()
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
    void whoIAm() const
    {
        cout <<__PRETTY_FUNCTION__ <<endl;
    }
};

std::optional<MyClass> returnMyClass(bool condition)
{
    if(condition)
    {
        return MyClass("MyTMP");
    }
    else
    {
        return nullopt;
    }

}

int main() 
{
    // std::optional<MyClass> tmp; //ctor of MyClass not called
    // std::optional<MyClass> tmp1(std::in_place); //ctor called with in_place
    if (auto ret = returnMyClass(true); ret.has_value())
    {
        ret->whoIAm();
    }
    cout <<"End" <<endl;

    return 0;
}