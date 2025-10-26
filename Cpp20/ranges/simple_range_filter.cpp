#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

std::vector<int> get_data() {
  return std::vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14};
}

auto test_data() -> bool {
  //   auto values = get_data();
  //   auto result = std::all_of(std::begin(values), std::end(values),
  //                             [](const int i) { return i < 5; });
  // with ranges:
  auto result =
      std::ranges::all_of(get_data(), [](const int i) { return i < 5; });
  return result;
}

// 2) pipable range vies

auto test_data_2() -> bool {
  auto result = std::ranges::all_of(get_data() | std::ranges::views::drop(2) |
                                        std::ranges::views::take(2),
                                    [](const int i) { return i < 5; });
  return result;
}

// 3)simple solution for skip the first element from the loop

auto iterate_data() -> void {
  for (const auto &elem : get_data() | std::ranges::views::drop(1)) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

// 4) lazy transform has interesting implications

void iterate_with_index() {
  auto make_index = [idx = std::size_t{0}]<typename T>(const T &elem) mutable {
    return std::pair<std::size_t, const T &>{idx++, elem};
  };
  for (const auto &[index, elem] :
       get_data() | std::ranges::views::take(5) |
           std::ranges::views::transform(make_index)) {
    std::cout << "{" << index << "} : " << "{" << elem << "} \n";
  }
}

int main() {
  //   auto result = test_data();
  auto result = test_data_2();
  std::cout << "Result: " << result << std::endl;

  iterate_data();
  iterate_with_index();

  return 0;
}