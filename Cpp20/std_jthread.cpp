#include <iostream>
#include <thread>

void work(std::stop_token stoken) {
    while (!stoken.stop_requested()) {
        std::cout << "Working...\n";
    }
}

int main() {
    std::jthread jt(work); // Automatically joins
    std::this_thread::sleep_for(std::chrono::seconds(1));
    jt.request_stop(); // Request the thread to stop
    return 0;
}