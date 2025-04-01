#include <iostream>


template <typename T>
void linePrinter(const T& x)
{
    if constexpr (std::is_integral_v<T>)
    {
        std::cout <<"num: " <<x <<'\n';
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        const auto frac = x - static_cast<long>(x);
        std::cout <<"flt: " <<x <<", frac " <<frac <<'\n';
    }
    else if constexpr(std::is_pointer_v<T>)
    {
        std::cout <<"ptr: ";
        linePrinter(*x);
    }
    else
    {
        std::cout <<x <<"\n";
    }
}

int main()
{
    int c = 123;
    int *ptr = &c;

    linePrinter(4);
    linePrinter(4.32);
    linePrinter(ptr);
    linePrinter("ttes");
}