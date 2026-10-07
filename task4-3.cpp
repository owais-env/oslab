#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void logger() {
    for (int i = 1; i <= 5; ++i) {
        cout << "Background logger running... " << i << '\n';
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "Logger finished.\n";
}

int main() {
    thread t(logger);
    t.detach();

    cout << "Main thread continues without join().\n";
    this_thread::sleep_for(chrono::seconds(6));
    cout << "Main thread finished.\n";
    return 0;
}
