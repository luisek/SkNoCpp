#include <iostream>

void func(int *) {}
void funcConst(const int *) {}

int main() {
  const int myInt{1998};
  // func(myInt);
  int *myIntPtr = const_cast<int *>(&myInt);
  func(myIntPtr);

  const int *myConstIntPtr = const_cast<const int *>(myIntPtr);
  funcConst(myConstIntPtr);
  funcConst(myIntPtr);

  char myChar = 'Q';
  char *myCarPointer(&myChar);
  // int *intPointer2 = static_cast<int *>(myCarPointer); <=ERROR
  int *intPointer = (int *)(myCarPointer);
  *intPointer = 'A'; // undefined behaviour
}