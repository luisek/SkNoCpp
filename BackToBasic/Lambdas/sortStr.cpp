#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

auto print(const std::vector<std::string> &items) {
  for (const auto &item : items) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

int main() {
  auto coll = std::vector<std::string>{"Here",   "are", "some",   "cities",
                                       "Berlin", "LA",  "London", "Cologne"};
  std::ranges::sort(coll);
  print(coll);
  std::ranges::sort(coll, [](const std::string &s1, const std::string &s2) {
    auto toUpper = [](auto item) { return std::toupper(item); };
    return std::ranges::lexicographical_compare(s1, s2, std::less{}, toUpper,
                                                toUpper);
  });
  print(coll);
}