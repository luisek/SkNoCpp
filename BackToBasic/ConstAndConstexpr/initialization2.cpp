#include <iostream>

/*
Can we initialize sth at compile time but is still local and we can modify it
*/

consteval auto doubleMe(auto val) { return 2 * val; }
int main() {
  auto res = doubleMe(1010);
  ++res;
}