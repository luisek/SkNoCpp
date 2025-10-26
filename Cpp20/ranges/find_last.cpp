#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
using namespace std;

int main() {
  string path = "/foo/bar/baz";

  auto leaf = std::ranges::find_last(path, '/') | std::ranges::views::drop(1);
  std::print("{}\n", std::string_view{leaf});
  return 0;
}