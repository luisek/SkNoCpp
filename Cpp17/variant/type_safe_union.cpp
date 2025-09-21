#include <iostream>

enum class DataType { Integer, String, Float };

struct SafeData {
  DataType type_;
  union {
    int i_;
    char str_;
    float f_;
  } data_;
};

int main() {
  SafeData safe_;
  safe_.type_ = DataType::Integer;
  safe_.data_.i_ = int(100);

  std::cout << safe_.data_.i_;
  return 0;
}
