#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


auto splitSV(std::string_view strv, std::string_view delims =" ") -> std::vector<std::string_view>
{
    auto output = std::vector<std::string_view>{};
    auto first = strv.begin();

    while(first != strv.end())
    {
        const auto second = std::find_first_of(first, std::cend(strv),
    std::cbegin(delims), std::cend(delims));
        if(first != second)
        {
            output.emplace_back(strv.substr(std::distance(strv.begin(), first), std::distance(first, second)));
        }
        if(second == strv.end())
            break;

        first = std::next(second);
    }
    return output;
}


int main()
{
    const std::string s{"Hello    Extra,,, Super, Amazing World"};
    for(const auto& word: splitSV(s, " ,"))
        std::cout <<word <<'\n';
}