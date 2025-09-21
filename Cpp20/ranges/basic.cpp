#include <iostream>
#include <ranges>
#include <vector>

using namespace std;


int main()
{
   auto square_evens = ranges::views::filter([](auto x){ return int(x)%2==0;}) | ranges::views::transform([](auto x){return x*x;});
   auto vect = std::vector{1,2,3,4,5,6};

   auto tmp = square_evens(vect);
   for(const auto& i : tmp)
        cout<< i <<std::endl;

    return 0;
}