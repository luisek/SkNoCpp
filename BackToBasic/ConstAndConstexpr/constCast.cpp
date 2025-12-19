#include <iostream>

int main() {
  int nonConstInt = 10;
  int *pNonConstInt = &nonConstInt;
  *pNonConstInt = 12;
  std::cout << nonConstInt << std::endl;

  const int constInt = 10;
  const int *pToConstInt = &constInt;
  int *pToInt = const_cast<int *>(pToConstInt);
  *pToInt =
      12; // undefined behaviour => modify object which was initially const
  std::cout << constInt << std::endl;
}