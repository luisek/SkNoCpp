#include <iostream>
#include <string>

namespace mpb
{
    template<typename T>
    decltype(auto) move(T&& param)
    {
        std::cout <<__PRETTY_FUNCTION__ <<std::endl;
        using ReturnType = typename std::remove_reference<T>::type&&;
        return static_cast<ReturnType>(param);
    }
}

class Widget
{
public:
    Widget(const std::string _name) : name{_name}
    {
        std::cout <<__PRETTY_FUNCTION__ <<std::endl;
        ++counter;
    }
    Widget(const Widget& other)
    {
        std::cout <<__PRETTY_FUNCTION__ <<std::endl;
        counter = other.counter;
        ++counter;
        name = other.name;
    }

    Widget(Widget&& other)
    {
        std::cout <<__PRETTY_FUNCTION__ <<std::endl;
        counter = mpb::move(other.counter);
        ++counter;
        name = mpb::move(other.name);
    }

private:
    std::string name;
    static int counter;
};

int Widget::counter = 0;

class Annotation
{
public:
    /*
        z const Widget w wywoływany jest konstruktor kopiujący dla klasy Widget Widget(const Widget&) cecha const o tym decyduje
        strona 189 odwołanie do (const) l-wartości może być powiązane ze stałą (const) do r-wartości
    */
    explicit Annotation(const Widget w) : ww(mpb::move(w))
    //explicit Annotation(Widget w) : ww(mpb::move(w)) 
    {
        std::cout <<__PRETTY_FUNCTION__ <<std::endl;
    }
    ~Annotation()
    {
        std::cout <<__PRETTY_FUNCTION__ <<std::endl;
    }
private:
    Widget ww;
};


int main(int argc, char* argv[])
{
    const Widget w("Ab");

    Annotation an(w);

    return 0;
}