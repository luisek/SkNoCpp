#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
#include <vector>

class TwoDIteratorJoin {
public:
  using Vect2D = std::vector<std::vector<int>>;
  using JoinView = std::ranges::join_view<std::ranges::ref_view<const Vect2D>>;
  using Iterator = std::ranges::iterator_t<JoinView>;

  explicit TwoDIteratorJoin(const Vect2D &data)
      : flattened_(data | std::views::join), iter_(flattened_.begin()),
        end_(flattened_.end()) {}

  [[nodiscard]] auto has_next() const -> bool { return iter_ != end_; }

  [[nodiscard]] auto next() -> int {
    if (!has_next())
      throw std::out_of_range("No more elements");
    return *iter_++;
  }

private:
  JoinView flattened_;
  Iterator iter_, end_;
};

int main() {
  const std::vector<std::vector<int>> input = {{1, 2}, {3}, {}, {4, 5, 6}};
  TwoDIteratorJoin it(input);

  while (it.has_next())
    std::print("{} ", it.next());
  return 0;
}