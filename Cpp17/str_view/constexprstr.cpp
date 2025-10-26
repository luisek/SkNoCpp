#include <string_view>

int main() {
  using namespace std::literals;

  constexpr auto strv = "Hello Programming World"sv;
  constexpr auto strvCut = strv.substr("Hello "sv.size());

  static_assert(strvCut == "Programming World"sv);
  return strvCut.size();
}