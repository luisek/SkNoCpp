#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int main() {
  auto print_int = [](int i) { cout << i << " "; };
  auto is_even = [](int i) { return i % 2 == 0; };

  vector<int> v{6, 2, 3, 4, 5, 6};

  // vew is defined -- no calculation performed
  auto after_leading_evens = ranges::views::drop_while(v, is_even);

  ranges::for_each(after_leading_evens, print_int);
  cout << endl;
}