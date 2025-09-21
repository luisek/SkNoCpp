#include <iostream>
#include <string>

using namespace std;


// auto StartFromWordStr(const std::string& strArg, const std::string& word) -> std::string
// {
//     return strArg.substr(strArg.find(word)); // substr create  new string
// }

auto StartFromWordStr(std::string_view strArg, std::string_view word) -> std::string_view
{
    return strArg.substr(strArg.find(word)); // substr create  new string
}



int main()
{
    std::string str{"Hello Amazing Programming Environment"};

    auto subStr = StartFromWordStr(str, "Programming Environment");
    std::cout << subStr <<"\n";

    return 0;
}