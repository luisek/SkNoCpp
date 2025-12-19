#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int main() {
  auto even = [](auto x) { return int(x) % 2 == 0; };
  auto square = [](auto x) { return x * x; };
  auto square_evens =
      ranges::views::filter(even) | ranges::views::transform(square);
  auto vect = std::vector{1, 2, 3, 4, 5, 6};

  auto tmp = square_evens(vect);
  std::ranges::for_each(tmp, [](auto x) { cout << x << ' '; });
  //   for (const auto &i : tmp)
  //     cout << i << std::endl;

  return 0;
}