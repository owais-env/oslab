#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void worker() {
    cout << "jthread worker is running.\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "jthread worker finished.\n";
}

int main() {
    {
        jthread jt(worker);
        cout << "jthread created. It will automatically join on scope exit.\n";
    }
    cout << "Scope ended safely.\n";
    return 0;
}
