#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>

int main() {
  auto square = [](int x) { return x * x; };
  auto add = [](int x, int y) { return x + y; };
  auto print_val = [](int i) { std::cout << i << std::endl; };

  auto square_view = std::ranges::views::iota(0) // infinite range
                     | std::ranges::views::transform(square) |
                     std::ranges::views::take(5);

  std::ranges::for_each(square_view, print_val);

  int total = std::ranges::fold_left(square_view, 0, add);
  std::print("{}\n", total);
  // std::print("{}\n", square_view | std::ranges::views::enumerate);
}