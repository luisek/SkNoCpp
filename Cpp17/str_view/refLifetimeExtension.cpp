#include <iostream>
#include <string>
#include <vector>

auto generateVect() ->std::vector<int>
{
    return {4,5};
}

auto func() -> std::string
{
    std::string tmp{"TMP str"};
    return tmp;
}

int main()
{
    for (const auto& e : generateVect())
    {
        std::cout <<e <<" " <<&e <<std::endl;
    }


    for (auto& e : generateVect())
    {
        std::cout <<e <<" " <<&e <<std::endl;
    }

    std::string_view sv = func();
    auto t = func();

    std::cout <<t <<std::endl;
    std::cout <<"Sv: " <<sv <<", len: " <<sv.length() <<std::endl;

    return 0;
}