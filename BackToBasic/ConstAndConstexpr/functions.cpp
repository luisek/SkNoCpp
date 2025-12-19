#include <iostream>

int sqrRunTime(int n) { return n * n; } // run in runtime

consteval int sqrCompileTime(int n) { return n * n; } // run in compile time
constexpr int sqrRunOrCompileTime(int n) {
  return n * n;
} // run in compile time and runtime
int main() {
  // constexpr int prod1 = sqrRunTime(100); //ERROR
  //  functions.cpp:10:35: error: call to non-‘constexpr’ function ‘int
  //  sqrRunTime(int)’
  //  10 |   constexpr int prod1 = sqrRunTime(100);

  constexpr int prod2 = sqrCompileTime(100);
  constexpr int prod3 = sqrRunOrCompileTime(100);

  int x = 100;
  int prod4 = sqrRunTime(x);
  int prod5 = sqrCompileTime(x);
  //   functions.cpp:20:29: error: call to consteval function
  //   ‘sqrCompileTime(x)’ is not a constant expression
  //    20 |   int prod5 = sqrCompileTime(x);
  //       |               ~~~~~~~~~~~~~~^~~
  // functions.cpp:20:29: error: the value of ‘x’ is not usable in a constant
  // expression

  int prod6 = sqrRunOrCompileTime(x);
}