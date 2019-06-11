#include <iostream>
#include <map>
using namespace std;

int getValue()
{
    return 121;
}

int main(int argc, char* argv[])
{

    //vefore init statement
    {
        auto value = getValue();
        if(value == 12)
        {
            std::cout <<"IF value : " <<value <<std::endl;
        }
        else
        {
            std::cout <<"ELSE value: " <<value <<std::endl;
        }

    }

    //in c++17
    if(auto value = getValue(); value == 12)
    {
        std::cout <<"IF cpp17 value : " <<value <<std::endl;
    }
    else
    {
        std::cout <<"ELSE cpp17 value : " <<value <<std::endl;
    }

    std::map<int, string> myMap{{1,"mama"}, {2, "tata"}};

    if(auto [iter, succeeded] = myMap.insert({3, "babcia"}); succeeded)
    {
        cout <<"insert succeeded: " <<std::boolalpha <<succeeded <<" iter = " <<iter->second <<std::endl;
        for(const auto& [key, value] : myMap)
        {
            std::cout <<"myMap["<<key <<"] = " <<value <<std::endl;
        }
    }


    return 0;
}