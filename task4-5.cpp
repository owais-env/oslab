#include <iostream>
#include <thread>
using namespace std;

int counter = 0;

void increment_routine() {
    for (int i = 0; i < 100000; ++i)
        counter++;
}

int main() {
    thread t1(increment_routine);
    thread t2(increment_routine);
    t1.join();
    t2.join();

    cout << "Expected result: 200000\n";
    cout << "Actual result (race condition): " << counter << '\n';
    cout << "Result may vary because counter is not synchronized.\n";
    return 0;
}
