#include <iostream>
#include <string>
#include <chrono>

namespace mpb
{
    template<typename T>
    //typename std::remove_reference<T>::type&&
    decltype(auto) 
    move(T&& param)
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
    static int counter;
private:
    std::string name;
    
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

void process(const Widget& lw)
{
    std::cout <<__PRETTY_FUNCTION__ <<std::endl;
    std::cout << lw.counter <<std::endl;
}

void process(const Widget&& rw)
{
    std::cout <<__PRETTY_FUNCTION__ <<std::endl;
    std::cout <<rw.counter <<std::endl;
}

template<typename T>
void logAndProcess(T&& param)
{
    auto now = std::chrono::system_clock::now();
    std::cout <<__PRETTY_FUNCTION__ << std::endl;
    std::cout <<"LOG: YOLO!" <<std::endl;
    //std::cout <<"LOG: " <<std::chrono::duration<double>(now) <<std::endl;
    process(std::forward<T>(param));
}

int main(int argc, char* argv[])
{
    const Widget cw("Ab");

    Annotation an(cw);

    Widget w("Ww");

    logAndProcess(w);
    logAndProcess(mpb::move(w));

    return 0;
}