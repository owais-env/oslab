#include <iostream>
#include <thread>
#include <future>
using namespace std;

int main() {
    promise<int> prom;
    future<int> fut = prom.get_future();

    thread worker([&prom]() {
        int result = 42;
        prom.set_value(result);
    });

    cout << "Main thread waiting for worker result...\n";
    int result = fut.get();
    worker.join();

    cout << "Received value: " << result << '\n';
    return 0;
}
