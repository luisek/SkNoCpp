#include <cxxabi.h>
#include <iostream>
#include <memory>
#include <optional>
#include <ranges>
#include <typeinfo>
#include <vector>

using namespace std;

enum class DataType {
  SIMPLE,
  COMPLEX,
};

auto toString(const DataType &dataType) -> std::string {
  switch (dataType) {
  case DataType::COMPLEX: {
    return "COMPLEX";
  }
  case DataType::SIMPLE: {
    return "SIMPLE";
  }
  }
  return "YOLO";
}

class Data {
public:
  Data(int value, DataType dataType) : value_{value}, dataType_{dataType} {}

  auto getType() const -> std::optional<DataType> { return dataType_; }
  auto getValue() const -> int { return value_; }

private:
  int value_;
  std::optional<DataType> dataType_;
};

struct DataProcessed {
  DataProcessed(const Data &data) : data_{data} {}
  auto print() const {
    std::cout << "Processed data " << toString(*data_.getType())
              << " value: " << data_.getValue() << std::endl;
  }
  Data data_;
};

auto process(const Data &type) {
  std::cout << "Execute: " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << toString(*type.getType()) << std::endl;
  std::cout << type.getValue() << std::endl;
}

int main() {
  std::vector<Data> dataList;
  dataList.reserve(100);

  for (int i = 0; i < 100; ++i) {
    int randomValue = rand() % 100; // Random value between 0 and 99
    DataType randomType =
        (rand() % 2 == 0) ? DataType::SIMPLE : DataType::COMPLEX;
    dataList.emplace_back(randomValue, randomType);
  }

  for (const auto &data : dataList) {
    std::cout << "Value: " << data.getValue() << ", Type: "
              << (data.getType().value() == DataType::SIMPLE ? "SIMPLE"
                                                             : "COMPLEX")
              << std::endl;
  }

  auto ff = dataList | std::views::filter([](const auto &item) {
              return item.getType() == DataType::SIMPLE;
            }) |
            std::views::transform([](const auto &item) {
              process(item);
              return DataProcessed(item);
            });
  int status;
  std::unique_ptr<char, void (*)(void *)> demangled(
      abi::__cxa_demangle(typeid(ff).name(), nullptr, nullptr, &status),
      std::free);
  std::cout << (demangled ? demangled.get() : typeid(ff).name()) << std::endl;

  std::cout << typeid(ff).name();

  auto requests = std::vector<DataProcessed>{};
  for (auto f : ff) {
    requests.push_back(f);
  }

  std::cout << "Done" << std::endl;

  return 0;
}