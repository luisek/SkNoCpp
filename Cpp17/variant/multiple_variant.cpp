#include <iostream>
#include <string>
#include <variant>

using namespace std;

template <class... Ts> struct overload : Ts... {
  using Ts::operator()...;
};
template <class... Ts> overload(Ts...) -> overload<Ts...>;

struct Pizza {};
struct Chocolate {};
struct Salami {};
struct IceCream {};

int main() {

  std::variant<Pizza, Chocolate, Salami, IceCream> firstIngredient{IceCream{}};
  std::variant<Pizza, Chocolate, Salami, IceCream> secondIngredient{
      Chocolate{}};

  std::visit(overload{
                 [](const Pizza &p, const Salami &s) {
                   std::cout << "Pizza with Salami\n";
                 },
                 [](const Salami &p, const Pizza &s) {
                   std::cout << "Salami with Pizza\n";
                 },

                 [](const Chocolate &p, const IceCream &s) {
                   std::cout << "Chocolate with IceCream\n";
                 },

                 [](const IceCream &p, const Chocolate &s) {
                   std::cout << "IceCream with Chocolate\n";
                 },

                 [](const auto &p, const auto &s) { std::cout << "Invalid\n"; },
             },
             firstIngredient, secondIngredient);
  return 0;
}