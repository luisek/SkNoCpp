#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int main() {
  vector<vector<int>> nested{{1, 2}, {3}, {}, {4, 5}};

  auto flat = nested | std::views::join;

  std::ranges::for_each(flat, [](auto e) { std::cout << e << ' '; });

  //     for (int i : flat) {
  //   cout << i << " ";
  // }

  return 0;
}