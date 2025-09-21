#include <iostream>
#include <vector>
using namespace std;

template <typename ...Args>
void FoldPrint(Args&&... args)
{
    auto sprarateLine = [](const auto& v) {
        std::cout <<v <<"\n";
    };
    (..., sprarateLine(std::forward<Args>(args)));
}

template<typename T, typename ...Args>
auto push_back_vect(std::vector<T>& cont, Args&& ...args)
{
    (cont.push_back(std::forward<Args>(args)),...);
}

template <typename ... T>
auto sum(T ... args)
{
    return (args + ...);
}

int main()
{
    FoldPrint("Hello world", 12, 33.43);

    std::vector<float> vectF;
    push_back_vect(vectF, 1.0f, 123.32f, 123.2f);
    for(const auto el : vectF)
    {
        std::cout <<el <<' ';
    }

    std::cout <<sum();
}