#include <iostream>
#include <memory>

template <typename Concrete, typename ...Ts>
std::unique_ptr<Concrete> constructArgs(Ts&& ...args)
{
    if constexpr(std::is_constructible_v<Concrete, Ts...>) //bez constexpr kod sie nie kompiluje jesli chcemy zapewnic wylaczenie galezi i pozwolic na dzialanie
    //w tym wypadku zwracanie nullptr musimy uzyc constexpr
        return std::make_unique<Concrete>(std::forward<Ts>(args)...);
    else
        return nullptr;
}


class Test
{
public:
    Test(int, int){}
};

int main()
{
    auto p = constructArgs<Test>(10,10,10);
    if(p == nullptr)
        std::cout <<"YES\n";
    auto pp = constructArgs<Test>(1,1);
}