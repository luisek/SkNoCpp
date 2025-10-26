#include <iostream>
#include <string>

int main() {
  const char *cstr = "Hello World";

  // the whole string;
  std::string_view sv1{cstr};
  std::cout << sv1 << ", len: " << sv1.size() << std::endl;

  std::string_view sv2{cstr, 5};

  std::cout << sv2 << ", len: " << sv2.size() << std::endl;
  std::cout << sv2.data() << ", with datalen: " << sv2.size() << std::endl;

  // from string
  std::string str = "Hello String";
  std::string_view sv3 = str;
  std::cout << sv3 << ", len: " << sv3.size() << std::endl;

  using namespace std::literals;
  std::string_view sv4 = "Hello\0 Supper world"sv;
  std::cout << sv4 << ", len: " << sv4.size() << std::endl;
  std::cout << sv4.data() << " - till zero\n";

  return 0;
}