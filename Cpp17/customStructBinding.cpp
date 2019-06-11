#include <iostream>
#include <tuple>

class UserEntry
{
public:
    void Load() { name = "Jan"; age=33; }
    std::string GetName() const
    {
        return name;
    }

    unsigned GetAge() const
    {
        return age;
    }

    std::string& GetName()
    {
        return name;
    }

    unsigned& GetAge()
    {
        return age;
    }

private:
    std::string name;
    unsigned age { 0 };
    size_t cacheEntry { 0 }; // not exposed
};

template <size_t I>
auto get(const UserEntry& u)
{
    if constexpr (I == 0)
        return u.GetName();
    else if constexpr (I == 1)
        return u.GetAge();
}

/* zamiast tego /\ (co na górze) if constexpr można napisać pojedyńcze getery
template<>
std::string get<0>(const UserEntry& u)
{
    return u.GetName();
}

template<>
unsigned get<1>(const UserEntry& u)
{
    return u.GetAge();
}
*/

namespace std
{
    template <> struct tuple_size<UserEntry> : std::integral_constant<size_t, 2> { }; //specifies how many elements are available
    template <> struct tuple_element<0,UserEntry> { using type = std::string; }; //defines the types for a specific element
    template <> struct tuple_element<1,UserEntry> { using type = unsigned; }; // ------//------ ------//------ ------//------
}

int main (int argc, char* argv[])
{
    UserEntry u;
    u.Load();
    auto [name, age] = u;

    std::cout <<name <<std::endl;
    std::cout <<age <<std::endl;

    name = "Tomek";

    std::cout <<" Changed: " <<u.GetName() <<' ' <<std::endl;

    return 0;
}
