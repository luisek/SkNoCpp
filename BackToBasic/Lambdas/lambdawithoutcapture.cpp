#include <cstdlib>
#include <iostream>

// lambda without capture can be treaded as a pointer to function
int main() {
  std::atexit([]() { std::cout << "good bye\n"; });
}