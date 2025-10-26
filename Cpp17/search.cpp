#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

int main() {
  std::string testString = "Hello Super World";
  std::string needle = "Super";

  const auto it = std::search(
      std::begin(testString), std::end(testString),
      std::boyer_moore_searcher(std::begin(needle), std::end(needle)));

  if (it == std::end(testString)) {
    std::cout << "The string " << needle << " not found\n";
  } else {
    std::cout << "Found " << std::distance(std::begin(testString), it)
              << std::endl;
  }
}