#include <algorithm>
#include <iostream>
#include <vector>

constexpr int maxElement() {
  std::vector myVect{1, 2, 45, 3};
  std::sort(myVect.begin(), myVect.end());
  return myVect.back();
}

int main() {
  std::cout << std::endl;
  constexpr int maxValues = maxElement();
  std::cout << "MaxValue: " << maxValues << std::endl;

  constexpr int maxValue2 = [] {
    std::vector myVect = {1, 3, 2, 5, 4};
    std::sort(myVect.begin(), myVect.end());
    return myVect.back();
  }();

  std::cout << "MaxValue2: " << maxValue2 << std::endl;
}