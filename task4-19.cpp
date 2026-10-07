#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void worker(stop_token token) {
    int count = 0;
    while (!token.stop_requested()) {
        cout << "Worker is running... " << ++count << '\n';
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    cout << "Worker received stop request and cleaned up.\n";
}

int main() {
    jthread jt(worker);

    this_thread::sleep_for(chrono::seconds(2));
    cout << "Manager requests worker to stop.\n";
    jt.request_stop();

    return 0;
}
