#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex m;

void add() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(m);
        ++counter;
    }
}

int main() {
    std::thread t1(add);
    std::thread t2(add);
    t1.join();
    t2.join();
    std::cout << "Final counter: " << counter << "\n";
    return 0;
}