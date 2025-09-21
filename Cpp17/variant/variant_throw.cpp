#include <iostream>
#include <variant>

using namespace std;

class ThrowClass {
public:
  explicit ThrowClass(int i) {
    if (i == 0) {
      throw int(10);
    }
  }
  operator int() { throw int(10); }
};

int main() {
  std::variant<int, ThrowClass> v{100};
  try {
    v = ThrowClass(0);
  } catch (...) {
    std::cout << "catch(...)\n";
    std::cout << v.valueless_by_exception() << '\n';
    std::cout << std::get<int>(v) << '\n';
  }

  try {
    v.emplace<0>(ThrowClass(10));
  } catch (...) {
    std::cout << "catch(...)\n";
    std::cout << v.valueless_by_exception() << '\n';
    std::cout << std::get<int>(v);
  }
}