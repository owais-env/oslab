#include <iostream>
#include <future>
#include <thread>
using namespace std;

int heavy_calculation(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i)
        sum += i;
    return static_cast<int>(sum);
}

int main() {
    future<int> fut = async(launch::async, heavy_calculation, 10000);

    cout << "Main thread continues other work...\n";
    this_thread::sleep_for(chrono::milliseconds(200));

    cout << "Async result: " << fut.get() << '\n';
    return 0;
}
