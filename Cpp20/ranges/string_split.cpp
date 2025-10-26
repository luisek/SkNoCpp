#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

int main() {
  auto split_strings =
      std::string_view{"Hello world C++20"} | std::ranges::views::split(' ');

  for (const auto &st : split_strings) {
    std::cout << std::string_view{st.begin(), st.end()} << std::endl;
    // for (char c : st)
    //   std::cout << c;
    // std::cout << std::endl;
  }
  return 0;
}