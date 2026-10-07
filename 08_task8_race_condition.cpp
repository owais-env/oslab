#include <iostream>
#include <thread>

long long counter = 0;

void increment_task() {
    for (int i = 0; i < 100000; ++i)
        ++counter;
}

int main() {
    std::thread t1(increment_task);
    std::thread t2(increment_task);

    t1.join();
    t2.join();

    std::cout << "Expected : 200000 | Actual counter : " << counter << '\n';
    std::cout << "Note: this program intentionally has a data race; the actual value is not guaranteed.\n";
    return 0;
}
