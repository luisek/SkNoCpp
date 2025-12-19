#include <chrono>
#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>

// Zwykła klasa Timer, która implementuje logikę dla co_await
class Timer {
private:
  std::chrono::milliseconds duration_;
  std::coroutine_handle<> continuation_;

  // Symulacja prostej petli zdarzen (ktora wznowi korutyne)
  static void wait_and_resume(std::coroutine_handle<> handle,
                              std::chrono::milliseconds ms) {
    std::this_thread::sleep_for(ms);
    if (handle) {
      handle.resume(); // Wznawia korutyne po uplywie czasu
    }
  }

public:
  Timer(std::chrono::milliseconds ms) : duration_(ms) {}

  // 1. await_ready: Czy jest gotowy do wznowienia (czy opóźnienie już minęło?)
  bool await_ready() const noexcept {
    return duration_ <= std::chrono::milliseconds(0);
  }

  // 2. await_suspend: Logika zawieszenia (co się stanie, gdy korutyna się
  // zawiesi)
  void await_suspend(std::coroutine_handle<> handle) noexcept {
    continuation_ = handle; // Zapisz uchwyt korutyny (do wznowienia)

    // ZAWIESZ: Uruchom nowy wątek, który po uplywie czasu wznowi korutyne.
    // W prawdziwym kodzie I/O uzywa się puli wątków lub timera w systemie
    // operacyjnym.
    std::thread([this] { wait_and_resume(continuation_, duration_); }).detach();
  }

  // 3. await_resume: Co się zwróci po wznowieniu
  void await_resume() const noexcept {
    // Nie zwracamy nic, po prostu kontynuujemy
  }
};

// Minimalna struktura dla obiektu zwracanego (Return object)
struct SimpleTask {
  struct promise_type {
    SimpleTask get_return_object() { return {}; }
    std::suspend_never initial_suspend() noexcept { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() { throw; }
    void return_void() {}
  };
};

// Korutyna, która wykonuje zadanie z opóźnieniem
SimpleTask delay_task(int id, std::chrono::milliseconds ms) {
  std::cout << "Task " << id << " rozpoczal dzialanie w w. "
            << std::this_thread::get_id() << std::endl;

  // Użycie co_await na obiekcie Timer
  // Korutyna zostaje ZAWIESZONA i zwraca kontrole
  co_await Timer(ms);

  // WZNOWNIENIE: To miejsce jest osiągnięte dopiero po upływie czasu 'ms'
  std::cout << "Task " << id << " wznowiony i zakonczyl dzialanie w w. "
            << std::this_thread::get_id() << " po " << ms.count() << "ms."
            << std::endl;
}

int main() {
  std::cout << "Glowny watek (ID: " << std::this_thread::get_id()
            << ") rozpoczyna." << std::endl;

  // Uruchomienie dwoch asynchronicznych zadan (korutyn)
  delay_task(1, std::chrono::milliseconds(2000));
  delay_task(2, std::chrono::milliseconds(1000));

  // Glowny watek wykonuje inne prace, nie czekając
  std::cout << "Glowny watek wykonuje inne zadanie." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "Glowny watek dalej pracuje (0.5s minelo)." << std::endl;

  // Czekamy na zakonczenie korutyn (musimy dac im czas)
  std::this_thread::sleep_for(std::chrono::milliseconds(2500));

  std::cout << "Glowny watek konczy." << std::endl;

  return 0;
}