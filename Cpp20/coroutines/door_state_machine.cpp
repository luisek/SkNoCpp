#include <coroutine>
#include <iostream>
#include <utility>

enum class DoorState { Closed, Opening, Open, Closing };

template <typename T> struct SimpleGenerator {
  struct promise_type {
    T value_;
    auto initial_suspend() noexcept { return std::suspend_always{}; }
    auto final_suspend() noexcept { return std::suspend_always{}; }
    auto get_return_object() {
      return SimpleGenerator{
          std::coroutine_handle<promise_type>::from_promise(*this)};
    }
    void unhandled_exception() { std::terminate(); }
    void return_void() {}
    auto yield_value(T value) {
      value_ = value;
      return std::suspend_always{};
    }
  };

  std::coroutine_handle<promise_type> handle_;
  explicit SimpleGenerator(std::coroutine_handle<promise_type> h) noexcept
      : handle_(h) {}
  SimpleGenerator(SimpleGenerator &&rhs) noexcept
      : handle_(std::exchange(rhs.handle_, {})) {}
  SimpleGenerator(const SimpleGenerator &) = delete;
  SimpleGenerator &operator=(const SimpleGenerator &) = delete;
  ~SimpleGenerator() {
    if (handle_)
      handle_.destroy();
  }
  T current_value() { return handle_.promise().value_; }
  bool move_next() {
    if (!handle_)
      return false;
    handle_.resume();
    return !handle_.done();
  }
};

void print_state(DoorState state) {
  switch (state) {
  case DoorState::Closed:
    std::cout << "Drzwi sa Zamkniete." << std::endl;
    break;
  case DoorState::Opening:
    std::cout << "Drzwi Otwieraja sie..." << std::endl;
    break;
  case DoorState::Open:
    std::cout << "Drzwi sa Otwarte." << std::endl;
    break;
  case DoorState::Closing:
    std::cout << "Drzwi Zamykaja sie..." << std::endl;
    break;
  }
}

SimpleGenerator<DoorState> door_state_machine() {
  // START: Stan poczatkowy
  co_yield DoorState::Closed;

  // --- Glowna petla maszyny stanow ---
  while (true) {
    // ZAMKNIETE (Closed) -> Czekanie na polecenie otwarcia
    // Po wznowieniu przechodzi do Opening
    std::cout << "DST Before Opening" << std::endl;
    co_yield DoorState::Opening;

    // OTWIERANIE (Opening) -> Osiagniecie stanu otwartego
    std::cout << "DST Before Open" << std::endl;
    co_yield DoorState::Open;

    // OTWARTE (Open) -> Czekanie na polecenie zamkniecia lub timeout
    // Po wznowieniu przechodzi do Closing
    std::cout << "DST Before Closing" << std::endl;
    co_yield DoorState::Closing;

    // ZAMYKANIE (Closing) -> Osiagniecie stanu zamknietego
    std::cout << "DST Before Closed" << std::endl;
    co_yield DoorState::Closed;
  }
}

int main() {
  std::cout << "--- Inicjalizacja Maszyny Stanow Drzwi ---" << std::endl;
  auto machine = door_state_machine();

  // START - pierwszy stan (initial_suspend)
  if (machine.handle_) {
    print_state(machine.current_value());
  }

  std::cout << "\n--- Symulacja 1: Otwarcie i Zamkniecie ---" << std::endl;

  // 1. ZAMKNIETE -> OTWIERANIE
  std::cout << "Zdarzenie: Nacisnieto przycisk OTWÓRZ" << std::endl;
  machine.move_next();
  print_state(machine.current_value());

  // 2. OTWIERANIE -> OTWARTE
  std::cout << "Zdarzenie: Silnik zakonczyl otwieranie" << std::endl;
  machine.move_next();
  print_state(machine.current_value());

  // 3. OTWARTE -> ZAMYKANIE
  std::cout << "Zdarzenie: Minął czas oczekiwania (TIMEOUT)" << std::endl;
  machine.move_next();
  print_state(machine.current_value());

  // 4. ZAMYKANIE -> ZAMKNIETE
  std::cout << "Zdarzenie: Silnik zakonczyl zamykanie" << std::endl;
  machine.move_next();
  print_state(machine.current_value());

  std::cout << "\n--- Symulacja 2: Ponowne Otwarcie ---" << std::endl;

  // 5. ZAMKNIETE -> OTWIERANIE (Cykl zaczyna sie od nowa)
  std::cout << "Zdarzenie: Nacisnieto przycisk OTWÓRZ" << std::endl;
  machine.move_next();
  print_state(machine.current_value());

  return 0;
}