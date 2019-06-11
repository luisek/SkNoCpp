#include <iostream>
#include <map>

int main()
{
    std::map<std::string, int> mapUserAge {{"Alex", 45}, {"John", 25}};
    std::map mapCopy{mapUserAge};

    if(auto [iter, wasAdded] = mapCopy.insert_or_assign("John", 26); !wasAdded)
    {
        std::cout <<iter->first <<" reasigned... \n";
    }

    for(const auto& [key, value] : mapCopy)
    {
        std::cout <<key <<", " <<value <<'\n';
    }

    return 0;
}