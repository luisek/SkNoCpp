#include <coroutine>
#include <iostream>
#include <utility>

struct ReturnType {
  struct promise_type {

    auto get_return_object() -> ReturnType { return ReturnType{this}; }
    auto initial_suspend() -> std::suspend_always { return {}; }
    auto return_void() -> void {}
    auto unhandled_exception() -> void {
      std::cerr << "Unhandled Exception occurred" << std::endl;
      std::terminate();
    }
    auto final_suspend() noexcept -> std::suspend_always { return {}; }
  };
  // zawsze wywoływany prz co_await
  // value from co_await
  auto await_transform() noexcept {
    // customized version instead of using suspend_always or suspend_never
    struct awaiter {
      promise_type &pt;
      auto await_ready() const noexcept -> bool { return false; }
      auto await_resume() const noexcept -> void {}
      auto await_suspend(std::coroutine_handle<>) const noexcept -> void {}
    };
  }
  using Handle = std::coroutine_handle<promise_type>;
  Handle mHandler_{};

  explicit ReturnType(promise_type *p) : mHandler_{Handle::from_promise(*p)} {}
  ReturnType(ReturnType &&rhs)
      : mHandler_{std::exchange(rhs.mHandler_, nullptr)} {}
  ~ReturnType() {
    if (mHandler_) {
      mHandler_.destroy();
    }
  }

  auto finished() const -> bool { return mHandler_.done(); }

  auto resume() -> void {
    if (not finished()) {
      mHandler_.resume();
    }
  }
};

ReturnType hello_coroutine() {
  std::cout << "hello from the coroutine" << std::endl;
  co_await
}

int main() {
  auto co = hello_coroutine();
  co.resume();
  std::cout << "Coroutine finished? " << std::boolalpha << co.finished()
            << std::endl;
  return 0;
}