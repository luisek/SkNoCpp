#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <vector>
using namespace std;

int main() {
  vector<int> vec_int{0, 1, 2, 3, 4, 5};
  auto even = [](int i) -> bool {
    cout << "ev: " << i << "\n";
    return 0 == i % 2;
  };
  auto square = [](int i) -> int {
    cout << "sq: " << i << "\n";
    return i * i;
  };
  for (int i : vec_int | ranges::views::filter(even) |
                   ranges::views::transform(square)) {
    cout << "for: " << i << "\n";
  }
}