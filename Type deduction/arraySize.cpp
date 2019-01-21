#include <iostream>

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N])
{
    return N;
}

int main(int argc, char const *argv[])
{
    int keyValues[] = {1, 2, 3, 4, 5};
    std::cout <<arraySize(keyValues);
    return 0;
}
