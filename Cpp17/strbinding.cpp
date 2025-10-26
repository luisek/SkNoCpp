#include <iostream>

class MyClass {
public:
  auto GetA() const -> int { return a; }
  auto GetB() const -> float { return b; }

private:
  int a;
  float b;
};

template <std::size_t I> auto get(MyClass &c) {
  if constexpr (I == 0)
    return c.GetA();
  else if constexpr (I == 1)
    return c.GetB();
}

namespace std {
template <> struct tuple_size<MyClass> : std::integral_constant<size_t, 2> {};

template <> struct tuple_element<0, MyClass> {
  using type = int;
};
template <> struct tuple_element<1, MyClass> {
  using type = float;
};
} // namespace std

int main() {
  MyClass cs;

  auto [a, b] = cs;
}