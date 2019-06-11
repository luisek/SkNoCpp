#include <iostream>
#include <set>
#include <tuple>
using namespace std;

set<int> mySet;

pair<std::set<int>::iterator, bool> insertElement(int el)
{
    return mySet.insert(el);
}

int main(int argc, char* argv[])
{
    bool inserted {false};
    std::set<int>::iterator iter;

    for(auto i = 0; i < 10; ++i)
    {
        std::tie(iter, inserted) = insertElement(i);
        if(inserted && iter != mySet.end())
        {
            cout <<"Element: " <<*iter <<", inserted: " <<inserted <<endl;
        }
        else
        {
            cout <<"Element not inserted: " <<inserted <<endl;
        }
    }

    auto [iter2, inserted2] = insertElement(5);
    if(inserted2 && iter2 != mySet.end())
    {
        cout <<"Element: " <<*iter2 <<", inserted: " <<inserted2 <<endl;
    }
    else
    {
        cout <<"Element not inserted: " <<inserted2 <<endl;
    }

    const auto& [iter3, inserted3] = insertElement(15);
    if(inserted3)
    {
        cout <<"Element: " <<*iter3 <<", inserted: " <<std::boolalpha <<inserted3 <<'\n';
    }
    else
    {
        cout <<"Element not inserted\n";
    }

    return 0;
}