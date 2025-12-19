#include <iostream>

constexpr int constexprVal = 100;
constinit int constinitVal = 100;

int main() {
  auto val = 100;
  const auto res = ++val;

  // std::cout << "++res " << ++res << std::endl; ERROR inc const
  // std::cout << "++constexprVal " << ++constexprVal << std::endl; ERROR

  std::cout << "++constinitVal " << ++constinitVal << std::endl;

  constexpr auto localConstexpr = 100;
  // constinit auto localConstinit = 100;
  //  initialization.cpp:16:18: error: ‘constinit’ can only be applied to a
  //  variable with static or thread storage duration
  //   16 |   constinit auto localConstinit = 100;
}