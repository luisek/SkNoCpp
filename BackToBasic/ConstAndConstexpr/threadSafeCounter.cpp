#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class ThreadSafeCounter {
  mutable std::mutex m;
  int counter = 0;

public:
  auto get() const -> int {
    std::lock_guard<std::mutex> lk(m);
    return counter;
  }
  auto inc() -> void {
    std::lock_guard<std::mutex> lk(m);
    ++counter;
  }
};

int main() {
  std::vector<std::jthread> vect;
  ThreadSafeCounter counter;
  for (auto i = 0; i < 20; ++i) {
    vect.emplace_back([&counter] {
      counter.inc();
      std::cout << "counter: " << counter.get() << std::endl;
      counter.inc();
    });
  }
}