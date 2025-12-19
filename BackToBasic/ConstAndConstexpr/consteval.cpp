#include <algorithm>
#include <iostream>
#include <vector>

/*
generate an immediate function
every call of an immediate function generates a constant expression that is
executed at compile time

cannot be applied to destructor
has the same requremnts as a conxtexpr func
*/
consteval int sqr(int n) { return n * n; }

int main() {
  constexpr int r = sqr(5);
  // int r = sqr(10);
}