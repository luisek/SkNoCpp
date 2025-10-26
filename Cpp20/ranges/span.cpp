#include <algorithm>
#include <iostream>
#include <ranges>
#include <span>
#include <vector>

using namespace std;

auto print_reverse(span<int> si) -> void {
  for (auto i : ranges::reverse_view{si}) {
    cout << i << " ";
  }
  cout << "\n";
}

int main() {
  vector<int> vi = {1, 2, 3, 4, 5};
  print_reverse(vi);

  span<int> si(vi);
  print_reverse(si.first(2));
  print_reverse(si.last(2));
}