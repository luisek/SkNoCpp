#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> stopFlag{false};

void work() {
    while (!stopFlag) {
        std::cout << "Working...\n";
    }
}

int main() {
    std::thread t(work);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    stopFlag = true; // Signal the thread to stop
    t.join();        // Must explicitly join
    return 0;
}