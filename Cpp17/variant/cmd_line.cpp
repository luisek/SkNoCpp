#include <charconv>
#include <iostream>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>

class CmdLine {
public:
  using Arg = std::variant<int, float, std::string>;

private:
  std::map<std::string, Arg> mParsedArgs;

  static auto TryParseString(std::string_view sv) -> Arg {
    // first try with float
    float fResult = 0.0f;
    const auto last = sv.data() + sv.size();
    const auto res = std::from_chars(sv.data(), last, fResult);
    if (res.ec != std::errc{} || res.ptr != last) {
      // if not possible, then just assume it's a string
      return std::string{sv};
    }
    // no fraction part? cast to int
    if (static_cast<int>(fResult) == fResult) {
      return static_cast<int>(fResult);
    }
    return fResult;
  }

public:
  explicit CmdLine(int argc, const char **argv) { ParseArgs(argc, argv); }

  auto Find(const std::string &name) const -> std::optional<Arg> {
    if (const auto it = mParsedArgs.find(name); it != mParsedArgs.end()) {
      return it->second;
    }
    return {};
  }

  auto ParseArgs(int argc, const char **argv) -> void {
    // the form: -argName value -argName value
    for (int i = 1; i < argc; i += 2) {
      if (argv[i][0] != '-') {
        throw std::runtime_error("wrong command name");
      }
      mParsedArgs[argv[i] + 1] = TryParseString(argv[i + 1]);
    }
  }
};

int main(int argc, const char **argv) {
  try {
    CmdLine cmdLine(argc, argv);
    if (auto arg = cmdLine.Find("paramInt"); arg)
      std::cout << "paramInt is: " << std::get<int>(*arg) << "\n";
    if (auto arg = cmdLine.Find("paramFloat"); arg) {
      if (const auto &intPtr = std::get_if<int>(&*arg); intPtr) {
        std::cout << "paramFloat is: " << *intPtr << " (integer)\n";
      } else {
        std::cout << "paramFloat is: " << std::get<float>(*arg) << '\n';
      }
    }
    if (auto arg = cmdLine.Find("paramText"); arg) {
      std::cout << "paramText is: " << std::get<std::string>(*arg) << "\n";
    }
  } catch (std::bad_variant_access &err) {
    std::cerr << "... err accessing a wrong variant type." << err.what()
              << '\n';
  } catch (std::runtime_error &err) {
    std::cerr << "... err: " << err.what() << "\n";
  }
}
