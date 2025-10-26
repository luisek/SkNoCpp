#include <deque>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int main() {
  vector<int> numbers = {1, 2, 3, 4, 5};
  auto squared = numbers |
                 ranges::views::transform([](int n) { return n * n; }) |
                 ranges::to<std::deque>();

  //   print("{}", squared);
  for (auto e : squared) {
    cout << e << endl;
  }
}